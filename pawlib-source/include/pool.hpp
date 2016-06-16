#ifndef POOL_HPP_INCLUDED
#define POOL_HPP_INCLUDED

#include <cstdint>
#include <exception>

namespace pawlib
{
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
    class Pool
    {
        private:
            // A pool reference must be able to access Pool's private functions.
            friend class pool_ref<T>;

            // Define our pool reference type.
            typedef pool_ref<T> poolref_t;
            // Define our pool object type.
            typedef pool_obj<T> poolobj_t;

            /** Indicates an invalid pool index, such as when the pool is full.
              * We actually use the largest unsigned int32 for this. */
            const uint32_t INVALID_INDEX = UINT32_MAX;

            /// The pointer to the beginning of our pool's chunk of memory.
            poolobj_t* pool_root;
            /// The maximum number of objects in the pool.
            uint32_t pool_size;

            /// If failsafe is on, we'll ignore alloc and access failures.
            bool failsafe;

            /** Find the next open position in the pool.
             * Return INVALID_INDEX if none found. */
            uint32_t find_open()
            {
                /* We use a sequential search [worst case: O(n)]. Because our search
                 * criteria (pool_root[live]) is never guarenteed to be sorted. */
                for(uint32_t i = 0; i < pool_size; ++i)
                {
                    // As soon as we find a "non-live" pool_obj, return its index.
                    if(!pool_root[i].live)
                    {
                        return i;
                    }
                }
                /* If we found nothing, return INVALID_INDEX.*/
                return INVALID_INDEX;
            }

            /** Create a new object in our pool. This version of alloc is intended
             * to only be called by the pool reference constructor which accepts
             * a pool as an argument, for a one-step alloc.
             * i.e. `pool_ref<Foo> rf(pool);`
             * \param the location to initialize at.
             */
            void alloc(uint32_t loc)
            {
                // If the pool is full...
                if(loc == INVALID_INDEX)
                {
                    // If we're in failsafe mode...
                    if(failsafe)
                    {
                        // The calling reference is already "invalid index". Do nothing.
                        return;
                    }
                    // Otherwise, throw an exception.
                    throw e_pool_full();
                }
                // Initiate that object.
                pool_root[loc].init();
            }

            /** Create a new object in our pool using the copy constructor.
             * This version of alloc is intended to only be called by the pool
             * reference constructor which accepts a pool as an argument, for a
             * one-step alloc.
             * i.e. `pool_ref<Foo> rf(pool, Foo(5));`
             * \param the location to initialize at.
             */
            void alloc(uint32_t loc, const T& cpy)
            {
                // If the pool is full...
                if(loc == INVALID_INDEX)
                {
                    // If we're in failsafe mode...
                    if(failsafe)
                    {
                        // The calling reference is already "invalid index". Do nothing.
                        return;
                    }
                    // Otherwise, throw an exception.
                    throw e_pool_full();
                }
                // Initiate that object using the copy object.
                pool_root[loc].init(cpy);
            }

        public:
            /** Define a new Pool of size n.
              * \param the maximum number of objects in the pool
              * \param whether to throw an exception on alloc() if pool is full
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
            }

            /** Create a new object in our pool, using the object's
             * default constructor.
             * \return a pool reference to the new object
             */
            poolref_t alloc()
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
                        return poolref_t(pool_root, loc);
                    }
                    // Otherwise, throw an exception.
                    throw e_pool_full();
                }

                // Initiate the object.
                pool_root[loc].init();

                // Define and return a new pool reference.
                return poolref_t(pool_root, loc);
            }

            /** Create a new object in our pool, using either
             * the object's default or copy constructor. This latter
             * provides access to non-default constructors.
             * i.e. `pool_ref<Foo> rf = pool.alloc(Foo(5));`
             * \param an optional object to copy from
             * \return a pool reference to the new object
             */
            poolref_t alloc(const T& cpy)
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
                        return poolref_t(pool_root, loc);
                    }
                    // Otherwise, throw an exception.
                    throw e_pool_full();
                }

                /* Initiate that object using the passed object (i.e. from the
                 * constructor). */
                pool_root[loc].init(cpy);

                // Define and return a new pool reference.
                return poolref_t(pool_root, loc);
            }

            /** Provides direct access to an object in the pool via its reference.
              * \param the pool reference to the object in the pool
              * \return the stored object, passed by reference
              */
            T& access(poolref_t rf)
            {
                // If the reference does not belong to the pool.
                if(rf.pool_root != pool_root)
                {
                    // Throw a foreign reference error.
                    throw e_pool_foreign_ref();
                }
                /* Else if the reference points to an invalid index (such as when
                 * the reference was returned from an alloc() on a full, failsafe
                 * pool. */
                else if(rf.index == INVALID_INDEX)
                {
                    throw e_pool_invalid_ref();
                }
                // Otherwise, we're good - return the stored object.
                else
                {
                    return pool_root[rf.index].object;
                }
            }

            /** Deinitialize the object in the pool at the given reference.
              * \param the pool reference to the object to be deinitialized.
              */
            void dealloc(poolref_t& rf)
            {
                // Deinitialize the object.
                pool_root[rf.index].deinit();
                // Invalidate the reference.
                rf.index = INVALID_INDEX;
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

            /** We store the pointer to the pool root to validate that the
             * reference belongs to a particular Pool. */
            const poolobj_t* pool_root;

            /// The index of the referenced object in the pool.
            uint32_t index;

            /** Create a new pool reference. Intended to only be called from within
              * the pool class.
              * \param the root pointer of the pool class
              * \param the index of the referenced object in the pool
              */
            pool_ref(poolobj_t* root, uint32_t i)
            :pool_root(root), index(i)
            {}

            void invalidate()
            {
                index = pool_t::INVALID_INDEX;
            }

        public:
            /** Create a new, empty pool reference. This is always invalid, and
              * will cause Pool to throw a "foreign reference" error.
              * PROPOSED: Should we remove this? */
            pool_ref()
            :pool_root(nullptr),index(pool_t::INVALID_INDEX)
            {}

            /** Create a new pool reference to a newly initialized object in the
              * passed Pool. Initializes the object with its default constructor.
              * \param the pool to initialize the object in
              */
            pool_ref(pool_t& pool)
            :pool_root(pool.pool_root), index(pool.find_open())
            {
                pool.alloc(index);
            }

            /** Create a new pool reference to a newly initialized object in the
              * passed Pool. Uses the passed object to initialize the new object
              * with its copy constructor, thereby providing access to the object's
              * non-default constructors.
              * \param the pool to initialize the object in
              * \param the object to copy to the new object in the pool
              */
            pool_ref(pool_t& pool, const T& cpy)
            :pool_root(pool.pool_root), index(pool.find_open())
            {
                pool.alloc(index, cpy);
            }

            /** Returns true if the pool reference is invalid. A full, failsafe pool
              * will return an invalid pool reference when attempting to initialize
              * a new object.
              * \return true if invalid, else false
              */
            bool invalid()
            {
                // Return true if the index matches the pool's invalid index constant.
                return (index == pool_t::INVALID_INDEX);
            }

            ~pool_ref(){}
    };

    /** An object in a Pool. Should NOT be used directly. */
    template<typename T>
    class pool_obj
    {
        friend class Pool<T>;
        private:
            /* NOTE: The presence of 'live' adds a maximum of 8 bytes over the base
             * type T, due to padding. */

            /// Marks whether the object is initialized or not.
            bool live;

            /// The object itself.
            T object;

            /** Initialize the object using its default constructor.*/
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
            void deinit()
            {
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
