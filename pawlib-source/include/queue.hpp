/** Queue [PawLIB]
  * Version: 1.0
  *
  * Allows managed, custom output to any console or terminal.
  * See WHAT IS IOCHANNEL? below.
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

#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

#include "base_flex_array.hpp"
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <class type>
    class Queue : public Base_FlexArr<type>
    {
        public:
            Queue() : Base_FlexArr<type>(){ }
            // cppcheck-suppress noExplicitConstructor
            Queue(int numElements) : Base_FlexArr<type>(numElements){ }

            //adds the passed in element to the queue
            void add(type newElement)
            {
                this->push_back(newElement);
            }

            //returns the value in the first index of the queue
            type peek()
            {
                return this->at(0);
            }

            //removes and returns the first element in the queue
            type poll()
            {
                //if there is an element that can be removed
                if(this->currElements > 0)
                {
                    //set temp to be the first element in the queue
                    type temp = this->theArray[0];
                    //shift all elements to the left 1 effectively deleting the element
                    for(int i = 0; i < this->currElements - 1; i++)
                    {
                        this->theArray[i] = this->theArray[i + 1];
                    }
                    //decrement the number of elements
                    this->currElements--;
                    //return the deleted element
                    return temp;
                }
                //if the queue is empty
                else
                {
                    ioc << cat_error << vrb_quiet << "The queue is empty" << io_end;
                    return nullptr;
                }
            }
    };
}

#endif // QUEUE_HPP_INCLUDED
