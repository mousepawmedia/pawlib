#ifndef TESTSUITE_H
#define TESTSUITE_H

//TODO: Replace with FlexArray
#include <vector>

/** All tests are derived from this base
 * class.*/
class Test
{
    public:
        Test(){};
        virtual void pre(){}
        virtual void run()=0;
        virtual void post(){}
        virtual ~Test();
};

/** Al test suites are derived from this
 * base class.*/
class TestSuite
{
    public:
        TestSuite(){};
        void add(Test test){tests.push_back(test);}
        virtual void pre(){}
        virtual void run()=0;
        virtual void post(){}
        virtual ~TestSuite();
    protected:
        std::vector<Test> tests;
};

class TestManager
{
    public:
        TestManager();
        void register_test(Test, std::string);
        void register_suite(TestSuite, std::string);
        ~TestManager();
    protected:
        std::vector<Test> tests;
        std::vector<TestSuite> suites;
};

#endif // TESTSUITE_H
