/** FlexStack [PawLIB]
  * Version: 1.0
  *
  * A Flex-based stack with a low dynamic allocation demand.
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

#ifndef FLEX_STACK_HPP_INCLUDED
#define FLEX_STACK_HPP_INCLUDED

#include <stack>

#include "pawlib/base_flex_array.hpp"
#include "pawlib/iochannel.hpp"

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <class type>
    class FlexStack : public Base_FlexArr<type>
    {
        public:
            FlexStack() : Base_FlexArr<type>() { }

            explicit FlexStack(unsigned int numElements)
            :Base_FlexArr<type>(numElements)
            {}

            /** Add the specified element to the FlexStack.
              * \param the element to add.
              * \return true if successful, else false.
              */
            bool push(type newElement)
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

            /** Returns the next (last) element in the FlexStack without
              * modifying the data structure.
              * \return the next element in the FlexStack.
              */
            type peek()
            {
                // If there is at least one element in the array...
                if(this->currElements > 0)
                {
                    // Return that element.
                    return this->at(this->currElements-1);
                }
                // Otherwise...
                else
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexArray: Cannot peek from empty FlexArray.");
                }
            }

            /** Return and remove the next element in the FlexStack.
              * \return the next (last) element, now removed.
              */
            type pop()
            {
                // If there are no elements...
                if(this->currElements == 0)
                {
                    // Throw a fatal error.
                    throw std::out_of_range("FlexStack: Cannot pop from empty FlexStack.");
                }
                // Else if there is at least one element...
                else
                {
                    /* Return the last element and decrement the
                     * number of elements. */
                    return this->theArray[--(this->currElements)];
                }
            }
    };
}
#endif // STACK_HPP_INCLUDED
