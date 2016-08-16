#include "flex_array_tests.hpp"

namespace pawlib
{
    void TestSuite_FlexArray::load_tests()
    {
        register_test("P-tB1001", new TestFlex_Push);
        register_test("P-tB1001*", new TestVector_Push, false);

        register_test("P-tB1002", new TestFlex_Shift);
        register_test("P-tB1002*", new TestVector_Shift, false);

        register_test("P-tB1003", new TestFlex_ShiftAlt);

        register_test("P-tB1004", new TestFlex_Insert);
        register_test("P-tB1004*", new TestVector_Insert, false);
    }

}
