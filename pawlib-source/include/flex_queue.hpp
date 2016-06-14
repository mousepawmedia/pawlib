/** Queue [PawLIB]
  * Version: 1.0
  *
  * A queue with a low dynamic allocation demand.
  *
  * Last Updated: 8 March 2016
  * Author: Michael Parkman
  */

/* LICENSE
 * Copyright (C) 2016 MousePaw Games. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef FLEX_QUEUE_HPP_INCLUDED
#define FLEX_QUEUE_HPP_INCLUDED

#include "base_flex_array.hpp"
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <class type>
    class flex_queue : public Base_FlexArr<type>
    {
        public:
            flex_queue() : Base_FlexArr<type>(){ }
            // cppcheck-suppress noExplicitConstructor
            Queue(int numElements) : Base_FlexArr<type>(numElements){ }

            //adds the passed in element to the queue
            void add(type newElement)
            {
                this->push_back(newElement);
            }

            //returns the value in the first index of the queue
            type peek()
            {
                return this->at(0);
            }

            //removes and returns the first element in the queue
            type poll()
            {
                //if there is an element that can be removed
                if(this->currElements > 0)
                {
                    //set temp to be the first element in the queue
                    type temp = this->theArray[0];
                    //shift all elements to the left 1 effectively deleting the element
                    for(int i = 0; i < this->currElements - 1; i++)
                    {
                        this->theArray[i] = this->theArray[i + 1];
                    }
                    //decrement the number of elements
                    this->currElements--;
                    //return the deleted element
                    return temp;
                }
                //if the queue is empty
                else
                {
                    ioc << cat_error << vrb_quiet << "The queue is empty" << io_end;
                    return nullptr;
                }
            }
    };
}

#endif // QUEUE_HPP_INCLUDED
