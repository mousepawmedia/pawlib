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

        // tB4005[a-i]: compare
        // tB4006[a-i]: opLess
        // tB4007[a-i]: opLessEqual
        // tB4008[a-i]: opGreater
        // tB4009[a-i]: opGreaterEqual

        // tB4010[a-i]: append
        // tB4011[a-i]: opAppend
        // tB4012: clear
        // tB4013: erase
        // tB4014[a-i]: insert
        // tB4015: push_back
        // tB4016: replace
        // tB4017: reverse
        // tB4018: swap

        // tB4019: at
        // tB4020: opAt ([])
        // tB4021: back
        // tB4022: capacity
        // tB4023: copy
        // tB4024: c_str (data)
        // tB4025: empty
        // tB4026: front
        // tB4027: getline
        // tB4028: length
        // tB4029: max_size
        // tB4030: pop_back
        // tB4031: substr

        // tB4032: opStreamInsert (<<)
        // tB4033: opStreamExtract (>>)

        // tB4034: find
        // tB4035: find_first_not_of
        // tB4036: find_first_of
        // tB4037: find_last_not_of
        // tB4038: rfind

        // tB4039: expand
        // tB4040: reserve
        // tB4041: shrink_to_fit
        // tB4042: force resize

        //TODO: Comparative tests against std::string
    }
}
