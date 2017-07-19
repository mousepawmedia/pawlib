OneString
#############################

What is OneString?
===================================
``OneString`` is a multi-sized, Unicode-compatible replacement
for ``std::string``. OneString contains all the
basic functions found in ``std::string`` while optimizing
the use of dynamic allocation wherever possible.
To handle Unicode, each OneString is made of OneChars,
which are enhanced characters.


Using a OneString
=====================================

Creating a OneString
--------------------------------------
You can create a OneString with characters initialized with the ``=`` operator
or leave it blank.

..  code-block:: c++

    // Empty OneString
    OneString blankString;

    // Containing OneChars
    OneString fullString = "these are Unicode Characters";

You can also use the ``=`` operator to create a new OneString with an existing
OneString.

..  code-block:: c++

  // Create the first OneString
  OneString firstString = "copy me";

  // Containing OneChars
  OneString secondString = firstString;

  // secondString now contains "copy me".


Adding to a OneString
---------------------------------------

``+``, ``+=``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ``+=`` and ``+`` operators add additional Unicode characters at the end of the
existing ``OneString``.

Using ``+=``

..  code-block:: c++

    //Declare a OneString
    OneString more = "apple";

    // Use += to append an "s"
    more += "s";
    // `more` is now "apples"

    // Use + to append "!"
    more = more + "!"
    // `more` is now "apples!"

``append()``, ``push_back()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Alternatively, you can use the functions ``append()`` and ``push_back()``
to add additional Unicode characters at the end of the existing ``OneString``.

Using ``append()``

..  code-block:: c++

    // Declare a OneString
    OneString to_add = "apple";

    // Add "s" to `to_add`
    to_add.append('s');

    // `to_add`is now "apples"

    // add "!" to `to_add`
    to_add.push_back(`!`);

    // `to_add` is now "apples!"


``insert()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``insert()`` allows you to insert a Unicode character into an existing
``OneString`` at a given position.

..  code-block:: c++

    // Declare a OneString
    OneString alphabet = "abcdf";

    // Insert a value into `alphabet`
    // The first value in the function refers to the index to be inserted
    // The second value refers to the value to be inserted
    alphabet.insert(4, 'E');

    // `alphabet` is now "abcdEf"

Removing from a OneString
---------------------------------------

``clear()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``clear()`` erases the contents of a OneString.

..  code-block:: c++

    // Declare a OneString
    OneString sleeve = "something";

    // Clear the contents of `sleeve`
    sleeve.clear();

    // `sleeve` is now empty


``pop_back()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``pop_back()`` removes the last Unicode character in the OneString

..  code-block:: c++

    // Declare a OneString
    OneString alphabet = "abcdef";

    // Remove the last element from `alphabet`
    alphabet.pop_back();

    // `alphabet` is now "abcde"

Accessing Elements of A OneString
---------------------------------------
``[]``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``[]`` operator acceses a Unicode character at a given location in a
``OneString``.

..  code-block:: c++

    // Declare a OneString
    OneString test = "hello";

    // Check what character is at position 1 in `test`
    test[1];

    // The operator returns 'e'

``at()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``at()`` function can be used as an alternative to ``[]``.

..  code-block:: c++

     // Declare a OneString
     OneString alphabet = "abcdef";

     // Find the OneChar at position 3 in `alphabet`
     alphabet.at(3);

     // The function returns "d"

Comparing OneStrings
---------------------------------------

``==``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``==`` operator checks for equivalence between two strings and returns
a boolean with the result.

..  code-block:: c++
    // Declare two OneString
    OneString dogs = "fun";
    OneString cats = "mean";

    // Check for equivalence
    if (dogs == cats)
    {
      return dogs;
    }
    else
    {
      return cats;
    }

    // This statement would return `cats`

    // Reassign `cats`
    cats = "fun";

    // Check for equivalence
    if (dogs == cats)
    {
      return dogs;
    }
    else
    {
      return cats;
    }

    // The statement now returns `dogs`.

``equals()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``equals()`` can also be used to check for equality.

..  code-block:: c++

    // Declare a OneString
    OneString checker = "red";

    // Compare with another OneString
    checker.equals("black");

    // The function returns false

    // Compare again
    checker.equals("red");

    // The function returns true

``<, >, <=, >=``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``<``, ``>``, ``<=``, and ``>=`` operators compare string sizes, with the first
relative to the second. ``<`` is less than, ``>`` is greater than, and ``<=`` and
``>=`` are less than or equal to, and greater than or equal to, respectively.

..  code-block:: c++

    // Delcare three OneStrings
    OneString first = "one";
    OneString second = "two";
    OneString third = "three";

    // Compare `first` to `second`
    if (first < second)
    {
      return first;
    }
    else
    {
      return second;
    }

    // The statement returns `second`

    if (first <= second)
    {
      return first;
    }
    else
    {
      return second;
    }

    // The statement now returns `first`

    if (third > second)
    {
      return third;
    }
    else
    {
      return second;
    }

    // Finally, this statement returns `third`

Other Functions
--------------------------------------

``empty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``empty()`` checks to see if a OneString is empty.
The function returns true if it is empty, and false if it is not.

..  code-block:: c++

    // Declare a OneString
    OneString toyBox;

    // Check to see if `toybox` empty
    toyBox.empty();

    // The function returns true

    // Assign values to `toyBox`
    toyBox = "basketball"

    // Check again to see if its empty
    toyBox.empty();

    // This time, the function returns false.


``getType()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``getType()`` returns a boolean that represents either a ``OneString``
or a ``QuickString``.


``size()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``size()`` returns the number of characters that make up the ``OneString``.

..  code-block:: c++

    // Declare a OneString
    OneString checker = "red";

    // check the size of `checker`
    checker.size();

    // The function will return 3

``substr()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``substr()`` creates a new substring based on a range of characters in an exisiting
``OneString``

..  code-block:: c++

    // Declare a OneString
    OneString full = "monochromatic"

    // Declare a new OneString
    // Using `full`
    // and substr
    OneString partial = full.substr(0,3);

    // The new OneString `partial` contains the word "mono".
    // The numbers in the function call refer to
    // the range to be copied into the new string.

``swap()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``swap()`` switches the contents of the current ``OneString`` with another.
The two ``OneStrings`` must be of the same size.

..  code-block:: c++

    // Declare two OneStrings
    OneString first = "primary";
    OneString second = "secondary";

    // Swap `primary` and `secondary`
    first.swap(second);

    // `first` now reads "secondary".
    // `second` now reads "primary"
