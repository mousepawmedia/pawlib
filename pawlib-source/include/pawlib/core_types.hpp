/** Core and Atomic Data Types [PawLIB]
  * Version: 1.0
  *
  * New basic data types, including Trilean.
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

#ifndef PAWLIB_CORETYPES_HPP
#define PAWLIB_CORETYPES_HPP

#include <cstdint>
#include <iostream>

namespace pawlib
{
    class tril;

    /* The uncertainty class is never intended to be modified after creation.
     * It is used to represent a "pure maybe" - a trilean with no valid boolean
     * value. The constant "maybe" is an instance of this class. Initializing
     * or assigning a tril with an uncertainty does not affect the tril's
     * boolean value. */
    class uncertainty
    {
        /* tril has to be able to access protected data of
         * uncertainty instances. */
        friend class tril;
        protected:
            bool data;

        public:
            /** Construct an uncertainty.
             * \param the initial value (default true) */
            explicit uncertainty(bool u=true)
            :data(u)
            {}

            /** Returns TRUE if the certainty is MAYBE. */
            friend bool operator~(const uncertainty&);

            friend bool operator==(const uncertainty&, const uncertainty&);
            friend bool operator!=(const uncertainty&, const uncertainty&);

            friend bool operator==(const uncertainty&, const bool&);
            friend bool operator!=(const uncertainty&, const bool&);

            friend bool operator==(const bool&, const uncertainty&);
            friend bool operator!=(const bool&, const uncertainty&);

            /* We see these again in the `tril` class. We're repeating the
             * declaration here to ensure these functions are friends of
             * BOTH classes. */
            friend bool operator==(const tril&, const uncertainty&);
            friend bool operator!=(const tril&, const uncertainty&);

            friend bool operator==(const uncertainty&, const tril&);
            friend bool operator!=(const uncertainty&, const tril&);

            friend std::ostream& operator<<(std::ostream&, const uncertainty&);

            ~uncertainty(){}
    };

    class tril
    {
        protected:
            /** The actual binary data. By using an int8_t, we are ensuring
             * that a tril is never larger than one byte. */
            int8_t data;

            /* These constants allow us to quickly check the three flags in
             * our data byte. Simply use "data & FLAG", where FLAG is one of the
             * following. */
            static const int8_t B = (1 << 0);
            static const int8_t U = (1 << 1);

            /* We are employing the Safe Bool Idiom. */
            typedef void (tril::*bool_type)() const;
            void this_type_does_not_support_some_comparisons() const {}

            /** Set the B (boolean) bit.
             * \param the new value for the boolean bit. */
            void set_b(bool);

            /** Set the U (uncertainty) bit.
             * \param the new value for the uncertainty bit. */
            void set_u(bool);

        public:
            /** Construct a new trilean with a default value of certain false. */
            tril()
            :data(0)
            {}

            /** Construct a new trilean with the specified flag values.
             * \param the boolean bit (true/false)
             * \param the uncertainty bit */
            tril(bool, bool=false);

            /** Trilean copy constructor.
             * \param the trilean to copy */
            tril(const tril& in)
            :data(in.data)
            {}

            /** Construct a new trilean with an uncertainty variable.
             * \param the uncertainty to copy */
            tril(const uncertainty& in)
            :data(0)
            {
                set_u(in.data);
            }

            /** Return last certain state of the trilean. Does not modify
              * the trilean itself.
              * \return the last certain state */
            bool certain();

            /** Boolean cast, following the Safe Bool Idiom.
              * Returns TRUE if the trilean is CERTAIN TRUE. */
            operator bool_type() const;

            /** Returns TRUE if the trilean is CERTAIN FALSE. */
            friend bool operator!(const tril&);
            /** Returns TRUE if the trilean is MAYBE. */
            friend bool operator~(const tril&);

            /** Assign a boolean (true/false) to this trilean. */
            tril& operator=(const bool&);
            /** Assign a trilean (true/false/maybe) to this trilean. */
            tril& operator=(const tril&);
            /** Assign an uncertainty to this trilean, only modifying the
             * uncertainty bit without modifying the boolean bit. */
            tril& operator=(const uncertainty&);

            /* Valid comparisons. All unspecified comparisons trigger compiler
             * errors, thanks to the Safe Bool Idiom. */
            friend bool operator==(const tril&, const bool&);
            friend bool operator==(const bool&, const tril&);
            friend bool operator==(const tril&, const tril&);
            friend bool operator==(const tril&, const uncertainty&);

            friend bool operator!=(const tril&, const bool&);
            friend bool operator!=(const bool&, const tril&);
            friend bool operator!=(const tril&, const tril&);
            friend bool operator!=(const tril&, const uncertainty&);

            friend std::ostream& operator<<(std::ostream&, const tril&);

            ~tril(){}
    };

    // We offer this constant to go alongside "true" and "false".
    const uncertainty maybe = uncertainty();
}

#endif // PAWLIB_CORETYPES_HPP
