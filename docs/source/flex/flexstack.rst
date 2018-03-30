FlexStack
###################################

What is FlexStack?
===================================

FlexStack is a flexibly-sized stack similar to ``std::stack``. We created this
implementation to be able to experiment with various optimizations and
algorithms, with the goal of creating a higher-performance data structure.

Performance
------------------------------------

FlexStack is slightly slower than ``std::stack``, but this is acceptable because
of the inherent difference between Flex and ``std::deque``; while Flex
guarantees storage in contiguous memory, ``std::deque`` does not. As a result,
we instead must compare against ``std::vector``.

For the analogous data structure with non-contiguous memory, see ``SpeedQueue``.

Comparison to ``std::stack``
-------------------------------------

FlexStack offers largely the same functionality as ``std::stack``. However,
it is not intended to feature-identical. Some functionality hasn't been
implemented yet, and we may not include some other features to leave room
for future optimization and experimentation.

* Internally, this is a contiguous-memory circular buffer.
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

Adding Elements
------------------------------------------

Stacks are "Last-In-First-Out"; you insert to the end (or "back"), and remove
from the back.

``push()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We add new elements to the stack with a "push" to the back using the ``push()``
function. The alias ``push_back()`` is also provided for convenience.

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
removed. (ergo "last-in-first-out").

``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``erase()`` allows you to delete elements in an stack in a given range. Values above
the top limit of the range will be shifted left to fill in empty indexes.

..  code-block:: c++

    FlexStack<string> albums;

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    // The stack is currently ["End of Silence", "Comatose", "Fireproof"]

    albums.erase(0, 1);
    // The first number in the fuction call is the lower bound
    // The second number is the upper bound.
    // The stack is now simply ["Fireproof"]

``pop()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``pop()`` returns the last value in an stack, and then removes it from the data set.
The alias ``pop_back()`` is also provided.

..  code-block:: c++

    FlexStack<int> dish_sizes;

    // We'll push some values for our example
    dish_sizes.push(22);
    dish_sizes.push(18);
    dish_sizes.push(12);

    // The stack is currently [22, 18, 12]

    dish_sizes.pop();
    // Returns 12. The stack is now [22, 18]

Other Functions
------------------------

``empty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``empty()`` is a boolean that returns true if the stack is empty, and false if it
contains values.

..  code-block:: c++

    FlexStack<string> albums;

    albums.empty();
    // The function will return true

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    albums.empty();
    // The function will return false

``getSize()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``getSize()`` allows you to check how many elements are currently in an stack.

..  code-block:: c++

    FlexStack<string> albums;

    // We'll push some values for our example
    albums.push("End Of Silence");
    albums.push("Comatose");
    albums.push("Fireproof");

    albums.getsize();
    // The function will return 3
