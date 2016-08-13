/** AVL Tree [PawLIB]
  * Version: 1.0
  *
  * The base class for a dynamic array with a low dynamic allocation demand.
  * Designed to take the place of 'std::vector'.
  *
  * Last Updated: 8 March 2016
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

#ifndef BASE_FLEX_ARRAY_HPP_INCLUDED
#define BASE_FLEX_ARRAY_HPP_INCLUDED

#include <stdlib.h>
#include <math.h>
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template<class type>
    class Base_FlexArr
    {
        public:
            Base_FlexArr()
            {
                //method double size sets the size to 8 on initiation
                size = 4;
                currElements = 0;
                //NOTE: Replace with NULL?
                theArray = nullptr;
                double_size(&theArray);
                resizable = true;
            }

            // cppcheck-suppress noExplicitConstructor
            Base_FlexArr(int numElements)
            {
                /*set the size to be the power of 2 just below the entered number.
                *double_size funtion will initiate with enough room in array*/
                size = pow(2, floor(log2(numElements)));
                currElements = 0;
                //NOTE: Replace with NULL?
                double_size(0, theArray);
                resizable = false;
            }

            ~Base_FlexArr()
            {
                free(theArray);
            }

            type operator[](int index)
            {
                return at(index);
            }

            type at(int index)
            {
                if(index > currElements - 1 || index < 0)
                {
                    ioc << cat_error << vrb_quiet << "Index out of bounds" << io_end;
                    return nullptr;
                }
                else
                {
                    return theArray[index];
                }
            }

            int getSize()
            {
                return currElements;
            }

            int getArraySize()
            {
                return size;
            }

        protected:
            type* theArray;
            unsigned int currElements, size;
            bool resizable;

            bool double_size(type** daArray)
            {
                //double the size
                size *= 2;
                //create the new array with twice the number of elements
                // cppcheck-suppress unmatchedSuppression
                type* tempArray = (type*) malloc(size * sizeof(type));
                //if there is an old array (change to NULL?)
                if(*daArray != nullptr)
                {
                    //transfer all the elements over
                    for(unsigned int i = 0; i < currElements; i++)
                    {
                        tempArray[i] = (*daArray)[i];
                    }
                    free(*daArray);
                }
                *daArray = tempArray;
                return true;
            }
            //add the new element to the back of the array
            bool push_back(type newElement)
            {
                if(currElements > size - 2 && resizable)
                {
                    double_size(&theArray);
                }
                else if(currElements > size - 2 && !resizable)
                {
                    /*Note:Throw Error. Out of room and not allowed to resize
                     *throw an index out of bounds exception
                     *print current size*/
                    ioc << cat_error << vrb_quiet << "Flex Array Size = " << size
                       //this->currElements - 1 //prints elements minus one
                       << " Array is full and cannot be resized" << io_end;
                       return false;
                }
                theArray[currElements++] = newElement;
                return true;
            }

    };
}

#endif // BASE_FLEX_ARRAY_HPP_INCLUDED
