FlexArray
###################################

What is FlexArray?
===================================

FlexArray is a flexibly-sized array similar to ``std::vector``. We created this
implementation to be able to experiment with various optimizations and
algorithms, with the goal of creating a higher-performance data structure.

Performance
------------------------------------

Initial benchmark comparisons show that FlexArray is always at least as fast
as ``std::vector``, and often faster. We believe the main reasons for this
may be:

(1) The underlying structure *doubles* in size every time an operation will
    exceed the capacity of the FlexArray. While this greatly reduces the
    frequency of dynamic allocations (and thus improves performance), it may
    have negative impacts on memory usage for higher capacities. We will be
    experimenting with other resizing algorithms in future versions.

(2) The code base is structured to be less prone to instruction cache misses.

We will be exploring further optimizations and algorithm improvements in future
verisons.

Comparison to ``std::vector``
-------------------------------------

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

Adding Elements
------------------------------------------

You can insert an element anywhere into a FlexArray. As with ``std::vector``
the first element is considered the "front", and the last element the "back".

``push()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The most common action is to "push" an element to the back using the ``push()``
function. The alias ``push_back()`` is also provided for convenience.

..  code-block:: c++

    FlexArray<int> temps_high;
    temps_high.push(45);
    temps_high.push(37);
    temps_high.push(35);
    temps_high.push_back(48); // we can also use push_back()
    // The FlexArray is now [45, 37, 35, 48]

``shift()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can also "shift" an element to the front using ``shift()``. The alias
``push_front()`` is also provided.

..  code-block:: c++

    FlexArray<int> temps_low;
    temps_low.shift(45);
    temps_low.shift(37);
    temps_low.shift(35);
    temps_low.push_front(48); // we can also use push_front()
    // The FlexArray is now [48, 35, 37, 45]

Bear in mind that, when shifting in an element, FlexArray must also move
all the other elements. Thus, the performance cost for ``shift()`` is ``O(n)``.
If performance is a concern, you should use ``push()`` whenever possible.

``insert()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

It is possible to insert an element anywhere in the array using ``insert()``.

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

Accessing Elements
-------------------------------------------

``peek()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``peek()`` allows you to access the first element in the array without modifying the
data structure. The alias ``peek_back()`` is also provided for convenience.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    apples.peek();
    // This outputs 36.
    // The array remains [23, 42, 36]

If you want to "peek" the first element, use ``at(0)``.

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

Removing Elements
-------------------------------------------

``yank()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``yank()`` removes a value at a given index. Remaining values at indexes greater than
that removed are shifted left to fill in the empty slot.

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

``unshift()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``unshift()`` will return the first element in the array, and remove it. All remaining
values are shifted one slot to the left.

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

``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``erase()`` allows you to delete elements in an array in a given range. Values above
the top limit of the range will be shifted left to fill in empty indexes.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    // The array is currently [23, 42, 36]

    apples.erase(0,1);
    // The first number in the fuction call is the lower bound
    // The second number is the upper bound.
    // The array is now simply [36]

``pop()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``pop()`` returns the last value in an array, and then removes it from the data set.
The alias ``pop_back()`` is also provided.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    // The array is currently [23, 42, 36]

    apples.pop(0,1);
    // Returns 3. The array is now [23, 42]

Other Functions
-----------------------------

``empty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``empty()`` is a boolean that returns true if the array is empty, and false if it
contains values.

..  code-block:: c++

    FlexArray<int> apples;

    apples.empty();
    // The function will return true

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    apples.empty();
    // The function will return false

``getSize()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``getSize()`` allows you to check how many elements are currently in an array.

..  code-block:: c++

    FlexArray<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(42);
    apples.push(36);

    apples.getsize();
    // The function will return 3