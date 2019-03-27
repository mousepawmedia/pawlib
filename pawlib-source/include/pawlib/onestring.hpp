/** OneString [PawLIB]
  * Version: 0.4
  *
  * OneString is a multi-sized, Unicode-compatible replacement
  * for std::string. OneString contains all the
  * basic functions found in std::string. The size of the
  * the OneString is doubled whenever the current size is maxed out.
  * To handle Unicode, each OneString is made of OneChars,
  * which are enhanced characters.
  *
  * Author(s): Jason C. McDonald, Scott Taylor, Jarek Thomas, Bowen Volwiler
  */

/* LICENSE
 * Copyright (c) 2016-2019 MousePaw Media.
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

#ifndef PAWLIB_ONESTRING_HPP
#define PAWLIB_ONESTRING_HPP

#include <cstring>
#include <iomanip>
#include <iostream>

#include "pawlib/onechar.hpp"

namespace pawlib
{
    class OneString
    {
        private:
            /// The default size the OneString is initialized at
            const int BASE_SIZE = 4;

            /// The factor the capacity is multiplied by to resize
            const float RESIZE_FACTOR = 1.5;

            /// The maximum number of elements that can be stored without resize
            size_t _capacity;

            /// The number of elements currently stored
            size_t _elements;

            /// The array of OneChars
            OneChar* internal;

        public:
            /*******************************************
            * Constructors + Destructor
            *******************************************/

            /**Default Constructor*/
            OneString();

            /**Create a OneString from c-string (string literal)
            * \param the c-string to be converted to OneString */
            // cppcheck-suppress noExplicitConstructor
            OneString(const char* str);

            /**Create a OneString from std::string
            * \param the string to be converted to OneString */
            // cppcheck-suppress noExplicitConstructor
            OneString(const std::string& str);

            /**Create a OneString from another OneString
            * \param the OneString to be copied */
            OneString(const OneString& str);

            /**Create a OneString from a char
             *  \param the char to be added */
            // cppcheck-suppress noExplicitConstructor
            OneString(char ch);

            /**Create a OneString from a OneChar
             *  \param the OneChar to be added */
            // cppcheck-suppress noExplicitConstructor
            OneString(const OneChar& ch);

            /**Destructor*/
            ~OneString();

            /*******************************************
            * Memory Management
            ********************************************/

            /** Requests that the string capacity be expanded to accomidate
             * the given number of additional characters.
             * `s.expand(n)` is equivalent to `s.reserve(s.length() + n)`
             * \param the number of additional elements to reserve space for */
            void expand(size_t expansion)
            {
                reserve(this->_elements + expansion);
            }

            /** Requests that the string capacity be expanded to accomidate
             * the given number of characters.
             * This is the primary function responsible for allocation.
             * \param the number of elements to reserve space for */
            void reserve(size_t elements)
            {
                // If we're already large enough, don't reallocate.
                if (this->_capacity >= elements) { return; }

                // A capacity of 0 will trigger a complete reallocation
                if (this->_capacity == 0)
                {
                    this->_capacity = BASE_SIZE;
                }

                // Expand until we have enough space.
                while (this->_capacity < elements)
                {
                    this->_capacity *= RESIZE_FACTOR;
                }

                // TODO: Would it be better to use realloc? (If so, be sure to throw bad_alloc as needed)

                // Allocate a new array with the new size.
                OneChar* newArr = new OneChar[this->_capacity];

                // If an old array exists...
                if(this->internal != nullptr)
                {
                    // Move the contents over
                    memmove(
                        newArr,
                        this->internal,
                        sizeof(OneChar) * this->_elements
                    );

                    // Delete the old structure
                    delete[] internal;
                    this->internal = nullptr;
                }

                // Store the new structure.
                this->internal = newArr;
            }

            /** Evaluate the number of Unicode characters in a c-string
              * \param the c-string to evaluate
              * \return the character count */
            static size_t characterCount(const char* cstr)
            {
                size_t index = 0;
                size_t count = 0;
                while (cstr[index] != '\0')
                {
                    index += OneChar::evaluateLength(cstr + index);
                    ++count;
                }
                return count;
            }

            /*******************************************
            * Access
            *******************************************/

            /**Gets the OneChar at a given position
             * \param the index of the OneChar to return
             * \return cooresponding OneChar */
            OneChar& at(size_t pos) const;

            /**Gets the current capacity of the OneString.
             * Used primarily internally for resizing purposes.
             * \return the size of the OneString */
            size_t capacity() const;

            /** Returns a c-string equivalent of a OneString
              * \return the c-string (remember to free[]) */
            const char* c_str() const;

            /** Returns a c-string equivalent of a OneString
              * Alias for OneString::c_str()
              * \return the c-string (remember to free[]) */
            const char* data() const { return c_str(); }

            /**Checks to see if a OneString contains any data
             * \returns true if empty, else false */
            bool empty() const;

            /**Gets the current number of elements in the OneString
             * \return the number of elements */
            size_t length() const;

            /**Gets the byte size of the equivalent c-string.
              * WARNING: Given a OneString 's', s.size() < sizeof(s)
              * \return the number of bytes in the OneString */
            size_t size() const;

            /*******************************************
            * Comparison
            ********************************************/

           bool equals(const char) const;
           bool equals(const char*) const;
           bool equals(const std::string&) const;
           bool equals(const OneChar&) const;
           bool equals(const OneString&) const;

            /*******************************************
            * Adding + Inserting
            ********************************************/

            void assign(const char);
            void assign(const char*);
            void assign(const std::string&);
            void assign(const OneChar&);
            void assign(const OneString&);

            /*******************************************
            * Removing
            ********************************************/

            /** Clears a OneString and reallocates it back to BASE_SIZE */
            void clear();

            /*******************************************
            * Operators
            ********************************************/

            OneChar& operator[](size_t pos) const { return at(pos); }

            OneString& operator=(char ch) { assign(ch); return *this; }
            OneString& operator=(const char* cstr) { assign(cstr); return *this; }
            OneString& operator=(const std::string& str) { assign(str); return *this; }
            OneString& operator=(const OneChar& ochr) { assign(ochr); return *this; }
            OneString& operator=(OneString& ostr) { assign(ostr); return *this; }

            bool operator==(const char ch) const { return equals(ch); }
            bool operator==(const char* cstr) const { return equals(cstr); }
            bool operator==(const std::string& str) const { return equals(str); }
            bool operator==(const OneChar& ochr) const { return equals(ochr); }
            bool operator==(const OneString& ostr) const { return equals(ostr); }

            bool operator!=(const char ch) const { return !equals(ch); }
            bool operator!=(const char* cstr) const { return !equals(cstr); }
            bool operator!=(const std::string& str) const { return !equals(str); }
            bool operator!=(const OneChar& ochr) const { return !equals(ochr); }
            bool operator!=(const OneString& ostr) const { return !equals(ostr); }

            ////////////// REVIEW /////////////////

            /**Adds the corresponding type to
             * the end of the OneString
             * in the form of a OneChar.
             * \param the characters to be added to the OneString */
            void append(const char);
            void append(const char*);
            void append(const std::string&);
            void append(const OneChar&);
            void append(const OneString&);

            /**Inserts a series of characters
             * Into a OneString at a given position
             * \param the position to be added
             * \param the characters to be added
             * \returns */
            void insert(size_t pos, char* ostr);
            void insert(size_t pos, char ochar);
            void insert(size_t pos, std::string ostr);
            void insert(size_t pos, OneChar& ochar);
            void insert(size_t pos, const OneString& ostr);

            /*An alias for append, adds characters
            * to the end of a OneString
            * \param the characters to be added
            * \returns */
            void push_back(char ochar);
            void push_back(const char* ostr);
            void push_back(const std::string& ostr);
            void push_back(const OneChar& ochar);
            void push_back(const OneString& ostr);



            /**Removes the last element
             * in a OneString
             * \param
             * \returns */
            void pop_back();

            /*******************************************
            * Comparison
            ********************************************/

            /**Helper functions for < and > operators
             * Parse through a OneString or char*
             * to determine greater than or less than
             * \param the OneString or char* to compare
             * \return whether or not the OneString is
             *         less than or equal to the item compared*/
            bool lessThanStr(const OneString& ostr);
            bool lessThanCharP(const char* ostr);

            /*******************************************
            * Other
            ********************************************/

            /**Swaps one OneString with another
             * \param the OneString to switch with
             * \return */
            void swap(OneString& str);

            /**Creates a smaller string out of
             * a series of OneChars in the existing OneString
             * \param the position to begin the string to be created
             * \param the length of the string to be created
             * \return the created string */
            OneString substr(size_t pos, size_t sublen);




            /**Checks to see if the OneString is
             * less than the cooresponding text data object
             * \param the text object to compare to
             * \return whether or not the OneString is less than*/
            bool operator<(const char* ostr2);
            bool operator<(const std::string& ostr2);
            bool operator<(const OneString& ostr2);

            /**Checks to see if the OneString is
             * less or equal to the cooresponding text data object
             * \param the text object to compare to
             * \return whether or not the OneString is less than or equal*/
            bool operator<=(const OneString& ostr2);
            bool operator<=(const char* ostr2);
            bool operator<=(const std::string& ostr2);

            /**Checks to see if the OneString is
             * greater than the cooresponding text data object
             * \param the text object to compare to
             * \return whether or not the OneString is greater than*/
            bool operator>(const OneString& ostr2);
            bool operator>(const char* ostr2);
            bool operator>(const std::string& ostr2);

            /**Checks to see if the OneString is
             * greater or equal to  the cooresponding text data object
             * \param the text object to compare to
             * \return whether or not the OneString is greater than or equal*/
            bool operator>=(const OneString& ostr2);
            bool operator>=(const char* ostr2);
            bool operator>=(const std::string& ostr2);

            /**Adds the cooresponding type to
             * the end of the OneString
             * in the form of a OneChar.
             * \param the characters to be added to the OneString
             * \returns */
            void operator+=(const OneString& ostr2);
            void operator+=(const char* ostr2);
            void operator+=(const std::string& ostr2);
            void operator+=(char ochar);
            void operator+=(const OneChar& ochar);

            /*******************************************
            * Friends
            *******************************************/

            friend std::istream& operator>>(std::istream& in, OneString& ostr)
            {
                ostr.clear();
                std::string temp;
                std::getline(in, temp);
                ostr.append(temp);
                return in;
            };

            /**Operator to output a OneString
            * \param the ostream to output on
            * \param the OneString to output
            * \return outputs the OneString as a cohesive string */
            friend std::ostream& operator<<(std::ostream& os, const OneString& ostr)
            {
                for(size_t i = 0; i < ostr.length(); ++i)
                {
                    ostr.internal[i].print(os);
                }
                return os;
            };
    };
}
#endif // PAWLIB_ONESTRING_HPP
