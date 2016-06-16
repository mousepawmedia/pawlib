/** Standard Utilities [PawLIB]
  * Version: 1.0
  *
  * Common utility functions used by the rest of PawLIB.
  *
  * Last Updated: 8 February 2016
  * Authors: Jason C. McDonald, Scott Taylor
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


#ifndef STDUTILS_H
#define STDUTILS_H

#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <limits>

//TODO: Replace with pawlib::string!
#include <string>
//NOTE: Leave this commented out until you are on g++ 5.3 or higher.
using std::isinf;
using std::isnan;
namespace pawlib
{
    ////const double PRECISION = 0.00000000000001;
    ////const int MAX_NUMBER_STRING_SIZE = 32;

    class stdutils
    {
        public:
            stdutils();

            /** Reverse a C-string. Algorithm from
            * http://stackoverflow.com/a/784567/472647
            * \param the C-string to reverse.
            * \param the reversed C-string
            */
            static char* strrev(char*);
            //TODO: Move this to pawlib::string!

            /**Count the number of digits/characters in an integer. Does not
             * count the null terminator.
             * Based on http://stackoverflow.com/a/1489873/472647
             * \param the number to count the digits in
             * \param the base, default 10
             * \param whether to count the symbols (ignored if unsigned)
             * \return the number of digits in the integer*/
            template <typename T>
            static int intlen(T, int, bool=false);

            /**Count the maximum (safest) estimated number of digits/characters
             * in a float/double. Does not count null terminator. WARNING: This
             * is designed to strategically overcount, to prevent fatal array size
             * errors. This is necessary, since floats are unpredictable by
             * nature.
             * http://stackoverflow.com/a/1489873/472647
             * \param the number to count the characters in
             * \param the precision (default 14)
             * \param whether to count the symbols
             * \return the number of digits in the float*/
            template <typename T>
            static int floatlen(T, int=14, int=1, bool=true);

            /**Convert an integer to a C-string.
             * \param the C-string to write to
             * \param the integer to convert
             * \param the base to convert in, default 10.
             * \param the length of the C-string, not counting the null
             * terminator. If 0 or omitted, this will be automatically
             * calculated.
             * \param whether to use capital letters for base > 10*/
            template <typename T>
            static void itoa(char*, T, int=10, int=0, bool=false);

            /**Convert a byte to a C-string.
             * \param the C-string to write to
             * \param the unsigned integer containing the byte
             * \param the length of the C-string, not counting the null
             * terminator. If 0 or omitted, this will be automatically
             * calculated.
             * \param whether to use capital letters for base > 10
             * \param whether this is interpreting a byte (use leading 0)*/
            static void uitoa(char*, unsigned int, int=10, int=0, bool=false, bool=false);

            /**Convert an unsigned long integer to a C-string.
             * \param the C-string to write to
             * \param the unsigned integer to convert
             * \param the base to convert in, default 10.
             * \param the length of the C-string, not counting the null
             * terminator. If 0 or omitted, this will be automatically
             * calculated.
             * \param whether to use capital letters for base > 10*/
            static void btoa(char*, unsigned int, int=0, bool=false);

            /**Convert a floating point number to a C-string.
             * \param the C-string to write to
             * \param the number to convert
             * \param the precision, as the number of significands (an integer)
             * \param whether to use scientific notation. 0=none, 1=automatic,
             * 2=force scientific notation.*/
            template <typename T>
            static void ftoa(char*, T, int=14, int=1);

            /**Convert an unsigned pointer integer to a Cstring.
             * Does not presently export the flag value, just the
             * memory address.
             * \param the C-string to write to
             * \param the pointer integer to convert
             * \param whether to use capital letters for base > 10*/
            static void ptrtoa(char*, uintptr_t, bool=false);

            /**Convert an int to a std::string.
             * \param the integer to convert
             * \param the base to convert
             * \param whether to use capital letters for base > 10
             * \return the string representing the integer.*/
            static std::string itos(int, int=10, bool=false);

            /**Convert a double to a std::string.
             * \param the integer to convert
             * \param the base to convert
             * \return the string representing the integer.*/
            static std::string dtos(double, int=14, int=1);

            /**Convert an unsigned pointer integer to a std::string.
             * \param the pointer integer to convert
             * \param whether to use capital letters for base > 10
             * \return the string representing the pointer.*/
            //static std::string ptrtos(uintptr_t);
            static std::string ptrtos(uintptr_t, bool=false);

            static void memdump(char*, const void*, unsigned int, bool=false, char=0);

            ~stdutils();
        protected:
        private:
    };
}

#endif // STDUTILS_H
