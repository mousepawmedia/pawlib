/** Base FlexArray [PawLIB]
  * Version: 1.0
  *
  * The base class for a dynamic array with a low dynamic allocation demand.
  * FlexArray, FlexQueue, and FlexStack all rely on these.
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

#ifndef PAWLIB_BASEFLEXARRAY_HPP
#define PAWLIB_BASEFLEXARRAY_HPP

#include <cstdint>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

#include "pawlib/iochannel.hpp"


using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <typename type>
    class Base_FlexArr
    {
        public:
            /** Create a new base flex array, with the default starting size.
              */
            Base_FlexArr()
            :theArray(nullptr), head(0), resizable(true), currElements(0), capacity(4)
            {
                /* The call to resize() will sets the capacity to 8
                 * on initiation. */

                // Allocate the structure.
                resize();
            }

            /** Create a new base flex array with room for the specified number
              * of elements.
              * \param the minimum number of elements the structure can hold.
              */
            // cppcheck-suppress noExplicitConstructor
            Base_FlexArr(uint32_t numElements)
            :theArray(nullptr), head(0), resizable(true), currElements(0)
            {
                /* Set the size to be the power of 2 just below the entered
                 * number. resize() will initiate with enough
                 * room in array. */
                capacity = pow(2, floor(log2(numElements)));

                // Allocate the structure.
                resize();
            }

            /** Destructor. */
            ~Base_FlexArr()
            {
                if(theArray != nullptr)
                {
                    delete[] theArray;
                }
            }

            /** Access an element at a given index using the [] operator.
              * For example, "theArray[5]".
              */
            type operator[](uint32_t index)
            {
                return at(index);
            }

            /** Access an element at the given index.
              * \param the index to access.
              * \return the element at the given index.
              */
            type at(uint32_t index)
            {
                if(index > currElements - 1)
                {
                    throw std::out_of_range("BaseFlexArray: Index out of range!");
                }

                return theArray[to_internal_index(index)];
            }

            /** Check if the data structure is empty.
              * \return true if empty, else false
              */
            bool empty()
            {
                return (currElements == 0);
            }

            /** Check to see if the data structure is full.
              * \return true is full, else false
              */
            bool full()
            {
                  return (capacity == currElements);
            }

            /** Erase the elements in the specified range.
              * \param the first index in the range to remove
              * \param the last index in the range to remove
              */
            bool erase(uint32_t first, uint32_t last=0)
            {
                /* If no last index was specified, prepare to delete only
                 * the element 'first'. */
                if(last == 0)
                {
                    last = first;
                }

                // If the range [first-last] is valid...
                if(last >= first && last < currElements)
                {
                    uint32_t removeCount = (last+1) - first;

                    //...and if we'll have leftovers after `last`
                    if(last < currElements - 1)
                    {
                        // Shift the leftovers backwards into place.
                        mem_shift(last+1, -removeCount);
                    }
                    // Recalculate the elements we have.
                    currElements -= removeCount;
                    return true;
                }
                else
                {
                    // Throw non-fatal error.
                    ioc << cat_error << "BaseFlexArray Erase: Invalid range ("
                        << first << " - " << last << "). Took no action."
                        << io_end;
                    return false;
                }
            }

            /** Get the current number of elements in the structure.
              * \return the number of elements
              */
            uint32_t getSize()
            {
                return currElements;
            }

            /** Get the maximum number of elements the structure can hold
              * without resizing.
              * \return the maximum number of elements
              */
            uint32_t getArraySize()
            {
                return capacity;
            }

        protected:
            /// The pointer to the actual structure in memory.
            type* theArray;

            /// The first index, as this may drift.
            uint32_t head;

            /// Whether the structure can be resize.
            bool resizable;

            /// The current number of elements in the structure.
            uint32_t currElements;

            /** The maximum number of elements (capacity) that can be contained
              * in the structure without resizing. (1-based) */
            uint32_t capacity;

            /** Get the internal array index.
              * \param the (external) index to access
              * \return the (internal) index
              */
            uint32_t to_internal_index(uint32_t index)
            {
                /* Get the internal index, by adding the external index
                 * to the head index, and then accounting for the
                 * circular buffer. */
                index = index + this->head;
                if(index >= this->capacity)
                {
                    index -= this->capacity;
                }
                return index;
            }

            /** Insert at head.
              * \return true if successful, else false
              */
            bool insert_head(type value)
            {
                if(this->currElements >= this->capacity)
                {
                    resize();
                }

                if(this->head == 0)
                {
                    this->head = this->capacity;
                }
                else
                {
                    --this->head;
                }

                this->theArray[this->head] = value;
            }

            bool insert_tail(type value)
            {
                if(this->currElements >= this->capacity)
                {
                    resize();
                }

                this->theArray[to_internal_index(this->currElements++)] = value;
            }

            bool insert(uint32_t index, type value)
            {
                if(this->currElements >= this->capacity)
                {
                    resize();
                }

                this->theArray[to_internal_index(index)] = value;
                ++this->currElements;
            }

            bool remove_head()
            {
                ++this->head;
                if (this->head >= this->capacity)
                {
                    this->head -= this->capacity;
                }
                --this->currElements;
            }

            bool remove_tail()
            {
                --this->currElements;
            }

            bool remove(uint32_t index)
            {
                mem_shift(index, -1);
                --this->currElements;
            }

            /** Double the capacity of the structure.
              * \return true if it was able to double capacity, else false.
              */
            bool resize()
            {
                // If we're not allowed to resize...
                if(!resizable)
                {
                    // Report failure.
                    return false;
                }

                //check to see if maximum size is being approached
                if(capacity >= UINT32_MAX/2)
                {
                  //set it to limit defined by UINT32_MAX
                  capacity = UINT32_MAX;
                  //set it so that array can no longer be doubled in size
                  resizable = false;
                }
                else
                {
                    // Double the maximum size (capacity).
                    capacity *= 2;
                }
                /* Create the new structure with the new capacity.*/
                type* tempArray = new type[capacity];

                // If there was an error allocating the new array...
                if(tempArray == nullptr)
                {
                    // Report failure.
                    return false;
                }

                // If an old array exists...
                if(this->theArray != nullptr)
                {
                    // Transfer all of the elements over.
                    /*memmove(
                        tempArray,
                        this->theArray,
                        sizeof(type) * this->currElements
                    );*/

                    /* Since this is a circular buffer, we have to move things
                     * so it has room for expansion. The fastest way to do this
                     * is by storing the head element back at index 0.
                     * To do this, we'll move everything in two parts:
                     * (1) head to end of space, and (2) 0 to head-1.
                     */
                    uint32_t step1 = this->capacity - this->head;
                    uint32_t step2 = this->head;
                    memmove(
                        tempArray,
                        this->theArray,
                        sizeof(type) * step1
                    );
                    /* NOTE: Would the code be faster if this move was in
                     * an "if step2 == 0" conditional?
                     */
                    memmove(
                        tempArray,
                        this->theArray + step2,
                        sizeof(type) * step2
                    );

                    // Delete the old structure.
                    delete[] theArray;
                    this->theArray = nullptr;
                }

                // Store the new structure.
                this->theArray = tempArray;

                // Reset the head.
                this->head = 0;

                // Report success.
                return true;
            }

            /** Shift all elements from the given position the given direction
              * and distance. This is intended for internal use only, and does
              * not check for memory errors.
              * \param the index to shift elements from
              * \param the direction and distance to shift the elements in.
              */
            void mem_shift(uint32_t fromIndex, int8_t direction)
            {
                /* Check if the index was valid given the number of elements
                 * we're actually storing. (We have to offset fromIndex so
                 * we do our math in 1-indexing).
                 */
                if(fromIndex + 1 > this->currElements)
                {
                    return;
                }

                // Switch fromIndex to internal indexing
                fromIndex = to_internal_index(fromIndex);

                // If the head is at 0, we can move in one step.
                if(this->head == 0)
                {
                    memmove(
                        // Move TO the given index.
                        this->theArray + (fromIndex + direction),
                        // Move FROM the given index, plus one.
                        this->theArray + fromIndex,
                        // Total move size is the number of elements to be moved,
                        // times element size. The number of elements we move
                        // is calculated from the 1-based total number of elements.
                        sizeof(type) * ((this->currElements) - (fromIndex))
                    );
                }
                else if(direction > 0)
                {
                    // Shift in a POSITIVE direction
                    // Slide the section after the wraparound.
                    memmove(
                        this->theArray + direction,
                        this->theArray,
                        sizeof(type) * (this->currElements - (this->capacity - this->head))
                    );
                    // Move the section that wraps around.
                    memmove(
                        this->theArray,
                        this->theArray + this->capacity - direction,
                        sizeof(type) * abs(direction)
                    );
                    // Move the section before the wraparound.
                    memmove(
                        this->theArray + fromIndex + direction,
                        this->theArray + fromIndex,
                        /* Move all the elements before the wraparound,
                         * except the ones we already moved.*/
                        sizeof(type) * (this->capacity - this->head - abs(direction))
                    );
                }
                else if(direction < 0)
                {
                    /* NEGATIVE direction
                     * PART 1: fromIndex..(capacity-1), shift by direction
                     * PART 2: 0, move to (capacity-1)
                     * PART 3: 1..tail, shift by direction
                     */

                    // Shift in a NEGATIVE direction
                    // Move the section before the wraparound.
                    memmove(
                        this->theArray + fromIndex + direction,
                        this->theArray + fromIndex,
                        sizeof(type) * (this->capacity - this->head)
                    );
                    // Move the section that wraps around.
                    memmove(
                        this->theArray + this->capacity - direction,
                        this->theArray,
                        sizeof(type) * abs(direction)
                    );
                    // Move the section after the wraparound.
                    memmove(
                        this->theArray,
                        this->theArray + direction,
                        /* Move all the elements after the wraparound,
                         * except the ones we already moved. */
                        sizeof(type) * (this->currElements - (this->capacity - this->head) - abs(direction))
                    );
                }
            }

            /** Add the given element to the back of the structure.
              * \param the element to add to the structure.
              * \return true if successful, else false.
              */
            bool push_back(type newElement)
            {
                /* If we only have room to push THIS element before running
                 * out of room in the structure...*/
                if(currElements > capacity - 1)
                {
                    /* Attempt to double the structure's capacity.
                     * If it fails...*/
                    if(!resize())
                    {
                        /* Out of room and could not resize.
                         * Throw a non-fatal error. */
                        ioc << cat_error << "Data structure is full and cannot be resized." << io_end;

                        // Report the failure status.
                        return false;
                    }
                }

                // Add the new element to the structure.
                this->theArray[currElements++] = newElement;

                // Report success.
                return true;
            }

    };
}

#endif // PAWLIB_BASEFLEXARRAY_HPP
