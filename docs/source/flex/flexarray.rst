FlexArray
###################################

What is FlexArray?
===================================

FlexArray is a flexibly-sized array similar to ``std::vector``. Internally,
it is implemented as a circular buffer deque, guaranteed to be stored in
contiguous memory, thereby helping to avoid or minimize cache misses.

While we aim to create a high-performance data structure, our top priority is
in giving the user easy *control* over the tradeoffs between CPU performance,
memory, and cache misses.

Performance
------------------------------------

FlexArray is usually as fast as, or faster than, ``std::vector``. Unlike
``std::deque``, FlexArray is guaranteed to be stored in contiguous memory.

Here's how FlexArray stacks up against the GCC implementation of
``std::vector``...

- Inserting to end is as fast or faster.
- Inserting to the middle is *slower*. (We plan to improve this in a later release.)
- Inserting to the beginning is faster.
- Removing from any position is faster.
- Accessing any position is as fast.

If general performance is more important to you than contiguous memory, see
``SpeedList``.

Functional Comparison to ``std::vector``
-------------------------------------------

FlexArray offers largely the same functionality as ``std::vector``. However,
it is not intended to feature-identical. Some functionality hasn't been
implemented yet, and we may not include some other features to leave room
for future optimization and experimentation.

* FlexArray does not offer iterators. This *may* be added in the future.
* You cannot change the underlying data structure. Our base class is where
  most of the heavy lifting occurs.
* Some advanced modifiers haven't been implemented yet.

Technical Limitations
--------------------------------------

FlexArray can store a maximum of 4,294,967,294 objects. This is because it uses
32-bit unsigned integers for internal indexing, with the largest value
reserved as  ``INVALID_INDEX``. The limit is calculated as follows.

``2^{32} - 2 = 4,294,967,294``

Using FlexArray
=========================================

Including FlexArray
---------------------------------------

To include FlexArray, use the following:

..  code-block:: c++

    #include "pawlib/flex_array.hpp"

Creating a FlexArray
------------------------------------------

A ``FlexArray`` object is created by whatever means is convenient. It handles
its own dynamic allocation for storing its elements.

When the FlexArray is first created, you must specify the type of its elements.

..  code-block:: c++

    // Both of these methods are valid...
    FlexArray<int> temps_high;

    FlexArray<int>* temps_low = new FlexArray<int>;

Resize Factor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To minimize the number of CPU cycles used on reallocation, when we run out of
space in the data structure, on the next insertion, we allocate more space than
we immediately need. This *resize factor* is controllable.

By default, when the FlexArray resizes, it **doubles** its capacity (``n * 2``).
This provides the best general performance. However, if you want to preserve
memory at a small performance cost, you can switch to a resize factor of
``n * 1.5`` (internally implemented as ``n + n / 2``).

To switch to the ``1.5`` factor, include ``false`` as the second template
parameter (``factor_double``).

..  code-block:: c++

    FlexArray<int, false> i_resize_slower;

Reserve Size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We can specify the initial size (in elements) of the FlexArray in the
constructor.

..  code-block:: c++

    FlexArray<int>* temps_high = new FlexArray<int>(100);

..  NOTE:: The FlexArray will always have minimum capacity of 2.

Adding Elements
------------------------------------------

You can insert an element anywhere into a FlexArray. As with ``std::vector``,
the first element is considered the "front", and the last element the "back".

``insert()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

It is possible to insert an element anywhere in the array using ``insert()``.
This function has a worst-case performance of ``O(n/2)``.

..  code-block:: c++

    FlexArray<int> temps;

    // We'll push a couple of values for our example.
    temps.push(45);
    temps.push(48);

    // Insert the value "37" at index 1.
    temps.insert(37, 1);
    // Insert the value "35" at index 2.
    temps.insert(35, 2);

    // The FlexArray is now [48, 35, 37, 45]

If there is ever a problem adding a value, the function will return ``false``.
Otherwise, it will return ``true``.

``push()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The most common action is to "push" an element to the back using the ``push()``
function. The alias ``push_back()`` is also provided for convenience.

In FlexArray, ``push()`` has exactly the same performance as ``shift()``;
that is, ``O(1)``.

..  code-block:: c++

    FlexArray<int> temps_high;
    temps_high.push(45);
    temps_high.push(37);
    temps_high.push(35);
    temps_high.push_back(48); // we can also use push_back()
    // The FlexArray is now [45, 37, 35, 48]

If there is ever a problem adding a value, the function will return ``false``.
Otherwise, it will return ``true``.

``shift()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can also "shift" an element to the front using ``shift()``. The alias
``push_front()`` is also provided.

In FlexArray, ``shift()`` has exactly the same performance as ``push()``;
that is, ``O(1)``.

..  code-block:: c++

    FlexArray<int> temps_low;
    temps_low.shift(45);
    temps_low.shift(37);
    temps_low.shift(35);
    temps_low.push_front(48); // we can also use push_front()
    // The FlexArray is now [48, 35, 37, 45]

If there is ever a problem adding a value, the function will return ``false``.
Otherwise, it will return ``true``.

Accessing Elements
-------------------------------------------

``at()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``at()`` allows you to access the value at a given array index.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    apples.at(1);

    // This output yields 42

Alternatively, you can use the ``[]`` operator to access a value.

..  code-block:: c++

    // Using the array from above...
    apples[2];

    // The array is [23, 42, 36]
    // This output yields 36

..  WARNING:: If the array is empty, or if the specified index is too large,
    this function/operator will throw the exception ``std::out_of_range``.

``peek()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``peek()`` allows you to access the last element in the array without modifying
the data structure. The alias ``peek_back()`` is also provided for convenience.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    apples.peek();
    // This outputs 36.
    // The array remains [23, 42, 36]

..  WARNING:: If the array is empty, this function will throw the exception
    ``std::out_of_range``.

If you want to "peek" the first element, use ``peek_front()``.

``peek_front()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``peek_front()`` allows you to access the first element in the array without
modifying the data structure.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    apples.peek_front();
    // This outputs 23.
    // The array remains [23, 42, 36]

..  WARNING:: If the array is empty, this function will throw the exception
    ``std::out_of_range``.

Removing Elements
-------------------------------------------

``clear()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``clear()`` removes all the elements in the FlexArray.

..  code-block:: c++

    FlexArray<int> pie_sizes;

    pie_sizes.push(18);
    pie_sizes.push(18);
    pie_sizes.push(15);

    // I ate everything...
    pie_sizes.clear();

This function always returns true, and will never throw an exception
(**no-throw guarantee**).

``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``erase()`` allows you to delete elements in an array in a given range.
Remaining values are shifted to fill in the empty slot. This function has a
worst-case performance of ``O(n/2)``.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    // The array is currently [23, 42, 36]

    apples.erase(0,1);
    // The first number in the function call is the lower bound
    // The second number is the upper bound.
    // The array is now simply [36]

If any of the indices are too large, this function will return ``false``.
Otherwise, it will return true. It never throws exceptions
(**no-throw guarantee**).

``pop()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``pop()`` returns the last value in an array, and then removes it from the data
set. The alias ``pop_back()`` is also provided. In FlexArray, ``pop()`` has
exactly the same performance as ``unshift()``; that is, ``O(1)``.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    // The array is currently [23, 42, 36]

    apples.pop(0,1);
    // Returns 3. The array is now [23, 42]

..  WARNING:: If the array is empty, this function will throw the exception
    ``std::out_of_range``.

``unshift()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``unshift()`` will return the first element in the array, and remove it.
In FlexArray, ``unshift()`` has exactly the same performance as ``pop()``;
that is, ``O(1)``.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(2);
    apples.push(1);
    apples.push(3);

    // The array is currently [23, 42, 36]

    apples.unshift();
    // Returns 23.
    // The array is now [42, 36]

..  WARNING:: If the array is empty, this function will throw the exception
    ``std::out_of_range``.

``yank()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``yank()`` removes a value at a given index. Remaining values are shifted
to fill in the empty slot. This function has a worst-case performance of
``O(n/2)``.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    // The array is currently [23, 42, 36]

    apples.yank(1);
    // Returns 42.
    // The array is now [23, 36]

..  WARNING:: If the array is empty, or if the specified index is too large,
    this function will throw the exception ``std::out_of_range``.

Size and Capacity Functions
-------------------------------------------

``getCapacity()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``getCapacity()`` returns the total number of elements that can be stored in
the FlexArray without resizing.

..  code-block:: c++

    FlexArray<int> short_term_memory;

    short_term_memory.getCapacity();
    // Returns 8, the default size.

``length()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``length()`` allows you to check how many elements are currently
in the FlexArray.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    apples.length();
    // The function will return 3

``isEmpty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``isEmpty()`` returns true if the FlexArray is empty, and false if it contains
values.

..  code-block:: c++

    FlexArray<int> answers;

    answers.isEmpty();
    // The function will return true

    // We'll push some values for our example
    answers.push(42);

    answers.isEmpty();
    // The function will return false


``isFull()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``isFull()`` returns true if the FlexArray is full to the current capacity
(before resizing), and false otherwise.

..  code-block:: c++

    FlexArray<int> answers;

    answers.isFull();
    // The function will return false

    // Push values until we are full, using the isFull() function to check.
    while(!answers.isFull())
    {
        answers.push(42);
    }

``reserve()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can use ``reserve()`` to resize the FlexArray to be able to store the given
number of elements. If the data structure is already equal to or larger than
the requested capacity, nothing will happen, and the function will
return ``false``.

..  code-block:: c++

    FlexArray<std::string> labors_of_hercules;

    // Reserve space for all the elements we plan on storing.
    labors_of_hercules.reserve(12);

    labors_of_hercules.getCapacity();
    // Returns 12, the requested capacity.

After reserving space in an existing FlexArray, it can continue to resize.

This function is effectively identical to specifying a size at instantiation.

``shrink()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can use ``shrink()`` function to resize the FlexArray to only be large
enough to store the current number of elements in it. If the shrink is
successful, it wil return ``true``, otherwise it will return ``false``.

..  code-block:: c++

    FlexArray<int> marble_collection;

    for(int i = 0; i < 100; ++i)
    {
        marble_collection.push(i);
    }

    marble_collection.getCapacity();
    // Returns 128, because FlexArray is leaving room for more elements.

    // Shrink to only hold the current number of elements.
    marble_collection.shrink();

    marble_collection.getCapacity();
    // Returns 100, the same as the number of elements.

After shrinking, we can continue to resize as new elements are added.

..  NOTE:: It is not possible to shrink below a capacity of 2.
