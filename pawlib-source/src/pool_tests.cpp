#include "pawlib/pool_tests.hpp"

void TestSuite_Pool::load_tests()
{
    register_test("P-tB1601",
        new TestPool_ThriceFill(), true, new TestPool_ThriceFillAlloc());

    register_test("P-tB1602",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::DFLT));
    register_test("P-tB1603",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::COPY));
    register_test("P-tB1604",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::DFLT_FAILSAFE));
    register_test("P-tB1605",
        new TestPool_Create(TestPool_Create::TestPoolCreateMode::COPY_FAILSAFE));

    register_test("P-tB1606",
        new TestPool_Access());

    register_test("P-tB1607",
        new TestPool_Access());

    register_test("P-tB1608",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_FULL_ASGN));
    register_test("P-tB1609",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_FULL_ASGN_CPY));
    register_test("P-tB160A",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_ACC_DELETED_REF));
    register_test("P-tB160B",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_DES_FOREIGN_REF));
    register_test("P-tB160C",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_DES_DELETED_REF));
    register_test("P-tB160D",
        new TestPool_Exception(TestPool_Exception::FailTestType::POOL_DES_FOREIGN_REF));
}
