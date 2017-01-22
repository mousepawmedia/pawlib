#ifndef TESTSYSTEM_HPP
#define TESTSYSTEM_HPP

#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include "pawlib/goldilocks.hpp"
#include "pawlib/iochannel.hpp"

#include "pawlib/core_types_tests.hpp"
#include "pawlib/flex_array_tests.hpp"
#include "pawlib/flex_bit_tests.hpp"
//TODO: #include "pawlib/flex_map_tests.hpp"
#include "pawlib/flex_queue_tests.hpp"
#include "pawlib/flex_stack_tests.hpp"
#include "pawlib/pawsort_tests.hpp"
#include "pawlib/onestring_tests.hpp"
#include "pawlib/pool_tests.hpp"

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
