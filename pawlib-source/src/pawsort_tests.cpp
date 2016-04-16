#include "pawsort_tests.hpp"

namespace pawlib
{
    void TestSuite_Pawsort::load_tests(TestManager* testmanager)
    {
        if(testmanager == nullptr)
        {
            return;
        }

        testmanager->register_test("P-tB301a",
            new TestStdSort(TestSort::ARRAY_SORTED),
            "Sorted Array (std::sort)",
            "Already sorted array.");
        testmanager->register_test("P-tB301b",
            new TestPawSort(TestSort::ARRAY_SORTED),
            "Sorted Array (pawsort)",
            "Already sorted array.");

        testmanager->register_test("P-tB302a",
            new TestStdSort(TestSort::ARRAY_REVERSED),
            "Reversed Array (std::sort)",
            "Already sorted array in reverse.");
        testmanager->register_test("P-tB302b",
            new TestPawSort(TestSort::ARRAY_REVERSED),
            "Reversed Array (pawsort)",
            "Already sorted array in reverse.");

        testmanager->register_test("P-tB303a",
            new TestStdSort(TestSort::ARRAY_NEARLY_2),
            "Nearly, Invert 2 (std::sort)",
            "Nearly sorted array - the order of every two are inverted.");
        testmanager->register_test("P-tB303b",
            new TestPawSort(TestSort::ARRAY_NEARLY_2),
            "Nearly, Invert 2 (pawsort)",
            "Nearly sorted array - the order of every two are inverted.");

        testmanager->register_test("P-tB304a",
            new TestStdSort(TestSort::ARRAY_NEARLY_5),
            "Nearly, Invert 5 (std::sort)",
            "Nearly sorted array - the order of every five are inverted.");
        testmanager->register_test("P-tB304b",
            new TestPawSort(TestSort::ARRAY_NEARLY_5),
            "Nearly, Invert 5 (pawsort)",
            "Nearly sorted array - the order of every five are inverted.");

        testmanager->register_test("P-tB305a",
            new TestStdSort(TestSort::ARRAY_FEW_UNIQUE),
            "Few Unique (std::sort)",
            "Few (specifically, five) unique values in the array.");
        testmanager->register_test("P-tB305b",
            new TestPawSort(TestSort::ARRAY_FEW_UNIQUE),
            "Few Unique (pawsort)",
            "Few (specifically, five) unique values in the array.");

        testmanager->register_test("P-tB306a",
            new TestStdSort(TestSort::ARRAY_BLACK_SHEEP),
            "Black Sheep (std::sort)",
            "Array with only two values out of place.");
        testmanager->register_test("P-tB306b",
            new TestPawSort(TestSort::ARRAY_BLACK_SHEEP),
            "Black Sheep (pawsort)",
            "Array with only two values out of place.");

        testmanager->register_test("P-tB307a",
            new TestStdSort(TestSort::ARRAY_DOUBLE_CLIMB),
            "Double Climb (std::sort)",
            "Array values ascends from 0 to half, twice sequentially.");
        testmanager->register_test("P-tB307b",
            new TestPawSort(TestSort::ARRAY_DOUBLE_CLIMB),
            "Double Climb (pawsort)",
            "Array values ascends from 0 to half, twice sequentially.");

        testmanager->register_test("P-tB308a",
            new TestStdSort(TestSort::ARRAY_DOUBLE_DROP),
            "Double Drop (std::sort)",
            "Array values descend from half to 0, twice sequentially.");
        testmanager->register_test("P-tB308b",
            new TestPawSort(TestSort::ARRAY_DOUBLE_DROP),
            "Double Drop (pawsort)",
            "Array values descend from half to 0, twice sequentially.");

        testmanager->register_test("P-tB309a",
            new TestStdSort(TestSort::ARRAY_STAIRS),
            "Stairs (std::sort)",
            "Array ascends and descends 'stairs', with a jump of 5.");
        testmanager->register_test("P-tB309b",
            new TestPawSort(TestSort::ARRAY_STAIRS),
            "Stairs (pawsort)",
            "Array ascends and descends 'stairs', with a jump of 5.");

        testmanager->register_test("P-tB310a",
            new TestStdSort(TestSort::ARRAY_MOUNTAIN),
            "Mountain (std::sort)",
            "Array ascends from 0 to half and drops back to 0.");
        testmanager->register_test("P-tB310b",
            new TestPawSort(TestSort::ARRAY_MOUNTAIN),
            "Mountain (pawsort)",
            "Array ascends from 0 to half and drops back to 0.");

        testmanager->register_test("P-tB311a",
            new TestStdSort(TestSort::ARRAY_DOUBLE_MOUNTAIN),
            "Double Mountain (std::sort)",
            "Array ascends from 0 to half and drops, twice. Uses double-jumps.");
        testmanager->register_test("P-tB311b",
            new TestPawSort(TestSort::ARRAY_DOUBLE_MOUNTAIN),
            "Double Mountain (pawsort)",
            "Array ascends from 0 to half and drops, twice. Uses double-jumps.");

        testmanager->register_test("P-tB312a",
            new TestStdSort(TestSort::ARRAY_EVEREST),
            "Everest (std::sort)",
            "Array ascends by huge increments, and then drop back to 0.");
        testmanager->register_test("P-tB312b",
            new TestPawSort(TestSort::ARRAY_EVEREST),
            "Everest (pawsort)",
            "Array ascends by huge increments, and then drop back to 0.");

        testmanager->register_test("P-tB313a",
            new TestStdSort(TestSort::ARRAY_CLIFF),
            "Cliff (std::sort)",
            "Array ascends by huge increments, and then drops off suddenly.");
        testmanager->register_test("P-tB313b",
            new TestPawSort(TestSort::ARRAY_CLIFF),
            "Cliff (pawsort)",
            "Array ascends by huge increments, and then drops off suddenly.");

        testmanager->register_test("P-tB314a",
            new TestStdSort(TestSort::ARRAY_SPIKE),
            "Spike (std::sort)",
            "Array ascends from 0 towards half, spikes suddenly, and then drops \
back down near half and descends towards 0. Intended to throw off the \
median-of-three by creating an absurdly high middle value.");
        testmanager->register_test("P-tB314b",
            new TestPawSort(TestSort::ARRAY_SPIKE),
            "Spike (pawsort)",
            "Array ascends from 0 towards half, spikes suddenly, and then drops \
back down near half and descends towards 0. Intended to throw off the \
median-of-three by creating an absurdly high middle value.");

        testmanager->register_test("P-tB315a",
            new TestStdSort(TestSort::ARRAY_CLIFF),
            "Chicken (std::sort)",
            "Array composed of pairs - one starting at 0 and incrementing by \
one each pair, and one starting at n and decrementing by one each [pair, with \
the middle pair values both being half of n.");
        testmanager->register_test("P-tB315b",
            new TestPawSort(TestSort::ARRAY_CLIFF),
            "Chicken (pawsort)",
            "Array composed of pairs - one starting at 0 and incrementing by \
one each pair, and one starting at n and decrementing by one each [pair, with \
the middle pair values both being half of n.");

        testmanager->register_test("P-tB316a",
            new TestStdSort(TestSort::ARRAY_NIGHTMARE),
            "Nightmare (std::sort)",
            "Array brutally murders the median-of-three by placing 0 at the \
first, middle, and last indices, on top of a reversed sorted array with few \
unique values. Really, this is just evil incarnate.");
        testmanager->register_test("P-tB316b",
            new TestPawSort(TestSort::ARRAY_NIGHTMARE),
            "Nightmare (pawsort)",
            "Array brutally murders the median-of-three by placing 0 at the \
first, middle, and last indices, on top of a reversed sorted array with few \
unique values. Really, this is just evil incarnate.");
    }
}
