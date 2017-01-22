/** Tests for PawSort[PawLIB]
  * Version: 1.0
  *
  * Author(s): Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Games.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef POOL_TESTS_HPP_INCLUDED
#define POOL_TESTS_HPP_INCLUDED

#include <new>

#include "pawlib/flex_array.hpp"
#include "pawlib/goldilocks.hpp"
#include "pawlib/pool.hpp"

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

            testdoc_t get_title()
            {
                return "Pool: Create & Destroy (Allocation)";
            }

            testdoc_t get_docs()
            {
                return "Allocate and deallocate 1000 Dummy objects the old fashioned way.";
            }

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

            testdoc_t get_title()
            {
                return "Pool: Create & Destroy (Pool)";
            }

            testdoc_t get_docs()
            {
                return "Create a 1000-object Dummy object pool, then create & destroy 1000 objects in it three times.";
            }

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
                        catch(e_pool_foreign_ref)
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
            enum TestPoolCreateMode
            {
                DFLT,
                COPY,
                DFLT_FAILSAFE,
                COPY_FAILSAFE
            };

            // cppcheck-suppress uninitMemberVar
            explicit TestPool_Create(TestPoolCreateMode mode)
            {
                switch(mode)
                {
                    case DFLT:
                    {
                        title = "Pool: Create by Assignment, Default";
                        docs = "Create a new object in a pool using pool_ref assignment and the object's default constructor.";
                        copyconst = false;
                        failsafe = false;
                        break;
                    }
                    case COPY:
                    {
                        title = "Pool: Create by Assignment, Copy";
                        docs = "Create a new object in a pool using pool_ref assignment and the object's copy constructor.";
                        copyconst = true;
                        failsafe = false;
                        break;
                    }
                    case DFLT_FAILSAFE:
                    {
                        title = "Pool: Create by Assignment, Default Failsafe";
                        docs = "Create a new object in a failsafe pool using pool_ref assignment and the object's default constructor.";
                        copyconst = false;
                        failsafe = true;
                        break;
                    }
                    case COPY_FAILSAFE:
                    {
                        title = "Pool: Create by Constructor, Default Failsafe";
                        docs = "Create a new object in a failsafe pool using the pool_ref constructor and the object's default constructor.";
                        copyconst = true;
                        failsafe = true;
                        break;
                    }
                }
            }

            testdoc_t get_title()
            {
                return title;
            }

            testdoc_t get_docs()
            {
                return docs;
            }

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
                    if(copyconst)
                    {
                        pool_ref<DummyClass> rf = pool->create(DummyClass(5,4,3,2,1));
                        poolrf = rf;
                    }
                    else
                    {
                        pool_ref<DummyClass> rf = pool->create();
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
            bool copyconst;
            bool failsafe;
            Pool<DummyClass>* pool;
            pool_ref<DummyClass> poolrf;

            testdoc_t title;
            testdoc_t docs;
    };

    // P-tB163
    class TestPool_Access : public Test
    {
        public:
            // cppcheck-suppress uninitMemberVar
            TestPool_Access(){}

            testdoc_t get_title()
            {
                return "Pool: Access Object";
            }

            testdoc_t get_docs()
            {
                return "Access an object inside the pool.";
            }

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

            testdoc_t get_title()
            {
                return "Pool: Destroy Object";
            }

            testdoc_t get_docs()
            {
                return "Destroy an object inside the pool.";
            }

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
                POOL_FULL_ASGN_CPY,
                POOL_ACC_DELETED_REF,
                POOL_ACC_FOREIGN_REF,
                POOL_DES_DELETED_REF,
                POOL_DES_FOREIGN_REF
            };

            // cppcheck-suppress uninitMemberVar
            explicit TestPool_Exception(FailTestType ex)
            :type(ex)
            {
                switch(type)
                {
                    case POOL_FULL_ASGN:
                    {
                        title = "Pool: (Exception) Full Pool Create Assignment w/ Default";
                        docs = "Throw and Catch e_pool_full from pool_ref assignment using the object's default constructor.";
                        break;
                    }
                    case POOL_FULL_ASGN_CPY:
                    {
                        title = "Pool: (Exception) Full Pool Create Constructor w/ Default";
                        docs = "Throw and Catch e_pool_full from pool_ref constructor using the object's default constructor.";
                        break;
                    }
                    case POOL_ACC_DELETED_REF:
                    {
                        title = "Pool: (Exception) Access w/ Deleted Ref";
                        docs = "Throw and Catch e_pool_invalid_ref from access using deleted reference.";
                        break;
                    }
                    case POOL_ACC_FOREIGN_REF:
                    {
                        title = "Pool: (Exception) Access w/ Foreign Ref";
                        docs = "Throw and Catch e_pool_invalid_ref from access using foreign reference.";
                        break;
                    }
                    case POOL_DES_DELETED_REF:
                    {
                        title = "Pool: (Exception) Destroy w/ Deleted Ref";
                        docs = "Throw and Catch e_pool_invalid_ref from destroy using deleted reference.";
                        break;
                    }
                    case POOL_DES_FOREIGN_REF:
                    {
                        title = "Pool: (Exception) Destroy w/ Foreign Ref";
                        docs = "Throw and Catch e_pool_invalid_ref from destroy using foreign reference.";
                        break;
                    }
                }
            }

            testdoc_t get_title()
            {
                return title;
            }

            testdoc_t get_docs()
            {
                return title;
            }

            bool pre()
            {
                pool = new Pool<DummyClass>(1);
                if(pool == nullptr)
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
                        pool_ref<DummyClass> poolrf = pool->create();

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
                    case POOL_FULL_ASGN_CPY:
                    {
                        pool_ref<DummyClass> poolrf = pool->create();

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
                        pool_ref<DummyClass> poolrf = pool->create();
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

                        pool_ref<DummyClass> foreignref = pool2.create();
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
                        pool_ref<DummyClass> poolrf = pool->create();
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
                        pool_ref<DummyClass> foreignref = pool2.create();
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

            testdoc_t title;
            testdoc_t docs;
    };

    class TestSuite_Pool : public TestSuite
    {
        public:
            explicit TestSuite_Pool(){}

            void load_tests();

            testdoc_t get_title()
            {
                return "PawLIB: Pool Tests";
            }

            ~TestSuite_Pool(){}
    };
}

#endif // POOL_TESTS_HPP_INCLUDED
