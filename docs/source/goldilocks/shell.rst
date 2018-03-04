..  _goldilocksshell:

GoldilocksShell
##################################################

What Is GoldilocksShell?
==================================================

What good are tests without a way to run them? While you can certainly
write your own class for interacting with Golidlocks, we wanted to provide
a quick and easy way to run your tests and suites interactively.

Assuming you have one or more TestSuites configured
(see :ref:`goldilocks_suites`), you can set up a GoldilocksShell
relatively quickly!

..  _goldilocksshell_setup:

Setting Up
==================================================

We import GoldilocksShell with...

..  code-block:: c++

    #include "pawlib/goldilocks_shell.hpp"

We start by defining a new ``GoldilocksShell`` object instaces somewhere in our
code, preferably in our ``main()`` function.

..  code-block:: c++

    GoldilocksShell* shell = new GoldilocksShell(">> ");

The part in quotes is the *prompt string*, which will appear at the start
of every line where the user can type in the interactive terminal.

Now we need to register all of our Goldilocks ``TestSuite`` classes with the
shell. Note that we don't need to create instances of these ourselves, but
merely pass the class as a type. We also need to specify the name of the
suite in quotes: this name will be what is used to idenfity it in the shell.

..  code-block:: c++

    shell->register_suite<TestSuite_Brakes>("s-brakes");
    shell->register_suite<TestSuite_Hologram>("s-hologram");
    shell->register_suite<TestSuite_TimeRotor>("s-timerotor");
    shell->register_suite<TestSuite_CloisterBell>("s-cloisterbell");

That is it! We are now ready to use GolidlocksShell.

..  _goldilocksshell_interactive:

Interactive Mode
===================================================

As long as we're running in the command line, we can hand over control to the
GoldilocksShell via a single line of code...

..  code-block:: c++

    shell->interactive();

The GoldilocksShell will immediately launch and take over the terminal, using
IOChannel.

..  _goldilocksshell_interactive_commands:

Commands
---------------------------------------------------

In Interactive Mode, you are given a complete shell for executing
Golilocks tests and suites.

..  NOTE:: This initial version of GoldilocksTester does not offer support
    for the conventional shell commands, including history or arrow-key
    navigation. We'll be adding these in a later version.

To get help at any point, run ``help``. To quit, type ``exit``.

In this guide, we'll be using the default GoldilocksShell prompt symbol,
``:``. This may be different for your project, depending on how you
configured GoldilocksShell.

Listing and Loading Suites and Tests
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When you first start GoldilocksShell, no tests have been loaded into
memory. However, all the suites you specified are *ready* to be loaded.

To see all the available suites, run ``listsuites``::

    : listsuites
    s-brakes: TARDIS Brakes Tests
    s-hologram: TARDIS Holographic Interface Tests
    s-timerotor: TARDIS Time Rotor Tests
    s-cloisterbell: TARDIS Cloister Bell Tests

Thus, before you can run a test or suite, you must first **load** the
suite containing it::

    : load s-brakes
    TARDIS Brakes Tests
    Suite loaded.

Now you can run the ``list`` command to see all the loaded tests::

    : list
    t-brakes-engage: TARDIS Brakes: Engage Brakes
    t-brakes-warn: TARDIS Brakes: No Brakes Warning
    t-brakes-disengage: TARDIS Brakes: Disengage Brakes
    t-brakes-fail: TARDIS Brakes: Brake Failure Protocol
    t-brakes-pressure: TARDIS Brakes: Brake Pressure Test

..  NOTE:: If ``list`` does not show any tests, be sure you've loaded at least
    one suite first.

If you just want to load *all* suites, simply run the ``load`` command without
any arguments. It will ask you to confirm your choice::

    : load
    Load ALL test suites? (y/N) y
    TARDIS Brakes Tests loaded.
    TARDIS Holographic Interface Tests loaded.
    TARDIS Time Rotor Tests loaded.
    TARDIS Cloister Bell Tests loaded.

You can find out more information about any test using the ``about`` command::

    : about t-brakes-engage
    TARDIS Brakes: Engage Brakes
    Ensures the controls are capable of engaging the brakes.

Running Tests and Suites
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

It is possible to run any test using the ``run`` command. This command always
asks you to confirm before continuing::

    : run t-brakes-engage
    Run test TARDIS Brakes: Engage Brakes [t-brakes-engage]? (y/N) y
    ===== [TARDIS Brakes: Engage Brakes] =====
    Pass 1 of 1
    TEST COMPLETE

Optionally, you can repeat a test multiple times by specifying the number of
times to repeat it.

    : run t-brakes-engage 5
    Run test TARDIS Brakes: Engage Brakes [t-brakes-engage]? (y/N) y
    ===== [TARDIS Brakes: Engage Brakes] =====
    Pass 1 of 5
    Pass 2 of 5
    Pass 3 of 5
    Pass 4 of 5
    Pass 5 of 5
    TEST COMPLETE

You can also run an entire suite in one step::

    : run s-brakes
    Run test suite TARDIS Brakes Tests [s-brakes]? (y/N) y
    ===== [TARDIS Brakes Tests] =====
    ===== [TARDIS Brakes: Engage Brakes] =====
    Pass 1 of 1
    TEST COMPLETE
    ===== [TARDIS Brakes: No Brakes Warning] =====
    Pass 1 of 1
    TEST COMPLETE
    ===== [TARDIS Brakes: Disengage Brakes] =====
    Pass 1 of 1
    TEST COMPLETE
    ===== [TARDIS Brakes: Brake Failure Protocol] =====
    Pass 1 of 1
    TEST COMPLETE
    ===== [TARDIS Brakes: Brake Pressure Test] =====
    Pass 1 of 1
    TEST COMPLETE

    SUITE COMPLETE

..  NOTE:: If you specify a repeat number for running a suite, it will be
    ignored.

Benchmarking
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Golidlocks supports *comparative benchmarking*. There are two ways to run
such a benchmark.

The first method requires a comparative test to be specified within a suite
(see :ref:`goldilocks_setupsuites_structure_loadtests`). If you've done
this, you can benchmark the test and its comparative, and output the complete
benchmark stats::

    : benchmark t-brakes-engage
    Run comparative benchmark between TARDIS Brakes: Engage Brakes [t-brakes-engage] and TARDIS Brakes: Handbrake? (y/N) at 100 repetitions? (y/N) y
    ======================
    |     BENCHMARKER    |
    ======================

Upon completion it will display the complete benchmarker stats
(see :ref:`goldilocks_benchmarker`).

You can also specify the number of times to run the benchmarker (the default
is 100)::

    : benchmark t-brakes-engage 1000
    Run comparative benchmark between TARDIS Brakes: Engage Brakes [t-brakes-engage] and TARDIS Brakes: Handbrake? (y/N) at 1000 repetitions? (y/N) y
    ======================
    |     BENCHMARKER    |
    ======================

You can also run a comparative benchmark on any two tests using the ``compare``
function. It functions in much the same way, except that you specify *two*
tests instead of one, and then the optional repetition count::

    : compare t-brakes-engage t-brakes disengage 500
    Run comparative benchmark between TARDIS Brakes: Engage Brakes [t-brakes-engage] and TARDIS Brakes: Disengage [t-brakes-disengage]? (y/N) at 1000 repetitions? (y/N) y
    ======================
    |     BENCHMARKER    |
    ======================

..  _goldilocksshell_cli:

Command Line Argument Mode
===================================================

..  _goldilocksshell_cli_invocation:

Invocation
---------------------------------------------------

GoldilocksShell is also designed to handle the same input arguments as your
typical ``int main()``, which allows you to invoke the shell using
command-line arguments.

This is especially useful for integrating Goldilocks into a Continuous
Integration [CI] system, such as Jenkins. If the specified tests and suites
are successful, the program will exit with code ``0``; failures will cause the
program to exit with code ``1``.

To use this feature, you must simply pass the argument count and argument
array to the GoldilocksShell's ``command()`` function. It handles its own
argument parsing.

..  code-block:: c++

    int main(int argc, char* argv[])
    {
        // ...setup code here...

        // If we got command-line arguments...
        if(argc > 1)
        {
            return shell->command(argc, argv);
        }

        return 0;
    }

..  _goldilocksshell_cli_skipargs:

Skipping Arguments
---------------------------------------------------

If you accept other arguments via command-line, you may ask GoldilocksShell
to skip those. Just specify the number of arguments to skip in the third
argument.

..  IMPORTANT:: GoldilocksShell already knows to skip the first argument,
    which is the program invocation. You only need to tell it how many
    *extra* arguments to skip.

For example...

..  code-block:: c++

    // myprogram --goldilocks --run sometest
    int main(int argc, char* argv[])
    {
        // ...setup code here...

        // If we're supposed to invoke Goldilocks.
        if(argc > 1 && strcmp(argv[1], "--goldilocks") == 0)
        {
            // Asking GoldilocksShell to skip one argument...
            return shell->command(argc, argv, 1);
            // Now it will only process arguments starting from ``--run``...
        }

        return 0;
    }

..  _goldilocksshell_cli_usage:

Usage
---------------------------------------------------

GoldilocksShell's command line interface accepts multiple arguments, which
are used to load and run tests, suites, and benchmarks. Commands are always
run from left to right, in order.

The basic commands are as follows:

* ``--help`` displays help.
* ``--listsuites`` lists all available suites.
* ``--load suite`` loads the suite ``suite``.
* ``--list`` lists all loaded tests.
* ``--run item`` runs the test or suite ``item``.
* ``--benchmark item`` benchmarks the test ``item``.

..  IMPORTANT:: The command line does not include the ``compare`` function,
    nor the ability to specify the number of test repetitions.

Ordinarily, to run a test, you must first load the suite containing it.
However, for the sake of convenience, if you don't explicitly load any
tests in the command, it will just load all suites. Thus...

..  code-block:: bash

    $ tester --run t-brakes-engage

...will just load all the suites before attempting to run the test
``t-brakes-engage``.

If you want to only load a single suite, perhaps to see what tests it contains,
just include the ``--load`` argument. (Remember, if you don't explicitly load
any suites, all the suites will be loaded.)

..  code-block:: bash

    $ tester --load s-brakes --list

..  WARNING:: Each command only accepts one argument! If you want to load
    multiple suites, you must precede each suite ID with the ``--load`` argument.

Arguments are run in order, from left to right, and the program doesn't exit
until all of them are finished. This means you can run multiple tests in one
command; success will only be reported (exit code ``0``) if all the tests
pass.

..  code-block:: bash

    $ tester --load s-brakes --run t-brakes-engage --run t-brakes-disengage

The above command, after loading only the specified suite, will run the
requested tests. If they *both* succeed, the program will exit reporting
success (exit code ``0``).

..  WARNING:: Each command only accepts one argument! If you want to load
    multiple suites, you must precede each suite ID with the ``--load`` argument.

We can also run benchmarks from the command line. ``--benchmark`` bases its
success/fail condition on the Baby Bear comparison; success means either
(a) the main test is faster than its comparative, or (b) the two tests are
roughly identical in performance ("dead heat").

..  code-block:: bash

    $ tester --load s-brakes --benchmark t-brakes-engage

..  _goldilocksshell_example:

A Complete Example
===================================================

Let's tie all this together. Here's an example of a complete ``int main()``
function set up to use GoldilocksShell, as outlined in the previous sections.

..  code-block:: c++

    int main(int argc, char* argv[])
    {
        GoldilocksShell* shell = new GoldilocksShell(">> ");

        shell->register_suite<TestSuite_Brakes>("s-brakes");
        shell->register_suite<TestSuite_Hologram>("s-hologram");
        shell->register_suite<TestSuite_TimeRotor>("s-timerotor");
        shell->register_suite<TestSuite_CloisterBell>("s-cloisterbell");

        // If we got command-line arguments...
        if(argc > 1)
        {
            return shell->command(argc, argv);
        }
        else
        {
            // Shift control to the interactive console.
            shell->interactive();
        }

        // Delete our GoldilocksShell.
        delete shell;
        shell = 0;

        return 0;
    }