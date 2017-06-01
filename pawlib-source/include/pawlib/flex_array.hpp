/** FlexArray [PawLIB]
  * Version: 1.0
  *
  * A dynamic array with a low dynamic allocation demand.
  * Designed to take the place of 'std::vector'.
  *
  * Author(s): Michael Parkman, Jonathan Theodore, Jason C. McDonald
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
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef FLEX_ARRAY_HPP_INCLUDED
#define FLEX_ARRAY_HPP_INCLUDED

#include <stdio.h>
#include <stdexcept>

#include "pawlib/base_flex_array.hpp"
#include "pawlib/constants.hpp"
#include "pawlib/iochannel.hpp"

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <typename type>
    class FlexArray : public Base_FlexArr<type>
    {
        public:
            /** Create a new FlexArray with the default capacity.
              */
            FlexArray()
                :Base_FlexArr<type>()
                {}

            /** Create a new FlexArray with the specified minimum capacity.
              * \param the minimum number of elements that the FlexArray can contain.
              */
            // cppcheck-suppress noExplicitConstructor
            FlexArray(uint32_t numElements)
                :Base_FlexArr<type>(numElements)
                {}

            /** Insert an element into the FlexArray at the given index.
             * Unsigned to prevent negative indices.
             * \param the element to insert
             * \param the index to insert the element at.
             * \return true if insert successful, else false.
             */
            bool insert(type newElement, uint32_t index)
            {
                /* If the index is greater than the number of elements
                 * in the array currently. */
                if(index > 0 && index > this-> currElements - 1)
                {
                    // Throw a non-fatal error. Numbers are 0-based.
                    ioc << cat_error << vrb_quiet << "Index " << index
                       << " out of bounds [0 - " << this->currElements - 1
                       << "]." << io_end;
                    // Report failure.
                    return false;
                }
                // Otherwise, the index is in bounds...
                else
                {
                    // If the number of elements is equal to the capacity.
                    if(this->full())
                    {
                        // Attempt to double the capacity. If it fails...
                        if(!this->double_size())
                        {
                            // Report failure.
                            return false;
                        }
                    }

                    // If there are elements in the FlexArray...
                    if(!this->empty())
                    {
                        /* Every element to from the index to the right should
                         * be shifted right one position. */
                        this->mem_shift(index, 1);

                        // Place the new element at the specified index.
                        this->theArray[index] = newElement;
                    }

                    // Increment the number of elements.
                    ++(this->currElements);

                    // Report success.
                    return true;
                }
            }

            /** Remove and return the element at the given index.
              * \param the index to act on.
              * \return the element from the given index.
              */
            type yank(uint32_t index)
            {
                // If there are no elements in the array...
                if(this->empty())
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot yank from empty FlexArray.");
                }
                // Else if the given index is out of bounds.
                else if(index > this->capacity)
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot yank from out of range index.");
                }
                else
                {
                    // Store the element at index, to be returned shortly.
                    type temp = this->theArray[index];

                    /* All of the elements to the right of the index should be
                     * shifted left one position. This effectively deletes the
                     * element from the array.*/
                    this->mem_shift(index + 1, -1);

                    // Decrement the number of elements.
                    --(this->currElements);

                    // Return the deleted element.
                    return temp;
                }
            }

            /** Insert an element at the end of the FlexArray.
              * Just an alias for push()
              * \param the element to insert.
              * \return true if successful, else false.
              */
            bool push_front(type newElement)
            {
                return push(newElement);
            }

            /** Insert an element at the beginning of the FlexArray.
              * \param the element to insert.
              * \return true if successful, else false.
              */
            bool shift(type newElement)
            {
                // If there are elements currently within the array.
                if(!this->empty())
                {
                    // If the array is full...
                    if(this->full())
                    {
                        // Attempt to double the array's capacity. If it fails...
                        if(!this->double_size())
                        {
                            // Report failure.
                            return false;
                        }
                    }
                    // Shift all the elements to the right one position.
                    this->mem_shift(0, 1);
                }

                // Store the new element in the first position.
                this->theArray[0] = newElement;

                // Increment the number of elements.
                ++(this->currElements);

                // Report success.
                return true;
            }

            /** Returns the last element in the FlexArray without modifying
              * the data structure.
              * \return the last element in the FlexArray.
              */
            type peek()
            {
                // If there is at least one element in the array...
                if(!this->empty())
                {
                    // Return the last element.
                    return this->at(this->currElements - 1);
                }
                // Otherwise...
                else
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot peek from empty FlexArray.");
                }
            }
            /** Returns the last element in FlexArray without modifying
              * the data structure
              * Just an alias for peek.
              * \return the first element in the FlexArray.
              */
            type peek_back()
            {
              return peek();
            }

            /** Returns and removes the first element in the FlexArray.
              * \return the first element, now removed.
              */
            type unshift()
            {
                // If there is at least one element in the array...
                if(!this->empty())
                {
                    // Store the first element, to be returned later.
                    type temp = this->theArray[0];

                    /* Move all elements to the left one index. This
                     * effectively deletes the first element from the array.
                     * We perform a raw memory move for efficiency. */
                    this->mem_shift(1, -1);

                    // Decrement the number of elements.
                    --(this->currElements);

                    // Return the element we just deleted.
                    return temp;
                }
                // Else if there are no elements in the array...
                else
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot unshift from empty FlexArray.");
                }
            }

            /** Return and remove the last element in the FlexArray.
              * Just an alias for pop()
              * \return the last element, now removed.
              */
            type pop_back()
            {
                return pop();
            }

            /** Return and remove the last element in the FlexArray.
              * \return the last element, now removed.
              */
            type pop()
            {
                // If there are no elements...
                if(this->empty())
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot pop from empty FlexArray.");
                }
                // Else if there is at least one element...
                else
                {
                    /* Return the last element and decrement the
                     * number of elements. */
                    return this->theArray[--(this->currElements)];
                }
            }

            /** Add the specified element to the end of the FlexArray.
              * Just an alias for push()
              * \param the element to add.
              * \return true if successful, else false.
              */
            bool push_back(type newElement)
            {
                return push(newElement);
            }

            /** Add the specified element to the end of the FlexArray.
              * \param the element to add.
              * \return true if successful, else false.
              */
            bool push(type newElement)
            {
                // If the array is full...
                if(this->full())
                {
                    // Attempt to double the array's capacity. If it fails...
                    if(!this->double_size())
                    {
                        // Report failure.
                        return false;
                    }
                }

                /* Store the new element in the last position and
                 * increment the number of elements. */
                this->theArray[(this->currElements)++] = newElement;

                // Report success.
                return true;
            }
    };
}
#endif // FLEX_ARRAY_HPP_INCLUDED
