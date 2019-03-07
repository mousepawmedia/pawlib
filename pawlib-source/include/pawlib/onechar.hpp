/** OneChar [PawLIB]
  * Version: 0.4
  *

  * OneChar is an array of character that can be used to represent both
  * Unicode character along with ASCII characters. We decided to go with
  * one class instead of the original two to cut out the problems that
  * arise when dealing with class hierarchies.
  *
  * Author(s): Scott Taylor, Jarek Thomas, Bowen Volwiler
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
    class OneString;

     /* OneChar class, now our main and only class. It contains all
        functions needed to handle both ASCII character and Unicode
        characters.*/
    class OneChar
    {
        friend OneString;
        private:
            static const size_t MAX_SIZE = 4;

            /// The number of bytes stored.
            size_t size;
            /// The character array
            char internal[MAX_SIZE];

            void copy(const OneChar&);
            void parse(const char);
            void parse(const char*);
            void parse(const std::string&);

            size_t parseFromString(const char*, size_t index);
            size_t parseFromString(const std::string, size_t index);

        public:
            /** Blank constructor
            *  Neccesary for declaring an
            *  array of OneChars */
            OneChar();

            // cppcheck-suppress noExplicitConstructor
            OneChar(const char);

            // cppcheck-suppress noExplicitConstructor
            OneChar(const char*);

            // cppcheck-suppress noExplicitConstructor
            OneChar(const std::string&);

            /** Copy constructor */
            OneChar(const OneChar&);

            /** Destructor */
            ~OneChar(){};

            /** Retrieve char from OneChar
            * This takes care of the setting part of the index operator
            * \param the desired position within the OneChar
            * \return returns that reference of the char located at pos*/
            char operator[](int pos) const;

            OneChar& operator=(char newChar);
            OneChar& operator=(const char* newChar);
            OneChar& operator=(const std::string& newChar);
            OneChar& operator=(const OneChar& newChar);

            bool equals(const char) const;
            bool equals(const char*) const;
            bool equals(const std::string&) const;
            bool equals(const OneChar&) const;

            const char* c_str() const;

            int compare(const char) const;
            int compare(const char*) const;
            int compare(const std::string&) const;
            int compare(const OneChar&) const;

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


            bool operator==(const char cmp) const { return equals(cmp); }
            bool operator==(const char* cmp) const { return equals(cmp); }
            bool operator==(const std::string& cmp) const { return equals(cmp); }
            bool operator==(const OneChar& cmp) const { return equals(cmp); }

            bool operator!=(const char cmp) const { return !equals(cmp); }
            bool operator!=(const char* cmp) const { return !equals(cmp); }
            bool operator!=(const std::string& cmp) const { return !equals(cmp); }
            bool operator!=(const OneChar& cmp) const { return !equals(cmp); }

            bool operator<(const char cmp) const { return (compare(cmp) < 0); }
            bool operator<(const char* cmp) const { return (compare(cmp) < 0); }
            bool operator<(const std::string& cmp) const { return (compare(cmp) < 0); }
            bool operator<(const OneChar& cmp) const { return (compare(cmp) < 0); }

            bool operator<=(const char cmp) const { return (compare(cmp) <= 0); }
            bool operator<=(const char* cmp) const { return (compare(cmp) <= 0); }
            bool operator<=(const std::string& cmp) const { return (compare(cmp) <= 0); }
            bool operator<=(const OneChar& cmp) const { return (compare(cmp) <= 0); }

            bool operator>(const char cmp) const { return (compare(cmp) > 0); }
            bool operator>(const char* cmp) const { return (compare(cmp) > 0); }
            bool operator>(const std::string& cmp) const { return (compare(cmp) > 0); }
            bool operator>(const OneChar& cmp) const { return (compare(cmp) > 0); }

            bool operator>=(const char cmp) const { return (compare(cmp) >= 0); }
            bool operator>=(const char* cmp) const { return (compare(cmp) >= 0); }
            bool operator>=(const std::string& cmp) const { return (compare(cmp) >= 0); }
            bool operator>=(const OneChar& cmp) const { return (compare(cmp) >= 0); }

            friend bool operator==(const char lhs, const OneChar& rhs) { return rhs.equals(lhs); }
            friend bool operator==(const char* lhs, const OneChar& rhs) { return rhs.equals(lhs); }
            friend bool operator==(const std::string& lhs, const OneChar& rhs) { return rhs.equals(lhs); }

            friend bool operator!=(const char lhs, const OneChar& rhs) { return !rhs.equals(lhs); }
            friend bool operator!=(const char* lhs, const OneChar& rhs) { return !rhs.equals(lhs); }
            friend bool operator!=(const std::string& lhs, const OneChar& rhs) { return !rhs.equals(lhs); }

            // Notice that we have to invert the comparison in the function body.
            friend bool operator<(const char lhs, const OneChar& rhs) { return (rhs.compare(lhs) > 0); }
            friend bool operator<(const char* lhs, const OneChar& rhs) { return (rhs.compare(lhs) > 0); }
            friend bool operator<(const std::string& lhs, const OneChar& rhs) { return (rhs.compare(lhs) > 0); }

            friend bool operator<=(const char lhs, const OneChar& rhs) { return (rhs.compare(lhs) >= 0); }
            friend bool operator<=(const char* lhs, const OneChar& rhs) { return (rhs.compare(lhs) >= 0); }
            friend bool operator<=(const std::string& lhs, const OneChar& rhs) { return (rhs.compare(lhs) >= 0); }

            friend bool operator>(const char lhs, const OneChar& rhs) { return (rhs.compare(lhs) < 0); }
            friend bool operator>(const char* lhs, const OneChar& rhs) { return (rhs.compare(lhs) < 0); }
            friend bool operator>(const std::string& lhs, const OneChar& rhs) { return (rhs.compare(lhs) < 0); }

            friend bool operator>=(const char lhs, const OneChar& rhs) { return (rhs.compare(lhs) <= 0); }
            friend bool operator>=(const char* lhs, const OneChar& rhs) { return (rhs.compare(lhs) <= 0); }
            friend bool operator>=(const std::string& lhs, const OneChar& rhs) { return (rhs.compare(lhs) <= 0); }


            // TODO: Revisit/rewrite these

            /** Helper function for operator<<
            * \param std::ostream to put output on */
            void print(std::ostream& os) const
            {
                os << this->internal << '\0';
            }

            /** Output operator
            * \param std::ostream to display output on
            * \param the OneChar that is the output
            * \return the std::ostream to output */
            friend std::ostream& operator<<(std:: ostream& os, const OneChar& ostr)
            {
                ostr.print(os);
                return os;
            }
    };
 }
 #endif // ONECHAR_HPP
