/** onechar [PawLIB]
  * Version: 0.4
  *
  * Onechar is an enhanced UTF-8 character class which is fully compatible with
  * the atomic char type, c-strings, and std::string. Onestring is a string
  * class which uses Onechars.
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

#ifndef ONECHAR_HPP
#define ONECHAR_HPP

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace pawlib
{
    class onestring;

    /** Stores a single unicode character */
    class onechar
    {
        friend onestring;
        private:
            /* We never store more than 4 bytes of meaningful data.
             * The null terminator is stored as an implementation detail, but
             * is ignored by virtually all Onechar functions. */
            static const size_t MAX_SIZE = 4;

            /// The number of bytes stored.
            size_t size;

            /// The character array as a c-string.
            char internal[MAX_SIZE + 1];

            /** Store an ASCII character in this onechar
              * \param the char to copy */
            void parse(const char);

            /** Extract and store a Unicode character from a c-string.
              * If more than one character is present in the c-string, only the
              * first will be parsed out; the rest will be ignored.
              * \param the c-string to extract the character from */
            void parse(const char*);

            /** Extract and store a Unicode character from a std::string.
              * If more than one character is present in the std::string, only
              * the first will be parsed out; the rest will be ignored.
              * \param the std::string to extract the character from */
            void parse(const std::string&);

            /** Extract and store a Unicode character from a c-string at the
              * given index. Returns the number of characters in the extracted
              * Unicode character, to aid in external parsing algorithms.
              * \param the c-string to extract the character from
              * \param the index of the start of the Unicode character
              * \return the number of elements (chars) parsed out */
            size_t parseFromString(const char*, size_t index);

            /** Extract and store a Unicode character from a std::string at the
              * given index. Returns the number of characters in the extracted
              * Unicode character, to aid in external parsing algorithms.
              * \param the std::string to extract the character from
              * \param the index of the start of the Unicode character
              * \return the number of elements (chars) parsed out */
            size_t parseFromString(const std::string&, size_t index);

        public:
            /** Initialize a onechar as a null terminator */
            onechar();

            /** Initialize a onechar with an ASCII character */
            // cppcheck-suppress noExplicitConstructor
            onechar(const char);

            /** Initialize a onechar with an ASCII or Unicode character
              * in a c-string. */
            // cppcheck-suppress noExplicitConstructor
            onechar(const char*);

            /** Initialize a onechar with an ASCII or Unicode character
              * in a std::string. */
            // cppcheck-suppress noExplicitConstructor
            onechar(const std::string&);

            /** Initialize a onechar as a copy of another. */
            onechar(const onechar&);

            /** Initialize a onechar by moving another. */
            onechar(onechar&&);

            /** Destructor */
            ~onechar(){};

            /** Test for equality against a character
              * \param the char to test against
              * \return true if equal, else false*/
            bool equals(const char) const;

            /** Test for equality against a c-string.
              * Does NOT ignore extraneous characters in the c-string
              * \param the c-string to test against
              * \return true if equal, else false */
            bool equals(const char*) const;

            /** Test for equality against the first character in a c-string.
              * Unlike equals(), DOES ignore extraneous characters
              * \param the c-string to test against
              * \return true in equal, else false */
            bool equals_at(const char*) const;

            /** Test for equality against a std::string
              * Does NOT ignore extraneous characters in the std::string
              * \param the std::string to test against
              * \return true if equal, else false */
            bool equals(const std::string&) const;

            /** Test for equality against another onechar
              * \param the onechar to test against
              * \return true if equal, else false */
            bool equals(const onechar&) const;

            /** Returns the c-string representation of the onechar.
              * Appends a null terminator.
              * \return c-string of the character */
            const char* c_str() const;

            /** Compare against a character.
              * \param the char to test against
              * \return 0 if equal to argument, negative if less, positive if greater */
            int compare(const char) const;

            /** Compare against a c-string.
              * Does NOT ignore extraneous characters in the c-string
              * \param the c-string to test against
              * \return 0 if equal to argument, negative if less, positive if greater */
            int compare(const char*) const;

            /** Compare against a std::string.
              * Does NOT ignore extraneous characters in the std::string
              * \param the std::string to test against
              * \return 0 if equal to argument, negative if less, positive if greater */
            int compare(const std::string&) const;

            /** Compare against another onechar
              * \param the onechar to test against
              * \return 0 if equal to argument, negative if less, positive if greater */
            int compare(const onechar&) const;

            /** Evaluate the number of bytes in a Unicode character.
              * Ignores all subsequent characters.
              * \param the pointer to the Unicode character (c-string)
              * \return the number of bytes in the Unicode character */
            static size_t evaluateLength(const char* cstr)
            {
                switch (cstr[0] & 0xF0)
                {
                    case 0xF0:
                    {
                        // Unicode code points U+10000 to U+10FFFF
                        return 4;
                    }
                    case 0xE0:
                    {
                        // Unicode code points U+0800 to U+FFFF
                        return 3;
                    }
                    case 0xD0:
                    case 0xC0:
                    {
                        // Unicode code points U+0080 to U+07FF
                        return 2;
                    }
                    default:
                    {
                        // Unicode code points U+0000 to U+007F
                        return 1;
                    }
                }
                // Can't happen
                return 0;
            }

            // Assignment Operators

            onechar& operator=(char ch)
            {
                parse(ch);
                return *this;
            }

            onechar& operator=(const char* cstr)
            {
                parse(cstr);
                return *this;
            }

            onechar& operator=(const std::string& str)
            {
                parse(str);
                return *this;
            }

            onechar& operator=(const onechar&);

            onechar& operator=(onechar&&);

            // Comparison Operators

            bool operator==(const char cmp) const { return equals(cmp); }
            bool operator==(const char* cmp) const { return equals(cmp); }
            bool operator==(const std::string& cmp) const { return equals(cmp); }
            bool operator==(const onechar& cmp) const { return equals(cmp); }

            bool operator!=(const char cmp) const { return !equals(cmp); }
            bool operator!=(const char* cmp) const { return !equals(cmp); }
            bool operator!=(const std::string& cmp) const { return !equals(cmp); }
            bool operator!=(const onechar& cmp) const { return !equals(cmp); }

            bool operator<(const char cmp) const { return (compare(cmp) < 0); }
            bool operator<(const char* cmp) const { return (compare(cmp) < 0); }
            bool operator<(const std::string& cmp) const { return (compare(cmp) < 0); }
            bool operator<(const onechar& cmp) const { return (compare(cmp) < 0); }

            bool operator<=(const char cmp) const { return (compare(cmp) <= 0); }
            bool operator<=(const char* cmp) const { return (compare(cmp) <= 0); }
            bool operator<=(const std::string& cmp) const { return (compare(cmp) <= 0); }
            bool operator<=(const onechar& cmp) const { return (compare(cmp) <= 0); }

            bool operator>(const char cmp) const { return (compare(cmp) > 0); }
            bool operator>(const char* cmp) const { return (compare(cmp) > 0); }
            bool operator>(const std::string& cmp) const { return (compare(cmp) > 0); }
            bool operator>(const onechar& cmp) const { return (compare(cmp) > 0); }

            bool operator>=(const char cmp) const { return (compare(cmp) >= 0); }
            bool operator>=(const char* cmp) const { return (compare(cmp) >= 0); }
            bool operator>=(const std::string& cmp) const { return (compare(cmp) >= 0); }
            bool operator>=(const onechar& cmp) const { return (compare(cmp) >= 0); }

            friend bool operator==(const char lhs, const onechar& rhs) { return rhs.equals(lhs); }
            friend bool operator==(const char* lhs, const onechar& rhs) { return rhs.equals(lhs); }
            friend bool operator==(const std::string& lhs, const onechar& rhs) { return rhs.equals(lhs); }

            friend bool operator!=(const char lhs, const onechar& rhs) { return !rhs.equals(lhs); }
            friend bool operator!=(const char* lhs, const onechar& rhs) { return !rhs.equals(lhs); }
            friend bool operator!=(const std::string& lhs, const onechar& rhs) { return !rhs.equals(lhs); }

            // Notice that we have to invert the comparison in the function body.
            friend bool operator<(const char lhs, const onechar& rhs) { return (rhs.compare(lhs) > 0); }
            friend bool operator<(const char* lhs, const onechar& rhs) { return (rhs.compare(lhs) > 0); }
            friend bool operator<(const std::string& lhs, const onechar& rhs) { return (rhs.compare(lhs) > 0); }

            friend bool operator<=(const char lhs, const onechar& rhs) { return (rhs.compare(lhs) >= 0); }
            friend bool operator<=(const char* lhs, const onechar& rhs) { return (rhs.compare(lhs) >= 0); }
            friend bool operator<=(const std::string& lhs, const onechar& rhs) { return (rhs.compare(lhs) >= 0); }

            friend bool operator>(const char lhs, const onechar& rhs) { return (rhs.compare(lhs) < 0); }
            friend bool operator>(const char* lhs, const onechar& rhs) { return (rhs.compare(lhs) < 0); }
            friend bool operator>(const std::string& lhs, const onechar& rhs) { return (rhs.compare(lhs) < 0); }

            friend bool operator>=(const char lhs, const onechar& rhs) { return (rhs.compare(lhs) <= 0); }
            friend bool operator>=(const char* lhs, const onechar& rhs) { return (rhs.compare(lhs) <= 0); }
            friend bool operator>=(const std::string& lhs, const onechar& rhs) { return (rhs.compare(lhs) <= 0); }


            // HACK: Here only to ensure compiling. Remove the need for this from onestring
            char operator[](int pos) const
            {
                return this->internal[pos];
            }


            // TODO: Revisit/rewrite these

            /** Helper function for operator<<
            * \param std::ostream to put output on */
            void print(std::ostream& os) const
            {
                os << this->c_str();
            }

            /** Output operator
            * \param std::ostream to display output on
            * \param the onechar that is the output
            * \return the std::ostream to output */
            friend std::ostream& operator<<(std::ostream& os, const onechar& ostr)
            {
                os << ostr.c_str();
                return os;
            }
    };
 }
 #endif // ONECHAR_HPP
