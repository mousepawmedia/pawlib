#include "pool_tests.hpp"

namespace pawlib
{
    void TestSuite_Pool::load_tests()
    {
        register_test("P-tB1601",
            new TestPool_ThriceFill());
        register_test("P-tB1601*",
            new TestPool_ThriceFillAlloc(), false);

        register_test("P-tB1602a",
            new TestPool_Create(TestPool_Create::ASGN_DFLT));
        register_test("P-tB1602b",
            new TestPool_Create(TestPool_Create::CSTR_DFLT));
        register_test("P-tB1602c",
            new TestPool_Create(TestPool_Create::ASGN_COPY));
        register_test("P-tB1602d",
            new TestPool_Create(TestPool_Create::CSTR_COPY));
        register_test("P-tB1602e",
            new TestPool_Create(TestPool_Create::ASGN_DFLT_FAILSAFE));
        register_test("P-tB1602f",
            new TestPool_Create(TestPool_Create::CSTR_DFLT_FAILSAFE));
        register_test("P-tB1602g",
            new TestPool_Create(TestPool_Create::ASGN_COPY_FAILSAFE));
        register_test("P-tB1602h",
            new TestPool_Create(TestPool_Create::CSTR_COPY_FAILSAFE));

        register_test("P-tB1603",
            new TestPool_Access());

        register_test("P-tB1604",
            new TestPool_Access());

        register_test("P-tB1605a",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_ASGN));
        register_test("P-tB1605b",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_ASGN_CPY));
        register_test("P-tB1605c",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_CTOR));
        register_test("P-tB1605d",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_CTOR_CPY));
        register_test("P-tB1605e",
            new TestPool_Exception(TestPool_Exception::POOL_ACC_DELETED_REF));
        register_test("P-tB1605f",
            new TestPool_Exception(TestPool_Exception::POOL_DES_FOREIGN_REF));
        register_test("P-tB1605g",
            new TestPool_Exception(TestPool_Exception::POOL_DES_DELETED_REF));
        register_test("P-tB1605h",
            new TestPool_Exception(TestPool_Exception::POOL_DES_FOREIGN_REF));
    }
}
