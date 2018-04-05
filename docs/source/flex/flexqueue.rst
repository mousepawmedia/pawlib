FlexQueue
##################################################

What is FlexQueue?
===================================

FlexQueue is a flexibly-sized queue similar to ``std::queue``. Internally,
it is implemented as a circular buffer deque, guaranteed to be stored in
contiguous memory, thereby helping to avoid or minimize cache misses.

While we aim to create a high-performance data structure, our top priority is
in giving the user easy *control* over the tradeoffs between CPU performance,
memory, and cache misses.

Performance
------------------------------------

Because ``std::queue`` is based on ``std::deque``, and thereby is not stored
in contiguous memory, we instead must benchmark ``FlexQueue`` against
``std::vector``.

FlexQueue is usually as fast as, or faster than, ``std::vector``.
Here's how FlexQueue ranks against the GCC implementation of
``std::vector``...

- Pushing (to back) is faster.
- Popping (from front) is faster.
- Accessing is at least as fast.

If general performance is more important to you than contiguous memory, see
``SpeedQueue``.

Comparison to ``std::queue``
-------------------------------------

FlexQueue offers largely the same functionality as ``std::queue``. However,
it is not intended to feature-identical. Some functionality hasn't been
implemented yet, and we may not include some other features to leave room
for future optimization and experimentation.

* FlexQueue does not offer iterators. This *may* be added in the future.
* You cannot change the underlying data structure. Our base class is where
  most of the heavy lifting occurs.
* Some advanced modifiers haven't been implemented yet.

Technical Limitations
--------------------------------------

FlexQueue can store a maximum of 4,294,967,294 objects. This is because it uses
32-bit unsigned integers for internal indexing, with the largest value
reserved as  ``INVALID_INDEX``. The limit is calculated as follows.

``2^{32} - 2 = 4,294,967,294``

Using FlexQueue
===================================

Queues are "First-In-First-Out"; you insert to the end (or "back"), and remove
from the front.

Including FlexQueue
---------------------------------------

To include FlexQueue, use the following:

..  code-block:: c++

    #include "pawlib/flex_queue.hpp"

Creating a FlexQueue
-----------------------------------

A ``FlexQueue`` object is created by whatever means is convenient. It handles
its own dynamic allocation for storing its elements.

When the FlexQueue is first created, you must specify the type of its elements.

..  code-block:: c++

    // Both of these methods are valid...

    FlexQueue<int> dmvLine;

    anotherQueue = new FlexQueue<int>;

Resize Factor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To minimize the number of CPU cycles used on reallocation, when we run out of
space in the data structure, on the next insertion, we allocate more space than
we immediately need. This *resize factor* is controllable.

By default, when the FlexQueue resizes, it **doubles** its capacity (``n * 2``).
This provides the best general performance. However, if you want to preserve
memory at a small performance cost, you can switch to a resize factor of
``n * 1.5`` (internally implemented as ``n + n / 2``).

To switch to the ``1.5`` factor, include ``false`` as the second template
parameter (``factor_double``).

..  code-block:: c++

    FlexQueue<int, false> i_resize_slower;

Reserve Size
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We can specify the initial size (in elements) of the FlexQueue in the
constructor.

..  code-block::

    FlexQueue<int>* dmvLine = new FlexQueue<int>(250);

..  NOTE:: The FlexQueue will always have minimum capacity of 2.

Adding Elements
----------------------------------

``enqueue()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``enqueue()`` adds a value to the end of the queue. Aliases ``push()`` and
``push_back()`` are also provided. This function has the performance of
``O(1)``.

..  code-block:: c++

    FlexQueue<int> apples;

    // We'll add some values
    // using the three aliases
    apples.enqueue(23);
    apples.push(12);
    apples.push_back(31);

    // The queue is now [23, 12, 31]

If there is ever a problem adding a value, the function will return ``false``.
Otherwise, it will return ``true``.

Accessing Elements
---------------------------------

``at()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``at()`` allows you to access the value at a given index.

..  code-block:: c++

    FlexQueue<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(12);
    apples.push(31);

    apples.at(1);

    // The queue is [23, 12, 31]
    // This output yields 12

Alternatively, you can use the ``[]`` operator to access a value.

..  code-block:: c++

    // Using the queue from above...

    apples[2];

    // The queue is [23, 12, 31]
    // This output yields 31

..  WARNING:: If the queue is empty, or if the specified index is too large,
    this function/operator will throw the exception ``std::out_of_range``.

``peek()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``peek()`` allows you to access the next element in the queue without modifying
the data structure.

..  code-block:: c++

    FlexQueue<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(12);
    apples.push(31);

    std::cout << apples.peek();

    // This output yields 23
    // The queue remains [23, 12, 31]

..  WARNING:: If the queue is empty, this function will throw the exception
    ``std::out_of_range``.

Removing Elements
----------------------------------

In a queue, we typically remove and return elements from the beginning,
or "front" of the queue. Imagine a line at a grocery store - you enter in the
back and exit in the front.

``clear()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``clear()`` removes all the elements in the FlexQueue.

..  code-block:: c++

    FlexQueue<int> pie_sizes;

    pie_sizes.push(18);
    pie_sizes.push(18);
    pie_sizes.push(15);

    // I ate everything...
    pie_sizes.clear();

    // The FlexQueue is now empty.

This function always returns true, and will never throw an exception
(**no-throw guarantee**).

``dequeue()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``dequeue()`` will remove and return the first element in the queue.
Aliases ``pop()`` and ``pop_front()`` are also provided. This function has
the performance of ``O(1)``.

..  code-block:: c++

  FlexQueue<int> apples;

  // We'll push some values
  apples.push(23);
  apples.push(12);
  apples.push(31);
  apples.push(40);

  // The queue is now [23, 12, 31, 40]

  // We'll now remove three elements
  // with the three provided aliases
  apples.dequeue();
  apples.pop();
  apples.pop_front();

  // The queue is now simply [40]

..  WARNING:: If the queue is empty, this function will throw the exception
    ``std::out_of_range``.

``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``erase()`` allows you to delete elements in a queue in a given range.
Remaining values are shifted to fill in the empty slot. This function has a
worst-case performance of ``O(n/2)``.

..  code-block:: c++

    FlexQueue<std::string> coffeeshop_line;

    // We'll push some values for our example
    coffeeshop_line.enqueue("Bob");
    coffeeshop_line.enqueue("Jane");
    coffeeshop_line.enqueue("Alice");

    // The queue is currently ["Bob", "Jane", "Alice"]

    apples.erase(0,1);
    // The first number in the function call is the lower bound
    // The second number is the upper bound.
    // The queue is now simply ["Alice"]

If any of the indices are too large, this function will return ``false``.
Otherwise, it will return true. It never throws exceptions
(**no-throw guarantee**).

Size and Capacity Functions
-------------------------------------------

``getCapacity()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``getCapacity()`` returns the total number of elements that can be stored in
the FlexQueue without resizing.

..  code-block:: c++

    FlexQueue<int> short_term_memory;

    short_term_memory.getCapacity();
    // Returns 8, the default size.

``getLength()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``getLength()`` allows you to check how many elements are currently
in the FlexQueue.

..  code-block:: c++

    FlexQueue<int> apples;

    // We'll enqueue some values for our example
    apples.enqueue(23);
    apples.enqueue(42);
    apples.enqueue(36);

    apples.getLength();
    // The function will return 3

``isEmpty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``isEmpty()`` returns true if the FlexQueue is empty, and false if it contains
values.

..  code-block:: c++

    FlexQueue<int> answers;

    answers.isEmpty();
    // The function will return true

    // We'll enqueue some values for our example
    answers.enqueue(42);

    answers.isEmpty();
    // The function will return false


``isFull()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

``isFull()`` returns true if the FlexQueue is full to the current capacity
(before resizing), and false otherwise.

..  code-block:: c++

    FlexQueue<int> answers;

    answers.isFull();
    // The function will return false

    // Push values until we are full, using the isFull() function to check.
    while(!answers.isFull())
    {
        answers.enqueue(42);
    }

``reserve()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can use ``reserve()`` to resize the FlexQueue to be able to store the given
number of elements. If the data structure is already equal to or larger than
the requested capacity, nothing will happen, and the function will
return ``false``.

..  code-block:: c++

    FlexQueue<std::string> labors_of_hercules;

    // Reserve space for all the elements we plan on storing.
    labors_of_hercules.reserve(12);

    labors_of_hercules.getCapacity();
    // Returns 12, the requested capacity.

After reserving space in an existing FlexQueue, it can continue to resize.

This function is effectively identical to specifying a size at instantiation.

``shrink()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can use ``shrink()`` function to resize the FlexQueue to only be large
enough to store the current number of elements in it. If the shrink is
successful, it wil return ``true``, otherwise it will return ``false``.

..  code-block:: c++

    FlexQueue<int> marble_collection;

    for(int i = 0; i < 100; ++i)
    {
        marble_collection.enqueue(i);
    }

    marble_collection.getCapacity();
    // Returns 128, because FlexQueue is leaving room for more elements.

    // Shrink to only hold the current number of elements.
    marble_collection.shrink();

    marble_collection.getCapacity();
    // Returns 100, the same as the number of elements.

After shrinking, we can continue to resize as new elements are added.

..  NOTE:: It is not possible to shrink below a capacity of 2.