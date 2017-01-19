#include "TestSystem.hpp"

TestSystem::TestSystem()
{
    // Initialize a new Goldilocks testmanager.
    testmanager = new TestManager;

    /* We merely need to register the suites with the system.
     * Loading their tests is now interactively on-demand. */
    testmanager->register_suite("P-sB01", new TestSuite_CoreTypes());
    testmanager->register_suite("P-sB10", new TestSuite_FlexArray());
    testmanager->register_suite("P-sB12", new TestSuite_FlexQueue());
    testmanager->register_suite("P-sB13", new TestSuite_FlexStack());
    testmanager->register_suite("P-sB16", new TestSuite_Pool());
    testmanager->register_suite("P-sB40", new TestSuite_Onestring());
    testmanager->register_suite("P-sB30", new TestSuite_Pawsort());
    testmanager->register_suite("P-sB15", new TestSuite_FlexBit());
}

TestSystem::~TestSystem()
{
    delete testmanager;
}
