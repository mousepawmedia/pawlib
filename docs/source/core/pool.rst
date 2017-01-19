Pool
###################################

What is Pool?
===================================

Pool is a generic implementation of the object pool design pattern. It can
store up to approximately 4 billion objects of the same type. All dynamic
allocation is performed up front.

Performance Considerations
--------------------------------

At present, Pool is actually a little *slower* than dynamic allocation on some
modern systems, due to some overhead when deleting an object. While future
versions may allevitate this, it is important to note that Pool's main advantage
is in providing safer dynamic memory access.

It is possible that Pool may offer better performance in environments where
dynamic allocation is extremely expensive. Running a comparative benchmark
between Goldilocks tests ``P-tB161a`` and ``P-tB161b`` will indicate whether
there exist any mid-execution performance gains from using Pool in your
particular environment.

Technical Limitations
--------------------------------

Pool can store a maximum of 4,294,967,294 objects. This is because it uses
32-bit unsigned integers for internal indexing, with the largest value
reserved as  ``INVALID_INDEX``. The limit is calculated as follows.

``2^{32} - 2 = 4,294,967,294``

Creating a Pool
====================================

A ``Pool`` object can be created by whatever means is convenient. It handles
its own dynamic allocation internally when first created.

When the Pool is created, you must define its type and maximum size.

..  code-block:: c++

    // Both of these methods are valid...

    // Define a pool storing up to 500 Particle objects.
    Pool<Particle> particles(500);

    // Define a pool storing up to 100 Enemy objects.
    Pool<Enemy>* baddies = new Pool<Enemy>(500);

Failsafe
------------------------------------

By default, Pool will throw an ``e_pool_full`` exception if you try to
add an object when the Pool is full. However, there are situations where
you may not want this behavior. You can initialize Pool in **failsafe mode**
to have Pool fail silently in this situation.

.. NOTE:: Even in failsafe mode, Pool will still throw its other exceptions.

..  code-block:: c++

    // Define a 500-object Particle pool in failsafe mode.
    Pool<Particle> pool(500, true);

Failsafe mode does introduce another situation where an exception may be
thrown. If the Pool is full, adding an object will return an invalid reference.
One must either ensure that the reference is valid before using it, or catch
the ``e_invalid_ref`` exception on ``Pool::access()`` and ``Pool::destroy()``.

Using Pool
====================================

Pool References
-------------------------------------

One of the main features of Pool is its safety. When used properly, you don't
run the risk of memory errors, segmentation faults, or other undefined behaviors
generally associated with dynamic allocation and pointers.

Instead of pointers, Pool offers pool references (``pool_ref``). You can think
of these as "keys" - you cannot access anything in a Pool without the
appropriate ``pool_ref``.

Each pool reference is associated with a particular object in the Pool. When
the object is destroyed, all the references to that object are invalidated
to prevent undefinied behavior.

..  IMPORTANT:: The most important thing to remember is that you should
    **never use pointers** to access objects within the Pool.

Each reference is also directly associated with a single Pool. You cannot use
a reference associated with one Pool to access an object in another Pool, even
if both Pools are initialized identically.

Invalid References
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A reference is invalid if:

* It refers to a destroyed object.
* It has only been created with its default constructor, with no assignment
  to it from ``Pool::create()``. (It will also be considered Foreign to every
  Pool.)
* It was returned from ``Pool::create`` in failsafe mode, and the pool was full.

You can check if a reference is invalid by using the ``pool_ref::invalid()``
function.

..  code-block:: c++

    // This would be an invalid reference, since no object was created.
    pool_ref<Foo> rf;

    // This would return true.
    rf.invalid();

Object Compatibility
--------------------------------------

To store an object in Pool, it **must** have a default constructor and a copy
constructor. The copy constructor is used to provide indirect access to all
the other constructors for the object.

Adding Objects
------------------------------------

There are several ways to add a new object to the pool. In each one, the
important thing is that you wind up with a ``pool_ref`` object. Watch this!
It is not possible to access or destroy an object within the Pool without its
reference.

All of the following methods are valid...

..  code-block:: c++

    /* Foo contains a default constructor, a copy constructor, and a
     * constructor that accepts an integer. */
    class Foo;
    Pool<Foo> pool(10);

    try
    {
        pool_ref<Foo> rf1 = pool.create();
        pool_ref<Foo> rf2 = pool.create(Foo(5));
        pool_ref<Foo> rf3(pool);
        pool_ref<Foo> rf4(pool, Foo(42));
    }
    catch(e_pool_full)
    {
        // Handle the exception.
    }

Let's break those down further.

The first method is to define a ``pool_ref`` object, and assign the result
of ``Pool::create`` function to it.

..  code-block:: c++

    // Uses default constructor.
    pool_ref<Foo> rf1 = pool.create();
    // Uses copy constructor to indirectly access another constructor.
    pool_ref<Foo> rf2 = pool.create(Foo(5));

You can also create the object by passing the Pool directly into the
``pool_ref``'s constructor. This calls Pool.create() implicitly, so if
the Pool is not in failsafe mode, you still need to watch out for the
``e_pool_full`` exception.


..  code-block:: c++

    // Uses default constructor.
    pool_ref<Foo> rf3(pool);
    // Uses copy constructor to indirectly access another constructor.
    pool_ref<Foo> rf4(pool, Foo(42));

Accessing Objects
-------------------------------------

Objects are accessed within a Pool using the ``pool_ref`` you got when
creating the object.

..  code-block:: c++

    // The class Foo has a function "say()"
    class Foo;
    Pool<Foo> pool(10);
    pool_ref<Foo> rf1 = pool.create();

    /* We use the pool reference to access the object. Then we can
     * interact with the object directly. */
    pool.access(rf1).say();

The ``Pool.access()`` function can throw two different exceptions.

The most common is ``e_pool_invalid_ref``. This is thrown when an invalid
pool reference is passed.

..  code-block:: c++

    Pool<Foo> pool(10);
    pool_ref<Foo> emptyRef;
    pool.access(emptyRef); // throws e_pool_invalid_ref

The other is ``e_pool_foreign_ref``, which is thrown
if a pool reference that belongs to another pool is passed.

..  code-block:: c++

    Pool<Foo> pool(10);
    Pool<Foo> otherPool(10);
    pool_ref<Foo> foreignRef = otherPool.create();
    pool.access(foreignRef); // throws e_pool_foreign_ref

Destroying Objects
---------------------------------------

When you're done with an object, you can remove it from the Pool. This frees
up space for another object to be created in its place later. To destroy
an object, simply pass a reference to it into ``Pool::destroy()``.

It's important to note that if you have multiple references to the same
object, they will all be invalidated when the object is destroyed.

..  code-block:: c++

    Pool<Foo> pool(10);
    pool_ref<Foo> thing(pool);
    pool_ref<Foo> copyOfThing = thing;

    // We destroy the object.
    pool.destroy(thing);

    pool.access(copyOfThing); // This will now throw e_pool_invalid_ref

``Pool::destroy()`` can throw ``e_pool_invalid_ref`` or ``e_pool_foreign_ref``
under the same circumstances as with ``Pool::access()``.

Exceptions
=====================================

``e_pool_full``
--------------------------------------

**Cause:** The Pool is full.

**Thrown By:** ``Pool::create()`` (in non-failsafe mode)

``e_pool_invalid_ref``
--------------------------------------

**Cause:** An invalid reference was used.

**Thrown By:** ``Pool::access()``, ``Pool::destroy()``

``e_pool_foreign_ref``
--------------------------------------

**Cause:** A reference from another pool was used, or a reference created
with its default constructor and not assigned to by ``Pool::create()``.

**Thrown By:** ``Pool::access()``, ``Pool::destroy()``

``e_pool_reinit``
--------------------------------------

**Cause:** Attempting to reinitialize an an object that already exists.

**Thrown By:** Internal - shouldn't happen.

Examples
=========================================

Enemy Pool
-----------------------------------------

..  code-block:: c++

    // Let's define an Enemy class for our example.
    class Enemy
    {
        Enemy();
        Enemy(const Enemy& cpy);
        Enemy(std::string);
        void attack();
        void hurt(int);
        void die();
        int health;
        ~Enemy();
    };

    // Create our pool.
    Pool<Enemy> baddies(500);

    // This function would return the damage from the player's move.
    int getPlayerMove();

    void fightSkeleton()
    {
        /* Since our pool is not in failsafe mode, we must be on the lookout
         * for the `e_pool_full` exception that create() can throw.*/
        try
        {
            /* Create a new Enemy object in the pool. This uses Enemy's copy
             * constructor to give access to the constructor accepting a string. */
            pool_ref<Enemy> skeleton = pool.create(Enemy("Skeleton"))
        }
        catch(e_pool_full)
        {
            // We couldn't create the enemy, so just quit.
            return;
        }

        while(baddies.access(skeleton).health > 0)
            // We order our skeleton to attack the player.
            baddies.access(skeleton).attack();
            // The player hurts the skeleton.
            baddies.access(skeleton).hurt(getPlayerMove());
        }

        // Make the skeleton character die.
        baddies.access(skeleton).die();
        // Destroy the skeleton object in the pool.
        baddies.destroy(skeleton);
    }

Particle System
--------------------------------------------

..  code-block:: c++

    class Particle
    {
        Particle();
        Particle(const Particle& cpy);
        Particle(int, int);
        emit();
    };

    /* For this example, we'll define a failsafe pool, so we don't have to
     * try/catch our creation of objects. */
    Pool<Particle> particles(2000, true);

    // Define a particle in the pool using its default constructor.
    pool_ref<Particle> particle(particles);

    void particleEffect(int type, int speed, int count)
    {
        /* One design pattern might be to generate a lot of particles in a loop.
         * In this example, we'll store them in a FlexArray. */
        FlexArray<pool_ref<Particle>> smoke_effect;

        for(int i=0; i<count; ++i)
        {
            /* Define a particle in the pool using its copy constructor, which
             * gives us access to the constructor that accepts an integer. */
            smoke_effect.push(pool_ref<Particle>(particles, Particle(type, speed));
        }

        /* Let's emit our particles. */
        for(int i=0; i<count; ++i)
        {
            // Ensure the particle exists before emitting it.
            if(!smoke_effect[i].invalid())
            {
                particles.access(smoke_effect[i]).emit();
            }
        }

        /* Destroy the particles when we're done. */
        for(int i=0; i<count; ++i)
        {
            // Ensure the particle exists before destroying it.
            if(!smoke_effect[i].invalid())
            {
                particles.destroy(smoke_effect[i]);
            }
        }
    }
