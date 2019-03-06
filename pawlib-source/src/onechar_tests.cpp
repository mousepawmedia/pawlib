#include "pawlib/onechar_tests.hpp"

namespace pawlib
{
    void TestSuite_OneChar::load_tests()
    {
        register_test("P-tB4101", new TestOneChar_EvaluateLength());
        register_test("P-tB4102", new TestOneChar_CStr());
        register_test("P-tB4103a", new TestOneChar_Assign(TestOneChar::CHAR));
        register_test("P-tB4103b", new TestOneChar_Assign(TestOneChar::CSTR));
        register_test("P-tB4103c", new TestOneChar_Assign(TestOneChar::STRING));
        register_test("P-tB4103d", new TestOneChar_Assign(TestOneChar::ONECHAR));
        register_test("P-tB4104a", new TestOneChar_Equals(TestOneChar::CHAR));
        register_test("P-tB4104b", new TestOneChar_Equals(TestOneChar::CSTR));
        register_test("P-tB4104c", new TestOneChar_Equals(TestOneChar::STRING));
        register_test("P-tB4104d", new TestOneChar_Equals(TestOneChar::ONECHAR));
        register_test("P-tB4105a", new TestOneChar_NotEquals(TestOneChar::CHAR));
        register_test("P-tB4105b", new TestOneChar_NotEquals(TestOneChar::CSTR));
        register_test("P-tB4105c", new TestOneChar_NotEquals(TestOneChar::STRING));
        register_test("P-tB4105d", new TestOneChar_NotEquals(TestOneChar::ONECHAR));
    }

}
