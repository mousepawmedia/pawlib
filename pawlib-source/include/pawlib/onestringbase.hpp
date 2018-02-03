/** OneString (Base) [PawLIB]
  * Version: 1.0
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
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */


#ifndef PAWLIB_ONESTRINGBASE_HPP
#define PAWLIB_ONESTRINGBASE_HPP

#include <cstring>
#include <iomanip>
#include <iostream>

#include "pawlib/iochannel.hpp"
#include "pawlib/onechar.hpp"


// Type constants
const bool QUICK_TYPE = 0;
const bool ONE_TYPE = 1;

namespace pawlib
{

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
    class OneStringBase
    {
        public:

            /**Default constructor
             * \return an empty OneString with size 0 */
            explicit OneStringBase();

            /**Create an empty OneStringBase
             * \param the int that represents the template size in derived class
             * \param the bool that represents what type of string is being created
             * \return an empty OneStringBase. */
            OneStringBase(int tempSize, bool type);

            /**Create a OneStringBase from a single char
             * \param the char to be converted to OneString
             * \param the int that represents the template size in derived class
             * \param the bool that represents what type of string is being created
             * \return a OneStringBase representation of ch. */
            OneStringBase(char ch, int tempSize, bool type);

            /**Create a OneStringBase from a OneChar
             * \param the OneChar to be converted to OneString
             * \param the int that represents the template size in derived class
             * \param the bool that represents what type of string is being created
             * \return a OneStringBase representation of ch */
            OneStringBase(const OneChar& ch, int tempSize, bool type);

            /**Copy Constructor for OneStringBase
             * \param the OneStringBase to be copied
             * \param the int that represents the template size in derived class
             * \param the bool that represents what type of string is being created
             * \return a new OneStringBase that is a deep copy of ostr */
            OneStringBase(const OneStringBase& ostr, int tempSize, bool type);


            // String functions

            /** Get the String type
             * \return a boolean that represents either a OneString or QuickString */
            bool getType() const;

            /**Determine number of OneChars in a OneString
             * \return an int that represents the number of OneChars in the OneString */
            int size() const;

            /**Returns the OneChar found at a specific index
             * \param an int to represent the desired index
             * \return the OneChar found at pos */
            OneChar& at(int pos);

            /**Tests for equality with another OneString
             * \param a OneStringBase to be tested for equality
             * \return true if the master array is equivalent to the OneStringBase. */
            bool equals(const OneStringBase& ostr) const;

            /**Tests for equality with a const char*
             * \param a const char* to be tested for equality
             * \return true if the master array is equivalent to the const char*. */
            virtual bool equals(const char* ostr)const = 0;

            /**Tests for equality with a std::string
             * \param a std::string to be tested for equality
             * \return true if the master array is equivalent to the std::string. */
            bool equals(std::string ostr) const;

            /**Adds a OneStringBase onto the end of the master array
             * \param the OneStringBase to be added to the end of the master array */
            void append(const OneStringBase& ostr);

            /**Adds a const char* onto the end of the master array
             * \param the const char* to be added to the end of the master array */
            virtual void append(const char* ostr) = 0;

            /**Adds a std::string to the end of the master array
             * \param the std::string to be added to the end of the master array */
            void append(std::string ostr);

            /**Adds a char onto the end of the master array
             * \param the char to be added to the end of the master array */
            void append(char ochar);

            /**Adds a OneChar onto the end of the master array
             * \param the OneChar to be added to the end of the master array */
            void append(const OneChar& ochar);

            /**Inserts a OneStringBase into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneStringBase to be inserted */
            void insert(int pos, const OneStringBase& ostr);

            /**Inserts a char* into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the const char* to be inserted */
            virtual void insert(int pos, const char* ostr) = 0;

            /**Inserts a std::string into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the std::string to be inserted */
            void insert(int pos, std::string ostr);

            /**Inserts a char into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the char to be inserted */
            void insert(int pos, char ochar);

            /**Inserts a OneChar into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneChar to be inserted */
            void insert(int pos, OneChar* ochar);

            /**Creates a substring from the master array
             * \param an int that corresponds to the start of the substring
             * \param an int for the size of the substring. Defaults to -1 to
             * indicate that the substring goes to the end of the master array
             * \return a OneStringBase that is a substring of the master array*/
            virtual OneStringBase& substr(int pos, int sublen = -1) = 0;

            /**Appends a single char to the end of a OneString
             * Same as append(char)
             * \param the char to be appended */
            void push_back(char ch);

            /**Appends a OneChar (either AscChar or UniChar) to the string
             * Same as append(OneChar)
             * \param the OneChar to be appended */
            void push_back(const OneChar& ochar);

            /**Erases the last OneChar of the OneString and reduces len */
            void pop_back();

            /**Exchanges the master array for the contents of str while
             * the contents of str become that of the master array
             * \param the reference to the OneStringBase to be swapped with */
            void swap(OneStringBase& str);

            /**Returns total number of bytes used
             * \return an int that indicates how many bytes the OneStringBase is */
            int length();

            /**Returns the largest a specific OneStringBase can be
             * \return an int that indicates the max_size for a specific class */
            int max_size();

            /**Determines if a OneStringBase is empty or not
             * \return true if len == 0, false otherwise */
            bool empty() const;

            /**Erases contents of the OneStringBase. Len becomes 0 */
            void clear();


            /**Retrieve OneChar from OneStringBase
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the OneStringBase
             * \return returns the OneChar located at pos */
            OneChar* operator [](int pos) const;

             /**Retrieve OneChar from OneStringBase
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the OneStringBase
             * \return returns the OneChar located at pos */
            OneChar& operator [](int pos);

            /**Copy Constructor for assignment operator OneStringBase
             * \param the OneStringBase to be copied
             * \return a new OneStringBase that is a deep copy of ostr */
            OneStringBase& operator=(const OneStringBase& newostr);


            /**Create a OneStringBase from std::string with assignment operator
             * \param the std::string to be converted to OneStringBase
             * \return a OneStringBase representation of str.
             *         All Unicode will be parsed appropriately. */
            OneStringBase& operator=(std::string str);

            /**Create a OneStringBase from const char* with assignment operator
             * Note: Double quotes default to const char*
             * \param the const char* to be converted to OneStringBase
             * \return a OneStringBase representation of str.
             *         All Unicode will be parsed appropriately. */
            OneStringBase& operator=(const char* str);

            /**Helper function for operator= that must be declared in derived
             * classes.
             * \param the const char* to be returned as a OneStringBase
             * \return either an initialized OneString or QuickString. */
            virtual OneStringBase& assignHelper(const char* str) = 0;

            /**Create a OneStringBase from a single char with assignment operator
             * \param the char to be converted to OneStringBase
             * \return a OneStringBase representation of ch. */
            OneStringBase& operator=(char ch);

            /**Helper function for operator= defined in derived classes.
             * \param the char to be converted to OneStringBase
             * \return a OneStringBase representation of an Ascii character */
            virtual OneStringBase& assignChar(char ch) = 0;

            /**Create a OneStringBase from a OneChar with assignment operator
             * \param the OneChar to be converted to OneString
             * \return a OneStringBase representation of ch. */
            OneStringBase& operator=(OneChar* ch);

            // Comparison operators

            /**Tests for equality with another OneStringBase of varying sizes
             * \param a OneStringBase (of different sizes) to be tested for equality
             * \return true if both OneStringBases are exactly equivalent. */
            bool operator==(const OneStringBase& ostr2);

            /**Tests for equality with a const char*
             * \param a const char* to be tested for equality
             * \return true if the OneStringBase is equivalent to the char* */
            bool operator==(const char* ostr2);

            /**Tests for equality with a std::string
             * \param a std::string to be tested for equality
             * \return true if the OneStringBase is equivalent to the std::string */
            bool operator==(std::string ostr2);

            /**The less-than operator
             * \param the right-hand OneStringBase operand
             * \return true if the OneStringBase is less than the right-hand */
            bool operator<(const OneStringBase& ostr2);

            /** Helper function for operator<
             * \param the OneStringBase to be compared to
             * \return true if the current string is less than the argument */
            virtual bool lessThanStr(const OneStringBase& ostr) = 0;

            /**The less-than operator
             * \param the right-hand const char* operand
             * \return true if the current string is less than the right-hand */
            bool operator<(const char* ostr2);

            /** Helper function for operator< (char*)
             * \param the const char* to be compared to
             * \return true if ostr is greater than the current string. */
            virtual bool lessThanCharP(const char* ostr) = 0;

            /**The less-than operator
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is less than the right-hand */
            bool operator<(std::string ostr2);

            /**The less-than-or-equal operator
             * \param the right-hand OneStringBase operand
             * \return true if the current string is less than or equal
             *         to the right-hand */
            bool operator<=(const OneStringBase& ostr2);

             /**The less-than-or-equal operator
             * \param the right-hand const char* operand
             * \return true if the current string is less than or equal
             *         the right-hand */
            bool operator<=(const char* ostr2);

             /**The less-than-or-equal operator
             * \param the right-hand std::string operand
             * \return true if the current string is less than or equal
             *         the right-hand */
            bool operator<=(std::string ostr2);

             /**The greater-than operator
             * \param the right-hand OneStringBase operand
             * \return true if the current string is greater than the right-hand */
            bool operator>(const OneStringBase& ostr2);

            /**The greater-than operator
             * \param the right-hand const char* operand
             * \return true if the current string is greater than the right-hand */
            bool operator>(const char* ostr2);

            /**The greater-than operator
             * \param the right-hand std::string operand
             * \return true if the current string is greater than the right-hand */
            bool operator>(std::string ostr2);

            /**The greater-than-or-equal operator
             * \param the right-hand OneStringBase operand
             * \return true if the current string is greater than or equal
             *         to the right-hand */
            bool operator>=(const OneStringBase& ostr2);

            /**The greater-than-or-equal operator
             * \param the right-hand const char* operand
             * \return true if the current string is greater than or equal
             *         to the right-hand */
            bool operator>=(const char* ostr2);

            /**The greater-than-or-equal operator
             * \param the right-hand std::string operand
             * \return true if the current string is greater than or equal
             *         to the right-hand */
            bool operator>=(std::string ostr2);

            /**Appends a OneStringBase onto the end of the current string
             * \param the OneStringBase to be appended*/
            void operator+=(const OneStringBase& ostr2);

            /**Appends a const char* onto the end of the current string
             * \param the const char* to be appended*/
            void operator+=(const char* ostr2);

            /**Appends a std::string onto the end of the current string
             * \param the std::string to be appended*/
            void operator+=(std::string ostr2);

            /**Appends a char onto the end of the current string
             * \param the char to be appended*/
            void operator+=(char ochar);

            /**Appends a OneChar onto the end of the current string
             * \param the OneChar to be appended*/
            void operator+=(const OneChar& ochar);

            /**Operator to output a OneStringBase
             * \param the ostream to output on
             * \param the OneStringBase to output
             * \return outputs the OneStringBase as a cohesive string */
            friend std::ostream& operator<<(std::ostream& os, const OneStringBase& ostr)
            {
                // Loop through and output each OneChar. Since OneChar has its
                // own operator<< overload everything shall be displayed neatly
                for(int i = 0; i < ostr.size(); i++)
                    os << ostr.master[i];
                return os;
            };

            /**Inputs a OneStringBase from the user so long as there are no spaces
             * \param the istream to receive input from
             * \param the OneStringBase to be input
             * \return an istream containing the inputted OneStringBase */
            friend std::istream& operator>>(std::istream& in, OneStringBase& ostr)
            {

                std::string temp;
                std::getline(in, temp);
                ostr = temp;
                return in;
            };

            // The master array
            OneChar*  master;

        private:
            int len;                // the length of string

            int MAX_SIZE;           // the largest a string can be

            bool strType;           // the type (ONE_STRING, or QUICK_STRING)
        protected:

            /**Increment the len variable. Used in derived classes */
            void incLen();

            /**Set the len variable. Used in derived classes
             * \param the int to set len to */
            void setLen(int newLen);

    };

    //#include "../src/OneString.cpp"

}
#endif // PAWLIB_ONESTRINGBASE_HPP
