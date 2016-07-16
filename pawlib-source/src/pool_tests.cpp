#include "pool_tests.hpp"

namespace pawlib
{
    void TestSuite_Pool::load_tests(TestManager* testmanager)
    {
        if(testmanager == nullptr)
        {
            return;
        }
        testmanager->register_test("P-tB161a",
            new TestPool_ThriceFillAlloc(),
            "Pool: Traditional Allocate & Deallocate",
            "Allocate and deallocate 1000 Dummy objects the old fashioned way.");
        testmanager->register_test("P-tB161b",
            new TestPool_ThriceFill(),
            "Pool: Create & Destroy",
            "Create a 1000-object Dummy object pool, then create & destroy 1000 objects in it three times.");

        testmanager->register_test("P-tB162a",
            new TestPool_Create(true, false, false),
            "Pool: Create by Assignment, Default",
            "Create a new object in a pool using pool_ref assignment and the object's default constructor.");
        testmanager->register_test("P-tB162b",
            new TestPool_Create(true, true, false),
            "Pool: Create by Assignment, Copy",
            "Create a new object in a pool using pool_ref assignment and the object's copy constructor.");
        testmanager->register_test("P-tB162c",
            new TestPool_Create(false, false, false),
            "Pool: Create by Constructor, Default",
            "Create a new object in a pool using the pool_ref constructor and the object's default constructor.");
        testmanager->register_test("P-tB162d",
            new TestPool_Create(false, true, false),
            "Pool: Create by Constructor, Copy",
            "Create a new object in a pool using the pool_ref constructor and the object's copy constructor.");
        testmanager->register_test("P-tB162e",
            new TestPool_Create(true, false, true),
            "Pool: Create by Assignment, Default Failsafe",
            "Create a new object in a failsafe pool using pool_ref assignment and the object's default constructor.");
        testmanager->register_test("P-tB162f",
            new TestPool_Create(true, true, true),
            "Pool: Create by Assignment, Copy Failsafe",
            "Create a new object in a failsafe pool using pool_ref assignment and the object's copy constructor.");
        testmanager->register_test("P-tB162g",
            new TestPool_Create(false, false, true),
            "Pool: Create by Constructor, Default Failsafe",
            "Create a new object in a failsafe pool using the pool_ref constructor and the object's default constructor.");
        testmanager->register_test("P-tB162h",
            new TestPool_Create(false, true, true),
            "Pool: Create by Constructor, Copy Failsafe",
            "Create a new object in a failsafe pool using the pool_ref constructor and the object's copy constructor.");

        testmanager->register_test("P-tB163",
            new TestPool_Access(),
            "Pool: Access Object",
            "Access an object inside the pool.");

        testmanager->register_test("P-tB164",
            new TestPool_Access(),
            "Pool: Destroy Object",
            "Destroy an object inside the pool.");

        testmanager->register_test("P-tB165a",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_ASGN),
            "Pool: (Exception) Full Pool Create Assignment w/ Default",
            "Throw and Catch e_pool_full from pool_ref assignment using the object's default constructor.");
        testmanager->register_test("P-tB165b",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_ASGN_CPY),
            "Pool: (Exception) Full Pool Create Assignment w/ Copy",
            "Throw and Catch e_pool_full from pool_ref assignment using the object's copy constructor.");
        testmanager->register_test("P-tB165c",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_CTOR),
            "Pool: (Exception) Full Pool Create Assignment w/ Default",
            "Throw and Catch e_pool_full from pool_ref constructor using the object's default constructor.");
        testmanager->register_test("P-tB165d",
            new TestPool_Exception(TestPool_Exception::POOL_FULL_CTOR_CPY),
            "Pool: (Exception) Full Pool Create Assignment w/ Copy",
            "Throw and Catch e_pool_full from pool_ref constructor using the object's copy constructor.");
        testmanager->register_test("P-tB165e",
            new TestPool_Exception(TestPool_Exception::POOL_ACC_DELETED_REF),
            "Pool: (Exception) Access w/ Deleted Ref",
            "Throw and Catch e_pool_invalid_ref from access using deleted reference.");
        testmanager->register_test("P-tB165f",
            new TestPool_Exception(TestPool_Exception::POOL_DES_FOREIGN_REF),
            "Pool: (Exception) Access w/ Foreign Ref",
            "Throw and Catch e_pool_invalid_ref from access using foreign reference.");
        testmanager->register_test("P-tB165g",
            new TestPool_Exception(TestPool_Exception::POOL_DES_DELETED_REF),
            "Pool: (Exception) Destroy w/ Deleted Ref",
            "Throw and Catch e_pool_invalid_ref from destroy using deleted reference.");
        testmanager->register_test("P-tB165h",
            new TestPool_Exception(TestPool_Exception::POOL_DES_FOREIGN_REF),
            "Pool: (Exception) Destroy w/ Foreign Ref",
            "Throw and Catch e_pool_invalid_ref from destroy using foreign reference.");
    }
}
