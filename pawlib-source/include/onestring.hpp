/** OneString [PawLIB]
  * Version: 1.0
  *
  * OneString is a multi-sized, Unicode-compatible replacement
  * for std::string. OneString contains all the
  * basic functions found in std::string all while
  * avoiding dynamic allocation whenever possible.
  * To handle Unicode, each OneString is made of OneChars,
  * which are enhanced characters.
  *
  * Last Updated: 10 April 2016
  * Author: Scott Taylor
  */

/* LICENSE
 * Copyright (C) 2016 MousePaw Games. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */


#ifndef ONESTRING_HPP
#define ONESTRING_HPP
#include <iostream>
#include <iochannel.hpp>

//const int MAX_SIZE = 8;
namespace pawlib
{
    /* OneChar is a special array of of chars
    It's purpose is to allow for Unicode characters in OneString */
    class OneChar
    {
        public:
            /**Default constructor
             * \return Returns a new OneChar with only one character: '\0' */
            OneChar();

            /**Retrieve char from OneChar
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the OneChar
             * \return returns the char located at pos */
            char operator[](int pos) const;

            /**Retrieve char from OneChar
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the OneChar
             * \return returns the char reference located at pos */
            char& operator[](int pos);

            // Overload all necessary operators

            /**Construct new OneChar
             * \param the char to initialize OneChar with
             * \return a new OneChar containing a char and '\0' */
            OneChar operator=(char newChar);

             /**Construct new OneChar from Unicode character
             * \param the 2-4 byte Unicode character to put in OneChar
             * \return a new OneChar containing a Unicode character and '\0' */
            OneChar operator=(char* newChar);

            /**Copy from another OneChar
             * \param the OneChar to copy from
             * \return a new OneChar copied from newChar */
            OneChar operator=(OneChar newChar);

            /**Operator to output a OneChar
             * \param the ostream to output on
             * \param the OneChar to output
             * \return outputs the OneChar as a single character */
            friend std::ostream& operator<<(std::ostream& os, const OneChar& ochr);

            /**Compares OneChar to another OneChar
             * \param the primary OneChar
             * \param the OneChar being compared to
             * \return true if the OneChars are exactly equal. false otherwise */
            friend bool operator==(const OneChar& ochr, const OneChar &newChar);

            /**Compares OneChar to a char*
             * Used for Unicode comparisons
             * \param the primary OneChar
             * \param the char* to be compared to (needs to be parsed)
             * \return true if the two are exactly equal. false otherwise */
            friend bool operator==(const OneChar& ochr, char* newChar);

            /**Compares OneChar to a single char
             * \param the primary OneChar
             * \param the char to be compared to
             * \return true if the two are exactly equal. false otherwise */
            friend bool operator==(const OneChar& ochr, char newChar);

            /**Determines if a OneChar is less than another
             * \param the primary OneChar
             * \param the OneChar being compared to
             * \return true if ochr's value is less than newChar */
            friend bool operator<(const OneChar& ochr, const OneChar &newChar);
        private:
            char miniChar[5];
    };

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
    class OneString
    {
        public:

            /**Default constructor
             * \return an empty OneString with size 0 */
            explicit OneString();

            /**Create a OneString from std::string
             * \param the string to be converted to OneString
             * \return a OneString representation of str.
             *         All Unicode will be parsed appropriately. */
            // cppcheck-suppress noExplicitConstructor
            OneString(std::string str);

            /**Create a OneString from const char*
             * Note: Double quotes default to const char*
             * \param the const char* to be converted to OneString
             * \return a OneString representation of str.
             *         All Unicode will be parsed appropriately. */
            // cppcheck-suppress noExplicitConstructor
            OneString(const char* str);

            /**Create a OneString from a single char
             * \param the char to be converted to OneString
             * \return a OneString representation of ch. */
            // cppcheck-suppress noExplicitConstructor
            OneString(char ch);

            /**Create a OneString from a OneChar
             * \param the OneChar to be converted to OneString
             * \return a OneString representation of ch */
            // cppcheck-suppress noExplicitConstructor
            OneString(OneChar ch);

            /* Inorder to interact with other OneString types, a function must
             * be made for every possible OneString. Trying to use templates to
             * alleviate this problem only resulted in bugs. This method, while
             * being larger code-wise, is much safer. */

            /**Copy Constructor for OneString<8>
             * \param the the OneString<8> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<8>& ostr);

            /**Copy Constructor for OneString<16>
             * \param the the OneString<16> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<16>& ostr);

            /**Copy Constructor for OneString<32>
             * \param the the OneString<32> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<32>& ostr);

            /**Copy Constructor for OneString<64>
             * \param the the OneString<64> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<64>& ostr);

            /**Copy Constructor for OneString<128>
             * \param the the OneString<128> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<128>& ostr);

            /**Copy Constructor for OneString<256>
             * \param the the OneString<256> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<256>& ostr);

            /**Copy Constructor for OneString<512>
             * \param the the OneString<512> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<512>& ostr);

            /**Copy Constructor for OneString<1024>
             * \param the the OneString<1024> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<1024>& ostr);

            /**Copy Constructor for OneString<2048>
             * \param the the OneString<2048> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<2048>& ostr);

            /**Copy Constructor for OneString<4096>
             * \param the the OneString<4096> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString(const OneString<4096>& ostr);

            // String functions

            /**Determine number of OneChars in a OneString
             * \return an int that represents the number of OneChars in the OneString */
            int size() const;

            /**Returns the OneChar found at a specific index
             * \param an int to represent the desired index
             * \return the OneChar found at pos */
            OneChar at(int pos);

            /**Tests for equality with another OneString
             * \param a OneString<8> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<8>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<16> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<16>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<32> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<32>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<64> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<64>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<128> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<128>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<256> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<256>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<512> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<512>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<1024> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<1024>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<2048> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<2048>& ostr) const;

            /**Tests for equality with another OneString
             * \param a OneString<4096> to be tested for equality
             * \return true if the master array is equivalent to the OneString. */
            bool equals(const OneString<4096>& ostr) const;

            /**Tests for equality with a const char*
             * \param a const char* to be tested for equality
             * \return true if the master array is equivalent to the const char*. */
            bool equals(const char* ostr)const;

            /**Tests for equality with a std::string
             * \param a std::string to be tested for equality
             * \return true if the master array is equivalent to the std::string. */
            bool equals(std::string ostr) const;

            /**Adds a OneString<8> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<8>& ostr);

            /**Adds a OneString<16> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<16>& ostr);

            /**Adds a OneString<32> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<32>& ostr);

            /**Adds a OneString<64> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<64>& ostr);

            /**Adds a OneString<128> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<128>& ostr);

            /**Adds a OneString<256> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<256>& ostr);

            /**Adds a OneString<512> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<512>& ostr);

            /**Adds a OneString<1024> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<1024>& ostr);

            /**Adds a OneString<2048> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<2048>& ostr);

            /**Adds a OneString<4096> onto the end of the master array
             * \param the OneString to be added to the end of the master array */
            void append(const OneString<4096>& ostr);

            /**Adds a const char* onto the end of the master array
             * \param the const char* to be added to the end of the master array */
            void append(const char* ostr);

            /**Adds a std::string to the end of the master array
             * \param the std::string to be added to the end of the master array */
            void append(std::string ostr);

            /**Adds a char onto the end of the master array
             * \param the char to be added to the end of the master array */
            void append(char ochar);

            /**Adds a OneChar onto the end of the master array
             * \param the OneChar to be added to the end of the master array */
            void append(OneChar ochar);

            /**Inserts a OneString<8> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<8> to be inserted */
            void insert(int pos, const OneString<8>& ostr);

            /**Inserts a OneString<16> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<16> to be inserted */
            void insert(int pos, const OneString<16>& ostr);

            /**Inserts a OneString<32> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<32> to be inserted */
            void insert(int pos, const OneString<32>& ostr);

            /**Inserts a OneString<64> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<64> to be inserted */
            void insert(int pos, const OneString<64>& ostr);

            /**Inserts a OneString<128> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<128> to be inserted */
            void insert(int pos, const OneString<128>& ostr);

            /**Inserts a OneString<256> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<256> to be inserted */
            void insert(int pos, const OneString<256>& ostr);

            /**Inserts a OneString<512> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<512> to be inserted */
            void insert(int pos, const OneString<512>& ostr);

            /**Inserts a OneString<1024> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<1024> to be inserted */
            void insert(int pos, const OneString<1024>& ostr);

            /**Inserts a OneString<2048> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<2048> to be inserted */
            void insert(int pos, const OneString<2048>& ostr);

            /**Inserts a OneString<4096> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the OneString<4096> to be inserted */
            void insert(int pos, const OneString<4096>& ostr);

            /**Inserts a char* into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the const char* to be inserted */
            void insert(int pos, const char* ostr);

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
            void insert(int pos, OneChar ochar);

            /**Creates a substring from the master array
             * \param an int that corresponds to the start of the substring
             * \param an int for the size of the substring. Defaults to -1 to
             * indicate that the substring goes to the end of the master array
             * \return a OneString that is a substring of the master array*/
            OneString substr(int pos, int sublen = -1);

            /**Appends a single char to the end of a OneString
             * Same as append(char)
             * \param the char to be appended */
             void push_back(char ch);

             /**Erases the last OneChar of the OneString and reduces len */
             void pop_back();

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<8> to be swapped with */
             void swap(OneString<8>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<16> to be swapped with */
             void swap(OneString<16>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<32> to be swapped with */
             void swap(OneString<32>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<64> to be swapped with */
             void swap(OneString<64>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<128> to be swapped with */
             void swap(OneString<128>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<256> to be swapped with */
             void swap(OneString<256>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<512> to be swapped with */
             void swap(OneString<512>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<1024> to be swapped with */
             void swap(OneString<1024>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<2048> to be swapped with */
             void swap(OneString<2048>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the OneString<4096> to be swapped with */
             void swap(OneString<4096>& str);

             /**Returns total number of bytes used
              * \return an int that indicates how many bytes the OneString is */
             int length();

             /**Returns the largest a specific OneString can be
              * \return an int that indicates the max_size for a specific class */
             int max_size();

             /**Determines if a OneString is empty or not
              * \return true if len == 0, false otherwise */
             bool empty() const;

             /**Erases contents of the OneString. Len becomes 0 */
             void clear();


            /**Retrieve OneChar from OneString
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the OneString
             * \return returns the OneChar located at pos */
            OneChar operator [](int pos) const;

             /**Retrieve OneChar from OneString
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the OneString
             * \return returns the OneChar located at pos */
            OneChar& operator [](int pos);

            /**Copy Constructor for assignment operator OneString<8>
             * \param the OneString<8> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<8> newostr);

            /**Copy Constructor for assignment operator OneString<16>
             * \param the OneString<16> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<16> newostr);

            /**Copy Constructor for assignment operator OneString<32>
             * \param the OneString<32> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<32> newostr);

            /**Copy Constructor for assignment operator OneString<64>
             * \param the OneString<64> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<64> newostr);

            /**Copy Constructor for assignment operator OneString<64>
             * \param the OneString<128> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<128> newostr);

            /**Copy Constructor for assignment operator OneString<64>
             * \param the OneString<256> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<256> newostr);

            /**Copy Constructor for assignment operator OneString<64>
             * \param the OneString<512> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<512> newostr);

            /**Copy Constructor for assignment operator OneString<64>
             * \param the OneString<1024> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<1024> newostr);

            /**Copy Constructor for assignment operator OneString<64>
             * \param the OneString<2048> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<2048> newostr);

            /**Copy Constructor for assignment operator OneString<64>
             * \param the OneString<4096> to be copied
             * \return a new OneString that is a deep copy of ostr */
            OneString operator=(OneString<4096> newostr);

            /**Create a OneString from std::string with assignment operator
             * \param the std::string to be converted to OneString
             * \return a OneString representation of str.
             *         All Unicode will be parsed appropriately. */
            OneString operator=(std::string str);

            /**Create a OneString from const char* with assignment operator
             * Note: Double quotes default to const char*
             * \param the const char* to be converted to OneString
             * \return a OneString representation of str.
             *         All Unicode will be parsed appropriately. */
            OneString operator=(const char* str);

            /**Create a OneString from a single char with assignment operator
             * \param the char to be converted to OneString
             * \return a OneString representation of ch. */
            OneString operator=(char ch);

            /**Create a OneString from a OneChar with assignment operator
             * \param the OneChar to be converted to OneString
             * \return a OneString representation of ch. */
            OneString operator=(OneChar ch);

            // Comparison operators

            // Because these friend functions are defined in the header, templates
            // can be used to account for different OneString sizes getting passed
            // as arguments. The left hand side will be the OneString type of
            // the current instance.
            /**Tests for equality with another OneString of varying sizes
             * \param the left-hand OneString operand
             * \param a OneString (of different sizes) to be tested for equality
             * \return true if both OneStrings are exactly equivalent. */
            template<const int oneSize2>
            friend bool operator==(const OneString& ostr1, const OneString<oneSize2>& ostr2)
            {
                // Goes to OneString version
                return ostr1.equals(ostr2);
            };

            /**Tests for equality with another OneString
             * \param the left-hand OneString operand
             * \param a const char* to be tested for equality
             * \return true if the OneString is equivalent to the char* */
            friend bool operator==(const OneString& ostr1, const char* ostr2)
            {
                // Goes to char* version
                return ostr1.equals(ostr2);
            };

            /**Tests for equality with another OneString
             * \param the left-hand OneString operand
             * \param a std::string to be tested for equality
             * \return true if the OneString is equivalent to the std::string */
            friend bool operator==(const OneString& ostr1, std::string ostr2)
            {
                // Goes to string version
                return ostr1.equals(ostr2);
            };


            /**The less-than operator
             * \param the left-hand OneString operand
             * \param the right-hand OneString operand
             * \return true if the left-hand operand is less than the right-hand */
            template<const int oneSize2>
            friend bool operator<(const OneString& ostr1, const OneString<oneSize2>& ostr2)
            {
                // Only loop as far as the smallest string
                int small_len = (ostr1.size() < ostr2.size())? ostr1.size(): ostr2.size();
                for(int i = 0; i< small_len; i++)
                {
                    if(ostr1[i] < ostr2[i])
                    return true;
                }

                // If they made it through the loop and ostr1 is smaller
                // then return true
                if((small_len == ostr1.size()) && (small_len != ostr2.size()))
                    return true;
                return false;
            };

            /**The less-than operator
             * \param the left-hand OneString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is less than the right-hand */
            friend bool operator<(const OneString& ostr1, const char* ostr2)
            {
                // Call the OneString version
                OneString<oneSize> convert = ostr2;
                return (ostr1 < convert);
            };

            /**The less-than operator
             * \param the left-hand OneString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is less than the right-hand */
            friend bool operator<(const OneString& ostr1, std::string ostr2)
            {
                // Call the OneString version
                OneString<oneSize> convert = ostr2;
                return (ostr1 < convert);
            };

            /**The less-than-or-equal operator
             * \param the left-hand OneString operand
             * \param the right-hand OneString operand
             * \return true if the left-hand operand is less than or equal
             *         the right-hand */
            template<const int oneSize2>
            friend bool operator<=(const OneString& ostr1, const OneString<oneSize2>& ostr2)
            {
                // Cannot call ! greater-than because an infinite loop would occur
                return ((ostr1 < ostr2)|| (ostr1 == ostr2));
            };

             /**The less-than-or-equal operator
             * \param the left-hand OneString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is less than or equal
             *         the right-hand */
            friend bool operator<=(const OneString& ostr1, const char* ostr2)
            {
                // Call the OneString version
                OneString<oneSize> convert = ostr2;
                return (ostr1 <= convert);
            };

             /**The less-than-or-equal operator
             * \param the left-hand OneString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is less than or equal
             *         the right-hand */
            friend bool operator<=(const OneString& ostr1, std::string ostr2)
            {
                OneString<oneSize> convert = ostr2;
                return (ostr1 <= convert);
            };

             /**The greater-than operator
             * \param the left-hand OneString operand
             * \param the right-hand OneString operand
             * \return true if the left-hand operand is greater than the right-hand */
            template<const int oneSize2>
            friend bool operator>(const OneString& ostr1, const OneString<oneSize2>& ostr2)
            {
                // Call previously made functions
                return(!(ostr1 <= ostr2));
            };

            /**The greater-than operator
             * \param the left-hand OneString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is greater than the right-hand */
            friend bool operator>(const OneString& ostr1, const char* ostr2)
            {
                OneString<oneSize> convert = ostr2;
                return(ostr1 > convert);
            };

            /**The greater-than operator
             * \param the left-hand OneString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is greater than the right-hand */
            friend bool operator>(const OneString& ostr1, std::string ostr2)
            {
                OneString<oneSize> convert = ostr2;
                return(ostr1 > convert);
            };

            /**The greater-than-or-equal operator
             * \param the left-hand OneString operand
             * \param the right-hand OneString operand
             * \return true if the left-hand operand is greater than or equal
             *         to the right-hand */
            template<const int oneSize2>
            friend bool operator>=(const OneString& ostr1, const OneString<oneSize2>& ostr2)
            {
                // Use previously made functions
                return(!(ostr1 < ostr2));
            };

            /**The greater-than-or-equal operator
             * \param the left-hand OneString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is greater than or equal
             *         to the right-hand */
            friend bool operator>=(const OneString& ostr1, const char* ostr2)
            {
                OneString<oneSize> convert = ostr2;
                return(ostr1 >= convert);
            };

            /**The greater-than-or-equal operator
             * \param the left-hand OneString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is greater than or equal
             *         to the right-hand */
            friend bool operator>=(const OneString& ostr1, std::string ostr2)
            {
                OneString<oneSize> convert = ostr2;
                return(ostr1 >= convert);
            };

            /**Appends a OneString onto the end of another OneString
             * \param the left-hand OneString operand to be appended to
             * \param the OneString to be appended onto the left-hand operand*/
            template<const int oneSize2>
            friend void operator+=(OneString& ostr1, const OneString<oneSize2>& ostr2)
            {
                ostr1.append(ostr2);
            };

            /**Appends a const char* onto the end of another OneString
             * \param the left-hand OneString operand to be appended to
             * \param the const char* to be appended onto the left-hand operand*/
            friend void operator+=(OneString& ostr1, const char* ostr2)
            {
                ostr1.append(ostr2);
            };

            /**Appends a std::string onto the end of another OneString
             * \param the left-hand OneString operand to be appended to
             * \param the std::string to be appended onto the left-hand operand*/
            friend void operator+=(OneString& ostr1, std::string ostr2)
            {
                ostr1.append(ostr2);
            };

            /**Appends a char onto the end of another OneString
             * \param the left-hand OneString operand to be appended to
             * \param the char to be appended onto the left-hand operand*/
            friend void operator+=(OneString& ostr1, char ochar)
            {
                ostr1.append(ochar);
            };

            /**Appends a OneChar onto the end of another OneString
             * \param the left-hand OneString operand to be appended to
             * \param the OneChar to be appended onto the left-hand operand*/
            friend void operator+=(OneString& ostr1, OneChar ochar)
            {
                ostr1.append(ochar);
            };

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
            friend OneString operator+(OneChar lhs, OneString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Operator to output a OneString
             * \param the ostream to output on
             * \param the OneString to output
             * \return outputs the OneString as a cohesive string */
            friend std::ostream& operator<<(std::ostream& os, const OneString& ostr)
            {
                // Loop through and output each OneChar. Since OneChar has its
                // own operator<< overload everything shall be displayed neatly
                for(int i = 0; i < ostr.size(); i++)
                    os << ostr.master[i];
                return os;
            };

            /**Inputs a OneString from the user so long as there are no spaces
             * \param the istream to receive input from
             * \param the OneString to be input
             * \return an istream containing the inputted OneString */
            friend std::istream& operator>>(std::istream& in, OneString& ostr)
            {
                std::string temp;
                in >> temp;
                ostr = temp;
                return in;
            };

        private:
             /**Parses char* into OneString based on size
             * Used primarily for Unicode Characters within OneString(const char*)
             * \param the const char* to be parsed
             * \param an int to represent the index to parse the char* at
             * \param an int to represent the number of bytes in the char* */
            void parseChar(const char* str, int index, int bytes);


            int len;
            int MAX_SIZE = oneSize;
            OneChar master[oneSize];
    };

    //#include "../src/OneString.cpp"

}
#endif // ONESTRING_HPP
