#include "pawlib/onestring.hpp"

namespace pawlib
{
    template <const int oneSize>
    OneString<oneSize>::OneString():OneStringBase(oneSize, ONE_TYPE){}

    template <const int oneSize>
    OneString<oneSize>::OneString(const char* str):OneStringBase(oneSize, ONE_TYPE)
    {
        append(str);
    }

    template <const int oneSize>
    OneString<oneSize>::OneString(std::string str):OneString(str.c_str()){}

    template <const int oneSize>
    OneString<oneSize>::OneString(char ch):OneStringBase(ch, oneSize, ONE_TYPE){}

    template <const int oneSize>
    OneString<oneSize>::OneString(OneChar& ch):OneStringBase(ch, oneSize, ONE_TYPE){}

    template <const int oneSize>
    bool OneString<oneSize>::equals(const char* ostr) const
    {
         // Convert the char* to a OneString and then call the equals function
        OneString<oneSize> compareStr(ostr);

        int thisSize = size();

        if(thisSize == compareStr.size())
        {
            for(int i = 0; i < thisSize; ++i)
            {
                if(!(master[i] == compareStr[i]))
                    return false;
            }
            return true;
        }
        return false;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const char* ostr)
    {
        int index = 0;
        while(ostr[index] != '\0')
        {
             // Check if the OneString is full
            if(size() >= oneSize)
            {
                ioc << cat_error << ta_bold << fg_red <<
                "OneString Error: Input string is too large." << io_end;
                OneString();
                return;
            }

            // Can tell how many bytes by masking the first character
            switch(ostr[index] & 0xF0)
            {
                case 0xF0 :
                    {
                        // Insert a 4 byte Unicode Char into the OneString
                        parseChar(ostr, index, 4);
                        index+=4;
                        break;
                    }
                case 0xE0 :
                    {
                        // Insert a 3 byte Unicode Char into the OneString
                        parseChar(ostr, index, 3);
                        index+=3;
                        break;
                    }
                case 0xC0:
                    {
                        // Insert a 2 byte Unicode Char into the OneString
                        parseChar(ostr, index, 2);
                        index+=2;
                        break;
                    }
                case 0x80:
                    {
                        ioc << cat_error << ta_bold << fg_red <<
                        "OneString Error: Invalid Character In String At Position: " << index << io_end;
                        return;
                    }
                default :
                    {
                        // Insert a standard char
                        parseChar(ostr, index, 1);
                        ++index;
                    }

            }
             incLen();
        }
    }

    template <const int oneSize>
    void OneString<oneSize>::parseChar(const char* str, int index, int bytes)
    {
        int length = size();
        // Bytes indicates the size of the desired parsing area while
        // index indicates the start of the parse area. Loop through the parse
        // area and add each character to the current OneChar in the OneString
        for(int i = 0; i < bytes; ++i)
            master[length][i] = str[index + i];
        master[length][bytes] = '\0'; // Terminate the OneChar
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const char* ostr)
    {
        // Convert to OneString then insert
        OneString<oneSize> temp = ostr;
        insert(pos, temp);
    }

    template <const int oneSize>
    OneStringBase& OneString<oneSize>::substr(int pos, int sublen)
    {
        // Check sublen flag. If -1, then go to the end of the OneString
        if(sublen == -1)
        {
            // Calculate the size from the position to the end of the OneString
            sublen = size() - pos;
        }
        // Check for valid index
        if((pos >= oneSize) || (pos < 0))
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error:" <<
            " Index Out of Bounds" << io_end;
            return *this;
        }
        // If the substring size is too large throw an error
        else if(sublen + pos > size())
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "Size exceeds limits of OneString"<<io_end;
            return *this;
        }
        else
        {
            // Create a new OneString and append each character that is found
            // in the substring
            OneString<oneSize>* newOne = new OneString();
            for(int i = 0; i < sublen; ++i)
            {
                newOne->append(master[pos]);
                pos++;
            }
            return *newOne;
        }
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<oneSize>& str)
    {
         /* Cannot swap if they are not of the same OneString type */
        if(str.size() > oneSize)
        {
            ioc << cat_error << ta_bold << fg_red << "OneStringBase Error" <<
            ": The OneStringBase argument is too large to"
            << " swap with" <<io_end;
        }
        else
        {
            OneString<oneSize> temp( *this);
            *this = str;
            str = temp;
        }
    }


    template <const int oneSize>
    OneStringBase& OneString<oneSize>::assignHelper(const char* str)
    {
        this->setLen(0);
        int index = 0;
        // Loop to end of char*
        while(str[index] != '\0')
        {
            // Check if the OneString is full
            if(size() >= oneSize)
            {
                ioc << cat_error << ta_bold << fg_red << "OneString Error" <<
                ": Input String is Too Large" <<io_end;
                return *this;
            }
            // Does it start with an F?
            if((str[index] & 0xF0) == 0xF0)
            {
                // Insert a 4 byte Unicode Char into the OneString
                parseChar(str, index, 4);
                index+=4;
            }
            // Does it start with an E?
            else if((str[index] & 0xF0) == 0xE0)
            {
                // Insert a 3 byte Unicode Char into the OneString
                parseChar(str, index, 3);
                index+=3;
            }
            // Does it start with a C?
            else if((str[index] & 0xF0) == 0xC0)
            {
                // Insert a 2 byte Unicode Char into the OneString
                parseChar(str, index, 2);
                index+=2;
            }
            // Check if the char is valid
            else if((str[index] & 0xF0) == 0x80)
            {
                ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
                " Invalid Character in String at Position: " << index <<io_end;
                break;
            }
            else
            {
                // Insert a 1-byte ASCII char
                parseChar(str, index, 1);
                index++;
            }
            this->incLen(); // Set the size for the OneString
        }
        return *this;
    }

    template <const int oneSize>
    OneStringBase& OneString<oneSize>::assignChar(char ch)
    {
        // Directly set the first OneChar in the OneString
        this->master[0][0] = ch;
        this->master[0][1] = '\0';
        this->setLen(1);
        return *this;
    }

    template <const int oneSize>
    bool OneString<oneSize>::lessThanStr(const OneStringBase& ostr)
    {
        // Only loop as far as the smallest string
        int small_len = (size() < ostr.size())? size(): ostr.size();
        for(int i = 0; i< small_len; i++)
        {
            if(master[i] < (*ostr[i]))
            {
                return true;
            }
            else
            {
                // If a OneChar is neither less than or equal, then it is
                // greater. Therefore making the input smaller
                if(!(master[i] == (*ostr[i])))
                {
                    return false;
                }
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

    template <const int oneSize>
    bool OneString<oneSize>::lessThanCharP(const char* ostr)
    {
        int mainIndex = 0;
        int smallIndex = 0;
        int charIndex = 0;
        int endIndex = size();

        /*Search through every index of the OneString, including each index
         of each UniChar. Compare to each index in input */
        while(mainIndex < endIndex)
        {
            //If an index is bigger, return false
            if(master[mainIndex][smallIndex] > ostr[charIndex])
            {
                return false;
            }
            //If an index is smaller in the OneString, then it is smaller
            else if(master[mainIndex][smallIndex] < ostr[charIndex])
            {
                return true;
            }

            //If we are not at the end of the UniChar, increase smallIndex
            if(master[mainIndex][smallIndex + 1] != '\0')
            {
                ++smallIndex;
            }
            //If we are at null-terminator move to the next UniChar.
            else
            {
                ++mainIndex;

                // Reset smallIndex for new UniChar
                smallIndex = 0;
            }

            // Always increase position in input const char*
            ++charIndex;
        }

        // Check that we are at the end of both strings. If the input is not
        // done, then the OneString is smaller
        if(ostr[charIndex] != '\0')
        {
            return true;
        }
        return false;
    }


    // Forward declare all template sizes
    template class OneString<8>;
    template class OneString<16>;
    template class OneString<32>;
    template class OneString<64>;
    template class OneString<128>;
    template class OneString<256>;
    template class OneString<512>;
    template class OneString<1024>;
    template class OneString<2048>;
    template class OneString<4096>;
}
