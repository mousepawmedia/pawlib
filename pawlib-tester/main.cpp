#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "pawlib/goldilocks_shell.hpp"
#include "pawlib/iochannel.hpp"

// Include tests.
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

int main(int argc, char* argv[])
{
    //Set up signal handling.
    ioc.configure_echo(echo_cout);

    TestCatalog* catalog = new TestCatalog;
    catalog->register_suite<TestSuite_CoreTypes>("P-sB01");
    catalog->register_suite<TestSuite_FlexArray>("P-sB10");
    catalog->register_suite<TestSuite_FlexQueue>("P-sB12");
    catalog->register_suite<TestSuite_FlexStack>("P-sB13");
    catalog->register_suite<TestSuite_FlexBit>("P-sB15");
    catalog->register_suite<TestSuite_Pool>("P-sB16");
    catalog->register_suite<TestSuite_Onestring>("P-sB30");
    catalog->register_suite<TestSuite_Pawsort>("P-sB40");

    (void) catalog;
    (void) argc;
    (void) argv;

    // If we got command-line arguments.
    if(argc > 1)
    {
        return GoldilocksShell::command(catalog, static_cast<unsigned int>(argc), argv);
    }
    else
    {
        ioc << ta_bold << fg_blue << "===== PawLIB Tester =====\n" << io_end;

        // Custom test code goes here.

        // Shift control to the interactive console.
        GoldilocksShell::interactive(catalog);
    }

    // Delete our test catalog.
    delete catalog;
    catalog = 0;

    return 0;
}