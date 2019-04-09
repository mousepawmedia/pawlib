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
        register_test("P-tB4012", new TestOneString_Back());
        register_test("P-tB4013", new TestOneString_Front());
        register_test("P-tB4014", new TestOneString_Capacity());
        register_test("P-tB4015", new TestOneString_PopBack());
        register_test("P-tB4016", new TestOneString_Length());
        register_test("P-tB4017", new TestOneString_Size());
        register_test("P-tB4018", new TestOneString_Copy());
        register_test("P-tB4019", new TestOneString_CStr());
        register_test("P-tB4020", new TestOneString_Empty());
        register_test("P-tB4021", new TestOneString_Substr());

        register_test("P-tB4022a", new TestOneString_Append(TestOneString::CHAR));
        register_test("P-tB4022b", new TestOneString_Append(TestOneString::OCHAR_ASCII));
        register_test("P-tB4022c", new TestOneString_Append(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4022d", new TestOneString_Append(TestOneString::CSTR_ASCII));
        register_test("P-tB4022e", new TestOneString_Append(TestOneString::CSTR_UNICODE));
        register_test("P-tB4022f", new TestOneString_Append(TestOneString::STR_ASCII));
        register_test("P-tB4022g", new TestOneString_Append(TestOneString::STR_UNICODE));
        register_test("P-tB4022h", new TestOneString_Append(TestOneString::OSTR_ASCII));
        register_test("P-tB4022i", new TestOneString_Append(TestOneString::OSTR_UNICODE));

        register_test("P-tB4023a", new TestOneString_OpAppend(TestOneString::CHAR));
        register_test("P-tB4023b", new TestOneString_OpAppend(TestOneString::OCHAR_ASCII));
        register_test("P-tB4023c", new TestOneString_OpAppend(TestOneString::OCHAR_UNICODE));
        register_test("P-tB4023d", new TestOneString_OpAppend(TestOneString::CSTR_ASCII));
        register_test("P-tB4023e", new TestOneString_OpAppend(TestOneString::CSTR_UNICODE));
        register_test("P-tB4023f", new TestOneString_OpAppend(TestOneString::STR_ASCII));
        register_test("P-tB4023g", new TestOneString_OpAppend(TestOneString::STR_UNICODE));
        register_test("P-tB4023h", new TestOneString_OpAppend(TestOneString::OSTR_ASCII));
        register_test("P-tB4023i", new TestOneString_OpAppend(TestOneString::OSTR_UNICODE));

        // tB4024: clear
        // tB4025: erase
        // tB4026[a-i]: insert
        // tB4027: replace
        // tB4028: reverse
        // tB4029: swap

        // tB4030: opStreamInsert (<<)
        // tB4031: opStreamExtract (>>)

        // tB4032: find
        // tB4033: find_first_not_of
        // tB4034: find_first_of
        // tB4035: find_last_not_of
        // tB4036: rfind

        // tB4037: expand
        // tB4038: reserve
        // tB4039: shrink_to_fit
        // tB4040: "force resize"

        //TODO: Comparative tests against std::string
    }
}
