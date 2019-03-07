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

    // P-tB4102
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
                const char* cstr = ch1.c_str();
                PL_ASSERT_EQUAL(cstr, "M");
                delete[] cstr;

                cstr = ch2.c_str();
                PL_ASSERT_EQUAL(cstr, "©");
                delete[] cstr;

                cstr = ch3.c_str();
                PL_ASSERT_EQUAL(cstr, "‽");
                delete[] cstr;

                cstr = ch4.c_str();
                PL_ASSERT_EQUAL(cstr, "🐭");
                delete[] cstr;

                return true;
            }
    };

    // P-tB4103[a-d]
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
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "M");
                        delete[] test_cstr;
                        return true;
                    }
                    case CSTR:
                    {
                        const char* cstr = "🐭";
                        test = cstr;
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "🐭");
                        delete[] test_cstr;
                        return true;
                    }
                    case STRING:
                    {
                        std::string str = "🐭";
                        test = str;
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "🐭");
                        delete[] test_cstr;
                        return true;
                    }
                    case ONECHAR:
                    {
                        OneChar ochr = "🐭";
                        test = ochr;
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "🐭");
                        delete[] test_cstr;
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

    // P-tB4104[a-d]
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

    // P-tB4105[a-d]
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

    // P-tB4101[a-d]
    class TestOneChar_Compare : public TestOneChar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOneChar_Compare(TestCharType type)
            : TestOneChar(type)
            {}

            testdoc_t get_title() override
            {
                return "OneChar: Compare " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the compare() function.";
            }

            bool run() override
            {
                OneChar test;
                switch(this->charType)
                {
                    case CHAR:
                    {
                        char ch_eq = 'M';
                        char ch_less = 'D';
                        char ch_more = 'm';
                        test = 'M';
                        PL_ASSERT_EQUAL(test.compare(ch_eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(ch_less), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(ch_more), 0);

                        PL_ASSERT_LESS(test.compare(ch_more), 0);
                        PL_ANTIASSERT_LESS(test.compare(ch_eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(ch_less), 0);

                        PL_ASSERT_GREATER(test.compare(ch_less), 0);
                        PL_ANTIASSERT_GREATER(test.compare(ch_eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(ch_more), 0);
                        return true;
                    }
                    case CSTR:
                    {
                        const char* cstr_eq = "🐭";
                        const char* cstr_less = "🐁";
                        const char* cstr_more = "🦊";
                        test = "🐭";
                        PL_ASSERT_EQUAL(test.compare(cstr_eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(cstr_less), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(cstr_more), 0);

                        PL_ASSERT_LESS(test.compare(cstr_more), 0);
                        PL_ANTIASSERT_LESS(test.compare(cstr_eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(cstr_less), 0);

                        PL_ASSERT_GREATER(test.compare(cstr_less), 0);
                        PL_ANTIASSERT_GREATER(test.compare(cstr_eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(cstr_more), 0);
                        return true;
                    }
                    case STRING:
                    {
                        std::string str_eq = "🐭";
                        std::string str_less = "🐁";
                        std::string str_more = "🦊";
                        test = "🐭";
                        PL_ASSERT_EQUAL(test.compare(str_eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(str_less), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(str_more), 0);

                        PL_ASSERT_LESS(test.compare(str_more), 0);
                        PL_ANTIASSERT_LESS(test.compare(str_eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(str_less), 0);

                        PL_ASSERT_GREATER(test.compare(str_less), 0);
                        PL_ANTIASSERT_GREATER(test.compare(str_eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(str_more), 0);
                        return true;
                    }
                    case ONECHAR:
                    {
                        OneChar ochr_eq = "🐭";
                        OneChar ochr_less = "🐁";
                        OneChar ochr_more = "🦊";
                        test = "🐭";
                        PL_ASSERT_EQUAL(test.compare(ochr_eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(ochr_less), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(ochr_more), 0);

                        PL_ASSERT_LESS(test.compare(ochr_more), 0);
                        PL_ANTIASSERT_LESS(test.compare(ochr_eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(ochr_less), 0);

                        PL_ASSERT_GREATER(test.compare(ochr_less), 0);
                        PL_ANTIASSERT_GREATER(test.compare(ochr_eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(ochr_more), 0);
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
