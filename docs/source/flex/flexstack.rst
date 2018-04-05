FlexStack
###################################

What is FlexStack?
===================================

FlexStack is a flexibly-sized stack similar to ``std::stack<T, std::vector>``.
Internally, it is implemented as a circular buffer deque, guaranteed to be
stored in contiguous memory, thereby helping to avoid or minimize cache misses.

While we aim to create a high-performance data structure, our top priority is
in giving the user easy *control* over the tradeoffs between CPU performance,
memory, and cache misses.

Performance
------------------------------------

FlexStack is slightly slower than the typical ``std::stack``, but this is
acceptable because of the inherent difference between Flex and ``std::deque``;
while Flex guarantees storage in contiguous memory, ``std::deque`` does not.
As a result, we instead must compare against ``std::stack<T, std::vector>``.

FlexStack is usually as fast as, or faster than, ``std::stack<T, std::vector>``.
Here's how FlexStack ranks against the GCC implementation of
``std::stack``, with ``std::vector`` as its underlying container...

- Pushing (to back) is as fast.
- Popping (from back) is faster.
- Accessing is at least as fast.

If general performance is more important to you than contiguous memory, see
``SpeedStack``.

Comparison to ``std::stack``
-------------------------------------

FlexStack offers largely the same functionality as ``std::stack``. However,
it is not intended to feature-identical. Some functionality hasn't been
implemented yet, and we may not include some other features to leave room
for future optimization and experimentation.

* FlexStack does not offer iterators. This *may* be added in the future.
* You cannot change the underlying data structure. Our base class is where
  most of the heavy lifting occurs.
* Some advanced modifiers haven't been implemented yet.

Technical Limitations
--------------------------------------

FlexStack can store a maximum of 4,294,967,294 objects. This is because it uses
32-bit unsigned integers for internal indexing, with the largest value
reserved as  ``INVALID_INDEX``. The limit is calculated as follows.

``2^{32} - 2 = 4,294,967,294``

Using FlexStack
=========================================

Including FlexStack
---------------------------------------

To include FlexStack, use the following:

..  code-block:: c++

    #include "pawlib/flex_stack.hpp"

Creating a FlexStack
------------------------------------------

A ``FlexStack`` object is created by whatever means is convenient. It handles
its own dynamic allocation for storing its elements.

When the FlexStack is first created, you must specify the type of its elements.

..  code-block:: c++

    // Both of these methods are valid...
    FlexStack<int> dish_sizes;

    FlexStack<int>* dish_sizes = new FlexStack<int>;

Resize Factor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To minimize the number of CPU cycles used on reallocation, when we run out of
space in the data structure, on the next insertion, we allocate more space than
we immediately need. This *resize factor* is controllable.

By default, when the FlexStack resizes, it **doubles** its capacity (``n * 2``).
This provides the best general performance. However, if you want to preserve
memory at a small performance cost, you can switch to a resize factor of
``n * 1.5`` (internally implemented as ``n + n / 2``).

To switch to the ``1.5`` factor, include ``false`` as the second template
parameter (``factor_double``).

..  code-block:: c++

    FlexStack<int, false> i_resize_slower;

Reserve Size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We can specify the initial size (in elements) of the FlexStack in the
constructor.

..  code-block::

    FlexStack<int>* temps_high = new FlexStack<int>(100);

..  NOTE:: The FlexStack will always have minimum capacity of 2.

Adding Elements
------------------------------------------

Stacks are "Last-In-First-Out"; you insert to the end (or "back"), and remove
from the back.

``push()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We add new elements to the stack with a "push" to the back using the ``push()``
function. The alias ``push_back()`` is also provided for convenience.
This function has a performance of ``O(1)``.

..  code-block:: c++

    FlexStack<int> dish_sizes;
    dish_sizes.push(22);
    dish_sizes.push(18);
    dish_sizes.push(18);
    dish_sizes.push_back(12); // we can also use push_back()
    // The FlexStack is now [22, 18, 18, 12]

Accessing Elements
-------------------------------------------

``at()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``at()`` allows you to access the value at a given stack index.

..  code-block:: c++

    FlexStack<string> albums;

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    albums.at(1);
    // This output yields "Comatose"

Alternatively, you can use the ``[]`` operator to access a value.

..  code-block:: c++

    // Using the stack from above...

    albums[2];
    // This output yields "Fireproof"

``peek()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``peek()`` allows you to access the next element in the stack without modifying
the data structure.

..  code-block:: c++

    FlexStack<string> albums;

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    albums.peek();

    // This output yields "Fireproof"
    // The stack remains ["End of Silence", "Comatose", "Fireproof"]

Removing Elements
-------------------------------------------

In a stack, we typically remove and return elements from the end, or "back" of
the stack. Imagine a stack of dishes - the last one added is the first one
removed (ergo "last-in-first-out").

``clear()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``clear()`` removes all the elements in the FlexStack.

..  code-block:: c++

    FlexStack<int> pie_sizes;

    pie_sizes.push(18);
    pie_sizes.push(18);
    pie_sizes.push(15);

    // I ate everything...
    pie_sizes.clear();

    // The FlexStack is now empty.

This function always returns true, and will never throw an exception
(**no-throw guarantee**).

``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``erase()`` allows you to delete elements in a stack in a given range.
Remaining values are shifted to fill in the empty slot. This function has a
worst-case performance of ``O(n/2)``.

..  code-block:: c++

    FlexStack<string> albums;

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    // The stack is currently ["End of Silence", "Comatose", "Fireproof"]

    albums.erase(0, 1);
    // The first number in the function call is the lower bound
    // The second number is the upper bound.
    // The stack is now simply ["Fireproof"]

If any of the indices are too large, this function will return ``false``.
Otherwise, it will return true. It never throws exceptions
(**no-throw guarantee**).

``pop()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``pop()`` returns the last value in an stack, and then removes it from the data
set. The alias ``pop_back()`` is also provided. This function has a
performance of ``O(1)``.

..  code-block:: c++

    FlexStack<int> dish_sizes;

    // We'll push some values for our example
    dish_sizes.push(22);
    dish_sizes.push(18);
    dish_sizes.push(12);

    // The stack is currently [22, 18, 12]

    dish_sizes.pop();
    // Returns 12. The stack is now [22, 18]

..  WARNING:: If the stack is empty, this function will throw the exception
    ``std::out_of_range``.

Size and Capacity Functions
-------------------------------------------

``getCapacity()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``getCapacity()`` returns the total number of elements that can be stored in
the FlexStack without resizing.

..  code-block:: c++

    FlexStack<int> short_term_memory;

    short_term_memory.getCapacity();
    // Returns 8, the default size.

``getLength()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``getLength()`` allows you to check how many elements are currently
in the FlexStack.

..  code-block:: c++

    FlexStack<string> albums;

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    albums.getLength();
    // The function will return 3

``isEmpty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``isEmpty()`` returns true if the FlexStack is empty, and false if it contains
values.

..  code-block:: c++

    FlexStack<string> albums;

    albums.isEmpty();
    // The function will return true

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    albums.isEmpty();
    // The function will return false


``isFull()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``isFull()`` returns true if the FlexStack is full to the current capacity
(before resizing), and false otherwise.

..  code-block:: c++

    FlexStack<int> answers;

    answers.isFull();
    // The function will return false

    // Push values until we are full, using the isFull() function to check.
    while(!answers.isFull())
    {
        answers.push(42);
    }

``reserve()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can use ``reserve()`` to resize the FlexStack to be able to store the given
number of elements. If the data structure is already equal to or larger than
the requested capacity, nothing will happen, and the function will
return ``false``.

..  code-block:: c++

    FlexStack<std::string> labors_of_hercules;

    // Reserve space for all the elements we plan on storing.
    labors_of_hercules.reserve(12);

    labors_of_hercules.getCapacity();
    // Returns 12, the requested capacity.

After reserving space in an existing FlexStack, it can continue to resize.

This function is effectively identical to specifying a size at instantiation.

``shrink()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can use ``shrink()`` function to resize the FlexStack to only be large
enough to store the current number of elements in it. If the shrink is
successful, it wil return ``true``, otherwise it will return ``false``.

..  code-block:: c++

    FlexStack<int> plate_collection;

    for(int i = 0; i < 100; ++i)
    {
        plate_collection.push(i);
    }

    plate_collection.getCapacity();
    // Returns 128, because FlexStack is leaving room for more elements.

    // Shrink to only hold the current number of elements.
    plate_collection.shrink();

    plate_collection.getCapacity();
    // Returns 100, the same as the number of elements.

After shrinking, we can continue to resize as new elements are added.

..  NOTE:: It is not possible to shrink below a capacity of 2.