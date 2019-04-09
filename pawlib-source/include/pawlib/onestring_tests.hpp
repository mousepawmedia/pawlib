/** Tests for OneString [PawLIB]
  * Version: 0.4
  *
  * Author(s): Jason C. McDonald, Scott Taylor, Bo Volwiler
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

#ifndef PAWLIB_ONESTRING_TESTS_HPP
#define PAWLIB_ONESTRING_TESTS_HPP

#include <string>

#include "pawlib/goldilocks.hpp"
#include "pawlib/onestring.hpp"

using namespace pawlib::ioformat;
using namespace pawlib;

namespace pawlib
{
    class TestOneString : public Test
    {
        public:
            enum TestStringType {
                CHAR,
                OCHAR_ASCII,
                OCHAR_UNICODE,
                CSTR_ASCII,
                CSTR_UNICODE,
                STR_ASCII,
                STR_UNICODE,
                OSTR_ASCII,
                OSTR_UNICODE
            };

            char ch_1 = 'M';
            char ch_2 = 'm';

            OneChar ochr_ascii_1 = "M";
            OneChar ochr_ascii_2 = "m";

            OneChar ochr_unicode_1 = "🐭";
            OneChar ochr_unicode_2 = "🦊";

            OneString ostr_ch_ascii_1 = "M";
            OneString ostr_ch_ascii_2 = "m";
            OneString ostr_ch_unicode_1 = "🐭";
            OneString ostr_ch_unicode_2 = "🦊";

            // We'll extract the c-strings from these as needed.
            std::string str_ascii_1 = "The quick brown fox jumped over the lazy dog.";
            std::string str_unicode_1 = "The quick brown 🦊 jumped over the lazy 🐶.";
            std::string str_ascii_2 = "Jackdaws love my big sphinx of quartz.";
            std::string str_unicode_2 = "🐦 ❤️ my big sphinx of 💎.";

            OneString ostr_ascii_1 = "The quick brown fox jumped over the lazy dog.";
            OneString ostr_unicode_1 = "The quick brown 🦊 jumped over the lazy 🐶.";
            OneString ostr_ascii_2 = "Jackdaws love my big sphinx of quartz.";
            OneString ostr_unicode_2 = "🐦 ❤️ my big sphinx of 💎.";

        protected:
            TestStringType stringType;

            testdoc_t title;

        public:
            explicit TestOneString(TestStringType type)
            :stringType(type)
            {
                switch(stringType)
                {
                    case CHAR:
                    {
                        title = "(char)";
                        break;
                    }
                    case OCHAR_ASCII:
                    {
                        title = "(OneChar, ASCII)";
                        break;
                    }
                    case OCHAR_UNICODE:
                    {
                        title = "(OneChar, Unicode)";
                        break;
                    }
                    case CSTR_ASCII:
                    {
                        title = "(c-string, ASCII)";
                        break;
                    }
                    case CSTR_UNICODE:
                    {
                        title = "(c-string, Unicode)";
                        break;
                    }
                    case STR_ASCII:
                    {
                        title = "(std::string, ASCII)";
                        break;
                    }
                    case STR_UNICODE:
                    {
                        title = "(std::string, Unicode)";
                        break;
                    }
                    case OSTR_ASCII:
                    {
                        title = "(OneString, ASCII)";
                        break;
                    }
                    case OSTR_UNICODE:
                    {
                        title = "(OneString, Unicode)";
                        break;
                    }
                }
            }

            virtual testdoc_t get_title() override = 0;

            virtual testdoc_t get_docs() override = 0;
    };

    // P-tB4001[a-i]
    class TestOneString_Assign : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_Assign(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Assign " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test assignment to a OneString.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        test.assign(ch_1);
                        PL_ASSERT_EQUAL(test, ostr_ch_ascii_1);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        test.assign(ochr_ascii_1);
                        PL_ASSERT_EQUAL(test, ostr_ch_ascii_1);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        test.assign(ochr_unicode_1);
                        PL_ASSERT_EQUAL(test, ostr_ch_unicode_1);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        test.assign(str_ascii_1.c_str());
                        PL_ASSERT_EQUAL(test, ostr_ascii_1);
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        test.assign(str_unicode_1.c_str());
                        PL_ASSERT_EQUAL(test, ostr_unicode_1);
                        return true;
                    }
                    case STR_ASCII:
                    {
                        test.assign(str_ascii_1);
                        PL_ASSERT_EQUAL(test, ostr_ascii_1);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        test.assign(str_unicode_1);
                        PL_ASSERT_EQUAL(test, ostr_unicode_1);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        test.assign(ostr_ascii_1);
                        PL_ASSERT_EQUAL(test, ostr_ascii_1);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        test.assign(ostr_unicode_1);
                        PL_ASSERT_EQUAL(test, ostr_unicode_1);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4002[a-i]
    class TestOneString_Equals : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_Equals(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Equals " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the equals() function.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        test = ch_1;
                        PL_ASSERT_TRUE(test.equals(ch_1));
                        PL_ASSERT_FALSE(test.equals(ch_2));
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        test = ochr_ascii_1;
                        PL_ASSERT_TRUE(test.equals(ochr_ascii_1));
                        PL_ASSERT_FALSE(test.equals(ochr_ascii_2));
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        test = ochr_unicode_1;
                        PL_ASSERT_TRUE(test.equals(ochr_unicode_1));
                        PL_ASSERT_FALSE(test.equals(ochr_unicode_2));
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        test = str_ascii_1;
                        PL_ASSERT_TRUE(test.equals(str_ascii_1.c_str()));
                        PL_ASSERT_FALSE(test.equals(str_ascii_2.c_str()));
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        test = str_unicode_1;
                        PL_ASSERT_TRUE(test.equals(str_unicode_1.c_str()));
                        PL_ASSERT_FALSE(test.equals(str_unicode_2.c_str()));
                        return true;
                    }
                    case STR_ASCII:
                    {
                        test = str_ascii_1;
                        PL_ASSERT_TRUE(test.equals(str_ascii_1));
                        PL_ASSERT_FALSE(test.equals(str_ascii_2));
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        test = str_unicode_1;
                        PL_ASSERT_TRUE(test.equals(str_unicode_1));
                        PL_ASSERT_FALSE(test.equals(str_unicode_2));
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        test = ostr_ascii_1;
                        PL_ASSERT_TRUE(test.equals(ostr_ascii_1));
                        PL_ASSERT_FALSE(test.equals(ostr_ascii_2));
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        test = ostr_unicode_1;
                        PL_ASSERT_TRUE(test.equals(ostr_unicode_1));
                        PL_ASSERT_FALSE(test.equals(ostr_unicode_2));
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4003[a-i]
    class TestOneString_OpEquals : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_OpEquals(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Equals (==) " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the == operator.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        test = ch_1;
                        PL_ASSERT_TRUE(test == ch_1);
                        PL_ASSERT_FALSE(test == ch_2);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        test = ochr_ascii_1;
                        PL_ASSERT_TRUE(test == ochr_ascii_1);
                        PL_ASSERT_FALSE(test == ochr_ascii_2);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        test = ochr_unicode_1;
                        PL_ASSERT_TRUE(test == ochr_unicode_1);
                        PL_ASSERT_FALSE(test == ochr_unicode_2);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        test = str_ascii_1;
                        PL_ASSERT_TRUE(test == str_ascii_1.c_str());
                        PL_ASSERT_FALSE(test == str_ascii_2.c_str());
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        test = str_unicode_1;
                        PL_ASSERT_TRUE(test == str_unicode_1.c_str());
                        PL_ASSERT_FALSE(test == str_unicode_2.c_str());
                        return true;
                    }
                    case STR_ASCII:
                    {
                        test = str_ascii_1;
                        PL_ASSERT_TRUE(test == str_ascii_1);
                        PL_ASSERT_FALSE(test == str_ascii_2);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        test = str_unicode_1;
                        PL_ASSERT_TRUE(test == str_unicode_1);
                        PL_ASSERT_FALSE(test == str_unicode_2);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        test = ostr_ascii_1;
                        PL_ASSERT_TRUE(test == ostr_ascii_1);
                        PL_ASSERT_FALSE(test == ostr_ascii_2);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        test = ostr_unicode_1;
                        PL_ASSERT_TRUE(test == ostr_unicode_1);
                        PL_ASSERT_FALSE(test == ostr_unicode_2);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4004[a-i]
    class TestOneString_OpNotEquals : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_OpNotEquals(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Not Equals (!=) " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the != operator.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        test = ch_1;
                        PL_ASSERT_TRUE(test != ch_2);
                        PL_ASSERT_FALSE(test != ch_1);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        test = ochr_ascii_1;
                        PL_ASSERT_TRUE(test != ochr_ascii_2);
                        PL_ASSERT_FALSE(test != ochr_ascii_1);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        test = ochr_unicode_1;
                        PL_ASSERT_TRUE(test != ochr_unicode_2);
                        PL_ASSERT_FALSE(test != ochr_unicode_1);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        test = str_ascii_1;
                        PL_ASSERT_TRUE(test != str_ascii_2.c_str());
                        PL_ASSERT_FALSE(test != str_ascii_1.c_str());
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        test = str_unicode_1;
                        PL_ASSERT_TRUE(test != str_unicode_2.c_str());
                        PL_ASSERT_FALSE(test != str_unicode_1.c_str());
                        return true;
                    }
                    case STR_ASCII:
                    {
                        test = str_ascii_1;
                        PL_ASSERT_TRUE(test != str_ascii_2);
                        PL_ASSERT_FALSE(test != str_ascii_1);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        test = str_unicode_1;
                        PL_ASSERT_TRUE(test != str_unicode_2);
                        PL_ASSERT_FALSE(test != str_unicode_1);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        test = ostr_ascii_1;
                        PL_ASSERT_TRUE(test != ostr_ascii_2);
                        PL_ASSERT_FALSE(test != ostr_ascii_1);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        test = ostr_unicode_1;
                        PL_ASSERT_TRUE(test != ostr_unicode_2);
                        PL_ASSERT_FALSE(test != ostr_unicode_1);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4005[a-i]
    class TestOneString_Compare : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_Compare(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Compare " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the compare() function.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        char eq = 'B';
                        char lt = 'A';
                        char gt = 'C';

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt), 0);

                        PL_ASSERT_LESS(test.compare(gt), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt), 0);

                        PL_ASSERT_GREATER(test.compare(lt), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt), 0);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        OneChar eq = "B";
                        OneChar lt = "A";
                        OneChar gt = "C";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt), 0);

                        PL_ASSERT_LESS(test.compare(gt), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt), 0);

                        PL_ASSERT_GREATER(test.compare(lt), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt), 0);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        OneChar eq = "🐭";
                        OneChar lt = "🐁";
                        OneChar gt = "🦊";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt), 0);

                        PL_ASSERT_LESS(test.compare(gt), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt), 0);

                        PL_ASSERT_GREATER(test.compare(lt), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt), 0);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(shorter.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(longer.c_str()), 0);

                        PL_ASSERT_LESS(test.compare(gt.c_str()), 0);
                        PL_ASSERT_LESS(test.compare(longer.c_str()), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq.c_str()), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt.c_str()), 0);
                        PL_ANTIASSERT_LESS(test.compare(shorter.c_str()), 0);

                        PL_ASSERT_GREATER(test.compare(lt.c_str()), 0);
                        PL_ASSERT_GREATER(test.compare(shorter.c_str()), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq.c_str()), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt.c_str()), 0);
                        PL_ANTIASSERT_GREATER(test.compare(longer.c_str()), 0);
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(shorter.c_str()), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(longer.c_str()), 0);

                        PL_ASSERT_LESS(test.compare(gt.c_str()), 0);
                        PL_ASSERT_LESS(test.compare(longer.c_str()), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq.c_str()), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt.c_str()), 0);
                        PL_ANTIASSERT_LESS(test.compare(shorter.c_str()), 0);

                        PL_ASSERT_GREATER(test.compare(lt.c_str()), 0);
                        PL_ASSERT_GREATER(test.compare(shorter.c_str()), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq.c_str()), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt.c_str()), 0);
                        PL_ANTIASSERT_GREATER(test.compare(longer.c_str()), 0);
                        return true;
                    }
                    case STR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

                        PL_ASSERT_LESS(test.compare(gt), 0);
                        PL_ASSERT_LESS(test.compare(longer), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt), 0);
                        PL_ANTIASSERT_LESS(test.compare(shorter), 0);

                        PL_ASSERT_GREATER(test.compare(lt), 0);
                        PL_ASSERT_GREATER(test.compare(shorter), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt), 0);
                        PL_ANTIASSERT_GREATER(test.compare(longer), 0);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "🐭ab";
                        std::string longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

                        PL_ASSERT_LESS(test.compare(gt), 0);
                        PL_ASSERT_LESS(test.compare(longer), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt), 0);
                        PL_ANTIASSERT_LESS(test.compare(shorter), 0);

                        PL_ASSERT_GREATER(test.compare(lt), 0);
                        PL_ASSERT_GREATER(test.compare(shorter), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt), 0);
                        PL_ANTIASSERT_GREATER(test.compare(longer), 0);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        OneString eq = "abcB";
                        OneString lt = "abcA";
                        OneString gt = "abcC";
                        OneString shorter = "ab";
                        OneString longer = "abcabc";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

                        PL_ASSERT_LESS(test.compare(gt), 0);
                        PL_ASSERT_LESS(test.compare(longer), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt), 0);
                        PL_ANTIASSERT_LESS(test.compare(shorter), 0);

                        PL_ASSERT_GREATER(test.compare(lt), 0);
                        PL_ASSERT_GREATER(test.compare(shorter), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt), 0);
                        PL_ANTIASSERT_GREATER(test.compare(longer), 0);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        OneString eq = "🐭abc🐭";
                        OneString lt = "🐭abc🐁";
                        OneString gt = "🐭abc🦊";
                        OneString shorter = "🐭ab";
                        OneString longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_EQUAL(test.compare(eq), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
                        PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

                        PL_ASSERT_LESS(test.compare(gt), 0);
                        PL_ASSERT_LESS(test.compare(longer), 0);
                        PL_ANTIASSERT_LESS(test.compare(eq), 0);
                        PL_ANTIASSERT_LESS(test.compare(lt), 0);
                        PL_ANTIASSERT_LESS(test.compare(shorter), 0);

                        PL_ASSERT_GREATER(test.compare(lt), 0);
                        PL_ASSERT_GREATER(test.compare(shorter), 0);
                        PL_ANTIASSERT_GREATER(test.compare(eq), 0);
                        PL_ANTIASSERT_GREATER(test.compare(gt), 0);
                        PL_ANTIASSERT_GREATER(test.compare(longer), 0);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4006[a-i]
    class TestOneString_OpLess : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_OpLess(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Less Than (<) " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the < operator.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        char eq = 'B';
                        char lt = 'A';
                        char gt = 'C';

                        test = eq;
                        PL_ASSERT_TRUE(test < gt);
                        PL_ASSERT_FALSE(test < eq);
                        PL_ASSERT_FALSE(test < lt);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        OneChar eq = "B";
                        OneChar lt = "A";
                        OneChar gt = "C";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt);
                        PL_ASSERT_FALSE(test < eq);
                        PL_ASSERT_FALSE(test < lt);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        OneChar eq = "🐭";
                        OneChar lt = "🐁";
                        OneChar gt = "🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt);
                        PL_ASSERT_FALSE(test < eq);
                        PL_ASSERT_FALSE(test < lt);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt.c_str());
                        PL_ASSERT_TRUE(test < longer.c_str());
                        PL_ASSERT_FALSE(test < eq.c_str());
                        PL_ASSERT_FALSE(test < lt.c_str());
                        PL_ASSERT_FALSE(test < shorter.c_str());
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt.c_str());
                        PL_ASSERT_TRUE(test < longer.c_str());
                        PL_ASSERT_FALSE(test < eq.c_str());
                        PL_ASSERT_FALSE(test < lt.c_str());
                        PL_ASSERT_FALSE(test < shorter.c_str());
                        return true;
                    }
                    case STR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt);
                        PL_ASSERT_TRUE(test < longer);
                        PL_ASSERT_FALSE(test < eq);
                        PL_ASSERT_FALSE(test < lt);
                        PL_ASSERT_FALSE(test < shorter);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "🐭ab";
                        std::string longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt);
                        PL_ASSERT_TRUE(test < longer);
                        PL_ASSERT_FALSE(test < eq);
                        PL_ASSERT_FALSE(test < lt);
                        PL_ASSERT_FALSE(test < shorter);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        OneString eq = "abcB";
                        OneString lt = "abcA";
                        OneString gt = "abcC";
                        OneString shorter = "ab";
                        OneString longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt);
                        PL_ASSERT_TRUE(test < longer);
                        PL_ASSERT_FALSE(test < eq);
                        PL_ASSERT_FALSE(test < lt);
                        PL_ASSERT_FALSE(test < shorter);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        OneString eq = "🐭abc🐭";
                        OneString lt = "🐭abc🐁";
                        OneString gt = "🐭abc🦊";
                        OneString shorter = "🐭ab";
                        OneString longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test < gt);
                        PL_ASSERT_TRUE(test < longer);
                        PL_ASSERT_FALSE(test < eq);
                        PL_ASSERT_FALSE(test < lt);
                        PL_ASSERT_FALSE(test < shorter);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4007[a-i]
    class TestOneString_OpLessEqual : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_OpLessEqual(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Less/Equal (<=) " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the <= operator.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        char eq = 'B';
                        char lt = 'A';
                        char gt = 'C';

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt);
                        PL_ASSERT_TRUE(test <= eq);
                        PL_ASSERT_FALSE(test <= lt);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        OneChar eq = "B";
                        OneChar lt = "A";
                        OneChar gt = "C";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt);
                        PL_ASSERT_TRUE(test <= eq);
                        PL_ASSERT_FALSE(test <= lt);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        OneChar eq = "🐭";
                        OneChar lt = "🐁";
                        OneChar gt = "🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt);
                        PL_ASSERT_TRUE(test <= eq);
                        PL_ASSERT_FALSE(test <= lt);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt.c_str());
                        PL_ASSERT_TRUE(test <= longer.c_str());
                        PL_ASSERT_TRUE(test <= eq.c_str());
                        PL_ASSERT_FALSE(test <= lt.c_str());
                        PL_ASSERT_FALSE(test <= shorter.c_str());
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt.c_str());
                        PL_ASSERT_TRUE(test <= longer.c_str());
                        PL_ASSERT_TRUE(test <= eq.c_str());
                        PL_ASSERT_FALSE(test <= lt.c_str());
                        PL_ASSERT_FALSE(test <= shorter.c_str());
                        return true;
                    }
                    case STR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt);
                        PL_ASSERT_TRUE(test <= longer);
                        PL_ASSERT_TRUE(test <= eq);
                        PL_ASSERT_FALSE(test <= lt);
                        PL_ASSERT_FALSE(test <= shorter);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "🐭ab";
                        std::string longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt);
                        PL_ASSERT_TRUE(test <= longer);
                        PL_ASSERT_TRUE(test <= eq);
                        PL_ASSERT_FALSE(test <= lt);
                        PL_ASSERT_FALSE(test <= shorter);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        OneString eq = "abcB";
                        OneString lt = "abcA";
                        OneString gt = "abcC";
                        OneString shorter = "ab";
                        OneString longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt);
                        PL_ASSERT_TRUE(test <= longer);
                        PL_ASSERT_TRUE(test <= eq);
                        PL_ASSERT_FALSE(test <= lt);
                        PL_ASSERT_FALSE(test <= shorter);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        OneString eq = "🐭abc🐭";
                        OneString lt = "🐭abc🐁";
                        OneString gt = "🐭abc🦊";
                        OneString shorter = "🐭ab";
                        OneString longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test <= gt);
                        PL_ASSERT_TRUE(test <= longer);
                        PL_ASSERT_TRUE(test <= eq);
                        PL_ASSERT_FALSE(test <= lt);
                        PL_ASSERT_FALSE(test <= shorter);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4008[a-i]
    class TestOneString_OpGreater : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_OpGreater(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Less Than (>) " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the > operator.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        char eq = 'B';
                        char lt = 'A';
                        char gt = 'C';

                        test = eq;
                        PL_ASSERT_TRUE(test > lt);
                        PL_ASSERT_FALSE(test > eq);
                        PL_ASSERT_FALSE(test > gt);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        OneChar eq = "B";
                        OneChar lt = "A";
                        OneChar gt = "C";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt);
                        PL_ASSERT_FALSE(test > eq);
                        PL_ASSERT_FALSE(test > gt);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        OneChar eq = "🐭";
                        OneChar lt = "🐁";
                        OneChar gt = "🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt);
                        PL_ASSERT_FALSE(test > eq);
                        PL_ASSERT_FALSE(test > gt);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt.c_str());
                        PL_ASSERT_TRUE(test > shorter.c_str());
                        PL_ASSERT_FALSE(test > eq.c_str());
                        PL_ASSERT_FALSE(test > gt.c_str());
                        PL_ASSERT_FALSE(test > longer.c_str());
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt.c_str());
                        PL_ASSERT_TRUE(test > shorter.c_str());
                        PL_ASSERT_FALSE(test > eq.c_str());
                        PL_ASSERT_FALSE(test > gt.c_str());
                        PL_ASSERT_FALSE(test > longer.c_str());
                        return true;
                    }
                    case STR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt);
                        PL_ASSERT_TRUE(test > shorter);
                        PL_ASSERT_FALSE(test > eq);
                        PL_ASSERT_FALSE(test > gt);
                        PL_ASSERT_FALSE(test > longer);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "🐭ab";
                        std::string longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt);
                        PL_ASSERT_TRUE(test > shorter);
                        PL_ASSERT_FALSE(test > eq);
                        PL_ASSERT_FALSE(test > gt);
                        PL_ASSERT_FALSE(test > longer);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        OneString eq = "abcB";
                        OneString lt = "abcA";
                        OneString gt = "abcC";
                        OneString shorter = "ab";
                        OneString longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt);
                        PL_ASSERT_TRUE(test > shorter);
                        PL_ASSERT_FALSE(test > eq);
                        PL_ASSERT_FALSE(test > gt);
                        PL_ASSERT_FALSE(test > longer);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        OneString eq = "🐭abc🐭";
                        OneString lt = "🐭abc🐁";
                        OneString gt = "🐭abc🦊";
                        OneString shorter = "🐭ab";
                        OneString longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test > lt);
                        PL_ASSERT_TRUE(test > shorter);
                        PL_ASSERT_FALSE(test > eq);
                        PL_ASSERT_FALSE(test > gt);
                        PL_ASSERT_FALSE(test > longer);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4009[a-i]
    class TestOneString_OpGreaterEqual : public TestOneString
    {
        protected:
            OneString test;

        public:
            explicit TestOneString_OpGreaterEqual(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Greater/Equal (>=) " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test comparison with the >= operator.";
            }

            bool janitor() override {
                OneString test = "";
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        char eq = 'B';
                        char lt = 'A';
                        char gt = 'C';

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt);
                        PL_ASSERT_TRUE(test >= eq);
                        PL_ASSERT_FALSE(test >= gt);
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        OneChar eq = "B";
                        OneChar lt = "A";
                        OneChar gt = "C";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt);
                        PL_ASSERT_TRUE(test >= eq);
                        PL_ASSERT_FALSE(test >= gt);
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        OneChar eq = "🐭";
                        OneChar lt = "🐁";
                        OneChar gt = "🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt);
                        PL_ASSERT_TRUE(test >= eq);
                        PL_ASSERT_FALSE(test >= gt);
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt.c_str());
                        PL_ASSERT_TRUE(test >= shorter.c_str());
                        PL_ASSERT_TRUE(test >= eq.c_str());
                        PL_ASSERT_FALSE(test >= gt.c_str());
                        PL_ASSERT_FALSE(test >= longer.c_str());
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt.c_str());
                        PL_ASSERT_TRUE(test >= shorter.c_str());
                        PL_ASSERT_TRUE(test >= eq.c_str());
                        PL_ASSERT_FALSE(test >= gt.c_str());
                        PL_ASSERT_FALSE(test >= longer.c_str());
                        return true;
                    }
                    case STR_ASCII:
                    {
                        std::string eq = "abcB";
                        std::string lt = "abcA";
                        std::string gt = "abcC";
                        std::string shorter = "ab";
                        std::string longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt);
                        PL_ASSERT_TRUE(test >= shorter);
                        PL_ASSERT_TRUE(test >= eq);
                        PL_ASSERT_FALSE(test >= gt);
                        PL_ASSERT_FALSE(test >= longer);
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        std::string eq = "🐭abc🐭";
                        std::string lt = "🐭abc🐁";
                        std::string gt = "🐭abc🦊";
                        std::string shorter = "🐭ab";
                        std::string longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt);
                        PL_ASSERT_TRUE(test >= shorter);
                        PL_ASSERT_TRUE(test >= eq);
                        PL_ASSERT_FALSE(test >= gt);
                        PL_ASSERT_FALSE(test >= longer);
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        OneString eq = "abcB";
                        OneString lt = "abcA";
                        OneString gt = "abcC";
                        OneString shorter = "ab";
                        OneString longer = "abcabc";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt);
                        PL_ASSERT_TRUE(test >= shorter);
                        PL_ASSERT_TRUE(test >= eq);
                        PL_ASSERT_FALSE(test >= gt);
                        PL_ASSERT_FALSE(test >= longer);
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        OneString eq = "🐭abc🐭";
                        OneString lt = "🐭abc🐁";
                        OneString gt = "🐭abc🦊";
                        OneString shorter = "🐭ab";
                        OneString longer = "🐭abc🦊🦊";

                        test = eq;
                        PL_ASSERT_TRUE(test >= lt);
                        PL_ASSERT_TRUE(test >= shorter);
                        PL_ASSERT_TRUE(test >= eq);
                        PL_ASSERT_FALSE(test >= gt);
                        PL_ASSERT_FALSE(test >= longer);
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4010
    class TestOneString_At : public Test
    {
        protected:
            OneString test = "⛰ The Matterhorn ⛰";

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
                PL_ASSERT_EQUAL(test.at(17), toCheck);
                return true;
            }
    };

    // P-tB4011
    class TestOneString_OpAt : public Test
    {
        protected:
            OneString test = "⛰ The Matterhorn ⛰";

        public:
            TestOneString_OpAt(){}

            testdoc_t get_title() override
            {
                return "OneString: at ([])";
            }

            testdoc_t get_docs() override
            {
                return "Test accessing one character of a OneString with the [] operator.";
            }

            bool run() override
            {
                OneChar toCheck;
                toCheck = "⛰";
                PL_ASSERT_EQUAL(test[17], toCheck);
                return true;
            }
    };

    // P-tB4012
    class TestOneString_Capacity : public Test
    {
        protected:
            OneString test = "🐦 ❤️ my big sphinx of 💎.";

        public:
            TestOneString_Capacity(){}

            testdoc_t get_title() override
            {
                return "OneString: at ([])";
            }

            testdoc_t get_docs() override
            {
                return "Test accessing one character of a OneString with the [] operator.";
            }

            bool run() override
            {
                size_t expected_capacity = OneString::BASE_SIZE;
                size_t string_length = test.length();
                while (expected_capacity < string_length)
                {
                    expected_capacity *= OneString::RESIZE_FACTOR;
                }
                PL_ASSERT_EQUAL(test.capacity(), expected_capacity);
                return true;
            }
    };

    // P-tB4013
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
                PL_ASSERT_EQUAL(test, target);
                return true;
            }
    };

    // P-tB4014
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
                PL_ASSERT_EQUAL(test.length(), 14U);
                test.pop_back();
                PL_ASSERT_EQUAL(test.length(), 13U);
                return true;
            }
    };

    // P-tB4015
    class TestOneString_Size : public Test
    {
        protected:
            OneString start = "M©‽🐭‽©M";
            OneString test;

        public:
            TestOneString_Size(){}

            testdoc_t get_title() override
            {
                return "OneString: size()";
            }

            testdoc_t get_docs() override
            {
                return "Test the size() function.";
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
                PL_ASSERT_EQUAL(test.size(4), 11u);
                PL_ASSERT_EQUAL(test.size(4, 3), 11u);

                PL_ASSERT_EQUAL(test.size(), 17u);
                // Remove last 'M' (1 byte)
                test.pop_back();
                PL_ASSERT_EQUAL(test.size(), 16u);
                // Remove last '©' (2 bytes)
                test.pop_back();
                PL_ASSERT_EQUAL(test.size(), 14u);
                // Remove last '‽' (3 bytes)
                test.pop_back();
                PL_ASSERT_EQUAL(test.size(), 11u);
                // Remove last '🐭' (4 bytes)
                test.pop_back();
                PL_ASSERT_EQUAL(test.size(), 7u);
                return true;
            }
    };

    // P-tB4016
    class TestOneString_Copy : public Test
    {
        protected:
            OneString test = "🐦 ❤ my big sphinx of 💎.";
            OneString sub1 = "🐦 ❤"; //3, 0
            OneString sub2 = "of 💎"; //4, 18

        public:
            TestOneString_Copy(){}

            testdoc_t get_title() override
            {
                return "OneString: copy()";
            }

            testdoc_t get_docs() override
            {
                return "Test copying to a c-string with copy().";
            }

            bool run() override
            {
                // Test copying the entire string.
                char* cstr = new char[test.size()];
                test.copy(cstr, test.size());
                PL_ASSERT_TRUE(test.equals(cstr));
                delete[] cstr;

                // Test copying substring 1
                cstr = new char[test.size(3, 0)];
                test.copy(cstr, test.size(3, 0), 3, 0);
                PL_ASSERT_TRUE(sub1.equals(cstr));
                delete[] cstr;

                // Test copying substring 2
                cstr = new char[test.size(4, 18)];
                test.copy(cstr, test.size(4, 18), 4, 18);
                PL_ASSERT_TRUE(sub2.equals(cstr));
                delete[] cstr;

                return true;
            }
    };

    // P-tB4017
    class TestOneString_CStr : public Test
    {
        public:
            TestOneString_CStr(){}

            testdoc_t get_title() override
            {
                return "OneString: c_str()";
            }

            testdoc_t get_docs() override
            {
                return "Test the c-string returned by the c_str() function.";
            }

            bool run() override
            {
                const char* cstr = "The quick brown 🦊 jumped over the lazy 🐶.";
                OneString test = cstr;
                PL_ASSERT_EQUAL(strcmp(cstr, test.c_str()), 0);
                return true;
            }
    };

    // P-tB4018
    class TestOneString_Empty : public Test
    {
        protected:
            OneString test1 = "";
            OneString test2 = "a";

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
                PL_ASSERT_TRUE(test1.empty());
                PL_ASSERT_FALSE(test2.empty());
                return true;
            }
    };

    // P-tB4019
    class TestOneString_Substr : public Test
    {
        protected:
            OneString start = "🐦 ❤ my big sphinx of 💎.";
            OneString sub1 = "🐦 ❤"; //pos = 0, len = 3
            OneString sub2 = "of 💎"; //pos = 18, len = 4
            OneString sub3 = "x of 💎."; //pos = 16, len = (undefined)
        public:
            TestOneString_Substr(){}

            testdoc_t get_title() override
            {
                return "OneString: substr()";
            }

            testdoc_t get_docs() override
            {
                return "Test creation of substrings with substr()";
            }

            bool run() override
            {
                OneString test1 = start.substr(0, 3);
                PL_ASSERT_EQUAL(test1, sub1);

                OneString test2 = start.substr(18, 4);
                PL_ASSERT_EQUAL(test2, sub2);

                OneString test3 = start.substr(16);
                PL_ASSERT_EQUAL(test3, sub3);

                return true;
            }
    };

    // P-tB4020
    class TestOneString_Append : public TestOneString
    {
        protected:
            OneString start = "TEST";
            OneString test = "TEST";
            // ‽

        public:
            explicit TestOneString_Append(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Append " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test appending to a OneString with append().";
            }

            bool janitor() override {
                OneString test = start;
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        char ch = '!';
                        test.append(ch);
                        PL_ASSERT_EQUAL(test, "TEST!");
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        OneChar ochr = "!";
                        test.append(ochr);
                        PL_ASSERT_EQUAL(test, "TEST!");
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        OneChar ochr = "‽";
                        test.append(ochr);
                        PL_ASSERT_EQUAL(test, "TEST‽");
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        std::string str = "!!!";
                        test.append(str.c_str());
                        PL_ASSERT_EQUAL(test, "TEST!!!");
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        std::string str = "‽‽‽";
                        test.append(str.c_str());
                        PL_ASSERT_EQUAL(test, "TEST‽‽‽");
                        return true;
                    }
                    case STR_ASCII:
                    {
                        std::string str = "!!!";
                        test.append(str);
                        PL_ASSERT_EQUAL(test, "TEST!!!");
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        std::string str = "‽‽‽";
                        test.append(str);
                        PL_ASSERT_EQUAL(test, "TEST‽‽‽");
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        OneString ostr = "!!!";
                        test.append(ostr);
                        PL_ASSERT_EQUAL(test, "TEST!!!");
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        OneString ostr = "‽‽‽";
                        test.append(ostr);
                        PL_ASSERT_EQUAL(test, "TEST‽‽‽");
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    // P-tB4021
    class TestOneString_OpAppend : public TestOneString
    {
        protected:
            OneString start = "TEST";
            OneString test = "TEST";
            // ‽

        public:
            explicit TestOneString_OpAppend(TestStringType type)
            :TestOneString(type)
            {}

            testdoc_t get_title() override
            {
                return "OneString: Append (+=) " + title;
            }

            testdoc_t get_docs() override
            {
                return "Test appending to a OneString with the += operator.";
            }

            bool janitor() override {
                OneString test = start;
                return true;
            }

            bool run() override {
                switch(stringType)
                {
                    case CHAR:
                    {
                        char ch = '!';
                        test += ch;
                        PL_ASSERT_EQUAL(test, "TEST!");
                        return true;
                    }
                    case OCHAR_ASCII:
                    {
                        OneChar ochr = "!";
                        test += ochr;
                        PL_ASSERT_EQUAL(test, "TEST!");
                        return true;
                    }
                    case OCHAR_UNICODE:
                    {
                        OneChar ochr = "‽";
                        test += ochr;
                        PL_ASSERT_EQUAL(test, "TEST‽");
                        return true;
                    }
                    case CSTR_ASCII:
                    {
                        std::string str = "!!!";
                        test += str.c_str();
                        PL_ASSERT_EQUAL(test, "TEST!!!");
                        return true;
                    }
                    case CSTR_UNICODE:
                    {
                        std::string str = "‽‽‽";
                        test += str.c_str();
                        PL_ASSERT_EQUAL(test, "TEST‽‽‽");
                        return true;
                    }
                    case STR_ASCII:
                    {
                        std::string str = "!!!";
                        test += str;
                        PL_ASSERT_EQUAL(test, "TEST!!!");
                        return true;
                    }
                    case STR_UNICODE:
                    {
                        std::string str = "‽‽‽";
                        test += str;
                        PL_ASSERT_EQUAL(test, "TEST‽‽‽");
                        return true;
                    }
                    case OSTR_ASCII:
                    {
                        OneString ostr = "!!!";
                        test += ostr;
                        PL_ASSERT_EQUAL(test, "TEST!!!");
                        return true;
                    }
                    case OSTR_UNICODE:
                    {
                        OneString ostr = "‽‽‽";
                        test += ostr;
                        PL_ASSERT_EQUAL(test, "TEST‽‽‽");
                        return true;
                    }
                    default:
                    {
                        // Can't reach
                        return false;
                    }
                }
            }
    };

    ///////////// REUSABLE /////////////

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
                PL_ASSERT_TRUE(test.empty());
                return true;
            }
    };

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
                PL_ASSERT_EQUAL(beforeOne, afterTwo);
                PL_ASSERT_EQUAL(beforeTwo, afterOne);
                return true;
            }
    };

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
                for (size_t i = 0; i < target.length(); ++i)
                {
                    test.append("🐉");
                }
                PL_ASSERT_EQUAL(test, target);
                return true;
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
