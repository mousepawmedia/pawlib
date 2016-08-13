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

#ifndef FLEX_ARRAY_TEXT_HPP
#define FLEX_ARRAY_TEXT_HPP

#include <vector>

#include <flex_array.hpp>
#include <goldilocks.hpp>

namespace pawlib
{
    class TestVector_Push : public Test
    {
        public:
            TestVector_Push(){}

            bool run()
            {
                std::vector<int> vec;
                for(unsigned int i=0; i<1000; ++i)
                {
                    vec.push_back(i);
                }
                return true;
            }

            ~TestVector_Push(){}
    };

    class TestFlex_Push : public Test
    {
        public:
            TestFlex_Push(){}

            bool run()
            {
                pawlib::FlexArray<int> flex;
                for(int i=0; i<1000; ++i)
                {
                    if(flex.push(i) == false)
                    {
                    return false;
                    }
                }
                return true;
            }

            ~TestFlex_Push(){}
    };
 //NOTE: What would happen if we do flex insert at 0 instead of shift at 0?
    class TestVector_Shift : public Test
    {
        public:
            TestVector_Shift(){}

            bool run()
            {
                std::vector<int> vec;
                //vec.push_back(0);
                //vec.push_back(1);

                for(int i=0; i<1000; ++i)
                {
                    vec.insert(vec.begin(), i);
                }
                return true;
            }

            ~TestVector_Shift(){}
    };

    class TestFlex_Shift : public Test
    {
        public:
            TestFlex_Shift(){}

            bool run()
            {
                pawlib::FlexArray<int> flex;
                //flex.push(0);
                //flex.push(1);

                for(int i=0; i<1000; ++i)
                {
                    flex.shift(i);
                }
                return true;
            }

            ~TestFlex_Shift(){}
    };

     class TestFlex_ShiftAlt : public Test
    {
        public:
            TestFlex_ShiftAlt(){}

            bool run()
            {
                pawlib::FlexArray<int> flex;
                //flex.push(0);
                //flex.push(1);

                for(int i=0; i<1000; ++i)
                {
                    if(!flex.insert(i,0))
                    {
                        return false;
                    }
                }
                return true;
            }

            ~TestFlex_ShiftAlt(){}
    };
    class TestVector_Insert : public Test
    {
        public:
            TestVector_Insert(){}

            bool run()
            {
                std::vector<int> vec;

                /* We initially push two values, to make the
                 * math calculating the insert index a bit safer.*/
                vec.push_back(0);
                vec.push_back(1);

                for(int i=1; i<1000; ++i)
                {
                    unsigned int j = vec.size()/2;
                    vec.insert(vec.begin()+j, i);
                }
                return true;
            }

            ~TestVector_Insert(){}
    };

    class TestFlex_Insert : public Test
    {
        public:
            TestFlex_Insert(){}

            bool run()
            {
                pawlib::FlexArray<int> flex;

                /* We initially push two values, to make the
                 * math calculating the insert index a bit safer.*/
                flex.push(0);
                flex.push(1);

                for(int i=1; i<1000; ++i)
                {
                    int j = flex.getSize()/2;
                    flex.insert(j, i);
                }
                return true;
            }

            ~TestFlex_Insert(){}
    };

    class TestSuite_FlexArray : public TestSuite
    {
        public:
            static void load_tests(TestManager*);
        protected:

        private:
    };
}

#endif // FLEX_ARRAY_TEXT_HPP
