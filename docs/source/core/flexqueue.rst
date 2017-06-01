FlexQueue
##################################################

What is FlexQueue?
===================================

FlexQueue is a unique queue based upon a flexible array structure,
similar to ``std::queue``, utilizing the
FIFO (first in, first out) data structure. It is based on ``FlexArray``
and shares similar high-performance characteristics.

Using FlexQueue
===================================

Creating a FlexQueue
-----------------------------------
A ``FlexQueue`` object is created by whatever means is convenient. It handles
its own dynamic allocation for storing its elements.

When the FlexQueue is first created, you must specify the type of its elements.

..  code-block:: c++

    // Both of these methods are valid...

    FlexQueue<int> dmvLine;

    anotherQueue = new FlexQueue<int>;

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

``peek()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``peek()`` allows you to access the first element in the array without modifying
the data structure.

..  code-block:: c++

    FlexQueue<int> apples;

    // We'll push some values for our example
    apples.push(23);
    apples.push(12);
    apples.push(31);

    cout << apples.peek();

    // This output yields 23
    // The queue remains [23, 12, 31]

Adding Elements
----------------------------------

``enqueue()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``enqueue()`` adds a value to the end of the queue. Aliases ``push()`` and
``push_back()`` are also provided.

..  code-block:: c++

    FlexQueue<int> apples;

    // We'll add some values
    // using the three aliases
    apples.enqueue(23);
    apples.push(12);
    apples.push_back(31);

    // The queue is now [23, 12, 31]

Removing Elements
----------------------------------

``dequeue()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``dequeue()`` will remove and return the first element in the queue. Aliases ``pop()`` and
``pop_front()`` are also provided.

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


``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``erase()`` removes elements from the queue in a given range.

..  code-block:: c++

  FlexQueue<int> apples;

  // We'll push some values
  apples.push(23);
  apples.push(12);
  apples.push(31);
  apples.push(40);
  apples.push(42);

  // The queue is now [23, 12, 31, 40, 42]

  apples.erase(1,3)
  // The first number refers to the lower bound
  // The second number refers to the upper bound

  // The queue is now [23, 42]



Other Fuctions
----------------------------------

``empty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``empty()`` is a boolean that returns true if the array is empty, and false if it
contains values.

..  code-block:: c++

    FlexQueue<int> apples;

    apples.empty();
    // The function will return true
    // No values have been added to 'apples'

    // Now we'll push some values...
    apples.push(23);
    apples.push(12);
    apples.push(31);

    apples.empty();
    // The function will now return false


``getSize()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``getSize()`` returns the number of elements currently in the queue.

..  code-block:: c++

  FlexQueue<int> apples;

  // We'll push some values
  apples.push(23);
  apples.push(12);
  apples.push(31);
  apples.push(40);

  // The queue is now [23, 12, 31, 40]

  apples.getSize();

  // The function will return 4
