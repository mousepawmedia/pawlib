#include "onestring_tests.hpp"

namespace pawlib
{
    void TestSuite_Onestring::load_tests()
    {
        register_test("P-tB4001",
            new TestPawCompare(TestString::SAME_NO_UNICODE));
        register_test("P-tB4001*",
            new TestStdCompare(TestString::SAME_NO_UNICODE), false);

        register_test("P-tB4002",
            new TestPawCompare(TestString::SAME_SOME_UNICODE));
        register_test("P-tB4002*",
            new TestStdCompare(TestString::SAME_SOME_UNICODE), false);

        register_test("P-tB4003",
            new TestPawCompare(TestString::SAME_ALL_UNICODE));
        register_test("P-tB4003*",
            new TestStdCompare(TestString::SAME_ALL_UNICODE), false);

        register_test("P-tB4004",
            new TestPawCompare(TestString::NSAME_FIRST_CHAR));
        register_test("P-tB4004*",
            new TestStdCompare(TestString::NSAME_FIRST_CHAR), false);

        register_test("P-tB4005",
            new TestPawCompare(TestString::NSAME_MIDDLE_CHAR));
        register_test("P-tB4005*",
            new TestStdCompare(TestString::NSAME_MIDDLE_CHAR), false);

        register_test("P-tB4006",
            new TestPawCompare(TestString::NSAME_LAST_CHAR));
        register_test("P-tB4006*",
            new TestStdCompare(TestString::NSAME_LAST_CHAR), false);
    }
}

