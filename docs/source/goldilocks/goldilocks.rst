Goldilocks
##################################################

..  index::
    single: test
    single: suite
    see: benchmark; test

What is Goldilocks?
==================================================

Goldilocks is a complete testing and runtime-benchmark framework,
based on MousePaw Media' :abbr:`LIT (Live-In Testing)` Standard. Although
:abbr:`LIT (Live-In Testing)` is inherently different from "unit testing" and
:abbr:`TDD (test-driven development)`, Goldilocks may be used for either
approach. It may also be used in conjunction with other testing systems.

The core idea of Goldilocks is that tests ship in the final code,
and can be loaded and executed within normal program execution via
a custom interface. A major advantage of this system is that benchmarks
may be performed on many systems without the need for additional
software.

The fatest way to run tests in Goldilocks is with the :ref:`goldilocksshell`.

Including Goldilocks
---------------------------------------

To include Goldilocks, use the following:

..  code-block:: c++

    #include "pawlib/goldilocks.hpp"

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

You can also optionally register a comparative test for benchmarking, which
will be run against the main test in the benchmarker.

.. code-block:: c++

    //Assuming testmanager is our instance of the Goldilocks test manager.
    testmanager.register_test("TestFoo", new TestFoo, new TestBar);

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

.. _goldilocks_suites:

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

..  _goldilocks_setupsuites_structure_loadtests:

``load_tests()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This function specifies which tests belong to the suite.

``TestSuite`` provides a function ``register_test()`` which properly registers
each test with both the suite and the TestManager itself. For convenience, it
follows the same format as ``TestManager::register_test()``, with the exception
of an optional boolean argument for specifying a test which belongs to the
suite, but should not be part of the Suite's batch run.

One reason to exclude a test from the batch run for the Suite is if the test
is a stress test that takes a long time to run.

We can also register the comparative tests as an optional fourth argument.

Below is an example of a Suite's ``load_tests``.

..  code-block:: c++

    void TestSuite_MagicThing::load_tests()
    {
        /* Register this test with both the suite and the test manager.
         * Also register the comparative form. */
        register_test("t101", new MagicThing_Poof(), true, new OtherThing_Poof());

        register_test("t102", new MagicThing_Vanish());

        register_test("t103", new MagicThing_Levitate());

        register_test("t104", new MagicThing_Telepathy());

        /* This test will be loaded by the suite, but will be excluded
         * from the batch run. */
        register_test("t105", new MagicThing_SawInHalf(), true);
    }

We have registered five tests with this suite, not counting the comparative form
of the one. Upon loading the suite, all five tests will be loaded into the test
manager. However, if we were to batch run this suite, only four of those tests
(t101, t102, t103, and t104) would be run.

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

Interfacing Functions
=========================================================

Goldilocks provides a number of convenience functions to aid in creating an
interactive command-line interface for the system.

In most cases, you can probably just use the GoldilocksShell (see
`goldilocksshell`).

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

..  _goldilocks_benchmarker:

Benchmarker Output
===========================================================

The Goldilocks benchmarker outputs a *lot* of information.
This section describes how to read it.

Pass Types
--------------------------------

To account for the effects of cache warming, Goldilocks makes three passes,
each with a specific behavior:

* **Mama Bear** attempts to simulate a "cold cache," increasing the
  likelihood of cache misses. This is done by running tests A and B
  alternatingly.

* **Papa Bear** attempts to simulate a "hot cache," decreasing the
  likelihood of cache misses. This is done by running all repetitions of
  test A before running all repetitions of test B.

* **Baby Bear** attempts to simulate average (or "just right") cache
  warming effects, such as what might be seen in typical program
  executions. This is done by running eight repetitions of each test
  alternatingly - 8 As, 8 Bs, 8 As, etc.

After running all three passes, the benchmarker results are displayed.

Result Groups
-------------------------------

At the top of the results, we see the ``BASELINE MEASUREMENTS``. These
are based on measuring the actual measurement function of our
benchmarker.

These results are important, as this is an indicator of fluctuations in results
from external factors. If either of the :abbr:`RSD (Relative Standard Deviation)`
numbers are high (>10%), the results of the benchmarker may be thrown off.

Next, we see the individual results for each test beneath each pass type.
The verdict is displayed below both sets of results, indicating which test
was faster, and by how much. The verdict is ultimately the difference between
means, but if that difference is less than the standard deviation, it
will indicate that the tests are "roughly equal."

Statistical Data
---------------------------------

Let's break down the statistical data in our results.

Most lines show two sets of values, separated with a ``/`` character. The *left*
side is the **RAW** value, accounting for each measurement taken. The *right*
side is the **ADJUSTED** value, which is the value after outlier measurements
have been removed from the data.

The **MEAN (μ)** is the average number of CPU cycles for a single run of the
test.

The **MIN-MAX(RANGE)** shows the lowest and highest measurement in the set,
as well as the difference between the two (the range).

**OUTLIERS** shows how many values have been removed from the ADJUSTED set.
Outliers are determined mathematically, and removing them allows us to account
for external factors, such as other processes using the CPU during the
benchmark.

**SD (σ)** shows our standard deviation, which indicates how much fluctuation
occurs between results. By itself, the standard deviation is not usually
meaningful.

The **RSD**, or Relative Standard Deviation, is the percentage form of the
standard deviation. This is perhaps the most important statistic! The lower
the RSD, the more precise the benchmark results are. If the RSD is too high,
it will actually be flagged as red.

The statistical data above can provide a useful indicator of the reliability
of the benchmark results.

A high RSD may indicate that the results are "contaminated" by external factors.
It is often helpful to run the comparative benchmark multiple times, and taking
the pass with the lowest RSD.

However, higher RSDs may be the result of the tests themselves, as we'll see
in the following example.

Other warning signs that the results may be contaminated or inaccurate include:

* The presence of outliers in BASELINE.

* RSDs > 10% in BASELINE.

* Red-flagged RSDs (> 25%) (unless the test has a technical reason to fluctuate
  in CPU cycle measurements between tests).

* Significantly different verdicts between passes.

The precision and accuracy of the results may be further validated by
running the comparative benchmark multiple times, especially across computers,
and directly comparing the RSDs and verdict outcomes. While actual CPU cycle
measurements may vary greatly between similar systems, the relative outcomes
should remain fairly consistent on most systems with the same processor
architecture.

Statistical Data Example
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Let's look at the comparison between the "shift" (insert at beginning)
functionality of FlexArray and ``std::vector``. You can run this yourself
using the PawLIB tester, with the command ``benchmark P-tB1002``.

We always start by screening the baseline::

    BASELINE MEASUREMENTS
        MEAN (μ): 64 / 65
    	MIN-MAX(RANGE): 58-75(17) / 58-75(17)
    	OUTLIERS: 0 LOW, 0 HIGH
    	SD (σ): 5.47 / 5.38
    	RSD: 8% / 8%

We have no outliers and very low RSDs, so our results probably aren't
contaminated. Of course, benchmarking is unpredictable, and external factors
may change during the benchmarking itself. However, we have no reason here to
throw out the results.

Had we seen an RSD greater than 10% for either result, it would have
been wise to discard these results and rerun the benchmark altogether.

Now let's look at the first pass, MAMA BEAR, which is designed to demonstrate
the effects of cache misses::

    MAMA BEAR: [FlexArray: Shift 1000 Integers to Front (FlexArray)]
    	MEAN (μ): 414650 / 401451
    	MIN-MAX(RANGE): 262280-739036(476756) / 262280-323876(61596)
    	OUTLIERS: 0 LOW, 5 HIGH
    	SD (σ): 106700.22 / 76270.09
    	RSD: 25% / 18%

    MAMA BEAR: [FlexArray: Shift 1000 Integers to Front (std::vector)]
    	MEAN (μ): 904723 / 876586
    	MIN-MAX(RANGE): 664354-1537966(873612) / 664354-714892(50538)
    	OUTLIERS: 0 LOW, 5 HIGH
    	SD (σ): 232960.59 / 169329.87
    	RSD: 25% / 19%

Unsurprisingly, both results show some high outliers. The RSDs are roughly
equal, however, so this is probably the result of those cache misses
or other related factors.

..  WARNING:: How the two tests are structured matters! We are very careful
    to ensure both tests have the same structure and implementation, so the
    only difference between the two is the functions or algorithms we are
    directly comparing.

Looking at the result::

    MAMA BEAR: VERDICT
    	     RAW: [FlexArray: Shift 1000 Integers to Front (FlexArray)] faster by approx. 490073 cycles.
    	ADJUSTED: [FlexArray: Shift 1000 Integers to Front (FlexArray)] faster by approx. 398864.90807662549195 cycles.

FlexArray wins that round.

Now let's look at PAPA BEAR, which attempts to demonstrate cache warming::

    PAPA BEAR: TEST [FlexArray: Shift 1000 Integers to Front (FlexArray)]
    	MEAN (μ): 321917 / 325168
    	MIN-MAX(RANGE): 305608-310824(5216) / 305608-310824(5216)
    	OUTLIERS: 0 LOW, 0 HIGH
    	SD (σ): 28252.27 / 28548.56
    	RSD: 8% / 8%

    PAPA BEAR: TEST [FlexArray: Shift 1000 Integers to Front (std::vector)]
    	MEAN (μ): 654278 / 659817
    	MIN-MAX(RANGE): 608020-765749(157729) / 608020-685548(77528)
    	OUTLIERS: 0 LOW, 1 HIGH
    	SD (σ): 53785.7 / 53494.46
    	RSD: 8% / 8%

Unlike MAMA BEAR, these results have much lower RSDs - in fact, they are
equal to the BENCHMARK RSDs (the ideal scenario) - and only one outlier
between the two. This further lends itself to our theory that the higher
RSDs in MAMA BEAR are the result of cache misses.

FlexArray wins this as well, albeit by a somewhat narrower margin::

    PAPA BEAR: VERDICT
    	     RAW: [FlexArray: Shift 1000 Integers to Front (FlexArray)] faster by approx. 332361 cycles.
    	ADJUSTED: [FlexArray: Shift 1000 Integers to Front (FlexArray)] faster by approx. 306100.43052620673552 cycles.

Finally, we look at BABY BEAR, which is intended to be the most similar to
typical use scenarios::

    BABY BEAR: TEST [FlexArray: Shift 1000 Integers to Front (FlexArray)]
    	MEAN (μ): 317852 / 321814
    	MIN-MAX(RANGE): 247433-323226(75793) / 306612-323226(16614)
    	OUTLIERS: 1 LOW, 0 HIGH
    	SD (σ): 33872.37 / 33610.86
    	RSD: 10% / 10%

    BABY BEAR: TEST [FlexArray: Shift 1000 Integers to Front (std::vector)]
    	MEAN (μ): 648568 / 652663
    	MIN-MAX(RANGE): 537774-780641(242867) / 537774-755231(217457)
    	OUTLIERS: 0 LOW, 2 HIGH
    	SD (σ): 60925.17 / 58541.29
    	RSD: 9% / 8%

Our RSDs are slightly higher than with PAPA BEAR, but we still see relatively
few outliers (a total of 3).

The BABY BEAR verdict indicates that FlexArray is the fastest, even in this
scenario::

    BABY BEAR: VERDICT
    	     RAW: [FlexArray: Shift 1000 Integers to Front (FlexArray)] faster by approx. 330716 cycles.
    	ADJUSTED: [FlexArray: Shift 1000 Integers to Front (FlexArray)] faster by approx. 297238.13385525450576 cycles.