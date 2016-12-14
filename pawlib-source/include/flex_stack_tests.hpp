/** Tests for FlexStack[PawLIB]
  * Version: 1.0
  *
  * Author(s): Jonathan Theodore
  */

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

#ifndef FLEX_STACK_TESTS_HPP
#define FLEX_STACK_TESTS_HPP

#include <stack>
#include <goldilocks.hpp>

#include <flex_stack.hpp>
//SStack classes test the standard library version of Stack
//FStack classes test the pawlib versions of FlexStack
namespace pawlib
{
    class TestSStack_Push : public Test
    {
        private:
            //may move declaration to public
            std::stack<unsigned int> stk;

            unsigned int iters;

        public:
            //TestSStack_PushU with iterators
            explicit TestSStack_Push(unsigned int iterations): iters(iterations){}

            //Test title
            testdoc_t get_title()
            {
                return "FlexStack: Push " + stdutils::itos(iters, 10) + " Integers (std::vector)";
            }
            //get documentation section
            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " integers on top of standard stack (push).";
            }

            //Run the test
            bool run()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    //iters should equal 1000 in this case
                    //increment i from 0
                    stk.push(i);
                }
                return true;
            }
            /*try
            {

            }
            catch
            {

            }
            */
            ~TestSStack_Push(){}
    };

    class TestFStack_Push : public Test
    {
        private:
            //may move to public
            pawlib::FlexStack<unsigned int> fstk;
            unsigned int iters;
        //FlexStack constructor with iterators
        public:
            explicit TestFStack_Push(unsigned int iterations): iters(iterations){}

            //Test title
            testdoc_t get_title()
            {
                return "FlexStack: Push " + stdutils::itos(iters, 10) + " integers on top of a flexstack (push)";
            }
            //Test documentation
            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " Integers (flexstack)";
            }
            // Run the test
            bool run()
            {

                for(unsigned int i=0; i<iters; ++i)
                {
                    fstk.push(i);
                }
                return true;
            }

            ~TestFStack_Push(){}
    };

    class TestSStack_Pop : public Test
    {
        private:
            std::stack<unsigned int> stk;
            unsigned int iters;
        public:
            explicit TestSStack_Pop(unsigned int iterations): iters(iterations){}

            // Test title
            testdoc_t get_title()
            {
                return"FlexStack: Pop " + stdutils::itos(iters, 10) + " integers from a std::stack.";
            }
            // test documentation
            testdoc_t get_docs()
            {
                return "Pop " + stdutils::itos(iters, 10) + " integers from a flexstack.";
            }

            bool pre()
            {
                return janitor();
            }

            // push 100 integers to be deleted
            bool janitor()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    stk.push(i);
                }
                return true;
            }
            // run deletion test
            bool run()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    stk.pop();
                }
                return true;
            }
            //destructor
            ~TestSStack_Pop(){}
    };

    class TestFStack_Pop : public Test
    {
        private:
            pawlib::FlexStack<unsigned int> fstk;
            unsigned int iters;

        public:
            explicit TestFStack_Pop(unsigned int iterations): iters(iterations){}
            // Test title
            testdoc_t get_title()
            {
                return"FlexStack: Pop " + stdutils::itos(iters, 10) + " integers from a Flexstack (Pop).";
            }
            // test documentation
            testdoc_t get_docs()
            {
                return "Pop " + stdutils::itos(iters, 10) + " integers from a flexstack";
            }

            bool pre()
            {
                return janitor();
            }

            bool janitor()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    fstk.push(i);
                }
                return true;
            }
            bool run()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    fstk.pop();
                }
                return true;
            }

            ~TestFStack_Pop(){}
    };

    class TestSuite_FlexStack : public TestSuite
    {
        public:
            explicit TestSuite_FlexStack(){}

            void load_tests();

            testdoc_t get_title()
            {
                return "Pawlib: FlexArray Tests";
            }

        private:
    };
}
#endif // FLEX_STACK_TESTS_H
