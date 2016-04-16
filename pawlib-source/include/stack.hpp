#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "base_flex_array.hpp"
#include <iochannel.hpp>

using pawlib::iochannel;
using namespace pawlib::ioformat;

namespace pawlib
{
    template <class type>
    class Stack : public Base_FlexArr<type>
    {
        public:
            Stack() : Base_FlexArr<type>() { }
            // cppcheck-suppress noExplicitConstructor
            Stack(int numElements) : Base_FlexArr<type>(numElements) { }

            //removes the last element in the stack
            type pop()
            {
                //if the stack is empty
                if(this->currElements == 0)
                {
                    ioc << cat_error << vrb_quiet << "The stack is empty" << io_end;
                    return nullptr;
                }
                else
                {
                    //return the last element in the stack and decrement the number of elements in the stack. This effectively deletes the element from the array.
                    return this->theArray[--this->currElements];
                }
            }

            //adds the passed in element to the back of the stack
            void push(type newElement)
            {
                this->push_back(newElement);
            }

        private:
    };
}

#endif // STACK_HPP_INCLUDED
