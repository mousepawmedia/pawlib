#include "pawlib/onestring_tests.hpp"

namespace pawlib
{
    void TestSuite_Onestring::load_tests()
    {
        register_test("P-tB4001",
            new TestPawCompare(TestString::SAME_NO_UNICODE), true,
            new TestStdCompare(TestString::SAME_NO_UNICODE));

        register_test("P-tB4002",
            new TestPawCompare(TestString::SAME_SOME_UNICODE), true,
            new TestStdCompare(TestString::SAME_SOME_UNICODE));

        register_test("P-tB4003",
            new TestPawCompare(TestString::SAME_ALL_UNICODE), true,
            new TestStdCompare(TestString::SAME_ALL_UNICODE));

        register_test("P-tB4004",
            new TestPawCompare(TestString::NSAME_FIRST_CHAR), true,
            new TestStdCompare(TestString::NSAME_FIRST_CHAR));

        register_test("P-tB4005",
            new TestPawCompare(TestString::NSAME_MIDDLE_CHAR), true,
            new TestStdCompare(TestString::NSAME_MIDDLE_CHAR));

        register_test("P-tB4006",
            new TestPawCompare(TestString::NSAME_LAST_CHAR), true,
            new TestStdCompare(TestString::NSAME_LAST_CHAR));
    }
}
