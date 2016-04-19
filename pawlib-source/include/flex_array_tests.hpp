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
                for(int i=0; i<1000; ++i)
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
                    flex.push(i);
                }
                return true;
            }

            ~TestFlex_Push(){}
    };

    class TestVector_Shift : public Test
    {
        public:
            TestVector_Shift(){}

            bool run()
            {
                std::vector<int> vec;
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
                for(int i=0; i<1000; ++i)
                {
                    flex.shift(i);
                }
                return true;
            }

            ~TestFlex_Shift(){}
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
