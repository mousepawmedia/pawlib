/** Standard Utilities [PawLIB]
  * Version: 1.0
  *
  * Common utility functions used by the rest of PawLIB.
  *
  * Last Updated: 5 August 2016
  * Authors: Jason C. McDonald, Scott Taylor
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Games.
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

// Needed for stdsplit
#include <string>
#include <vector>

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
