#include "pawlib/flex_array_tests.hpp"

const int ONETHOU = 1000;
const int HUNTHOU = 100000;
//const int tenmill = 10,000,000; // for stress testing
void TestSuite_FlexArray::load_tests()
{
    //Benchmark test section for "Push" function (flexarray vs. vector)
    //push at end
    register_test("P-tB1001", new TestFArray_Push(ONETHOU), true, new TestVector_Push(ONETHOU));
    register_test("P-tS1001", new TestFArray_Push(HUNTHOU), false);

    //Benchmark test section for "Shift" function (flexarray vs. vector)
    //push at front
    register_test("P-tB1002", new TestFArray_Shift(ONETHOU), true, new TestVector_Shift(ONETHOU));
    register_test("P-tS1002", new TestFArray_Shift(HUNTHOU), false);

    //Benchmark test section for "Insert" function (flexarray vs. vector)
    //insert at middle
    register_test("P-tB1003", new TestFArray_Insert(ONETHOU), true, new TestVector_Insert(ONETHOU));
    register_test("P-tS1003", new TestFArray_Insert(HUNTHOU), false);

    register_test("P-tB1004", new TestFArray_Yank(ONETHOU), true, new TestVector_Yank(ONETHOU));
    register_test("P-tS1004", new TestFArray_Yank(HUNTHOU), false);

    register_test("P-tB1005", new TestFArray_Unshift(ONETHOU), true, new TestVector_Unshift(ONETHOU));
    register_test("P-tS1005", new TestFArray_Unshift(HUNTHOU), false);

    register_test("P-tB1006", new TestFArray_Pop(ONETHOU), true, new TestVector_Pop(ONETHOU));
    register_test("P-tS1006", new TestFArray_Pop(HUNTHOU), false);

    register_test("P-tB1007", new TestFArray_Erase(ONETHOU), true, new TestVector_Erase(ONETHOU));
    register_test("P-tS1007", new TestFArray_Erase(HUNTHOU), false);

    register_test("P-tB1008", new TestFArray_Peek(), true, new TestVector_Peek());
}
