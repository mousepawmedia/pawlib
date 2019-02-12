/** Goldilocks Test System: Assertions [PawLIB]
 * Version: 1.0
 *
 * Assertion functions and macros for Goldilocks…
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

#include "pawlib/iochannel.hpp"

using namespace pawlib;
using namespace pawlib::ioformat;

// Assertion macros
#define PL_ASSERT_TRUE(val) \
    do { if (!do_assert_true(val)) { return false; } } while(0)

#define PL_ASSERT_FALSE(val) \
    do { if (!do_assert_false(val)) { return false; } } while(0)

#define PL_ASSERT_EQUAL(lhs, rhs) \
    do { if (!do_assert_equal(lhs, rhs)) { return false; } } while(0)

#define PL_ANTIASSERT_EQUAL(lhs, rhs) \
    do { if (!do_antiassert_equal(lhs, rhs)) { return false; } } while(0)

#define PL_ASSERT_NOT_EQUAL(lhs, rhs) \
    do { if (!do_assert_not_equal(lhs, rhs)) { return false; } } while(0)

#define PL_ANTIASSERT_NOT_EQUAL(lhs, rhs) \
    do { if (!do_antiassert_not_equal(lhs, rhs)) { return false; } } while(0)

#define PL_ASSERT_LESS(lhs, rhs) \
    do { if (!do_assert_less(lhs, rhs)) { return false; } } while(0)

#define PL_ASSERT_LESS_EQUAL(lhs, rhs) \
    do { if (!do_assert_less_equal(lhs, rhs)) { return false; } } while(0)

#define PL_ASSERT_GREATER(lhs, rhs) \
    do { if (!do_assert_greater(lhs, rhs)) { return false; } } while(0)

#define PL_ASSERT_GREATER_EQUAL(lhs, rhs) \
    do { if (!do_assert_greater_equal(lhs, rhs)) { return false; } } while(0)

// TODO: Predicate [P, v... => P(v...)], Throws, NaN, INF, no-throw, fail w/ message, skip, report, warn

namespace pawlib {
    template <typename T>
    bool do_assert_true(T val)
    {
        if (!(val)) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << val
                << io_endline
                << "Yields " << false << ", expected " << true << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T>
    bool do_assert_false(T val)
    {
        if (val) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << val
                << io_endline
                << "Yields " << true << ", expected " << false << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_assert_equal(T lhs, U rhs)
    {
        if (!(lhs == rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " == "
                << ta_bold << rhs
                << io_endline
                << "Yields " << false << ", expected " << true << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_antiassert_equal(T lhs, U rhs)
    {
        if ((lhs == rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Anti-assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " == "
                << ta_bold << rhs
                << io_endline
                << "Yields " << true << ", expected " << false << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_assert_not_equal(T lhs, U rhs)
    {
        if (!(lhs != rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " != "
                << ta_bold << rhs
                << io_endline
                << "Yields " << false << ", expected " << true << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_antiassert_not_equal(T lhs, U rhs)
    {
        if ((lhs != rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Anti-assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " != "
                << ta_bold << rhs
                << io_endline
                << "Yields " << true << ", expected " << false << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_assert_less(T lhs, U rhs)
    {
        if (!(lhs < rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " < "
                << ta_bold << rhs
                << io_endline
                << "Yields " << false << ", expected " << true << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_assert_less_equal(T lhs, U rhs)
    {
        if (!(lhs <= rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " <= "
                << ta_bold << rhs
                << io_endline
                << "Yields " << false << ", expected " << true << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_assert_greater(T lhs, U rhs)
    {
        if (!(lhs > rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " > "
                << ta_bold << rhs
                << io_endline
                << "Yields " << false << ", expected " << true << "\n"
                << io_end;
            return false;
        }
        return true;
    }

    template <typename T, typename U>
    bool do_assert_greater_equal(T lhs, U rhs)
    {
        if (!(lhs < rhs)) {
            ioc << cat_error << fg_red << ta_bold << "Assertion Failed!" << io_endline
                << ta_bold << lhs
                << io_send << " >= "
                << ta_bold << rhs
                << io_endline
                << "Yields " << false << ", expected " << true << "\n"
                << io_end;
            return false;
        }
        return true;
    }
}
