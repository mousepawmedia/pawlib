Standard Utilities
###################################

These are common utility functions which are used by many other classes
in PawLIB.

Not all of the functions are documented below, only those we believe will
be useful to PawLIB users.

Including Standard Utilities
=================================

To include Standard Utilities, use the following:

..  code-block:: c++

    #include "pawlib/stdutils.hpp"

Integer to std::string [``itos()``]
==================================================

We can convert any integer data type, signed or unsigned, to a std::string
using ``itos()``.

``itos()`` converts the integer to a std::string. It accepts three arguments,
two of which are required:

* the integer to convert,

* the base you're working in, represented as an integer (default=10),

* whether to represent digits greater than 9 as uppercase (default=false)

..  code-block:: c++

    // The integer to convert.
    int foo = -16753;

    /* Convert the float to a std::string. We're passing all the arguments,
     * even though only the first two are required, for the sake of example.
     */
    std::string foo_s = stdutils::itos(foo, 10, false);

    // Print out the std::string.
    ioc << foo_s << IOCtrl::endl;

    // OUTPUT: -16753

..  IMPORTANT:: Enumerations are not implicitly cast to ints with this function.
    Therefore, you must ``static_cast<int>()`` any enumeration variables
    before passing them to this function.

Integer to C-String [``itoa()`` & ``intlen()``]
==================================================

We can convert any integer data type, signed or unsigned, to a C-string
using ``itoa()`` and ``intlen()``.

``intlen()`` returns the character count necessary to represent the integer
as a string. It accepts three arguments, two of which are required:

* the integer being measured,

* the base you're working in, represented as an integer, and

* whether to include space for the sign (default=true).

``itoa()`` converts the integer to a C-string. It accepts five arguments,
two of which are required:

* the C-string to write to,

* the integer to convert,

* the base you're working in, represented as an integer (default=10),

* the number of characters in the integer (default=0, meaning it will be
  internally calculated), and

* whether to represent digits greater than 9 as uppercase (default=false)

Combining these functions allows us to flexibly convert any integer to a
C-string, without having to know anything in advance.

..  code-block:: c++

    // The integer to convert.
    int foo = -16753;

    /* We use the intlen function to determine the size of our C-string
     * Note that we are adding one to leave room for our null terminator. */
    char foo_a[stdutils::intlen(foo, 10, true) + 1];

    /* Convert the integer to a C-string. We're passing all the arguments,
     * even though only the first two are required, for the sake of example.
     * 0 for the fourth argument (size) causes the function to internally
     * calculate the size of the integer again, which is another call to
     * intlen(). You might save some execution time by specifying this instead.
     */
    stdutils::itoa(foo_a, foo, 10, 0, false);

    // Print out the C-string.
    ioc << foo_a << IOCtrl::endl;

    // OUTPUT: -16753

..  NOTE:: It is generally going to be more practical to use ``itos()`` instead.

..  IMPORTANT:: Enumerations are not implicitly cast to ints with this function.
    Therefore, you must ``static_cast<int>()`` any enumeration variables
    before passing them to this function.

Float to String [``ftos()``]
================================

We can convert any floating-point number data type (float, double, or long
double) to a std::string using `ftos()`.

We need to specify the number of significands - in our case, the number of
digits after the decimal point - to work with. Because of the nature of floating
point numbers, the conversion is *not* perfect, as we'll see shortly.

``ftos()`` converts the number into a C-string. It accepts three arguments, one
of which are required:

* the number to convert,

* the number of significands (default=14), and

* whether to use scientific notation - 0=none, 1=automatic,
  and 2=force scientific notation (default=1).

..  code-block:: c++

    // The integer to convert.
    float foo = -65.78325;

    /* Convert the float to a std::string. */
    std::string foo_s = stdutils::ftos(foo, 5, 1);

    // Print out the std::string.
    ioc << foo_s << IOCtrl::endl;

    // OUTPUT: -65.78324

As you can see, the output is off by 0.00001. Again, this is because of
how floating point numbers work, and the number of significands we
specified. If we were to raise the significands to the default 14, our output
would actually have been "-65.78324891505623".

Float to C-String [``ftoa()`` & ``floatlen()``]
=================================================

We can convert any floating-point data type (float, double, or long double)
to a C-string using ``ftoa()`` and ``floatlen()``.

In both functions, we need to specify the number of significands - in our case,
the number of digits after the decimal point - to work with. Because of the
nature of floating point numbers, the conversion is *not* perfect, as we'll
see shortly.

``floatlen()`` returns the character count necessary to represent the
floating-point number as a string. It accepts three arguments, only one of which
is required:

* the number to count the characters in,

* the number of significands (default=14), and

* whether to count the symbols (default=true)

``ftoa()`` converts the number into a C-string. It accepts four arguments, two
of which are required:

* the C-string to write to,

* the number to convert,

* the number of significands (default=14), and

* whether to use scientific notation - 0=none, 1=automatic,
  and 2=force scientific notation (default=1).

..  code-block:: bash

    // The integer to convert.
    float foo = -65.78325;

    /* Convert the float to a std::string. */
    std::string foo_s = stdutils::ftos(foo, 5, 1);

    // Print out the std::string.
    ioc << foo_s << IOCtrl::endl;

    // OUTPUT: -65.78324

As you can see, the output is off by 0.00001. Again, this is because of
how floating point numbers work, and the number of significands we
specified. If we were to raise the significands to the default 14, our output
would actually have been "-65.78324891505623".

..  NOTE:: It is generally going to be more practical to use ``ftos()`` instead.


Split String By Tokens [``stdsplit``]
===========================================

This will split a ``std::string`` by a given token and store it in a
``std::vector``. The token will be stripped out in the process.

Later versions of this will support Onestring and FlexArray.

..  code-block:: c++

    std::string splitMe = "What if we:Want to split:A string:By colons?";
    std::vector<std::string> result;

    stdutils::stdsplit(splitMe, ":", result);
    // result now contains "What if we", "Want to split", "A string", "By colons?"

Reverse C-String [``strrev()``]
===================================

This will reverse a given C-string in place, overriding the string.

..  code-block:: c++

    char foo[14] = "Hello, world!";
    stdutils::strrev(foo);
    ioc << foo << IOCtrl::endl;
