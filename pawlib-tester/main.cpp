#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>

//#include "pawlib/core_types.hpp"
//#include "pawlib/flex_array.hpp"
#include "pawlib/goldilocks.hpp"
#include "pawlib/goldilocks_shell.hpp"
#include "pawlib/iochannel.hpp"
//#include "pawlib/onestringbase.hpp"
//#include "pawlib/onestring.hpp"
//#include "pawlib/pool.hpp"
//#include "pawlib/quickstring.hpp"
//#include "pawlib/onechar.hpp"
//#include "pawlib/pawsort.hpp"
//#include "pawlib/stdutils.hpp"

#include "pawlib/core_types_tests.hpp"
#include "pawlib/flex_array_tests.hpp"
#include "pawlib/flex_bit_tests.hpp"
#include "pawlib/flex_queue_tests.hpp"
#include "pawlib/flex_stack_tests.hpp"
#include "pawlib/pawsort_tests.hpp"
#include "pawlib/onestring_tests.hpp"
#include "pawlib/pool_tests.hpp"

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;
using namespace pawlib;
using namespace std;

void print(std::string msg)
{
    std::cout << msg;
}

int main(int argc, char* argv[])
{
    //Set up signal handling.
    //ioc.signal_all.add(&print);
    ioc.configure_echo(echo_cout);

    TestCatalog* sys = new TestCatalog;
    sys->register_suite<TestSuite_CoreTypes>("P-sB01");
    sys->register_suite<TestSuite_FlexArray>("P-sB10");
    sys->register_suite<TestSuite_FlexQueue>("P-sB12");
    sys->register_suite<TestSuite_FlexStack>("P-sB13");
    sys->register_suite<TestSuite_FlexBit>("P-sB15");
    sys->register_suite<TestSuite_Pool>("P-sB16");
    sys->register_suite<TestSuite_Onestring>("P-sB30");
    sys->register_suite<TestSuite_Pawsort>("P-sB40");

    (void) sys;
    (void) argc;
    (void) argv;

    // If we got command-line arguments.
    if(argc > 1)
    {
        return GoldilocksShell::command(sys, static_cast<unsigned int>(argc), argv);
    }
    else
    {
        ioc << ta_bold << fg_blue << "===== PawLIB Tester =====\n" << io_end;

        // Custom test code goes here.

        // Shift control to the interactive console.
        GoldilocksShell::interactive(sys);
    }

    delete sys;
    sys = 0;

    return 0;
}