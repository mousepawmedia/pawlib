/** Binary Converters [PawLIB]
  * Version: 1.0
  *
  * Data-to-binary and binary-to-data converters.
  *
  * Last Updated: 10 April 2016
  * Author: Michael Parkman
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

#ifndef BINCONV_HPP_INCLUDED
#define BINCONV_HPP_INCLUDED

#include <string>
#include <sstream>
#include <math.h>
#include <vector>

using std::vector;
using std::string;
using std::stringstream;

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
#endif // BINCONV_HPP_INCLUDED
