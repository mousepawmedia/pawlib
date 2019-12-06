/** Tests for FlexBit[PawLIB]
  * Version: 0.1
  *
  * Author(s): Sergio Ramirez
  */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2016-2019 MousePaw Media.
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

#ifndef PAWLIB_FLEXBIT_TESTS_HPP
#define PAWLIB_FLEXBIT_TESTS_HPP

#include <bitset>
#include <iostream>
#include <limits>

#include "pawlib/flex_bit.hpp"
#include "pawlib/goldilocks.hpp"
#include "pawlib/iochannel.hpp"
#include "pawlib/stdutils.hpp"

namespace pawlib
{
    //Testing push function.
    class TestFlexBit_Push : public Test
    {
        public:

            //Constructor.
            explicit TestFlexBit_Push(unsigned int iterations): iters(iterations) {}

            //Destructor
            ~TestFlexBit_Push() {}

            //Test title.
            testdoc_t get_title() override
            {
                return "FlexBit: Push " + stdutils::itos(iters, 10) + " bytes.";
            }

            //Test description.
            testdoc_t get_docs() override
            {
                return "Push " + stdutils::itos(iters, 10) + " bytes to a flex bit.";
            }

            //Run the test.
            bool run() override
            {
                FlexBit flexbit;

                try
                {
                    //Loop for the given amount of iterations.
                    for (unsigned int i = 0; i < iters; ++i)
                    {
                        //Using Mod operator to limit the input size of the byte. (0 >= value <= 255)
                        std::bitset<8> byte(i % 255);
                        flexbit.push(byte);
                    }
                }
                catch (const std::exception& e)
                {
                    //Any unaccounted for exception.
                    ioc << IOCat::error << "Error occurred: " << e << IOCtrl::endl;
                    return false;
                }
                catch (...)
                {
                    //Unknown failure.
                    ioc << IOCat::error << "Unknown failure occurred." << IOCtrl::endl;
                    return false;
                }

                return true;
            }

        private:
            unsigned int iters;
    };

    //Test peek function.
    class TestFlexBit_Peek : public Test
    {
        public:

            //Default constructor
            TestFlexBit_Peek() {}

            //Destructor
            ~TestFlexBit_Peek() {}

            //Test tittle.
            testdoc_t get_title() override
            {
                return "FlexBit: Peek";
            }

            //Test description.
            testdoc_t get_docs() override
            {
                return "Push 101 bytes to a flex bit then peek and test if its the right value.";
            }

            //Adding 100 bytes to a test FlexBit.
            bool pre() override
            {
                try
                {
                    //Add 100 bytes to FlexBit.
                    for (int i = 100; i >= 0; i--)
                    {
                        //Using Mod operator to limit the input size of the byte. (0 >= value <= 255)
                        std::bitset<8> byte(i % 255);
                        testFlexBit.push(byte);
                    }
                }
                catch (const std::exception& e)
                {
                    //Any unaccounted for exception.
                    std::cerr << "Error occurred: " << e.what() << std::endl;
                    return false;
                }
                catch (...)
                {
                    //Unknown failure.
                    std::cerr << "Unknown failure occurred." << std::endl;
                    return false;
                }

                return true;
            }

            //Running the test to peek at the FlexBit.
            bool run() override
            {
                try
                {
                    /* If the peek value is not "01100100" (decimal value: 100),
                       which is the value that is in first position in the queue
                       designed for this test. Then the test will fail. */
                    std::bitset<8> peekValue = testFlexBit.peek();
                    if (peekValue != std::bitset<8>(std::string("01100100")))
                    {
                        return false;
                    }

                }
                catch (const std::out_of_range& e)
                {
                    //Out of range exception.
                    ioc << IOCat::error << "Out of range error: " << e << IOCtrl::endl;
                    return false;
                }
                catch (const std::exception& e)
                {
                    //Any unaccounted for exception.
                    ioc << IOCat::error << "Error occurred: " << e << IOCtrl::endl;
                    return false;
                }
                catch (...)
                {
                    //Unknown failure.
                    ioc << IOCat::error << "Unknown failure occurred." << IOCtrl::endl;
                    return false;
                }

                return true;
            }

            //Clean up.
            bool post() override
            {
                testFlexBit.~FlexBit();

                return true;
            }

        private:
            FlexBit testFlexBit;


    };

    //Testing the poll(remove) function of flexbit.
    class TestFlexBit_Poll : public Test
    {
        public:

            //Default constructor.
            explicit TestFlexBit_Poll(unsigned int iterations): iters(iterations) {}

            //Destructor
            ~TestFlexBit_Poll() {}

            //Test title.
            testdoc_t get_title() override
            {
                return "FlexBit: Poll " + stdutils::itos(iters, 10) + " bytes.";
            }

            //Test description.
            testdoc_t get_docs() override
            {
                return "Push " + stdutils::itos(iters,
                                                10) + " bytes to a flex bit then remove them.";
            }

            //Add given amount of bytes to a FlexBit.
            bool pre() override
            {
                for (int i = iters - 1; i >= 0 ; i--)
                {
                    //Using Mod operator to limit the input size of the byte. (0 >= value <= 255)
                    std::bitset<8> byte(i % 255);
                    testFlexBit.push(byte);
                }
                return true;
            }

            //Running the poll function until FlexBit is empty.
            bool run() override
            {
                try
                {
                    //Checking if the size is not what its supposed to be.
                    if (testFlexBit.getSize() != iters)
                    {
                        return false;
                    }
                    //Removing every single byte from the FlexBit.
                    for (int i = iters - 1; i >= 0 ; i--)
                    {
                        //Making sure the value is what its suppose to.
                        if (std::bitset<8>(i % 255) != testFlexBit.poll())
                        {
                            return false;
                        }
                    }

                }
                catch (const std::length_error& e)
                {
                    //Length error, which is only thrown inside poll().
                    ioc << IOCat::error << "Length error: " << e << IOCtrl::endl;
                    return false;
                }
                catch (const std::exception& e)
                {
                    //Any unaccounted for exception.
                    ioc << IOCat::error << "Error occurred: " << e << IOCtrl::endl;
                    return false;
                }
                catch (...)
                {
                    //Unknown failure.
                    ioc << IOCat::error << "Unknown failure occurred." << IOCtrl::endl;
                    return false;
                }

                return true;

            }

            //Clean up.
            bool post() override
            {
                testFlexBit.~FlexBit();

                return true;
            }

        private:
            FlexBit testFlexBit;
            unsigned int iters;
    };

    //Basic test for the print function in flexbit.
    class TestFlexBit_ToString : public Test
    {
        public:

            //Default constructor.
            explicit TestFlexBit_ToString(unsigned int iterations): iters(iterations) {}

            //Destructor
            ~TestFlexBit_ToString() {}

            //Test tittle.
            testdoc_t get_title() override
            {
                return "FlexBit: ToString " + stdutils::itos(iters, 10) + " bytes.";
            }

            //Test description.
            testdoc_t get_docs() override
            {
                return "Push " + stdutils::itos(iters,
                                                10) + " bytes to a flex bit and return as a readable string.";
            }

            //Add given amount of bytes to a FlexBit.
            bool pre() override
            {
                for (int i = iters - 1; i >= 0 ; i--)
                {
                    //Using Mod operator to limit the input size of the byte. (0 >= value <= 255)
                    std::bitset<8> byte(i % 255);
                    testFlexBit.push(byte);
                }
                return true;
            }

            //Running test to print given amount of bytes in the FlexBit.
            bool run() override
            {
                try
                {
                    std::string str = testFlexBit.toString();

                    //Only checking values from small flexbits,
                    //Anything larger than 100 elements will be
                    //purely stress testing.
                    if (iters <= 100)
                    {
                        std::string compareStr = "";

                        //Duplicating the method used to create the flexbit
                        //to check if the values are correct.
                        for (int i = iters - 1; i > 0 ; i--)
                        {
                            compareStr += std::bitset<8>(i % 255).to_string() + ", ";
                        }

                        compareStr += std::bitset<8>(0 % 255).to_string() + "\n";

                        //Checking if the string returned from the
                        //flexbit toString method is what it should be.
                        if (str.compare(compareStr) != 0)
                        {
                            return false;
                        }
                    }

                }
                catch (const std::length_error& e)
                {
                    //Length error.
                    ioc << IOCat::error << "Length error: " << e << IOCtrl::endl;
                    return false;
                }
                catch (const std::exception& e)
                {
                    //Any unaccounted for exception.
                    ioc << IOCat::error << "Error occurred: " << e << IOCtrl::endl;
                    return false;
                }
                catch (...)
                {
                    //Unknown failure.
                    std::cerr << "Unknown failure occurred." << std::endl;
                    ioc << IOCat::error << "Unknown failure occurred." << IOCtrl::endl;
                    return false;
                }

                return true;

            }

            //Clean up.
            bool post() override
            {
                testFlexBit.~FlexBit();

                return true;
            }

        private:
            FlexBit testFlexBit;
            unsigned int iters;
    };


    class TestSuite_FlexBit : public TestSuite
    {
        public:
            void load_tests() override;
            testdoc_t get_title() override
            {
                return "PawLIB: FlexBit tests";
            }

    };
}


#endif // PAWLIB_FLEXBIT_TESTS_HPP
