/** Rigid Stack [PawLIB]
  * Version: 1.0
  *
  * A high-performance, fixed-size stack with no inherent
  * dynamic allocation overhead.
  *
  * Last Updated: 28 June 2016
  * Author: Jason C. McDonald
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

#ifndef RIGID_STACK_HPP_INCLUDED
#define RIGID_STACK_HPP_INCLUDED

#include <cstdint>
#include <stdexcept>

namespace pawlib
{
    template<typename T, uint64_t S, bool F>
    class RigidStack
    {
        private:
            // The length of the stack.
            const uint64_t len;
            /* Points to the next empty position in the stack. We track this
             * instead of the "top" index, so empty is "next==0" and full is
             * "next==S". */
            uint64_t next;
            // The stack's array.
            T stk[S];

        public:
            /** Construct a new RigidStack. */
            RigidStack()
            :len(S), next(0), failsafe(F)
            {}

            /** Access the top element in the stack.
              * \return the element
              */
            T top()
            {
                // If the stack is empty...
                if(next == 0)
                {
                    throw std::out_of_range("Cannot get top() from empty RigidStack.");
                }
                //Else return the top element (next-1) without changing next.
                return stk[next-1];
            }

            /** Access the front element in the stack. Alias for top().
              * \return the element.
              */
            inline T front()
            {
                return top();
            }

            /** Access and remove the top element in the stack.
              * \return the element */
            T pop()
            {
                // If the stack is empty...
                if(next == 0)
                {
                    throw std::out_of_range("Cannot pop from empty RigidStack.");
                }
                // Else, decrement next and return the top element.
                return stk[--next];
            }

            /** Push an element to the stack.
              * \param the element to push */
            void push(T ele)
            {
                // If the stack is full...
                if(next >= len)
                {
                    if(failsafe)
                    {
                        return;
                    }
                    else
                    {
                        throw std::length_error("Cannot push to full RigidStack.");
                    }
                }
                // Else, store the element and increment next.
                stk[next++] = ele;
            }

            /** Get the number of elements in the stack.
              * \return the number of elements currently in the stack
              */
            uint64_t length()
            {
                return next;
            }

            /** Returns whether there are elements in the stack.
              * \return true if elements, else false
              */
            bool not_empty()
            {
                return (next > 0);
            }

            /** Get the maximum number of elements in the stack.
              * \return the maximum number of elements that can fit in stack
              */
            uint64_t max_length()
            {
                return len;
            }



            ~RigidStack(){}
        private:
            // Allow ignoring the relatively expensive "full stack" exception.
            bool failsafe;
    };
}

#endif // RIGID_STACK_HPP_INCLUDED
