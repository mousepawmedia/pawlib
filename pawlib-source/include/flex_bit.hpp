#ifndef FLEXBIT_HPP_INCLUDED
#define FLEXBIT_HPP_INCLUDED

#include "base_flex_array.hpp"
#include "flex_array.hpp"
#include <bitset>
#include <stdexcept>
#include <iochannel.hpp>

using std::bitset;

/* Must use startIndex to point to the beginning of the FlexBit! */

namespace pawlib
{
    typedef bitset<8> byte;
    class FlexBit
    {
        public:

            //Default constructor.
            FlexBit(): startIndex(0), totalSize(10), size(0)
            {
                container = new byte[totalSize];
            }

            //Copy constructor.
            FlexBit(const FlexBit& other)
            {
                startIndex = other.startIndex;
                totalSize = other.totalSize;
                size = other.size;
                container = new byte[other.totalSize];
                container = other.container;
            }

            //Destructor
            ~FlexBit()
            {
                delete[] container;
            }

            //Getters
            unsigned int getSize() {return size;}
            unsigned int getTotalSize() {return totalSize;}
            unsigned int getStartIndex() {return startIndex;}

            //Appends a byte to the end of FlexArray.
            inline void push(byte b)
            {
                addLast(b);
            }

            //Retrieves, but does not remove, the first element in the queue.
            inline byte peek()
            {
                //Throws out_of_range exception.
                return at(startIndex);
            }

            /*Retrieves and removes the first element in the queue.
              Only shifting the contents of FlexBit when they make up less
              than 25% of the total space, will also copy contents into a smaller
              space in memory deallocating the old FlexBit. */
            byte poll()
            {
                //If the queue is not empty,
                //otherwise throw an exception.
                if (size > 0)
                {
                    //Getting the first element in the queue.
                    byte head = container[startIndex];

                    //Checking if there is less than approximately 25% total space being used.
                    //Depending on the lost of precision when the value is calculated and then cast into
                    //an integer value. So anything that yields a value between 4 and 5 will be considered 4. eg. 4.99999 will be casted to 4.
                    //Let totalSize/size = n.
                    //If n > 4, that means that the current size of
                    //FlexBit can fit equally into the total size of the container
                    //n times, so the greater n is the more space that is not being used.
                    if (totalSize / size > 4)
                    {

                        ++startIndex;
                        if (--size == 0)
                        {
                            totalSize = 10;
                        }
                        else
                        {
                            totalSize = size * 2;

                        }
                        byte* tempContainer = new byte[totalSize];

                        //Copy elements into the new container.
                        if (container && size > 0)
                        {
                            //Copy elements into the new container.
                            memcpy(tempContainer, &container[startIndex], size * sizeof(byte));
                        }
                        delete[] container;
                        container = tempContainer;
                        startIndex = 0;
                    }
                    else
                    {
                        --size;
                        ++startIndex;
                    }

                    return head;

                }
                else
                {
                    throw std::length_error("Empty FlexBit");
                }

            }

            //Prints the FlexBit to the screen.
            std::string toString()
            {
                std::string str = "";
                std::string cur = "";
                if (size > 0)
                {
                    for (unsigned int i = startIndex; i < (size + startIndex) - 1; i++)
                    {
                        cur = at(i).to_string();
                        str += cur + ", ";
                    }

                    cur = at((size + startIndex) - 1).to_string();
                    str += cur + "\n";
                    return str;

                }
                else
                {
                    throw std::length_error("Empty FlexBit");
                }


            }

            //Prints the first byte in the FlexBit.
            void printPeek()
            {
                ioc << peek().to_string() << io_end;
            }

        private:

            /* "startIndex" is where the first element in the FlexBit starts.
               "totalSize" is the total size in the array of bytes.
               "size" is the number of bytes in FlexBit. */
            unsigned int startIndex, totalSize, size;
            byte* container;

            /* Idea taken from flex_array, where we double the size
               of the array container which will be used by the push function. */
            void doubleSize()
            {
                totalSize *= 2;

                byte* tempContainer = new byte[totalSize];

                //If container pointer is not null.
                if (container)
                {
                    //Copy elements into the new container.
                    memcpy(&tempContainer[0], &container[startIndex], size * sizeof(byte));

                }
                delete[] container;
                container = tempContainer;
                startIndex = 0;

            }

            //Adds the new byte at the end of the FlexBit.
            void addLast(byte b)
            {
                //If current size is >= totalSize then double totalSize.
                if (size + startIndex >= totalSize - 1)
                {
                    doubleSize();
                }

                container[startIndex + size] = b;
                ++size;
            }

            //Retrieves byte at given index.
            byte at(unsigned int index)
            {
                if (index > (size + startIndex) - 1 || index < startIndex)
                {
                    throw std::out_of_range("Index out of bounds.");
                }
                else
                {
                    return container[index];
                }
            }

    };
}




#endif // FLEXBIT_HPP_INCLUDED
