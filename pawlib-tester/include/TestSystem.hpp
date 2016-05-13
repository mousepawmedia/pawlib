#ifndef TESTSYSTEM_HPP
#define TESTSYSTEM_HPP

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include <iochannel.hpp>
#include <goldilocks.hpp>

#include <pawsort_tests.hpp>
#include <onestring_tests.hpp>

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;
using namespace pawlib;

class TestSystem
{
    public:
        TestSystem();
        ~TestSystem();

        TestManager* testmanager;
    protected:
    private:
};

#endif // TESTSYSTEM_HPP
