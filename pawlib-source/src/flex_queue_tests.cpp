#include "pawlib/flex_queue_tests.hpp"

const int ONETHOU = 1000;
const int HUNTHOU = 100000;

void TestSuite_FlexQueue::load_tests()
{
    register_test("P-tB1201", new TestFQueue_Push(ONETHOU), true,  new TestSQueue_Push(ONETHOU));
    register_test("P-tS1201", new TestFQueue_Push(HUNTHOU), false);

    register_test("P-tB1202", new TestFQueue_Peek());

    register_test("P-tB1203", new TestFQueue_Pop(ONETHOU), true, new TestSQueue_Pop(ONETHOU));
    register_test("P-tS1203", new TestFQueue_Pop(HUNTHOU), false);
}
