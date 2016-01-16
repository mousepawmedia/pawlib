/* Goldilocks Test System, version 1.0 [PawLIB]
 *
 * Goldilocks stores, manages, and calls tests.
 * It also contains a runtime benchmarker which
 * measures CPU cycles for any given test with
 * as much accuracy as is possible from user-level
 * assembly code. Goldilock's benchmarker also
 * calculates additional useful statistical data,
 * especially for comparing the execution of two
 * tests.
 *
 * Last Updated: 16 November 2015
 * Author: Jason C. McDonald
 */

/* LICENSE
 * Copyright (C) MousePaw Games.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef TESTSUITE_H
#define TESTSUITE_H

//uint64_t and friends
#include <cstdlib>
//std::unique_ptr
#include <memory>
//std::map (we will use this here)
#include <map>
//std::vector (we will use this here)
#include <vector>

//Output
#include <iochannel.hpp>

using namespace pawlib;
using namespace pawlib::ioformat;

namespace pawlib
{
    /** All tests are derived from this base
     * class.*/
    class Test : public sigc::trackable
    {
        public:
            /**A Test generally should not have a constructor.
             * Instead, setup tasks (such as dynamic allocation)
             * should be performed by `pre()`, so `prefail()`, `post()`,
             * and `postmortem()` can handle cleanup depending on the
             * test's success.
             * In short, THIS SHOULD ALWAYS BE EMPTY!
             */
            Test(){}

            /**Set up for the test. Called only once, even if test is
             * repeated multiple times.
             * \return true if successful, false if it fails.*/
            virtual bool pre(){return true;}

            /**Clean up from a failed pre-test.
             * \return true if successful, false if it fails.*/
            virtual bool prefail(){return true;}

            /**Clean up from a failed pre-test.
             * \return true if successful, false if it fails.*/
            virtual bool run()=0;

            /**Clean up after successful test.
             * \return true if successful, false if it fails.*/
            virtual bool post(){return true;}

            /**Clean up after a failed test.
             * \return true if successful, false if it fails.*/
            virtual bool postmortem(){return true;}

            /**Like the constructor, a destructor is unnecessary for a Test.
             * Cleanup should be handled by `prefail()`, `post()`, and
             * `postmortem()`, depending on the test's success.
             * In short, THIS SHOULD ALWAYS BE EMPTY!*/
            virtual ~Test(){}
    };

    /* Q: Where Is TestSuite?
     * A: It turns out that having a separate TestSuite is rather
     * redundant. Since the idea is that multiple tests need to be
     * run, but that each test suite requires different rules, outputs,
     * and other custom functionality to work as expected in each situation,
     * it is just more efficient to have the end-developer write a Test
     * that runs multiple tests via `testmanager.run_test()`. Most tests
     * handle their own setup and cleanup, so a suite's pre/post tasks would
     * also be completely custom, like a Test is. Therefore, since a TestSuite
     * is just a Test with a different name, we don't bother increasing the
     * size of our code, class, or memory usage to accommodate it.
     */

    /**TestManager stores and calls tests by names. It exposes functions for
     * testing and benchmarking, and automatically handles the proper call
     * sequence for any Test object. It also handles garbage collection for
     * all tests under its control.*/
    class TestManager
    {
        public:
            /* We are using smart pointers, so that TestManager exclusively
             * owns all test instances it uses, and thus can delete them
             * automatically later.*/

             /* The Test smart pointer type shall henceforth be known
              * as "test_ptr".*/
            typedef std::unique_ptr<Test> test_ptr;

            /* The type we use for storing test names shall henceforth be
             * known as "name". Basically, I'm doing this so we can swap to
             * `pawlib::pawstring` later, and back again if necessary.*/
            typedef std::string name;
            // TODO: Change `name` typedef to pawstring.

            /**The TestManager doesn't need anything to its constructor,
             * as all of its tests will be added ("registered") after the
             * fact, and it doesn't do any heap allocation besides that.*/
            TestManager(){}

            /**Register a new test with the TestManager.
             * \param a string of the test's name
             * \param a pointer to the test. The safest way to use this is to
             * pass the "new Test" as this argument, since TestManager will be
             * taking exclusive ownership of the instance. It will handle
             * NULL automatically, so no error checking is required.*/
            void register_test(name, Test*);

            /**Run a test by name.
             * \param the name of the test to run*/
            void run_test(name);

            /**Measure the approximate number of CPU cycles that a particular
             * test takes to run.
             *
             * WARNING: This tool is not a replacement for a proper code
             * profiler. See the documentation for more information.
             * \param the name of the test to benchmark
             * \param the number of times to run the test
             * (10 - 10,000, default 100). The more repetitions we have,
             * the more accurate the benchmark will be - but bear execution
             * time in mind, as some tests can take a while.*/
            void run_benchmark(name, int=100);

            /**Benchmark and compare two tests using a three-pass system.
             * The three passes - MAMA BEAR, PAPA BEAR, and BABY BEAR -
             * handle test execution sequence differently to account for
             * cache warming factors.
             *
             * The tests should be designed to perform the exact same logical
             * task by two different methods.
             *
             * WARNING: This tool is not a replacement for a proper code
             * profiler. See the documentation for more information.
             * \param the name of test A
             * \param the name of test B
             * \param the number of times to run each test per pass
             * (10 - 10,000, default 100). The more repetitions we have,
             * the more accurate the benchmark will be - but bear execution
             * time in mind, as some tests can take a while.
             * In short, we have 100 repetitions each * 2 tests * 3 passes,
             * or 100 => 600 total repetitions.*/
            void run_compare(name, name, int=100);

            /**We don't need anything in the destructor, as the smart pointers
             * handle deletion automatically.*/
            ~TestManager(){}
        protected:

            /**The BenchmarkResult struct stores all of the statistical data
             * from a single test benchmark. Having this struct makes our
             * code more efficient, and allows us to write standard
             * functions for calculating results and comparisons, and
             * outputting everything.*/
            struct BenchmarkResult
            {
                /// The accumulated count.
                uint64_t acc = 0;
                /// The adjusted accumulated count.
                uint64_t acc_adj = 0;
                /// The number of repetitions (size).
                uint64_t repeat = 0;
                /// The average (mean).
                uint64_t mean = 0;
                /// The adjusted average (mean).
                uint64_t mean_adj = 0;
                /// The median value.
                uint64_t median = 0;
                /// The lower quartile value.
                uint64_t q1 = 0;
                /// The upper quartile value.
                uint64_t q3 = 0;
                /// The range.
                uint64_t range = 0;
                /// The adjusted range.
                uint64_t range_adj = 0;
                /// The minimum value.
                uint64_t min_val = 0;
                /// The minimum non-outlier value.
                uint64_t min_adj_val = 0;
                /// The maximum value.
                uint64_t max_val = 0;
                /// The maximum non-outlier value.
                uint64_t max_adj_val = 0;
                /// Lower inner fence value.
                uint64_t lif = 0;
                /// Lower outer fence value
                uint64_t lof = 0;
                /// Upper inner fence value.
                uint64_t uif = 0;
                /// Upper outer fence value.
                uint64_t uof = 0;
                /// The number of low minor outliers
                uint64_t low_out_minor = 0;
                /// The number of low major outliers
                uint64_t low_out_major = 0;
                /// The number of upper minor outliers
                uint64_t upp_out_minor = 0;
                /// The number of upper major outliers
                uint64_t upp_out_major = 0;
                /// The standard deviance
                double std_dev = 0;
                /// The adjusted standard deviance
                double std_dev_adj = 0;
                /// The relative standard deviation (coefficient of variation)
                uint8_t rsd = 0;
                /// The adjusted relative standard deviation
                uint8_t rsd_adj = 0;
            };

            /**Convert a raw array of clock measurements into a complete
             * benchmark result. This does all of our statistical computations.
             * \param the BenchmarkResult instance to write to
             * \param the array of CPU cycle measurements, stored as
             * 64-bit integers
             * \param the size of the array (number of measurements)*/
            void resultFromArray(BenchmarkResult&, uint64_t arr[], int);

            /**Print the data from a BenchmarkResult. This uses the
             * standard IOChannel. Output formatting is retained until the end
             * of the function, so you can modify formatting by preceding this
             * function call with `ioc << [SOME FORMATTING TAGS] << io_send_keep;`
             * \param the BenchmarkResult to output from */
            void printResult(BenchmarkResult&);

            /**Compare and print two BenchmarkResults. This calculates which
             * result was faster, based on the adjusted statistics (outliers
             * removed), and factoring uncertainty into the verdict.
             * Output formatting is retained until the end
             * of the function, so you can modify formatting by preceding this
             * function call with `ioc << [SOME FORMATTING TAGS] << io_send_keep;`
             * \param the BenchmarkResult from test A
             * \param the BenchmarkResult from test B
             * \param the name of test A (optional)
             * \param the name of test B (optional)*/
            void printVerdict(BenchmarkResult&, BenchmarkResult&, name = "TEST A", name = "TEST B");

            /** Calibrate the CPU clocking functionality by serializing the
             * assembly instruction cache, per Intel's documentation on RDTSC.*/
            void calibrate();

            /** Measure the number of CPU cycles it takes to execute a test
             * (or just the measurement itself, to get a baseline measurement).
             * To increase average accuracy, this does not serialize execution.
             * We are assuming that an out-of-order measurement will get removed
             * as an outlier in a set of measurements.
             * \param the raw pointer to the test to run. If omitted, no test
             * will be executed, allowing us to measure the execution time of
             * the measurement instructions themselves.
             * \return the CPU cycle measurement as a 64-bit unsigned integer*/
            uint64_t clock(Test* = 0);

            /** Print the banner for the benchmarker functions using IOChannel.*/
            void benchmark_banner();

            /// Stores all of the test pointers for access-by-name-string.
            std::map<name, test_ptr> tests;

            /* We are using std::map intentionally above. Dynamic allocation is
             * more appropriate in this situation, especially since test
             * registration should be on-demand and front-loaded (all at once).*/
    };

    /// The static (extern) global instance of the TestManager.
    extern TestManager testmanager;
}


#endif // TESTSUITE_H
