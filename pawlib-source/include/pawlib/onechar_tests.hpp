/** Tests for onechar [PawLIB]
  * Version: 0.4
  *
  * Author(s): Jason C. McDonald
  */

/* LICENSE
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

#ifndef PAWLIB_ONECHAR_TESTS_HPP
#define PAWLIB_ONECHAR_TESTS_HPP

#include "pawlib/goldilocks.hpp"
#include "pawlib/onestring.hpp"
#include "pawlib/iochannel.hpp"

using namespace pawlib;

namespace pawlib
{
    class TestOnechar : public Test
    {
        public:
            enum class TestCharType {
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
            explicit TestOnechar(TestCharType type)
            :charType(type)
            {
                switch(charType)
                {
                    case TestCharType::CHAR:
                    {
                        title = "(char)";
                        break;
                    }
                    case TestCharType::CSTR:
                    {
                        title = "(c-string)";
                        break;
                    }
                    case TestCharType::STRING:
                    {
                        title = "(std::string)";
                        break;
                    }
                    case TestCharType::ONECHAR:
                    {
                        title = "(onechar)";
                        break;
                    }
                }
            }

            virtual testdoc_t get_title() override = 0;
            virtual testdoc_t get_docs() override = 0;
    };

    // P-tB4101
    class TestOnechar_EvaluateLength : public Test
    {
        public:
            TestOnechar_EvaluateLength(){}

            testdoc_t get_title() override
            {
                return "Onechar: Evaluate Length";
            }

            testdoc_t get_docs() override
            {
                return "Test that the onechar::evaluateLength() function works correctly.";
            }

            bool run() override
            {
                PL_ASSERT_EQUAL(onechar::evaluateLength("M"), 1u);
                PL_ASSERT_EQUAL(onechar::evaluateLength("©"), 2u);
                PL_ASSERT_EQUAL(onechar::evaluateLength("‽"), 3u);
                PL_ASSERT_EQUAL(onechar::evaluateLength("🐭"), 4u);
                return true;
            }

            ~TestOnechar_EvaluateLength(){}
    };

    // P-tB4102
    class TestOnechar_CStr : public Test
    {
        protected:
            onechar ch1 = "M";
            onechar ch2 = "©";
            onechar ch3 = "‽";
            onechar ch4 = "🐭";

        public:
            TestOnechar_CStr(){}

            testdoc_t get_title() override
            {
                return "Onechar: C String";
            }

            testdoc_t get_docs() override
            {
                return "Test the c-string returned from a onechar is accurate.";
            }

            bool run() override
            {
                const char* cstr = ch1.c_str();
                PL_ASSERT_EQUAL(cstr, "M");

                cstr = ch2.c_str();
                PL_ASSERT_EQUAL(cstr, "©");

                cstr = ch3.c_str();
                PL_ASSERT_EQUAL(cstr, "‽");

                cstr = ch4.c_str();
                PL_ASSERT_EQUAL(cstr, "🐭");

                return true;
            }
    };

    // P-tB4103[a-d]
    class TestOnechar_Assign : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_Assign(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Assign " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test assigning data into a onechar.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch = 'M';
                        test = ch;
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "M");
                        return true;
                    }
                    case TestCharType::CSTR:
                    {
                        const char* cstr = "🐭";
                        test = cstr;
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "🐭");
                        return true;
                    }
                    case TestCharType::STRING:
                    {
                        std::string str = "🐭";
                        test = str;
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "🐭");
                        return true;
                    }
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr = "🐭";
                        test = ochr;
                        const char* test_cstr = test.c_str();
                        PL_ASSERT_EQUAL(test_cstr, "🐭");
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
    class TestOnechar_Equals : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_Equals(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Equals " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the equals() function.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch = 'M';
                        char ch_bad = 'X';
                        test = 'M';
                        PL_ASSERT_TRUE(test.equals(ch));
                        PL_ASSERT_FALSE(test.equals(ch_bad));
                        return true;
                    }
                    case TestCharType::CSTR:
                    {
                        const char* cstr = "🐭";
                        const char* cstr_double = "🐭🐭";
                        const char* cstr_bad = "©";
                        test = "🐭";
                        PL_ASSERT_TRUE(test.equals(cstr));
                        PL_ASSERT_FALSE(test.equals(cstr_double));
                        PL_ASSERT_FALSE(test.equals(cstr_bad));
                        return true;
                    }
                    case TestCharType::STRING:
                    {
                        std::string str = "🐭";
                        std::string str_double = "🐭🐭";
                        std::string str_bad = "©";
                        test = "🐭";
                        PL_ASSERT_TRUE(test.equals(str));
                        PL_ASSERT_FALSE(test.equals(str_double));
                        PL_ASSERT_FALSE(test.equals(str_bad));
                        return true;
                    }
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr = "🐭";
                        onechar ochr_bad = "©";
                        test = "🐭";
                        PL_ASSERT_TRUE(test.equals(ochr));
                        PL_ASSERT_FALSE(test.equals(ochr_bad));
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
    class TestOnechar_OpEquals : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_OpEquals(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Equals (==) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the == operator.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch = 'M';
                        char ch_bad = 'X';
                        test = 'M';
                        PL_ASSERT_TRUE(test == ch);
                        PL_ASSERT_FALSE(test == ch_bad);
                        return true;
                    }
                    case TestCharType::CSTR:
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
                    case TestCharType::STRING:
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
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr = "🐭";
                        onechar ochr_bad = "©";
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

    // P-tB4106[a-d]
    class TestOnechar_OpNotEquals : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_OpNotEquals(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Not Equals (!=) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the != operator.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch = 'M';
                        char ch_bad = 'X';
                        test = 'M';
                        PL_ASSERT_FALSE(test != ch);
                        PL_ASSERT_TRUE(test != ch_bad);
                        return true;
                    }
                    case TestCharType::CSTR:
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
                    case TestCharType::STRING:
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
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr = "🐭";
                        onechar ochr_bad = "©";
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

    // P-tB4107[a-d]
    class TestOnechar_Compare : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_Compare(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Compare " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the compare() function.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
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
                    case TestCharType::CSTR:
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
                    case TestCharType::STRING:
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
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr_eq = "🐭";
                        onechar ochr_less = "🐁";
                        onechar ochr_more = "🦊";
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

    // P-tB4108[a-d]
    class TestOnechar_OpLess : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_OpLess(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Less Than (<) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the < operator.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch_eq = 'M';
                        char ch_less = 'D';
                        char ch_more = 'm';
                        test = 'M';

                        PL_ASSERT_TRUE(test < ch_more);
                        PL_ASSERT_TRUE(ch_less < test);

                        PL_ASSERT_FALSE(test < ch_eq);
                        PL_ASSERT_FALSE(ch_eq < test);
                        return true;
                    }
                    case TestCharType::CSTR:
                    {
                        const char* cstr_eq = "🐭";
                        const char* cstr_less = "🐁";
                        const char* cstr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test < cstr_more);
                        PL_ASSERT_TRUE(cstr_less < test);

                        PL_ASSERT_FALSE(test < cstr_eq);
                        PL_ASSERT_FALSE(cstr_eq < test);
                        return true;
                    }
                    case TestCharType::STRING:
                    {
                        std::string str_eq = "🐭";
                        std::string str_less = "🐁";
                        std::string str_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test < str_more);
                        PL_ASSERT_TRUE(str_less < test);

                        PL_ASSERT_FALSE(test < str_eq);
                        PL_ASSERT_FALSE(str_eq < test);
                        return true;
                    }
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr_eq = "🐭";
                        onechar ochr_less = "🐁";
                        onechar ochr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test < ochr_more);
                        PL_ASSERT_TRUE(ochr_less < test);

                        PL_ASSERT_FALSE(test < ochr_eq);
                        PL_ASSERT_FALSE(ochr_eq < test);
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

    // P-tB4109[a-d]
    class TestOnechar_OpLessEqual : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_OpLessEqual(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Less/Equal (<=) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the <= operator.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch_eq = 'M';
                        char ch_less = 'D';
                        char ch_more = 'm';
                        test = 'M';

                        PL_ASSERT_TRUE(test <= ch_more);
                        PL_ASSERT_TRUE(ch_less <= test);

                        PL_ASSERT_TRUE(test <= ch_eq);
                        PL_ASSERT_TRUE(ch_eq <= test);

                        PL_ASSERT_FALSE(test <= ch_less);
                        PL_ASSERT_FALSE(ch_more <= test);
                        return true;
                    }
                    case TestCharType::CSTR:
                    {
                        const char* cstr_eq = "🐭";
                        const char* cstr_less = "🐁";
                        const char* cstr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test <= cstr_more);
                        PL_ASSERT_TRUE(cstr_less <= test);

                        PL_ASSERT_TRUE(test <= cstr_eq);
                        PL_ASSERT_TRUE(cstr_eq <= test);

                        PL_ASSERT_FALSE(test <= cstr_less);
                        PL_ASSERT_FALSE(cstr_more <= test);
                        return true;
                    }
                    case TestCharType::STRING:
                    {
                        std::string str_eq = "🐭";
                        std::string str_less = "🐁";
                        std::string str_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test <= str_more);
                        PL_ASSERT_TRUE(str_less <= test);

                        PL_ASSERT_TRUE(test <= str_eq);
                        PL_ASSERT_TRUE(str_eq <= test);

                        PL_ASSERT_FALSE(test <= str_less);
                        PL_ASSERT_FALSE(str_more <= test);
                        return true;
                    }
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr_eq = "🐭";
                        onechar ochr_less = "🐁";
                        onechar ochr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test <= ochr_more);
                        PL_ASSERT_TRUE(ochr_less <= test);

                        PL_ASSERT_TRUE(test <= ochr_eq);
                        PL_ASSERT_TRUE(ochr_eq <= test);

                        PL_ASSERT_FALSE(test <= ochr_less);
                        PL_ASSERT_FALSE(ochr_more <= test);
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

    // P-tB4110[a-d]
    class TestOnechar_OpGreater : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_OpGreater(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Greater Than (>) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the > operator.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch_eq = 'M';
                        char ch_less = 'D';
                        char ch_more = 'm';
                        test = 'M';

                        PL_ASSERT_TRUE(test > ch_less);
                        PL_ASSERT_TRUE(ch_more > test);

                        PL_ASSERT_FALSE(test > ch_eq);
                        PL_ASSERT_FALSE(ch_eq > test);
                        return true;
                    }
                    case TestCharType::CSTR:
                    {
                        const char* cstr_eq = "🐭";
                        const char* cstr_less = "🐁";
                        const char* cstr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test > cstr_less);
                        PL_ASSERT_TRUE(cstr_more > test);

                        PL_ASSERT_FALSE(test > cstr_eq);
                        PL_ASSERT_FALSE(cstr_eq > test);
                        return true;
                    }
                    case TestCharType::STRING:
                    {
                        std::string str_eq = "🐭";
                        std::string str_less = "🐁";
                        std::string str_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test > str_less);
                        PL_ASSERT_TRUE(str_more > test);

                        PL_ASSERT_FALSE(test > str_eq);
                        PL_ASSERT_FALSE(str_eq > test);
                        return true;
                    }
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr_eq = "🐭";
                        onechar ochr_less = "🐁";
                        onechar ochr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test > ochr_less);
                        PL_ASSERT_TRUE(ochr_more > test);

                        PL_ASSERT_FALSE(test > ochr_eq);
                        PL_ASSERT_FALSE(ochr_eq > test);
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

    // P-tB4111[a-d]
    class TestOnechar_OpGreaterEqual : public TestOnechar
    {
        public:
            // cppcheck-suppress noExplicitConstructor
            TestOnechar_OpGreaterEqual(TestCharType type)
            : TestOnechar(type)
            {}

            testdoc_t get_title() override
            {
                return "Onechar: Greater/Equal (>=) " + this->title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the >= operator.";
            }

            bool run() override
            {
                onechar test;
                switch(this->charType)
                {
                    case TestCharType::CHAR:
                    {
                        char ch_eq = 'M';
                        char ch_less = 'D';
                        char ch_more = 'm';
                        test = 'M';

                        PL_ASSERT_TRUE(test >= ch_less);
                        PL_ASSERT_TRUE(ch_more >= test);

                        PL_ASSERT_TRUE(test >= ch_eq);
                        PL_ASSERT_TRUE(ch_eq >= test);

                        PL_ASSERT_FALSE(test >= ch_more);
                        PL_ASSERT_FALSE(ch_less >= test);
                        return true;
                    }
                    case TestCharType::CSTR:
                    {
                        const char* cstr_eq = "🐭";
                        const char* cstr_less = "🐁";
                        const char* cstr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test >= cstr_less);
                        PL_ASSERT_TRUE(cstr_more >= test);

                        PL_ASSERT_TRUE(test >= cstr_eq);
                        PL_ASSERT_TRUE(cstr_eq >= test);

                        PL_ASSERT_FALSE(test >= cstr_more);
                        PL_ASSERT_FALSE(cstr_less >= test);
                        return true;
                    }
                    case TestCharType::STRING:
                    {
                        std::string str_eq = "🐭";
                        std::string str_less = "🐁";
                        std::string str_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test >= str_less);
                        PL_ASSERT_TRUE(str_more >= test);

                        PL_ASSERT_TRUE(test >= str_eq);
                        PL_ASSERT_TRUE(str_eq >= test);

                        PL_ASSERT_FALSE(test >= str_more);
                        PL_ASSERT_FALSE(str_less >= test);
                        return true;
                    }
                    case TestCharType::ONECHAR:
                    {
                        onechar ochr_eq = "🐭";
                        onechar ochr_less = "🐁";
                        onechar ochr_more = "🦊";
                        test = "🐭";

                        PL_ASSERT_TRUE(test >= ochr_less);
                        PL_ASSERT_TRUE(ochr_more >= test);

                        PL_ASSERT_TRUE(test >= ochr_eq);
                        PL_ASSERT_TRUE(ochr_eq >= test);

                        PL_ASSERT_FALSE(test >= ochr_more);
                        PL_ASSERT_FALSE(ochr_less >= test);
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

    class TestSuite_Onechar : public TestSuite
    {
        public:
            explicit TestSuite_Onechar(){}

            void load_tests() override;

            testdoc_t get_title() override
            {
                return "PawLIB: Onechar Tests";
            }
    };
}
#endif // PAWLIB_ONECHAR_TESTS_HPP
