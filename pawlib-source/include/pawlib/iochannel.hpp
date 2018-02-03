/** IOChannel [PawLIB]
  * Version: 1.0
  *
  * Allows managed, custom output to any console or terminal.
  * See WHAT IS IOCHANNEL? below.
  *
  * Author: Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Media.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

/* WHAT IS IOCHANNEL?
 * IOChannel is intended both as a replacement and wrapper for `std::iostream` and
 * `stdio.h/printf`. It allows for messages and errors to be output to multiple
 * sources simultaneously and asyncronously using signals (libsigc++). New
 * messages from any source are added to the back of the queue, and arbitrary
 * outputs can read them asynchronously from the front, either destructively or
 * non-destructively.
 *
 * Each output is also able to individually timing, as well as which messages it is
 * interested in and how it reads them, without interfering with the behavior
 * of other outputs.
 *
 * EXTERNAL OUTPUTS
 * An external output waits for a signal to be dispatched before it collects its
 * messages. Different signals are dispatched for different levels of verbosity
 * and categories.
 *
 * INTERNAL OUTPUTS
 * Optionally, iochannel can output to the terminal automatically via either
 * `std::iostream` or `stdio.h/printf`. This output can be controlled externally.
 * For example, a developer might choose to create pseudocommands in their
 * command-line that allow them to change verbosity on-the-fly while the program
 * is running.
 *
 * VERBOSITY
 * The concept of verbosity allows for developers to write and leave all manner
 * of useful output data, including debug information, detailed error messages,
 * and outright snark. Verbosity can be toggled globally for a channel,
 * or on a connection-by-connection basis.
 *
 * Verbosity ranges from 0 (only essential messages) to 3 (literally all messages).
 *
 * CATEGORY
 * Messages can be assigned a category, which makes it easier to different messages
 * to be sent to different outputs, or otherwise be handled differently. At the
 * moment, the categories are...
 * - Normal Messages
 * - Warnings
 * - Errors
 * - Debug Output
 *
 * CROSS-PLATFORM FORMATTING
 * IOChannel offers coloring and basic formatting on both UNIX and Windows systems
 * via the same interface.
 */

#ifndef PAWLIB_IOCHANNEL_HPP
#define PAWLIB_IOCHANNEL_HPP

//Needed for output sources.
#include <stdio.h>
#include <iostream>

//Needed for the `intptr_t` type
#include <cstdint>

//Needed for `ceil()`
#include <cmath>

//Bitset
#include <bitset>

//Needed for checking types.
#include <typeinfo>

//Needed for handling passed-in exceptions.
#include <exception>

//Signals and callbacks.
#include "cpgf/gcallbacklist.h"

/*We are only using std::string and std::queue temporarily.
These need to be swapped out for pawlib alternatives ASAP.*/
#include <string>
#include <queue>

//We use C's classes often.
#include <cstdio>

#include "core_types.hpp"
#include "stdutils.hpp"

namespace pawlib
{
    class pure_tril;
    class tril;

    namespace ioformat
    {
        enum IOFormatBase
        {
            base_bin = 2,
            base_2 = 2,
            base_ter = 3,
            base_3 = 3,
            base_quat = 4,
            base_4 = 4,
            base_quin = 5,
            base_5 = 5,
            base_sen = 6,
            base_6 = 6,
            base_sep = 7,
            base_7 = 7,
            base_oct = 8,
            base_8 = 8,
            base_9 = 9,
            base_dec = 10,
            base_10 = 10,
            base_und = 11,
            base_11 = 11,
            base_duo = 12,
            base_doz = 12,
            base_12 = 12,
            base_tri = 13,
            base_13 = 13,
            base_tetra = 14,
            base_14 = 14,
            base_pent = 15,
            base_15 = 15,
            base_hex = 16,
            base_16 = 16,
            base_17 = 17,
            base_18 = 18,
            base_19 = 19,
            base_vig = 20,
            base_20 = 20,
            base_21 = 21,
            base_22 = 22,
            base_23 = 23,
            base_24 = 24,
            base_25 = 25,
            base_26 = 26,
            base_27 = 27,
            base_28 = 28,
            base_29 = 29,
            base_30 = 30,
            base_31 = 31,
            base_32 = 32,
            base_33 = 33,
            base_34 = 34,
            base_35 = 35,
            base_36 = 36
        };

        enum IOFormatBool
        {
            bool_lower = 0,
            bool_upper = 1,
            bool_caps = 2,
            bool_numeral = 3,
            bool_scott = 4
        };

        //SIGNIFICANDS
        struct set_significands
        {
            explicit set_significands(unsigned int s):significands(s){}
            int significands = 14;
        };

        [[deprecated("Replaced by set_significands()")]]
        typedef set_significands set_precision;

        enum IOFormatSciNotation
        {
            ///Turn off all scientific notation.
            sci_none = 0,
            ///Automatically select the best option.
            sci_auto = 1,
            ///Turn on all scientific notation.
            sci_on = 2
        };

        enum IOFormatPointer
        {
            ///Print the value at the address.
            ptr_value = 0,
            ///Print the actual memory address.
            ptr_address = 1,
            ///Dump the hexadecimal representation of the memory at address.
            ptr_memory = 2
        };

        /**Indicate how many bytes to read from any pointer that isn't
         * recognized explicitly by iochannel, including void pointers.
         * This will not override the memory dump read size of built-in types.*/
        struct read_size
        {
            /**Indicate how many bytes to read from any pointer that isn't
             * recognized explicitly by iochannel, including void pointers.
             * This will not override the memory dump read size of built-in
             * types.
             * CAUTION: Misuse can cause SEGFAULT or other memory errors.
             \param the number of bytes to read*/
            explicit read_size(unsigned int i):readsize(i){}
            unsigned int readsize = 1;
        };

        enum IOFormatMemorySeparators
        {
            ///Output as one long string.
            mem_nosep = 0,
            ///Output with spaces between bytes.
            mem_bytesep = (1 << 0),
            ///Output with bars between words (8 bytes).
            mem_wordsep = (1 << 1),
            ///Output with spaces between bytes and bars between words.
            mem_allsep = 3
        };

        enum IOFormatNumeralCase
        {
            ///Print all letter digits as lowercase.
            num_lower = 0,
            ///Print all letter digits as uppercase.
            num_upper = 1
        };

        enum IOFormatCharValue
        {
            char_char = 0,
            char_int = 1
        };

        /**The standard ANSI text attributes.*/
        enum IOFormatTextAttributes
        {
            ///Turn of all attributes.
            ta_none = 0,
            ///Bold text.
            ta_bold = 1,
            ///Underlined text.
            ta_underline = 4,
            ///Inverted text colors, also known as "reverse video".
            ta_invert = 6
        };

        /**The standard ANSI text foreground colors.*/
        enum IOFormatTextFG
        {
            //None.
            fg_none = 0,
            ///Black text.
            fg_black = 30,
            ///Red text.
            fg_red = 31,
            ///Green text
            fg_green = 32,
            ///Yellow text.
            fg_yellow = 33,
            ///Blue text.
            fg_blue = 34,
            ///Magenta text.
            fg_magenta = 35,
            ///Cyan text.
            fg_cyan = 36,
            ///White text.
            fg_white = 37
        };

        /**The standard ANSI text background colors.*/
        enum IOFormatTextBG
        {
            //None.
            bg_none = 0,
            ///Black text background.
            bg_black = 40,
            ///Red text background.
            bg_red = 41,
            ///Green text background.
            bg_green = 42,
            ///Yellow text background.
            bg_yellow = 43,
            ///Blue text background.
            bg_blue = 44,
            ///Magenta text background.
            bg_magenta = 45,
            ///Cyan text background.
            bg_cyan = 46,
            ///White text background.
            bg_white = 47
        };

        /**The level of verbosity necessary for the message to display.*/
        enum IOFormatVerbosity
        {
            /**Only essential messages and errors. For normal end-use.
            Shipping default.*/
            vrb_quiet = 0,
            /**Common messages and errors. For common and normal end-user
            testing.*/
            vrb_normal = 1,
            /**Most messages and errors. For detailed testing and
            debugging.*/
            vrb_chatty = 2,
            /**Absolutely everything. For intense testing, detailed
            debugging, and driving the developers crazy.*/
            vrb_tmi = 3
        };

        /**The category of the message. Don't confuse this with Verbosity!
        Both a loop iterator output (V_TMI) and rare function start
        notification (V_NORMAL or V_CHATTY) belong under C_DEBUG, but they
        have different verbosity levels, as demonstrated.*/
        enum IOFormatCategory
        {
            /**The default value - anything that doesn't fit elsewhere.*/
            cat_normal = 1,
            /**Warnings, but not necessarily errors.*/
            cat_warning = 2,
            /**Error messages.*/
            cat_error = 4,
            /**Debug messages, such as variable outputs.*/
            cat_debug = 8,
            /**Testing messages that we may want shut off during benchmarking.*/
            cat_testing = 16,
            /**All message categories. Does not have a correlating signal.*/
            cat_all = 31
        };

        /**Special structures for iochannel, such as "END".*/
        enum IOControl
        {
            /**Newline, end of message (EoM), remove formatting.*/
            io_end = 0,
            /**Newline, EoM, retain formatting.*/
            io_end_keep = 1,
            /**EoM, remove formatting.*/
            io_send = 2,
            /**EoM, retain formatting.*/
            io_send_keep = 3,
            /**Newline, NOT EoM, retain formatting.*/
            io_endline_keep = 4,
            /**Newline, NOT EoM, remove formatting.*/
            io_endline = 5,
            /**Carriage return and flush, EoM, remove formatting.*/
            io_show = 6,
            /**Carriage return and flush, EoM, retain formatting.*/
            io_show_keep = 7,
            /**Flush only.*/
            io_flush = 8
        };

        enum IOEchoMode
        {
            /** Don't automatically output messages via the stdout echo. */
            echo_none = 0,
            /** Output messages to stdout via C-style `printf`. */
            echo_printf = 1,
            /** Output messages to stdout via C++-style `std::cout`. */
            echo_cout = 2
        };
    }

    //We need this here to shorten code in the following class/classes.
    using namespace ioformat;

    /**An iochannel allows console output to be custom routed to one or more
    * text-based output channels, including the terminal. It supports various
    * advanced functions, formatting and colors, and message priority.*/
    class iochannel
    {
        public:
            /**Declares a new iochannel instance.*/
            iochannel();

            /** CPGF multi-output signal (callback list) for categories. */
            typedef cpgf::GCallbackList<void (std::string,
                IOFormatCategory)> IOSignalCat;
            /** CPGF multi-output signal (callback list) for verbosities. */
            typedef cpgf::GCallbackList<void (std::string,
                IOFormatVerbosity)> IOSignalVrb;
            /** CPGF multi-output signal (callback list) for everything,
              * transmitting the message, the verbosity, and the catgeory. */
            typedef cpgf::GCallbackList<void (std::string,
                IOFormatVerbosity, IOFormatCategory)> IOSignalFull;
            /** CPGF multi-output signal (callback list) for everything,
              * transmitting only the message. */
            typedef cpgf::GCallbackList<void (std::string)> IOSignalAll;

            /* NOTE: In the examples below, the verbosity-related signals must
             * transmit what category the message is (since verbosity is
             * inherent and assumed). The inverse is true of category-related
             * signals. */

            /** Emitted when a message with verbosity 0 (quiet) is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatCategory){}'
              */
            IOSignalCat signal_v_quiet;

            /** Emitted when a message with verbosity <= 1 (normal) is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatCategory){}'
              */
            IOSignalCat signal_v_normal;

            /** Emitted when a message with verbosity <=2 (chatty) is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatCategory){}'
              */
            IOSignalCat signal_v_chatty;

            /** Emitted when a message with verbosity <=3 (tmi) is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatCategory){}'
              */
            IOSignalCat signal_v_tmi;

            /** Emitted when a message with category "normal" is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatVerbosity){}'
              */
            IOSignalVrb signal_c_normal;

            /** Emitted when a message with category "warning" is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatVerbosity){}'
              */
            IOSignalVrb signal_c_warning;

            /** Emitted when a message with category "error" is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatVerbosity){}'
              */
            IOSignalVrb signal_c_error;

            /** Emitted when a message with category "debug" is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatVerbosity){}'
              */
            IOSignalVrb signal_c_debug;

            /** Emitted when a message with category "testing" is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatVerbosity){}'
              */
            IOSignalVrb signal_c_testing;

            /** Emitted when any message is broadcast.
              * Callback must be of form 'void callback(string,
              * IOFormatVerbosity, IOFormatCategory){}'
              */
            IOSignalFull signal_full;

            /** Emitted when any message is broadcast, but only transmits the
              * message, and omits the verbosity and category.
              * Callback must be of form 'void callback(string){}'
              */
            IOSignalAll signal_all;

            // Overloaded stream insertion operators for IOChannel.

            //These need custom implementations.
            iochannel& operator<<(const bool&);
            iochannel& operator<<(const tril&);
            iochannel& operator<<(const char&);
            iochannel& operator<<(const std::string&);
            //TODO: Add support for OneString.

            inline iochannel& operator<<(const unsigned char& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const int& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const unsigned int& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const short int& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const unsigned short int& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const long int& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const unsigned long int& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const long long int& rhs){return resolve_integer(rhs);}
            inline iochannel& operator<<(const unsigned long long int& rhs){return resolve_integer(rhs);}

            inline iochannel& operator<<(const float& rhs){return resolve_float(rhs);}
            inline iochannel& operator<<(const double& rhs){return resolve_float(rhs);}
            inline iochannel& operator<<(const long double& rhs){return resolve_float(rhs);}

            template <typename T>
            inline iochannel& operator<<(const T* rhs){return resolve_pointer_smart(rhs);}

            inline iochannel& operator<<(const void* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const bool* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const char* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const unsigned char* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const unsigned int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const short int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const unsigned short int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const long int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const unsigned long int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const long long int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const unsigned long long int* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const float* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const double* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const long double* rhs){return resolve_pointer(rhs);}
            inline iochannel& operator<<(const std::string* rhs){return resolve_pointer(rhs);}

            iochannel& operator<<(const std::exception& rhs);

            //All of these need custom implementations.
            template<const long unsigned int T>
            iochannel& operator<<(const std::bitset<T>& rhs)
            {
                // Store the old values for the two flags we use.
                unsigned int old_readsize = readsize;
                IOFormatPointer old_ptr = ptr;

                /* The readsize (in bytes) is the bitset size (bits) divided
                 * by 8 and rounded to the nearest integer. */
                readsize = static_cast<unsigned int>(ceil((T/8)));
                // We want a memory dump.
                ptr = ptr_memory;

                // Remove the const-ness from the pointer.
                std::bitset<T>* rhs_ptr = const_cast<std::bitset<T>*>(&rhs);
                /* Convert to a void pointer for easier resolution.
                 * We must store the result as a pointer for returning shortly.
                 */
                iochannel* r = &resolve_pointer(static_cast<void*>(rhs_ptr));

                // Restore our prior flag values.
                ptr = old_ptr;
                readsize = old_readsize;

                /* Return the value at the pointer, which will be inplicitly
                 * converted to reference by the function return. */
                return *r;
            }

            iochannel& operator<<(const IOFormatBase&);
            iochannel& operator<<(const IOFormatBool&);
            iochannel& operator<<(const IOFormatCharValue&);
            iochannel& operator<<(const set_significands&);
            iochannel& operator<<(const IOFormatSciNotation&);
            iochannel& operator<<(const IOFormatNumeralCase&);
            iochannel& operator<<(const IOFormatPointer&);
            iochannel& operator<<(const IOFormatMemorySeparators&);
            iochannel& operator<<(const IOFormatTextBG&);
            iochannel& operator<<(const IOFormatTextFG&);
            iochannel& operator<<(const IOFormatTextAttributes&);
            iochannel& operator<<(const read_size&);
            iochannel& operator<<(const IOFormatVerbosity&);
            iochannel& operator<<(const IOFormatCategory&);
            iochannel& operator<<(const IOControl&);

            void configure_echo(IOEchoMode, IOFormatVerbosity = vrb_tmi, IOFormatCategory = cat_all);

            /** Suppress a category from broadcasting at all.
              * \param the category to suppress
              */
            void shutup(IOFormatCategory);

            /** Suppress verbosities higher than the one given.
              * This is also mainly used to reset verbosity back to "normal"
              * (the default).
              * \param the maximum verbosity to permit (default=vrb_normal)
              */
            void shutup(IOFormatVerbosity = vrb_normal);

            /** Permit a category to broadcast.
              * \param the category to broadcast
              */
            void speakup(IOFormatCategory);

            /** Permit a verbosity (and all below it) to broadcast.
              * Functionally identical to `shutup(IOFormatVerbosity)`.
              * \param the maximum verbosity to permit
              */
            void speakup(IOFormatVerbosity);

            /** Permit all messages (full verbosity and all categories)
              * to be broadcast.
              */
            void speakup();

            ~iochannel();
        protected:
            // TODO: Swap to OneString
            std::string msg;

            // The bitfield storing which categories are permitted.
            int16_t process_c = cat_all;
            // The maximum verbosity to permit.
            IOFormatVerbosity process_v = vrb_tmi;

            // Which method should be used for IOChannel's default stdout echo?
            IOEchoMode echomode = echo_printf;
            // The maximum verbosity to echo.
            IOFormatVerbosity echovrb = vrb_tmi;
            // The category to echo.
            IOFormatCategory echocat = cat_all;
            // TODO: Change echocat to a bitfield.

            /* MESSAGE ATTRIBUTES
             * These are set by enums and flags,
             * and should be reset after each message (unless
             * the user ends the message with an EoM stream
             * control with a "keep" flag.
             */

            /* The base or radix to display numbers in. */
            IOFormatBase base = base_10;
            /* The boolean value output style. This will also be used
             * later for trilean. */
            IOFormatBool boolstyle = bool_lower;
            /* What data type to interpret char values as. */
            IOFormatCharValue charval = char_char;
            /* The significants to display in floating point values. */
            int significands = 14;
            /* Whether to display in scientific notation or not. */
            IOFormatSciNotation sci = sci_auto;
            /* Whether to display digits > 9 [radix > 10] as uppercase
             * or lowercase. */
            IOFormatNumeralCase numcase = num_upper;
            /* What to print out when given a pointer.*/
            IOFormatPointer ptr = ptr_value;
            /* How many bytes of data to read from a pointer. */
            unsigned int readsize = 1;
            /* Bitfield for binary data display formats. */
            unsigned char memformat = 0;

            /* Text attributes. */
            IOFormatTextAttributes ta = ta_none;
            // TODO: Change `ta` to a bitfield, to allow multiple format flags.
            /* Text background color. */
            IOFormatTextBG bg = bg_none;
            /* Text foreground color. */
            IOFormatTextFG fg = fg_none;

            /* Message verbosity. */
            IOFormatVerbosity vrb = vrb_normal;
            /* Message category. */
            IOFormatCategory cat = cat_normal;
            /* Message parsable */
            tril parse = maybe;

            template <typename T>
            iochannel& resolve_pointer_smart(const T* rhs)
            {
                //If we cannot parse because of `shutup()` settings, abort.
                if(!can_parse()){return *this;}

                switch(ptr)
                {
                    //If we are to print as value...
                    case ptr_value:
                    {
                        *this << "[iochannel cannot interpret value at pointer of this type.]";
                        break;
                    }
                    //If we are to print as address...
                    case ptr_address:
                    {
                        //Inject raw address, overriding with byte read size 1.
                        inject(rhs, 1, false);
                        break;
                    }
                    //If we are to print the raw memory...
                    case ptr_memory:
                    {
                        //Inject raw address with the object size as read_size.
                        inject(rhs, sizeof(T), true);
                        break;
                    }
                }
                return *this;
            }

            /** Resolves any common pointer. This can handle
              * all atomic and numeric C and C++ types.
              * \param the pointer to resolve
              */
            template <typename T>
            iochannel& resolve_pointer(const T*);

            /** Resolves a void pointer, which allows
              * for raw data dumps from any pointer
              * imaginable.
              * \param the pointer to resolve
              */
            iochannel& resolve_pointer(const void*);

            /** Resolves a char pointer.
              * \param the pointer to resolve
              */
            iochannel& resolve_pointer(const char*);

            /** Resolves any integer.
              * \param the integer variable to resolve
              */
            template <typename T>
            iochannel& resolve_integer(const T&);

            /** Resolves any floating point number variable.
              * \param the floating point variable to resolve
              */
            template <typename T>
            iochannel& resolve_float(const T&);

            //The string containing the format.
            std::string format = "";
            //TODO: Swap to OneString

            /**Flush the standard output.*/
            void flush();

            /**Insert a single character without need for null terminator.
            * \param the character to insert
            */
            void inject(char);

            /**Insert a C string into the output stream. Automatically applies
            * unapplied attributes before inserting text.
            * \param the C-string to insert.
            * \param whether the call was recursive. (Internal use only!)
            */
            void inject(const char*, bool=false);

            /**Insert a memory address or its raw contents into the output
             * stream.
             * \param the address to insert
             * \param the size of the object referenced
             * \param whether to print literal address (false) or memory
             * dump (true); default false*/
            void inject(const void*, unsigned int len, bool=false);

            /**Transmit the current pending output stream and reset in
            * preparation for the next message.
            * \param whether to retain the flags
            */
            void transmit(bool=false);

            ///Dirty flag raised when attributes are changed and not yet applied.
            bool dirty_attributes = false;

            /**Apply formatting attributes (usually ANSI) that are pending.
            * \param true if new attributes were applied
            */
            bool apply_attributes();

            /**Returns whether the vrb and cat match parsing (shutup) rules.*/
            bool can_parse();

            /**Clear the channel's message substring array.*/
            void clear_msg();

            /**Reset all attributes.*/
            void reset_attributes();

            /**Reset all flags.*/
            void reset_flags();

    };

    ///Global external (static) instance of iochannel.
    extern iochannel ioc;
}


#endif // PAWLIB_BROADCAST_H
