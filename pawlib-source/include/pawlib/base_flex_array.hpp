/** Base FlexArray [PawLIB]
  * Version: 2.0
  *
  * The base class for a dynamic array with a low dynamic allocation demand.
  * FlexArray, FlexQueue, and FlexStack all rely on these.
  *
  * Author(s): Jason C. McDonald, Michael Parkman,
  *            Jonathan Theodore, Moshe Uminer
  */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2016-2020 MousePaw Media.
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

#include <math.h>
#include <stdexcept>
#include <stdlib.h>

#include "pawlib/iochannel.hpp"

template <typename type, bool raw_copy = false, bool factor_double = true>
class Base_FlexArr
{
    public:
        /** Create a new base flex array, with the default starting size.
         */
        Base_FlexArr()
        :internalArray(nullptr), internalArrayBound(nullptr),
            head(nullptr), tail(nullptr), resizable(true),
            _elements(0), _capacity(0)
        {
            /* The call to resize() will sets the capacity to 8
                * on initiation. */

            // Allocate the structure with an initial size.
            resize(8);
        }

        /** Create a new base flex array from another base flex array.
         * Copies the contents of the source array.
         * \param the source array
         */
        Base_FlexArr(const Base_FlexArr<type>& cpy)
        :internalArray(nullptr), internalArrayBound(nullptr),
         head(nullptr), tail(nullptr), resizable(cpy.resizable),
         _elements(0), _capacity(0)
        {
            // Resize to the reserved size of the old array (handles _capacity)
            resize(cpy._capacity);
            // Copy elements over to the new memory (handles _elements)
            copyForeignMemory(cpy);
        }

        /** Move the contents of a flex array.
         * Moves (steals) the contents of the source array.
         * \param the source array
         */
        Base_FlexArr(Base_FlexArr<type>&& mov)
        :internalArray(std::move(mov.internalArray)),
         internalArrayBound(mov.internalArrayBound),
         head(mov.head), tail(mov.tail), resizable(mov.resizable),
         _elements(mov._elements), _capacity(mov._capacity)
        {
            // Prevent double-free when source object is destroyed.
            mov.internalArray = nullptr;
        }

        /** Create a new base flex array with room for the specified number
         * of elements.
         * \param the number of elements the structure can hold.
         */
        // cppcheck-suppress noExplicitConstructor
        Base_FlexArr(size_t numElements)
        :internalArray(nullptr), head(nullptr), tail(nullptr), resizable(true),
         _elements(0), _capacity(0)
        {
            // Never allow instantiating with a capacity less than 2.
            if(numElements > 1)
            {
                // Allocate the structure with the requested size.
                resize(numElements);
            }
            else
            {
                resize(2);
            }

        }

        /** Destructor. */
        ~Base_FlexArr()
        {
            if(internalArray != nullptr)
            {
                delete[] internalArray;
            }
        }

        Base_FlexArr<type>& operator=(const Base_FlexArr<type>& rhs)
        {
            // Don't copy from self.
            if (&rhs == this) { return *(this); }

            // Free original array
            if(this->internalArray != nullptr)
            {
                delete[] this->internalArray;
            }
            this->internalArray = nullptr;
            this->internalArrayBound = nullptr;
            this->head = nullptr;
            this->tail = nullptr;

            // Redefine properties
            this->resizable = rhs.resizable;

            // Resize to the reserved size of the old array (handles _capacity)
            resize(rhs._capacity);
            // Copy elements over to the new memory (handles _elements)
            copyForeignMemory(rhs);

            return *(this);
        }

        Base_FlexArr<type>& operator=(Base_FlexArr&& rhs)
        {
            // Don't copy from self.
            if (&rhs == this) { return *(this); }

            // Free original array
            if(this->internalArray != nullptr)
            {
                delete[] this->internalArray;
            }

            // Directly steal the contents of the source array.
            this->internalArray = std::move(rhs.internalArray);
            this->internalArrayBound = rhs.internalArrayBound;
            this->head = rhs.head;
            this->tail = rhs.tail;
            this->resizable = rhs.resizable;
            this->_elements = rhs._elements;
            this->_capacity = rhs._capacity;

            // Prevent double-free when source object is destroyed.
            rhs.internalArray = nullptr;

            return *(this);
        }

        /** Access an element at a given index using the [] operator.
         * For example, "internalArray[5]".
         */
        type& operator[](size_t index)
        {
            return at(index);
        }

        const type& operator[](size_t index) const
        {
            return at(index);
        }

        /** Access an element at the given index.
         * \param the index to access.
         * \return the element at the given index.
         */
        type& at(size_t index)
        {
            if(!validateIndex(index, false))
            {
                throw std::out_of_range("BaseFlexArray: Index out of range!");
            }

            return internalArray[toInternalIndex(index)];
        }

        const type& at(size_t index) const
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
            this->_elements = 0;
            this->head = this->internalArray;
            this->tail = this->internalArray;
            return true;
        }

        /** Check if the data structure is empty.
             * \return true if empty, else false
             */
        bool isEmpty() const
        {
            return (_elements == 0);
        }

        /** Check to see if the data structure is full.
         * \return true is full, else false
         */
        bool isFull() const
        {
                return (_capacity == _elements);
        }

        /** Erase the elements in the specified range.
         * \param the first index in the range to remove
         * \param the last index in the range to remove
         */
        bool erase(size_t first, size_t last=0)
        {
            /* If no last index was specified, prepare to delete only
            * the element 'first'. */
            if(last == 0)
            {
                last = first;
            }

            // If the range [first-last] is valid...
            if(last >= first && last < this->_elements)
            {
                size_t removeCount = (last+1) - first;

                //...and if we'll have leftovers after `last`
                if(last < this->_elements - 1)
                {
                    // Shift the leftovers backwards into place.
                    memShift(last+1, -removeCount);
                }
                // Recalculate the elements we have.
                this->_elements -= removeCount;

                return true;
            }
            else
            {
                // Throw non-fatal error.
                ioc << IOCat::error << "BaseFlexArray Erase: Invalid range ("
                    << first << " - " << last << "). Took no action."
                    << IOCtrl::endl;
                return false;
            }
        }

        /** Get the current number of elements in the structure.
         * \return the number of elements
         */
        size_t length() const
        {
            return _elements;
        }

        /** Get the maximum number of elements the structure can hold
         * without resizing.
         * \return the maximum number of elements
         */
        size_t capacity() const
        {
            return _capacity;
        }

        /** Reserves room for the exact number of elements.
         * \param the number of elements to reserve
         * \return true if successful, else false
         */
        bool reserve(size_t size)
        {
            return resize(size);
        }

        bool shrink()
        {
            // Never allow shrinking smaller than 2.
            if(this->_elements < 2)
            {
                return resize(2, true);
            }
            // (implicit else)
            return resize(this->_elements, true);
        }
    protected:
        /// The pointer to the actual structure in memory.
        type* internalArray;

        /// The pointer to the end of the internal array.
        type* internalArrayBound;

        /// Pointer to the head element.
        type* head;

        /// Pointer to one past the tail element.
        type* tail;

        /// Whether the structure can be resized.
        bool resizable;

        /// The current number of elements in the structure.
        size_t _elements;

        /** The maximum number of elements (capacity) that can be contained
         * in the structure without resizing. (1-based) */
        size_t _capacity;

        /** Directly access a value in the internal array.
         * Does not check for bounds.
         * \param the internal index to access
         * \return the element at index
         */
        type& rawAt(size_t index)
        {
            return internalArray[toInternalIndex(index)];
        }

        const type& rawAt(size_t index) const
        {
            return internalArray[toInternalIndex(index)];
        }

        /** Validate the given index is in range
         * \param the index to validate
         * \param whether to show an error message on failure, default false
         * \return true if index is in range, else false
         */
        inline bool validateIndex(size_t index, bool yell = false) const
        {
            /* If the index is greater than the number of elements
                * in the array currently. */
            if(index > this->_elements - 1)
            {
                if(yell)
                {
                    // Throw a non-fatal error. Numbers are 0-based.
                    ioc << IOCat::error << IOVrb::quiet << "Index " << index
                    << " out of bounds [0 - " << this->_elements - 1
                    << "]." << IOCtrl::endl;
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
        inline size_t toInternalIndex(size_t index) const
        {
            /* Get the internal index, by adding the external index
                * to the head index, and then accounting for the
                * circular buffer.
                * Thanks to pydsigner and nisstyre in ##python-offtopic
                * for suggesting the modulus.
                */
            return (this->head - this->internalArray + index) % this->_capacity;
        }

        type& getFromHead()
        {
            return *(this->head);
        }

        const type& getFromHead() const
        {
            return *(this->head);
        }

        type& getFromTail()
        {
            if(this->tail == this->internalArray)
            {
                // We have to get the element at the end of the internalArray.
                return *(this->internalArray + (this->_capacity - 1));
            }
            return *(this->tail - 1);
        }

        const type& getFromTail() const
        {
            if(this->tail == this->internalArray)
            {
                // We have to get the element at the end of the internalArray.
                return *(this->internalArray + (this->_capacity - 1));
            }
            return *(this->tail - 1);
        }

        /** Efficiently insert a value at the head of the array.
         * \param the value to insert
         * \param whether to show an error message on failure, default false
         * \return true if successful, else false
         */
        bool insertAtHead(type&& value, bool yell = false)
        {
            // Check capacity and attempt a resize if necessary.
            if(!checkSize(yell)) { return false; }

            shiftHeadBack();

            // Insert our value at the new head position.
            *(this->head) = std::move(value);

            // Increment the number of current elements in the array.
            ++this->_elements;

            return true;
        }


        /** Efficiently insert a value at the tail of the array.
         * \param the value to insert
         * \param whether to show an error message on failure, default false
         * return true if successful, else false
         */
        bool insertAtTail(type&& value, bool yell = false)
        {
            // Check capacity and attempt a resize if necessary.
            if(!checkSize(yell)) { return false; }

            *(this->tail) = std::move(value);

            shiftTailForward();

            // Increment the number of current elements in the array
            ++this->_elements;

            return true;
        }

        /** Insert a value at the given position in the array.
         * Does NOT check index validity.
         * \param the value to insert
         * \param the index to insert the value at
         * \param whether to show an error message on failure, default false
         * \return true if successful, else false
         */
        bool insertAtIndex(type&& value, size_t index, bool yell = false)
        {
            // Check capacity and attempt a resize if necessary.
            if(!checkSize(yell)) { return false; }

            // Shift the values to make room.
            memShift(index, 1);
            // Store the new value.
            this->internalArray[toInternalIndex(index)] = std::move(value);

            // Leave the head/tail shifting to memShift!

            // Increment the number of current elements in the array.
            ++this->_elements;

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
            --this->_elements;

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
            --this->_elements;

            return true;
        }

        /** Remove a value from the array.
         * Does NOT check index validity.
         * Does NOT check if the array is empty.
         * \param the index to remove
         * \return true if successful, else false
         */
        bool removeAtIndex(size_t index)
        {
            /* Decrement the number of elements we're storing.
                * If we have more than one element remaining...
                */
            if(this->_elements-- > 1)
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
            if(this->_elements >= this->_capacity)
            {
                // If we weren't able to resize, report failure.
                if(!resize())
                {
                    if(yell)
                    {
                        ioc << IOCat::error
                        << "Data structure is full and cannot be resized."
                        << IOCtrl::endl;
                    }
                    return false;
                }
            }
            /* If no resize was necessary, or if resize was successful,
                * report success.
                */
            return true;
        }

        /** Copy elements from another Flex-based data structure
         * \param the source data structure
         */
        void copyForeignMemory(const Base_FlexArr<type>& cpy)
        {
            for (size_t i = 0; i < cpy._elements; ++i)
            {
                *(this->tail) = cpy.rawAt(i);
                shiftTailForward();
            }

            this->_elements = cpy._elements;
        }

        /** Double the capacity of the structure.
         * \param the number of elements to reserve space for
         * \param whether we're allowed to non-destructively shrink.
         * \return true if it was able to double capacity, else false.
         */
        bool resize(size_t reserve = 0, bool allow_shrink = false)
        {
            // If we're not allowed to resize, report failure.
            if(!resizable){ return false; }

            size_t oldCapacity = this->_capacity;

            if(reserve == 0)
            {
                // check to see if maximum size is being approached
                if(this->_capacity >= UINT32_MAX/2)
                {
                    // set it to limit defined by UINT32_MAX
                    this->_capacity = UINT32_MAX;
                    // set it so that array can no longer be doubled in size
                    resizable = false;
                }
                // Increase the capacity.

                /* Which option we use depends on whether we want to
                    * optimize for SPEED (2) or SPACE (1.5). */
                if(factor_double)
                {
                    this->_capacity = this->_capacity * 2;
                }
                else
                {
                    this->_capacity += this->_capacity / 2;
                }
            }
            else
            {
                // If the reservation would destroy elements...
                if(reserve < this->_elements)
                {
                    // Report error.
                    return false;
                }
                /* If the reservation would shrink the structure
                    * without permission... */
                else if(!allow_shrink && reserve <= this->_capacity)
                {
                    // Report error.
                    return false;
                }
                this->_capacity = reserve;
            }

            /* Create the new structure with the new capacity.*/
            type* tempArray = new type[this->_capacity];

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
                size_t headIndex = this->head - this->internalArray;
                size_t step1 = oldCapacity - headIndex;
                size_t step2 = headIndex;

                if constexpr (raw_copy)
                {
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
                }
                else
                {
                    size_t destIndex = 0;
                    for (size_t i = headIndex; i < headIndex + step1; ++i)
                    {
                        tempArray[destIndex++] =
                            std::move(this->internalArray[i]);
                    }
                    for (size_t i = 0; i < step2; ++i)
                    {
                        tempArray[destIndex++] =
                            std::move(this->internalArray[i]);
                    }
                }

                // Delete the old structure.
                delete[] this->internalArray;
                this->internalArray = nullptr;
            }

            // Store the new structure.
            this->internalArray = tempArray;
            this->internalArrayBound = this->internalArray + this->_capacity;

            // Reset the head and tail
            this->head = this->internalArray;
            this->tail = this->internalArray + this->_elements;

            // Report success.
            return true;
        }

        /** Shift all elements from the given position the given direction
         * and distance. This is intended for internal use only, and does
         * not check for memory errors.
         * \param the index to shift elements from
         * \param the direction and distance to shift the elements in.
         */
        void memShift(size_t fromIndex, int8_t direction)
        {
            /* Check if the index was valid given the number of elements
                * we're actually storing. (We have to offset so we do our math
                * in 1-indexing).
                */
            if(fromIndex >= this->_elements)
            {
                return;
            }

            // If the array is already empty, there's nothing to move.
            if(isEmpty()){ return; }

            // If we haven't yet had wraparound, move the tail section.
            if(this->tail > this->head && this->tail < this->internalArrayBound)
            {
                if constexpr (raw_copy)
                {
                    memmove(
                        // Move TO the given index.
                        this->head + fromIndex + direction,
                        // Move FROM the given index.
                        this->head + fromIndex,
                        // Total move size is the number of elements to be moved,
                        // times element size. The number of elements we move
                        // is calculated from the 1-based total number of elements.
                        sizeof(type) * (this->_elements - fromIndex)
                    );
                }
                else
                {
                    size_t headIndex = this->head - this->internalArray;
                    size_t destIndex = headIndex + fromIndex + direction;
                    size_t srcIndex = headIndex + fromIndex;
                    size_t toMove = this->_elements - fromIndex;

                    // We must move elements last to first to prevent overwrite.
                    for (size_t i = toMove; i > 0; --i)
                    {
                        /* toMove is converted to zero-index here, so the
                         * loop will break if toMove is 0 (undef behavior) */
                        // MOVE elements instead of copying
                        this->internalArray[destIndex + i - 1] =
                            std::move(this->internalArray[srcIndex + i - 1]);
                    }
                }

                shiftTail(direction);
            }
            // Else If we've already had wraparound, move the head section.
            else if(this->tail < this->head)
            {
                /* There is an ironic side-effect here that, if we are
                 * inserting at 0, we'll only move the head, and not
                 * actually shift anything! (Weird, but it works.)
                 */
                if constexpr (raw_copy)
                {
                    memmove(
                        // Move TO the given index.
                        // Must invert direction for this to work right.
                        this->head - direction,
                        // Move FROM the given index.
                        this->head,
                        sizeof(type) * fromIndex
                    );
                }
                else
                {
                    size_t headIndex = this->head - this->internalArray;
                    size_t destIndex = headIndex - direction;
                    size_t srcIndex = headIndex;
                    size_t toMove = fromIndex;

                    // We must move elements first-to-last to prevent overwrite.
                    for (size_t i = 0; i < toMove; ++i)
                    {
                        // MOVE elements instead of copying
                        this->internalArray[destIndex + i] =
                            std::move(this->internalArray[srcIndex + i]);
                    }
                }

                shiftHead(-direction);
            }
            else
            {
                ioc << "Flex: Impossible circular buffer arrangement."
                    << IOCtrl::endl;

                ioc << "Internal Array: " << IOFormatPtr::address
                    << this->internalArray << IOCtrl::endl;

                ioc << "Head: " << IOFormatPtr::address
                    << this->head << IOCtrl::endl;

                ioc << "Tail: " << IOFormatPtr::address
                    << this->tail << IOCtrl::endl;

                ioc << "Array Bound: " << IOFormatPtr::address
                    << this->internalArrayBound << IOCtrl::endl;

                ioc << "Capacity: " << IOFormatPtr::address
                    << this->_capacity << IOCtrl::endl;

                ioc << "Elements: " << IOFormatPtr::address
                    << this->_elements << IOCtrl::endl;

                throw std::runtime_error(
                    "Flex: Impossible situation. Aborting!"
                );
            }
        }

        inline void shiftHead(size_t direction)
        {
            size_t magnitude = direction;
            if(direction > 0)
            {
                for(size_t i = 0; i < magnitude; ++i)
                {
                    shiftHeadForward();
                }
            }
            else
            {
                for(size_t i = 0; i < magnitude; ++i)
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
                this->head = this->internalArray + (this->_capacity - 1);
            }
        }

        inline void shiftHeadForward()
        {
            // Move the head forward, accounting for wraparound.
            if(++this->head - this->internalArray >= int(this->_capacity))
            {
                this->head = this->internalArray;
            }
        }

        inline void shiftTail(size_t direction)
        {
            size_t magnitude = direction;
            if(direction > 0)
            {
                for(size_t i = 0; i < magnitude; ++i)
                {
                    shiftTailForward();
                }
            }
            else
            {
                for(size_t i = 0; i < magnitude; ++i)
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
                this->tail = this->internalArray + (this->_capacity - 1);
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

#endif // PAWLIB_BASEFLEXARRAY_HPP
