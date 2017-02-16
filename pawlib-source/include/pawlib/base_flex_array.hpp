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
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef BASE_FLEX_ARRAY_HPP_INCLUDED
#define BASE_FLEX_ARRAY_HPP_INCLUDED

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
            :theArray(nullptr), resizable(true), currElements(0), capacity(4)
            {
                /* The call to double_size() will sets the capacity to 8
                 * on initiation. */

                // Allocate the structure.
                double_size();
            }

            /** Create a new base flex array with room for the specified number
              * of elements.
              * \param the minimum number of elements the structure can hold.
              */
            Base_FlexArr(int numElements)
            :theArray(nullptr), resizable(true), currElements(0)
            {
                /* Set the size to be the power of 2 just below the entered
                 * number. double_size() will initiate with enough
                 * room in array. */
                capacity = pow(2, floor(log2(numElements)));

                // Allocate the structure.
                double_size();
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
            type operator[](unsigned int index)
            {
                return at(index);
            }

            /** Access an element at the given index.
              * \param the index to access.
              * \return the element at the given index.
              */
            type at(unsigned int index)
            {
                if(index > currElements - 1 || index < 0)
                {
                    throw std::out_of_range("BaseFlexArray: Index out of range!");
                }
                else
                {
                    return theArray[index];
                }
            }

            /** Check if the data structure is empty.
              * \return true if empty, else false
              */
            bool empty()
            {
                return (currElements = 0);
            }

            /** Erase the elements in the specified range.
              * \param the first index in the range to remove
              * \param the last index in the range to remove
              */
            bool erase(unsigned int first, unsigned int last=0)
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
                    int removeCount = (last+1) - first;

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
            int getSize()
            {
                return currElements;
            }

            /** Get the maximum number of elements the structure can hold
              * without resizing.
              * \return the maximum number of elements
              */
            int getArraySize()
            {
                return capacity;
            }

        protected:
            /// The pointer to the actual structure in memory.
            type* theArray;

            /// Whether the structure can be resize.
            bool resizable;

            /// The current number of elements in the structure.
            unsigned int currElements;

            /** The maximum number of elements (capacity) that can be contained
              * in the structure without resizing. */
            unsigned int capacity;

            /** Double the capacity of the structure.
              * \return true if it was able to double capacity, else false.
              */
            bool double_size()
            {
                // If we're not allowed to resize...
                if(!resizable)
                {
                    // Report failure.
                    return false;
                }

                // Double the maximum size (capacity).
                capacity *= 2;

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
                    /*for(unsigned int i = 0; i < currElements; i++)
                    {
                        tempArray[i] = this->theArray[i];
                    }*/
                    memmove(
                        tempArray,
                        this->theArray,
                        sizeof(type) * this->currElements
                    );

                    // Delete the old structure.
                    delete[] theArray;
                    this->theArray = nullptr;
                }

                // Store the new structure.
                this->theArray = tempArray;

                // Report success.
                return true;
            }

            /** Shift all elements from the given position the given direction
              * and distance. This is intended for internal use only, and does
              * not check for memory errors.
              * \param the index to shift elements from
              * \param the direction and distance to shift the elements in.
              */
            void mem_shift(unsigned int fromIndex, int direction)
            {
                if(fromIndex + 1 > this->currElements)
                {
                    return;
                }

                memmove(
                    // Move TO the given index.
                    this->theArray + (fromIndex + direction),
                    // Move FROM the given index, plus one.
                    this->theArray + fromIndex,
                    /* Total move size is the number of elements to be moved,
                    * times element size. The number of elements we move
                    * is calculated from the 1-based total number of elements.
                    */
                    sizeof(type) * ((this->currElements) - (fromIndex))
                );
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
                    if(!double_size())
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

#endif // BASE_FLEX_ARRAY_HPP_INCLUDED
