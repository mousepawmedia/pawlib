/** OneString [PawLIB]
  * Version: 0.3
  *
  * OneString is a multi-sized, Unicode-compatible replacement
  * for std::string. OneString contains all the
  * basic functions found in std::string all while
  * avoiding dynamic allocation whenever possible.
  * To handle Unicode, each OneString is made of OneChars,
  * which are enhanced characters.
  *
  * Author(s): Scott Taylor
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
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef ONESTRING_HPP
#define ONESTRING_HPP

#include <cstring>
#include <iomanip>
#include <iostream>

#include "pawlib/iochannel.hpp"
#include "pawlib/onechar.hpp"
#include "pawlib/quickstring.hpp"
#include "pawlib/onestringbase.hpp"

namespace pawlib
{
    // Forward declare QuickString
    template <const int oneSize>
    class QuickString;

    /* The purpose of OneString is to provide the functionality of std::string
     * but without dynamic allocation and with increased support for Unicode
     * Characters. As a templated class, the possible types of OneString are:
     * OneString<8>, OneString<16>, OneString<32>, OneString<64>, OneString<128>,
     * and any other future forward declarations. The difference between each of these
     * OneString types is the MAX_SIZE of each. OneString<8> can hold a maximum of 8 OneChars
     * while OneString<32> can hold up to 32 OneChars. Each OneString
     * class contains a master array that is an array of OneChars. The size of
     * the master array is determined by the MAX_SIZE for the class.
     * When expanding the possible OneString sizes, one must add the forward declaration
     * to the end of OneString.cpp and the corresponding declarations/implementation for
     * the copy constructor, equals(), append(), insert(), swap(), and operator=().*/
    template <const int oneSize>
    class OneString: public OneStringBase
	{
		public:
			explicit OneString();

			 /**Create a OneString from const char*
             * Note: Double quotes default to const char*
             * \param the const char* to be converted to OneString
             * \return a OneString representation of str.
             *         All Unicode will be parsed appropriately. */
            // cppcheck-suppress noExplicitConstructor
            OneString(const char* str);

			/**Create a OneString from std::string
             * \param the string to be converted to OneString
             * \return a OneString representation of str.
             *         All Unicode will be parsed appropriately. */
            // cppcheck-suppress noExplicitConstructor
            OneString(std::string str);

            /**Create a OneString from a single char
             * \param the char to be converted to OneString
             * \return a OneString representation of ch. */
            // cppcheck-suppress noExplicitConstructor
            OneString(char ch);

            /**Create a OneString from a OneChar
             * \param the OneChar to be converted to OneString
             * \return a OneString representation of ch */
            // cppcheck-suppress noExplicitConstructor
            OneString(OneChar& ch);

            /* Constructors do not handle the abstract base well. Therefore,
             it is necessary to create a constructor for each OneString and
             QuickString size. Luckily this can be accomplished in only 3 functions */

            /**Copy constructor for OneString<oneSize>
             * NOTE: This constructor is for a OneString that has the same
             *      template size as the current OneString.
             * \param the OneString<oneSize> to be copied
             * \return a new OneString that is a deep copy of the other */
            OneString(const OneString& ostr):OneStringBase(ostr, oneSize, ONE_TYPE){};

            /**Copy Constructor for all other OneString sizes
             * \param the OneString<N> to be copied (N != oneSize)
             * \return a new OneString that is a deep copy of ostr */
            template <const int N>
            OneString(const OneString<N>& ostr):OneStringBase(ostr, oneSize, ONE_TYPE){};

            /**Copy Constructor for all QuickString sizes
             * \param the QuickString<N> to be copied (N is any of the specified sizes)
             * \return a new OneString that is a deep copy of ostr */
            template <const int N>
            // cppcheck-suppress noExplicitConstructor
            OneString(const QuickString<N>& ostr):OneStringBase(ostr, oneSize, ONE_TYPE){};

            /**Tests for equality with a const char*
             * \param a const char* to be tested for equality
             * \return true if the master array is equivalent to the const char*. */
            bool equals(const char* ostr) const;

             // Include all declarations in base class
            using OneStringBase::equals;

            /**Adds a const char* onto the end of the master array
             * \param the const char* to be added to the end of the master array */
            void append(const char* ostr);

            // Include all declarations in base class
            using OneStringBase::append;

             /**Parses char* into OneString based on size
             * Used primarily for Unicode Characters within OneString(const char*)
             * \param the const char* to be parsed
             * \param an int to represent the index to parse the char* at
             * \param an int to represent the number of bytes in the char* */
            void parseChar(const char* str, int index, int bytes);

             /**Inserts a char* into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the const char* to be inserted */
            void insert(int pos, const char* ostr);

             // Include all declarations in base class
            using OneStringBase::insert;

            /**Creates a substring from the master array
             * \param an int that corresponds to the start of the substring
             * \param an int for the size of the substring. Defaults to -1 to
             * indicate that the substring goes to the end of the master array
             * \return a OneString that is a substring of the master array*/
            OneStringBase& substr(int pos, int sublen = -1);

            /**Exchanges the master array for the contents of str while
              * Note: must be the same MAX_SIZE
              * the contents of str become that of the master array
              * \param the reference to the OneString to be swapped with */
             void swap(OneString& str);

            /**Helper function for operator= that must be declared in derived
             * classes.
             * \param the const char* to be returned as a OneStringBase
             * \return either an initialized OneString or QuickString. */
            OneStringBase& assignHelper(const char* str);

             /**Helper function for operator= defined in derived classes.
             * \param the char to be converted to OneStringBase
             * \return a OneStringBase representation of an Ascii character */
            OneStringBase& assignChar(char ch);

             /** Helper function for operator<
             * \param the OneStringBase to be compared to
             * \return true if the current string is less than the argument */
            bool lessThanStr(const OneStringBase& ostr);

            /** Helper function for operator< (char*)
             * \param the const char* to be compared to
             * \return true if ostr is less than the current string. */
            bool lessThanCharP(const char* ostr);

            /*******************************************************************
            * CURRENT WORKING SOLUTION TO OPERATOR+ ISSUE
            ********************************************************************/

            // Define Macro to associate code to each operator+ function
            #define ADDOP_FUNCT \
            { \
                /* We don't want to alter the left-hand side, so we create a copy*/\
                OneString cpyStr = lhs;\
                /* Append the right-hand side */\
                cpyStr.append(rhs);\
                return cpyStr;\
            }

            /**Appends the right hand operator onto the left hand operator
             * What makes this different from += is that + may be used
             * multiple times per line of code
             * The rhs param can be either a OneString, char, const char*,
             * OneChar, or std::string.
             * \param the left-hand OneString to be added to
             * \param the right-hand argument to be appended
             * \return the OneString result of joining the lhs and rhs*/
            template <class R>
            friend OneString operator+(const OneString& lhs, R rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a OneString to a char*
             * \param the left-hand char* to be added to
             * \param the right-hand OneString to be appended
             * \return the OneString result of joining the lhs and rhs*/
            friend OneString operator+(const char* lhs,  OneString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a OneString to a char
             * \param the left-hand char to be added to
             * \param the right-hand OneString to be appended
             * \return the OneString result of joining the lhs and rhs*/
            friend OneString operator+(char lhs,  OneString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a OneString to a std::string
             * \param the left-hand std::string to be added to
             * \param the right-hand OneString to be appended
             * \return the OneString result of joining the lhs and rhs*/
            friend OneString operator+(std::string lhs,  OneString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a OneString to a OneChar
             * \param the left-hand OneChar to be added to
             * \param the right-hand OneString to be appended
             * \return the OneString result of joining the lhs and rhs*/
            friend OneString operator+(OneChar* lhs, OneString rhs)
            {
                ADDOP_FUNCT;
            };

	};

}
#endif // ONESTRING_HPP
