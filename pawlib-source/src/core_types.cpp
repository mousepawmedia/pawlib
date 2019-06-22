#include "pawlib/core_types.hpp"

namespace pawlib
{
    // UNCERTAINTY

    bool operator~(const uncertainty& rhs) noexcept
    {
        // Return the certainty of rhs.
        bool r = rhs.data;
        return r;
    }

    std::ostream& operator<<(std::ostream& output, const uncertainty& in)
    {
        output << (in.data ? "Uncertain" : "Certain");
        return output;
    }

    bool operator==(const uncertainty& lhs, const uncertainty& rhs) noexcept
    {
        return (lhs.data == rhs.data);
    }

    bool operator!=(const uncertainty& lhs, const uncertainty& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    bool operator==(const uncertainty&, const bool&) noexcept
    {
        return false;
    }

    bool operator!=(const uncertainty&, const bool&) noexcept
    {
        return false;
    }

    bool operator==(const bool& lhs, const uncertainty& rhs) noexcept
    {
        return (rhs == lhs);
    }

    bool operator!=(const bool& lhs, const uncertainty& rhs) noexcept
    {
        return !(rhs == lhs);
    }

    bool operator==(const uncertainty& lhs, const tril& rhs) noexcept
    {
        return (rhs == lhs);
    }

    bool operator!=(const uncertainty& lhs, const tril& rhs) noexcept
    {
        return (rhs != lhs);
    }


    // TRIL

    tril::tril(bool in_b, bool in_u) noexcept
    :data(0)
    {
        set_b(in_b);
        set_u(in_u);
    }

    void tril::set_b(bool b) noexcept
    {
        data = (b ? (data | B) : (data & ~B));
    }

    void tril::set_u(bool u) noexcept
    {
        data = (u ? (data | U) : (data & ~U));
    }

    tril::operator bool_type() const noexcept
    {
        if(~(*this))
        {
            return 0;
        }
        else
        {
            return (!!(*this)) ?
                &tril::this_type_does_not_support_some_comparisons : 0;
        }
    }

    bool operator!(const tril& rhs) noexcept
    {
        // Get the boolean bit of rhs.
        bool b = (rhs.data & tril::B);
        // Get the uncertainty bit of rhs.
        bool u = (rhs.data & tril::U);

        /* If uncertain, return false. Otherwise, return inverse (NOT) of
         * the boolean flag. */
        return (u ? false : !b);
    }

    bool operator~(const tril& rhs) noexcept
    {
        // Return just the uncertainty bit of rhs.
        return (rhs.data & tril::U);
    }

    tril& tril::operator=(const bool& rhs) noexcept
    {
        set_b(rhs);
        set_u(false);
        return *this;
    }

    tril& tril::operator=(const tril& rhs) noexcept
    {
        // We just copy all the data from one tril to the other.
        data = rhs.data;

        return *this;
    }

    tril& tril::operator=(const uncertainty& rhs) noexcept
    {
        /* We only copy the uncertainty state, so as to preserve the
         * boolean bit and allow reverting with `certain()`. */
        set_u(rhs.data);

        return *this;
    }

    bool tril::certain() const noexcept
    {
        // Return the boolean bit, ignoring the uncertainty bit.
        return (data & tril::B);
    }

    bool operator==(const tril& lhs, const bool& rhs) noexcept
    {
        // Get the boolean bit of the left side.
        bool b = (lhs.data & tril::B);
        // Get the uncertainty bit of the right side.
        bool u = (lhs.data & tril::U);

        // If uncertain, return FALSE. Else, return whether boolean values match.
        return (u ? false : rhs == b);
    }

    bool operator==(const bool& lhs, const tril& rhs) noexcept
    {
        // We'll use operator!=(tril, bool), since the logic is the same.
        return (rhs == lhs);
    }

    bool operator==(const tril& lhs, const tril& rhs) noexcept
    {
        // Get the boolean bit of the left side.
        bool lb = (lhs.data & tril::B);
        // Get the uncertainty bit of the left side.
        bool lu = (lhs.data & tril::U);

        // Get the boolean bit of the right side.
        bool rb = (rhs.data & tril::B);
        // Get the uncertainty bit of the right side.
        bool ru = (rhs.data & tril::U);

        /* Return TRUE if both are uncertain
         * OR if they are both certain and have same boolean value. */
        return ( (lu && ru) || (!lu && !ru && lb == rb) );
    }

    bool operator==(const tril& lhs, const uncertainty& rhs) noexcept
    {
        /* When comparing a tril and a pure tril, the boolean bit is irrelevant.
         * Only the uncertainty flag matters in a pure tril. */

        // Get the uncertainty bit of the left side.
        bool u = (lhs.data & tril::U);

        // Return TRUE if both certainty flags match.
        return (u == rhs.data);
    }

    bool operator!=(const tril& lhs, const bool& rhs) noexcept
    {
        // Get the boolean bit of the left side.
        bool b = (lhs.data & tril::B);
        // Get the uncertainty bit of the right side.
        bool u = (lhs.data & tril::U);

        // If uncertain, return FALSE. Else, return whether boolean values match.
        return (u ? true : rhs != b);
    }

    bool operator!=(const bool& lhs, const tril& rhs) noexcept
    {
        // We'll use operator!=(tril, bool), since the logic is the same.
        return (rhs != lhs);
    }

    bool operator!=(const tril& lhs, const tril& rhs) noexcept
    {
        // Get the boolean bit of the left side.
        bool lb = (lhs.data & tril::B);
        // Get the uncertainty bit of the left side.
        bool lu = (lhs.data & tril::U);

        // Get the boolean bit of the right side.
        bool rb = (rhs.data & tril::B);

        // Get the uncertainty bit of the right side.
        bool ru = (rhs.data & tril::U);

        /* If one (not both) is uncertain
         * OR if they're both certain and the boolean types don't match. */
        return ( (lu && !ru) || (!lu && ru) || (!lu && !ru && lb != rb));
    }

    bool operator!=(const tril& lhs, const uncertainty& rhs) noexcept
    {
        /* When comparing a tril and a pure tril, the boolean bit is irrelevant.
         * Only the uncertainty flag matters in a pure tril. */

        // Get the uncertainty bit of the left side.
        bool u = (lhs.data & tril::U);

        // Return FALSE if both certainty flags match.
        return (u != rhs.data);
    }

    std::ostream& operator<<(std::ostream& output, const tril& in)
    {
        // Get the boolean bit of the trilean.
        bool b = (in.data & tril::B);
        // Get the uncertainty bit of the trilean.
        bool u = (in.data & tril::U);

        /* If uncertain, we'll pass the number "2". Otherwise, we can just
         * pass the boolean bit, and "0" will be shown for false, and "1" for
         * true, as with all booleans. */
        output << (u ? 2 : b);
        return output;
    }
}
