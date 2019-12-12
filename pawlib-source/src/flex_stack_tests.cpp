#include "pawlib/flex_stack_tests.hpp"
/*general layout for creating tests in the cpp file
    line 1: testmanager->register_test ("unique test name",
    line 2: new "function that is being tested",
    line 3: "title",
    line 4: "description");
*/

const int ONETHOU = 1000;
const int HUNTHOU = 100000;

void TestSuite_FlexStack::load_tests()
{
    register_test("P-tB1301", new TestFStack_Push(ONETHOU), true, new TestSStack_Push(ONETHOU));
    register_test("P-tS1301", new TestFStack_Push(HUNTHOU), false);

    register_test("P-tB1302", new TestFStack_Peek());

    register_test("P-tB1303", new TestFStack_Pop(ONETHOU), true, new TestSStack_Pop(ONETHOU));
    register_test("P-tS1303", new TestFStack_Pop(HUNTHOU), false);
}
