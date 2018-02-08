/** Goldilocks Shell [PawLIB]
  * Version 1.0
  *
  * This is a ready-to-use interface for Goldilocks.
  * It will eventually be expanded and replaced with
  * Blueshell.
  *
  * Author(s): Jason C. McDonald
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

#ifndef PAWLIB_GOLDILOCKS_SHELL_HPP
#define PAWLIB_GOLDILOCKS_SHELL_HPP

#include <algorithm>
// std::is_base_of
#include <type_traits>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "pawlib/goldilocks.hpp"

using namespace pawlib;

namespace pawlib
{
    class TestCatalog
    {
        public:
            TestCatalog();

            template <typename T>
            bool register_suite(std::string name)
            {
                /* Before we continue, ensure we are being asked to register an
                * actual Goldilocks suite!
                */
                if(std::is_base_of<TestSuite, T>::value)
                {
                    // Register a new instance of the TestSuite with the given name.
                    this->testmanager->register_suite(name, new T());
                    return true;
                }
                return false;
            }

            TestManager* testmanager;

            ~TestCatalog();
        protected:
        private:
    };

    class GoldilocksShell
    {
        public:
            GoldilocksShell(){}

            /** Run using command-line arguments. Designed to directly accept
              * the same arguments as `int main()`
              * \param the pointer to the TestCatalog instance being used.
              * \param the argument count, as from 'int main()'.
              * \param the argument array, as from 'int main()'.
              * \param the return code, to be returned by 'int main()'.
              */
            static int command(TestCatalog* sys, int argc, char* argv[]);

            /** Launch an interactive terminal session using IOChannel.
              * \param the pointer to the Testcatalog instance being used.
              */
            static void interactive(TestCatalog* sys);

            ~GoldilocksShell(){}

        protected:
            /** The full text of the help command for the shell.
              */
            static void help();
    };
}

#endif //PAWLIB_GOLDILOCKS_SHELL_HPP