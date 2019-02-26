/** OneChar [PawLIB]
  * Version: 0.3
  *

  * OneChar is an array of character that can be used to represent both
  * Unicode character along with ASCII characters. We decided to go with
  * one class instead of the original two to cut out the problems that
  * arise when dealing with class hierarchies.
  *
  * Author(s): Scott Taylor, Jarek Thomas, Bowen Volwiler
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


#ifndef ONECHAR_HPP
#define ONECHAR_HPP

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

 namespace pawlib
 {
     /* OneChar class, now our main and only class. It contains all
        functions needed to handle both ASCII character and Unicode
        characters.*/
    class OneChar
    {
        private:
            static const uint_least8_t MAX_SIZE = 4;

            /// The number of bytes stored.
            uint_least8_t size;
            /// The character array
            char internal[MAX_SIZE];

            void copy(const OneChar&);
            void parse(const char);
            void parse(const char*);

            static uint_least8_t evaluateLength(const char* cstr)
            {
                switch (cstr[0] & 0xF0)
                {
                    case 0xF0:
                    {
                        return 4;
                    }
                    case 0xE0:
                    {
                        return 3;
                    }
                    case 0xC0:
                    {
                        return 2;
                    }
                    default:
                    {
                        return 1;
                    }
                }
            }

        public:
            /** Blank constructor
            *  Neccesary for declaring an
            *  array of OneChars */
            OneChar();

            // cppcheck-suppress noExplicitConstructor
            OneChar(const char*);

            // cppcheck-suppress noExplicitConstructor
            OneChar(const char);

            /** Copy constructor */
            OneChar(const OneChar&);

            /** Destructor */
            ~OneChar(){};

            /** Retrieve char from OneChar
            * This takes care of the setting part of the index operator
            * \param the desired position within the OneChar
            * \return returns that reference of the char located at pos*/
            char operator[](int pos) const;

            /** Assignment operator for char
            * \param the char to be initialized from
            * \return an initialized OneChar*/
            OneChar& operator=(char newChar);

            /** Assignment operator for const char*
            * \param the const char* to be initialized from
            * \return an initialized OneChar*/
            OneChar& operator=(const char* newChar);

            /** Assignment operator for OneChar
            * \param the base class OneChar to be initialized from
            * \return an initialized OneChar*/
            OneChar& operator=(const OneChar& newChar);

            bool equals(const char) const;
            bool equals(const char*) const;
            bool equals(const OneChar&) const;

            /** Equals operator for char
            * \param the char to be compared to
            * \return true if the param is equal to the current OneChar
                otherwise return false*/
            bool operator==(const char) const;

            bool operator==(const char*) const;

            /** Equals operator for OneChar
            * \param the base class OneChar to be compared to
            * \return true if the param is equal to the current OneChar
                otherwise return false*/
            bool operator==(const OneChar&) const;

            /** Not equals operator for OneChar
            * \param the base class OneChar to be compared to
            * \return true if the param is equal to the current OneChar
                otherwise return false*/
            bool operator!=(const char) const;

            bool operator!=(const char*) const;

            /** Not equals operator for OneChar
            * \param the base class OneChar to be compared to
            * \return true if the param is equal to the current OneChar
                otherwise return false*/
            bool operator!=(const OneChar&) const;

            /** Helper function for operator<<
            * \param std::ostream to put output on */
            // NOTE: Was previously pure
            virtual void print(std:: ostream& os) const;

            const char* c_str() const;

            uint8_t compare(const char) const;
            uint8_t compare(const char*) const;

            /** Helper function for operator<
            * \param the OneChar to be compared to
            * \return true if the OneChar is equal to the current class */
            uint8_t compare(const OneChar&) const;

            /** Function to allow direct access to internal array
             * \param internal array exists to add */
            void addDirectly(char newChar, int pos);

            /** Determines if a OneChar is less than another OneChar
            * \param the OneChar being compared to.
            \ return true if ochr's value is less than newChar */
            bool operator<(const OneChar& cmp)
            {
                return (compare(cmp) < 0);
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
