#include "onestring_tests.hpp"

namespace pawlib
{
    void TestSuite_Onestring::load_tests(TestManager* testmanager)
    {
        if(testmanager == nullptr)
        {
            return;
        }

        testmanager->register_test("P-tB401a",
            new TestStdCompare(TestString::SAME_NO_UNICODE),
            "String Compare, Same No Unicode (std::string)",
            "Compares two identical strings containing no Unicode.");
        testmanager->register_test("P-tB401b",
            new TestPawCompare(TestString::SAME_NO_UNICODE),
            "String Compare, Same No Unicode (onestring)",
            "Compares two identical strings containing no Unicode.");

        testmanager->register_test("P-tB402a",
            new TestStdCompare(TestString::SAME_SOME_UNICODE),
            "String Compare, Same Some Unicode (std::string)",
            "Compares two identical strings containing some Unicode.");
        testmanager->register_test("P-tB402b",
            new TestPawCompare(TestString::SAME_SOME_UNICODE),
            "String Compare, Same Some Unicode (onestring)",
            "Compares two identical strings containing some Unicode.");

        testmanager->register_test("P-tB403a",
            new TestStdCompare(TestString::SAME_ALL_UNICODE),
            "String Compare, Same All Unicode (std::string)",
            "Compares two identical strings containing all Unicode.");
        testmanager->register_test("P-tB403b",
            new TestPawCompare(TestString::SAME_ALL_UNICODE),
            "String Compare, Same All Unicode (onestring)",
            "Compares two identical strings containing all Unicode.");

        testmanager->register_test("P-tB404a",
            new TestStdCompare(TestString::NSAME_FIRST_CHAR),
            "String Compare, Diff First (std::string)",
            "Compares two strings with the first character different.");
        testmanager->register_test("P-tB404b",
            new TestPawCompare(TestString::NSAME_FIRST_CHAR),
            "String Compare, Diff First (onestring)",
            "Compares two strings with the first character different.");

        testmanager->register_test("P-tB405a",
            new TestStdCompare(TestString::NSAME_MIDDLE_CHAR),
            "String Compare, Diff Middle (std::string)",
            "Compares two strings with the middle character different.");
        testmanager->register_test("P-tB405b",
            new TestPawCompare(TestString::NSAME_MIDDLE_CHAR),
            "String Compare, Diff Middle (onestring)",
            "Compares two strings with the middle character different.");

        testmanager->register_test("P-tB406a",
            new TestStdCompare(TestString::NSAME_LAST_CHAR),
            "String Compare, Diff Last (std::string)",
            "Compares two strings with the last character different.");
        testmanager->register_test("P-tB406b",
            new TestPawCompare(TestString::NSAME_LAST_CHAR),
            "String Compare, Diff Last (onestring)",
            "Compares two strings with the last character different.");
    }
}

