/** Goldilocks Shell [PawLIB]
  * Version 1.1
  *
  * This is a ready-to-use interface for Goldilocks.
  * It will eventually be expanded and replaced with
  * Blueshell.
  *
  * Author(s): Jason C. McDonald
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

#ifndef PAWLIB_GOLDILOCKS_SHELL_HPP
#define PAWLIB_GOLDILOCKS_SHELL_HPP

#include <algorithm>
#include <cstdint>
// std::is_base_of
#include <type_traits>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

#include "pawlib/goldilocks.hpp"

/* NOTE: We definitely don't want a copy constructor.
    * Sharing the testmanager is a VERY bad idea in this current form.
    * We may revisit this later.
    */
class GoldilocksShell
{
    public:
        /** Default constructor*/
        GoldilocksShell()
        :testmanager(new TestManager), prompt(":")
        {}

        // HACK: Disable copy constructor (not sure this is needed)
        GoldilocksShell(const GoldilocksShell&) = delete;

        /** Construct with a specific prompt string
             * \param the prompt symbol for the shell interface
             */
        // cppcheck-suppress noExplicitConstructor
        GoldilocksShell(const char* prompt_string)
        :testmanager(new TestManager), prompt(prompt_string)
        {}

        /** Run using command-line arguments. Designed to directly accept
             * the same arguments as `int main()`
             * \param the argument count, as from 'int main()'.
             * \param the argument array, as from 'int main()'.
             * \param the number of arguments to skip, default 0
             * \return the return code, to be returned by 'int main()'.
             */
        int command(int argc, char* argv[], unsigned int skip = 0);

        /** Launch an interactive terminal session using IOChannel.
             * \param the pointer to the Testcatalog instance being used.
             */
        void interactive();

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

        // HACK: Disable copy assignment (not sure this is needed)
        GoldilocksShell operator=(const GoldilocksShell&) = delete;

        ~GoldilocksShell()
        {
            delete testmanager;
            testmanager = 0;
        }

    protected:
        typedef std::vector<std::string> stringvector;

        TestManager* testmanager;
        std::string prompt;

        /** The full text of the help command for the shell.
             */
        void help();

        void about(stringvector&);
        void benchmark(stringvector&);
        void compare(stringvector&);
        void list(stringvector&);
        void listsuites(stringvector&);
        void load(stringvector&);
        void run(stringvector&);

        uint8_t validate_arguments(stringvector&, uint8_t, uint8_t = 0);
};

#endif //PAWLIB_GOLDILOCKS_SHELL_HPP
