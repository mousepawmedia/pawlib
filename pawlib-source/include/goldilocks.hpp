/** Goldilocks Test System [PawLIB]
  * Version: 1.0
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
  * Last Updated: 6 April 2016
  * Author: Jason C. McDonald
  */

/* LICENSE
 * Copyright (C) 2016 MousePaw Games. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
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

//Sorting
#include <pawsort.hpp>

using namespace pawlib;
using namespace pawlib::ioformat;

namespace pawlib
{
    /** All tests are derived from this base
     * class.*/
    class Test
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

            /**Clean up between successful runs, in preparation for a repeat.
             * \return true if successful, false if it fails.*/
            virtual bool janitor(){return true;}

            /**Run test.
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

    /**A TestSuite is responsible for registering a batch of Tests with
     * Goldilocks Test Manager on demand. This is primarily useful if an
     * interactive test console is implemented, as we can load batches of
     * tests when, and only when, we need them. A TestSuite should also
     * be able to report what tests it contains, for user reference while
     * using the interactive test console.
     */
    class TestSuite
    {
        public:
            TestSuite(){}
            virtual void load_tests() = 0;
            virtual ~TestSuite(){}
    };

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
              * as "testptr_t".*/
            typedef std::unique_ptr<Test> testptr_t;

            /* The type we use for storing test names shall henceforth be
             * known as "name". Basically, I'm doing this so we can swap to
             * `pawlib::pawstring` later, and back again if necessary.*/
            typedef std::string testname_t;

            /* The type we use for storing documentation strings. Like with
             * `testname_t`, I'm doing this so we can swap to another string
             * library, such as `pawlib::pawstring`, later, and back again
             * if necessary. */
            typedef std::string testdoc_t;

            /**The TestManager doesn't need anything to its constructor,
             * as all of its tests will be added ("registered") after the
             * fact, and it doesn't do any heap allocation besides that.*/
            TestManager(){}

            /**List all tests registered with the TestManager.
             */
            void list_tests(bool=false);

            /**Get the documentation string for a given test.
             * \param the test to return the documentation string for
             * \return the documentation string.
             */
            void show_docs(testname_t);

            /**Register a new test with the TestManager.
             * \param a string of the test's name
             * \param a pointer to the test. The safest way to use this is to
             * pass the "new Test" as this argument, since TestManager will be
             * taking exclusive ownership of the instance. It will handle
             * NULL automatically, so no error checking is required.*/
            void register_test(testname_t, Test*, testdoc_t = "", testdoc_t = "");

            /**Interactively (confirm before start) run a test by name.
             * \param the name of the test to run*/
            void i_run_test(testname_t);

            /**Interactively run a benchmark by name.
             *
             * \param the name of the test to benchmark
             * \param the number of times to run the test */
            void i_run_benchmark(testname_t, unsigned int=100);

            /**Interactively (confirm before start) run a comparative
             * benchmark by test name.
             * \param the name of test A
             * \param the name of test B
             * \param the number of times to run each test per pass
             * \param whether to print all of the output, or just the summaried
             * verdict */
            void i_run_compare(testname_t, testname_t, unsigned int=100, bool=true);

            /**Run a test by name.
             * \param the name of the test to run*/
            void run_test(testname_t);

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
            void run_benchmark(testname_t, unsigned int=100);

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
             * \param whether to print all of the output, or just the summaried
             * verdict.
             * (10 - 10,000, default 100). The more repetitions we have,
             * the more accurate the benchmark will be - but bear execution
             * time in mind, as some tests can take a while.
             * In short, we have 100 repetitions each * 2 tests * 3 passes,
             * or 100 => 600 total repetitions.*/
            void run_compare(testname_t, testname_t, unsigned int=100, bool=true);

            /**We don't need anything in the destructor, as the smart pointers
             * handle deletion automatically.*/
            ~TestManager(){}
        protected:
            /**Validate that the test (by name) is registered with Golidlocks.
             * this is critical in preventing segfaults from accessing
             * invalid tests.
             *
             * \param the name of the test to check for
             * \param whether to display an error message if there is no match
             * \return true if the test exists, else false
             */
            bool validate(testname_t, bool=false);

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

            struct TestInfo
            {
                TestInfo(testdoc_t titleIn="", testdoc_t docIn="")
                    :title(titleIn), doc(docIn)
                    {}
                /// The human-readable title for the test.
                testdoc_t title;
                /// The documentation string for the test.
                testdoc_t doc;
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
            void printVerdict(BenchmarkResult&, BenchmarkResult&, testname_t = "TEST A", testname_t = "TEST B");

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

            /** Stores all of the test pointers for access-by-name-string. */
            std::map<testname_t, testptr_t> tests;
            /**Stores all of the test info (and docs), accessed by
              * name string.*/
            std::map<testname_t, TestInfo> test_info;

            /* We are using std::map intentionally above. Dynamic allocation is
             * more appropriate in this situation, especially since test
             * registration should be on-demand and front-loaded (all at once).*/
    };
}


#endif // TESTSUITE_H
