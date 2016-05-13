/*PawLib Library, version 1.3
* OneString Class
* OneString is a dynamic-allocation-free replacement for std::string
* Last Updated: November 12, 2015
*
* Scott Taylor
* MousePaw Games
*/

#include "onestring.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <iochannel.hpp>


namespace pawlib
{
    /*************************************************************************
    // The OneChar functions start here
    **************************************************************************/
    OneChar::OneChar()
    {
        //miniChar[0] = '\0'; code profiling
    }

    char OneChar::operator[](int pos) const
    {
        return miniChar[pos];
    }

    char& OneChar::operator[](int pos)
    {
        return miniChar[pos];
    }

    OneChar OneChar::operator=(char newChar)
    {
        // Due to the nature of char, we know it is one bite

        // Add the char to the beginning of an array of chars,
        // and then add a null terminator to the next position in the array.
        this->miniChar[0] = newChar;
        this->miniChar[1] = '\0';
        return *this;
    }

    OneChar OneChar::operator=(char* newChar)
    {
        // We need to check that the input is only Unicode and not conventional
        // strings. This can be done by checking the first character. Since
        // Unicode chars are large hex numbers, they will be negative.
        if(newChar[0] < 0 )
        {
            int index;
            // Add each non-terminating character to the char array.
            for(index = 0; newChar[index] != '\0'; index++)
            {
                this->miniChar[index] = newChar[index];
            }
            // Add a null terminator to the end of the char array
            this->miniChar[index] = '\0';
        }
        else
        {
            ioc << cat_error << "WARNING: " " is only for using multi-byte "
            << "Unicode chars. Use ' ' for ASCII characters." <<io_end;
        }
        return *this;
    }


    OneChar OneChar::operator=(OneChar newChar)
    {
        int index;
         // Add each non-terminating character to the char array.
        for(index = 0; newChar.miniChar[index] != '\0'; index++)
        {
            this->miniChar[index] = newChar.miniChar[index];
        }
        // Add a null-terminator to the end of the char array
        this->miniChar[index] = '\0';
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const OneChar& ochr)
    {
        // To display the full OneChar we loop through the char array
        // until a null-terminator is found.
        for(int i = 0; ochr.miniChar[i] != '\0'; ++i)
        {
            os<< ochr.miniChar[i];
        }
        return os;
    }

    bool operator==(const OneChar& ochr, const OneChar& newChar)
    {
        // Two OneChars are equal if every value in their arrays are equivalent
        for(int i = 0; newChar.miniChar[i] != '\0'; ++i)
        {
            if(ochr.miniChar[i] != newChar.miniChar[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator==(const OneChar& ochr, char* newChar)
    {
        for(int i = 0; newChar[i] != '\0'; ++i)
        {
            // Check if each position in the char* is equal to the
            // same position in the OneChar
            if(ochr.miniChar[i] != newChar[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator==(const OneChar& ochr, char newChar)
    {
        // Compare to the first char in the char array,
        // And make sure the OneChar is only 1 byte.
        return ((newChar == ochr[0]) && (ochr[1] == '\0'));
    }

    bool operator<(const OneChar& ochr, const OneChar &newChar)
    {
        for(int i = 0; ochr[i] != '\0'; ++i)
        {
            // If newChar has reached the end then ochr is larger.
            if(newChar[i] == '\0')
            {
                return false;
            }
            if(ochr[i] < newChar[i])
            {
                return true;
            }
        }
        return false;
    }

    /*************************************************************************
    // The OneString functions begin here
    *************************************************************************/
    // Initialize the OneString with a len (size) of 0
    template <const int oneSize>
    OneString<oneSize>::OneString():len(0){}

    // Initialization with const char* ""
    template <const int oneSize>
    OneString<oneSize>::OneString(const char* str):len(0)
    {
        append(str);
    }

    // Initialization with std::string. To do this, we convert the std::string
    // to a char* and call the OneString constructor for char*
    template <const int oneSize>
    OneString<oneSize>::OneString(std::string str):OneString(str.c_str())
    {
    }

     // Single char initialization
    template <const int oneSize>
    OneString<oneSize>::OneString(char ch):len(0)
    {
        // Insert the char into the first OneChar in the OneChar array (master array)
        master[len][0] = ch;
        master[len][1] = '\0';
        len = 1;
    }

    // OneChar initialization
    template <const int oneSize>
    OneString<oneSize>::OneString(OneChar ch):len(0)
    {
        // Insert the OneChar into the first position of the master array
        master[len] = ch;
        len = 1;
    }

    // Define a macro to avoid repeating large amounts of code
    #define ONESTRING_CONSTRUCTOR \
    { \
        int i = 0; \
        /* Only copy upto the size of the other OneString or until the OneString is full */ \
        while((i < ostr.size()) && (i <= MAX_SIZE)) \
        {\
            master[i] = ostr[i];  /*copy*/ \
            i++; \
        }\
        len = i;   /*make sure to set len appropriately*/ \
    }
    // Copy constructor for OneString<8>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<8>& ostr):len(0)
    {
        ONESTRING_CONSTRUCTOR;
    }

     // Copy constructor for OneString<16>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<16>& ostr):len(0)
    {
        ONESTRING_CONSTRUCTOR;
    }

     // Copy constructor for OneString<32>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<32>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

     // Copy constructor for OneString<64>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<64>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

    // Copy constructor for OneString<128>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<128>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

    // Copy constructor for OneString<256>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<256>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

    // Copy constructor for OneString<512>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<512>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

    // Copy constructor for OneString<1024>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<1024>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

    // Copy constructor for OneString<2048>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<2048>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

    // Copy constructor for OneString<4096>
    template <const int oneSize>
    OneString<oneSize>::OneString(const OneString<4096>& ostr):len(0)
    {
       ONESTRING_CONSTRUCTOR;
    }

    template <const int oneSize>
    int OneString<oneSize>::size() const
    {
        // Returns how many OneChars are in the OneString
        return len;
    }

    template <const int oneSize>
    OneChar OneString<oneSize>::at(int pos)
    {
        // Only return a true value if the position is within the proper bounds
        if ((pos < len) && (pos >= 0))
            return master[pos];
        else
        {
            // Give a warning and return an empty OneChar
            ioc << cat_error << ta_bold << fg_red  <<
             "OneString Error: Index Out of Bounds" <<io_end;
            OneChar err;
            return err;
        }
    }

    #define EQUALS_FUNCT \
    {\
        /* Two OneStrings are only equal if they are the same size and */ \
        /* have the exact same OneChars */ \
        if(len == ostr.size()) \
        { \
            for(int i = 0; i < len; ++i) \
            { \
                if(!(master[i] == ostr[i])) \
                    return false; \
            } \
            return true; \
        } \
        return false; \
    }
    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<8>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<16>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<32>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<64>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<128>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<256>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<512>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<1024>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<2048>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const OneString<4096>& ostr) const
    {
        EQUALS_FUNCT;
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(const char* ostr) const
    {
        // Convert the char* to a OneString and then call the equals function
        OneString<oneSize> compareStr = ostr;
        return this->equals(compareStr);
    }

    template <const int oneSize>
    bool OneString<oneSize>::equals(std::string ostr) const
    {
        // Convert the std::string to a char* and call equals
        return equals(ostr.c_str());
    }

    // Define a macro to avoid repeating the same code over and over
    #define APPEND_FUNCT \
    { \
        /* Don't append if combining the two OneStrings will overfill the OneString*/ \
        if(len + ostr.size() > MAX_SIZE) \
        { \
            ioc << cat_error << ta_bold << fg_red << "OneString Error: Append() exceeds " <<\
            "MAX_SIZE for OneString. Use larger OneString" <<io_end;\
        }\
        else\
        {\
            /* Insert each OneChar at the very end of the OneString*/ \
            for(int i= 0; i < ostr.size(); ++i)\
            {\
                master[len] = ostr[i];\
                len++;\
            }\
        } \
    }
    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<8>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<16>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<32>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<64>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<128>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<256>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<512>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<1024>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<2048>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const OneString<4096>& ostr)
    {
        APPEND_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(const char* ostr)
    {
        int index = 0;
        while(ostr[index] != '\0')
        {
             // Check if the OneString is full
            if(len > MAX_SIZE)
            {
                ioc << cat_error << ta_bold << fg_red <<
                "OneString Error: Input string is too large." << io_end;
                OneString();
                break;
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
             ++ len;
        }
    }

    template <const int oneSize>
    void OneString<oneSize>::append(std::string ostr)
    {
        // Convert the std::string and call append
        append(ostr.c_str());
    }

    template <const int oneSize>
    void OneString<oneSize>::append(char ochar)
    {
        // Don't append if the OneString is full
        if(len >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red  << "OneString Error: "<<
            "Append() exceeds MAX_SIZE for OneString. Use larger OneString" <<io_end;
            return;
        }
        // Otherwise, add the char to the end of the OneString and increase size
        // Not sure if it would actually be beneficial to call parseChar() here
        master[len][0] = ochar;
        master[len][1] = '\0';
        len++;
    }

    template <const int oneSize>
    void OneString<oneSize>::append(OneChar ochar)
    {
        // Don't append if the OneString is full
        if(len >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "Append() exceeds MAX_SIZE for OneString. Use larger OneString" <<io_end;
            return;
        }
        // Add the OneChar to the end of the OneString
        master[len] = ochar;
        len++;
    }

    /***************************************************************************
    * When it comes to efficiency, we'll need to see if it is better to shift
    * every item to the right or to make three OneStrings (left of insert, insert,
    * and right of insert) and append them to each other.
    *************************************************************************/

    // Create a macro to avoid repeating code (yes, I see the irony of repeating this comment)
    #define INSERT_FUNCT \
    { \
        int insertSize = ostr.size(); \
        /* Check if the position is valid*/ \
        if(pos < 0 || pos > len ) \
        { \
            ioc << cat_error << ta_bold << fg_red << \
            "OneString Error: Index Out of Bounds"<<io_end; \
            return; \
        } \
        /* Don't insert if the insertion will overfill */ \
        if(pos >= MAX_SIZE || (len + insertSize > MAX_SIZE)) \
        {\
            ioc << cat_error << ta_bold << fg_red << \
            "OneString Error: Insert() exceeds MAX_SIZE. Use " \
            <<" different OneString size"<<io_end; \
            return; \
        } \
        /* If we are not inserting at the end, shift everything to the right */ \
        if(pos != len) \
        { \
            /* Shift to right how ever long the insert OneString is */ \
            for(int i = len - 1; i >= pos; i--) \
                master[i + insertSize] = master[i]; \
        } \
        /* Insert OneString into empty slots */ \
        for(int off = 0; off < insertSize; off++) \
            master[pos + off] = ostr[off]; \
        len += ostr.size(); \
    }
    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<8>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<16>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<32>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<64>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<128>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<256>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<512>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<1024>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<2048>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const OneString<4096>& ostr)
    {
        INSERT_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, const char* ostr)
    {
        // Convert to OneString then insert
        OneString<oneSize> temp = ostr;
        insert(pos, temp);
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, std::string ostr)
    {
        // Convert to OneString then insert
        OneString<oneSize> temp = ostr;
        insert(pos, temp);
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, char ochar)
    {
        // Don't insert if there will be overfilling
        if(len == MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "insert() exceeds MAX_SIZE. Use different OneString size"<<io_end;
            return;
        }
        // Make sure the index is valid
        if(pos < 0 || pos > len)
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error: Index Out of Bounds"<<io_end;
            return;
        }
        // Shift everything after the index over one slot
        for(int i = len - 1; i >= pos; i--)
            master[i + 1] = master[i];
        master[pos][0] = ochar;
        master[pos][1] = '\0';
        len++;
    }

    template <const int oneSize>
    void OneString<oneSize>::insert(int pos, OneChar ochar)
    {
        // Don't insert if there will be overfilling
        if(len == MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "Insert() exceeds MAX_SIZE. Use different OneString size"<<io_end;
            return;
        }
        // Make sure the index is valid
        if(pos < 0 || pos > len)
        {
            ioc << cat_error << ta_bold << fg_red  << "OneString Error: " <<
            " Index Out of Bounds"<<io_end;
            return;
        }
        // Shift everything after the index over one slot
        for(int i = len - 1; i >= pos; i--)
            master[i + 1] = master[i];
        master[pos] = ochar;
        len++;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::substr(int pos, int sublen)
    {
        // Check sublen flag. If -1, then go to the end of the OneString
        if(sublen == -1)
        {
            // Calculate the size from the position to the end of the OneString
            sublen = len - pos;
        }
        // Check for valid index
        if((pos >= MAX_SIZE) || (pos < 0))
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error:" <<
            " Index Out of Bounds" << io_end;
            return *this;
        }
        // If the substring size is too large throw an error
        else if(sublen + pos >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "Size exceeds limits of OneString"<<io_end;
            return *this;
        }
        else
        {
            // Create a new OneString and append each character that is found
            // in the substring
            OneString<oneSize> newPaw;
            for(int i = 0; i < sublen; i++)
            {
                newPaw.append(master[pos]);
                pos++;
            }
            return newPaw;
        }
    }

    template <const int oneSize>
    void OneString<oneSize>::push_back(char ch)
    {
        append(ch);
    }

    template <const int oneSize>
    void OneString<oneSize>::pop_back()
    {
        // Cannot pop an empty OneString
        if(len == 0)
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "Cannot POP an empty OneString" <<io_end;
        else
        {
            // Clear the OneChar at the end
            master[len - 1] = '\0';
            len--;
        }
    }

    #define SWAP_FUNCT \
    { \
        /* Cannot swap if they are not of the same OneString type */ \
        if(str.size() > MAX_SIZE) \
        { \
            ioc << cat_error << ta_bold << fg_red << "OneString Error" <<\
            ": The OneString argument is too large to" \
            << " swap with" <<io_end; \
        } \
        else \
        { \
            /* Swap the values */ \
            OneString<oneSize> temp = *this; \
            *this = str; \
            str = temp; \
        } \
    }
    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<8>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<16>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<32>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<64>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<128>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<256>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<512>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<1024>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<2048>& str)
    {
        SWAP_FUNCT;
    }

    template <const int oneSize>
    void OneString<oneSize>::swap(OneString<4096>& str)
    {
        SWAP_FUNCT;
    }


    template <const int oneSize>
    int OneString<oneSize>::length()
    {
        // Return the MAX_SIZE for OneString multiplied by number of bytes
        // in a OneChar (5)
        return (MAX_SIZE * 5);
    }

    template <const int oneSize>
    int OneString<oneSize>::max_size()
    {
        // Return the largest possible size for this OneString
        return MAX_SIZE;
    }

    template <const int oneSize>
    bool OneString<oneSize>::empty() const
    {
        return (len == 0);
    }

    template <const int oneSize>
    void OneString<oneSize>::clear()
    {
        // Reset all OneChar values
        for(int i=0; i < len; i++)
            master[i] = '\0';
        len = 0;
    }

    template <const int oneSize>
    OneChar OneString<oneSize>::operator [](int pos) const
    {
        if ((pos < len) && (pos >= 0))
            return master[pos];
        else
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error" <<
            ": INDEX OUT OF BOUNDS" <<io_end;
            OneChar err;
            return err;
        }
    }

    // Not sure about how to relate this to at()
    template <const int oneSize>
    OneChar& OneString<oneSize>::operator [](int pos)
    {
        if ((pos < len) && (pos >= 0))
            return master[pos];
        else
        {
            // Display error and return last character
            ioc << cat_error << ta_bold << fg_red << "OneString Error" <<
            ": INDEX OUT OF BOUNDS" <<io_end;
            return master[len - 1];
        }
    }

    #define ASSIGN_OP \
    { \
        int i = 0; \
        /* Copy each OneChar from the OneString argument */ \
        while((i < newostr.size()) && (i <= MAX_SIZE)) \
        { \
            this->master[i] = newostr[i]; \
            i++; \
        } \
        len = i; \
        return *this; \
    }
    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<8> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<16> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<32> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<64> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<128> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<256> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<512> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<1024> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<2048> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneString<4096> newostr)
    {
        ASSIGN_OP;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(const char* str)
    {
        this->len = 0;
        int index = 0;
        // Loop to end of char*
        while(str[index] != '\0')
        {
            // Check if the OneString is full
            if(len > MAX_SIZE)
            {
                ioc << cat_error << ta_bold << fg_red << "OneString Error" <<
                ": Input String is Too Large" <<io_end;
                *this = OneString();
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
            this->len++; // Set the size for the OneString
        }
        return *this;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(std::string str)
    {
        // Convert the std::string and initialize a OneString
        *this = str.c_str();
        return *this;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(char ch)
    {
        // Directly set the first OneChar in the OneString
        this->master[0][0] = ch;
        this->master[0][1] = '\0';
        this->len = 1;
        return *this;
    }

    template <const int oneSize>
    OneString<oneSize> OneString<oneSize>::operator=(OneChar ch)
    {
        // Directly set the first OneChar in the OneString
        this->master[0] = ch;
        this->len = 1;
        return *this;
    }

    // Private function
    template <const int oneSize>
    void OneString<oneSize>::parseChar(const char* str, int index, int bytes)
    {
        // Bytes indicates the size of the desired parsing area while
        // index indicates the start of the parse area. Loop through the parse
        // area and add each character to the current OneChar in the OneString
        for(int i = 0; i < bytes; ++i)
            master[len][i] = str[index + i];
        master[len][bytes] = '\0'; // Terminate the OneChar
    }

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
