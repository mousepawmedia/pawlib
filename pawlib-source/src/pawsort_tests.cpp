#include "pawlib/pawsort_tests.hpp"

namespace pawlib
{
    void TestSuite_Pawsort::load_tests()
    {
        register_test("P-tB3001",
            new TestPawSort(TestSort::ARRAY_SORTED), true,
            new TestStdSort(TestSort::ARRAY_SORTED));

        register_test("P-tB3002",
            new TestPawSort(TestSort::ARRAY_REVERSED), true,
            new TestStdSort(TestSort::ARRAY_REVERSED));

        register_test("P-tB3003",
            new TestPawSort(TestSort::ARRAY_NEARLY_2), true,
            new TestStdSort(TestSort::ARRAY_NEARLY_2));

        register_test("P-tB3004",
            new TestPawSort(TestSort::ARRAY_NEARLY_5), true,
            new TestStdSort(TestSort::ARRAY_NEARLY_5));

        register_test("P-tB3005",
            new TestPawSort(TestSort::ARRAY_FEW_UNIQUE), true,
            new TestStdSort(TestSort::ARRAY_FEW_UNIQUE));

        register_test("P-tB3006",
            new TestPawSort(TestSort::ARRAY_BLACK_SHEEP), true,
            new TestStdSort(TestSort::ARRAY_BLACK_SHEEP));

        register_test("P-tB3007",
            new TestPawSort(TestSort::ARRAY_DOUBLE_CLIMB), true,
            new TestStdSort(TestSort::ARRAY_DOUBLE_CLIMB));

        register_test("P-tB3008",
            new TestPawSort(TestSort::ARRAY_DOUBLE_DROP), true,
            new TestStdSort(TestSort::ARRAY_DOUBLE_DROP));

        register_test("P-tB3009",
            new TestPawSort(TestSort::ARRAY_STAIRS), true,
            new TestStdSort(TestSort::ARRAY_STAIRS));

        register_test("P-tB3010*",
            new TestStdSort(TestSort::ARRAY_MOUNTAIN), true,
            new TestPawSort(TestSort::ARRAY_MOUNTAIN));

        register_test("P-tB3011",
            new TestPawSort(TestSort::ARRAY_DOUBLE_MOUNTAIN), true,
            new TestStdSort(TestSort::ARRAY_DOUBLE_MOUNTAIN));

        register_test("P-tB3012",
            new TestPawSort(TestSort::ARRAY_EVEREST), true,
            new TestStdSort(TestSort::ARRAY_EVEREST));

        register_test("P-tB3013",
            new TestPawSort(TestSort::ARRAY_CLIFF), true,
            new TestStdSort(TestSort::ARRAY_CLIFF));

        register_test("P-tB3014",
            new TestPawSort(TestSort::ARRAY_SPIKE), true,
            new TestStdSort(TestSort::ARRAY_SPIKE));

        register_test("P-tB3015",
            new TestPawSort(TestSort::ARRAY_CLIFF), true,
            new TestStdSort(TestSort::ARRAY_CLIFF));

        register_test("P-tB3016",
            new TestPawSort(TestSort::ARRAY_NIGHTMARE), true,
            new TestStdSort(TestSort::ARRAY_NIGHTMARE));
    }
}
