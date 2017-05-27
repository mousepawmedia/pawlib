Goldilocks
##################################################

..  index::
    single: test
    single: suite
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
    single: test; get_title()

``get_title()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Returns a string (of type ``pawlib::testdoc_t``) with the title of the test.
This is a required function for any test.

..  NOTE:: The title is separate from the ID (name) of the test used to
    register the test with the TestManager. You use the ID (name) to refer
    to the test; the title is displayed on the screen before running
    the test.

..  index::
    single: test; get_docs()

``get_docs()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Returns a string (of type ``pawlib::testdoc_t``) with the documentation
string for the test. This should describe what the test does.
This is a required function for any test.

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

This is a required function for any test. It contains all the code for
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

        testdoc_t get_title()
        {
            return "Example Test";
        }

        testdoc_t get_docs()
        {
            return "This is the docstring for our example test."
        }

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

Setting Up Suites
=====================================================

A Suite is a collection of tests. In a typical use of Goldilocks, all tests
are organized into Suites.

In addition to allowing on-demand loading groups of tests, a Suite can be "batch
run", where all of its tests are run in succession. When one test fails, the
batch run halts and returns false.

..  index::
    single: suite; structure

Structure
-----------------------------------------------------

Every Goldilocks suite is derived from the ``TestSuite`` abstract class. This
only has two functions to overload, but both are required.

..  index::
    single: suite; get_title()

``get_title()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Returns a string (of type ``pawlib::testsuitedoc_t``) with the title of the
suite. This is the a required function for any test.

..  NOTE:: The title is separate from the ID (name) of the test used to
    register the test with the TestManager. You use the ID (name) to refer
    to the test; the title is displayed on the screen before running
    the test.

``load_tests()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This function specifies which tests belong to the suite.

``TestSuite`` provides a function ``register_test()`` which properly registers
each test with both the suite and the TestManager itself. For convenience, it
follows the same format as ``TestManager::register_test()``, with the exception
of an optional boolean argument for specifying a test which belongs to the
suite, but should not be part of the Suite's batch run.

One reason to exclude a test from the batch run for the Suite is if the test
is used only for comparative benchmarking.

Below is an example of a Suite's ``load_tests``.

..  code-block:: c++

    void TestSuite_FlexArray::load_tests()
    {
        // Register this test with both the suite and the test manager.
        register_test("t101", new TestFlex_Push);

        /* This test will be loaded by the suite, but will be excluded
         * from the batch run. */
        register_test("t101b", new TestVector_Push, false);

        register_test("t102", new TestFlex_Shift);
        register_test("t102b", new TestVector_Shift, false);

        register_test("t103", new TestFlex_ShiftAlt);

        register_test("t104", new TestFlex_Insert);
        register_test("t104b", new TestVector_Insert, false);
    }

We have registered seven tests with this suite. Upon loading the suite, all
seven tests will be loaded into the test manager. However, if we were to
batch run this suite, only four of those tests (t101, t102, t103, and t103)
would be run. This makes sense, because the other tests are only for
comparative benchmarking: t101b performs the exact same task as t101, but it
uses an external library. If we batch run this suite as a part of integration
testing, it wouldn't matter whether those comparative tests passed - they
would have no effect on our library's function.

Registering a Suite
----------------------------------------------------

Registering a suite with Goldilocks is as easy as registering a test. Simply
use its ``register_suite()`` function. Once a suite class has been defined,
as above, it is registered with...

..  code-block:: c++

    //Assuming testmanager is our instance of the Goldilocks test manager.
    testmanager.register_suite("TestSuiteFoo", new TestSuiteFoo());

As with tests, Goldilocks owns the instance of ``TestSuiteFoo``, and
automatically handles its deletion at the proper time.

..  WARNING:: Goldilocks requires exclusive ownership of each suite
    object registered to it, the same as it does tests.

Loading a Suite
---------------------------------------------------------

One of the major advantages of using a suite is that you can load its tests
on demand. This is especially useful if you have hundreds or thousands of tests.

..  code-block:: c++

    //Load a particular suite.
    testmanager.load_suite("TestSuiteFoo");

Of course, sometimes you don't want to have to load each suite manually.
As a shortcut, you can just load all suites currently registered with the
test manager by calling...

..  code-block:: c++

    //Load a particular suite.
    testmanager.load_suite();

Running a Suite
-------------------------------------------------------------

You can start a batch run of all the suite's tests using...

..  code-block:: c++

    //Batch run all tests in a suite.
    testmanager.run_suite("TestSuiteFoo");

Interactive Mode
=========================================================

..  WARNING:: This feature is under active development, and is subject
    to change dramatically.

Goldilocks provides a number of convenience functions to aid in creating an
interactive command-line interface for the system.

Functions
-----------------------------------------------------------

``list_suites()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can display the names and titles of all the tests currently registered
in the test manager using...

..  code-block:: c++

    // List all registered suites with their names and titles.
    testmanager.list_suites();

    // List all registered suites with their name only (no title).
    testmanager.list_suites(false);

``list_tests()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can display the names and titles of all the tests currently registered
(loaded) in the test manager using...

..  code-block:: c++

    // List all registered tests with their names and titles.
    testmanager.list_tests();

    // List all registered tests with their name only (no title).
    testmanager.list_tests(false);

If a test is loaded via a suite, it will not appear in this list until its
suite has actually been loaded during that session.

``i_load_suite()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Identical usage to ``load_suite()``, except it prompts the user for
confirmation before loading a suite.

``i_run_benchmark()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Identical usage to ``run_benchmark()``, except it prompts the user for
confirmation before running the benchmark.

``i_run_compare()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Identical usage to ``run_compare()``, except it prompts the user for
confirmation before running the compare.

``i_run_suite()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Identical usage to ``run_suite()``, except it prompts the user for
confirmation before running the suite.

``i_run_test()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Identical usage to ``run_test()``, except it prompts the user for
confirmation before running the test.
