/** Base Iterator [PawLIB]
  * Version: 0.1 (Experimental)
  *
  * The base class for (hopefully) all types of iterators in PawLIB.
  *
  * Author(s): Ankush Thakur
  */

/* LICENSE
 * Copyright (c) 2018 MousePaw Media.
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

#ifndef PAWLIB_BASE_ITERATOR_HPP
#define PAWLIB_BASE_ITERATOR_HPP

namespace pawlib
{
    template<class Type>
    class BaseIterator {
        private:
            // the total number of elements currently in the data structure
            unsigned int size;

        public:
            // The default constructor
            // (Since it's an abstract class, there's no idea how will help :-/ )
            BaseIterator() : size(0) {}

            // Function to check if the iterator is valid.
            // It's currently not known how this will be used,
            // but including this functinality seemed like a
            // good idea. :D
            virtual bool isValid() = 0;

            // Function to get the first element in the collection
            // Note: This does NOT move the iterator
            virtual Type* getFirst() = 0;

            // Function to get the last element in the collection
            // Note: This does NOT move the iterator
            virtual Type* getLast() = 0;

            // Get the size of the collection
            unsigned int size() {
                return this->size;
            };

            // Move the iterator to the beginning of the collection
            // Note: This does NOT return any element from the collection
            virtual void moveToFirst() = 0;

            // Move the iterator to the end of the collection
            virtual void moveToLast() = 0;

            // Move to the next element
            // This becomes the part of the 'master' base class,
            // because the idea is that all iterators will have a
            // moveToNext() functionality. By contrast, moveToPrev()
            // won't make sense on, say, singly linked lists.
            virtual void moveToNext() = 0;
    };
}

#endif
