/** Base FlexArray [PawLIB]
  * Version: 1.0
  *
  * The base class for a dynamic array with a low dynamic allocation demand.
  * FlexArray, FlexQueue, and FlexStack all rely on these.
  *
  * Author(s): Michael Parkman, Jonathan Theodore, Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2018 MousePaw Media.
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
            :internalArray(nullptr), internalArrayBound(nullptr),
             head(nullptr), tail(nullptr), resizable(true),
             currElements(0), capacity(0)
            {
                /* The call to resize() will sets the capacity to 8
                 * on initiation. */

                // Allocate the structure with an initial size.
                resize(8);
            }

            /** Create a new base flex array with room for the specified number
              * of elements.
              * \param the number of elements the structure can hold.
              */
            // cppcheck-suppress noExplicitConstructor
            Base_FlexArr(uint32_t numElements)
            :internalArray(nullptr), head(nullptr), tail(nullptr), resizable(true),
             currElements(0), capacity(0)
            {
                // Allocate the structure with the requested size.
                resize(numElements);
            }

            /** Destructor. */
            ~Base_FlexArr()
            {
                if(internalArray != nullptr)
                {
                    delete[] internalArray;
                }
            }

            /** Access an element at a given index using the [] operator.
              * For example, "internalArray[5]".
              */
            type& operator[](uint32_t index)
            {
                return at(index);
            }

            /** Access an element at the given index.
              * \param the index to access.
              * \return the element at the given index.
              */
            type& at(uint32_t index)
            {
                if(!validateIndex(index, false))
                {
                    throw std::out_of_range("BaseFlexArray: Index out of range!");
                }

                return internalArray[toInternalIndex(index)];
            }

            /** Clear all the elements in the array.
              * \return true if successful, else false
              */
            bool clear()
            {
                this->currElements = 0;
                this->head = this->internalArray;
                this->tail = this->internalArray;
                return true;
            }

            /** Check if the data structure is empty.
              * \return true if empty, else false
              */
            bool isEmpty()
            {
                return (currElements == 0);
            }

            /** Check to see if the data structure is full.
              * \return true is full, else false
              */
            bool isFull()
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
                if(last >= first && last < this->currElements)
                {
                    uint32_t removeCount = (last+1) - first;

                    //...and if we'll have leftovers after `last`
                    if(last < this->currElements - 1)
                    {
                        // Shift the leftovers backwards into place.
                        memShift(last+1, -removeCount);
                    }
                    // Recalculate the elements we have.
                    this->currElements -= removeCount;

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
            uint32_t getLength()
            {
                return currElements;
            }

            /** Get the maximum number of elements the structure can hold
              * without resizing.
              * \return the maximum number of elements
              */
            uint32_t getCapacity()
            {
                return capacity;
            }

            /** Reserves room for the exact number of elements.
              * \param the number of elements to reserve
              * \return true if successful, else false
              */
            bool reserve(uint32_t size)
            {
                return resize(size);
            }
        protected:
            const float RESIZE_FACTOR = 1.5;

            /// The pointer to the actual structure in memory.
            type* internalArray;

            /// The pointer to the end of the internal array.
            type* internalArrayBound;

            /// Pointer to the head element.
            type* head;

            // Pointer to one past the tail element.
            type* tail;

            /// Whether the structure can be resize.
            bool resizable;

            /// The current number of elements in the structure.
            uint32_t currElements;

            /** The maximum number of elements (capacity) that can be contained
              * in the structure without resizing. (1-based) */
            uint32_t capacity;

            /** Directly access a value in the internal array.
              * Does not check for bounds.
              * \param the internal index to access
              * \return the element at index
              */
            type& rawAt(uint32_t index)
            {
                return internalArray[toInternalIndex(index)];
            }

            /** Validate the given index is in range
              * \param the index to validate
              * \param whether to show an error message on failure, default false
              * \return true if index is in range, else false
              */
            inline bool validateIndex(uint32_t index, bool yell = false)
            {
                /* If the index is greater than the number of elements
                 * in the array currently. */
                if(index > this->currElements - 1)
                {
                    if(yell)
                    {
                        // Throw a non-fatal error. Numbers are 0-based.
                        ioc << cat_error << vrb_quiet << "Index " << index
                        << " out of bounds [0 - " << this->currElements - 1
                        << "]." << io_end;
                    }
                    // Report failure.
                    return false;
                }
                // Otherwise, return true.
                return true;
            }

            /** Convert an index to an internal index.
              * \param the (external) index to access
              * \return the (internal) index
              */
            inline uint32_t toInternalIndex(uint32_t index)
            {
                /* Get the internal index, by adding the external index
                 * to the head index, and then accounting for the
                 * circular buffer.
                 * Thanks to pydsigner and nisstyre in ##python-offtopic
                 * for suggesting the modulus.
                  */
                return (this->head - this->internalArray + index) % this->capacity;
            }

            type& getFromHead()
            {
                return *(this->head);
            }

            type& getFromTail()
            {
                if(this->tail == this->internalArray)
                {
                    // We have to get the element at the end of the internalArray.
                    return *(this->internalArray + (this->capacity - 1));
                }
                return *(this->tail - 1);
            }

            /** Efficiently insert a value at the head of the array.
              * \param the value to insert
              * \param whether to show an error message on failure, default false
              * \return true if successful, else false
              */
            bool insertAtHead(type value, bool yell = false)
            {
                // Check capacity and attempt a resize if necessary.
                if(!checkSize(yell)) { return false; }

                shiftHeadBack();

                // Insert our value at the new head position.
                *(this->head) = value;

                // Increment the number of current elements in the array.
                ++this->currElements;

                return true;
            }


            /** Efficiently insert a value at the tail of the array.
              * \param the value to insert
              * \param whether to show an error message on failure, default false
              * return true if successful, else false
              */
            bool insertAtTail(type value, bool yell = false)
            {
                // Check capacity and attempt a resize if necessary.
                if(!checkSize(yell)) { return false; }

                *(this->tail) = value;

                shiftTailForward();

                // Increment the number of current elements in the array
                ++this->currElements;

                return true;
            }

            /** Insert a value at the given position in the array.
              * Does NOT check index validity.
              * \param the value to insert
              * \param the index to insert the value at
              * \param whether to show an error message on failure, default false
              * \return true if successful, else false
              */
            bool insertAtIndex(type value, uint32_t index, bool yell = false)
            {
                // Check capacity and attempt a resize if necessary.
                if(!checkSize(yell)) { return false; }

                // Shift the values to make room.
                memShift(index, 1);
                // Store the new value.
                this->internalArray[toInternalIndex(index)] = value;

                // Leave the head/tail shifting to memShift!

                // Increment the number of current elements in the array.
                ++this->currElements;

                return true;
            }

            /** Efficiently remove a value from the head.
              * Does NOT check if the array is empty.
              * \return true if successful, else false
              */
            bool removeAtHead()
            {
                shiftHeadForward();

                // Decrement the number of elements we're currently storing.
                --this->currElements;

                return true;
            }

            /** Efficiently remove a value from the tail.
              * Does NOT check if the array is empty.
              * \return true if successful, else false
              */
            bool removeAtTail()
            {
                /* Move the tail position back, so the previous last value
                 * is now ignored.
                 */

                shiftTailBack();

                // Decrement the number of elements we're currently storing.
                --this->currElements;

                return true;
            }

            /** Remove a value from the array.
              * Does NOT check index validity.
              * Does NOT check if the array is empty.
              * \param the index to remove
              * \return true if successful, else false
              */
            bool removeAtIndex(uint32_t index)
            {
                /* Decrement the number of elements we're storing.
                 * If we have more than one element remaining...
                 */
                if(this->currElements-- > 1)
                {
                    /* Shift all the elements after the index left one position,
                    * overwriting the element we're removing.
                    */
                    memShift(index, -1);
                }
                else
                {
                    /* If we have only one element remaining, we should not
                     * memShift. Just ignore the element's existence.
                     */
                    shiftTailBack();
                }

                return true;
            }

            /** Check if the array is full and attempt a resize if necessary.
              * \param whether to show an error message on failure, default false
              * \return true if resize successful or no resize necessary
              */
            inline bool checkSize(bool yell = false)
            {
                // If we're full, attempt a resize.
                if(this->currElements >= this->capacity)
                {
                    // If we weren't able to resize, report failure.
                    if(!resize())
                    {
                        if(yell)
                        {
                            ioc << cat_error
                            << "Data structure is full and cannot be resized."
                            << io_end;
                        }
                        return false;
                    }
                }
                /* If no resize was necessary, or if resize was successful,
                 * report success.
                 */
                return true;
            }

            /** Double the capacity of the structure.
              * \return true if it was able to double capacity, else false.
              */
            bool resize(uint32_t reserve = 0)
            {
                // If we're not allowed to resize, report failure.
                if(!resizable){ return false; }

                uint32_t oldCapacity = this->capacity;

                if(reserve == 0)
                {
                    // check to see if maximum size is being approached
                    if(this->capacity >= UINT32_MAX/2)
                    {
                        // set it to limit defined by UINT32_MAX
                        this->capacity = UINT32_MAX;
                        // set it so that array can no longer be doubled in size
                        resizable = false;
                    }
                    // Increase the capacity.
                    this->capacity = this->capacity * RESIZE_FACTOR;
                }
                else
                {
                    // If the reservation would shrink the structure..
                    if(reserve <= this->capacity)
                    {
                        // Report error.
                        return false;
                    }
                    this->capacity = reserve;
                }

                /* Create the new structure with the new capacity.*/
                type* tempArray = new type[this->capacity];

                // If there was an error allocating the new array...
                if(tempArray == nullptr)
                {
                    // Report failure.
                    return false;
                }

                // If an old array exists...
                if(this->internalArray != nullptr)
                {
                    /* Transfer all of the elements over.
                     * Since this is a circular buffer, we have to move things
                     * so it has room for expansion. The fastest way to do this
                     * is by storing the head element back at index 0.
                     * To do this, we'll move everything in two parts:
                     * (1) head to end of space, and (2) 0 to head-1.
                     */
                    uint32_t headIndex = this->head - this->internalArray;
                    uint32_t step1 = oldCapacity - headIndex;
                    uint32_t step2 = headIndex;
                    memcpy(
                        tempArray,
                        this->head,
                        sizeof(type) * step1
                    );
                    memcpy(
                        tempArray + step1,
                        this->internalArray,
                        sizeof(type) * step2
                    );

                    // Delete the old structure.
                    delete[] this->internalArray;
                    this->internalArray = nullptr;
                }

                // Store the new structure.
                this->internalArray = tempArray;
                this->internalArrayBound = this->internalArray + this->capacity;

                // Reset the head and tail
                this->head = this->internalArray;
                this->tail = this->internalArray + this->currElements;

                // Report success.
                return true;
            }

            /** Shift all elements from the given position the given direction
              * and distance. This is intended for internal use only, and does
              * not check for memory errors.
              * \param the index to shift elements from
              * \param the direction and distance to shift the elements in.
              */
            void memShift(uint32_t fromIndex, int8_t direction)
            {
                /* Check if the index was valid given the number of elements
                 * we're actually storing. (We have to offset so we do our math
                 * in 1-indexing).
                 */
                if(fromIndex >= this->currElements)
                {
                    return;
                }

                // If the array is already empty, there's nothing to move.
                if(isEmpty()){ return; }

                // If we haven't yet had wraparound, move the tail section.
                if(this->tail > this->head && this->tail < this->internalArrayBound)
                {
                    memmove(
                        // Move TO the given index.
                        this->head + fromIndex + direction,
                        // Move FROM the given index.
                        this->head + fromIndex,
                        // Total move size is the number of elements to be moved,
                        // times element size. The number of elements we move
                        // is calculated from the 1-based total number of elements.
                        sizeof(type) * (this->currElements - fromIndex)
                    );

                    shiftTail(direction);
                }
                // Else If we've already had wraparound, move the head section.
                else if(this->tail < this->head)
                {
                    /* There is an ironic side-effect here that, if we are
                     * inserting at 0, we'll only move the head, and not
                     * actually shift anything! (Weird, but it works.)
                     */
                    memmove(
                        // Move TO the given index.
                        // Must invert direction for this to work right.
                        this->head - direction,
                        // Move FROM the given index.
                        this->head,
                        sizeof(type) * fromIndex
                    );

                    shiftHead(-direction);
                }
                else
                {
                    // NOTE: Test for this.
                    ioc << "weird edge case" << io_end;
                }
            }

            inline void shiftHead(int32_t direction)
            {
                uint32_t magnitude = direction;
                if(direction > 0)
                {
                    for(uint32_t i = 0; i < magnitude; ++i)
                    {
                        shiftHeadForward();
                    }
                }
                else
                {
                    for(uint32_t i = 0; i < magnitude; ++i)
                    {
                        shiftHeadBack();
                    }
                }
            }

            inline void shiftHeadBack()
            {
                // Move the head back, accounting for wraparound.
                if(this->head-- <= this->internalArray)
                {
                    this->head = this->internalArray + (this->capacity - 1);
                }
            }

            inline void shiftHeadForward()
            {
                // Move the head forward, accounting for wraparound.
                if(++this->head - this->internalArray >= this->capacity)
                {
                    this->head = this->internalArray;
                }
            }

            inline void shiftTail(int32_t direction)
            {
                uint32_t magnitude = direction;
                if(direction > 0)
                {
                    for(uint32_t i = 0; i < magnitude; ++i)
                    {
                        shiftTailForward();
                    }
                }
                else
                {
                    for(uint32_t i = 0; i < magnitude; ++i)
                    {
                        shiftTailBack();
                    }
                }
            }

            inline void shiftTailBack()
            {
                // Move the tail back, accounting for wraparound.
                if(this->tail-- == this->internalArray)
                {
                    this->tail = this->internalArray + (this->capacity - 1);
                }
            }

            inline void shiftTailForward()
            {
                // Move the tail forward, accounting for wraparound.
                if(++this->tail >= this->internalArrayBound)
                {
                    this->tail = this->internalArray;
                }
            }
    };
}

#endif // PAWLIB_BASEFLEXARRAY_HPP
