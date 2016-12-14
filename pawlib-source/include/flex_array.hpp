/** Flex Array [PawLIB]
  * Version: 1.0
  *
  * A dynamic array with a low dynamic allocation demand.
  * Designed to take the place of 'std::vector'.
  *
  * Last Updated: 22 June, 2016 by Jonathan Theodore
  * Author: Michael Parkman
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

#ifndef FLEX_ARRAY_HPP_INCLUDED
#define FLEX_ARRAY_HPP_INCLUDED

#include "base_flex_array.hpp"
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

           explicit FlexArray(unsigned int numElements) : Base_FlexArr<type>(numElements) { }

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
                    if(this->currElements == this->max_size)
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
            type yank(unsigned int index)
            {
                //if there are no elements in the array
                if(this->currElements == 0)
                {
                    //assign temp to be the element at the passed in index
                    type temp = this->theArray[index];
                    //throw error and return null
                    ioc << cat_error << vrb_quiet << "Flex Array is empty" << io_end;
                    return temp;
                }
                //else if index is out of bounds
                else if(index > this->max_size)
                {
                    //assign temp to be the element at the passed in index
                    type temp = this->theArray[index];
                    //throw error and return null
                    ioc << cat_error << vrb_quiet << "Index out of bounds" << io_end;
                    return temp;
                }
                else
                {
                    //assign temp to be the element at the passed in index
                    type temp = this->theArray[index];
                    //shift all of the elements to the right of the index, to the left 1
                    //this effectivly deletes the element from the array
                    for(unsigned int i = index; i < this->currElements - 1; i++)
                    {
                        this->theArray[i] = this->theArray[i + 1];
                    }
                    //decrement the number of elements
                    this->currElements--;
                    //return the deleted element
                    return temp;
                }
            }

            //insert at the beginning
            bool shift(type newElement)
            {
                //if there are elements currently within the array
                if(this->currElements > 0)
                {
                    //if the array is currently maxed out
                    if(this->currElements == this->max_size)
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
                    //ioc << cat_error << vrb_quiet << "Flex Array is empty" << io_end;
                    throw std::out_of_range("Flex Array is empty.");
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
