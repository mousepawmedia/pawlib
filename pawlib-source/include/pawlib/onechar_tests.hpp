/** Tests for OneChar [PawLIB]
  * Version: 0.4
  *
  * Author(s): Jason C. McDonald
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

#ifndef PAWLIB_ONECHAR_TESTS_HPP
#define PAWLIB_ONECHAR_TESTS_HPP

#include "pawlib/goldilocks.hpp"
#include "pawlib/onestring.hpp"
#include "pawlib/iochannel.hpp"

using namespace pawlib::ioformat;
using namespace pawlib;

namespace pawlib
{
    class TestOneChar : public Test
    {
        public:
            enum TestCharType {
                CHAR,
                CSTR,
                STRING,
                ONECHAR
            };

            //🐭

        protected:
            TestCharType charType;

            testdoc_t title;

        public:
            explicit TestOneChar(TestCharType type)
            :charType(type)
            {
                switch(charType)
                {
                    case CHAR:
                    {
                        title = "(char)";
                        break;
                    }
                    case CSTR:
                    {
                        title = "(c-string)";
                        break;
                    }
                    case STRING:
                    {
                        title = "(std::string)";
                        break;
                    }
                    case ONECHAR:
                    {
                        title = "(OneChar)";
                        break;
                    }
                }
            }

            virtual testdoc_t get_title() override = 0;
            virtual testdoc_t get_docs() override = 0;
    };

    // P-tB4101
    class TestOneChar_EvaluateLength : public Test
    {
        public:
            TestOneChar_EvaluateLength(){}

            testdoc_t get_title() override
            {
                return "OneChar: Evaluate Length";
            }

            testdoc_t get_docs() override
            {
                return "Test that the OneChar::evaluateLength() function works correctly.";
            }

            bool run() override
            {
                PL_ASSERT_EQUAL(OneChar::evaluateLength("M"), 1u);
                PL_ASSERT_EQUAL(OneChar::evaluateLength("©"), 2u);
                PL_ASSERT_EQUAL(OneChar::evaluateLength("‽"), 3u);
                PL_ASSERT_EQUAL(OneChar::evaluateLength("🐭"), 4u);
                return true;
            }

            ~TestOneChar_EvaluateLength(){}
    };

    // c_str()
    class TestOneChar_CStr : public Test
    {
        protected:
            OneChar ch1 = "M";
            OneChar ch2 = "©";
            OneChar ch3 = "‽";
            OneChar ch4 = "🐭";

        public:
            TestOneChar_CStr(){}

            testdoc_t get_title() override
            {
                return "OneChar: C String";
            }

            testdoc_t get_docs() override
            {
                return "Test the c-string returned from a OneChar is accurate.";
            }

            bool run() override
            {
                PL_ASSERT_EQUAL(ch1.c_str(), "M");
                PL_ASSERT_EQUAL(ch2.c_str(), "©");
                PL_ASSERT_EQUAL(ch3.c_str(), "‽");
                PL_ASSERT_EQUAL(ch4.c_str(), "🐭");
                return true;
            }
    };

    class TestOneChar_Assign : public TestOneChar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOneChar_Assign(TestCharType type)
            : TestOneChar(type)
            {}

            testdoc_t get_title() override
            {
                return "OneChar: Assign " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test assigning data into a OneChar.";
            }

            bool run() override
            {
                OneChar test;
                switch(this->charType)
                {
                    case CHAR:
                    {
                        char ch = 'M';
                        test = ch;
                        PL_ASSERT_EQUAL(test.c_str(), "M");
                        return true;
                    }
                    case CSTR:
                    {
                        const char* cstr = "🐭";
                        test = cstr;
                        PL_ASSERT_EQUAL(test.c_str(), "🐭");
                        return true;
                    }
                    case STRING:
                    {
                        std::string str = "🐭";
                        test = str;
                        PL_ASSERT_EQUAL(test.c_str(), "🐭");
                        return true;
                    }
                    case ONECHAR:
                    {
                        OneChar ochr = "🐭";
                        test = ochr;
                        PL_ASSERT_EQUAL(test.c_str(), "🐭");
                        return true;
                    }
                    default:
                    {
                        // Can't reach.
                        return false;
                    }
                }
            }
    };

    class TestOneChar_Equals : public TestOneChar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOneChar_Equals(TestCharType type)
            : TestOneChar(type)
            {}

            testdoc_t get_title() override
            {
                return "OneChar: Equals (==) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the == operator.";
            }

            bool run() override
            {
                OneChar test;
                switch(this->charType)
                {
                    case CHAR:
                    {
                        char ch = 'M';
                        char ch_bad = 'X';
                        test = 'M';
                        PL_ASSERT_TRUE(test == ch);
                        PL_ASSERT_FALSE(test == ch_bad);
                        return true;
                    }
                    case CSTR:
                    {
                        const char* cstr = "🐭";
                        const char* cstr_double = "🐭🐭";
                        const char* cstr_bad = "©";
                        test = "🐭";
                        PL_ASSERT_TRUE(test == cstr);
                        PL_ASSERT_FALSE(test == cstr_double);
                        PL_ASSERT_FALSE(test == cstr_bad);
                        return true;
                    }
                    case STRING:
                    {
                        std::string str = "🐭";
                        std::string str_double = "🐭🐭";
                        std::string str_bad = "©";
                        test = "🐭";
                        PL_ASSERT_TRUE(test == str);
                        PL_ASSERT_FALSE(test == str_double);
                        PL_ASSERT_FALSE(test == str_bad);
                        return true;
                    }
                    case ONECHAR:
                    {
                        OneChar ochr = "🐭";
                        OneChar ochr_bad = "©";
                        test = "🐭";
                        PL_ASSERT_TRUE(test == ochr);
                        PL_ASSERT_FALSE(test == ochr_bad);
                        return true;
                    }
                    default:
                    {
                        // Can't reach.
                        return false;
                    }
                }
            }
    };

    class TestOneChar_NotEquals : public TestOneChar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOneChar_NotEquals(TestCharType type)
            : TestOneChar(type)
            {}

            testdoc_t get_title() override
            {
                return "OneChar: Not Equals (!=) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the != operator.";
            }

            bool run() override
            {
                OneChar test;
                switch(this->charType)
                {
                    case CHAR:
                    {
                        char ch = 'M';
                        char ch_bad = 'X';
                        test = 'M';
                        PL_ASSERT_FALSE(test != ch);
                        PL_ASSERT_TRUE(test != ch_bad);
                        return true;
                    }
                    case CSTR:
                    {
                        const char* cstr = "🐭";
                        const char* cstr_double = "🐭🐭";
                        const char* cstr_bad = "©";
                        test = "🐭";
                        PL_ASSERT_FALSE(test != cstr);
                        PL_ASSERT_TRUE(test != cstr_double);
                        PL_ASSERT_TRUE(test != cstr_bad);
                        return true;
                    }
                    case STRING:
                    {
                        std::string str = "🐭";
                        std::string str_double = "🐭🐭";
                        std::string str_bad = "©";
                        test = "🐭";
                        PL_ASSERT_FALSE(test != str);
                        PL_ASSERT_TRUE(test != str_double);
                        PL_ASSERT_TRUE(test != str_bad);
                        return true;
                    }
                    case ONECHAR:
                    {
                        OneChar ochr = "🐭";
                        OneChar ochr_bad = "©";
                        test = "🐭";
                        PL_ASSERT_FALSE(test != ochr);
                        PL_ASSERT_TRUE(test != ochr_bad);
                        return true;
                    }
                    default:
                    {
                        // Can't reach.
                        return false;
                    }
                }
            }
    };

    // compare char
    // compare char*
    // compare std::string
    // compare OneString

    class TestSuite_OneChar : public TestSuite
    {
        public:
            explicit TestSuite_OneChar(){}

            void load_tests() override;

            testdoc_t get_title() override
            {
                return "PawLIB: OneChar Tests";
            }
    };
}
#endif // PAWLIB_ONECHAR_TESTS_HPP
