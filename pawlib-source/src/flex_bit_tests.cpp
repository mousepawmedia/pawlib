#include "pawlib/flex_bit_tests.hpp"

namespace pawlib
{
    const int TENMILL = 10000000;
    const int ONEHUND = 100;
    void TestSuite_FlexBit::load_tests()
    {
        if (testmanager == nullptr)
        {
            return;
        }

        register_test("P-tB152",new TestFlexBit_Push(ONEHUND));
        register_test("P-tS152", new TestFlexBit_Push(TENMILL), false);

        register_test("P-tB153", new TestFlexBit_Peek());

        register_test("P-tB154", new TestFlexBit_Poll(ONEHUND));
        register_test("P-tS154", new TestFlexBit_Poll(TENMILL), false);

        register_test("P-tB151",new TestFlexBit_ToString(ONEHUND));
        register_test("P-tS151",new TestFlexBit_ToString(TENMILL), false);

    }

}
