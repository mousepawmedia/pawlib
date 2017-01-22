#include "pawlib/pawsort_tests.hpp"

namespace pawlib
{
    void TestSuite_Pawsort::load_tests()
    {
        register_test("P-tB3001",
            new TestPawSort(TestSort::ARRAY_SORTED));
        register_test("P-tB3001*",
            new TestStdSort(TestSort::ARRAY_SORTED), false);

        register_test("P-tB3002",
            new TestPawSort(TestSort::ARRAY_REVERSED));
        register_test("P-tB3002*",
            new TestStdSort(TestSort::ARRAY_REVERSED), false);

        register_test("P-tB3003",
            new TestPawSort(TestSort::ARRAY_NEARLY_2));
        register_test("P-tB3003*",
            new TestStdSort(TestSort::ARRAY_NEARLY_2), false);

        register_test("P-tB3004",
            new TestPawSort(TestSort::ARRAY_NEARLY_5));
        register_test("P-tB3004*",
            new TestStdSort(TestSort::ARRAY_NEARLY_5), false);

        register_test("P-tB3005",
            new TestPawSort(TestSort::ARRAY_FEW_UNIQUE));
        register_test("P-tB3005*",
            new TestStdSort(TestSort::ARRAY_FEW_UNIQUE), false);

        register_test("P-tB3006",
            new TestPawSort(TestSort::ARRAY_BLACK_SHEEP));
        register_test("P-tB3006*",
            new TestStdSort(TestSort::ARRAY_BLACK_SHEEP), false);

        register_test("P-tB3007",
            new TestPawSort(TestSort::ARRAY_DOUBLE_CLIMB));
        register_test("P-tB3007*",
            new TestStdSort(TestSort::ARRAY_DOUBLE_CLIMB), false);

        register_test("P-tB3008",
            new TestPawSort(TestSort::ARRAY_DOUBLE_DROP));
        register_test("P-tB3008*",
            new TestStdSort(TestSort::ARRAY_DOUBLE_DROP), false);

        register_test("P-tB3009",
            new TestPawSort(TestSort::ARRAY_STAIRS));
        register_test("P-tB3009*",
            new TestStdSort(TestSort::ARRAY_STAIRS), false);

        register_test("P-tB3010*",
            new TestStdSort(TestSort::ARRAY_MOUNTAIN));
        register_test("P-tB3010",
            new TestPawSort(TestSort::ARRAY_MOUNTAIN), false);

        register_test("P-tB3011",
            new TestPawSort(TestSort::ARRAY_DOUBLE_MOUNTAIN));
        register_test("P-tB3011*",
            new TestStdSort(TestSort::ARRAY_DOUBLE_MOUNTAIN), false);

        register_test("P-tB3012",
            new TestPawSort(TestSort::ARRAY_EVEREST));
        register_test("P-tB3012*",
            new TestStdSort(TestSort::ARRAY_EVEREST), false);

        register_test("P-tB3013",
            new TestPawSort(TestSort::ARRAY_CLIFF));
        register_test("P-tB3013*",
            new TestStdSort(TestSort::ARRAY_CLIFF), false);

        register_test("P-tB3014",
            new TestPawSort(TestSort::ARRAY_SPIKE));
        register_test("P-tB3014*",
            new TestStdSort(TestSort::ARRAY_SPIKE), false);

        register_test("P-tB3015",
            new TestPawSort(TestSort::ARRAY_CLIFF));
        register_test("P-tB3015*",
            new TestStdSort(TestSort::ARRAY_CLIFF), false);

        register_test("P-tB3016",
            new TestPawSort(TestSort::ARRAY_NIGHTMARE));
        register_test("P-tB3016*",
            new TestStdSort(TestSort::ARRAY_NIGHTMARE), false);
    }
}
