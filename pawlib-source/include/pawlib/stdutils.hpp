/** Standard Utilities [PawLIB]
  * Version: 1.0
  *
  * Common utility functions used by the rest of PawLIB.
  *
  * Author(s): Jason C. McDonald, Scott Taylor
  */

/* LICENSE (BSD-3-Clause)
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

#ifndef PAWLIB_STDUTILS_HPP
#define PAWLIB_STDUTILS_HPP

#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
// Needed for stdsplit
#include <string>

/* NOTE: Due to bug 19439, if we're using GCC, this only works on g++ 5.3 or higher.
 * https://sourceware.org/bugzilla/show_bug.cgi?id=19439
 */
#if defined(__clang__) || defined(__INTEL_COMPILER) || __GNUC__ > 5 || (__GNUC__ == 5 && (__GNUC_MINOR__ > 3 || (__GNUC_MINOR__ == 3 && __GNUC_PATCHLEVEL__ > 0)))
using std::isinf;
using std::isnan;
#endif // __GNUC__

////const double PRECISION = 0.00000000000001;
////const int MAX_NUMBER_STRING_SIZE = 32;

class stdutils
{
    public:
        stdutils();

        /** Efficiently split a std::string by tokens.
        * \param the string to split
        * \param the character or string to split by
        * \param the vector to store the tokens in
        */
        static void stdsplit(std::string, std::string, std::vector<std::string>&);

        /** Reverse a C-string. Algorithm from
        * http://stackoverflow.com/a/784567/472647
        * \param the C-string to reverse.
        * \param the reversed C-string
        */
        static char* strrev(char*);
        //TODO: Move this to onestring!

        template <typename T>
        static void arev(T* arr, size_t start, size_t end)
        {
            T tmp;
            while(start < end)
            {
                memcpy(&tmp, (arr + end), sizeof(T));
                memcpy((arr+end), (arr+start), sizeof(T));
                memcpy((arr+start), &tmp, sizeof(T));
                ++start;
                --end;
            }
        }

        /**Count the number of digits/characters in an integer. Does not
         * count the null terminator.
         * Based on http://stackoverflow.com/a/1489873/472647
         * \param the number to count the digits in
         * \param the base, default 10
         * \param whether to count the symbols (ignored if unsigned)
         * \return the number of digits in the integer*/
        template <typename T>
        static int intlen(T, int, bool=true);

        /**Count the maximum (safest) estimated number of digits/characters
         * in a float/double. Does not count null terminator. WARNING: This
         * is designed to strategically overcount, to prevent fatal array size
         * errors. This is necessary, since floats are unpredictable by
         * nature.
         * http://stackoverflow.com/a/1489873/472647
         * \param the number to count the characters in
         * \param the number of significands (default 14)
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
         * \param the byte (unsigned integer) to convert
         * \param the base to convert in, default 10.
         * \param the length of the C-string, not counting the null
         * terminator. If 0 or omitted, this will be automatically
         * calculated.
         * \param whether to use capital letters for base > 10*/
        static void btoa(char*, unsigned int, int=0, bool=false);

        /**Convert a floating point number to a C-string.
         * \param the C-string to write to
         * \param the number to convert
         * \param the number of significands (an integer)
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
        template <typename T>
        static std::string itos(T, int=10, bool=false);

        /**Convert a float to a std::string.
         * \param the float to convert
         * \param the number of significands (an integer)
         * \param whether to use scientific notation. 0=none, 1=automatic,
         * 2=force scientific notation.
         * \return the string representing the integer.*/
        template <typename T>
        static std::string ftos(T, int=14, int=1);

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

#endif // PAWLIB_STDUTILS_HPP
