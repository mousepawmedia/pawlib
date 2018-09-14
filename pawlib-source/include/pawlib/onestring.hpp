/** OneString [PawLIB]
  * Version: 0.3
  *
  * OneString is a multi-sized, Unicode-compatible replacement
  * for std::string. OneString contains all the
  * basic functions found in std::string. The size of the
  * the OneString is doubled whenever the current size is maxed out.
  * To handle Unicode, each OneString is made of OneChars,
  * which are enhanced characters.
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

#ifndef PAWLIB_ONESTRING_HPP
#define PAWLIB_ONESTRING_HPP

#include <cstring>
#include <iomanip>
#include <iostream>

#include "pawlib/iochannel.hpp"
#include "pawlib/onechar.hpp"

namespace pawlib
{
     /* The purpose of OneString is to provide the functionality of std::string
      * but with better allocation of memory along with increased support for Unicode
      * characters. OneString works just like std::string only when the max size of the
      * current string is hit, the size is automatically doubled. The size starts with 4
      * and is then immediately increased to 8. Each OneString class contains a master
      * array of OneChars.*/

    class OneString
    {
        public:

        /*******************************************
        * Constructors + Destructor
        *******************************************/

        /**Default Constructor*/
        OneString();

        /**Create a OneString from const char*
        * Note: Double quotes default to const char*
        * \param the const char* to be converted to OneString
        * \return a OneString representation of str.
        *         All Unicode will be parsed appropriately. */
        OneString(const char* str);

        /**Create a OneString from std::string
        * Note: Double quotes default to const char*
        * \param the string to be converted to OneString
        * \return a OneString representation of str.
        *         All Unicode will be parsed appropriately. */
        OneString(const std::string& str);

        /**Create a OneString from another OneString
        * \param the OneString to be copied
        * \return a OneString representation of str.
        *         All Unicode will be parsed appropriately.*/
        OneString(const OneString& str);

        /**Create a OneString from a char
         *  \param the char to be added
         *  \return a OneString containing that char */
        OneString(char ch);

         /**Create a OneString from a char
         *  \param the OneChar to be added
         *  \return a OneString containing that OneChar */
        OneString(const OneChar& ch);

        /**Destructor*/
        ~OneString();

        /*******************************************
        * Helpers
        *******************************************/

        /**Helper function for operator= that must be declared in derived
             * classes.
             * \param the const char* to be returned as a OneString
             * \return the initialized OneString */
        OneString& assignHelper(const char* str);

        /**Parses char* into OneString based on size
             * Used primarily for Unicode Characters within OneString(const char*)
             * \param the const char* to be parsed
             * \param an int to represent the index to parse the char* at
             * \param an int to represent the number of bytes in the char* */
        void parseChar(const char* str, int index, int bytes);

        /**Parses char* into OneString based on size
             * Used primarily for Unicode Characters within OneString(const std::string*)
             * \param the const string to be parsed
             * \param an int to represent the index to parse the string at
             * \param an int to represent the number of bytes in the string */
        void parseChar(const std::string& str, int index, int bytes);

        /**Handles resizing the array
         * when max_size is reached
         * \param
         * \returns */
        void doubleSize();

        /*******************************************
        * Access
        *******************************************/

        /**Gets the OneChar at a given position
         * \param the index of the OneChar to return
         * \return cooresponding OneChar */
        OneChar at(int pos) const;

        /**Checks to see if a OneString
         * contains any OneChars
         * \param
         * \returns true/false depending on if the OneString
         *          contains OneChars */
        bool empty() const;

        /**Gets the current max_size of
         * the OneString. Used primarily internally
         * for resizing purposes.
         * \param
         * \returns the size of the OneString */
        int max_size() const;

        /**Gets the current number of
         * elements in the OneString
         * \param
         * \return the number of elements */
        int length() const;

        /*******************************************
        * Adding + Inserting
        ********************************************/

        /**Adds the cooresponding type to
         * the end of the OneString
         * in the form of a OneChar.
         * \param the characters to be added to the OneString
         * \returns */
        void append(const OneString& ostr);
        void append(char ochar);
        void append(const char* ostr);
        void append(const std::string& ostr);
        void append(const OneChar& ochar);

        /**Inserts a series of characters
         * Into a OneString at a given position
         * \param the position to be added
         * \param the characters to be added
         * \returns */
        void insert(int pos, const OneString& ostr);
        void insert(int pos, std::string ostr);
        void insert(int pos, char* ostr);
        void insert(int pos, char ochar);
        void insert(int pos, OneChar* ochar);
        void insert(int pos, OneChar& ochar);

        /*An alias for append, adds characters
        * to the end of a OneString
        * \param the characters to be added
        * \returns */
        void push_back(const OneString& ostr);
        void push_back(char ochar);
        void push_back(const char* ostr);
        void push_back(const std::string ostr);
        void push_back(const OneChar& ochar);

        /*******************************************
        * Removing
        ********************************************/

        /**Clears a OneString and
         * Reallocates it back to BASE_SIZE
         * \param
         * \returns */
        void clear();

        /**Removes the last element
         * in a OneString
         * \param
         * \returns */
        void pop_back();

        /*******************************************
        * Comparison
        ********************************************/

        /**Compares the OneString to another
         * character data type
         * \param the characters to compare to
         * \returns whether or not they are equivalent */
        bool equals(const OneString& ostr) const;
        bool equals(std::string ostr) const;
        bool equals(const char* ostr) const;

        /**Helper functions for < and > operators
         * Parse through a OneString or char*
         * to detirmine greater than or less than
         * \param the OneString or char* to compare
         * \return whether or not the OneString is
         *         less than or equal to the item compared*/
        bool lessThanStr(const OneString& ostr);
        bool lessThanCharP(const char* ostr);

        /*******************************************
        * Other
        ********************************************/

        /**Swaps one OneString with another
         * \param the OneString to swithc with
         * \return */
        void swap(OneString& str);

        /**Creates a smaller string out of
         * a series of OneChars in the existing OneString
         * \param the position to begin the string to be created
         * \param the length of the string to be created
         * \return the created string */
        OneString substr(int pos, int sublen);

        /*******************************************
        * Operators
        ********************************************/

        /**Retrieve OneChar from OneString
         * This takes care of the "setting" part of the index operator
         * \param the desired position within in the OneString
         * \return returns the OneChar located at pos */
        OneChar& operator[](int pos) const;

        /**Assignment operators
         * Assigns the OneString to the given
         * parameter. All unicode will be parsed appropriately
         * \param the data type with characters
         *        to be copied to a OneString
         * \return the OneString containing those characters*/
        OneString& operator=(std::string str);
        OneString& operator=(const char* str);
        OneString& operator=(const OneChar& str);
        OneString& operator=(OneChar* ch);
        OneString& operator=(char ch);
        OneString& operator=(OneString& ostr);

        /**Compares the OneString to another
         * text data type to check for equivalence
         * \param the text object to compare to
         * \return whether or not they are equivalent*/
        bool operator==(const OneString& ostr);
        bool operator==(const char* ostr);
        bool operator==(std::string ostr);

        /**Checks to see if the OneString is
         * less than the cooresponding text data object
         * \param the text object to compare to
         * \return whether or not the OneString is less than*/
        bool operator<(const char* ostr2);
        bool operator<(std::string ostr2);
        bool operator<(const OneString& ostr2);

        /**Checks to see if the OneString is
         * less or equal to the cooresponding text data object
         * \param the text object to compare to
         * \return whether or not the OneString is less than or equal*/
        bool operator<=(const OneString& ostr2);
        bool operator<=(const char* ostr2);
        bool operator<=(std::string ostr2);

        /**Checks to see if the OneString is
         * greater than the cooresponding text data object
         * \param the text object to compare to
         * \return whether or not the OneString is greater than*/
        bool operator>(const OneString& ostr2);
        bool operator>(const char* ostr2);
        bool operator>(std::string ostr2);

        /**Checks to see if the OneString is
         * greater or equal to  the cooresponding text data object
         * \param the text object to compare to
         * \return whether or not the OneString is greater than or equal*/
        bool operator>=(const OneString& ostr2);
        bool operator>=(const char* ostr2);
        bool operator>=(std::string ostr2);

        /**Adds the cooresponding type to
         * the end of the OneString
         * in the form of a OneChar.
         * \param the characters to be added to the OneString
         * \returns */
        void operator+=(const OneString& ostr2);
        void operator+=(const char* ostr2);
        void operator+=(std::string ostr2);
        void operator+=(char ochar);
        void operator+=(const OneChar& ochar);

        /*******************************************
        * Friends
        *******************************************/

        /*friend std::istream& operator>>(std::istream& in, OneString& ostr)
        {
            ostr.clear();
            std::string temp;
            std::getline(in, temp);

            int counter = 0;
            while (temp[counter] != '\0')
            {
                counter++;
            }

            ostr.resize(counter);

            ostr = temp;

            return in;
        };*/

        /**Operator to output a OneString
        * \param the ostream to output on
        * \param the OneString to output
        * \return outputs the OneString as a cohesive string */
        friend std::ostream& operator<<(std::ostream& os, const OneString& ostr)
        {
            for(int i = 0; i < ostr.length(); ++i)
            {
                os << ostr.masterArray[i];
            }
            return os;
        };

        private:
        const int BASE_SIZE = 4; // the size the OneString is initialized at
        int MAX_SIZE;   // the current size of the array
        int currElements = 0; // the number of elements in the array
        OneChar* masterArray; // the array of OneChars
    };
}
#endif // PAWLIB_ONESTRING_HPP
