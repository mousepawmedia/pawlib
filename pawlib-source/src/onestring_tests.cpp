#include "pawlib/onestring_tests.hpp"

namespace pawlib
{
    void TestSuite_Onestring::load_tests()
    {
        register_test("P-tB4001a", new TestOnestring_Assign(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4001b", new TestOnestring_Assign(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4001c", new TestOnestring_Assign(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4001d", new TestOnestring_Assign(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4001e", new TestOnestring_Assign(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4001f", new TestOnestring_Assign(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4001g", new TestOnestring_Assign(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4001h", new TestOnestring_Assign(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4001i", new TestOnestring_Assign(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4002a", new TestOnestring_Equals(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4002b", new TestOnestring_Equals(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4002c", new TestOnestring_Equals(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4002d", new TestOnestring_Equals(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4002e", new TestOnestring_Equals(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4002f", new TestOnestring_Equals(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4002g", new TestOnestring_Equals(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4002h", new TestOnestring_Equals(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4002i", new TestOnestring_Equals(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4003a", new TestOnestring_OpEquals(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4003b", new TestOnestring_OpEquals(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4003c", new TestOnestring_OpEquals(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4003d", new TestOnestring_OpEquals(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4003e", new TestOnestring_OpEquals(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4003f", new TestOnestring_OpEquals(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4003g", new TestOnestring_OpEquals(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4003h", new TestOnestring_OpEquals(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4003i", new TestOnestring_OpEquals(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4004a", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4004b", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4004c", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4004d", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4004e", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4004f", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4004g", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4004h", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4004i", new TestOnestring_OpNotEquals(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4005a", new TestOnestring_Compare(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4005b", new TestOnestring_Compare(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4005c", new TestOnestring_Compare(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4005d", new TestOnestring_Compare(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4005e", new TestOnestring_Compare(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4005f", new TestOnestring_Compare(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4005g", new TestOnestring_Compare(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4005h", new TestOnestring_Compare(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4005i", new TestOnestring_Compare(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4006a", new TestOnestring_OpLess(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4006b", new TestOnestring_OpLess(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4006c", new TestOnestring_OpLess(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4006d", new TestOnestring_OpLess(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4006e", new TestOnestring_OpLess(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4006f", new TestOnestring_OpLess(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4006g", new TestOnestring_OpLess(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4006h", new TestOnestring_OpLess(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4006i", new TestOnestring_OpLess(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4007a", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4007b", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4007c", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4007d", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4007e", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4007f", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4007g", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4007h", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4007i", new TestOnestring_OpLessEqual(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4008a", new TestOnestring_OpGreater(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4008b", new TestOnestring_OpGreater(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4008c", new TestOnestring_OpGreater(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4008d", new TestOnestring_OpGreater(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4008e", new TestOnestring_OpGreater(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4008f", new TestOnestring_OpGreater(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4008g", new TestOnestring_OpGreater(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4008h", new TestOnestring_OpGreater(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4008i", new TestOnestring_OpGreater(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4009a", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4009b", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4009c", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4009d", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4009e", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4009f", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4009g", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4009h", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4009i", new TestOnestring_OpGreaterEqual(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4010", new TestOnestring_At());
        register_test("P-tB4011", new TestOnestring_OpAt());
        register_test("P-tB4012", new TestOnestring_Back());
        register_test("P-tB4013", new TestOnestring_Front());
        register_test("P-tB4014", new TestOnestring_Capacity());
        register_test("P-tB4015", new TestOnestring_PopBack());
        register_test("P-tB4016", new TestOnestring_Length());
        register_test("P-tB4017", new TestOnestring_Size());
        register_test("P-tB4018", new TestOnestring_Copy());
        register_test("P-tB4019", new TestOnestring_CStr());
        register_test("P-tB4020", new TestOnestring_Empty());
        register_test("P-tB4021", new TestOnestring_Substr());

        register_test("P-tB4022a", new TestOnestring_Append(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4022b", new TestOnestring_Append(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4022c", new TestOnestring_Append(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4022d", new TestOnestring_Append(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4022e", new TestOnestring_Append(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4022f", new TestOnestring_Append(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4022g", new TestOnestring_Append(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4022h", new TestOnestring_Append(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4022i", new TestOnestring_Append(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4023a", new TestOnestring_OpAppend(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4023b", new TestOnestring_OpAppend(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4023c", new TestOnestring_OpAppend(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4023d", new TestOnestring_OpAppend(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4023e", new TestOnestring_OpAppend(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4023f", new TestOnestring_OpAppend(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4023g", new TestOnestring_OpAppend(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4023h", new TestOnestring_OpAppend(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4023i", new TestOnestring_OpAppend(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4024", new TestOnestring_Clear());
        register_test("P-tB4025", new TestOnestring_Erase());

        register_test("P-tB4026a", new TestOnestring_Insert(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4026b", new TestOnestring_Insert(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4026c", new TestOnestring_Insert(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4026d", new TestOnestring_Insert(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4026e", new TestOnestring_Insert(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4026f", new TestOnestring_Insert(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4026g", new TestOnestring_Insert(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4026h", new TestOnestring_Insert(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4026i", new TestOnestring_Insert(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4027a", new TestOnestring_Replace(TestOnestring::TestStringType::CHAR));
        register_test("P-tB4027b", new TestOnestring_Replace(TestOnestring::TestStringType::OCHAR_ASCII));
        register_test("P-tB4027c", new TestOnestring_Replace(TestOnestring::TestStringType::OCHAR_UNICODE));
        register_test("P-tB4027d", new TestOnestring_Replace(TestOnestring::TestStringType::CSTR_ASCII));
        register_test("P-tB4027e", new TestOnestring_Replace(TestOnestring::TestStringType::CSTR_UNICODE));
        register_test("P-tB4027f", new TestOnestring_Replace(TestOnestring::TestStringType::STR_ASCII));
        register_test("P-tB4027g", new TestOnestring_Replace(TestOnestring::TestStringType::STR_UNICODE));
        register_test("P-tB4027h", new TestOnestring_Replace(TestOnestring::TestStringType::OSTR_ASCII));
        register_test("P-tB4027i", new TestOnestring_Replace(TestOnestring::TestStringType::OSTR_UNICODE));

        register_test("P-tB4028", new TestOnestring_Reverse());
        register_test("P-tB4029", new TestOnestring_Swap());

        register_test("P-tB4030", new TestOnestring_Expand());
        register_test("P-tB4031", new TestOnestring_Reserve());
        register_test("P-tB4032", new TestOnestring_Resize());
        register_test("P-tB4033", new TestOnestring_ShrinkToFit());
        register_test("P-tB4034", new TestOnestring_ForceResize());
        register_test("P-tS4034", new TestOnestring_ForceResizeStress(), false);

        // tB4035: find
        // tB4036: find_first_not_of
        // tB4037: find_first_of
        // tB4038: find_last_not_of
        // tB4039: rfind

        //TODO: Comparative tests against std::string
    }
}
