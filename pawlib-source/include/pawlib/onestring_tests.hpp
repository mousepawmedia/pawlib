/** Tests for OneString[PawLIB]
  * Version: 0.3
  *
  * Author(s): Scott Taylor, Bo Volwiler, Jason C. McDonald
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Media.
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

#ifndef PAWLIB_ONESTRING_TESTS_HPP
#define PAWLIB_ONESTRING_TESTS_HPP

#include <string>

#include "pawlib/goldilocks.hpp"
#include "pawlib/onestring.hpp"
#include "iochannel.hpp"
#include "goldilocks.hpp"

using namespace pawlib::ioformat;
using namespace pawlib;

namespace pawlib
{
    class TestOneString : public Test
    {
        public:
            enum TestStringType {
                NO_UNICODE,
                SOME_UNICODE,
                JUST_UNICODE
            };

            OneString noUnicode1 = "The quick brown fox jumped over the lazy dog.";
            OneString someUnicode1 = "The quick brown 🦊 jumped over the lazy 🐶.";
            OneString justUnicode1 = "Ø÷ℌ№Ⅳ↉₲ↇ↕↹↱";

            OneString noUnicode2 = "Jackdaws love my big sphinx of quartz.";
            OneString someUnicode2 = "🐦 ❤️ my big sphinx of 💎.";
            OneString justUnicode2 = "℀ℂ℟ℚⅦↂℬΩ℡";

        protected:
            TestStringType stringType;

            testdoc_t title;

        public:
            explicit TestOneString(TestStringType type)
            :stringType(type)
            {
                switch(stringType)
                {
                    case NO_UNICODE:
                    {
                        title = "(No Unicode)";
                        break;
                    }
                    case SOME_UNICODE:
                    {
                        title = "(Some Unicode)";
                        break;
                    }
                    case JUST_UNICODE:
                    {
                        title = "(Just Unicode)";
                        break;
                    }
                }
            }

            virtual testdoc_t get_title() override = 0;

            virtual testdoc_t get_docs() override = 0;
    };

    // P-tB4001[a-c]
    class TestOneString_Equal : public TestOneString
    {
        public:
            explicit TestOneString_Equal(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: == Operator " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test that the == operator returns true between like strings.";
            }

            bool run() override {
                switch(stringType)
                {
                    case NO_UNICODE:
                    {
                        return (noUnicode1 == noUnicode1 && noUnicode2 == noUnicode2);
                    }
                    case SOME_UNICODE:
                    {
                        return (someUnicode1 == someUnicode1 && someUnicode2 == someUnicode2);
                    }
                    case JUST_UNICODE:
                    {
                        return (justUnicode1 == justUnicode1 && justUnicode2 == justUnicode2);
                    }
                }
                return false;
            }
    };

    // P-tB4002[a-c]
    class TestOneString_EqualFail : public TestOneString
    {
        public:
            explicit TestOneString_EqualFail(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: == Operator Fail " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test that the == operator returns false between non-like strings.";
            }

            bool run() override {
                switch(stringType)
                {
                    case NO_UNICODE:
                    {
                        // cppcheck-suppress duplicateExpression
                        return (noUnicode1 == noUnicode2 || noUnicode2 == noUnicode1) ? false : true;
                    }
                    case SOME_UNICODE:
                    {
                        // cppcheck-suppress duplicateExpression
                        return (someUnicode1 == someUnicode2 || someUnicode2 == someUnicode1) ? false : true;
                    }
                    case JUST_UNICODE:
                    {
                        // cppcheck-suppress duplicateExpression
                        return (justUnicode1 == justUnicode2 || justUnicode2 == justUnicode1) ? false : true;
                    }
                }
                return false;
            }
    };

    // P-tB4003[a-c]
    class TestOneString_NotEqual : public TestOneString
    {
        public:
            explicit TestOneString_NotEqual(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: != Operator " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test that the != operator returns true between non-like strings.";
            }

            bool run() override {
                switch(stringType)
                {
                    case NO_UNICODE:
                    {
                        // cppcheck-suppress duplicateExpression
                        return (noUnicode1 != noUnicode2 && noUnicode2 != noUnicode1);
                    }
                    case SOME_UNICODE:
                    {
                        // cppcheck-suppress duplicateExpression
                        return (someUnicode1 != someUnicode2 && someUnicode2 != someUnicode1);
                    }
                    case JUST_UNICODE:
                    {
                        // cppcheck-suppress duplicateExpression
                        return (justUnicode1 != justUnicode2 && justUnicode2 != justUnicode1);
                    }
                }
                return false;
            }
    };

    // P-tB4004[a-c]
    class TestOneString_NotEqualFail : public TestOneString
    {
        public:
            explicit TestOneString_NotEqualFail(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: != Operator " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test that the != operator returns false between like strings.";
            }

            bool run() override {
                switch(stringType)
                {
                    case NO_UNICODE:
                    {
                        return (noUnicode1 != noUnicode1 || noUnicode2 != noUnicode2) ? false : true;
                    }
                    case SOME_UNICODE:
                    {
                        return (someUnicode1 != someUnicode1 || someUnicode2 != someUnicode2) ? false : true;
                    }
                    case JUST_UNICODE:
                    {
                        return (justUnicode1 != justUnicode1 || justUnicode2 != justUnicode2) ? false : true;
                    }
                }
                return false;
            }
    };

    // P-tB4005[a-c]
    class TestOneString_Equals : public TestOneString
    {
        public:
            explicit TestOneString_Equals(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: equals() " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test that the equal() function returns true between like strings.";
            }

            bool run() override {
                switch(stringType)
                {
                    case NO_UNICODE:
                    {
                        return (noUnicode1.equals(noUnicode1) && noUnicode2.equals(noUnicode2));
                    }
                    case SOME_UNICODE:
                    {
                        return (someUnicode1.equals(someUnicode1) && someUnicode2.equals(someUnicode2));
                    }
                    case JUST_UNICODE:
                    {
                        return (justUnicode1.equals(justUnicode1) && justUnicode2.equals(justUnicode2));
                    }
                }
                return false;
            }
    };

    // P-tB4006[a-c]
    class TestOneString_EqualsFail : public TestOneString
    {
        public:
            explicit TestOneString_EqualsFail(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: equals() Fail " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test that the equals() function returns false between non-like strings.";
            }

            bool run() override {
                switch(stringType)
                {
                    case NO_UNICODE:
                    {
                        return (noUnicode1.equals(noUnicode2) || noUnicode2.equals(noUnicode1)) ? false : true;
                    }
                    case SOME_UNICODE:
                    {
                        return (someUnicode1.equals(someUnicode2) || someUnicode2.equals(someUnicode1)) ? false : true;
                    }
                    case JUST_UNICODE:
                    {
                        return (justUnicode1.equals(justUnicode2) || justUnicode2.equals(justUnicode1)) ? false : true;
                    }
                }
                return false;
            }
    };

    // P-tB4007
    class TestOneString_Append : public Test
    {
        protected:
            OneString start = "Ø÷";
            OneString target1 = "Ø÷a";
            OneString target2 = "Ø÷aऐ";
            OneString test;
        public:
            TestOneString_Append(){}

            testdoc_t get_title() override
            {
                return "OneString: append()";
            }

            testdoc_t get_docs() override
            {
                return "Test for adding characters to a OneString with append()";
            }

            bool pre() override
            {
                return janitor();
            }

            bool janitor() override
            {
                test = start;
                return (test == start);
            }

            bool run() override
            {
                // Append a C char
                test.append('a');
                if(test != target1)
                {
                    return false;
                }

                // Append a Unicode character string literal
                test.append("ऐ");
                if(test != target2)
                {
                    return false;
                }

                return true;
            }
    };

    // P-tB4008
    class TestOneString_PopBack : public Test
    {
        protected:
            OneString start = "The quick brown 🦊 jumped over the lazy 🐶📣";
            OneString target = "The quick brown 🦊 jumped over the lazy 🐶";
            OneString test;

        public:
            TestOneString_PopBack(){}

            testdoc_t get_title() override
            {
                return "OneString: pop_back()";
            }

            testdoc_t get_docs() override
            {
                return "Tests for removing characters from a OneString using pop_back().";
            }

            bool pre() override
            {
                return janitor();
            }

            bool janitor() override
            {
                test = start;
                return (test == start);
            }

            bool run() override
            {
                test.pop_back();
                return (test == target);
            }
    };

    // P-tB4009
    class TestOneString_Length : public Test
    {
        protected:
            OneString start = "Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷";
            OneString test;

        public:
            TestOneString_Length(){}

            testdoc_t get_title() override
            {
                return "OneString: length()";
            }

            testdoc_t get_docs() override
            {
                return "Test the length() function.";
            }

            bool pre() override
            {
                return janitor();
            }

            bool janitor() override
            {
                test = start;
                return (test == start);
            }

            bool run() override
            {
                if (test.length() != 14)
                {
                    return false;
                }

                test.pop_back();

                if (test.length() != 13)
                {
                    return false;
                }

                return true;
            }
    };

    // P-tB4010
    class TestOneString_Empty : public Test
    {
        protected:
            OneString test = "";

        public:
            TestOneString_Empty(){}

            testdoc_t get_title() override
            {
                return "OneString: empty()";
            }

            testdoc_t get_docs() override
            {
                return "Test that the empty() function returns true on an empty string.";
            }

            bool run() override
            {
                return test.empty();
            }
    };

    // P-tB4011
    class TestOneString_EmptyFail : public Test
    {
        protected:
            OneString test = "a";

        public:
            TestOneString_EmptyFail(){}

            testdoc_t get_title() override
            {
                return "OneString: empty() Fail";
            }

            testdoc_t get_docs() override
            {
                return "Test that the empty() function returns false on a non-empty string.";
            }

            bool run() override
            {
                return (!test.empty());
            }
    };

    // P-tB4012
    class TestOneString_Insert : public Test
    {
        protected:
            OneString start = "Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷";
            OneString test;

        public:
            TestOneString_Insert(){}

            testdoc_t get_title() override
            {
                return "OneString: insert()";
            }

            testdoc_t get_docs() override
            {
                return "Test inserting characters in the middle of a OneString using insert().";
            }

            bool pre() override
            {
                return janitor();
            }

            bool janitor() override
            {
                test = start;
                return (test == start);
            }

            bool run() override
            {
                OneChar toInsert;
                toInsert = "Ø";
                OneChar toCheck;
                toCheck = "÷";
                test.insert(3, toInsert);

                if(test[3] != toInsert)
                {
                    return false;
                }
                if(test[2] != toCheck)
                {
                    return false;
                }
                if(test[4] != toCheck)
                {
                    return false;
                }

                return true;
            }
    };

    // P-tB4013
    class TestOneString_Clear : public Test
    {
        protected:
            OneString start = "Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷";
            OneString test;

        public:
            TestOneString_Clear(){}

            testdoc_t get_title() override
            {
                return "OneString: clear()";
            }

            testdoc_t get_docs() override
            {
                return "Tests for clearing all items in a OneString with clear().";
            }

            bool pre() override {
                return janitor();
            }

            bool janitor() override
            {
                test = start;
                return (!test.empty());
            }

            bool run() override
            {
                test.clear();
                return test.empty();
            }
    };

    // P-tB4014
    class TestOneString_Swap : public Test
    {
        protected:
            OneString beforeOne;
            OneString beforeTwo;
            OneString afterOne;
            OneString afterTwo;

        public:
            TestOneString_Swap(){}

            testdoc_t get_title() override
            {
                return "OneString: swap()";
            }

            testdoc_t get_docs() override
            {
                return "Test swapping two OneStrings.";
            }

            bool pre() override
            {
                return janitor();
            }

            bool janitor() override
            {
                beforeOne = "Pre Swap Ø";
                beforeTwo = "Ø Post Swap";
                afterOne = beforeOne;
                afterTwo = beforeTwo;
                return true;
            }

            bool run() override
            {
                beforeOne.swap(beforeTwo);

                if(beforeOne != afterTwo)
                {
                    return false;
                }
                if(beforeTwo != afterOne)
                {
                    return false;
                }

                return true;
            }
    };

    // P-tB4015
    class TestOneString_Substr : public Test
    {
        protected:
            OneString start = "⛰ The Matterhorn ⛰";

        public:
            TestOneString_Substr(){}

            testdoc_t get_title() override
            {
                return "OneString: substr()";
            }

            testdoc_t get_docs() override
            {
                return "Test creating a substring from a OneString.";
            }

            bool run() override
            {
                OneString partial = start.substr(12,4);
                return (partial == "horn");
            }
    };

    // P-tB4016
    class TestOneString_At : public Test
    {
        protected:
            OneString before = "⛰ The Matterhorn ⛰";

        public:
            TestOneString_At(){}

            testdoc_t get_title() override
            {
                return "OneString: at()";
            }

            testdoc_t get_docs() override
            {
                return "Test accessing one character of a OneString with at()";
            }

            bool run() override
            {
                OneChar toCheck;
                toCheck = "⛰";
                return (before.at(17) == toCheck);
            }
    };

    // P-tB4017
    class TestOneString_ForceResize : public Test
    {
        protected:
            OneString target = "🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉";
        public:
            TestOneString_ForceResize(){}

            testdoc_t get_title() override
            {
                return "OneString: Force Resize";
            }

            testdoc_t get_docs() override
            {
                return "Append characters to force resizing of the OneString's internal structure.";
            }

            bool run() override
            {
                OneString test;
                for (int i = 0; i < target.length(); ++i)
                {
                    test.append("🐉");
                }
                return (test == target);
            }
    };

    class TestSuite_OneString : public TestSuite
    {
        public:
            explicit TestSuite_OneString(){}

            void load_tests() override;

            testdoc_t get_title() override
            {
                return "PawLIB: OneString Tests";
            }
    };
}
#endif // PAWLIB_ONESTRING_TESTS_HPP
