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

#ifndef FLEX_QUEUE_TESTS_HPP
#define FLEX_QUEUE_TESTS_HPP

#include <queue>

#include <goldilocks.hpp>
#include <flex_queue.hpp>

namespace pawlib
{
    //Test Standard Queue's Push Function
    class TestSQueue_Push : public Test
    {
        private:
            unsigned int iters;

        public:
           explicit TestSQueue_Push(unsigned int iterations): iters(iterations){}

            //Test title
            testdoc_t get_title()
            {
                return "FlexQueue: Push " + stdutils::itos(iters, 10) + " Integers (std::queue)";
            }

            //Get documentation section
            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " integers to the back of a Queue (push).";
            }

            bool run()
            {
                //create and instance of standard queue
                std::queue<int> sq;

                for(unsigned int i=0; i<iters; ++i)
                {
                    //iters should equal 1000 in this case
                    //increment i from 0 until it equals iters
                    sq.push(i);
                }
                return true;
            }

            ~TestSQueue_Push(){}
    };
    //Test FlexQueue's Push function
    class TestFQueue_Push : public Test
    {
        private:
            unsigned int iters;

        public:

            //Flex Queue constructor for Push function with iterators
           explicit TestFQueue_Push(unsigned int iterations): iters(iterations){}

             //Test title
            testdoc_t get_title()
            {
                return "FlexQueue: Push " + stdutils::itos(iters, 10) + " Integers (flexqueue)";
            }
            //Test documentation
            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " integers at the back of a FlexQueue (push).";
            }

            bool run()
            {
                //create an instance of FlexQueue
                pawlib::FlexQueue<int> fq;

                //iters should equal 1000 in this case
                //increment i from 0 until it equals iters
                for(unsigned int i=0; i<iters; ++i)
                {
                    fq.push(i);
                }
                return true;
            }
            //destructor
            ~TestFQueue_Push(){}
    };
    //Test for peek() checks the first item after x elements are inserted. WIP
    class TestFQueue_Peek : public Test
    {
        private:
            pawlib::FlexQueue<int> fq;
        public:
            TestFQueue_Peek(){}

            testdoc_t get_title()
            {
                return "FlexQueue: Peek";
            }

            testdoc_t get_docs()
            {
                return "FlexQueue: Peek the first out of five integers placed into a FlexQueue";
            }
            //Set up for the test. Called only once, even if test is repeated multiple times.
            bool pre()
            {
                for(int i=1; i<5; ++i)
                {
                    fq.push(i);
                }
                return true;
            }

            //Run the test
            bool run()
            {
                int i = fq.peek();
                return (i==1);
            }

            ~TestFQueue_Peek(){}
    };// End TestFqueue_Peek

    //TestSqueue_Pop Function with unsigned ints
    class TestSQueue_Pop : public Test
    {
        private:
            //left declaration in private class to avoid doing so in both janitor() and run()
            std::queue<unsigned int> sq;
            unsigned int iters;

        // TestSQueue_Pop Constructor with iterators
        public:
            explicit TestSQueue_Pop(unsigned int iterations): iters(iterations){}

             //Test title
            testdoc_t get_title()
            {
                return "FlexQueue: Pop " + stdutils::itos(iters, 10) + " Integers (std::queue)";
            }
            //Test documentation
            testdoc_t get_docs()
            {
                return "Pop " + stdutils::itos(iters, 10) + " integers at the back of a standard Queue (pop).";
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
                    //push 1000 unsigned ints into std::queue
                    sq.push(i);
                }
                return true;
            }

            //Run the test
            bool run()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    sq.pop();
                    //had to leave the check statement out because
                    //std pop function is void function whereas flex is 'type'
                    //that can be anything
                    //not sure how to the check statement for std now..
                    /*if(sq.pop() != i )
                    {
                        return false;
                    }*/
                }
                return true;
            }
                    /*if(sq.pop() != i)
                    {
                    return false;
                    }
                    */
            ~TestSQueue_Pop(){}
    };

    //TestFQueue_Pop Function
    class TestFQueue_Pop : public Test
    {
        private:
            //left declaration in private class to avoid doing so in both janitor() and run()
            pawlib::FlexQueue<unsigned int> fq;
            unsigned int iters;

        public:
            //TestFQueue_Pop constructor with iterators
           explicit TestFQueue_Pop(unsigned int iterations): iters(iterations){}

             //Test title
            testdoc_t get_title()
            {
                return "FlexQueue: Pop " + stdutils::itos(iters, 10) + " Integers (Flexqueue)";
            }
            //Test documentation
            testdoc_t get_docs()
            {
                return "Pop " + stdutils::itos(iters, 10) + " integers at the back of a FlexQueue (pop).";
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
                    fq.push(i);
                }
                return true;
            }

            //Run the test
            bool run()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    if(fq.pop() != i)
                    {
                        return false;
                    }
                }
                return true;
            }

            ~TestFQueue_Pop(){}
    };

class TestSuite_FlexQueue : public TestSuite
    {
    public:
        explicit TestSuite_FlexQueue(){}

        void load_tests();

        testdoc_t get_title()
        {
            return "PawLIB: FlexQueue Tests";
        }

        ~TestSuite_FlexQueue(){}
    };

};
#endif // FLEX_QUEUE_TESTS_HPP_H
