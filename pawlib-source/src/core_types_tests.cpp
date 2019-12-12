#include "pawlib/core_types_tests.hpp"

void TestSuite_CoreTypes::load_tests()
{
    register_test("P-tB0101",
        new TestTrilean_CompareConst(TestTrilean_CompareConst::Scenario::FALSE));
    register_test("P-tB0102",
        new TestTrilean_CompareConst(TestTrilean_CompareConst::Scenario::MAYBE));
    register_test("P-tB0103",
        new TestTrilean_CompareConst(TestTrilean_CompareConst::Scenario::TRUE));

    register_test("P-tB0104",
        new TestTrilean_CompareTril(TestTrilean_CompareTril::Scenario::FALSE));
    register_test("P-tB0105",
        new TestTrilean_CompareTril(TestTrilean_CompareTril::Scenario::MAYBE));
    register_test("P-tB0106",
        new TestTrilean_CompareTril(TestTrilean_CompareTril::Scenario::TRUE));

    register_test("P-tB0107",
        new TestTrilean_Unary(TestTrilean_Unary::Scenario::FALSE));
    register_test("P-tB0108",
        new TestTrilean_Unary(TestTrilean_Unary::Scenario::MAYBE));
    register_test("P-tB0109",
        new TestTrilean_Unary(TestTrilean_Unary::Scenario::TRUE));

    register_test("P-tB010A", new TestTrilean_AssignConst);
    register_test("P-tB010B", new TestTrilean_AssignTril);
    register_test("P-tB010C", new TestTrilean_Certain);
    register_test("P-tB010D", new TestTrilean_NoNonsense);
}
