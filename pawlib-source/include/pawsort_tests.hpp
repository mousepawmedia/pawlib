/* LICENSE
 * Copyright (c) 2016 MousePaw Games.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef PAWSORT_TESTS_HPP
#define PAWSORT_TESTS_HPP

#include <algorithm>

#include <goldilocks.hpp>
#include <pawsort.hpp>

namespace pawlib
{
    class TestSort : public Test
    {
        public:
            enum TestArrayType
            {
                /// Totally random array. Not recommended; inconsistent results.
                ARRAY_RANDOM,
                /// Already sorted array.
                ARRAY_SORTED,
                /// Already sorted array in reverse.
                ARRAY_REVERSED,
                /// Nearly sorted - the order of every two are inverted.
                ARRAY_NEARLY_2,
                /// Nearly sorted - the order of every five are inverted.
                ARRAY_NEARLY_5,
                /// Few (specifically, five) unique values.
                ARRAY_FEW_UNIQUE,
                /** Only two values are out of place. This fails PawSort's
                  * check-for-sorted test, thereby causing the algorithm
                  * to display behavior close to "already sorted". */
                ARRAY_BLACK_SHEEP,
                /** Ascends from 0 to half, twice sequentially. May cause
                  * similar problems to SORTED, but not as extreme. */
                ARRAY_DOUBLE_CLIMB,
                /** Descends from half to 0, twice sequentially. May cause
                  * similar problems to RESERVED, but not as extreme. */
                ARRAY_DOUBLE_DROP,
                /** Ascends and descends stairs, with a jump of 5. */
                ARRAY_STAIRS,
                /** Ascends from 0 to half, and drops back to 0. */
                ARRAY_MOUNTAIN,
                /** Ascends from 0 to half and drops, twice. Uses double-jumps. */
                ARRAY_DOUBLE_MOUNTAIN,
                /** Ascends by huge increments, and drops back to 0. */
                ARRAY_EVEREST,
                /** Ascends by huge increments, and then drops off suddenly. */
                ARRAY_CLIFF,
                /** Ascends from 0 towards half, spikes suddenly, and then drops
                  * back down near half and descends towards 0. Intended to throw
                  * off the median-of-three by creating an absurdly high middle
                  * value.*/
                ARRAY_SPIKE,
                /** Composed of pairs - one starting at 0 and incrementing by
                  * one each pair, and one starting at n and decrementing by
                  * one each pair, with the middle pair values both being half
                  * of n. */
                ARRAY_CHICKEN,
                /** Brutally murders the median-of-three by placing 0 at the
                  * first, middle, and last indices, on top of a reversed
                  * sorted array with few unique values. Really, this is just evil
                  * incarnate. */
                ARRAY_NIGHTMARE
            };

        protected:
            // CHANGE ME: This is the size of the array. Must be a multiple of 10.
            static const int test_size = 10000;
            // CHANGE ME: This is the type of array to generate.
            TestArrayType arrayType;
            int start_arr[test_size];
            int test_arr[test_size];

            testdoc_t title;
            testdoc_t docs;

        public:
            // cppcheck-suppress uninitMemberVar
            explicit TestSort(TestArrayType type):arrayType(type)
            {
                // We'll initialize titles and doc strings in the constructor.
                switch(arrayType)
                {
                    case ARRAY_RANDOM:
                    {
                        title = "Pawsort: Random";
                        docs = "Random array. DO NOT USE.";
                        break;
                    }
                    case ARRAY_SORTED:
                    {
                        title = "PawSort: Sorted Array";
                        docs = "Already sorted array.";
                        break;
                    }
                    case ARRAY_REVERSED:
                    {
                        title = "PawSort: Reversed Array";
                        docs = "Already sorted array in reverse.";
                        break;
                    }
                    case ARRAY_NEARLY_2:
                    {
                        title = "PawSort: Nearly, Invert 2";
                        docs = "Nearly sorted array - the order of every two are inverted.";
                        break;
                    }
                    case ARRAY_NEARLY_5:
                    {
                        title = "PawSort: Nearly, Invert 5";
                        docs = "Nearly sorted array - the order of every five are inverted.";
                        break;
                    }
                    case ARRAY_FEW_UNIQUE:
                    {
                        title = "PawSort: Few Unique";
                        docs = "Few (specifically, five) unique values in the array.";
                        break;
                    }
                    case ARRAY_BLACK_SHEEP:
                    {
                        title = "PawSort: Black Sheep";
                        docs = "Array with only two values out of place.";
                        break;
                    }
                    case ARRAY_DOUBLE_CLIMB:
                    {
                        title = "PawSort: Double Climb";
                        docs = "Array values ascends from 0 to half, twice sequentially.";
                        break;
                    }
                    case ARRAY_DOUBLE_DROP:
                    {
                        title = "PawSort: Double Drop";
                        docs = "Array values descend from half to 0, twice sequentially.";
                        break;
                    }
                    case ARRAY_STAIRS:
                    {
                        title = "PawSort: Stairs";
                        docs = "Array ascends and descends 'stairs', with a jump of 5.";
                        break;
                    }
                    case ARRAY_MOUNTAIN:
                    {
                        title = "PawSort: Mountain";
                        docs = "Array ascends from 0 to half and drops back to 0.";
                        break;
                    }
                    case ARRAY_DOUBLE_MOUNTAIN:
                    {
                        title = "PawSort: Double Mountain";
                        docs = "Array ascends from 0 to half and drops, twice. Uses double-jumps.";
                        break;
                    }
                    case ARRAY_EVEREST:
                    {
                        title = "PawSort: Everest";
                        docs = "Array ascends by huge increments, and then drop back to 0.";
                        break;
                    }
                    case ARRAY_CLIFF:
                    {
                        title = "PawSort: Cliff";
                        docs = "Array ascends by huge increments, and then drops off suddenly.";
                        break;
                    }
                    case ARRAY_SPIKE:
                    {
                        title = "PawSort: Spike";
                        docs = "Array ascends from 0 towards half, spikes suddenly, and then drops \
back down near half and descends towards 0. Intended to throw off the \
median-of-three by creating an absurdly high middle value.";
                        break;
                    }
                    case ARRAY_CHICKEN:
                    {
                        title = "PawSort: Chicken";
                        docs = "Array composed of pairs - one starting at 0 and incrementing by \
one each pair, and one starting at n and decrementing by one each [pair, with \
the middle pair values both being half of n.";
                        break;
                    }
                    case ARRAY_NIGHTMARE:
                    {
                        title = "PawSort: Nightmare";
                        docs = "Array brutally murders the median-of-three by placing 0 at the \
first, middle, and last indices, on top of a reversed sorted array with few \
unique values. Really, this is just evil incarnate.";
                        break;
                    }
                }
            }

            virtual testdoc_t get_title() = 0;

            testdoc_t get_docs()
            {
                return docs;
            }

            bool pre()
            {
                // Random seed
                srand(time(NULL));

                // If the test size is not divisible by 10...
                if(test_size % 10 != 0)
                {
                    /* Abort - many array generation types rely on
                     * a number of elements disible by ten. */
                    return false;
                }

                switch(arrayType)
                {
                    case ARRAY_RANDOM:
                    {
                        for(int i = 0; i < test_size; ++i)
                        {
                            start_arr[i] = (rand() % 100 + 1);
                        }
                        break;
                    }
                    case ARRAY_SORTED:
                    {
                        for(int i = 0; i < test_size; ++i)
                        {
                            start_arr[i] = i;
                        }
                        break;
                    }
                    case ARRAY_REVERSED:
                    {
                        for(int i = 0; i < test_size; ++i)
                        {
                            start_arr[i] = test_size-i;
                        }
                        break;
                    }
                    case ARRAY_NEARLY_2:
                    {
                        for(int i = 0; i < test_size; i+=2)
                        {
                            // The first number in the pair has a higher value.
                            start_arr[i] = i+1;
                            // The second number in the pair has the lower value.
                            start_arr[i+1] = i;
                        }
                        break;
                    }
                    case ARRAY_NEARLY_5:
                    {
                        for(int i = 0; i < test_size; i+=5)
                        {
                            // Loop through five indices...
                            for(int j = 0; j < 5; ++j)
                            {
                                /* For each index in the set of 5, write the
                                 * index plus the opposite subindex.
                                 * For example, if i=6, we'd be looping
                                 * 6, 7, 8, 9, 10, and writing the values
                                 * 10, 9, 8, 7, 6. */
                                start_arr[i+j] = i+(4-j);
                            }
                        }
                        break;
                    }
                    case ARRAY_FEW_UNIQUE:
                    {
                        //Only have 6 unique values.
                        int jump = test_size / 6;
                        //Start with 22 for our first value.
                        int value = 22;
                        //Calculate half.
                        int half = test_size / 2;
                        for(int i = 0; i < half; i+=jump)
                        {
                            // Loop through (jump) number of indices...
                            for(int j = 0; j < jump; ++j)
                            {
                                // Use the value for this set.
                                start_arr[i+j] = value;
                                start_arr[(test_size-1)-(i+j)] = value+2;
                            }
                            /* Decrement value before making the next jump.*/
                            value -= 5;
                        }
                        break;
                    }
                    case ARRAY_BLACK_SHEEP:
                    {
                        // First, generate an already-sorted array.
                        for(int i = 0; i < test_size; ++i)
                        {
                            start_arr[i] = i;
                        }
                        // Swap the 1/3 and 2/3 indices.
                        int third = test_size/3;
                        int tmp = start_arr[third];
                        start_arr[third] = start_arr[third+third];
                        start_arr[third+third] = tmp;
                        break;
                    }
                    case ARRAY_DOUBLE_CLIMB:
                    {
                        int half = test_size/2;
                        for(int i = 0; i < half; ++i)
                        {
                            start_arr[i] = i;
                            start_arr[i+half] = i;
                        }
                        break;
                    }
                    case ARRAY_DOUBLE_DROP:
                    {
                        int half = test_size/2;
                        for(int i = 0; i < half; ++i)
                        {
                            start_arr[i] = half-i;
                            start_arr[i+half] = half-i;
                        }
                        break;
                    }
                    case ARRAY_STAIRS:
                    {
                        int half = test_size/2;
                        int maxI = test_size-1;
                        int jump = 5;
                        for(int i = 0; i < half; i+=jump)
                        {
                            for(int j = 0; j < jump; ++j)
                            {
                                start_arr[i+j] = i;
                                start_arr[maxI-(i+j)] = i;
                            }
                        }
                        break;
                    }
                    case ARRAY_MOUNTAIN:
                    {
                        int half = test_size/2;
                        int maxI = test_size-1;
                        for(int i = 0; i < half; ++i)
                        {
                            start_arr[i] = i;
                            start_arr[maxI-i] = i;
                        }
                        break;
                    }
                    case ARRAY_DOUBLE_MOUNTAIN:
                    {
                        int half = test_size/2;
                        int qtr = half/2;
                        int value = 0;
                        for(int i = 0; i < half; ++i)
                        {
                            start_arr[i] = value;
                            start_arr[i+half] = value;
                            (i > qtr) ? --value : ++value;
                        }
                        break;
                    }
                    case ARRAY_EVEREST:
                    {
                        int half = test_size/2;
                        int maxI = test_size-1;
                        int value = 0;
                        for(int i = 0; i < half; ++i)
                        {
                            start_arr[i] = value;
                            start_arr[maxI-i] = value;
                            value+=(test_size/6);
                        }
                        break;
                    }
                    case ARRAY_CLIFF:
                    {
                        int dropoff = test_size - (test_size/10);
                        for(int i = 0; i < dropoff; ++i)
                        {
                            start_arr[i] = i;
                        }
                        int value = test_size-dropoff;
                        for(int i = dropoff; i < test_size; ++i)
                        {
                            start_arr[i] = value--;
                        }
                        break;
                    }
                    case ARRAY_SPIKE:
                    {
                        int half = test_size/2;
                        int maxI = test_size-1;
                        int value = 0;
                        for(int i = 0; i < half-4; ++i)
                        {
                            start_arr[i] = value;
                            start_arr[maxI-i] = value;
                            ++value;
                        }
                        for(int i = half-4; i < half; ++i)
                        {
                            value+=(test_size/6);
                            start_arr[i] = value;
                            start_arr[maxI-i] = value;
                        }
                        break;
                    }
                    case ARRAY_CHICKEN:
                    {
                        // Increments from 0 to half.
                        int low = 0;
                        // Decrements from test_size-1 to half.
                        int high = test_size-1;
                        for(int i = 0; i < test_size; i+=2)
                        {
                            // The first number in the pair is the low value.
                            start_arr[i] = low++;
                            // The second number in the pair is the high value.
                            start_arr[i+1] = high--;
                        }
                        break;
                    }
                    case ARRAY_NIGHTMARE:
                    {
                        //Only have 5 unique values.
                        int jump = test_size / 5;
                        //Use values 5-9
                        int value = 9;
                        for(int i = 0; i < test_size; i+=jump)
                        {
                            // Loop through (jump) number of indices...
                            for(int j = 0; j < jump; ++j)
                            {
                                // Use the value for this set.
                                start_arr[i+j] = value;
                            }
                            /* Decrement the value, to preserve the "reverse sorted"
                             * property of the array.*/
                            --value;
                        }

                        /* Be evil and overwrite the first, middle, and last
                         * indices, which are used for median-of-three, with
                         * the lowest value. This also breaks the sequence and
                         * forces PawSort to attempt a sort.*/
                        start_arr[0] = value;
                        start_arr[(test_size/2)-1] = value;
                        start_arr[(test_size/2)] = value;
                        start_arr[test_size-1] = value;

                        break;
                    }
                    default:
                    {
                        return false;
                    }
                }

                for(int i = 0; i < test_size; ++i)
                {
                    test_arr[i] = start_arr[i];
                }

                return true;
            }
            bool janitor()
            {
                for(int i = 0; i < test_size; ++i)
                {
                    test_arr[i] = start_arr[i];
                }
                return true;
            }
            virtual bool run()
            {
                return true;
            }
            virtual ~TestSort(){}

    };

    class TestStdSort : public TestSort
    {
        public:
            explicit TestStdSort(TestArrayType type):TestSort(type)
            {}

            testdoc_t get_title()
            {
                return title + " (std::sort)";
            }

            bool run()
            {
                std::sort(std::begin(test_arr), std::end(test_arr));
                return true;
            }
            ~TestStdSort(){}

    };

    class TestPawSort : public TestSort
    {
        public:
            explicit TestPawSort(TestArrayType type):TestSort(type)
            {}

            testdoc_t get_title()
            {
                return title + " (pawsort)";
            }

            bool run()
            {
                pawsort::introsort(test_arr, test_size);
                return true;
            }
            ~TestPawSort(){}
    };

    class TestSuite_Pawsort : public TestSuite
    {
        public:
            explicit TestSuite_Pawsort(){}

            void load_tests();

            testdoc_t get_title()
            {
                return "PawLIB: Pawsort Tests";
            }

            ~TestSuite_Pawsort(){}
    };
}

#endif // PAWSORT_TESTS_HPP
