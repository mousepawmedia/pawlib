#include "TestSystem.hpp"

TestSystem::TestSystem()
{
    // Initialize a new Goldilocks testmanager.
    testmanager = new TestManager;

    /* We are loading suites directly right now. Eventually, this will be
     * on-demand instead of hardcoded, but that requires a few more changes.*/
    pawlib::TestSuite_Pawsort::load_tests(testmanager);
    pawlib::TestSuite_Pawstring::load_tests(testmanager);
}

TestSystem::~TestSystem()
{
    delete testmanager;
}

/*
    bool showStats = true;
    testmanager->run_compare("StdSort_SORTED", "PawSort_SORTED", 100, showStats);
    testmanager->run_compare("StdSort_REVERSED", "PawSort_REVERSED", 100, showStats);
    testmanager->run_compare("StdSort_NEARLY_2", "PawSort_NEARLY_2", 100, showStats);
    testmanager->run_compare("StdSort_NEARLY_5", "PawSort_NEARLY_5", 100, showStats);
    testmanager->run_compare("StdSort_FEW_UNIQUE", "PawSort_FEW_UNIQUE", 100, showStats);
    testmanager->run_compare("StdSort_BLACK_SHEEP", "PawSort_BLACK_SHEEP", 100, showStats);
    testmanager->run_compare("StdSort_DOUBLE_CLIMB", "PawSort_DOUBLE_CLIMB", 100, showStats);
    testmanager->run_compare("StdSort_DOUBLE_DROP", "PawSort_DOUBLE_DROP", 100, showStats);
    testmanager->run_compare("StdSort_STAIRS", "PawSort_STAIRS", 100, showStats);
    testmanager->run_compare("StdSort_MOUNTAIN", "PawSort_MOUNTAIN", 100, showStats);
    testmanager->run_compare("StdSort_DOUBLE_MOUNTAIN", "PawSort_DOUBLE_MOUNTAIN", 100, showStats);
    testmanager->run_compare("StdSort_EVEREST", "PawSort_EVEREST", 100, showStats);
    testmanager->run_compare("StdSort_CLIFF", "PawSort_CLIFF", 100, showStats);
    testmanager->run_compare("StdSort_SPIKE", "PawSort_SPIKE", 100, showStats);
    testmanager->run_compare("StdSort_CHICKEN", "PawSort_CHICKEN", 100, showStats);
    testmanager->run_compare("StdSort_NIGHTMARE", "PawSort_NIGHTMARE", 100, showStats);

    testmanager->run_compare("StdString Equal No Unicode", "PawString Equal No Unicode", 100);
    testmanager->run_compare("StdString Equal Some Unicode", "PawString Equal Some Unicode", 100);
    testmanager->run_compare("StdString Equal All Unicode", "PawString Equal All Unicode", 100);
    testmanager->run_compare("StdString Not Equal 1st Char", "PawString Not Equal 1st Char", 100);
    testmanager->run_compare("StdString Not Equal Middle", "PawString Not Equal Middle", 100);
    testmanager->run_compare("StdString Not Equal Last", "PawString Not Equal Last", 100);
*/
