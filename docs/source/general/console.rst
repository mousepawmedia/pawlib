..  _console:

PawLIB Tester Console
################################

PawLIB also provides a tester application, which will allow you to run
any of Goldilocks tests and benchmarks.

..  NOTE:: The console interface is in early development, and will be
    improved significantly in a subsequent release.

See :ref:`setup-build-tester` for instructions on how to build the PawLIB
Tester.

Once it's built, you can run the tester from within the PawLIB repository
via ``./tester``.

For PawLIB test and suite ID naming conventions, see :ref:`tests`.

In this guide, ``[arg]`` indicates an optional argument, and ``<arg>``
indicates a required argument.

Interactive Mode
================================

We can start Interactive Mode by running the tester application without
arguments, via ``./tester``. Type commands at the ``:`` prompt.

``help`` displays all of the the commands, for quick reference. ``exit``
quits the program.

..  NOTE:: This initial version of the PawLIB Tester does not offer support
    for the conventional shell commands, including history or arrow-key
    navigation. We'll be adding these in a later version.

Loading A Suite
-----------------------------

Before we can run any tests or benchmarks, we have to load one or more
**suites**.

The ``listsuites`` command displays all of the suites that are available
for loading. The output will probably look like this::

    P-sB01: PawLIB: Trilean Tests
    P-sB10: PawLIB: FlexArray Tests
    P-sB12: PawLIB: FlexQueue Tests
    P-sB13: PawLIB: FlexStack Tests
    P-sB15: PawLIB: FlexBit tests
    P-sB16: PawLIB: Pool Tests
    P-sB30: PawLIB: Pawsort Tests
    P-sB40: PawLIB: QuickString Tests

Running ``load`` without any arguments will load all available suites.
This usually isn't ideal, since it generally clutters up the test list.

Otherwise, we can load a specific suite via ``load [suite]``. For example, to
load the "FlexArray Tests" suite, we would run ``load P-sB10``.

The suites tests are now ready to run.

Running Tests
--------------------------------

The fastest way to run the tests in the suite is just to run ``suite <suite>``.
Continuing the earlier example, we may run all the tests the "FlexArray Tests"
suite via ``suite P-sB10``.

Running an entire suite will only run the Behavior tests (delineated by ``tB``),
and will skip the comparative tests (marked with a trailing (``*``).

Optionally, you can run individual tests. You can view all loaded tests
with ``list``. For example, if we have loaded the "FlexArray Tests" suite,
we may see::

    P-tB1001: FlexArray: Push 1000 Integers (FlexArray)
    P-tB1001*: FlexArray: Push 1000 Integers (std::vector)
    P-tB1002: FlexArray: Shift 1000 Integers to Front (FlexArray)
    P-tB1002*: FlexArray: Shift 1000 Integers to Front (std::vector)
    P-tB1003: FlexArray: Insert 1000 Integers At Middle (flexarray)
    P-tB1003*: FlexArray: Insert 1000 Integers At Middle (std::vector)
    P-tB1004: FlexArray: Yank 1000 Integers (flexarray)
    P-tB1004*: FlexArray: Erase 1000 Integers Individually (std::vector)

...and so on.

We can see the documentation for a test with ``about <test>``.

We can run a single test using the ``test <test>`` command. To run the
"FlexArray: Insert 100 Integers At Middle" test, you would enter ``test
P-tB1003``.

Confirm :kbd:`y` and press :kbd:`ENTER` to run the test. It will respond with
either ``TEST COMPLETE`` or ``TEST FAILED``.

Running Benchmarks
---------------------------------

Goldilocks contains a benchmarker that measures CPU cycles, and generates
extensive statistics for validating the results.

..  NOTE:: A ``benchmark`` command is provided for running a single test
    through the benchmarker, but this is not likely to be useful. We will
    be repurposing this command in a later version.

We've provided comparative tests in our suites, to facilitate performance
comparisons of PawLIB against the standard alternatives. Each test pair
shares the same name, but the standard comparative test is marked with
an asterisk (``*``).

You can run a comparative benchmark using the command
``compare <test1> <test2> [repetitions]``. The optional last argument allows
you to specify how many times to run each test per pass, between 10 and 10,000
inclusively. The more repetitions, the more accurate the results, but the
longer it will take to run. If you're not sure, you should just go with
the default (1000 repetitions).

For example, to see how FlexArray performs against ``std::vector``
in inserting values at the beginning of the data structure (shifting), you
can run ``compare P-tB1002 P-tB1002*``.

Confirm that the select tests and repetition count is what you want, and then
confirm :kbd:`y` and press :kbd:`ENTER` to run the comparison.

It may take a while to run the test. Progress will generally be displayed,
but some tests interfere with the progress indicator. Three passes are made:
"Mama Bear", "Papa Bear", and "Baby Bear". (See :ref:`console-results`).

Command-Line Mode
==============================

We can run tests and suites by passing arguments to our ``./tester``
application. This is especially useful if you want to run tests in a
automated manner, such as with a continuous integration system.

You can get help via ``./tester --help``.

Multiple commands may be run in a single line. They will be executed in order.

Loading Suites and Listing Tests
-------------------------------------

To load a suite, use ``--load <suite>``. If you don't provide a ``--load``
command as your first argument, all suites will automatically be loaded.

If you choose to load multiple specified suite, each much be in its
own ``--load`` argument. For example, ``./tester --load P-sB10 --load P-sB12``

To view all available suites, use the argument ``--listsuites``. To view
all loaded tests, include the argument ``--list``. For example, to see
all the tests belonging to the FlexArray test suite, run
``./tester --load P-sB10 --list``.

Running Suites and Tests
----------------------------

You can run a suite using ``--suite <suite>``, and you can run a test with
``--test <test>``. As with ``--load``, you must run each test or suite in
its own argument.

For example, if I wanted to load the suites for FlexArray and FlexQueue,
run the first two tests for FlexArray, and the entire suite for FlexQueue, I
would run
``./tester --load P-sB10 --load P-sB12 --test P-tB1001 --test P-tB1002 --suite P-sB12``.

Optionally, I could have allowed Tester to load all the suites, and just run
those tests and suites, with ``./tester --test P-tB1001 --test P-tB1002 --suite P-sB12``.

If a test or suite fails, the program will exit with code 1. If everything
succeeds, it will exit with code 0.

..  IMPORTANT:: You presently cannot run benchmarks via command-line argument.

..  _console-results:

Understanding Benchmark Results
=====================================

The ``benchmark`` and ``compare`` functions output a *lot* of information.
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
functionality of FlexArray and ``std::vector``. You can run this yourself with
the command ``compare P-tB1002 P-tB1002*``.

We always start by screening the baseline::

    BASELINE MEASUREMENTS
        MEAN (μ): 64 / 65
    	MIN-MAX(RANGE): 58-75(17) / 58-75(17)
    	OUTLIERS: 0 LOW, 0 HIGH
    	SD (σ): 5.47 / 5.38
    	RSD: 8% / 8%

We have no outliers and very low RSDs, so our results probably aren't
contaminated. Of course, benchmarking is unpredicable, and external factors
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
