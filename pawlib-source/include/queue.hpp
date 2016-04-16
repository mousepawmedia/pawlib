#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

#include "base_flex_array.hpp"
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <class type>
    class Queue : public Base_FlexArr<type>
    {
        public:
            Queue() : Base_FlexArr<type>(){ }
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
