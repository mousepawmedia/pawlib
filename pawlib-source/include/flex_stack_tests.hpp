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
