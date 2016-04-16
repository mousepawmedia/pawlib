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
                //set the size to be the power of 2 just below the entered number. double_size funtion will initiate with enough room in array
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
            int currElements, size;
            bool resizable;

            void double_size(type** daArray)
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
                    for(int i = 0; i < currElements; i++)
                    {
                        tempArray[i] = (*daArray)[i];
                    }
                    free(*daArray);
                }
                *daArray = tempArray;
            }

            //add the new element to the back of the array
            void push_back(type newElement)
            {
                if(currElements > size - 2 && resizable)
                {
                    double_size(&theArray);
                }
                else if(currElements > size - 2 && !resizable)
                {
                    //TODO: Throw Error. Out of room and not allowed to resize
                }
                theArray[currElements++] = newElement;
            }

    };
}

#endif // BASE_FLEX_ARRAY_HPP_INCLUDED
