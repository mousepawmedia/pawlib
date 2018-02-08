/** FlexQueue [PawLIB]
  * Version: 1.0
  *
  * A Flex-based queue with a low dynamic allocation demand.
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
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#ifndef PAWLIB_FLEXQUEUE_HPP
#define PAWLIB_FLEXQUEUE_HPP

#include "pawlib/base_flex_array.hpp"
#include "pawlib/iochannel.hpp"

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <typename type>
    class FlexQueue : public Base_FlexArr<type>
    {
        public:
            /** Create a new FlexQueue with the default capacity.
              */
            FlexQueue()
                :Base_FlexArr<type>()
                {}

            /** Create a new FlexQueue with the specified minimum capacity.
              * \param the minimum number of elements that the FlexQueue can contain.
              */
            // cppcheck-suppress noExplicitConstructor
            FlexQueue(uint32_t numElements)
                :Base_FlexArr<type>(numElements)
                {}

            /** Adds the specified element to the FlexQueue.
             * This is just an alias for enqueue()
              * \param the element to enqueue
              * \return true if successful, else false.
             */
            bool push(type newElement)
            {
                return enqueue(newElement);
            }

            /** Adds the specified element to the FlexQueue.
             * This is just an alias for enqueue()
              * \param the element to enqueue
              * \return true if successful, else false.
             */
            bool push_back(type newElement)
            {
                return enqueue(newElement);
            }

            /** Adds the specified element to the FlexQueue.
              * \param the element to enqueue
              * \return true if successful, else false.
              */
            bool enqueue(type newElement)
            {
                // If the array is full...
                if(this->currElements == this->capacity)
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

            /** Returns the next (first) element in the FlexQueue without
              * modifying the data structure.
              * \return the next element in the FlexQueue.
              */
            type peek()
            {
                // If there is at least one element in the array...
                if(this->currElements > 0)
                {
                    // Return that element.
                    return this->at(0);
                }
                // Otherwise...
                else
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot peek from empty FlexArray.");
                }
            }

            /**Return and remove the next element in the FlexStack.
             * This is just an alias for dequeue()
             * \return the next (first) element, now removed.
             */
            type pop()
            {
                return dequeue();
            }

            /**Return and remove the next element in the FlexStack.
             * This is just an alias for dequeue()
             * \return the next (first) element, now removed.
             */
            type pop_front()
            {
                return dequeue();
            }

            /** Return and remove the next element in the FlexQueue.
              * \return the next (first) element, now removed.
              */
            type dequeue()
            {
                // If there is at least one element in the array...
                if(this->currElements > 0)
                {
                    // Store the first element, to be returned later.
                    type temp = this->theArray[0];

                    /* Shift all elements to the left one index. This
                     * effectively deletes the first element from the array. */
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
                    throw std::out_of_range("FlexQueue: Cannot pop from empty FlexQueue.");
                }
            }
    };
}

#endif // QUEUE_HPP_INCLUDED
