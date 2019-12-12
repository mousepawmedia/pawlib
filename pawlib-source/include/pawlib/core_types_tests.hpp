/** Tests for Core and Atomic Data Types [PawLIB]
  * Version: 1.0
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

#ifndef PAWLIB_CORETYPES_TESTS_HPP
#define PAWLIB_CORETYPES_TESTS_HPP

#include "pawlib/core_types.hpp"
#include "pawlib/goldilocks.hpp"

// P-tB010[1-3]
class TestTrilean_CompareConst : public Test
{
    public:
        enum class Scenario
        {
            FALSE,
            MAYBE,
            TRUE
        };

        explicit TestTrilean_CompareConst(Scenario scenario)
        :s(scenario)
        {}

        testdoc_t get_title() override
        {
            switch(s)
            {
                case Scenario::FALSE:
                    return "Trilean: Const Comparions Against 'false'";
                case Scenario::MAYBE:
                    return "Trilean: Const Comparions Against 'maybe'";
                case Scenario::TRUE:
                    return "Trilean: Const Comparions Against 'true'";
            }
            return "";
        }

        testdoc_t get_docs() override
        {
            switch(s)
            {
                case Scenario::FALSE:
                    return "Test tril-to-const comparions against a 'false' tril.";
                case Scenario::MAYBE:
                    return "Test tril-to-const comparions against a 'maybe' tril.";
                case Scenario::TRUE:
                    return "Test tril-to-const comparions against a 'true' tril.";
            }
            return "";
        }

        bool run() override
        {
            switch(s)
            {
                // P-tB0101
                case Scenario::FALSE:
                {
                    tril t(false);

                    // Should match itself.
                    if( ! (t == false) )
                        return false;

                    // Should mismatch the other two constants.
                    if( (t != maybe) == false )
                        return false;

                    if( (t != true) == false )
                        return false;

                    // Should not match the other two constants.
                    if ( t == true )
                        return false;

                    if( t == maybe )
                        return false;

                    // Should not mismatch itself.
                    if( t != false )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
                // P-tB0102
                case Scenario::MAYBE:
                {
                    tril t(maybe);

                    // Should match itself.
                    if( !(t == maybe) )
                        return false;

                    // Should mismatch the other two constants.
                    if( (t != false) == false )
                        return false;

                    if( (t != true) == false )
                        return false;

                    // Should not match the other two constants.
                    if ( t == false )
                        return false;

                    if( t == true )
                        return false;

                    // Should not mismatch itself.
                    if( t != maybe )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
                // P-tB0103
                case Scenario::TRUE:
                {
                    tril t(true);

                    // Should match itself.
                    if( !(t == true) )
                        return false;

                    // Should mismatch the other two constants.
                    if( (t != false) == false )
                        return false;

                    if( (t != maybe) == false )
                        return false;

                    // Should not match the other two constants.
                    if ( t == false )
                        return false;

                    if( t == maybe )
                        return false;

                    // Should not mismatch itself.
                    if( t != true )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
            }

            // If we get here, the switch failed, and something's wrong.
            return false;
        }

        ~TestTrilean_CompareConst(){}
    protected:
        Scenario s;
};

// P-tB010[4-6]
class TestTrilean_CompareTril : public Test
{
    public:
        enum class Scenario
        {
            FALSE,
            MAYBE,
            TRUE
        };

        explicit TestTrilean_CompareTril(Scenario scenario)
        :s(scenario)
        {}

        testdoc_t get_title() override
        {
            switch(s)
            {
                case Scenario::FALSE:
                    return "Trilean: Trilean Comparions Against 'false'";
                case Scenario::MAYBE:
                    return "Trilean: Trilean Comparions Against 'maybe'";
                case Scenario::TRUE:
                    return "Trilean: Trilean Comparions Against 'true'";
            }
            return "";
        }

        testdoc_t get_docs() override
        {
            switch(s)
            {
                case Scenario::FALSE:
                    return "Test tril-to-tril comparions against a 'false' tril.";
                case Scenario::MAYBE:
                    return "Test tril-to-tril comparions against a 'maybe' tril.";
                case Scenario::TRUE:
                    return "Test tril-to-tril comparions against a 'true' tril.";
            }
            return "";
        }

        bool run() override
        {
            // A false (certain false) tril.
            tril test_f = false;
            // A true (certain true) tril.
            tril test_t = true;

            // An uncertain false tril.
            tril test_mf = false;
            (void)test_mf;
            test_mf = maybe;

            // An uncertain true tril.
            tril test_mt = true;
            (void)test_mt;
            test_mt = maybe;

            switch(s)
            {
                // P-tB0104
                case Scenario::FALSE:
                {
                    tril t(false);

                    // Should match its own kind.
                    // cppcheck-suppress knownConditionTrueFalse
                    if( (t == test_f) == false )
                        return false;

                    // Should mismatch the other values.
                    if( (t != test_mf) == false )
                        return false;

                    if( (t != test_mt) == false)
                        return false;

                    if( (t != test_t) == false )
                        return false;

                    // Should not match the other values.
                    if ( t == test_mf )
                        return false;

                    if ( t == test_mt )
                        return false;

                    if( t == test_t )
                        return false;

                    // Should not mismatch its own kind.
                    if( t != test_f )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
                // P-tB0105
                case Scenario::MAYBE:
                {
                    tril t(maybe);

                    // Should match its own kind - either variant.
                    if( (t == test_mf) == false )
                        return false;

                    if( (t == test_mt) == false )
                        return false;

                    // Should mismatch the other two values.
                    if( (t != test_f) == false )
                        return false;

                    if( (t != test_t) == false )
                        return false;

                    // Should not match the other two values.
                    if ( t == test_f )
                        return false;

                    if( t == test_t )
                        return false;

                    // Should not mismatch its own kind - either variant.
                    if( t != test_mf )
                        return false;

                    if( t != test_mt )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
                // P-tB0106
                case Scenario::TRUE:
                {
                    tril t(true);

                    // Should match its own kind.
                    if( (t == test_t) == false )
                        return false;

                    // Should mismatch the other two values.
                    if( (t != test_f) == false )
                        return false;

                    if( (t != test_mf) == false )
                        return false;

                    if( (t != test_mt) == false )
                        return false;

                    // Should not match the other two values.
                    if ( t == test_f )
                        return false;

                    if( t == test_mf )
                        return false;

                    if( t == test_mt )
                        return false;

                    // Should not mismatch its own kind.
                    if( t != test_t )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
            }

            // If we get here, the switch failed, and something's wrong.
            return false;
        }

        ~TestTrilean_CompareTril(){}
    protected:
        Scenario s;
};

// P-tB010[7-9]
class TestTrilean_Unary : public Test
{
    public:
        enum class Scenario
        {
            FALSE,
            MAYBE,
            TRUE
        };

        explicit TestTrilean_Unary(Scenario scenario)
        :s(scenario)
        {}

        testdoc_t get_title() override
        {
            switch(s)
            {
                case Scenario::FALSE:
                    return "Trilean: Unary False (!foo)";
                case Scenario::MAYBE:
                    return "Trilean: Unary Maybe (~foo)";
                case Scenario::TRUE:
                    return "Trilean: Unary True (foo)";
            }
            return "";
        }

        testdoc_t get_docs() override
        {
            switch(s)
            {
                case Scenario::FALSE:
                    return "Test the NOT operator (!foo) on trileans.";
                case Scenario::MAYBE:
                    return "Test the 'maybe' operator (~foo) on trileans.";
                case Scenario::TRUE:
                    return "Test the boolean condition (foo) on trileans.";
            }
            return "";
        }

        bool run() override
        {
            switch(s)
            {
                // P-tB0107
                case Scenario::FALSE:
                {
                    tril t(false);

                    // Should pass its matching unary operator.
                    if( (!t) == false )
                        return false;

                    // Should fail the other two unary operators.
                    if ( t )
                        return false;

                    if( ~t )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
                // P-tB0108
                case Scenario::MAYBE:
                {
                    tril t(maybe);

                    // Should pass its matching unary operator.
                    if( (~t) == false )
                        return false;

                    // Should fail the other two unary operators.
                    if ( !t )
                        return false;

                    if( t )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
                // P-tB0109
                case Scenario::TRUE:
                {
                    tril t(true);

                    // Should pass its matching unary operator.
                    if( (t) == false )
                        return false;

                    // Should fail the other two unary operators.
                    if ( ~t )
                        return false;

                    if( !t )
                        return false;

                    // If we get this far, return true.
                    return true;
                }
            }

            // If we get here, the switch failed, and something's wrong.
            return false;
        }

        ~TestTrilean_Unary(){}

    protected:
        Scenario s;
};

// P-tB010A
class TestTrilean_AssignConst : public Test
{
    public:
        TestTrilean_AssignConst(){}

        testdoc_t get_title() override
        {
            return "Trilean: Assign Constant";
        }

        testdoc_t get_docs() override
        {
            return "Test assignment of the three valid constants.";
        }

        bool run() override
        {
            tril a = false;

            // If the check for false fails...
            // cppcheck-suppress knownConditionTrueFalse
            // cppcheck-suppress oppositeExpression
            if((!a) == false)
            {
                // Fail the test.
                return false;
            }

            a = maybe;
            if((~a) == false)
            {
                return false;
            }

            a = true;
            // cppcheck-suppress knownConditionTrueFalse
            if((a) == false)
            {
                return false;
            }

            // Cycle back around to maybe and false...

            a = maybe;
            if((~a) == false)
            {
                return false;
            }

            a = false;
            // cppcheck-suppress knownConditionTrueFalse
            if((!a) == false)
            {
                return false;
            }

            // If we get this far, the test passes.
            return true;
        }

        ~TestTrilean_AssignConst(){}
};

// P-tB010B
class TestTrilean_AssignTril : public Test
{
    public:
        TestTrilean_AssignTril(){}

        testdoc_t get_title() override
        {
            return "Trilean: Assign Tril";
        }

        testdoc_t get_docs() override
        {
            return "Test assignment of other trileans.";
        }

        bool run() override
        {
            tril f = false;
            tril m = maybe;
            tril t = true;

            tril a = f;

            // If the check for false fails...
            // cppcheck-suppress knownConditionTrueFalse
            if((!a) == false)
            {
                // Fail the test.
                return false;
            }

            a = m;
            if((~a) == false)
            {
                return false;
            }

            a = t;
            // cppcheck-suppress knownConditionTrueFalse
            if((a) == false)
            {
                return false;
            }

            // Cycle back around to maybe and false...

            a = m;
            if((~a) == false)
            {
                return false;
            }

            a = f;
            // cppcheck-suppress knownConditionTrueFalse
            if((!a) == false)
            {
                return false;
            }

            // If we get this far, the test passes.
            return true;
        }

        ~TestTrilean_AssignTril(){}
};

// P-tB010C
class TestTrilean_Certain : public Test
{
    public:
        TestTrilean_Certain(){}

        testdoc_t get_title() override
        {
            return "Trilean: Certain";
        }

        testdoc_t get_docs() override
        {
            return "Test certain() function of trilean.";
        }

        bool run() override
        {
            tril a = true;

            // Do something with that value to bypass the compiler warning.
            (void)a;

            a = maybe;

            if(a.certain() != true)
            {
                return false;
            }

            a = false;
            (void)a;

            a = maybe;

            if(a.certain() != false)
            {
                return false;
            }

            // If we get this far, the test passes.
            return true;
        }

        ~TestTrilean_Certain(){}
};

// P-tB010D
class TestTrilean_NoNonsense : public Test
{
    public:
        TestTrilean_NoNonsense(){}

        testdoc_t get_title() override
        {
            return "Trilean: No Nonsense";
        }

        testdoc_t get_docs() override
        {
            return "Ensure 'maybe' doesn't ever match 'true' or 'false'.";
        }

        bool run() override
        {
            bool t = true;
            bool f = false;
            tril m = maybe;

            // Ensure a 'maybe' tril doesn't match true or false either way.
            if(t == m || f == m)
            {
                return false;
            }

            if(m == t || m == f)
            {
                return false;
            }

            /* Ensure our 'maybe' constant (pure_tril) doesn't match
                * true or false either way. */
            if(t == maybe || f == maybe)
            {
                return false;
            }

            if(maybe == t || maybe == f)
            {
                return false;
            }

            // If we get this far, the test passes.
            return true;
        }

        ~TestTrilean_NoNonsense(){}
};

class TestSuite_CoreTypes : public TestSuite
{
    public:
        explicit TestSuite_CoreTypes(){}

        void load_tests() override;

        testdoc_t get_title() override
        {
            return "PawLIB: Trilean Tests";
        }

        ~TestSuite_CoreTypes(){}
};

#endif // PAWLIB_CORETYPES_TESTS_HPP
