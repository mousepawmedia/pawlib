..  _console:

PawLIB Tester Console
################################

PawLIB also provides a tester application, which will allow you to run
any of Goldilocks tests and benchmarks using GoldilocksShell.

In addition to the various tests, we've provided comparative tests in our
suites, to facilitate performance comparisons of PawLIB against the standard
alternatives. See :ref:`goldilocks_benchmarker` for details on reading the
benchmarker statistics and results.

See :ref:`setup-build-tester` for instructions on how to build the PawLIB
Tester.

Once it's built, you can run the tester from within the PawLIB repository
via ``./tester``.

For PawLIB test and suite ID naming conventions, see :ref:`tests`.

Interactive Mode
================================

We can start Interactive Mode by running the tester application without
arguments, via ``./tester``. Type commands at the ``>>`` prompt.

All commands are detailed under :ref:`goldilocksshell_interactive`.

Command-Line Mode
==============================

We can run tests and suites by passing arguments to our ``./tester``
application. This is especially useful if you want to run tests in a
automated manner, such as with a continuous integration system.

You can get help via ``./tester --help``.

Multiple commands may be run in a single line. They will be executed in order.

All commands are detailed under :ref:`goldilocksshell_cli`.