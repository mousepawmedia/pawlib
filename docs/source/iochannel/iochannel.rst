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

Documentation Assumptions
-------------------------------------

For purposes of expediency, the default global static instance ``pawlib::ioc``
will be used in this documentation. Furthermore, we will assume that
``using namespace pawlib;`` is being used. All namespaces outside of the
scope of PawLIB will be stated explicitly.

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

+------------+--------------------+------------------------------------------------------------------+
| Category   | Enum               | Use                                                              |
+============+====================+==================================================================+
| Normal     | ``IOCat::normal``  | Regular use messages, especially those you want the user to see. |
+------------+--------------------+------------------------------------------------------------------+
| Warning    | ``IOCat::warning`` | Warnings about potential problems.                               |
+------------+--------------------+------------------------------------------------------------------+
| Error      | ``IOCat::error``   | Error messages.                                                  |
+------------+--------------------+------------------------------------------------------------------+
| Debug      | ``IOCat::debug``   | Messages that might help you track down problems.                |
+------------+--------------------+------------------------------------------------------------------+
| Testing    | ``IOCat::testing`` | Messages related solely to testing.                              |
+------------+--------------------+------------------------------------------------------------------+
| All        | ``IOCat::all``     | All of the above.                                                |
+------------+--------------------+------------------------------------------------------------------+

One of the advantages of this system is that you can actually leave messages
in the code, and just control when and how they are processed and broadcast.
This means you can actually ship with debugging statements still alive in the
code, allowing you to diagnose problems on any machine.

..  index::
    pair: output; verbosity
    see: priority; verbosity

Verbosity
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Some messages we need to see every time, and others only in special
circumstances. This is what verbosity is for.

+------------+-------------------+---------------------------------------------------------------------------------------------------+
| Verbosity  | Enum              | Use                                                                                               |
+============+===================+===================================================================================================+
| Quiet      | ``IOVrb::quiet``  | Only essential messages and errors. For normal end-use. Shipping default.                         |
+------------+-------------------+---------------------------------------------------------------------------------------------------+
| Normal     | ``IOVrb::normal`` | Common messages and errors. For common and normal end-user testing.                               |
+------------+-------------------+---------------------------------------------------------------------------------------------------+
| Chatty     | ``IOVrb::chatty`` | Most messages and errors. For detailed testing and debugging.                                     |
+------------+-------------------+---------------------------------------------------------------------------------------------------+
| TMI        | ``IOVrb::tmi``    | Absolutely everything. For intense testing, detailed debugging, and driving the developers crazy. |
+------------+-------------------+---------------------------------------------------------------------------------------------------+

One example of verbosity in action would be in debugging messages. A
notification about a rare and potentially problematic function being called
might be ``IOVrb::normal``, while the output of a loop iterator would probably
be ``IOVrb::tmi``.

..  index::
    single: output

Output
=======================================

General
--------------------------------------

All output is done using the stream insertion (``<<``) operator, in the same
manner as with ``std::cout``. Before a message is broadcast, a stream
control flags such as ``IOCtrl::endl`` must be passed.

``IOCtrl::endl`` serves as an "end of transmission" [EoT] flag, clears any
formatting set during the stream, and inserts a final newline character before
flushing the stream. Thus, ``\n`` is not needed if the output should be
displayed on a single line. This functionality also allows a single
transmission to be split up over multiple lines, if necessary. Other stream
control enumerations have different behaviors. (See `Stream Control`_)

..  code-block:: c++

    ioc << "This is the first part. ";
    //Some more code here.
    ioc << "This is the second part." << IOCtrl::endl;

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

    ioc << "Hello, world!" << IOCtrl::endl;
    //OUTPUT: "Hello, world!"

    char* cstr = "I am a Cstring.\0";
    ioc << cstr << IOCtrl::endl;
    //OUTPUT: "I am a Cstring."

    std::string stdstr = "I am a standard string.";
    ioc << stdstr << IOCtrl::endl;
    //OUTPUT: "I am a standard string."

..  index::
    pair: output; formatting

Formatting
----------------------------------------

Cross-platform output formatting is built in to IOChannel. This means that
formatting can be set using the IOFormat flags, and it will display
correctly on each output and environment.

..  code-block:: c++

    ioc << IOFormatTextAttr::bold << IOFormatTextFG::red << "This is bold, red text. "
        << IOFormatTextAttr::underline << IOFormatTextFG::blue << IOFormatTextBG::yellow << "This is bold, underline, blue text with a yellow background. "
        << IOFormatTextAttr::none << IOFormatTextFG::none << IOFormatTextBG::none << "This is normal text."
        << IOCtrl::endl;
    //The output is exactly what you'd expect.

..  IMPORTANT:: Currently, only ANSI is used. Windows support,
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
    ioc << foo << IOCtrl::endl;
    //OUTPUT: "TRUE"

The output style can be adjusted, however, using the ``IOFormatBool::`` flags.

..  code-block:: c++

    bool foo = true;
    ioc << IOFormatBool::lower << foo << IOCtrl::endl;
    //OUTPUT: "true"
    ioc << IOFormatBool::upper << foo << IOCtrl::endl;
    //OUTPUT: "True"
    ioc << IOFormatBool::caps << foo << IOCtrl::endl;
    //OUTPUT: "TRUE"
    ioc << IOFormatBool::numeral << foo << IOCtrl::endl;
    //OUTPUT: "1"

..  index::
    pair: output; char

Char
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Since char can represent both an integer and a character, IOChannel lets
you display it as either. By default, IOChannel displays the char as a literal
character. Using the ``IOFormatCharValue::as_int`` flag forces it to print as
an integer.

..  code-block:: c++

    char foo = 'A';
    ioc << "Character " << foo << " has ASCII value "
        << IOFormatCharValue::as_int << foo << IOCtrl::endl;
    //OUTPUT: Character A has ASCII value 65

When output as an integer, char can be used with all of the enumerations for
int (see that section).

..  index::
    pair: output; integers

Integer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

An ``int`` can be represented in any base (radix) from binary (base 2) to
base 35 using the ``IOFormatBase::`` flags.

..  code-block:: c++

    int foo = 12345;
    ioc << "Binary: " << IOFormatBase::bin << foo << IOCtrl::endl;
    ioc << "Octal: " << IOFormatBase::oct << foo << IOCtrl::endl;
    ioc << "Decimal: " << IOFormatBase::dec << foo << IOCtrl::endl;
    ioc << "Dozenal: " << IOFormatBase::doz << foo << IOCtrl::endl;
    ioc << "Hexadecimal: " << IOFormatBase::hex << foo << IOCtrl::endl;
    ioc << "Base 31: " << IOFormatBase::b31 << foo << IOCtrl::endl;

    /*OUTPUT:
    Binary: 11000000111001
    Octal: 30071
    Decimal: 12345
    Dozenal: 7189
    Hexadecimal: 3039
    Base 31: cq7
    */

In bases larger than decimal (10), the letter numerals can be output as
lowercase or uppercase (default) using the ``IOFormatNumCase::`` flags.

..  code-block:: c++

    int foo = 187254;
    ioc << "Hexadecimal Lower: " << IOFormatBase::hex << foo << IOCtrl::endl;
    ioc << "Hexadecimal Upper: " << IOFormatNumCase::upper
        << IOFormatBase::hex << foo << IOCtrl::endl;

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

Significands can be modified using the ``IOFormatSignificands(#)`` flag.
Scientific notation can be turned on with ``IOFormatSciNotation::on``,
and off using ``IOFormatSciNotation::none``. It can also be reset to automatic
with ``IOFormatSciNotation::automatic``.

..  code-block:: c++

    float foo = 12345.12345678912345;
    ioc << "Significands 5, no sci: " << IOFormatSignificands(5) << foo << IOCtrl::endl;
    ioc << "Significands 10, sci: " << IOFormatSignificands(10)
        << IOFormatSciNotation::on << foo << IOCtrl::endl;

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
can also be forced using ``IOFormatPtr::value``.

..  code-block:: c++

    int foo = 12345;
    int* fooptr = &foo;
    ioc << "Value of foo: " << IOFormatPtr::value << fooptr << IOCtrl::endl;

    char* bar = "My name is Bob, and I am a coder.\0";
    ioc << "Value of bar: " << bar << IOCtrl::endl;

    /*OUTPUT:
    Value of foo: 12345
    Value of bar: My name is Bob, and I am a coder.
    */

Pointer Address
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
IOChannel can print out the address of the pointer in hexadecimal using
``IOFormatPtr::address``. It displays with lowercase letter numerals by default,
though these can be displayed in uppercase using ``IOFormatNumCase::upper``.
It is capable of doing this with any pointer, even for custom objects.

..  code-block:: c++

    int foo = 12345;
    int* fooptr = &foo;
    ioc << "Address of foo: " << IOFormatPtr::address << fooptr << IOCtrl::endl;

    char* bar = "My name is Bob, and I am a coder.\0";
    ioc << "Address of bar: " << IOFormatPtr::address << IOFormatNumCase::upper
        << bar << IOCtrl::endl;

    /*OUTPUT:
    Address of foo: 0x7ffc33518308
    Address of bar: 0x405AF0
    */

Pointer Memory Dump
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
IOChannel is capable of dumping the raw memory at any pointer using
``IOFormatPtr::memory``. The function is safe for pointers to most objects and
atomic types, as the memory dump will automatically determine the size
and will never overrun the size of the variable. With char pointers (cstring),
the only danger is when the cstring is not null terminated.

Spacing can be added between bytes (``IOFormatMemSep::byte``) and bytewords
(``IOFormatMemSep::word``), or both (``IOFormatMemSep::all``). By default,
the memory dumps with no spacing (``IOFormatMemSep::none``).

..  code-block:: c++

    int foo = 12345;
    int* fooptr = &foo;
    ioc << "Memory dump of foo: " << IOFormatPtr::memory << IOFormatMemSep::byte
        << fooptr << IOCtrl::endl;

    char* bar = "My name is Bob, and I am a coder.\0";
    ioc << "Memory dump of bar: " << IOFormatPtr::memory << IOFormatMemSep::all
        << bar << IOCtrl::endl;

    /*OUTPUT:
    Memory dump of foo: 39 30 00 00
    Memory dump of bar: 4d 79 20 6e 61 6d 65 20 | 69 73 20 42 6f 62 2c 20 | 61 6e 64 20 49 20 61 6d | 20 61 20 63 6f 64 65 72 | 2e 00
    */

The following dumps the raw memory for a custom object.

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

    ioc << IOFormatPtr::memory << IOFormatMemSep::all << &blah << IOCtrl::endl;
    /*OUTPUT:
    39 30 00 00 00 00 00 00 | ad 1c 78 ba 35 ff 5e 40 | 48 65 6c 6c 6f 2c 20 77 | 6f 72 6c 64 21 00 00 00
    */

You can also read memory from a void pointer, though you must specify the
number of bytes to read using ``IOMemReadSize()``.

.. WARNING:: This feature must be used with caution, as reading too many bytes
    can trigger segfaults or any number of memory errors. Use the sizeof
    operator in the read_bytes() argument to prevent these types of problems.
    (See code).

..  index::
    pair: output; control

Bitset
----------------------------------------

IOChannel is able to intelligently output the contents of any bitset. It
temporarily forces use of the ``IOFormatPtr::memory`` flag to ensure proper
output.

One may use any of the ``IOFormatMemSep::`` flags to control the
style of output. By default, ``IOFormatMemSep::none`` is used.

..  code-block:: c++

    bitset<32> foo = bitset<32>(12345678);
    ioc << IOFormatMemSep::all << foo << IOCtrl::endl;
    /* OUTPUT:
    4e 61 bc 00
    */

Stream Control
------------------------------------------------

There are multiple enums for controlling IOChannel's output.

For example, one might want to display progress on the same line, and then
move to a new line for a final message. This can be accomplished via...

..  code-block:: c++

    ioc << "Let's Watch Progress!" << IOCtrl::endl;
    ioc << fg_blue << ta_bold;
    for(int i=0; i<100; i++)
    {
        //Some long drawn out code here.
        ioc << i << "%" << IOCtrl::sendc;
    }
    ioc << io_endl;
    ioc << "Wasn't that fun?" << io_endl;

    /* FINAL OUTPUT:
    Let's Watch Progress!
    100%
    Wasn't that fun?
    */

The complete list of stream controls is as follows. Some notes...

*   EoM indicates "End of Message", meaning IOChannel will broadcast the
    message at this point.
*   \n is a newline.
*   \r is simply a carriage return (move to start of current line).
*   Clear means all formatting flags are reset to their defaults.
*   Flush forces stdout to refresh. This is generally necessary when
    overwriting a line or moving to a new line after
    overwriting a previous one.

+---------------------+-----+-------+----+----+-------+
| Command             | EoM | Clear | \r | \n | Flush |
+=====================+=====+=======+====+====+=======+
| ``IOCtrl::clear``   |     | X     |    |    |       |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::flush``   |     |       |    |    | X     |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::end``     | X   | X     |    |    |       |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::endc``    | X   | X     | X  |    | X     |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::endl``    | X   | X     |    | X  | X     |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::send``    | X   |       |    |    |       |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::sendc``   | X   |       | X  |    | X     |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::sendl``   | X   |       |    | X  | X     |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::r``       |     |       | X  |    |       |
+---------------------+-----+-------+----+----+-------+
| ``IOCtrl::n``       |     |       |    | X  |       |
+---------------------+-----+-------+----+----+-------+

..  index::
    pair: output; cursor movement

Cursor Movement
----------------------------------------------

IOChannel can move the cursor back and forth on ANSI-enabled terminals
using the `IOCursor::left` and `IOCursor::right` flags.

..  code-block:: c++

    std::string buffer;
    pawlib::ioc << "Hello, world!"
                << IOCursor::left
                << IOCursor::left
                << IOCtrl::end;
    std::getline(std::cin, buffer);

    /* Will now wait for user input, while displaying "Hello, world!"
     * with the cursor highlighting the 'd' character.
     */

..  IMPORTANT:: Currently, only ANSI is used. Windows support,
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

These settings are modified by passing a ``IOEchoMode::`` flag to the
``configure_echo()`` member function.

..  code-block:: c++

    //Set to use `std::cout`
    ioc.configure_echo(IOEchoMode::cout);

    //Set to use `printf` and show only error messages (any verbosity)
    ioc.configure_echo(IOEchoMode::printf, IOVrb::tmi, IOCat::error);

    //Set to use `cout` and show only "quiet" verbosity messages.
    ioc.configure_echo(IOEchoMode::cout, IOVrb::quiet);

    //Turn off internal output.
    ioc.configure_echo(IOEchoMode::none);

External Broadcast with Signals
-------------------------------------------------
One of the primary features of IOChannel is that it can be connected to
multiple outputs using signals. Examples of this might be if you want to
output to a log file, or display messages in a console in your interface.

Main Signal (``signal_all``)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The main signal is ``signal_all``, which requires a callback function of the
form ``void callback(std::string, IOVrb, IOCat)``,
as seen in the following example.

..  code-block:: c++

    //This is our callback function.
    void print(std::string msg, IOVrb vrb, IOCat cat)
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
``void callback(std::string, IOVrb)``. Below is an example.

..  code-block:: c++

    //This is our callback function.
    void print_error(std::string msg, IOVrb vrb)
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
``void callback(std::string, IOCat)``. Below is an example inside
the context of a class.

..  code-block:: c++

    class TestClass
    {
        public:
            TestClass(){}
            void output(std::string msg, IOCat cat)
            {
                //Handle the message however we want.
                std::cout << msg;
            }
            ~TestClass(){}
    };

    TestClass testObject;
    ioc.signal_v_normal.add(&testObject, TestClass::output)

Flag Lists
=============================================

..  index::
    single: category

Category (``IOCat::``)
--------------------------------------------------------

+--------------------+-------------------------------------------------------------------------------------+
| Flag               | Use                                                                                 |
+====================+=====================================================================================+
| ``IOCat::normal``  | The default value - anything that doesn't fit elsewhere.                            |
+--------------------+-------------------------------------------------------------------------------------+
| ``IOCat::warning`` | Warnings, but not necessarily errors.                                               |
+--------------------+-------------------------------------------------------------------------------------+
| ``IOCat::error``   | Error messages.                                                                     |
+--------------------+-------------------------------------------------------------------------------------+
| ``IOCat::debug``   | Debug messages, such as variable outputs.                                           |
+--------------------+-------------------------------------------------------------------------------------+
| ``IOCat::testing`` | Messages in tests. (Goldilocks automatically suppresses these during benchmarking.) |
+--------------------+-------------------------------------------------------------------------------------+
| ``IOCat::all``     | All message categories. Does not have a correlating signal.                         |
+--------------------+-------------------------------------------------------------------------------------+

..  index::
    single: cursor

Cursor Control (``IOCursor::``)
-----------------------------------------

+-----------------------+--------------------------------------+
| Flag                  | Use                                  |
+=======================+======================================+
| ``IOCursor::left``    | Moves the cursor left one position.  |
+-----------------------+--------------------------------------+
| ``IOCursor::right``   | Moves the cursor right one position. |
+-----------------------+--------------------------------------+

..  index::
    single: output, echo

Echo Mode (``IOEchoMode::``)
-----------------------------------------

.. NOTE:: These cannot be passed directly to IOChannel.

+------------------------+-------------------------------------+
| Flag                   | Use                                 |
+========================+=====================================+
| ``IOEchoMode::none``   | No internal output.                 |
+------------------------+-------------------------------------+
| ``IOEchoMode::printf`` | Internal output uses ``printf()``.  |
+------------------------+-------------------------------------+
| ``IOEchoMode::cout``   | Internal output uses ``std::cout``. |
+------------------------+-------------------------------------+

..  index::
    pair: base; format
    see: radix; base

Base/Radix Format (``IOFormatBase::``)
--------------------------------------------------------

+-------------------------+------+
| Flag                    | Base |
+=========================+======+
| ``IOFormatBase::bin``   | 2    |
+-------------------------+------+
| ``IOFormatBase::b2``    | 2    |
+-------------------------+------+
| ``IOFormatBase::ter``   | 3    |
+-------------------------+------+
| ``IOFormatBase::b3``    | 3    |
+-------------------------+------+
| ``IOFormatBase::quat``  | 4    |
+-------------------------+------+
| ``IOFormatBase::b4``    | 4    |
+-------------------------+------+
| ``IOFormatBase::quin``  | 5    |
+-------------------------+------+
| ``IOFormatBase::b5``    | 5    |
+-------------------------+------+
| ``IOFormatBase::sen``   | 6    |
+-------------------------+------+
| ``IOFormatBase::b6``    | 6    |
+-------------------------+------+
| ``IOFormatBase::sep``   | 7    |
+-------------------------+------+
| ``IOFormatBase::b7``    | 7    |
+-------------------------+------+
| ``IOFormatBase::oct``   | 8    |
+-------------------------+------+
| ``IOFormatBase::b8``    | 8    |
+-------------------------+------+
| ``IOFormatBase::b9``    | 9    |
+-------------------------+------+
| ``IOFormatBase::dec``   | 10   |
+-------------------------+------+
| ``IOFormatBase::b10``   | 10   |
+-------------------------+------+
| ``IOFormatBase::und``   | 11   |
+-------------------------+------+
| ``IOFormatBase::b11``   | 11   |
+-------------------------+------+
| ``IOFormatBase::duo``   | 12   |
+-------------------------+------+
| ``IOFormatBase::doz``   | 12   |
+-------------------------+------+
| ``IOFormatBase::b12``   | 12   |
+-------------------------+------+
| ``IOFormatBase::tri``   | 13   |
+-------------------------+------+
| ``IOFormatBase::b13``   | 13   |
+-------------------------+------+
| ``IOFormatBase::tetra`` | 14   |
+-------------------------+------+
| ``IOFormatBase::b14``   | 14   |
+-------------------------+------+
| ``IOFormatBase::pent``  | 15   |
+-------------------------+------+
| ``IOFormatBase::b15``   | 15   |
+-------------------------+------+
| ``IOFormatBase::hex``   | 16   |
+-------------------------+------+
| ``IOFormatBase::b16``   | 16   |
+-------------------------+------+
| ``IOFormatBase::b17``   | 17   |
+-------------------------+------+
| ``IOFormatBase::b18``   | 18   |
+-------------------------+------+
| ``IOFormatBase::b19``   | 19   |
+-------------------------+------+
| ``IOFormatBase::vig``   | 20   |
+-------------------------+------+
| ``IOFormatBase::b20``   | 20   |
+-------------------------+------+
| ``IOFormatBase::b21``   | 21   |
+-------------------------+------+
| ``IOFormatBase::b22``   | 22   |
+-------------------------+------+
| ``IOFormatBase::b23``   | 23   |
+-------------------------+------+
| ``IOFormatBase::b24``   | 24   |
+-------------------------+------+
| ``IOFormatBase::b25``   | 25   |
+-------------------------+------+
| ``IOFormatBase::b26``   | 26   |
+-------------------------+------+
| ``IOFormatBase::b27``   | 27   |
+-------------------------+------+
| ``IOFormatBase::b28``   | 28   |
+-------------------------+------+
| ``IOFormatBase::b29``   | 29   |
+-------------------------+------+
| ``IOFormatBase::b30``   | 30   |
+-------------------------+------+
| ``IOFormatBase::b31``   | 31   |
+-------------------------+------+
| ``IOFormatBase::b32``   | 32   |
+-------------------------+------+
| ``IOFormatBase::b33``   | 33   |
+-------------------------+------+
| ``IOFormatBase::b34``   | 34   |
+-------------------------+------+
| ``IOFormatBase::b35``   | 35   |
+-------------------------+------+
| ``IOFormatBase::b36``   | 36   |
+-------------------------+------+

..  index::
    pair: boolean; format

Boolean Format (``IOFormatBool::``)
--------------------------------------------------------

+-------------------------+-------------------------------+
| Flag                    | Use                           |
+=========================+===============================+
| ``IOFormatBool::lower`` | Lowercase - "true" or "false" |
+-------------------------+-------------------------------+
| ``IOFormatBool::upper`` | Uppercase - "True" or "False" |
+-------------------------+-------------------------------+
| ``IOFormatBool::caps``  | All caps - "TRUE" or "FALSE"  |
+-------------------------+-------------------------------+
| ``IOFormatBool::num``   | Binary numerals - "0" or "1"  |
+-------------------------+-------------------------------+
| ``IOFormatBool::scott`` | "Yea" or "Nay"                |
+-------------------------+-------------------------------+

..  index::
    pair: char type; format

Char Value (``IOFormatCharValue::``)
--------------------------------------------------------

+--------------------------------+---------------------------------------+
| Enum                           | Action                                |
+================================+=======================================+
| ``IOFormatCharValue::as_char`` | Output chars as ASCII characters.     |
+--------------------------------+---------------------------------------+
| ``IOFormatCharValue::as_int``  | Output chars as integers.             |
+--------------------------------+---------------------------------------+

..  index::
    pair: memory separators; format
    single: pointers; memory separators

Memory Separators (``IOFormatMemSep::``)
--------------------------------------------------------

+--------------------------+-------------------------------------------------------------------------------------+
| Enum                     | Action                                                                              |
+==========================+=====================================================================================+
| ``IOFormatMemSep::no``   | Output memory dump as one long string.                                              |
+--------------------------+-------------------------------------------------------------------------------------+
| ``IOFormatMemSep::byte`` | Output memory dump with spaces between bytes.                                       |
+--------------------------+-------------------------------------------------------------------------------------+
| ``IOFormatMemSep::word`` | Output memory dump with bars between words (8 bytes).                               |
+--------------------------+-------------------------------------------------------------------------------------+
| ``IOFormatMemSep::all``  | Output memory dump with spaces between bytes and bars between words.                |
+--------------------------+-------------------------------------------------------------------------------------+

..  index::
    pair: numeral case; format

Numeral Case (``IOFormatNumCase::``)
--------------------------------------------------------

+------------------------------+---------------------------------------+
| Enum                         | Action                                |
+==============================+=======================================+
| ``IOFormatNumCase::lower``   | Print all letter digits as lowercase. |
+------------------------------+---------------------------------------+
| ``IOFormatNumCase::upper``   | Print all letter digits as uppercase. |
+------------------------------+---------------------------------------+

..  index::
    pair: pointers; format

Pointer Format (``IOFormatPtr::``)
--------------------------------------------------------

+--------------------------+-------------------------------------------------------------------+
| Enum                     | Action                                                            |
+==========================+===================================================================+
| ``IOFormatPtr::value``   | Print the value at the address.                                   |
+--------------------------+-------------------------------------------------------------------+
| ``IOFormatPtr::address`` | Print the actual memory address.                                  |
+--------------------------+-------------------------------------------------------------------+
| ``IOFormatPtr::memory``  | Dump the hexadecimal representation of the memory at the address. |
+--------------------------+-------------------------------------------------------------------+

..  index::
    pair: scientific notation; format

Scientific Notation Format (``IOFormatSciNotation::``)
--------------------------------------------------------

+----------------------------------+---------------------------------------+
| Enum                             | Action                                |
+==================================+=======================================+
| ``IOFormatSciNotation::none``    | No scientific notation.               |
+----------------------------------+---------------------------------------+
| ``IOFormatSciNotation::auto``    | Automatically select the best option. |
+----------------------------------+---------------------------------------+
| ``IOFormatSciNotation::on``      | Force use of scientific notation.     |
+----------------------------------+---------------------------------------+

..  WARNING:: ``IOFormatSciNotation::none`` has been known to cause truncation
    in very large and very small values, regardless of significands.

..  index::
    pair: significands; format

Significands(``IOFormatSignificands()``)
--------------------------------------------------------

``IOFormatSignificands(n)`` where ``n`` is the significands, as an integer
representing the number of significands.


..  index::
    pair: text attributes; format

Text Attributes(``IOFormatTextAttr::``)
--------------------------------------------------------

+---------------------------------+------------------------------------------+
| Enum                            | Action                                   |
+=================================+==========================================+
| ``IOFormatTextAttr::none``      | Turn off all attributes.                 |
+---------------------------------+------------------------------------------+
| ``IOFormatTextAttr::bold``      | **Bold text**.                           |
+---------------------------------+------------------------------------------+
| ``IOFormatTextAttr::underline`` | Underlined text.                         |
+---------------------------------+------------------------------------------+
| ``IOFormatTextAttr::invert``    | Invert foreground and background colors. |
+---------------------------------+------------------------------------------+

..  index::
    pair: color, background; format

Text Background Color(``IOFormatTextBG::``)
--------------------------------------------------------

+-----------------------------+---------------------------------------+
| Enum                        | Action                                |
+=============================+=======================================+
| ``IOFormatTextBG::none``    | Default text background.              |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::black``   | Black text background.                |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::red``     | Red text background.                  |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::green``   | Green text background.                |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::yellow``  | Yellow text background.               |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::blue``    | Blue text background.                 |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::magenta`` | Meganta text background.              |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::cyan``    | Cyan text background.                 |
+-----------------------------+---------------------------------------+
| ``IOFormatTextBG::white``   | White text background.                |
+-----------------------------+---------------------------------------+

..  index::
    pair: color, foreground; format

Text Foreground Color(``IOFormatTextFG::``)
--------------------------------------------------------

+----------------------------+---------------------------------------+
| Enum                       | Action                                |
+============================+=======================================+
| ``IOFormatTextFG::none``   | Default text foreground.              |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::black``  | Black text foreground.                |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::red``    | Red text foreground.                  |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::green``  | Green text foreground.                |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::yellow`` | Yellow text foreground.               |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::blue``   | Blue text foreground.                 |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::magenta``| Meganta text foreground.              |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::cyan``   | Cyan text foreground.                 |
+----------------------------+---------------------------------------+
| ``IOFormatTextFG::white``  | White text foreground.                |
+----------------------------+---------------------------------------+


..  index::
    pair: read size; format
    single: pointer; read size

Memory Dump Read Size (``IOMemReadSize()``)
--------------------------------------------------------

``IOMemReadSize(n)`` where ``n`` is the number of bytes to read and print,
starting at the memory address. **Only used with void pointers.**

..  WARNING:: Misuse triggers undefined behavior, including SEGFAULT.
    Use with caution.

..  index::
    single: verbosity; priority

Verbosity/Priority (``IOVrb::``)
--------------------------------------------------------

+--------------------+---------------------------------------------------------------------------------------------------+
| Enum               | Use                                                                                               |
+====================+===================================================================================================+
| ``IOVrb::quiet``   | Only essential messages and errors. For normal end-use. Shipping default.                         |
+--------------------+---------------------------------------------------------------------------------------------------+
| ``IOVrb::normal``  | Common messages and errors. For common and normal end-user testing.                               |
+--------------------+---------------------------------------------------------------------------------------------------+
| ``IOVrb::chatty``  | Most messages and errors. For detailed testing and debugging.                                     |
+--------------------+---------------------------------------------------------------------------------------------------+
| ``IOVrb::tmi``     | Absolutely everything. For intense testing, detailed debugging, and driving the developers crazy. |
+--------------------+---------------------------------------------------------------------------------------------------+
