Goldilocks
##################################################

..  index::
    single: test
    see: benchmark; test

What is Goldilocks?
==================================================

Goldilocks is a complete testing and runtime-benchmark framework,
based on MousePaw Games' :abbr:`LIT (Live-In Testing)` Standard. Although
:abbr:`LIT (Live-In Testing)` is inherently different from "unit testing" and
:abbr:`TDD (test-driven development)`, Goldilocks may be used for either
approach. It may also be used in conjunction with other testing systems.

The core idea of Goldilocks is that tests ship in the final code,
and can be loaded and executed within normal program execution via
a custom interface. A major advantage of this system is that benchmarks
may be performed on many systems without the need for additional
software.

Setting Up Tests
==================================================

..  index::
    single: test; structure

Structure
---------------------------------------------------

Every Goldilocks test is derived from the Test abstract class, which has
six functions that may be overloaded.

..  index::
    single: test; pre()

``pre()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is an optional function that sets up the test to be run. In cases where
a test is run multiple consecutive times, it is only called once. Thus, it
must be possible to call ``pre()`` once, and then successfully call ``run()``
any number of times.

The function must return true if setup was successful, and false otherwise,
to make sure the appropriate actions are taken.

``prefail()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is an optional function that tears down the test after a failed call to
``pre()``. It is the only function to be called in that situation, and it
will not be called under any other circumstances. It has no fail handler
itself, so ``prefail()`` must succeed in any reasonable circumstance.

The function should return a boolean indicating whether the tear-down was
successful or not.

..  NOTE:: Goldilocks currently ignores ``prefail()``'s return.

``run()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is the only required function for any test. It contains all the code for
the test run itself. After ``pre()`` is called once (optionally), ``run()``
must be able to handle any number of consecutive calls to itself.

There must always be a version of ``run()`` that accepts no arguments.
However, it is not uncommon to overload ``run()`` to accept a scenario string
(part of the LIT Standard) for generating a particular scenario, or
prompting a random one to be generated.

The function should return true if the test succeeded, and false if it failed.

..  IMPORTANT:: ``run()`` (with no arguments) should be consistent in its
    success. Assuming pre() was successful, if the first consecutive call to
    ``run()`` is successful, all subsequent calls to run() must also be successful.
    This is vital to the benchmarker functions, as they can call a single test
    up to 10,000 times. One consideration, then, is that run() should only use
    one scenario in a single lifetime, unless explicitly instructed by its
    function arguments to do otherwise.

``janitor()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is called after each repeat of ``run()`` during benchmarking and
comparative benchmarking. It is designed to perform cleanup in between
``run()`` calls, but not to perform first time setup (``pre())`` or end of
testing (``post()``) cleanup. It returns a boolean indicating success.

``post()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is an optional function which is called at the end of a test's normal
lifetime. It is the primary teardown function, generally responsible for
cleaning up whatever was created in ``pre()`` and ``run()``. It is normally
only if ``run()`` returns true, although it will be called at the end of
benchmarking regardless of ``run()``'s success.

This function should return a boolean indicating success. It has no fail
handler itself, so ``post()`` should succeed in all reasonable circumstances.

..  NOTE:: Goldilocks currently ignores ``post()``'s return.

``postmortem()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is an optional teardown function which is usually called if a test fails
(``run()`` returns false). It is responsible for cleaning up whatever was
created in ``pre()`` and ``run()``, much like ``post()`` is, but again only
for those scenarios where ``run()`` fails.

This function should return a boolean indicating success. It has no fail
handler itself, so ``postmortem()`` should succeed in all reasonable
circumstances.

..  index::
    single: test; creating

Creating a Test
----------------------------------------------------

Creating a test is as simple as creating a class that inherits from
``pawlib::Test (from goldilocks.hpp)``, which is a pure virtual base class.

..  IMPORTANT:: The constructor and destructor must obviously be defined,
    however, it is not recommended that they actually do anything - all setup
    and teardown tasks must be handled by the other functions in order to
    ensure proper functionality - a test instance is defined once when
    Goldilocks is set up, but it is highly likely to have multiple lifetimes.

Only bool ``run()`` must be defined in a test class. The rest of the
functions are already defined (they do nothing other than return true),
so you only need to define them if you require them to do something.

The following example exhibits a properly-defined, though overly
simplistic, test. In reality, we could have skipped ``pre()``, ``prefail()``,
``janitor()``, ``postmortem()``, and ``post()``, but they are defined to
demonstrate their behavior.

..  code-block:: c++

    #include <iochannel.hpp>
    #include <goldilocks.hpp>

    using namespace pawlib::ioformat;
    using namespace pawlib;

    class TestFoo : public Test
    {
      public:
          TestFoo(){}
          bool pre()
          {
              ioc << cat_testing << "Do Pre Stuff" << io_end;
              return true;
          }
          bool prefail()
          {
              ioc << cat_testing << "Do Prefail Stuff" << io_end;
              return true;
          }
          bool run()
          {
              ioc << cat_testing << "Do Test Stuff" << io_end;
              char str[5000] = {'\0'};
              for(int a=0;a<5000;a++)
              {
                  str[a] = 'A';
              }
              return true;
          }
          bool janitor()
          {
              ioc << cat_testing << "Do Janitorial Stuff" << io_end;
              return true;
          }
          bool postmortem()
          {
              ioc << cat_testing << "Do Postmortem Stuff" << io_end;
              return true;
          }
          bool post()
          {
              ioc << cat_testing << "Do Post Stuff" << io_end;
              return true;
          }
          ~TestFoo(){}
    };

..  index::
    single: test; registering

Registering a Test
----------------------------------------------------

Registering a test with Goldilocks is a trivial task, thanks to its
``register_test()`` function. Once a test class has been defined, as above,
simply register it via...

.. code-block:: c++

    //Assuming testmanager is our instance of the Goldilocks test manager.
    testmanager.register_test("TestFoo", new TestFoo);

Goldilocks will now actually own the instance of ``TestFoo``, and automatically
handle its deletion at the proper time.

.. WARNING:: Goldilocks actually requires exclusive ownership of each test
    object registered to it - thus, you should always pass the new declaration
    as the second argument. If you create the object first, and then pass the
    pointer, you run a high risk of a segfault or other undefined behavior.

The test can now be called by name using Goldilocks' various functions. (See below.)

..  index::
    single: test; running

Running a Test
----------------------------------------------------

Once a test is registered with Goldilocks, running it is quite easy.

..  code-block:: c++

    //Run the test once.
    testmanager.run_test("TestFoo");
    //Benchmark TestFoo on 100 repetitions.
    testmanager.run_benchmark("TestFoo", 100);
    //Compare TestFoo and TestBar on 100 repetitions.
    testmanager.run_compare("TestFoo", "TestBar", 100);
