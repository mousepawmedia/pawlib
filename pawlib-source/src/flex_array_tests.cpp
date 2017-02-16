#include "pawlib/flex_array_tests.hpp"

namespace pawlib
{
    const int onethou = 1000;
    const int hunthou = 100000;
    //const int tenmill = 10,000,000; // for stress testing
    void TestSuite_FlexArray::load_tests()
    {
        //Benchmark test section for "Push" function (flexarray vs. vector)
        //push at end
        register_test("P-tB1001", new TestFArray_Push(onethou));
        register_test("P-tS1001", new TestFArray_Push(hunthou), false);
        register_test("P-tB1001*", new TestVector_Push(onethou), false);

        //Benchmark test section for "Shift" function (flexarray vs. vector)
        //push at front
        register_test("P-tB1002", new TestFArray_Shift(onethou));
        register_test("P-tS1002", new TestFArray_Shift(hunthou), false);
        register_test("P-tB1002*", new TestVector_Shift(onethou), false);

        //Benchmark test section for "Insert" function (flexarray vs. vector)
        //insert at middle
        register_test("P-tB1003", new TestFArray_Insert(onethou));
        register_test("P-tS1003", new TestFArray_Insert(hunthou), false);
        register_test("P-tB1003*", new TestVector_Insert(onethou), false);

        register_test("P-tB1004", new TestFArray_Yank(onethou));
        register_test("P-tS1004", new TestFArray_Yank(hunthou), false);
        register_test("P-tB1004*", new TestVector_Yank(onethou), false);

        register_test("P-tB1005", new TestFArray_Unshift(onethou));
        register_test("P-tS1005", new TestFArray_Unshift(hunthou), false);
        register_test("P-tB1005*", new TestVector_Unshift(onethou), false);

        register_test("P-tB1006", new TestFArray_Pop(onethou));
        register_test("P-tS1006", new TestFArray_Pop(hunthou), false);
        register_test("P-tB1006*", new TestVector_Pop(onethou), false);

        register_test("P-tB1007", new TestFArray_Erase(onethou));
        register_test("P-tS1007", new TestFArray_Erase(hunthou), false);
        register_test("P-tB1007*", new TestVector_Erase(onethou), false);
    }

}
