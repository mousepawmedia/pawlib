/** Binary Converters [PawLIB]
  * Version: 0.1 (Experimental)
  *
  * Data-to-binary and binary-to-data converters.
  *
  * Author(s): Michael Parkman
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

#ifndef BINCONV_HPP_INCLUDED
#define BINCONV_HPP_INCLUDED

#include <math.h>
#include <sstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::stringstream;

namespace pawlib
{
    class binconv
    {
        public:
            ///TODO: Write methods for boolean & ternary. Comment toFloat and toDouble
            ///THEN Write wrapper methods for boolean & ternary.
            ///Then write a generic wrapper method just in case. Pass in varName, data, and "INTEGER" or "BOOLEAN" etc
            static string toBinary(bool b);
            static bool toBool(string);
            static int toTernary(string);
            static string toBinary(int, int numBits = 32);
            static int toInt(string);
            static string toBinary(long, int numBits = 32);
            static long toLong(string);
            static string toBinary(float);
            static float toFloat(string);
            static string toBinary(double);
            static double toDouble(string);
            static string toBinary(char);
            static char toChar(string);
            static string toBinary(string);
            static string binaryToString(string);

            //In the header file because I couldn't make it work in the cpp with templates
            //converts a vector of type T into binary
            template<class theType, class Alloc>
            static string toBinary(vector<theType, Alloc> vec)
            {
                //the stream used for converting the binary values to strings
                stringstream ss;
                for(int i = 0; i < vec.size(); i++)
                {
                    //call the specific types data to binary
                    //then adds it to the end of the current string
                    ss << toBinary(vec.at(i));
                    //Seperate each of the elements with the control code ^? (Unit Seperator)
                    //needed for strings and maybe other vectors?
                    ss << toBinary("^?");
                }
                //returns the whole string
                return ss.str();
            }
    };
}
#endif // BINCONV_HPP_INCLUDED
