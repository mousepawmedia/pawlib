/** QuickString [PawLIB]
  * Version: 1.0
  *
  * QuickString is a multi-sized replacement
  * for std::string. QuickString contains all the
  * basic functions found in std::string all while
  * avoiding dynamic allocation whenever possible.
  * Each QuickString is made of AscChars,
  * which are simple ASCII characters.
  *
  * Last Updated: 10 Aug 2016
  * Author: Scott Taylor
  */

/* LICENSE
 * Copyright (C) 2016 MousePaw Games.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef QUICKSTRING_HPP
#define QUICKSTRING_HPP

#include <iostream>
#include <iochannel.hpp>
#include <onechar.hpp>
#include <onestringbase.hpp>
#include <onestring.hpp>

namespace pawlib
{
    // Forward declare OneString
    template <const int oneSize>
    class OneString;

    /* The purpose of QuickString is to provide the functionality of std::string
     * but with limited dynamic allocation and with a greater efficiency than
     * std::string. As a templated class, the possible types of QuickString are:
     * QuickString<8>, QuickString<16>, QuickString<32>, QuickString<64>, QuickString<128>,
     * and any other future forward declarations. The difference between each of these
     * QuickString types is the MAX_SIZE of each. QuickString<8> can hold a maximum of 8 OneChars
     * while QuickString<32> can hold up to 32 OneChars. Each QuickString
     * class contains a master array that is an array of OneChars. The size of
     * the master array is determined by the MAX_SIZE for the class.
     * When expanding the possible OneString sizes, one must add the forward declaration
     * to the end of QuickString.cpp and the corresponding declarations/implementation for
     * the copy constructor, equals(), append(), insert(), swap(), and operator=().*/
    template <const int quickSize>
    class QuickString: public OneStringBase
	{
		public:
			explicit QuickString();

			 /**Create a QuickString from const char*
             * Note: Double quotes default to const char*
             * \param the const char* to be converted to QuickString
             * \return a QuickString representation of str.*/
            // cppcheck-suppress noExplicitConstructor
            QuickString(const char* str);

			/**Create a QuickString from std::string
             * \param the string to be converted to QuickString
             * \return a QuickString representation of str.*/
            // cppcheck-suppress noExplicitConstructor
            QuickString(std::string str);

            /**Create a QuickString from a single char
             * \param the char to be converted to QuickString
             * \return a QuickString representation of ch. */
            // cppcheck-suppress noExplicitConstructor
            QuickString(char ch);

            /**Create a QuickString from a OneChar
             * \param the OneChar to be converted to QuickString
             * \return a QuickString representation of ch */
            // cppcheck-suppress noExplicitConstructor
            QuickString(OneChar& ch);

            /* Constructors do not handle the abstract base well. Therefore,
             it is necessary to create a constructor for each OneString and
             QuickString size. Luckily this can be accomplished in only 3 functions */

            /**Copy constructor for QuickString<quickSize>
             * NOTE: This constructor is for a QuickString that has the same
             *      template size as the current QuickString.
             * \param the QuickString<oneSize> to be copied
             * \return a new QuickString that is a deep copy of the other */
            QuickString(const QuickString& ostr):OneStringBase(ostr, quickSize, QUICK_TYPE){};

            /**Copy Constructor for all other QuickString sizes
             * \param the QuickString<N> to be copied (N != quickSize)
             * \return a new QuickString that is a deep copy of ostr */
            template <const int N>
            QuickString(const QuickString<N>& ostr):OneStringBase(ostr, quickSize, QUICK_TYPE){};

            /**Copy Constructor for all OneString sizes
             * \param the OneString<N> to be copied (N is any of the specified sizes)
             * \return a new QuickString that is a deep copy of ostr */
            template <const int N>
            // cppcheck-suppress noExplicitConstructor
            QuickString(const OneString<N>& ostr):OneStringBase(ostr, quickSize, QUICK_TYPE){};

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
             * \return a QuickString that is a substring of the master array*/
            OneStringBase& substr(int pos, int sublen = -1);


            /**Exchanges the master array for the contents of str while
              * Note: must be the same MAX_SIZE
              * the contents of str become that of the master array
              * \param the reference to the QuickString to be swapped with */
            void swap(QuickString& str);

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
            #define QADDOP_FUNCT \
            { \
                /* We don't want to alter the left-hand side, so we create a copy*/\
                QuickString cpyStr = lhs;\
                /* Append the right-hand side */\
                cpyStr.append(rhs);\
                return cpyStr;\
            }

            /**Appends the right hand operator onto the left hand operator
             * What makes this different from += is that + may be used
             * multiple times per line of code
             * The rhs param can be either a QuickString, char, const char*,
             * OneChar, or std::string.
             * \param the left-hand QuickString to be added to
             * \param the right-hand argument to be appended
             * \return the QuickString result of joining the lhs and rhs*/
            template <class R>
            friend QuickString operator+(const QuickString& lhs, R rhs)
            {
                QADDOP_FUNCT;
            };

            /**Appends a QuickString to a char*
             * \param the left-hand char* to be added to
             * \param the right-hand QuickString to be appended
             * \return the QuickString result of joining the lhs and rhs*/
            friend QuickString operator+(const char* lhs,  QuickString rhs)
            {
                QADDOP_FUNCT;
            };

            /**Appends a QuickString to a char
             * \param the left-hand char to be added to
             * \param the right-hand QuickString to be appended
             * \return the QuickString result of joining the lhs and rhs*/
            friend QuickString operator+(char lhs,  QuickString rhs)
            {
                QADDOP_FUNCT;
            };

            /**Appends a QuickString to a std::string
             * \param the left-hand std::string to be added to
             * \param the right-hand OneString to be appended
             * \return the QuickString result of joining the lhs and rhs*/
            friend QuickString operator+(std::string lhs,  QuickString rhs)
            {
                QADDOP_FUNCT;
            };

            /**Appends a QuickString to a OneChar
             * \param the left-hand OneChar to be added to
             * \param the right-hand QuickString to be appended
             * \return the QuickString result of joining the lhs and rhs*/
            friend QuickString operator+(OneChar* lhs, QuickString rhs)
            {
                QADDOP_FUNCT;
            };

	};

}
#endif // QUICKSTRING_HPP
