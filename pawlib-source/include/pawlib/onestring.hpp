/** onestring [PawLIB]
  * Version: 0.4
  *
  * onestring is a multi-sized, Unicode-compatible replacement
  * for std::string. onestring contains all the
  * basic functions found in std::string. The size of the
  * the onestring is doubled whenever the current size is maxed out.
  * To handle Unicode, each onestring is made of onechars,
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

#include <algorithm>
#include <cctype> // isspace()
#include <cstring>
#include <iomanip>
#include <iostream>
#include <istream>

#include "pawlib/onechar.hpp"

namespace pawlib
{
    class onestring
    {
        public:
            /// The default size the onestring is initialized at
            inline static const size_t BASE_SIZE = 4;

            /// The greatest possible value for an element.
            inline static const size_t npos = -1;

            /// The factor the capacity is multiplied by to resize
            inline static const float RESIZE_FACTOR = 1.5;

        private:
            /// The maximum number of elements that can be stored without resize
            size_t _capacity;

            /// The number of elements currently stored
            size_t _elements;

            /// The array of onechars
            onechar* internal;

            void replace_setup(size_t pos, size_t len, size_t sublen);

        public:
            /*******************************************
            * Constructors + Destructor
            *******************************************/

            /**Default Constructor*/
            onestring();

            /**Create a onestring from c-string (string literal)
            * \param the c-string to be converted to onestring */
            // cppcheck-suppress noExplicitConstructor
            onestring(const char* str);

            /**Create a onestring from std::string
            * \param the string to be converted to onestring */
            // cppcheck-suppress noExplicitConstructor
            onestring(const std::string& str);

            /**Create a onestring from another onestring
            * \param the onestring to be copied */
            onestring(const onestring& str);

            /**Create a onestring from a char
             *  \param the char to be added */
            // cppcheck-suppress noExplicitConstructor
            onestring(char ch);

            /**Create a onestring from a onechar
             *  \param the onechar to be added */
            // cppcheck-suppress noExplicitConstructor
            onestring(const onechar& ch);

            /**Destructor*/
            ~onestring();

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

                // If we're about to blow past indexing, fail
                if (elements >= npos) { return; }

                // Expand until we have enough space.
                while (this->_capacity < elements)
                {
                    this->_capacity *= RESIZE_FACTOR;
                }

                // TODO: Would it be better to use realloc? (If so, be sure to throw bad_alloc as needed)

                // Allocate a new array with the new size.
                onechar* newArr = new onechar[this->_capacity];

                // If an old array exists...
                if(this->internal != nullptr)
                {
                    // Move the contents over
                    memmove(
                        newArr,
                        this->internal,
                        sizeof(onechar) * this->_elements
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
                    index += onechar::evaluateLength(cstr + index);
                    ++count;
                }
                return count;
            }

            /*******************************************
            * Access
            *******************************************/

            /** Gets the onechar at a given position
              * \param the index of the onechar to return
              * \return a reference to the corresponding onechar */
            onechar& at(size_t pos);
            const onechar& at(size_t pos) const;

            /** Gets the last onechar in the string.
              * If the string is empty, this has undefined behavior
              * (although it is guaranteed memory safe.)
              * \return a reference to the last onechar in the string.
              */
            onechar& back();
            const onechar& back() const;

            /** Gets the current capacity of the onestring.
              * Used primarily internally for resizing purposes.
              * \return the size of the onestring */
            size_t capacity() const;

            /** Copies a substring from the onestring to the given array.
              * Guaranteed to copy the entirety of any Unicode character,
              * or else skip it.
              * \param pointer to an array of characters (c-string)
              * \param the maximum number of char elements in the c-string
              * \param the number of Unicode characters to copy. Defaults to 0,
              * which will copy the maximum number of characters that will fit
              * into the c-string.
              * \param the position of the first character to be copied (optional)
              * If this is greater than the string length, it throws out_of_range
              * \return the number of char elements copied to the array*/
            size_t copy(char* arr, size_t max, size_t len = 0, size_t pos = 0) const;

            /** Returns a c-string equivalent of a onestring
              * \return the c-string (remember to free[]) */
            const char* c_str() const;

            /** Returns a c-string equivalent of a onestring
              * Alias for onestring::c_str()
              * \return the c-string (remember to free[]) */
            const char* data() const { return c_str(); }

            /**Checks to see if a onestring contains any data
             * \returns true if empty, else false */
            bool empty() const;

            /** Gets the first onechar in the string.
              * If the string is empty, this has undefined behavior
              * (although it is guaranteed memory safe.)
              * \return a reference to the first onechar in the string.
              */
            onechar& front();
            const onechar& front() const;

            /**Gets the current number of elements in the onestring
             * \return the number of elements */
            size_t length() const;

            /** Returns the largest possible index allowed in onestring.
              * This is theoretical only, based on implementation. Allocation
              * may fail well before this.
              */
            static size_t max_size() { return npos; }

            /**Creates a smaller string out of
             * a series of onechars in the existing onestring
             * \param the position to begin the string to be created
             * \param the length of the string to be created, optional.
             * \return the created string */
            onestring substr(size_t pos = 0, size_t len = npos) const;

            /**Gets the byte size of the equivalent c-string.
              * WARNING: Given a onestring 's', s.size() < sizeof(s)
              * \return the number of bytes in the onestring */
            size_t size() const;

            /** Gets the byte size of the equivalent c-string for the
              * specified substring.
              * \param the number of Unicode characters in the substring.
              * \param the position of the first character in the substring.
              * Defaults to 0.
              * If this is greater than the string length, it throws out_of_range
              */
            size_t size(size_t, size_t = 0) const;


            /*******************************************
            * Comparison
            ********************************************/

            bool equals(const char) const;
            bool equals(const char*) const;
            bool equals(const std::string&) const;
            bool equals(const onechar&) const;
            bool equals(const onestring&) const;

            int compare(const char) const;
            int compare(const char*) const;
            int compare(const std::string&) const;
            int compare(const onechar&) const;
            int compare(const onestring&) const;

            /*******************************************
            * Adding + Inserting
            ********************************************/

            onestring& assign(const char);
            onestring& assign(const char*);
            onestring& assign(const std::string&);
            onestring& assign(const onechar&);
            onestring& assign(const onestring&);

            onestring& append(const char);
            onestring& append(const char*);
            onestring& append(const std::string&);
            onestring& append(const onechar&);
            onestring& append(const onestring&);

            onestring& insert(size_t pos, char ch);
            onestring& insert(size_t pos, char* cstr);
            onestring& insert(size_t pos, std::string& str);
            onestring& insert(size_t pos, onechar& ochr);
            onestring& insert(size_t pos, const onestring& ostr);

            onestring& push_back(char ch) { return append(ch); }
            onestring& push_back(const char* cstr) { return append(cstr); }
            onestring& push_back(const std::string& str) { return append(str); }
            onestring& push_back(const onechar& ochr) { return append(ochr); }
            onestring& push_back(const onestring& ostr) { return append(ostr); }

            onestring& replace(size_t pos, size_t len, const char ch);
            onestring& replace(size_t pos, size_t len, const onechar& ochr);
            onestring& replace(size_t pos, size_t len, const char* cstr);
            onestring& replace(size_t pos, size_t len, const std::string& str);
            onestring& replace(size_t pos, size_t len, const onestring& ostr);
            onestring& replace(size_t pos, size_t len, const char* cstr, size_t subpos, size_t sublen);
            onestring& replace(size_t pos, size_t len, const std::string& str, size_t subpos, size_t sublen);
            onestring& replace(size_t pos, size_t len, const onestring& ostr, size_t subpos, size_t sublen);

            /*******************************************
            * Removing
            ********************************************/

            /** Clears a onestring and reallocates it back to BASE_SIZE */
            void clear();

            /** Erases part of a string, reducing its length.
              * \param the first character to erase. Defaults to 0.
              * If this is greater than the string length, it throws out_of_range
              * \param the total number of characters to erase
              * Defaults to all the characters from the given start position
              * to the end of the string.
              */
            onestring& erase(size_t pos = 0, size_t len = npos);

            /*******************************************
            * Operators
            ********************************************/

            onechar& operator[](size_t pos) { return at(pos); }
            const onechar& operator[](size_t pos) const { return at(pos); }

            onestring& operator=(char ch) { assign(ch); return *this; }
            onestring& operator=(const char* cstr) { assign(cstr); return *this; }
            onestring& operator=(const std::string& str) { assign(str); return *this; }
            onestring& operator=(const onechar& ochr) { assign(ochr); return *this; }
            onestring& operator=(onestring& ostr) { assign(ostr); return *this; }

            void operator+=(const char ch) { append(ch); }
            void operator+=(const char* cstr) { append(cstr); }
            void operator+=(const std::string& str) { append(str); }
            void operator+=(const onechar& ochr) { append(ochr); }
            void operator+=(const onestring& ostr) { append(ostr); }

            bool operator==(const char ch) const { return equals(ch); }
            bool operator==(const char* cstr) const { return equals(cstr); }
            bool operator==(const std::string& str) const { return equals(str); }
            bool operator==(const onechar& ochr) const { return equals(ochr); }
            bool operator==(const onestring& ostr) const { return equals(ostr); }

            friend bool operator==(const char ch, const onestring& ostr) { return ostr.equals(ch); }
            friend bool operator==(const char* cstr, const onestring& ostr) { return ostr.equals(cstr); }
            friend bool operator==(const std::string& str, const onestring& ostr) { return ostr.equals(str); }
            friend bool operator==(const onechar& ochr, const onestring& ostr) { return ostr.equals(ochr); }

            bool operator!=(const char ch) const { return !equals(ch); }
            bool operator!=(const char* cstr) const { return !equals(cstr); }
            bool operator!=(const std::string& str) const { return !equals(str); }
            bool operator!=(const onechar& ochr) const { return !equals(ochr); }
            bool operator!=(const onestring& ostr) const { return !equals(ostr); }

            friend bool operator!=(const char ch, const onestring& ostr) { return !ostr.equals(ch); }
            friend bool operator!=(const char* cstr, const onestring& ostr) { return !ostr.equals(cstr); }
            friend bool operator!=(const std::string& str, const onestring& ostr) { return !ostr.equals(str); }
            friend bool operator!=(const onechar& ochr, const onestring& ostr) { return !ostr.equals(ochr); }

            bool operator<(const char ch) const { return (compare(ch) < 0); }
            bool operator<(const char* cstr) const { return (compare(cstr) < 0); }
            bool operator<(const std::string& str) const { return (compare(str) < 0); }
            bool operator<(const onechar& ochr) const { return (compare(ochr) < 0); }
            bool operator<(const onestring& ostr) const { return (compare(ostr) < 0); }

            friend bool operator<(const char ch, const onestring& ostr) { return (ostr.compare(ch) > 0); }
            friend bool operator<(const char* cstr, const onestring& ostr) { return (ostr.compare(cstr) > 0); }
            friend bool operator<(const std::string& str, const onestring& ostr) { return (ostr.compare(str) > 0); }
            friend bool operator<(const onechar& ochr, const onestring& ostr) { return (ostr.compare(ochr) > 0); }

            bool operator<=(const char ch) const { return (compare(ch) <= 0); }
            bool operator<=(const char* cstr) const { return (compare(cstr) <= 0); }
            bool operator<=(const std::string& str) const { return (compare(str) <= 0); }
            bool operator<=(const onechar& ochr) const { return (compare(ochr) <= 0); }
            bool operator<=(const onestring& ostr) const { return (compare(ostr) <= 0); }

            friend bool operator<=(const char ch, const onestring& ostr) { return (ostr.compare(ch) >= 0); }
            friend bool operator<=(const char* cstr, const onestring& ostr) { return (ostr.compare(cstr) >= 0); }
            friend bool operator<=(const std::string& str, const onestring& ostr) { return (ostr.compare(str) >= 0); }
            friend bool operator<=(const onechar& ochr, const onestring& ostr) { return (ostr.compare(ochr) >= 0); }

            bool operator>(const char ch) const { return (compare(ch) > 0); }
            bool operator>(const char* cstr) const { return (compare(cstr) > 0); }
            bool operator>(const std::string& str) const { return (compare(str) > 0); }
            bool operator>(const onechar& ochr) const { return (compare(ochr) > 0); }
            bool operator>(const onestring& ostr) const { return (compare(ostr) > 0); }

            friend bool operator>(const char ch, const onestring& ostr) { return (ostr.compare(ch) < 0); }
            friend bool operator>(const char* cstr, const onestring& ostr) { return (ostr.compare(cstr) < 0); }
            friend bool operator>(const std::string& str, const onestring& ostr) { return (ostr.compare(str) < 0); }
            friend bool operator>(const onechar& ochr, const onestring& ostr) { return (ostr.compare(ochr) < 0); }

            bool operator>=(const char ch) const { return (compare(ch) >= 0); }
            bool operator>=(const char* cstr) const { return (compare(cstr) >= 0); }
            bool operator>=(const std::string& str) const { return (compare(str) >= 0); }
            bool operator>=(const onechar& ochr) const { return (compare(ochr) >= 0); }
            bool operator>=(const onestring& ostr) const { return (compare(ostr) >= 0); }

            friend bool operator>=(const char ch, const onestring& ostr) { return (ostr.compare(ch) <= 0); }
            friend bool operator>=(const char* cstr, const onestring& ostr) { return (ostr.compare(cstr) <= 0); }
            friend bool operator>=(const std::string& str, const onestring& ostr) { return (ostr.compare(str) <= 0); }
            friend bool operator>=(const onechar& ochr, const onestring& ostr) { return (ostr.compare(ochr) <= 0); }

            friend std::istream& operator>>(std::istream& is, onestring& ostr)
            {
                ostr.clear();

                char ch;
                while (is.get(ch) && !isspace(ch))
                {
                    ostr.append(ch);
                }
                return is;
            };

            friend std::ostream& operator<<(std::ostream& os, const onestring& ostr)
            {
                os << ostr.c_str();
                return os;
            };

            /*******************************************
            * Static Functions
            ********************************************/

            static std::istream& getline(std::istream& is, onestring& ostr, char delim = '\n')
            {
                ostr.clear();

                char ch;
                while (is.get(ch) && ch != delim)
                {
                    ostr.append(ch);
                }
                return is;
            }

            ////////////// REVIEW /////////////////

            /**Inserts a series of characters
             * Into a onestring at a given position
             * \param the position to be added
             * \param the characters to be added
             * \returns */



            /**Removes the last element
             * in a onestring
             * \param
             * \returns */
            void pop_back();

            /*******************************************
            * Comparison
            ********************************************/

            /**Helper functions for < and > operators
             * Parse through a onestring or char*
             * to determine greater than or less than
             * \param the onestring or char* to compare
             * \return whether or not the onestring is
             *         less than or equal to the item compared*/
            bool lessThanStr(const onestring& ostr);
            bool lessThanCharP(const char* ostr);

            /*******************************************
            * Other
            ********************************************/

            /**Swaps one onestring with another
             * \param the onestring to switch with
             * \return */
            void swap(onestring& str);
    };
}
#endif // PAWLIB_ONESTRING_HPP
