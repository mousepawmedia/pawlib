#include "pawlib/flex_queue_tests.hpp"

namespace pawlib
{
    const int onethou = 1000;
    const int hunthou = 100000;

    void TestSuite_FlexQueue::load_tests()
    {
        register_test("P-tB1201", new TestFQueue_Push(onethou));
        register_test("P-tS1201", new TestFQueue_Push(hunthou), false);
        register_test("P-tB1201*", new TestSQueue_Push(onethou), false);

        register_test("P-tB1202", new TestFQueue_Peek());

        register_test("P-tB1203", new TestFQueue_Pop(onethou));
        register_test("P-tS1203", new TestFQueue_Pop(hunthou), false);
        register_test("P-tB1203*", new TestSQueue_Pop(onethou), false);
    }
}
