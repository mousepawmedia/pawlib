/** AVL Tree [PawLIB]
  * Version: 1.0
  *
  * The base class for a dynamic array with a low dynamic allocation demand.
  * Designed to take the place of 'std::vector'.
  *
  * Author: Michael Parkman, Jonathan Theodore
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
#include <stdexcept>

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
                //NOTE: method double size sets the max_size to 8 on initiation
                max_size = 4;
                currElements = 0;
                theArray = nullptr;
                double_size(&theArray);
                resizable = true;
            }

            Base_FlexArr(int numElements)
            {
                /*set the size to be the power of 2 just below the entered number.
                *double_size function will initiate with enough room in array*/
                max_size = pow(2, floor(log2(numElements)));
                currElements = 0;
                double_size(0, theArray);// declaration count:...
                resizable = false;
            }

            ~Base_FlexArr()
            {
                free(theArray);
            }

            type operator[](unsigned int index)
            {
                return at(index);
            }

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

            int getSize()
            {
                return currElements;
            }

            int getArraySize()
            {
                return max_size;
            }

        protected:
            type* theArray;
            unsigned int currElements, max_size;
            bool resizable;

            bool double_size(type** daArray)
            {
                //double the maximum size
                max_size *= 2;
                //create the new array with twice the number of elements, 8

                type* tempArray = new type[max_size];

                //if there is an old array (change to NULL?)
                if(*daArray && tempArray != nullptr)
                {
                    //transfer all the elements over
                    for(unsigned int i = 0; i < currElements; i++)
                    {
                        tempArray[i] = (*daArray)[i];
                    }
                    delete (*daArray);
                }
                *daArray = tempArray;
                return true;
            }
            //add the new element to the back of the array
            bool push_back(type newElement)
            {
                if(currElements > max_size - 2 && resizable)
                {
                    double_size(&theArray);
                }
                else if(currElements > max_size - 2 && !resizable)
                {
                    /*Out of room and not allowed to resize.
                      Throw an index out of bounds exception.*/
                    ioc << cat_error << "Array is full and cannot be resized" << io_end;
                    return false;
                }
                theArray[currElements++] = newElement;
                return true;
            }

    };
}

#endif // BASE_FLEX_ARRAY_HPP_INCLUDED
