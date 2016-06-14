#include "flex_array_tests.hpp"

namespace pawlib
{
    void TestSuite_FlexArray::load_tests(TestManager* testmanager)
    {
        if(testmanager == nullptr)
        {
            return;
        }

        testmanager->register_test("P-tB101a",
            new TestVector_Push,
            "Push 1000 Integers (std::vector)",
            "Insert 1000 integers at the back of a vector (push).");
        testmanager->register_test("P-tB101b",
            new TestFlex_Push,
            "Push 1000 Integers (flexarray)",
            "Insert 1000 integers at the back of a flexarray (push).");

        testmanager->register_test("P-tB102a",
            new TestVector_Shift,
            "Insert 1000 Integers At Front (std::vector)",
            "Insert 1000 integers at the front of a vector (shift).");
        testmanager->register_test("P-tB102b",
            new TestFlex_Shift,
            "Insert 1000 Integers At Front (flexarray)",
            "Insert 1000 integers at the front of a flexarray (shift).");
         testmanager->register_test("P-tB102c",
            new TestFlex_ShiftAlt,// new becuase "unique pointer"
            "Insert 1000 Integers At Front using insert at 0 (flexarray)",
            "Insert 1000 integers at the front of a flexarray using isnert at 0.");
        testmanager->register_test("P-tB103a",
            new TestVector_Insert,
            "Insert 1000 Integers At Middle (std::vector)",
            "Insert 1000 integers at the middle of a vector. Middle is \
calculated as size()/2.");
        testmanager->register_test("P-tB103b",
            new TestFlex_Insert,
            "Insert 1000 Integers At Middle (flexarray)",
            "Insert 1000 integers at the middle of a flexarray. Middle is \
calculated as size()/2.");
    }

}
