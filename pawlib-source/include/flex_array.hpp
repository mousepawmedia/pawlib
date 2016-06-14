/** Flex Array [PawLIB]
  * Version: 1.0
  *
  * The a dynamic array with a low dynamic allocation demand.
  * Designed to take the place of 'std::vector'.
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

#ifndef FLEX_ARRAY_HPP_INCLUDED
#define FLEX_ARRAY_HPP_INCLUDED

#include "stack.hpp"
#include "queue.hpp"
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
    {
    template<class type>
    class FlexArray : public Base_FlexArr<type>
    {
        public:
            FlexArray() : Base_FlexArr<type>() { }
            // cppcheck-suppress noExplicitConstructor
            FlexArray(int numElements) : Base_FlexArr<type>(numElements) { }

            //insert an element into the flex_array at a given index. Unsigned to prevent negatives.
            bool insert(type newElement, unsigned int index)
            {
                //if the index is greater than the number of elements in the array currently
                if(index > 0 && index > this-> currElements - 1)
                {
                    //throw an index out of bounds exception
                    //prints current index
                    ioc << cat_error << vrb_quiet << "Index " << index
                       //prints elements minus one.
                       << " out of bounds [0 - " << this->currElements - 1
                       << "]." << io_end;
                       return false;
                }
                //otherwise the index is in bounds
                else
                {
                    //if the number of elements is equal to the number of avaiable slots
                    if(this->currElements == this->size)
                    {
                        //double the number of slots
                        this->double_size(&this->theArray);
                    }
                    if(this->currElements > 0)
                    { //shift every element to the right of the index, right 1 slot
                        for(unsigned int i = this->currElements - 1; i > index; i--)
                        {
                            this->theArray[i] = this->theArray[i - 1];
                        }
                    //assign the desired index the passed in value
                        this->theArray[index] = newElement;
                    }
                    //incrememnt the number of elements
                    this->currElements++;
                    return true;
                }
            }

            //remove the element at the given index
            type yank(int index)
            {
                //if there are no elements in the array
                if(this->currElements == 0)
                {
                    //throw error and return null
                    ioc << cat_error << vrb_quiet << "Flex Array is emptry" << io_end;
                    return nullptr;
                }
                //else if index is out of bounds
                else if(index < 0 || index > this->size)
                {
                    //throw error and return null
                    ioc << cat_error << vrb_quiet << "Index out of bounds" << io_end;
                    return nullptr;
                }
                else
                {
                    //assign temp to be the element at the passed in index
                    type temp = this->theArray[index];
                    //shift all of the elements to the right of the index, to the left 1
                    //this effectivly deletes the element from the array
                    for(int i = index; i < this->currElements - 1; i++)
                    {
                        this->theArray[i] = this->theArray[i + 1];
                    }
                    //decrement the number of elements
                    this->currElements--;
                    //return the deleted element
                    return temp;
                }
            }

            //insert in the beginning
            bool shift(type newElement)
            {
                //if there are elements currently within the array
                if(this->currElements > 0)
                {
                    //if the array is currently maxed out
                    if(this->currElements == this->size)
                    {
                        //double the size of the array
                        this->double_size(&this->theArray);
                    }
                    //shift all the elements to the right 1 index
                    for(int i = this->currElements - 1; i > 0; i--)
                    {
                        this->theArray[i] = this->theArray[i - 1];
                    }
                }
                //assign the first element to be the passed in element
                this->theArray[0] = newElement;
                //increment the nubmer of elements
                this->currElements++;
                return true;
            }

            //returns the first value in the array
            type peek()
            {
                return this->at(0);
            }

            //deletes the first element in the array
            type unshift()
            {
                //if there is at least 1 element in the array
                if(this->currElements > 0)
                {
                    //assign temp to be the first element in the array
                    type temp = this->theArray[0];
                    //shift all elements to the left 1 index. This effectively deletes the first element from the array
                    for(int i = 0; i < this->currElements - 1; i++)
                    {
                        this->theArray[i] = this->theArray[i + 1];
                    }
                    //decrement the number of elements
                    this->currElements--;
                    //return the deleted element value
                    return temp;
                }
                //if there are no elements in the array
                else
                {
                    //throw error and return null
                    ioc << cat_error << vrb_quiet << "Flex Array is empty" << io_end;
                    return nullptr;
                }
            }

            //remove the last element in the array
            type pop()
            {
                //if there are no elements
                if(this->currElements == 0)
                {
                    //throw error and return null
                    ioc << cat_error << vrb_quiet << "Flex Array is empty" << io_end;
                    return nullptr;
                }
                //if there is at least 1 element
                else
                {
                    //return the last element and decrement the number of elements
                    return this->theArray[--this->currElements];
                }
            }

            //push the passed in element to the back of the array
            bool push(type newElement)
            {
                return this->push_back(newElement);
            }
    };
}
#endif // FLEX_ARRAY_HPP_INCLUDED
