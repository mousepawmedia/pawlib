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

        register_test("P-tB4105a", new TestOneChar_OpEquals(TestOneChar::CHAR));
        register_test("P-tB4105b", new TestOneChar_OpEquals(TestOneChar::CSTR));
        register_test("P-tB4105c", new TestOneChar_OpEquals(TestOneChar::STRING));
        register_test("P-tB4105d", new TestOneChar_OpEquals(TestOneChar::ONECHAR));

        register_test("P-tB4106a", new TestOneChar_OpNotEquals(TestOneChar::CHAR));
        register_test("P-tB4106b", new TestOneChar_OpNotEquals(TestOneChar::CSTR));
        register_test("P-tB4106c", new TestOneChar_OpNotEquals(TestOneChar::STRING));
        register_test("P-tB4106d", new TestOneChar_OpNotEquals(TestOneChar::ONECHAR));

        register_test("P-tB4107a", new TestOneChar_Compare(TestOneChar::CHAR));
        register_test("P-tB4107b", new TestOneChar_Compare(TestOneChar::CSTR));
        register_test("P-tB4107c", new TestOneChar_Compare(TestOneChar::STRING));
        register_test("P-tB4107d", new TestOneChar_Compare(TestOneChar::ONECHAR));

        register_test("P-tB4108a", new TestOneChar_OpLess(TestOneChar::CHAR));
        register_test("P-tB4108b", new TestOneChar_OpLess(TestOneChar::CSTR));
        register_test("P-tB4108c", new TestOneChar_OpLess(TestOneChar::STRING));
        register_test("P-tB4108d", new TestOneChar_OpLess(TestOneChar::ONECHAR));

        register_test("P-tB4109a", new TestOneChar_OpLessEqual(TestOneChar::CHAR));
        register_test("P-tB4109b", new TestOneChar_OpLessEqual(TestOneChar::CSTR));
        register_test("P-tB4109c", new TestOneChar_OpLessEqual(TestOneChar::STRING));
        register_test("P-tB4109d", new TestOneChar_OpLessEqual(TestOneChar::ONECHAR));

        register_test("P-tB4110a", new TestOneChar_OpGreater(TestOneChar::CHAR));
        register_test("P-tB4110b", new TestOneChar_OpGreater(TestOneChar::CSTR));
        register_test("P-tB4110c", new TestOneChar_OpGreater(TestOneChar::STRING));
        register_test("P-tB4110d", new TestOneChar_OpGreater(TestOneChar::ONECHAR));

        register_test("P-tB4111a", new TestOneChar_OpGreaterEqual(TestOneChar::CHAR));
        register_test("P-tB4111b", new TestOneChar_OpGreaterEqual(TestOneChar::CSTR));
        register_test("P-tB4111c", new TestOneChar_OpGreaterEqual(TestOneChar::STRING));
        register_test("P-tB4111d", new TestOneChar_OpGreaterEqual(TestOneChar::ONECHAR));
    }

}
