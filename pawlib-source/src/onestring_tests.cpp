#include "pawlib/onestring_tests.hpp"

namespace pawlib
{
    void TestSuite_OneString::load_tests()
    {
        register_test("P-tB4001a", new TestOneString_Assign(TestOneString::CHAR));
        register_test("P-tB4001b", new TestOneString_Assign(TestOneString::OCHAR_ASCII));
        register_test("P-tB4001c", new TestOneString_Assign(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4001d", new TestOneString_Assign(TestOneString::CSTR_ASCII));
        register_test("P-tB4001e", new TestOneString_Assign(TestOneString::CSTR_UNICODE));
        register_test("P-tB4001f", new TestOneString_Assign(TestOneString::STR_ASCII));
        register_test("P-tB4001g", new TestOneString_Assign(TestOneString::STR_UNICODE));
        register_test("P-tB4001h", new TestOneString_Assign(TestOneString::OSTR_ASCII));
        register_test("P-tB4001i", new TestOneString_Assign(TestOneString::OSTR_UNICODE));

        register_test("P-tB4002a", new TestOneString_Equals(TestOneString::CHAR));
        register_test("P-tB4002b", new TestOneString_Equals(TestOneString::OCHAR_ASCII));
        register_test("P-tB4002c", new TestOneString_Equals(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4002d", new TestOneString_Equals(TestOneString::CSTR_ASCII));
        register_test("P-tB4002e", new TestOneString_Equals(TestOneString::CSTR_UNICODE));
        register_test("P-tB4002f", new TestOneString_Equals(TestOneString::STR_ASCII));
        register_test("P-tB4002g", new TestOneString_Equals(TestOneString::STR_UNICODE));
        register_test("P-tB4002h", new TestOneString_Equals(TestOneString::OSTR_ASCII));
        register_test("P-tB4002i", new TestOneString_Equals(TestOneString::OSTR_UNICODE));

        register_test("P-tB4003a", new TestOneString_OpEquals(TestOneString::CHAR));
        register_test("P-tB4003b", new TestOneString_OpEquals(TestOneString::OCHAR_ASCII));
        register_test("P-tB4003c", new TestOneString_OpEquals(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4003d", new TestOneString_OpEquals(TestOneString::CSTR_ASCII));
        register_test("P-tB4003e", new TestOneString_OpEquals(TestOneString::CSTR_UNICODE));
        register_test("P-tB4003f", new TestOneString_OpEquals(TestOneString::STR_ASCII));
        register_test("P-tB4003g", new TestOneString_OpEquals(TestOneString::STR_UNICODE));
        register_test("P-tB4003h", new TestOneString_OpEquals(TestOneString::OSTR_ASCII));
        register_test("P-tB4003i", new TestOneString_OpEquals(TestOneString::OSTR_UNICODE));

        register_test("P-tB4004a", new TestOneString_OpNotEquals(TestOneString::CHAR));
        register_test("P-tB4004b", new TestOneString_OpNotEquals(TestOneString::OCHAR_ASCII));
        register_test("P-tB4004c", new TestOneString_OpNotEquals(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4004d", new TestOneString_OpNotEquals(TestOneString::CSTR_ASCII));
        register_test("P-tB4004e", new TestOneString_OpNotEquals(TestOneString::CSTR_UNICODE));
        register_test("P-tB4004f", new TestOneString_OpNotEquals(TestOneString::STR_ASCII));
        register_test("P-tB4004g", new TestOneString_OpNotEquals(TestOneString::STR_UNICODE));
        register_test("P-tB4004h", new TestOneString_OpNotEquals(TestOneString::OSTR_ASCII));
        register_test("P-tB4004i", new TestOneString_OpNotEquals(TestOneString::OSTR_UNICODE));

        register_test("P-tB4005a", new TestOneString_Compare(TestOneString::CHAR));
        register_test("P-tB4005b", new TestOneString_Compare(TestOneString::OCHAR_ASCII));
        register_test("P-tB4005c", new TestOneString_Compare(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4005d", new TestOneString_Compare(TestOneString::CSTR_ASCII));
        register_test("P-tB4005e", new TestOneString_Compare(TestOneString::CSTR_UNICODE));
        register_test("P-tB4005f", new TestOneString_Compare(TestOneString::STR_ASCII));
        register_test("P-tB4005g", new TestOneString_Compare(TestOneString::STR_UNICODE));
        register_test("P-tB4005h", new TestOneString_Compare(TestOneString::OSTR_ASCII));
        register_test("P-tB4005i", new TestOneString_Compare(TestOneString::OSTR_UNICODE));

        register_test("P-tB4006a", new TestOneString_OpLess(TestOneString::CHAR));
        register_test("P-tB4006b", new TestOneString_OpLess(TestOneString::OCHAR_ASCII));
        register_test("P-tB4006c", new TestOneString_OpLess(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4006d", new TestOneString_OpLess(TestOneString::CSTR_ASCII));
        register_test("P-tB4006e", new TestOneString_OpLess(TestOneString::CSTR_UNICODE));
        register_test("P-tB4006f", new TestOneString_OpLess(TestOneString::STR_ASCII));
        register_test("P-tB4006g", new TestOneString_OpLess(TestOneString::STR_UNICODE));
        register_test("P-tB4006h", new TestOneString_OpLess(TestOneString::OSTR_ASCII));
        register_test("P-tB4006i", new TestOneString_OpLess(TestOneString::OSTR_UNICODE));

        register_test("P-tB4007a", new TestOneString_OpLessEqual(TestOneString::CHAR));
        register_test("P-tB4007b", new TestOneString_OpLessEqual(TestOneString::OCHAR_ASCII));
        register_test("P-tB4007c", new TestOneString_OpLessEqual(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4007d", new TestOneString_OpLessEqual(TestOneString::CSTR_ASCII));
        register_test("P-tB4007e", new TestOneString_OpLessEqual(TestOneString::CSTR_UNICODE));
        register_test("P-tB4007f", new TestOneString_OpLessEqual(TestOneString::STR_ASCII));
        register_test("P-tB4007g", new TestOneString_OpLessEqual(TestOneString::STR_UNICODE));
        register_test("P-tB4007h", new TestOneString_OpLessEqual(TestOneString::OSTR_ASCII));
        register_test("P-tB4007i", new TestOneString_OpLessEqual(TestOneString::OSTR_UNICODE));

        register_test("P-tB4008a", new TestOneString_OpGreater(TestOneString::CHAR));
        register_test("P-tB4008b", new TestOneString_OpGreater(TestOneString::OCHAR_ASCII));
        register_test("P-tB4008c", new TestOneString_OpGreater(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4008d", new TestOneString_OpGreater(TestOneString::CSTR_ASCII));
        register_test("P-tB4008e", new TestOneString_OpGreater(TestOneString::CSTR_UNICODE));
        register_test("P-tB4008f", new TestOneString_OpGreater(TestOneString::STR_ASCII));
        register_test("P-tB4008g", new TestOneString_OpGreater(TestOneString::STR_UNICODE));
        register_test("P-tB4008h", new TestOneString_OpGreater(TestOneString::OSTR_ASCII));
        register_test("P-tB4008i", new TestOneString_OpGreater(TestOneString::OSTR_UNICODE));

        register_test("P-tB4009a", new TestOneString_OpGreaterEqual(TestOneString::CHAR));
        register_test("P-tB4009b", new TestOneString_OpGreaterEqual(TestOneString::OCHAR_ASCII));
        register_test("P-tB4009c", new TestOneString_OpGreaterEqual(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4009d", new TestOneString_OpGreaterEqual(TestOneString::CSTR_ASCII));
        register_test("P-tB4009e", new TestOneString_OpGreaterEqual(TestOneString::CSTR_UNICODE));
        register_test("P-tB4009f", new TestOneString_OpGreaterEqual(TestOneString::STR_ASCII));
        register_test("P-tB4009g", new TestOneString_OpGreaterEqual(TestOneString::STR_UNICODE));
        register_test("P-tB4009h", new TestOneString_OpGreaterEqual(TestOneString::OSTR_ASCII));
        register_test("P-tB4009i", new TestOneString_OpGreaterEqual(TestOneString::OSTR_UNICODE));

        register_test("P-tB4010", new TestOneString_At());
        register_test("P-tB4011", new TestOneString_OpAt());
        register_test("P-tB4012", new TestOneString_Capacity());
        register_test("P-tB4013", new TestOneString_PopBack());
        register_test("P-tB4014", new TestOneString_Length());
        register_test("P-tB4015", new TestOneString_Size());
        register_test("P-tB4016", new TestOneString_Copy());
        register_test("P-tB4017", new TestOneString_CStr());
        register_test("P-tB4018", new TestOneString_Empty());
        // tB4020: length
        // tB4021: max_size
        // tB4022: substr

        // tB4023[a-i]: append
        // tB4024[a-i]: opAppend
        // tB4025: back
        // tB4026: clear
        // tB4027: erase
        // tB4028: front
        // tB4029[a-i]: insert
        // tB4030: replace
        // tB4031: reverse
        // tB4032: swap

        // tB4033: opStreamInsert (<<)
        // tB4034: opStreamExtract (>>)

        // tB4035: find
        // tB4036: find_first_not_of
        // tB4037: find_first_of
        // tB4038: find_last_not_of
        // tB4039: rfind

        // tB4040: expand
        // tB4041: reserve
        // tB4042: shrink_to_fit
        // tB4043: "force resize"

        //TODO: Comparative tests against std::string
    }
}
