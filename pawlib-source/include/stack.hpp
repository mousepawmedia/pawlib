/** Stack [PawLIB]
  * Version: 1.0
  *
  * A stack with a low dynamic allocation demand.
  *
  * Last Updated: 8 March 2016
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

#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "base_flex_array.hpp"
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <class type>
    class Stack : public Base_FlexArr<type>
    {
        public:
            Stack() : Base_FlexArr<type>() { }
            // cppcheck-suppress noExplicitConstructor
            Stack(int numElements) : Base_FlexArr<type>(numElements) { }

            //removes the last element in the stack
            type pop()
            {
                //if the stack is empty
                if(this->currElements == 0)
                {
                    ioc << cat_error << vrb_quiet << "The stack is empty" << io_end;
                    return nullptr;
                }
                else
                {
                    //return the last element in the stack and decrement the number of elements in the stack. This effectively deletes the element from the array.
                    return this->theArray[--this->currElements];
                }
            }

            //adds the passed in element to the back of the stack
            void push(type newElement)
            {
                this->push_back(newElement);
            }

        private:
    };
}

#endif // STACK_HPP_INCLUDED
