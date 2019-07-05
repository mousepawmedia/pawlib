IOChannel
###################################

What is IOChannel?
===================================

IOChannel is designed as a wrapper and, depending on usage, a replacement
for ``std::cout`` and ``printf()``. Its sports a number of unique and useful
features.

* Multiple asynchronous outputs.
* Message priorities (verbosity).
* Message categories.
* Built-in output formatting.
* Advanced memory tools.

..  index:: iochannel

Setting up IOChannel
=====================================

Including IOChannel
---------------------------------------

To include IOChannel, use the following:

..  code-block:: c++

    #include "pawlib/iochannel.hpp"

IOChannel Instance
-------------------------------------

For convenience, a single static global instance of IOChannel, ``ioc``,
exists in that header. It is suitable for most purposes, though a custom
iochannel instance may be declared. All inputs and outputs that the developer
wishes to interface with one another via this class must share the same
instance.

IOFormat
-------------------------------------

IOChannel uses a number of enumerations and data types for formatting,
data manipulation, and advanced usage. These are in the pawlib::ioformat
namespace. To save typing, it may be helpful to import that particular
namespace via using namespace pawlib::ioformat;, even if the primary
namespace pawlib is not imported.

Documentation Assumptions
-------------------------------------

For purposes of expediency, the default global static instance ``pawlib::ioc``
will be used in this documentation. Furthermore, we will assume that
``using namespace pawlib::ioformat;`` and ``using namespace pawlib;`` are
being used. All namespaces outside of the scope of PawLIB will be stated explicitly.

Concepts
-------------------------------------

IOChannel uses two unique concepts: **Verbosity** and **Category**.

..  index::
    pair: output; category

Category
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The benefit to having categories on messages is that you can route different
kinds of messages to different outputs. For example, you might send all errors
and warnings to a debug terminal, and reserve "normal" messages for game
notifications.

+------------+-----------------+------------------------------------------------------------------+
| Category   | Enum            | Use                                                              |
+============+=================+==================================================================+
| Normal     | ``cat_normal``  | Regular use messages, especially those you want the user to see. |
+------------+-----------------+------------------------------------------------------------------+
| Warning    | ``cat_warning`` | Warnings about potential problems.                               |
+------------+-----------------+------------------------------------------------------------------+
| Error      | ``cat_error``   | Error messages.                                                  |
+------------+-----------------+------------------------------------------------------------------+
| Debug      | ``cat_debug``   | Messages that might help you track down problems.                |
+------------+-----------------+------------------------------------------------------------------+
| Testing    | ``cat_testing`` | Messages related solely to testing.                              |
+------------+-----------------+------------------------------------------------------------------+
| All        | ``cat_all``     | All of the above.                                                |
+------------+-----------------+------------------------------------------------------------------+

One of the advantages of this system is that you can actually leave messages
in the code, and just control when and how they are processed and broadcast.
This means you can actually ship with debugging statements still alive in the
code, allowing you to diagnose problems on any machine!

..  index::
    pair: output; verbosity
    see: priority; verbosity

Verbosity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Some messages we need to see every time, and others only in special
circumstances. This is what verbosity is for.

+------------+-----------------+---------------------------------------------------------------------------------------------------+
| Verbosity  | Enum            | Use                                                                                               |
+============+=================+===================================================================================================+
| Quiet      | ``vrb_quiet``   | Only essential messages and errors. For normal end-use. Shipping default.                         |
+------------+-----------------+---------------------------------------------------------------------------------------------------+
| Normal     | ``vrb_normal``  | Common messages and errors. For common and normal end-user testing.                               |
+------------+-----------------+---------------------------------------------------------------------------------------------------+
| Chatty     | ``vrb_chatty``  | Most messages and errors. For detailed testing and debugging.                                     |
+------------+-----------------+---------------------------------------------------------------------------------------------------+
| TMI        | ``vrb_tmi``     | Absolutely everything. For intense testing, detailed debugging, and driving the developers crazy. |
+------------+-----------------+---------------------------------------------------------------------------------------------------+

One example of verbosity in action would be in debugging messages. A
notification about a rare and potentially problematic function being called
might be ``vrb_normal``, while the output of a loop iterator would probably be
``vrb_tmi``.

..  index::
    single: output

Output
=======================================

General
--------------------------------------

All output is done using the stream insertion (``<<``) operator, in the same
manner as with ``std::cout``. Before a message is broadcast, a stream
control enumeration such as ``io_end`` must be passed.

``io_end`` serves as an "end of transmission" [EoT] flag, clears any formatting
set during the stream, and inserts a final newline character. Thus, ``\n`` is
not needed if the output should be displayed on a single line. This functionality
also allows a single transmission to be split up over multiple lines, if
necessary. Other stream control enumerations have different behaviors.
(See `Stream Control`_)

..  code-block:: c++

    ioc << "This is the first part. ";
    //Some more code here.
    ioc << "This is the second part." << io_end;

..  index::
    pair: output; strings

Strings
----------------------------------------

IOChannel natively supports string literals, cstring (char arrays),
``std::string``, and ``pawlib::onestring``.

These are passed in using the ``<<`` operator, as with anything being output
via IOChannel. The message will not be broadcast until an EoT
(end-of-transmission) flag is passed.

..  code-block:: c++

    ioc << "Hello, world!" << io_end;
    //OUTPUT: "Hello, world!"

    char* cstr = "I am a Cstring.\0";
    ioc << cstr << io_end;
    //OUTPUT: "I am a Cstring."

    std::string stdstr = "I am a standard string.";
    ioc << stdstr << io_end;
    //OUTPUT: "I am a standard string."

..  index::
    pair: output; formatting

Formatting
----------------------------------------

Cross-platform output formatting is built in to IOChannel. This means that
formatting can be set using the IOFormat enumerations, and it will display
correctly on each output and environment.

..  code-block:: c++

    ioc << ta_bold << fg_red << "This is bold, red text. " << ta_underline << fg_blue << bg_yellow << "This is bold, underline, blue text with a yellow background. " << ta_none << fg_none << bg_none << "This is normal text." << io_end;
    //The output is exactly what you'd expect.

.. IMPORTANT:: Currently, only ANSI is used. Windows support,
   formatting-removed, and an easy-to-parse formatting flag system for custom
   outputs will be added soon.

..  index::
    pair: output; variables

Variable Input
----------------------------------------

IOChannel supports all basic C/C++ data types.

* Boolean (``bool``)
* Char (``char``)
* Integer (``int``) and its various forms.
* Float (``float``)
* Double (``double``)

..  index::
    pair: output; boolean

Boolean
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Output for boolean is pretty basic and boring.

..  code-block:: c++

    bool foo = true;
    ioc << foo << io_end;
    //OUTPUT: "TRUE"

The output style can be adjusted, however, using the ``bool_`` enumerations.

..  code-block:: c++

    bool foo = true;
    ioc << bool_lower << foo << io_end;
    //OUTPUT: "true"
    ioc << bool_upper << foo << io_end;
    //OUTPUT: "True"
    ioc << bool_caps << foo << io_end;
    //OUTPUT: "TRUE"
    ioc << bool_numeral << foo << io_end;
    //OUTPUT: "1"

..  index::
    pair: output; char

Char
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Since char can represent both an integer and a character, IOChannel lets
you display it as either. By default, IOChannel displays the char as a literal
character. Using the ``char_int`` flag forces it to print as an integer.

..  code-block:: c++

    char foo = 'A';
    ioc << "Character " << foo << " has ASCII value " << char_int << foo << io_end;
    //OUTPUT: Character A has ASCII value 65

When output as an integer, char can be used with all of the enumerations for
int (see that section).

..  index::
    pair: output; integers

Integer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An ``int`` can be represented in any base (radix) from binary (base 2) to
base 35 using the base enumerations.

..  code-block:: c++

    int foo = 12345;
    ioc << "Binary: " << base_bin << foo << io_end;
    ioc << "Octal: " << base_oct << foo << io_end;
    ioc << "Decimal: " << base_dec << foo << io_end;
    ioc << "Dozenal: " << base_doz << foo << io_end;
    ioc << "Hexadecimal: " << base_hex << foo << io_end;
    ioc << "Base 31: " << base_31 << foo << io_end;

    /*OUTPUT:
    Binary: 11000000111001
    Octal: 30071
    Decimal: 12345
    Dozenal: 7189
    Hexadecimal: 3039
    Base 31: cq7
    */

In bases larger than decimal (10), the letter numerals can be output as
lowercase or uppercase (default).

..  code-block:: c++

    int foo = 187254;
    ioc << "Hexadecimal Lower: " << base_hex << foo << io_end;
    ioc << "Hexadecimal Upper: " << num_upper << base_hex << foo << io_end;

    /*OUTPUT:
    Hexadecimal Lower: 2db76
    Hexadecimal Upper: 2DB76
    */

..  index::
    pair: output; float
    pair: output; double

Float and Double
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Float and Double can only be output in base 10 directly. (Hexadecimal output is
only possible through a pointer memory dump. See that section.) However, the
significands (the number of digits after the decimal point) and use of
scientific notation can be modified. By default, significands is 14, and use of
scientific notation is automatic for very large and small numbers.

Significands can be modified using the ``set_significands(#)`` function. Scientific
notation can be turned on with ``sci_on``, and off using ``sci_none``. It can
also be reset to automatic with ``sci_auto``.

..  code-block:: c++

    float foo = 12345.12345678912345;
    ioc << "Significands 5, no sci: " << set_significands(5) << foo << io_end;
    ioc << "Significands 10, sci: " << set_significands(10) << sci_on << foo << io_end;

    /*OUTPUT:
    Significands 5, no sci: 12345.12304
    Significands 10, sci: 1.2345123046e+4
    */

Both types work the same.

..  index::
    pair: output; pointer

Pointer Output
-----------------------------------------

One of the most powerful features of IOChannel is its handling of pointers.
In addition to printing the value at known pointer types, it can print the
address or raw memory for ANY pointer, even for custom objects.

Pointer Value
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

By default, IOChannel will attempt to print the value at the pointers. This
can also be forced using ``ptr_value``.

..  code-block:: c++

    int foo = 12345;
    int* fooptr = &foo;
    ioc << "Value of foo: " << ptr_value << fooptr << io_end;

    char* bar = "My name is Bob, and I am a coder.\0";
    ioc << "Value of bar: " << bar << io_end;

    /*OUTPUT:
    Value of foo: 12345
    Value of bar: My name is Bob, and I am a coder.
    */

Pointer Address
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
IOChannel can print out the address of the pointer in hexadecimal using
``ptr_address``. It displays with lowercase letter numerals by default,
though these can be displayed in uppercase using ``num_upper``. It is capable
of doing this with any pointer, even for custom objects.

..  code-block:: c++

    int foo = 12345;
    int* fooptr = &foo;
    ioc << "Address of foo: " << ptr_address << fooptr << io_end;

    char* bar = "My name is Bob, and I am a coder.\0";
    ioc << "Address of bar: " << ptr_address << num_upper << bar << io_end;

    /*OUTPUT:
    Address of foo: 0x7ffc33518308
    Address of bar: 0x405AF0
    */

Pointer Memory Dump
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
IOChannel is capable of dumping the raw memory at any pointer using
``ptr_memory``. The function is safe for most known pointer types
(``bool``, ``int``, ``float``, and ``double``), as the memory dump will not
overrun the size of the variable. With char pointers (cstring), the only
danger is when the cstring is not null terminated.

Spacing can be added between bytes (``mem_bytesep``) and bytewords
(``mem_wordsep``), or both (``mem_allsep``). By default, the memory dumps
with no spacing (``mem_nosep``).

..  code-block:: c++

    int foo = 12345;
    int* fooptr = &foo;
    ioc << "Memory dump of foo: " << ptr_memory << mem_bytesep << fooptr << io_end;

    char* bar = "My name is Bob, and I am a coder.\0";
    ioc << "Memory dump of bar: " << ptr_memory << mem_allsep << bar << io_end;

    /*OUTPUT:
    Memory dump of foo: 39 30 00 00
    Memory dump of bar: 4d 79 20 6e 61 6d 65 20 | 69 73 20 42 6f 62 2c 20 | 61 6e 64 20 49 20 61 6d | 20 61 20 63 6f 64 65 72 | 2e 00
    */

You can print memory from any pointer, though you must specify the number of
bytes to read using ``read_bytes()``.

.. WARNING:: This feature must be used with caution, as reading too many bytes
    can trigger segfaults or any number of memory errors. Use the sizeof
    operator in the read_bytes() argument to prevent these types of problems.
    (See code).

The following is the safest way to dump the raw memory for a custom object.

..  code-block:: c++

    //Let's define a struct as our custom object, and make an instance of it.
    struct CustomStruct
    {
        int foo = 12345;
        double bar = 123.987654321;
        char faz[15] = "Hello, world!\0";
        void increment(){foo++;bar++;}
    };
    CustomStruct blah;

    ioc << ptr_memory << mem_allsep << read_size(sizeof blah) << &blah << io_end;
    /*OUTPUT:
    39 30 00 00 00 00 00 00 | ad 1c 78 ba 35 ff 5e 40 | 48 65 6c 6c 6f 2c 20 77 | 6f 72 6c 64 21 00 00 00
    */

..  index::
    pair: output; control

Bitset
----------------------------------------

IOChannel is able to intelligently output the contents of any bitset. It
temporarily forces use of the ``readsize()`` and ``ptr_memory`` parameters
in order to ensure proper output.

One may use any of the ``IOFormatMemorySeperator`` parameters to control the
style of output. By default, ``mem_nosep`` is used.

..  code-block:: c++

    bitset<32> foo = bitset<32>(12345678);
    ioc << mem_allsep << foo << io_end;
    /* OUTPUT:
    4e 61 bc 00
    */

Stream Control
------------------------------------------------

There are multiple enums for controlling IOChannel's output. All of these are
compatible with ``std::cout`` and ``printf``.

For example, one might want to display progress on the same line, and then
move to a new line for a final message. This can be accomplished via...

..  code-block:: c++

    ioc << "Let's Watch Progress!" << io_end;
    ioc << fg_blue << ta_bold << io_send_keep;
    for(int i=0; i<100; i++)
    {
        //Some long drawn out code here.
        ioc << i << "%" << io_show_keep;
    }
    ioc << io_end << io_flush;
    ioc << "Wasn't that fun?" << io_end;

    /* FINAL OUTPUT:
    Let's Watch Progress!
    100%
    Wasn't that fun?
    */

The complete list of stream controls is as follows. Some notes...

* \n is a newline.
* \r is simply a carriage return (move to start of current line).
* EoM indicates "End of Message", meaning IOChannel will broadcast the
    message at this point.
* R means "Remove Formatting", where all format tags are reset to their defaults.
* F indicates a "flush", which forces stdout to refresh. This is generally
    necessary when overwriting a line or moving to a new line after
    overwriting a previous one.

+---------------------+---------+------+-----+----+
| Command             | Appends | EoM? | RM? | F? |
+=====================+=========+======+=====+====+
| ``io_end``          | ``\n``  | X    | X   |    |
+---------------------+---------+------+-----+----+
| ``io_end_keep``     | ``\n``  | X    |     |    |
+---------------------+---------+------+-----+----+
| ``io_send``         |         | X    | X   |    |
+---------------------+---------+------+-----+----+
| ``io_send_keep``    |         | X    |     |    |
+---------------------+---------+------+-----+----+
| ``io_endline``      | ``\n``  |      | X   |    |
+---------------------+---------+------+-----+----+
| ``io_endline_keep`` | ``\n``  |      |     |    |
+---------------------+---------+------+-----+----+
| ``io_show``         | ``\r``  | X    | X   | X  |
+---------------------+---------+------+-----+----+
| ``io_show_keep``    | ``\r``  | X    |     | X  |
+---------------------+---------+------+-----+----+
| ``io_flush``        |         |      |     | X  |
+---------------------+---------+------+-----+----+

..  index::
    pair: output; cursor movement

Cursor Movement
----------------------------------------------

IOChannel can move the cursor back and forth on ANSI-enabled terminals
using the `cur_left` and `cur_right` enums.

..  code-block:: c++

    std::string buffer;
    pawlib::ioc << "Hello, world!"
                << pawlib::ioformat::cur_left
                << pawlib::ioformat::cur_left
                << pawlib::io_send;
    std::getline(std::cin, buffer);

    /* Will now wait for user input, while displaying "Hello, world!"
     * with the cursor highlighting the 'd' character.
     */

.. IMPORTANT:: Currently, only ANSI is used. Windows support,
   formatting-removed, and an easy-to-parse formatting flag system for custom
   outputs will be added soon.

..  index::
    pair: output; broadcast
    pair: output; forwarding

Internal Broadcast Settings
----------------------------------------------

IOChannel can internally output to either ``printf()`` or ``std::cout``
(or neither). By default, it uses printf(). However, as stated, this can be
changed.

IOChannel's internal output also broadcasts all messages by default. This can
also be changed.

These settings are modified using the ``configure_echo()`` member function.
(The arguments are all IOFormat enumerations).

..  code-block:: c++

    //Set to use `std::cout`
    ioc.configure_echo(echo_cout);

    //Set to use `printf` and show only error messages (any verbosity)
    ioc.configure_echo(echo_printf, vrb_tmi, cat_error);

    //Set to use `cout` and show only "quiet" verbosity messages.
    ioc.configure_echo(echo_cout, vrb_quiet);

    //Turn off internal output.
    ioc.configure_echo(echo_none);

External Broadcast with Signals
-------------------------------------------------
One of the primary features of IOChannel is that it can be connected to
multiple outputs using signals. Examples of this might be if you want to
output to a log file, or display messages in a console in your interface.

Main Signal (``signal_all``)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The main signal is ``signal_all``, which requires a callback function of the
form ``void callback(std::string, IOFormatVerbosity, IOFormatCategory)``,
as seen in the following example.

..  code-block:: c++

    //This is our callback function.
    void print(std::string msg, IOFormatVerbosity vrb, IOFormatCategory cat)
    {
        //Handle the message however we want.
        std::cout << msg;
    }

    //We connect the callback function to `signal_all` so we get all messages.
    ioc.signal_all.add(&print);

Category Signals (``signal_c_...``)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Almost all categories have a signal: ``signal_c_normal``, ``signal_c_warning``,
``signal_c_error``, ``signal_c_testing``, and ``signal_c_debug``.

.. NOTE:: ``cat_all`` is used internally, and does not have a signal.
    Use ``signal_all`` instead.

The callbacks for category signals require the form
``void callback(std::string, IOFormatVerbosity)``. Below is an example.

..  code-block:: c++

    //This is our callback function.
    void print_error(std::string msg, IOFormatVerbosity vrb)
    {

    //Handle the message however we want.
    std::cout << msg;

    }

    //We connect the callback function to signal_c_error to get only error messages.
    ioc.signal_c_error.add(&print_error);

Verbosity Signals (``signal_v_...``)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Each verbosity has a signal: ``signal_v_quiet``, ``signal_v_normal``,
``signal_v_chatty``, and ``signal_v_tmi``. A signal is broadcast when any
message of that verbosity or lower is transmitted.

The callbacks for verbosity signals require the form
``void callback(std::string, IOFormatCategory)``. Below is an example inside
the context of a class.

..  code-block:: c++

    class TestClass
    {
        public:
            TestClass(){}
            void output(std::string msg, IOFormatCategory cat)
            {
                //Handle the message however we want.
                std::cout << msg;
            }
            ~TestClass(){}
    };

    TestClass testObject;
    ioc.signal_v_normal.add(&testObject, TestClass::output)

Enumeration Lists
=============================================

..  index::
    pair: base; format
    see: radix; base

Base/Radix (``IOFormatBase``)
--------------------------------------------------------

+----------------+------+
| Enum           | Base |
+================+======+
| ``base_bin``   | 2    |
+----------------+------+
| ``base_2``     | 2    |
+----------------+------+
| ``base_ter``   | 3    |
+----------------+------+
| ``base_3``     | 3    |
+----------------+------+
| ``base_quat``  | 4    |
+----------------+------+
| ``base_4``     | 4    |
+----------------+------+
| ``base_quin``  | 5    |
+----------------+------+
| ``base_5``     | 5    |
+----------------+------+
| ``base_sen``   | 6    |
+----------------+------+
| ``base_6``     | 6    |
+----------------+------+
| ``base_sep``   | 7    |
+----------------+------+
| ``base_7``     | 7    |
+----------------+------+
| ``base_oct``   | 8    |
+----------------+------+
| ``base_8``     | 8    |
+----------------+------+
| ``base_9``     | 9    |
+----------------+------+
| ``base_dec``   | 10   |
+----------------+------+
| ``base_10``    | 10   |
+----------------+------+
| ``base_und``   | 11   |
+----------------+------+
| ``base_11``    | 11   |
+----------------+------+
| ``base_duo``   | 12   |
+----------------+------+
| ``base_doz``   | 12   |
+----------------+------+
| ``base_12``    | 12   |
+----------------+------+
| ``base_13``    | 13   |
+----------------+------+
| ``base_tetra`` | 14   |
+----------------+------+
| ``base_14``    | 14   |
+----------------+------+
| ``base_pent``  | 15   |
+----------------+------+
| ``base_15``    | 15   |
+----------------+------+
| ``base_hex``   | 16   |
+----------------+------+
| ``base_16``    | 16   |
+----------------+------+
| ``base_17``    | 17   |
+----------------+------+
| ``base_18``    | 18   |
+----------------+------+
| ``base_19``    | 19   |
+----------------+------+
| ``base_vig``   | 20   |
+----------------+------+
| ``base_20``    | 20   |
+----------------+------+
| ``base_21``    | 21   |
+----------------+------+
| ``base_22``    | 22   |
+----------------+------+
| ``base_23``    | 23   |
+----------------+------+
| ``base_24``    | 24   |
+----------------+------+
| ``base_25``    | 25   |
+----------------+------+
| ``base_26``    | 26   |
+----------------+------+
| ``base_27``    | 27   |
+----------------+------+
| ``base_28``    | 28   |
+----------------+------+
| ``base_29``    | 29   |
+----------------+------+
| ``base_30``    | 30   |
+----------------+------+
| ``base_31``    | 31   |
+----------------+------+
| ``base_32``    | 32   |
+----------------+------+
| ``base_33``    | 33   |
+----------------+------+
| ``base_34``    | 34   |
+----------------+------+
| ``base_35``    | 35   |
+----------------+------+
| ``base_36``    | 36   |
+----------------+------+

..  index::
    pair: boolean; format

Boolean Format (``IOFormatBool``)
--------------------------------------------------------

+----------------+-------------------------------+
| Enum           | Use                           |
+================+===============================+
| ``bool_lower`` | Lowercase - "true" or "false" |
+----------------+-------------------------------+
| ``bool_upper`` | Uppercase - "True" or "False" |
+----------------+-------------------------------+
| ``bool_caps``  | All caps - "TRUE" or "FALSE"  |
+----------------+-------------------------------+
| ``bool_num``   | Binary numerals - "0" or "1"  |
+----------------+-------------------------------+
| ``bool_scott`` | "Yea" or "Nay"                |
+----------------+-------------------------------+

Category (``IOFormatCategory``)
--------------------------------------------------------

+-----------------+-------------------------------------------------------------------------------------+
| Enum            | Use                                                                                 |
+=================+=====================================================================================+
| ``cat_normal``  | The default value - anything that doesn't fit elsewhere.                            |
+-----------------+-------------------------------------------------------------------------------------+
| ``cat_warning`` | Warnings, but not necessarily errors.                                               |
+-----------------+-------------------------------------------------------------------------------------+
| ``cat_error``   | Error messages.                                                                     |
+-----------------+-------------------------------------------------------------------------------------+
| ``cat_debug``   | Debug messages, such as variable outputs.                                           |
+-----------------+-------------------------------------------------------------------------------------+
| ``cat_testing`` | Messages in tests. (Goldilocks automatically suppresses these during benchmarking.) |
+-----------------+-------------------------------------------------------------------------------------+
| ``cat_all``     | All message categories. Does not have a correlating signal.                         |
+-----------------+-------------------------------------------------------------------------------------+

Cursor Control (``IOCursor``)
-----------------------------------------

+-----------------+--------------------------------------+
| Enum            | Use                                  |
+=================+======================================+
| ``cur_left``    | Moves the cursor left one position.  |
+-----------------+--------------------------------------+
| ``cur_right``   | Moves the cursor right one position. |
+-----------------+--------------------------------------+


Echo Mode (``IOEchoMode``)
-----------------------------------------

.. NOTE:: These cannot be passed directly to IOChannel.

+-----------------+-------------------------------------+
| Enum            | Use                                 |
+=================+=====================================+
| ``echo_none``   | No internal output.                 |
+-----------------+-------------------------------------+
| ``echo_printf`` | Internal output uses ``printf()``.  |
+-----------------+-------------------------------------+
| ``echo_cout``   | Internal output uses ``std::cout``. |
+-----------------+-------------------------------------+

..  index::
    pair: memory separators; format
    single: pointers; memory separators

Memory Separators (``IOFormatMemorySeperators``)
--------------------------------------------------------

+-----------------+-------------------------------------------------------------------------------------+
| Enum            | Action                                                                              |
+=================+=====================================================================================+
| ``mem_nosep``   | Output memory dump as one long string.                                              |
+-----------------+-------------------------------------------------------------------------------------+
| ``mem_bytesep`` | Output memory dump with spaces between bytes.                                       |
+-----------------+-------------------------------------------------------------------------------------+
| ``mem_wordsep`` | Output memory dump with bars between words (8 bytes).                               |
+-----------------+-------------------------------------------------------------------------------------+
| ``mem_allsep``  | Output memory dump with spaces between bytes and bars between words.                |
+-----------------+-------------------------------------------------------------------------------------+

..  index::
    pair: numeral case; format

Numeral Case (``IOFormatNumeralCase``)
--------------------------------------------------------

+-----------------+---------------------------------------+
| Enum            | Action                                |
+=================+=======================================+
| ``num_lower``   | Print all letter digits as lowercase. |
+-----------------+---------------------------------------+
| ``num_upper``   | Print all letter digits as uppercase. |
+-----------------+---------------------------------------+

..  index::
    pair: pointers; format

Pointer (``IOFormatPointer``)
--------------------------------------------------------

+-----------------+-------------------------------------------------------------------+
| Enum            | Action                                                            |
+=================+===================================================================+
| ``ptr_value``   | Print the value at the address.                                   |
+-----------------+-------------------------------------------------------------------+
| ``ptr_address`` | Print the actual memory address.                                  |
+-----------------+-------------------------------------------------------------------+
| ``ptr_memory``  | Dump the hexadecimal representation of the memory at the address. |
+-----------------+-------------------------------------------------------------------+

..  index::
    pair: significands; format

Significands(``set_significands``)
--------------------------------------------------------

``set_significands(n)`` where ``n`` is the significands, as an integer representing
the number of significands.

..  index::
    pair: read size; format
    single: pointer; read size

Memory Dump Read Size (``read_size``)
--------------------------------------------------------

``read_size(n)`` where ``n`` is the number of bytes to read and print, starting
at the memory address.

.. WARNING:: Misuse triggers undefined behavior, including SEGFAULT.
    Use with caution.

..  index::
    pair: scientific notation; format

Scientific Notation (``IOFormatSciNotation``)
--------------------------------------------------------

+-----------------+---------------------------------------+
| Enum            | Action                                |
+=================+=======================================+
| ``sci_none``    | No scientific notation.               |
+-----------------+---------------------------------------+
| ``sci_auto``    | Automatically select the best option. |
+-----------------+---------------------------------------+
| ``sci_on``      | Force use of scientific notation.     |
+-----------------+---------------------------------------+

..  WARNING:: ``sci_none`` has been known to cause truncation in very large and
    very small values, regardless of significands.

..  index::
    pair: text attributes; format

Text Attributes(``IOFormatTextAttributes``)
--------------------------------------------------------

+------------------+------------------------------------------+
| Enum             | Action                                   |
+==================+==========================================+
| ``ta_none``      | Turn off all attributes.                 |
+------------------+------------------------------------------+
| ``ta_bold``      | **Bold text**.                           |
+------------------+------------------------------------------+
| ``ta_underline`` | Underlined text.                         |
+------------------+------------------------------------------+
| ``ta_invert``    | Invert foreground and background colors. |
+------------------+------------------------------------------+

..  index::
    pair: color, background; format

Text Background Color(``IOFormatTextBG``)
--------------------------------------------------------

+-----------------+---------------------------------------+
| Enum            | Action                                |
+=================+=======================================+
| ``bg_none``     | Default text background.              |
+-----------------+---------------------------------------+
| ``bg_black``    | Black text background.                |
+-----------------+---------------------------------------+
| ``bg_red``      | Red text background.                  |
+-----------------+---------------------------------------+
| ``bg_green``    | Green text background.                |
+-----------------+---------------------------------------+
| ``bg_yellow``   | Yellow text background.               |
+-----------------+---------------------------------------+
| ``bg_blue``     | Blue text background.                 |
+-----------------+---------------------------------------+
| ``bg_magenta``  | Meganta text background.              |
+-----------------+---------------------------------------+
| ``bg_cyan``     | Cyan text background.                 |
+-----------------+---------------------------------------+
| ``bg_white``    | White text background.                |
+-----------------+---------------------------------------+

..  index::
    pair: color, foreground; format

Text Foreground Color(``IOFormatTextFG``)
--------------------------------------------------------

+-----------------+---------------------------------------+
| Enum            | Action                                |
+=================+=======================================+
| ``fg_none``     | Default text foreground.              |
+-----------------+---------------------------------------+
| ``fg_black``    | Black text foreground.                |
+-----------------+---------------------------------------+
| ``fg_red``      | Red text foreground.                  |
+-----------------+---------------------------------------+
| ``fg_green``    | Green text foreground.                |
+-----------------+---------------------------------------+
| ``fg_yellow``   | Yellow text foreground.               |
+-----------------+---------------------------------------+
| ``fg_blue``     | Blue text foreground.                 |
+-----------------+---------------------------------------+
| ``fg_magenta``  | Meganta text foreground.              |
+-----------------+---------------------------------------+
| ``fg_cyan``     | Cyan text foreground.                 |
+-----------------+---------------------------------------+
| ``fg_white``    | White text foreground.                |
+-----------------+---------------------------------------+

Verbosity/Priority (``IOFormatVerbosity``)
--------------------------------------------------------

+-----------------+---------------------------------------------------------------------------------------------------+
| Enum            | Use                                                                                               |
+=================+===================================================================================================+
| ``vrb_quiet``   | Only essential messages and errors. For normal end-use. Shipping default.                         |
+-----------------+---------------------------------------------------------------------------------------------------+
| ``vrb_normal``  | Common messages and errors. For common and normal end-user testing.                               |
+-----------------+---------------------------------------------------------------------------------------------------+
| ``vrb_chatty``  | Most messages and errors. For detailed testing and debugging.                                     |
+-----------------+---------------------------------------------------------------------------------------------------+
| ``vrb_tmi``     | Absolutely everything. For intense testing, detailed debugging, and driving the developers crazy. |
+-----------------+---------------------------------------------------------------------------------------------------+
