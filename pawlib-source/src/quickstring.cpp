/*PawLib Library, version 1.3
* QuickString Class
* QuickString is a dynamic-allocation-limited replacement for std::string
* Last Updated: November 12, 2015
*
* Scott Taylor
* MousePaw Media
*/

#include "pawlib/quickstring.hpp"

namespace pawlib
{
    template <const int quickSize>
    QuickString<quickSize>::QuickString():OneStringBase(quickSize, QUICK_TYPE){}

    template <const int quickSize>
    QuickString<quickSize>::QuickString(const char* str):OneStringBase(quickSize, QUICK_TYPE)
    {
        append(str);
    }

    template <const int quickSize>
    QuickString<quickSize>::QuickString(std::string str):QuickString(str.c_str()){}

    template <const int quickSize>
    QuickString<quickSize>::QuickString(char ch):OneStringBase(ch, quickSize, QUICK_TYPE){}

    template <const int quickSize>
    QuickString<quickSize>::QuickString(OneChar& ch):OneStringBase(ch, quickSize, QUICK_TYPE){}

    template <const int quickSize>
    bool QuickString<quickSize>::equals(const char* ostr) const
    {
        int strSize = size();
        int inpSize;

        //Loop through input until you hit null terminator
        for(inpSize = 0; ostr[inpSize] != '\0' ; ++inpSize)
        {
            // If at end of OneString during loop, they are not equal
            if(inpSize == strSize)
            {
                return false;
            }

            // If characters are not the same, not equal
            else if(!(master[inpSize] == ostr[inpSize]))
            {
                return false;
            }
        }

        // Only equal if the two sizes are equal
        if(strSize != inpSize - 1)
        {
            return false;
        }
        return true;
    }

    template <const int quickSize>
    void QuickString<quickSize>::append(const char* ostr)
    {
        for(int i = 0; ostr[i] != '\0'; ++i)
        {
            // Check if the OneString is full
            if(size() >= quickSize)
            {
                ioc << cat_error << ta_bold << fg_red <<
                "QuickString Error: Input string is too large." << io_end;
                QuickString();
                return;
            }

            // Copy over
            master[i] = ostr[i];

            // Increase length
            incLen();
        }
    }

    template <const int quickSize>
    void QuickString<quickSize>::insert(int pos, const char* ostr)
    {
        // Convert to QuickString then insert
        QuickString<quickSize> temp = ostr;
        insert(pos, temp);
    }

    template <const int quickSize>
    OneStringBase& QuickString<quickSize>::substr(int pos, int sublen)
    {
        // Check sublen flag. If -1, then go to the end of the QuickString
        if(sublen == -1)
        {
            // Calculate the size from the position to the end of the QuickString
            sublen = size() - pos;
        }
        // Check for valid index
        if((pos >= quickSize) || (pos < 0))
        {
            ioc << cat_error << ta_bold << fg_red << "QuickString Error:" <<
            " Index Out of Bounds" << io_end;
            return *this;
        }
        // If the substring size is too large throw an error
        else if(sublen + pos > size())
        {
            ioc << cat_error << ta_bold << fg_red << "QuickString Error: " <<
            "Size exceeds limits of QuickString"<<io_end;
            return *this;
        }
        else
        {
            // Create a new OneString and append each character that is found
            // in the substring
            QuickString<quickSize>* newPaw = new QuickString();
            for(int i = 0; i < sublen; i++)
            {
                newPaw->append(master[pos]);
                pos++;
            }
            return *newPaw;
        }
    }

    template <const int quickSize>
    void QuickString<quickSize>::swap(QuickString<quickSize>& str)
    {
        /* Cannot swap if they are not of the same OneString type */
        if(str.size() > quickSize)
        {
            ioc << cat_error << ta_bold << fg_red << "OneStringBase Error" <<
            ": The OneStringBase argument is too large to"
            << " swap with" <<io_end;
        }
        else
        {
            /* Swap the values */
            QuickString<quickSize> temp = *this;
            *this = str;
            str = temp;
        }
    }

    template <const int quickSize>
    OneStringBase& QuickString<quickSize>::assignHelper(const char* str)
    {
        this->setLen(0);

        for(int i = 0; str[i] != '\0'; ++i)
        {
            // Check if the QuickString is full
            if(size() >= quickSize)
            {
                ioc << cat_error << ta_bold << fg_red << "QuickString Error" <<
                ": Input String is Too Large" <<io_end;
                return *this;
            }

            // Copy
            master[i] = str[i];

            this->incLen(); // Set the size for the OneString
        }
        return *this;
    }

    template <const int quickSize>
    OneStringBase& QuickString<quickSize>::assignChar(char ch)
    {
        // Directly set the first OneChar in the QuickString
        this->master[0]= ch;
        this->setLen(1);
        return *this;
    }

    template <const int quickSize>
    bool QuickString<quickSize>::lessThanStr(const OneStringBase& ostr)
    {
        // Only loop as far as the smallest string
        int small_len = (size() < ostr.size())? size(): ostr.size();
        for(int i = 0; i< small_len; i++)
        {
            if(&master[i] < ostr[i])
            {
                return true;
            }
        }

        // If they made it through the loop and ostr1 is smaller
        // then return true
        if((small_len == size()) && (small_len != ostr.size()))
        {
            return true;
        }
        return false;
    }

    template <const int quickSize>
    bool QuickString<quickSize>::lessThanCharP(const char* ostr)
    {
        int charIndex;
        int endIndex = size();

        //Search through every index of the QuickString. Compare to each index
        // in input
        for(charIndex = 0; charIndex < endIndex; ++charIndex)
        {
            //If we are at the end of input, then the string is larger
            if(ostr[charIndex] == '\0')
            {
                return false;
            }

            //If an index is bigger, return false
            if(master[charIndex][0] > ostr[charIndex])
            {
                return false;
            }
            //If an index is smaller in the QuickString, then it is smaller
            else if(master[charIndex][0] < ostr[charIndex])
            {
                return true;
            }

        }

        // Check that we are at the end of both strings. If the input is not
        // done, then the QuickString is smaller
        if(ostr[charIndex] != '\0')
        {
            return true;
        }
        return false;
    }


    // Forward declare all QuickString sizes
    template class QuickString<8>;
    template class QuickString<16>;
    template class QuickString<32>;
    template class QuickString<64>;
    template class QuickString<128>;
    template class QuickString<256>;
    template class QuickString<512>;
    template class QuickString<1024>;
    template class QuickString<2048>;
    template class QuickString<4096>;
}
