/** FlexArray [PawLIB]
  * Version: 1.1
  *
  * A dynamic array with a low dynamic allocation demand.
  * Designed to take the place of 'std::vector'.
  *
  * Author(s): Jason C. McDonald, Michael Parkman, Jonathan Theodore
  */

/* LICENSE
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

#ifndef PAWLIB_FLEXARRAY_HPP
#define PAWLIB_FLEXARRAY_HPP

#include <stdio.h>
#include <stdexcept>

#include "pawlib/base_flex_array.hpp"
#include "pawlib/constants.hpp"
#include "pawlib/iochannel.hpp"

using pawlib::iochannel;

namespace pawlib
{
    template <typename type, bool factor_double = true>
    class FlexArray : public Base_FlexArr<type, factor_double>
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
            FlexArray(size_t numElements)
                :Base_FlexArr<type>(numElements)
                {}

            /** Insert an element into the FlexArray at the given index.
             * Unsigned to prevent negative indices.
             * \param the element to insert
             * \param the index to insert the element at.
             * \return true if insert successful, else false.
             */
            bool insert(type newElement, size_t index)
            {
                if(!this->validateIndex(index))
                {
                    ioc << IOCat::error << IOVrb::quiet
                        << "FlexArray: insert() failed. " << index
                        << " out of bounds [0 - " << this->_elements - 1
                        << "]." << IOCtrl::endl;
                    return false;
                }
                return this->insertAtIndex(newElement, index);
            }

            type& peek_front()
            {
                // If the array is empty...
                if(this->isEmpty())
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot peek_front() from empty FlexArray.");
                }
                return this->getFromHead();
            }

            /** Returns the last element in the FlexArray without modifying
              * the data structure.
              * \return the last element in the FlexArray.
              */
            type peek()
            {
                // If the array is empty...
                if(this->isEmpty())
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot peek() from empty FlexArray.");
                }
                return this->getFromTail();
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

            /** Remove and return the element at the given index.
              * \param the index to act on.
              * \return the element from the given index.
              */
            type yank(size_t index)
            {
                // If there are no elements in the array...
                if(this->isEmpty())
                {
                    throw std::out_of_range("FlexArray: yank() failed. The FlexArray is empty.");
                    return false;
                }
                // Else if the given index is out of bounds.
                else if(!this->validateIndex(index, false))
                {
                    throw std::out_of_range("FlexArray: yank() failed. Index out of bounds.");
                    return false;
                }

                // Store the element at index, to be returned shortly.
                type temp = this->rawAt(index);
                // Delete the element.
                this->removeAtIndex(index);
                // Return the deleted element.
                return temp;
            }

            /** Insert an element at the beginning of the FlexArray.
              * Just an alias for shift()
              * \param the element to insert.
              * \return true if successful, else false.
              */
            bool push_front(type newElement)
            {
                return shift(newElement);
            }

            /** Insert an element at the beginning of the FlexArray.
              * \param the element to insert.
              * \return true if successful, else false.
              */
            bool shift(type newElement)
            {
                /* We'll use the deque head insertion here.
                 * Use that function's error messages.
                 */
                return this->insertAtHead(newElement, true);
            }

            /** Returns and removes the first element in the FlexArray.
              * \return the first element, now removed.
              */
            type unshift()
            {
                // If the array is empty...
                if(this->isEmpty())
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot unshift() from empty FlexArray.");
                }

                // Store the first element, to be returned later.
                type temp = this->rawAt(0);
                // Delete the front value.
                this->removeAtHead();
                // Return the element we just deleted.
                return temp;
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
                // If the array is empty...
                if(this->isEmpty())
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot pop() from empty FlexArray.");
                }

                // Store the last element, to be returned later.
                type temp = this->rawAt(this->_elements-1);
                // Delete the back value.
                this->removeAtTail();
                // Return the element we just deleted.
                return temp;
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
                /* We'll use the deque tail insert here.
                 * Use that function's error messages.
                 */
                return this->insertAtTail(newElement, true);
            }
    };
}
#endif // PAWLIB_FLEXARRAY_HPP
