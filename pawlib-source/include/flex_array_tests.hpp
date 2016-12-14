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

#ifndef FLEX_ARRAY_TEST_HPP
#define FLEX_ARRAY_TEST_HPP

#include <vector>

#include <flex_array.hpp>
#include <goldilocks.hpp>
#include <stdutils.hpp>

/*for debugging and performance reasons
* there are signed int versions and unsigned int
* versions of the folowing tests
*/

namespace pawlib
{
    //TestVector_Push Function unsigned version
    class TestVector_Push : public Test
    {
        private:
            unsigned int iters;

        public:
            //TestVector_Push constructor with iterators
            explicit TestVector_Push(unsigned int iterations): iters(iterations){}

            //Test title
            testdoc_t get_title()
            {
                return "FlexArray: Push " + stdutils::itos(iters, 10) + " Integers (std::vector)";
            }

            //get documentation section
            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " integers to the back of a vector (push).";
            }

            // Run the test
            bool run()
            {
                //Create instance of vector, vec
                std::vector<unsigned int> vec;

                for(unsigned int i=0; i<iters; ++i)
                {
                    //iters should equal 1000 in this case
                    //increment i from 0 until it equals iters
                    vec.push_back(i);
                }
                return true;
            }

            //TestVector_Push destructor
            ~TestVector_Push(){}

    };


    class TestFArray_Push : public Test
    {
        private:
                unsigned int iters;

        //FlexArray constructor with iterators
        public:
            explicit TestFArray_Push(unsigned int iterations): iters(iterations){}

            //Test title
            testdoc_t get_title()
            {
                return "FlexArray: Push " + stdutils::itos(iters, 10) + " Integers (std::vector)";
            }
            //Test documentation
            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " integers at the back of a flexarray (push).";
            }
            // Run the test
            bool run()
            {
                //Create instance of flexarray
                pawlib::FlexArray< unsigned int> flex;

                //iters should equal 1000 in this case
                //increment i from 0 until it equals iters
                for(unsigned int i=0; i<iters; ++i)
                {
                    //if the index is not out of bounds push iters (1000)
                    if(flex.push(i) == false)
                    {
                    return false;
                    }
                }
                return true;
            }

            // Destructor
            ~TestFArray_Push(){}

    };


    class TestVector_Shift : public Test
    {
        //Testvector_Shift constructor with iterators
        public:
           explicit TestVector_Shift(unsigned int iterations): iters(iterations){}

            //Test title
            testdoc_t get_title()
            {
                return "FlexArray: Shift " + stdutils::itos(iters, 10) + " Integers to Front (std::vector)";
            }

            //Test documentation
            testdoc_t get_docs()
            {
                return "Shift " + stdutils::itos(iters, 10) + " integers to the front of a vector (shift).";
            }

            //Run the test
            bool run()
            {
                //Create instance of vector, vec
                std::vector<unsigned int> vec;

                //iters should equal 1000 in this case
                //increment i from 0 until it equals iters
                for(unsigned int i=0; i<iters; ++i)
                {
                    //insert at front of vector
                    vec.insert(vec.begin(), i);
                }
                return true;
            }

            ~TestVector_Shift(){}

            private:
                unsigned int iters;
     };

     class TestFArray_Shift: public Test
     {
        private:
            unsigned int iters;

        //TestFArray_Shift constructor with iterators
        public:
            explicit TestFArray_Shift(unsigned int iterations): iters(iterations){}

            //Test title
            testdoc_t get_title()
            {
                return "FlexArray: Shift " + stdutils::itos(iters, 10) + " Integers to Front (flexarray)";
            }
            //Test description
            testdoc_t get_docs()
            {
                return "Insert " + stdutils::itos(iters, 10) + " integers to the front of a flexarray using insert at 0 (shift).";
            }

            //Run the test
            bool run()
            {
                //create instance of Flexarray, flex
                pawlib::FlexArray<unsigned int> flex;

                //iters should equal 1000 in this case
                //increment i from 0 until it equals iters
                for(unsigned int i=0; i<iters; ++i)
                {
                    //if there is something at position zero move on
                    if(!flex.insert(i,0))
                    {
                        return false;
                    }
                }
                return true;
            }

            ~TestFArray_Shift(){}

    };

    class TestFArray_Insert : public Test
    {
        private:
            unsigned int iters;

        //TestFArray_insert constructor with iterators
        public:
            explicit TestFArray_Insert(unsigned int iterations): iters(iterations){}
            //Test title
            testdoc_t get_title()
            {
                return "FlexArray: Insert " + stdutils::itos(iters, 10) + " Integers At Middle (flexarray)";
            }
            // Test description
            testdoc_t get_docs()
            {
                return "Insert " + stdutils::itos(iters, 10) + " integers at the middle of a flexarray. \
Middle is calculated as size()/2.";
            }

            bool run()
            {
                pawlib::FlexArray<unsigned int> flex;

                /* We initially push two values, to make the
                 * math calculating the insert index a bit safer.*/
                flex.push(0);
                flex.push(1);

                for(unsigned int i=1; i<iters; ++i)
                {
                    int j = flex.getSize()/2;
                    flex.insert(j, i);
                }
                return true;
            }

            ~TestFArray_Insert(){}

    };


   // TestVector_Insert Function
    class TestVector_Insert : public Test
    {
        private:
            unsigned int iters;

        public:
            explicit TestVector_Insert(unsigned int iterations): iters(iterations){}

            testdoc_t get_title()
            {
                return "FlexArray: Insert " + stdutils::itos(iters, 10) + " Integers At Middle (std::vector)";
            }

            testdoc_t get_docs()
            {
                return "Insert " + stdutils::itos(iters, 10) + " integers at the middle of a vector. Middle \
is calculated as size()/2.";
            }

            bool run()
            {
                std::vector< unsigned int> vec;

                // We initially push two values, to make the
                // math calculating the insert index a bit safer.
                vec.push_back(0);
                vec.push_back(1);

                for(unsigned int i=1; i<1000; ++i)
                {
                    unsigned int j = vec.size()/2;
                    vec.insert(vec.begin()+j, i);
                }
                return true;
            }

            ~TestVector_Insert(){}

    };

    class TestVector_Erase : public Test
    {
        private:
            //left declaration in private class to avoid doing so in both janitor() and run()
            std::vector<unsigned int> vec;
            unsigned int iters;

        // Testvector_Pop Constructor with iterators
        public:
          explicit  TestVector_Erase(unsigned int iterations): iters(iterations){}

             //Test title
            testdoc_t get_title()
            {
                return "FlexArray: Erase " + stdutils::itos(iters, 10) + " Integers (std::vector)";
            }
            //Test documentation
            testdoc_t get_docs()
            {
                return "Erase " + stdutils::itos(iters, 10) + " integers at the front of a Vector (pop).";
            }

            //Clean up between successful runs, in preparation for a repeat
            bool janitor()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    vec.push_back(i);
                }
                return true;
            }

            //Run the test
            bool run()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    if(vec.front() != i)
                    {
                        return false;
                    }
                    vec.pop_back();
                }
                return true;
            }

            ~TestVector_Erase(){}
    };

    // removes element at any given index as opposed to erase so needs special test...
    class TestFArray_Yank : public Test
    {
        private:
            //left declaration in private class to avoid doing so in both janitor() and run()
            pawlib::FlexArray<unsigned int> flex;
            unsigned int iters;

        // Testvector_Pop Constructor with iterators
        public:
           explicit TestFArray_Yank(unsigned int iterations): iters(iterations){}
            //Test title
            testdoc_t get_title()
            {
                return "FlexArray: Yank " + stdutils::itos(iters, 10) + " Integers (flexarray)";
            }
            //Test documentation
            testdoc_t get_docs()
            {
                return "Erase " + stdutils::itos(iters, 10) + " integers at any given index (yank).";
            }

            bool pre()
            {
                return janitor();
            }

            //Clean up between successful runs, in preparation for a repeat
            bool janitor()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    flex.push(i);
                }
                return true;
            }
            //Run the test
            bool run()
            {
                for(int i=(iters-1); i>=0; --i)
                {
                    unsigned int temp = flex.at(i);
                    if(flex.yank(i) != temp)
                    {
                        return false;
                    }
                }
                return true;
            }
        ~TestFArray_Yank(){}
    };

class TestSuite_FlexArray : public TestSuite
{
    public:
        explicit TestSuite_FlexArray(){}

        void load_tests();

        testdoc_t get_title()
        {
            return "PawLIB: FlexArray Tests";
        }

        ~TestSuite_FlexArray(){}
};
};
#endif // FLEX_ARRAY_TEST_HPP
