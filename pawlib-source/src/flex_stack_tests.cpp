#include "flex_stack_tests.hpp"
/*general layout for creating tests in the cpp file
    line 1: testmanager->register_test ("unique test name",
    line 2: new "function that is being tested",
    line 3: "title",
    line 4: "description");
*/
namespace pawlib
{
    const int onethou = 1000;
    const int hunthou = 100000;

    void TestSuite_FlexStack::load_tests()
    {
        register_test("P-tB1301", new TestFStack_Push(onethou));
        register_test("P-tS1301", new TestFStack_Push(hunthou), false);
        register_test("P-tB1301*", new TestSStack_Push(onethou), false);

        register_test("P-tB1302", new TestFStack_Peek());

        register_test("P-tB1303", new TestFStack_Pop(onethou));
        register_test("P-tS1303", new TestFStack_Pop(hunthou), false);
        register_test("P-tB1303*", new TestSStack_Pop(onethou), false);
    }
}
