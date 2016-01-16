#include "goldilocks.hpp"

namespace pawlib
{
    //Declaring global instance of testmanager.
    TestManager testmanager;

    // MACRO IF we are using a GCC-style compiler.
    // NOTE: We're assuming Intel/AMD. What about PowerPC and ARM?
    #if defined __GNUC__ || __MINGW32__ || __MINGW64__
        // If we're on a 64-bit system...
        #if defined __LP64__

        void TestManager::calibrate()
        {
            /* According to Intel's documentation, we must "warms up"
             * the instruction cache that we'll be using for measurement,
             * to improve accuracy.*/

            uint32_t low, high;

            /* Run the following commands three times to warm up the
            instructions cache.*/
            for(uint16_t i=0;i<3;i++)
            {
                asm volatile ("cpuid;"
                              "rdtsc;"
                              "mov %%edx, %0;"
                              "mov %%eax, %1;"
                              : "=r" (high), "=r" (low)
                              :: "%rax", "%rbx", "%rcx", "%rdx");

                asm volatile ("rdtsc;"
                              "mov %%edx, %0;"
                              "mov %%eax, %1;"
                              : "=r" (high), "=r" (low)
                              :: "%rax", "%rbx", "%rcx", "%rdx");
            }
        }

        inline uint64_t TestManager::clock(Test* test)
        {
            uint32_t low, high;
            uint64_t cyc1, cyc2;

            //Serialize initially (we won't do it later, though.)
            asm volatile ("cpuid;"
                          ::: "%rax", "%rbx", "%rcx", "%rdx");
            //Get the initial timestamp (all 64 bits).
            asm volatile ("rdtsc;"
                          "mov %%edx, %0;"
                          "mov %%eax, %1;"
                          : "=r" (high), "=r" (low)
                          :: "%rax", "%rdx");
            //Put the high and low halves of the timestamp together and store.
            cyc1 = ((uint64_t)high << 32) | low;

            /* If we have a test, run it. (If there is no test, we will just
             * wind up measuring the measurement instructions by themselves.*/
            if(test!=NULL) test->run();

            /* Get the second timestamp. DO NOT SERIALIZE! The CPUID instruction
             * is too unpredictable in terms of execution size. We can just
             * assume that an out-of-order execution will yield an outlier
             * measurement.*/
            asm volatile (/*"cpuid;"*/
                          "rdtsc;"
                          "mov %%edx, %0;"
                          "mov %%eax, %1;"
                          : "=r" (high), "=r" (low)
                          :: "%rax", "%rdx");

            //Put the high and low halves of the timestamp together and store.
            cyc2 = ((uint64_t)high << 32) | low;

            //Return the difference between the AFTER and BEFORE timestamps.
            return (cyc2 - cyc1);
        }

        // If we're on a 32-bit system...
        #else
        /* NOTE: This seems to be assuming we're not on a 16-bit system. Do we
         * need to factor that in?*/

        /* See the comments for the 64-bit versions of these functions. The only
         * difference between the 32-bit and 64-bit versions is in which
         * registers we are clobbering. On x86 (32-bit), we clobber %eax-%edx,
         * while on x64, we clobber %rax-%rdx.*/
        void TestManager::calibrate()
        {
            uint32_t low, high;

            for(uint16_t i=0;i<3;i++)
            {
                asm volatile ("cpuid;"
                              "rdtsc;"
                              "mov %%edx, %0;"
                              "mov %%eax, %1;"
                              : "=r" (high), "=r" (low)
                              :: "%eax", "%ebx", "%ecx", "%edx");

                asm volatile ("rdtsc;"
                              "mov %%edx, %0;"
                              "mov %%eax, %1;"
                              : "=r" (high), "=r" (low)
                              :: "%eax", "%ebx", "%ecx", "%edx");
            }
        }


        inline uint64_t TestManager::clock(Test* test)
        {
            uint32_t low, high;
            uint64_t cyc1, cyc2;

            asm volatile ("cpuid;"
                          ::: "%eax", "%ebx", "%ecx", "%edx");
            asm volatile ("rdtsc;"
                          "mov %%edx, %0;"
                          "mov %%eax, %1;"
                          : "=r" (high), "=r" (low)
                          :: "%eax", "%edx");
            cyc1 = ((uint64_t)high << 32) | low;
            if(test!=NULL) test->run();
            asm volatile (/*"cpuid;"*/
                          "rdtsc;"
                          "mov %%edx, %0;"
                          "mov %%eax, %1;"
                          : "=r" (high), "=r" (low)
                          :: "%eax", "%edx");

            cyc2 = ((uint64_t)high << 32) | low;

            return (cyc2 - cyc1);
        }

        #endif

    /* MACRO ELSE if we're not on a GCC, just don't offer the rdtsc functions;
     * offer dummies instead. We will NOT be supporting MSVC under ANY
     * circumstances!*/
    #else
    uint64_t TestManager::calibrate_rdtsc()
    {
        return 0;
    }

    uint64_t TestManager::rdtsc()
    {
        return 0;
    }

    #endif

    void TestManager::register_test(name test_name, Test* test)
    {
        /* ENTRY: Add a new test by name to the test manager. */

        /* We generally advise the end-developer to pass `new Test` as
         * the second parameter. Thus, if the allocation fails (or they
         * otherwise pass in a null pointer)...*/
        if(test == 0)
        {
            //Display an error message.
            ioc << cat_error << "TestManager: Unable to create a new "
                << "instance of the test \"" << test_name << "\". Test not "
                << "registered." << io_end;

            //Return non-fatally.
            return;
        }

        /* Add the new test to the TestManager's map (tests), with the name
         * string as the key, and a smart pointer (unique_ptr) to the test.
         * emplace() allows us to define the new unique_ptr within the map,
         * as insert() would literally NOT work (you can't copy a unique_ptr).*/
        tests.emplace(test_name, test_ptr(test));

        /* WARNING: The end-developer must be sure they aren't trying to
         * retain ownership of the Test instance, as that will cause UB
         * (in my observation, usually a segfault) when the TestManager
         * instance is destroyed - the unique_ptr will not be able to
         * destroy the instance. It's not pretty.*/
    }

    void TestManager::run_test(name test)
    {
        /* ENTRY: Run a single test.*/

        // Display the test name in a banner.
        ioc << "===== [" << test << "] =====" << io_end;

        /* Attempt to run the pretest function, which is intended to set up
         * for multiple runs of the test. If that fails (returns false)...*/
        if(!(tests[test]->pre()))
        {
            // Alert the user with an error message.
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "PRE-TEST FAILED - ABORTING" << io_end;

            // Run the function to clean up after a pretest fail.
            tests[test]->prefail();

            // End of test.
            return;
        }

        // Run the test. If it fails (return false)...
        if(!(tests[test]->run()))
        {
            // Alert the user with an error message.
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "TEST FAILED" << io_end;

            // Run the test's fail-cleanup function.
            tests[test]->postmortem();

            //End of test.
            return;
        }
        //If the test run succeeds (return true)...
        else
        {
            // Let the user know that all went well.
            ioc << cat_normal << ta_bold << bg_green << fg_white
                << "TEST COMPLETE" << io_end;

            // Run the test's cleanup (post) function.
            tests[test]->post();

            //End of test.
            return;
        }
    }

    void TestManager::benchmark_banner()
    {
        // Display the fancy benchmark banner, with its disclaimer.
        ioc << ta_bold << fg_blue
            << "======" << "===========" << "=====\n"
            << "|     " << "BENCHMARKER" << "    |\n"
            << "======" << "===========" << "=====" << io_end;
        ioc << ta_none << fg_red
            << "Disclaimer: This benchmarker is intended to give a rough estimate "
            << "of how many CPU cycles a particular test takes. It is not a "
            << "replacement for a fully-featured code profiler. "
            << "Cache warming will NOT be performed.\n"
            << io_end;
    }

    void TestManager::run_benchmark(name test, int repeat)
    {
        /* ENTRY: Run a benchmark.
         * run_compare() is largely based off of this, with
         * some adjustments for the three types of comparisons.
         */

        /* We should only allow repeating between 10 and 10,000 times,
         * inclusively. If the user asked for more than that...*/
        if(repeat < 10 || repeat > 10000)
        {
            // Display an error.
            ioc << cat_error << "Benchmark requires a repeat value "
                << "between 10-10000 (inclusively)." << io_end;

            // Abort the benchmark.
            return;
        }

        // Display the fancy benchmarker banner and disclaimer.
        benchmark_banner();

        // Display the name of the test we're about to benchmark.
        ioc << "===== [" << test << "] =====" << io_end;

        // Attempt to set up the test (pre). If that fails...
        if(!(tests[test]->pre()))
        {
            // Alert the user with an error message..
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "[" << test << "] PRE-TEST FAILED - ABORTING" << io_end;
            // Run the test's pre-fail cleanup function.
            tests[test]->prefail();

            // Abort the benchmark.
            return;
        }

        // Let the user know what we're doing.
        ioc << "Ensuring [" << test << "] succeeds before benchmarking..." << io_end;

        /* Run the test to make sure it is successful before benchmarking.
         * If it fails...*/
        if(!(tests[test]->run()))
        {
            // Alert the user with an error message.
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "[" << test << "] FAILED - ABORTING" << io_end;
            // Run the test's fail-cleanup function.
            tests[test]->postmortem();

            //Abort the benchmark.
            return;
        }
        // Else if the test succeeds...
        else
        {
            // Give the user the good news.
            ioc << cat_normal << ta_bold << bg_green << fg_white
                << "[" << test << "] PASSED" << io_end;

            //Continue with the benchmarker!
        }

        // Display notice that we're starting to measure now.
        ioc << cat_normal << bg_cyan << fg_black << "STARTING BENCHMARK" << io_end;

        /* Shut off all testing messages; they aren't useful after the initial
         * test run has finished. We don't want to clog up or clutter output.*/
        ioc.shutup(cat_testing);

        /* The average execution time of the measurement functions, represented
         * as a 64-bit unsigned integer.*/
        uint64_t base;
        /* Instances of BenchmarkResult for storing the statistical data from
         * our base and test benchmarks.*/
        BenchmarkResult benchmark, baseR;

        // Dynamically allocate the array for storing clock measurements.
        uint64_t* results = new uint64_t[repeat];

        /* Ensure we were able to allocate the array.
         * If it failed (NULL pointer)...*/
        if(results == 0)
        {
            // Alert the user with an error message.
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "Cannot allocate results array. Aborting." << io_end;
            // Abort the benchmark.
            return;
        }

        // Calibrate our measurement functions. (See that function's comments.)
        calibrate();

        // Get <repeat> measurements of the measurement function.
        for(int i=0; i<repeat; i++)
        {
            float fltRepeat = repeat;
            /* Display our ongoing progress to the user. We are using `io_show`
             * so we keep it all on the same line.*/
            ioc << cat_normal << "CALIBRATING: " << (((i+1)/fltRepeat)*100) << "%" << io_show;
            // Record each measurement to the array.
            results[i] = clock();
        }

        // Calculate the statistical data for the base measurements.
        resultFromArray(baseR, results, repeat);
        /* Store the average base. We'll offset all other measurements
         * with this, so we're only measuring the TEST.*/
        base = baseR.mean;

        // Get <repeat> measurements of the test.
        for(int i=0; i<repeat; i++)
        {
            /* Display our ongoing progress to the user. We are using `io_show_keep`
             * so we keep it all on the same line and retain formatting.*/
            ioc << cat_normal << "Pass " << (i+1) << " of " << repeat << "." << io_show_keep;
            // Record each measurement to the array, overwriting the old data.
            results[i] = clock(tests[test].get()) - base;
        }

        // Calculate the statistical data for the base measurements.
        resultFromArray(benchmark, results, repeat);

        // Turn on testing messages again.
        ioc.speakup(cat_testing);

        // Flush the output so we can start working on a newline.
        ioc << io_endline_keep << io_flush << io_send;

        // Run post-test function.
        tests[test]->post();

        // Tell the user that we're done with benchmarking.
        ioc << ta_bold << bg_green << fg_white
                << "BENCHMARKER COMPLETE" << io_end;

        // Display results information.
        ioc << "RESULTS" << io_end;
        ioc << "\tMany numbers are displayed as VALUE/ADJUSTED" << io_endline_keep
            << "\t(The adjusted value excludes outlier values.)" << io_endline << io_end;

        // Output the baseline measurements for reference.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "BASELINE MEASUREMENTS" << io_end;
        printResult(baseR);

        // Output the test measurements.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "[" << test << "] MEASUREMENTS" << io_end;
        printResult(benchmark);

        // Clean up: delete our results array.
        delete [] results;
        // Null out the pointer to the results array (by habit).
        results = 0;
    }

    void TestManager::run_compare(name test1, name test2, int repeat)
    {
        /* ENTRY: Compare two function benchmarks.
         * Largely based on run_benchmark, with several
         * additions for the different comparison types.
         */

        /* We should only allow repeating between 10 and 10,000 times,
         * inclusively. If the user asked for more than that...*/
        if(repeat < 10 || repeat > 10000)
        {
            // Display an error.
            ioc << cat_error << "Benchmark requires a repeat value "
                << "between 10-10000 (inclusively)." << io_end;

            // Abort the benchmark.
            return;
        }

        // Display the fancy benchmarker banner and disclaimer.
        benchmark_banner();
        // Display the names of the tests we're about to compare.
        ioc << "===== [" << test1 << "] | [" << test2 << "] =====" << io_end;

        // Attempt to run the "pre" function for test 1. If it fails...
        if(!(tests[test1]->pre()))
        {
            // Alert the user with an error message...
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "[" << test1 << "] PRE-TEST FAILED - ABORTING" << io_end;
            // Perform pre-fail cleanup on test 1.
            tests[test1]->prefail();

            // Don't worry about test 2 - it hasn't been set up yet.

            // Abort the benchmarker.
            return;
        }

        // Attempt to run the "pre" function for test 2. If it fails...
        if(!(tests[test2]->pre()))
        {
            // Alert the user with an error message...
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "[" << test2 << "] PRE-TEST FAILED - ABORTING" << io_end;

            // Perform pre-fail cleanup on test 2.
            tests[test2]->prefail();

            /* Perform standard cleanup (post) on test 1. Otherwise, we can
             * potentially wind up with memory leaks and other issues.*/
            tests[test1]->post();

            //Abort the benchmarker.
            return;
        }

        // Let the user know what we're doing...
        ioc << "Ensuring [" << test1 << "] succeeds before benchmarking..." << io_end;

        // Run test1 to make sure it works. If it fails...
        if(!(tests[test1]->run()))
        {
            // Alert the user with an error message.
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "[" << test1 << "] FAILED - ABORTING" << io_end;

            // Run postmortem cleanup on test1.
            tests[test1]->postmortem();

            /* Perform standard cleanup (post) on test 2. Otherwise, we can
             * potentially wind up with memory leaks and other issues.*/
            tests[test2]->post();

            //Abort the benchmarker.
            return;
        }
        // Otherwise, if test 1 succeeds...
        else
        {
            // Let the user know the good news...
            ioc << cat_normal << ta_bold << bg_green << fg_white
                << "[" << test1 << "] PASSED" << io_end;
            // ...and move on.
        }

        // Give the user a status update.
        ioc << "Ensuring [" << test2 << "] succeeds before benchmarking..." << io_end;

        // Run test2 to make sure it works. If it fails...
        if(!(tests[test2]->run()))
        {
            // Alert the user with an error message.
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "[" << test2 << "] FAILED - ABORTING" << io_end;

            // Run postmortem cleanup on test2.
            tests[test2]->postmortem();

            /* Perform standard cleanup (post) on test 1. Otherwise, we can
             * potentially wind up with memory leaks and other issues.*/
            tests[test1]->post();

            // Abort the benchmarker.
            return;
        }
        // Otherwise, if test 2 succeeds...
        else
        {
            // Let the user know the good news about that as well...
            ioc << cat_normal << ta_bold << bg_green << fg_white
                << "[" << test2 << "] PASSED" << io_end;
            // ...and let the fun proceed!
        }

        // Let the user know that we're starting our measurements.
        ioc << cat_normal << bg_cyan << fg_black << "STARTING BENCHMARK" << io_end;

        /* Shut off all testing messages; they aren't useful after the initial
         * test run has finished. We don't want to clog up or clutter output.*/
        ioc.shutup(cat_testing);

        /* The average execution time of the measurement functions, represented
         * as a 64-bit unsigned integer.*/
        uint64_t base;
        /* The BenchmarkResult instances for storing the output of all our
         * measurements.*/
        BenchmarkResult mama1, mama2, papa1, papa2, baby1, baby2, baseR;

        // Dynamically allocate two arrays for storing measurements.
        uint64_t* results1 = new uint64_t[repeat];
        uint64_t* results2 = new uint64_t[repeat];

        // If we were unable to allocate either (or both) array...
        if(results1 == 0 || results2 == 0)
        {
            // Alert the user with an error message.
            ioc << cat_error << ta_bold << bg_red << fg_white
                << "Cannot allocate results arrays. Aborting." << io_end;
            // Abort the benchmarker.
            return;
        }

        // Calibrate our measurement functions. (See that function's comments.)
        calibrate();

        /* Take <repeat> baseline measurements (measuring the measurement
         * function itself.)*/
        for(int i=0; i<repeat; i++)
        {
            /* Keep the user apprised of our progress. We use `io_show` so we
             * keep overwriting the same line.*/
            ioc << cat_normal << "CALIBRATING: " << (((i+1)/repeat)*100) << "%" << io_show;
            // Get a baseline measurement.
            results1[i] = clock();
        }

        /* Calculate the statistical results from our array of baseline
         * measurements.*/
        resultFromArray(baseR, results1, repeat);
        /* Store the average baseline measurement for offsetting all our later
         * measurements, thereby measuring JUST the test.*/
        base = baseR.mean;

        /* MAMA BEAR (cold cache) alternates the tests A-B-A-B-A-B, to maximize
         * the possibility of cache misses on each individual test run.*/

        // Display MAMA BEAR banner.
        ioc << cat_normal  << "\n" << bg_cyan << fg_black << "COMPARISON 1/3: MAMA BEAR" << io_flush << io_end;

        // Take <repeat> measurements of test A and B.
        for(int i=0; i<repeat; i++)
        {
            // Display progress (overwrite line.)
            ioc << cat_normal << "(MAMA BEAR) Pass " << (i+1) << "-A of " << repeat << ".  " << io_show;
            // Record test 1 measurement, offset by baseline.
            results1[i] = clock(tests[test1].get()) - base;

            // Display progress (overwrite line.)
            ioc << cat_normal << "(MAMA BEAR) Pass " << (i+1) << "-B of " << repeat << ".  " << io_show;
            // Record test 2 measurement, offset by baseline.
            results2[i] = clock(tests[test2].get()) - base;
        }

        // Move to a new line for output.
        ioc << io_flush << io_end;

        // Calculate the statistical results for MAMA BEAR, tests 1 and 2.
        resultFromArray(mama1, results1, repeat);
        resultFromArray(mama2, results2, repeat);

        /* PAPA BEAR (hot cache) performs all runs of test A before test B, to
        * minimize the possibility of cache misses on each individual test run;
        * in other words, allowing natural cache warming to occur.*/

        // Display PAPA BEAR banner.
        ioc << cat_normal  << "\n" << bg_cyan << fg_black << "COMPARISON 2/3: PAPA BEAR" << io_flush << io_end;

        // Take <repeat> measurements of test A.
        for(int i=0; i<repeat; i++)
        {
            // Display progress (overwrite line).
            ioc << cat_normal << "(PAPA BEAR) Pass " << (i+1) << "-A of " << repeat << ".  " << io_show;
            // Record test 1 measurement, offset by baseline.
            results1[i] = clock(tests[test1].get()) - base;
        }

        // Take <repeat> measurements of test B.
        for(int i=0; i<repeat; i++)
        {
            // Display progress (overwrite line).
            ioc << cat_normal << "(PAPA BEAR) Pass " << (i+1) << "-B of " << repeat << ".  " << io_show;
            // Record test 2 measurement, offset by baseline.
            results2[i] = clock(tests[test2].get()) - base;
        }

        // Move to a new line for output.
        ioc << io_flush << io_end;
        ////ioc << "\n\n" << io_end << io_flush;

        // Calculate the statistical results for PAPA BEAR, tests 1 and 2.
        resultFromArray(papa1, results1, repeat);
        resultFromArray(papa2, results2, repeat);

        /* BABY BEAR (warm cache, or "just right"), alternates tests A and B
         * in sets of eight, therefore allowing some cache warming to occur,
         * but also allowing cache misses to be a factor. In some cases, this
         * is closer to what would occur with typical use of an algorithm or
         * approach.*/

        // Display BABY BEAR banner.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "COMPARISON 3/3: BABY BEAR" << io_end;

        /* Define three 16-bit unsigned integers for managing BABY BEAR's more
         * complex alternation - counters for the outer and inner loops, and
         * one for all remaining tests when our repeat is not divisible by
         * eight (which it usually won't be.) The inner loop should always be
         * eight!*/
        uint16_t inner=8, outer, remain;
        // The outer loop is the repeat count, integer-divided-by eight.
        outer = repeat / 8;
        // We store the remainder, so we still meet the exact repeat count.
        remain = repeat % 8;

        // We run 8 of each test in each set (outer)...
        for(int o=0; o<outer; o++)
        {
            // Run test 1 eight consecutive times for this set...
            for(int i1=0; i1<inner; i1++)
            {
                // Display progress (overwrite line.)
                ioc << cat_normal << "(BABY BEAR) Pass " << ((o+1)*(i1+1)) << "-A of " << repeat << ".  " << io_show;
                // Record test 1 measurement, offset by baseline.
                results1[i1] = clock(tests[test1].get()) - base;
            }

            // Run test 2 eight consecutive times for this set...
            for(int i2=0; i2<inner; i2++)
            {
                // Display progress (overwrite line.)
                ioc << cat_normal << "(BABY BEAR) Pass " << ((o+1)*(i2+1)) << "-B of " << repeat << ".  " << io_show;
                // Record test 2 measurement, offset by baseline.
                results2[i2] = clock(tests[test2].get()) - base;
            }
        }

        // Run test 1 the remaining number of times consecutively...
        for(int r1=0; r1<remain; r1++)
        {
            // Display progress (overwrite line.)
            ioc << cat_normal << "(BABY BEAR) Pass " << ((outer*inner)+(r1+1)) << "-A of " << repeat << ".  " << io_show;
            // Record test 1 measurement, offset by baseline.
            results1[r1] = clock(tests[test1].get()) - base;
        }

        // Run test 2 the remaining number of times consecutively...
        for(int r2=0; r2<remain; r2++)
        {
            // Display progress (overwrite line.)
            ioc << cat_normal << "(BABY BEAR) Pass " << ((outer*inner)+(r2+1)) << "-B of " << repeat << "." << io_show_keep;
            // Record test 2 measurement, offset by baseline.
            results2[r2] = clock(tests[test2].get()) - base;
        }

        // Move to a new line for output.
        ioc << io_flush << io_end;
        ////ioc << io_end << io_flush;

        // Calculate the statistical results for BABY BEAR, tests 1 and 2.
        resultFromArray(baby1, results1, repeat);
        resultFromArray(baby2, results2, repeat);

        // Turn on testing messages again, as we're done running the tests.
        ioc.speakup(cat_testing);

        // Let the user know that we're done running the benchmarker.
        ioc << cat_normal << "\n" << ta_bold << bg_green << fg_white
                << "BENCHMARKER COMPLETE" << io_end;


        // Cleanup test 1 and 2 using their post functions.
        tests[test1]->post();
        tests[test2]->post();

        // Display information about results.
        ioc << "RESULTS" << io_end;
        ioc << "\tMany numbers are displayed as VALUE/ADJUSTED" << io_endline_keep
            << "\t(The adjusted value excludes outlier values.)" << io_endline << io_end;

        // Display the baseline measurements, for reference.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "BASELINE MEASUREMENTS" << io_end;
        printResult(baseR);

        // Display the results for MAMA BEAR, test 1.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "MAMA BEAR: [" << test1 << "]" << io_end;
        printResult(mama1);

        // Display the results for MAMA BEAR, test 2.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "MAMA BEAR: [" << test2 << "]" << io_end;
        printResult(mama2);

        // Display the verdict for MAMA BEAR in BOLD.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "MAMA BEAR: VERDICT" << io_end;
        ioc << ta_bold;
        printVerdict(mama1, mama2, test1, test2);

        // Display the results for PAPA BEAR, test 1.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "PAPA BEAR: TEST [" << test1 << "]" << io_end;
        printResult(papa1);

        // Display the results for PAPA BEAR, test 2.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "PAPA BEAR: TEST [" << test2 << "]" << io_end;
        printResult(papa2);

        // Display the verdict for PAPA BEAR in BOLD.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "PAPA BEAR: VERDICT" << io_end;
        ioc << ta_bold;
        printVerdict(papa1, papa2, test1, test2);

        // Display the results for BABY BEAR, test 1.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "BABY BEAR: TEST [" << test1 << "]" << io_end;
        printResult(baby1);

        // Display the results for BABY BEAR, test 2.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "BABY BEAR: TEST [" << test2 << "]" << io_end;
        printResult(baby2);

        // Display the verdict for BABY BEAR in BOLD.
        ioc << cat_normal << "\n" << bg_cyan << fg_black << "BABY BEAR: VERDICT" << io_end;
        ioc << ta_bold;
        printVerdict(baby1, baby2, test1, test2);

        // Cleanup: Delete the results arrays.
        delete [] results1;
        delete [] results2;
        // Null out the pointers to the results arrays (by habit).
        results1 = NULL;
        results2 = NULL;
    }

    void TestManager::resultFromArray(BenchmarkResult& result, uint64_t arr[], int repeat)
    {
        // Selection sort the array.
        stdutils::selection_sort(arr, repeat);

        // Store the repetition count.
        result.repeat = repeat;

        /* Calculate the accumulator (grand total).
         * For each item in the array...*/
        for(int i=0; i<repeat; i++)
        {
            // Add the value to the accumulator.
            result.acc += arr[i];
        }

        // Calculate mean.
        result.mean = result.acc / repeat;

        // Store the minimum and maximum values.
        result.min_val = arr[0];
        result.max_val = arr[repeat-1];

        // Calculate the range as the maximum - minimum values.
        result.range = result.max_val - result.min_val;

        /* Calculate standard deviance (s) from variance (s^2).
         * This is calculated as s^2 = [ (arr[i] - mean)^2 / (count-1) ]
         * and s = √[s^2]
        */
        // We'll be using this accumulator temporarily.
        int64_t v_acc = 0;
        // A temporary integer.
        int64_t temp = 0;
        // We'll loop to create the summation. For each value...
        for(int i=0; i<repeat; i++)
        {
            // Add (arr[i] - mean)^2 to the accumulator.
            temp = arr[i] - result.mean;
            v_acc += (temp * temp);
        }

        // The variance is the accumulator / the count minus one.
        double variance = v_acc/(repeat-1);
        // The standard deviation is the square root of the variance.
        result.std_dev = sqrt(variance);

        /* The relative standard deviation is the standard deviation / mean,
         * expressed as a percentage.*/
        result.rsd = (result.std_dev / result.mean) * 100;

        // Calculate median.
        int mI = repeat/2;
        // If we have a single value as our exact median...
        if(repeat%2 == 0)
        {
            // Store that value as the median.
            result.median = arr[mI];
        }
        // Otherwise, if we do NOT have a single value as our exact median...
        else
        {
            // Store the mean of the middle two values as the median.
            result.median = ((arr[mI] + arr[mI+1])/2);
        }

        // Calculate lower and upper quartile values.
        int q1I = repeat/4;
        int q3I = repeat*3/4;

        // We're following the same basic approach as with median.
        if(repeat%4 == 0)
        {
            result.q1 = arr[q1I];
            result.q3 = arr[q3I];
        }
        else
        {
            result.q1 = (arr[q1I] + arr[q1I+1])/2;
            result.q3 = (arr[q3I] + arr[q3I+1])/2;
        }

        // Calculate the interquartile value (transitory).
        uint64_t iq = result.q3 - result.q1;

        // Calculate the lower and upper inner and outer fence.
        result.lif = result.q1-(iq*1.5);
        result.uif = result.q3+(iq*1.5);
        result.lof = result.q1-(iq*3);
        result.uof = result.q3+(iq*3);

        /* Calculate the number of minor and major LOWER outliers.*/

        /* These will correspond to the index just past the last outlier
         * in each direction, for use in calculating the adjusted values,
         * which omit outliers.*/
        int lower_cutoff = 0;
        int upper_cutoff = repeat-1;

        // For each item (ascending)
        for(int i=0; i<repeat; i++)
        {
            //If the item is smaller than the inner fence value...
            if(arr[i] < result.lif)
            {
                //If the item is also smaller than the outer fence value...
                if(arr[i] < result.lof)
                {
                    //It is a major outlier.
                    result.low_out_major++;
                }
                //Otherwise...
                else
                {
                    //It is a minor outlier.
                    result.low_out_minor++;
                }
            }
            else
            {
                /* We've found the first non-outlier value.
                 * Store the index as lower cutoff.*/
                lower_cutoff = i;
                //We're done. No sense counting further in a sorted array.
                break;
            }
        }

         // For each item (descending)
        for(int i=(repeat-1); i>=0; i--)
        {
            //If the item is larger than the inner fence value...
            if(arr[i] > result.uif)
            {
                //If the item is also larger than the outer fence value...
                if(arr[i] > result.uof)
                {
                    //It is a major outlier.
                    result.upp_out_major++;
                }
                //Otherwise...
                else
                {
                    //It is a minor outlier.
                    result.upp_out_minor++;
                }
            }
            else
            {
                /* We've found the first non-outlier value.
                 * Store the index as upper cutoff.*/
                upper_cutoff = i;
                //We're done. No sense counting further in a sorted array.
                break;
            }
        }

        /* Calculate the adjusted accumulator.
         * For each item in the array, within cutoffs...*/
        for(int i=lower_cutoff; i<=upper_cutoff; i++)
        {
            // Add the value to the accumulator.
            result.acc_adj += arr[i];
        }

        // Calculate a new count to work with, omitting outliers.
        int repeat_adj = upper_cutoff - lower_cutoff;

        // Calculate adjusted mean.
        result.mean_adj = result.acc_adj / repeat_adj;
        // FIXME: Why is this giving a different answer than mean w/o any outliers?
        /* Possible answer (just found this comment again)...
         * because it's REMOVING OUTLIERS??
         */

        // Store the minimum and maximum non-outlier values.
        result.min_adj_val = arr[lower_cutoff];
        result.max_adj_val = arr[upper_cutoff];

        // Calculate the adjusted range as the maximum - minimum (adjusted) values.
        result.range_adj = result.max_adj_val - result.min_adj_val;

        /* Calculate adjusted standard deviance (s) from variance (s^2).
         * This is calculated as s^2 = [ (arr[i] - mean)^2 / (count-1) ]
         * and s = √[s^2], except using the adjusted numbers.
        */
        // We'll be reusing this accumulator from earlier.
        v_acc = 0;
        // We'll loop to create the summation. For each value...
        for(int i=0; i<repeat_adj; i++)
        {
            temp = arr[i] - result.mean_adj;
            // Add (arr[i] - mean)^2 to the accumulator.
            v_acc += (temp*temp);
        }
        // The variance is the accumulator / the count minus one.
        double variance_adj = v_acc/(repeat_adj-1);
        // The standard deviation is the square root of the variance.
        result.std_dev_adj = sqrt(variance_adj);

        /* The relative standard deviation is the standard deviation / mean,
         * expressed as a percentage.*/
        result.rsd_adj = (result.std_dev_adj / result.mean_adj) * 100;
    }

    void TestManager::printResult(BenchmarkResult& result)
    {
        /* If the adjusted relative standard deviation is greater than this
         * value, the accuracy of the other numbers is in serious doubt, and
         * should be taken with a grain of salt. In that situation, we will
         * highlight the RSD output line in red.*/
        int rsd_threshold = 25;

        //Output the relevant data, keeping formatting until the end.
        ioc << "\tMEAN (μ): " << result.mean << " / " << result.mean_adj << io_end_keep;

        ioc <<  "\tMIN-MAX(RANGE): " << result.min_val << "-" << result.max_val << "(" << result.range << ") / "
            <<  result.min_adj_val << "-" << result.max_adj_val << "(" << result.range_adj <<")" << io_end_keep;

        ioc << "\tOUTLIERS: " << result.low_out_major+result.low_out_minor << " LOW, "
            << result.upp_out_major+result.upp_out_minor << " HIGH" << io_end_keep;

        ioc << "\tSD (σ): " << set_precision(2) << result.std_dev << " / " << result.std_dev_adj << "" << io_end_keep;

        ioc << "\t" << (result.rsd_adj > rsd_threshold ? bg_red : bg_none)
            << "RSD: " << result.rsd << "% / " << result.rsd_adj << "%" << io_end;
    }

    void TestManager::printVerdict(BenchmarkResult& result1, BenchmarkResult& result2, name test1, name test2)
    {
        // Calculate difference between the non-adjusted mean averages.
        int64_t difference = result1.mean-result2.mean;
        // Calculate difference between the adjusted mean averages.
        int64_t difference_adj = result1.mean_adj-result2.mean_adj;

        // FOR NON-ADJUSTED (RAW) DATA...

        // If the absolute difference is less than either standard deviation...
        if(abs(difference) <= result1.std_dev || abs(difference) <= result2.std_dev)
        {
            //Non-adjusted, the tests are roughly identical.
            ioc << "\t     RAW: Both tests are roughly identical. (DIFF <= STD DEV)" << io_end_keep;
        }
        else
        {
            // If the first test won (its non-adjusted mean was smaller)...
            if(difference < 0)
            {
                // Declare the first test as faster, and by how much.
                ioc << "\t     RAW: [" << test1 << "] faster by approx. " << (abs(difference)) << " cycles." << io_end_keep;
            }
            //Else if the second test won (its non-adjusted mean was smaller)...
            else if(difference > 0)
            {
                // Declare the second test as faster, and by how much.
                ioc << "\t     RAW: [" << test2 << "] faster by approx. " << (abs(difference)) << " cycles." << io_end_keep;
            }
        }

        // FOR ADJUSTED DATA...

        // If the absolute difference is less than either standard deviation...
        if(abs(difference_adj) <= result1.std_dev_adj || abs(difference_adj) <= result2.std_dev_adj)
        {
            //Adjusted, the tests are roughly identical.
            ioc << "\tADJUSTED: Both tests are roughly identical. (DIFF <= STD DEV)" << io_end;
        }
        else
        {
            //If the first test won (its adjusted mean was smaller)...
            if(difference < 0)
            {
                // Declare the first test as faster, and by how much.
                ioc << "\tADJUSTED: [" << test1 << "] faster by approx. " << (abs(difference_adj) - result1.std_dev_adj) << " cycles." << io_end;
            }
            //Else if the second test won (its adjusted mean was smaller)...
            else if(difference > 0)
            {
                // Declare the second test as faster, and by how much.
                ioc << "\tADJUSTED: [" << test2 << "] faster by approx. " << (abs(difference_adj) - result2.std_dev_adj) << " cycles." << io_end;
            }
        }
    }
}
