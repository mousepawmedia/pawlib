#include "pawlib/onestring_tests.hpp"

namespace pawlib
{
    void TestSuite_OneString::load_tests()
    {
        register_test("P-tB4001a", new TestOneString_Equal(TestOneString::NO_UNICODE));
        register_test("P-tB4001b", new TestOneString_Equal(TestOneString::SOME_UNICODE));
        register_test("P-tB4001c", new TestOneString_Equal(TestOneString::JUST_UNICODE));

        register_test("P-tB4002a", new TestOneString_EqualFail(TestOneString::NO_UNICODE));
        register_test("P-tB4002b", new TestOneString_EqualFail(TestOneString::SOME_UNICODE));
        register_test("P-tB4002c", new TestOneString_EqualFail(TestOneString::JUST_UNICODE));

        register_test("P-tB4003a", new TestOneString_NotEqual(TestOneString::NO_UNICODE));
        register_test("P-tB4003b", new TestOneString_NotEqual(TestOneString::SOME_UNICODE));
        register_test("P-tB4003c", new TestOneString_NotEqual(TestOneString::JUST_UNICODE));

        register_test("P-tB4004a", new TestOneString_NotEqualFail(TestOneString::NO_UNICODE));
        register_test("P-tB4004b", new TestOneString_NotEqualFail(TestOneString::SOME_UNICODE));
        register_test("P-tB4004c", new TestOneString_NotEqualFail(TestOneString::JUST_UNICODE));

        register_test("P-tB4005a", new TestOneString_Equals(TestOneString::NO_UNICODE));
        register_test("P-tB4005b", new TestOneString_Equals(TestOneString::SOME_UNICODE));
        register_test("P-tB4005c", new TestOneString_Equals(TestOneString::JUST_UNICODE));

        register_test("P-tB4006a", new TestOneString_EqualsFail(TestOneString::NO_UNICODE));
        register_test("P-tB4006b", new TestOneString_EqualsFail(TestOneString::SOME_UNICODE));
        register_test("P-tB4006c", new TestOneString_EqualsFail(TestOneString::JUST_UNICODE));

        register_test("P-tB4007", new TestOneString_Append());
        register_test("P-tB4008", new TestOneString_PopBack());
        register_test("P-tB4009", new TestOneString_Length());
        register_test("P-tB4010", new TestOneString_Empty());
        register_test("P-tB4011", new TestOneString_EmptyFail());
        register_test("P-tB4012", new TestOneString_Insert());
        register_test("P-tB4013", new TestOneString_Clear());
        register_test("P-tB4014", new TestOneString_Swap());
        register_test("P-tB4015", new TestOneString_Substr());
        register_test("P-tB4016", new TestOneString_At());
        register_test("P-tB4017", new TestOneString_ForceResize());

        //TODO: Comparative tests against std::string
    }
}
