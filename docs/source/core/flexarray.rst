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

    //Insert the value "37" at index 1.
    temps.insert(37, 1);
    //Insert the value "35" at index 2.
    temps.insert(35, 2);

    // The FlexArray is now [48, 35, 37, 45]

Accessing Elements
-------------------------------------------

``peek()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Peek allows you to access the first element in the array without modifying the
data structure.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   cout << apples.peek();

   //This output yields 2
   //The array remains [2, 1, 3]

``at()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
At allows you to access the value at a given array index.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   cout << apples.at(1);

   //The array is [2, 1, 3]
   //This output yields 1

Alternatively, you can use the ``[]`` operator to access a value.

..  code-block:: c++

  //using the array from above...

  cout << apples[2];

  //The array is [2, 1, 3]
  //This output yields 3

``getSize()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Get size allows you to check how many elements are currently in an array.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   apples.getsize();
   //The function will return 3


Removing Elements
-------------------------------------------

``yank()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Yank removes a value at a given index. Remaining values at indexes greater than
that removed are shifted left to fill in the empty slot.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   //The array is currently [2, 1, 3]

   apples.yank(1);

   //The array is now [2, 3]

``unshift()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Unshift will return the first element in the array, and remove it. All remaining
values are shifted one slot to the left.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   //The array is currently [2, 1, 3]

   apples.unshift();

   //The array is now [1, 3]

``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Erase allows you to delete elements in an array in a given range. Values above
the top limit of the range will be shifted left to fill in empty indexes.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   //The array is currently [2, 1, 3]

   apples.erase(0,1);
   //The first number in the fuction call is the lower bound
   //The second number is the upper bound.
   //The array is now simply [3]

``empty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Empty is a boolean that returns true if the array is empty, and false if it
contains values.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   apples.empty();
   //The function will return false

or

..  code-block:: c++

   FlexArray<int> apples;

   apples.empty();
   //The function will return true
   //No values have been added to 'apples'



``pop()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Pop returns the last value in an array, and then removes it from the data set.
The alias ``pop_back()`` is also provided.

..  code-block:: c++

   FlexArray<int> apples;

   //We'll push some values for our example
   apples.push(2);
   apples.push(1);
   apples.push(3);

   //The array is currently [2, 1, 3]

   apples.pop(0,1);
   //The array is now [2, 1]
