#ifndef POOL_TESTS_HPP_INCLUDED
#define POOL_TESTS_HPP_INCLUDED

#include <new>

#include <flex_array.hpp>
#include <goldilocks.hpp>
#include <pool.hpp>

namespace pawlib
{
    class DummyClass
    {
        private:
            int64_t num1;
            int64_t num2;
            int64_t num3;
            int64_t num4;
            int64_t num5;
        public:
            DummyClass(int n1 = 1, int n2 = 2, int n3 = 3, int n4 = 4, int n5 = 5)
            :num1(n1), num2(n2), num3(n3), num4(n4), num5(n5)
            {}
            DummyClass(const DummyClass& cpy)
            :num1(cpy.num1), num2(cpy.num2), num3(cpy.num3),
             num4(cpy.num4), num5(cpy.num5)
            {}

            bool alive()
            {
                return true;
            }

            ~DummyClass(){}
    };

    // P-tB161a
    class TestPool_ThriceFillAlloc : public Test
    {
        public:
            // cppcheck-suppress uninitMemberVar
            TestPool_ThriceFillAlloc(){}

            bool run()
            {
                for(int r = 0; r < 3; ++r)
                {
                    for(int i = 0; i < 1000; ++i)
                    {
                        refs[i] = new DummyClass();
                    }
                    for(int j = 0; j < 1000; ++j)
                    {
                        delete refs[j];
                        refs[j] = 0;
                    }
                }
                return true;
            }

            ~TestPool_ThriceFillAlloc(){}
        private:
            DummyClass* refs[1000];
    };

    // P-tB161b
    class TestPool_ThriceFill : public Test
    {
        public:
            // cppcheck-suppress uninitMemberVar
            TestPool_ThriceFill(){}

            bool pre()
            {
                pool = new Pool<DummyClass>(1000);
                if(pool == nullptr)
                {
                    return false;
                }
                return true;
            }
            bool run()
            {

                for(int r = 0; r < 3; ++r)
                {
                    for(int i = 0; i < 1000; ++i)
                    {
                        try
                        {
                            refs[i] = pool->create();
                        }
                        catch(e_pool_reinit)
                        {
                            return false;
                        }
                    }
                    for(int j = 0; j < 1000; ++j)
                    {
                        try
                        {
                            pool->destroy(refs[j]);
                        }
                        catch(e_pool_invalid_ref)
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
            bool post()
            {
                delete pool;
                pool = 0;
                return true;
            }
            bool postmortem()
            {
                return post();
            }

            ~TestPool_ThriceFill(){}
        private:
            Pool<DummyClass>* pool;
            pool_ref<DummyClass> refs[1000];
    };

    // P-tB162[a-h]
    class TestPool_Create : public Test
    {
        public:
            // cppcheck-suppress uninitMemberVar
            TestPool_Create(bool asgn, bool cpy, bool fs)
            :assignment(asgn), copyconst(cpy), failsafe(fs)
            {}

            bool pre()
            {
                pool = new Pool<DummyClass>(1, failsafe);
                if(pool == nullptr)
                {
                    return false;
                }
                return true;
            }

            bool janitor()
            {
                if(!poolrf.invalid())
                {
                    pool->destroy(poolrf);
                }
                return true;
            }

            bool run()
            {
                try
                {
                    if(assignment && !copyconst)
                    {
                        pool_ref<DummyClass> rf = pool->create();
                        poolrf = rf;
                    }
                    else if(assignment && copyconst)
                    {
                        pool_ref<DummyClass> rf = pool->create(DummyClass(5,4,3,2,1));
                        poolrf = rf;
                    }
                    else if(!assignment && !copyconst)
                    {
                        pool_ref<DummyClass> rf(*pool);
                        poolrf = rf;
                    }
                    else if(!assignment && copyconst)
                    {
                        pool_ref<DummyClass> rf(*pool, DummyClass(5,4,3,2,1));
                        poolrf = rf;
                    }
                }
                catch(e_pool_full)
                {
                    return false;
                }

                if(poolrf.invalid())
                {
                    return false;
                }

                return true;
            }

            bool post()
            {
                delete pool;
                pool = 0;
                return true;
            }

            bool postmortem()
            {
                return post();
            }

            ~TestPool_Create(){}

        private:
            bool assignment;
            bool copyconst;
            bool failsafe;
            Pool<DummyClass>* pool;
            pool_ref<DummyClass> poolrf;
    };

    // P-tB163
    class TestPool_Access : public Test
    {
        public:
            // cppcheck-suppress uninitMemberVar
            TestPool_Access(){}

            bool pre()
            {
                pool = new Pool<DummyClass>(1);
                if(pool == nullptr)
                {
                    return false;
                }

                try
                {
                    poolrf = pool->create();
                }
                catch(e_pool_full)
                {
                    return false;
                }

                return true;
            }

            bool run()
            {
                bool r = false;
                try
                {
                    r = pool->access(poolrf).alive();
                }
                catch(e_pool_invalid_ref)
                {
                    return false;
                }

                return r;
            }

            bool post()
            {
                delete pool;
                pool = 0;
                return true;
            }

            bool postmortem()
            {
                return post();
            }

            ~TestPool_Access(){}

        private:
            Pool<DummyClass>* pool;
            pool_ref<DummyClass> poolrf;
    };

    // P-tB164
    class TestPool_Destroy : public Test
    {
        public:
            // cppcheck-suppress uninitMemberVar
            TestPool_Destroy(){}

            bool pre()
            {
                pool = new Pool<DummyClass>(1);
                if(pool == nullptr)
                {
                    return false;
                }

                try
                {
                    poolrf = pool->create();
                }
                catch(e_pool_full)
                {
                    return false;
                }

                return true;
            }

            bool run()
            {
                try
                {
                    pool->destroy(poolrf);
                }
                catch(e_pool_invalid_ref)
                {
                    return false;
                }

                // The reference should now be invalid. Return true if so.
                return poolrf.invalid();
            }

            bool post()
            {
                delete pool;
                pool = 0;
                return true;
            }

            bool postmortem()
            {
                return post();
            }

            ~TestPool_Destroy(){}

        private:
            Pool<DummyClass>* pool;
            pool_ref<DummyClass> poolrf;
    };

    // P-tB165a-h
    class TestPool_Exception : public Test
    {
        public:
            enum FailTestType
            {
                POOL_FULL_ASGN,
                POOL_FULL_CTOR,
                POOL_FULL_ASGN_CPY,
                POOL_FULL_CTOR_CPY,
                POOL_ACC_DELETED_REF,
                POOL_ACC_FOREIGN_REF,
                POOL_DES_DELETED_REF,
                POOL_DES_FOREIGN_REF
            };

            // cppcheck-suppress uninitMemberVar
            explicit TestPool_Exception(FailTestType ex)
            :type(ex){}

            bool pre()
            {
                pool = new Pool<DummyClass>(1);
                if(pool == nullptr)
                {
                    return false;
                }

                try
                {
                    poolrf = pool->create();
                }
                catch(e_pool_full)
                {
                    return false;
                }

                return true;
            }

            bool run()
            {
                switch(type)
                {
                    case POOL_FULL_ASGN:
                    {
                        try
                        {
                            pool_ref<DummyClass> rf2 = pool->create();
                        }
                        catch(e_pool_full)
                        {
                            return true;
                        }
                        return false;
                    }
                    case POOL_FULL_CTOR:
                    {
                        try
                        {
                            pool_ref<DummyClass> rf2(*pool);
                        }
                        catch(e_pool_full)
                        {
                            return true;
                        }
                        return false;
                    }
                    case POOL_FULL_ASGN_CPY:
                    {
                        try
                        {
                            pool_ref<DummyClass> rf2 = pool->create(DummyClass(5,4,3,2,1));
                        }
                        catch(e_pool_full)
                        {
                            return true;
                        }
                        return false;
                    }
                    case POOL_FULL_CTOR_CPY:
                    {
                        try
                        {
                            pool_ref<DummyClass> rf2 = pool->create(DummyClass(5,4,3,2,1));
                        }
                        catch(e_pool_full)
                        {
                            return true;
                        }
                        return false;
                    }
                    case POOL_ACC_DELETED_REF:
                    {
                        pool->destroy(poolrf);
                        try
                        {
                            pool->access(poolrf).alive();
                        }
                        catch(e_pool_invalid_ref)
                        {
                            return true;
                        }
                        return false;
                    }
                    case POOL_ACC_FOREIGN_REF:
                    {
                        Pool<DummyClass> pool2(1);
                        pool_ref<DummyClass> foreignref(pool2);
                        try
                        {
                            pool->access(foreignref).alive();
                        }
                        catch(e_pool_foreign_ref)
                        {
                            return true;
                        }
                        return false;
                    }
                    case POOL_DES_DELETED_REF:
                    {
                        pool->destroy(poolrf);
                        try
                        {
                            pool->destroy(poolrf);
                        }
                        catch(e_pool_invalid_ref)
                        {
                            return true;
                        }
                        return false;
                    }
                    case POOL_DES_FOREIGN_REF:
                    {
                        Pool<DummyClass> pool2(1);
                        pool_ref<DummyClass> foreignref(pool2);
                        try
                        {
                            pool->destroy(foreignref);
                        }
                        catch(e_pool_foreign_ref)
                        {
                            return true;
                        }
                        return false;
                    }
                }
                return false;
            }

            bool post()
            {
                delete pool;
                pool = 0;
                return true;
            }

            bool postmortem()
            {
                return post();
            }

            ~TestPool_Exception(){}

        private:
            FailTestType type;

            Pool<DummyClass>* pool;
            pool_ref<DummyClass> poolrf;
    };

    class TestSuite_Pool : public TestSuite
    {
        public:
            static void load_tests(TestManager*);
        protected:

        private:
    };
}

#endif // POOL_TESTS_HPP_INCLUDED
