/** Pool [PawLIB]
  * Version: 1.0
  *
  * A general-purpose object pool implementation, which offers
  * on-demand initialization, access, and deinitialization of
  * objects with fully front-loaded dynamic allocation.
  *
  * Author(s): Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Media.
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


#ifndef POOL_HPP_INCLUDED
#define POOL_HPP_INCLUDED

#include <cstdint>
#include <exception>
#include <iostream>

//#include <rigid_stack.hpp>
#include "pawlib/flex_stack.hpp"

//Signals and callbacks.
#include "cpgf/gcallbacklist.h"

namespace pawlib
{
    /** Indicates an invalid pool index, such as when the pool is full.
      * We actually use the largest unsigned int32 for this. */
    static const uint32_t INVALID_INDEX = UINT32_MAX;

    template<typename T> class pool_ref;
    template<typename T> class pool_obj;

    class e_pool_full : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Pool is full. Could not initialize new object.";
        }
    };

    class e_pool_foreign_ref : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Cannot access values in pool using foreign reference.";
        }
    };

    class e_pool_invalid_ref : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Cannot access invalid or uninitialized value in pool.";
        }
    };

    class e_pool_reinit : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Cannot reinitialize object.";
        }
    };

    /** A ready-to-use object Pool. Dynamic allocation is front-loaded.*/
    template<typename T>
    // cppcheck-suppress noCopyConstructor
    class Pool
    {
        private:
            // A pool reference must be able to access Pool's private functions.
            friend class pool_ref<T>;

            // Define our pool reference type.
            typedef pool_ref<T> poolref_t;
            // Define our pool object type.
            typedef pool_obj<T> poolobj_t;
            typedef cpgf::GCallbackList<void ()> poolobjsignal_t;

            /// The pointer to the beginning of our pool's chunk of memory.
            poolobj_t* pool_root;
            /// The maximum number of objects in the pool.
            uint32_t pool_size;

            /* The stack of available indexes. */
            FlexStack<uint32_t> index_available;

            /// If failsafe is on, we'll ignore create and access failures.
            bool failsafe;

            void populate_stack()
            {
                for(uint32_t i = 0; i < pool_size; ++i)
                {
                    index_available.push(i);
                }
            }

            /** Find the next open position in the pool.
             * Return INVALID_INDEX if none found. */
            uint32_t find_open()
            {
                // Check for available indexes...
                try
                {
                    // Use the latest one.
                    return index_available.pop();
                }
                // If our stack was empty...
                catch(std::out_of_range)
                {
                    // The pool is full.
                    return INVALID_INDEX;
                }
            }

            poolobjsignal_t* object_signal(uint32_t loc)
            {
                return &(pool_root[loc].signal_deinit);
            }

        public:
            /** Define an empty Pool. */
            Pool()
            :pool_size(0), failsafe(false), pool_root(nullptr)
            {}

            /** Define a new Pool of size n.
              * \param the maximum number of objects in the pool
              * \param whether to throw an exception on create() if pool is full
              */
            Pool(const uint32_t n, bool fs=false)
            :pool_size(n), failsafe(fs)
            {
                /* If the specified size is also the maximum valid integer,
                 * which we reserved for our invalid index marker, use one less.
                 * It is highly unlikely that this subtlty will ever be noticed or
                 * matter to the end-developer, although we'll document it anyway.
                 */
                if(pool_size == INVALID_INDEX)
                {
                    --pool_size;
                }
                // We dynamically allocate all the space up front.
                pool_root = new poolobj_t[pool_size];

                populate_stack();
            }

            /** Create a new object in our pool, using the object's
             * default constructor.
             * \return a pool reference to the new object
             */
            poolref_t create()
            {
                // Try to find space in the pool.
                uint32_t loc = find_open();
                // If the pool is full...
                if(loc == INVALID_INDEX)
                {
                    // If we're in failsafe mode...
                    if(failsafe)
                    {
                        // Return "invalid index" reference.
                        return poolref_t(this);
                    }
                    // Otherwise, throw an exception.
                    throw e_pool_full();
                }

                // Initiate the object.
                pool_root[loc].init();

                // Define and return a new pool reference.
                return poolref_t(this, loc, object_signal(loc));
            }

            /** Create a new object in our pool, using either
             * the object's default or copy constructor. This latter
             * provides access to non-default constructors.
             * i.e. `pool_ref<Foo> rf = pool.create(Foo(5));`
             * \param an optional object to copy from
             * \return a pool reference to the new object
             */
            poolref_t create(const T& cpy)
            {
                // Try to find space in the pool.
                uint32_t loc = find_open();
                // If the pool is full...
                if(loc == INVALID_INDEX)
                {
                    // If we're in failsafe mode...
                    if(failsafe)
                    {
                        // Return "invalid index" reference.
                        return poolref_t(this);
                    }
                    // Otherwise, throw an exception.
                    throw e_pool_full();
                }

                /* Initiate that object using the passed object (i.e. from the
                 * constructor). */
                pool_root[loc].init(cpy);

                // Define and return a new pool reference.
                return poolref_t(this, loc, object_signal(loc));
            }

            /** Provides direct access to an object in the pool via its reference.
              * \param the pool reference to the object in the pool
              * \return the stored object, passed by reference
              */
            T& access(poolref_t& rf)
            {
                // If the reference does not belong to the pool.
                if(rf.pool_ptr != this)
                {
                    // Throw a foreign reference error.
                    throw e_pool_foreign_ref();
                }
                /* Else if the reference points to an invalid index (such as when
                 * the reference was returned from an create() on a full, failsafe
                 * pool. */
                else if(rf.getIndex() == INVALID_INDEX)
                {
                    throw e_pool_invalid_ref();
                }
                // Otherwise, we're good - return the stored object.
                else
                {
                    return pool_root[rf.getIndex()].object;
                }
            }

            /** Deinitialize the object in the pool at the given reference.
              * \param the pool reference to the object to be deinitialized.
              */
            void destroy(poolref_t& rf)
            {
                // If the reference does not belong to the pool.
                if(rf.pool_ptr != this)
                {
                    // Throw a foreign reference error.
                    throw e_pool_foreign_ref();
                }
                /* Else if the reference points to an invalid index (such as when
                 * the reference was returned from an create() on a full, failsafe
                 * pool. */
                else if(rf.getIndex() == INVALID_INDEX)
                {
                    throw e_pool_invalid_ref();
                }
                // Otherwise, we're good - deinitialize the object.
                else
                {
                    try
                    {
                        /* Mark this index as up for grabs. We must do this now,
                        * before the reference is invalidated. */
                        index_available.push(rf.getIndex());
                    }
                    catch(std::length_error)
                    {
                        // Just don't bother pushing.
                    }

                    // Deinitialize the object.
                    pool_root[rf.getIndex()].deinit();
                    /* References are invalidated via the signal dispatched from
                     * pool_obj<T>::deinit(). */
                }
            }

            /** Returns the size of the pool in bytes. Does not count the
              * pool's internal metadata, which is negligible in size.*/
            uint32_t size()
            {
                /* The pool's size in memory is simply the size of a pool object
                 * times the number of objects in the pool. */
                return (sizeof(poolobj_t)*pool_size);
            }

            ~Pool()
            {
                // Deallocate and destroy the entire pool.
                delete[] pool_root;
            }
    };

    /** References an object in a Pool. Should always be used as a constant.*/
    template<typename T>
    class pool_ref
    {
        // The Pool class must be able to access private members in the reference.
        friend class Pool<T>;
        private:
            // Define our pool object type.
            typedef pool_obj<T> poolobj_t;
            // Define our pool type.
            typedef Pool<T> pool_t;
            typedef cpgf::GCallbackList<void ()> poolobjsignal_t;

            /** We store the pointer to the pool, first to validate that the
             * reference belongs to a particular Pool, and second to be able
             * to get an object's destroy signal. */
            pool_t* pool_ptr;

            /** The index of the referenced object in the pool. Although it is
              * possible to access and modify this directly from a friend class
              * (such as Pool), the getIndex() and invalidate() functions should
              * be used instead. */
            uint32_t index;

            /** Create a new pool reference. Intended to only be called from within
              * the pool class.
              * \param the pointer to the pool class
              * \param the index of the referenced object in the pool
              * \param the object destroy signal to connect to
              */
            pool_ref(pool_t* pool, uint32_t i, poolobjsignal_t* signal)
            :pool_ptr(pool), index(i)
            {
                signal->add(this, &pool_ref<T>::invalidate);
            }

            /** Sets the reference's index to INVALID. */
            void invalidate()
            {
                disconnect();
                index = INVALID_INDEX;
            }

            void disconnect()
            {
                if(pool_ptr != nullptr && index != INVALID_INDEX)
                {
                    pool_ptr->object_signal(index)->remove(this, &pool_ref<T>::invalidate);
                }
            }

            /** Returns the index for the reference. */
            //cppcheck-suppress unusedPrivateFunction
            uint32_t getIndex()
            {
                return index;
            }



        public:
            /** Create a new, empty pool reference. This is always invalid, and
              * will cause Pool to throw a "foreign reference" error.
              * PROPOSED: Should we remove this? */
            pool_ref()
            :pool_ptr(nullptr), index(INVALID_INDEX)
            {}

            /** Create a new invalid pool reference.
              * \param the pointer to the owning pool class
              */
            explicit pool_ref(pool_t* pool)
            :pool_ptr(pool), index(INVALID_INDEX)
            {}

            /** Copy constructor.
              * \param the reference to copy
              */
            pool_ref(const pool_ref<T>& cpy)
            :pool_ptr(cpy.pool_ptr), index(cpy.index)
            {
                if(pool_ptr && index != INVALID_INDEX)
                {
                    pool_ptr->object_signal(index)->add(this, &pool_ref<T>::invalidate);
                }
            }

            void operator=(const pool_ref<T>& cpy)
            {
                disconnect();
                pool_ptr = cpy.pool_ptr;
                index = cpy.index;
                if(index != INVALID_INDEX)
                {
                   pool_ptr->object_signal(index)->add(this, &pool_ref<T>::invalidate);
                }
            }

            /** Returns true if the pool reference is invalid. A full, failsafe pool
              * will return an invalid pool reference when attempting to initialize
              * a new object.
              * \return true if invalid, else false
              */
            bool invalid()
            {
                return (index == INVALID_INDEX);
            }

            ~pool_ref(){}
    };

    /** An object in a Pool. Should NOT be used directly. */
    template<typename T>
    class pool_obj
    {
        friend class Pool<T>;
        private:
            pool_obj<T>()
            :live(false)
            {}

            /* NOTE: The presence of 'live' adds a maximum of 8 bytes over the base
             * type T, due to padding. */

            typedef cpgf::GCallbackList<void ()> poolobjsignal_t;
            poolobjsignal_t signal_deinit;

            /// Marks whether the object is initialized or not.
            bool live;

            /// The object itself.
            T object;

            /** Initialize the object using its default constructor.*/
            //cppcheck-suppress unusedPrivateFunction
            void init()
            {
                // If the object is already live...
                if(live)
                {
                    // Throw an error.
                    throw e_pool_reinit();
                }

                // Mark the object as live.
                live = true;
                // Use the object's default constructor.
                object = T();
            }

            /** Initialize the object using its copy constructor.
              * \param the object to initialize the new object with
              */
            //cppcheck-suppress unusedPrivateFunction
            void init(const T& cpy)
            {
                // If the object is already live...
                if(live)
                {
                    // Throw an error.
                    throw e_pool_reinit();
                }

                // Mark the object as live.
                live = true;
                // Use the object's copy constructor.
                object = T(cpy);
            }

            /** Deinitialize the object. */
            //cppcheck-suppress unusedPrivateFunction
            void deinit()
            {
                // Order all the references to invalidate.
                signal_deinit.dispatch();

                // Explicitly call the object's destructor.
                object.~T();

                // Mark the object as uninitialized (not live).
                live = false;
            }

        public:
            /* Our constructors are all private, to prevent instantiation
             * of pool_obj outside of the friend Pool class.*/

            /// Destructor
            ~pool_obj(){}
    };
}

#endif // POOL_HPP_INCLUDED
