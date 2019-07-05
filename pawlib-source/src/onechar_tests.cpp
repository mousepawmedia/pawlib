#include "pawlib/onechar_tests.hpp"

namespace pawlib
{
    void TestSuite_Onechar::load_tests()
    {
        register_test("P-tB4101", new TestOnechar_EvaluateLength());

        register_test("P-tB4102", new TestOnechar_CStr());

        register_test("P-tB4103a", new TestOnechar_Assign(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4103b", new TestOnechar_Assign(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4103c", new TestOnechar_Assign(TestOnechar::TestCharType::STRING));
        register_test("P-tB4103d", new TestOnechar_Assign(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4104a", new TestOnechar_Equals(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4104b", new TestOnechar_Equals(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4104c", new TestOnechar_Equals(TestOnechar::TestCharType::STRING));
        register_test("P-tB4104d", new TestOnechar_Equals(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4105a", new TestOnechar_OpEquals(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4105b", new TestOnechar_OpEquals(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4105c", new TestOnechar_OpEquals(TestOnechar::TestCharType::STRING));
        register_test("P-tB4105d", new TestOnechar_OpEquals(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4106a", new TestOnechar_OpNotEquals(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4106b", new TestOnechar_OpNotEquals(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4106c", new TestOnechar_OpNotEquals(TestOnechar::TestCharType::STRING));
        register_test("P-tB4106d", new TestOnechar_OpNotEquals(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4107a", new TestOnechar_Compare(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4107b", new TestOnechar_Compare(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4107c", new TestOnechar_Compare(TestOnechar::TestCharType::STRING));
        register_test("P-tB4107d", new TestOnechar_Compare(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4108a", new TestOnechar_OpLess(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4108b", new TestOnechar_OpLess(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4108c", new TestOnechar_OpLess(TestOnechar::TestCharType::STRING));
        register_test("P-tB4108d", new TestOnechar_OpLess(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4109a", new TestOnechar_OpLessEqual(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4109b", new TestOnechar_OpLessEqual(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4109c", new TestOnechar_OpLessEqual(TestOnechar::TestCharType::STRING));
        register_test("P-tB4109d", new TestOnechar_OpLessEqual(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4110a", new TestOnechar_OpGreater(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4110b", new TestOnechar_OpGreater(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4110c", new TestOnechar_OpGreater(TestOnechar::TestCharType::STRING));
        register_test("P-tB4110d", new TestOnechar_OpGreater(TestOnechar::TestCharType::ONECHAR));

        register_test("P-tB4111a", new TestOnechar_OpGreaterEqual(TestOnechar::TestCharType::CHAR));
        register_test("P-tB4111b", new TestOnechar_OpGreaterEqual(TestOnechar::TestCharType::CSTR));
        register_test("P-tB4111c", new TestOnechar_OpGreaterEqual(TestOnechar::TestCharType::STRING));
        register_test("P-tB4111d", new TestOnechar_OpGreaterEqual(TestOnechar::TestCharType::ONECHAR));
    }

}
