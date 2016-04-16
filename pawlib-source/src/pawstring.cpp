/*PawLib Library, version 1.3
* PawString Class
* PawString is a dynamic-allocation-free replacement for std::string
* Last Updated: November 12, 2015
*
* Scott Taylor
* MousePaw Games
*/

#include "pawstring.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <iochannel.hpp>


namespace pawlib
{
    /*************************************************************************
    // The PawChar functions start here
    **************************************************************************/
    PawChar::PawChar()
    {
        //miniChar[0] = '\0'; code profiling
    }

    char PawChar::operator[](int pos) const
    {
        return miniChar[pos];
    }

    char& PawChar::operator[](int pos)
    {
        return miniChar[pos];
    }

    PawChar PawChar::operator=(char newChar)
    {
        // Due to the nature of char, we know it is one bite

        // Add the char to the beginning of an array of chars,
        // and then add a null terminator to the next position in the array.
        this->miniChar[0] = newChar;
        this->miniChar[1] = '\0';
        return *this;
    }

    PawChar PawChar::operator=(char* newChar)
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


    PawChar PawChar::operator=(PawChar newChar)
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

    std::ostream& operator<<(std::ostream& os, const PawChar& pchr)
    {
        // To display the full PawChar we loop through the char array
        // until a null-terminator is found.
        for(int i = 0; pchr.miniChar[i] != '\0'; ++i)
        {
            os<< pchr.miniChar[i];
        }
        return os;
    }

    bool operator==(const PawChar& pchr, const PawChar& newChar)
    {
        // Two PawChars are equal if every value in their arrays are equivalent
        for(int i = 0; newChar.miniChar[i] != '\0'; ++i)
        {
            if(pchr.miniChar[i] != newChar.miniChar[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator==(const PawChar& pchr, char* newChar)
    {
        for(int i = 0; newChar[i] != '\0'; ++i)
        {
            // Check if each position in the char* is equal to the
            // same position in the PawChar
            if(pchr.miniChar[i] != newChar[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator==(const PawChar& pchr, char newChar)
    {
        // Compare to the first char in the char array,
        // And make sure the PawChar is only 1 byte.
        return ((newChar == pchr[0]) && (pchr[1] == '\0'));
    }

    bool operator<(const PawChar& pchr, const PawChar &newChar)
    {
        for(int i = 0; pchr[i] != '\0'; ++i)
        {
            // If newChar has reached the end then pchr is larger.
            if(newChar[i] == '\0')
            {
                return false;
            }
            if(pchr[i] < newChar[i])
            {
                return true;
            }
        }
        return false;
    }

    /*************************************************************************
    // The PawString functions begin here
    *************************************************************************/
    // Initialize the PawString with a len (size) of 0
    template <const int pawSize>
    PawString<pawSize>::PawString():len(0){}

    // Initialization with const char* ""
    template <const int pawSize>
    PawString<pawSize>::PawString(const char* str):len(0)
    {
        append(str);
    }

    // Initialization with std::string. To do this, we convert the std::string
    // to a char* and call the PawString constructor for char*
    template <const int pawSize>
    PawString<pawSize>::PawString(std::string str):PawString(str.c_str())
    {
    }

     // Single char initialization
    template <const int pawSize>
    PawString<pawSize>::PawString(char ch):len(0)
    {
        // Insert the char into the first PawChar in the PawChar array (master array)
        master[len][0] = ch;
        master[len][1] = '\0';
        len = 1;
    }

    // PawChar initialization
    template <const int pawSize>
    PawString<pawSize>::PawString(PawChar ch):len(0)
    {
        // Insert the PawChar into the first position of the master array
        master[len] = ch;
        len = 1;
    }

    // Define a macro to avoid repeating large amounts of code
    #define PAWSTRING_CONSTRUCTOR \
    { \
        int i = 0; \
        /* Only copy upto the size of the other PawString or until the PawString is full */ \
        while((i < pstr.size()) && (i <= MAX_SIZE)) \
        {\
            master[i] = pstr[i];  /*copy*/ \
            i++; \
        }\
        len = i;   /*make sure to set len appropriately*/ \
    }
    // Copy constructor for PawString<8>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<8>& pstr):len(0)
    {
        PAWSTRING_CONSTRUCTOR;
    }

     // Copy constructor for PawString<16>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<16>& pstr):len(0)
    {
        PAWSTRING_CONSTRUCTOR;
    }

     // Copy constructor for PawString<32>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<32>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

     // Copy constructor for PawString<64>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<64>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

    // Copy constructor for PawString<128>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<128>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

    // Copy constructor for PawString<256>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<256>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

    // Copy constructor for PawString<512>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<512>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

    // Copy constructor for PawString<1024>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<1024>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

    // Copy constructor for PawString<2048>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<2048>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

    // Copy constructor for PawString<4096>
    template <const int pawSize>
    PawString<pawSize>::PawString(const PawString<4096>& pstr):len(0)
    {
       PAWSTRING_CONSTRUCTOR;
    }

    template <const int pawSize>
    int PawString<pawSize>::size() const
    {
        // Returns how many PawChars are in the PawString
        return len;
    }

    template <const int pawSize>
    PawChar PawString<pawSize>::at(int pos)
    {
        // Only return a true value if the position is within the proper bounds
        if ((pos < len) && (pos >= 0))
            return master[pos];
        else
        {
            // Give a warning and return an empty PawChar
            ioc << cat_error << ta_bold << fg_red  <<
             "PawString Error: Index Out of Bounds" <<io_end;
            PawChar err;
            return err;
        }
    }

    #define EQUALS_FUNCT \
    {\
        /* Two PawStrings are only equal if they are the same size and */ \
        /* have the exact same PawChars */ \
        if(len == pstr.size()) \
        { \
            for(int i = 0; i < len; ++i) \
            { \
                if(!(master[i] == pstr[i])) \
                    return false; \
            } \
            return true; \
        } \
        return false; \
    }
    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<8>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<16>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<32>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<64>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<128>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<256>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<512>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<1024>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<2048>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const PawString<4096>& pstr) const
    {
        EQUALS_FUNCT;
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(const char* pstr) const
    {
        // Convert the char* to a PawString and then call the equals function
        PawString<pawSize> compareStr = pstr;
        return this->equals(compareStr);
    }

    template <const int pawSize>
    bool PawString<pawSize>::equals(std::string pstr) const
    {
        // Convert the std::string to a char* and call equals
        return equals(pstr.c_str());
    }

    // Define a macro to avoid repeating the same code over and over
    #define APPEND_FUNCT \
    { \
        /* Don't append if combining the two PawStrings will overfill the PawString*/ \
        if(len + pstr.size() > MAX_SIZE) \
        { \
            ioc << cat_error << ta_bold << fg_red << "PawString Error: Append() exceeds " <<\
            "MAX_SIZE for PawString. Use larger PawString" <<io_end;\
        }\
        else\
        {\
            /* Insert each PawChar at the very end of the PawString*/ \
            for(int i= 0; i < pstr.size(); ++i)\
            {\
                master[len] = pstr[i];\
                len++;\
            }\
        } \
    }
    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<8>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<16>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<32>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<64>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<128>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<256>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<512>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<1024>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<2048>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const PawString<4096>& pstr)
    {
        APPEND_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(const char* pstr)
    {
        int index = 0;
        while(pstr[index] != '\0')
        {
             // Check if the PawString is full
            if(len > MAX_SIZE)
            {
                ioc << cat_error << ta_bold << fg_red <<
                "PawString Error: Input string is too large." << io_end;
                PawString();
                break;
            }

            // Can tell how many bytes by masking the first character
            switch(pstr[index] & 0xF0)
            {
                case 0xF0 :
                    {
                        // Insert a 4 byte Unicode Char into the PawString
                        parseChar(pstr, index, 4);
                        index+=4;
                        break;
                    }
                case 0xE0 :
                    {
                        // Insert a 3 byte Unicode Char into the PawString
                        parseChar(pstr, index, 3);
                        index+=3;
                        break;
                    }
                case 0xC0:
                    {
                        // Insert a 2 byte Unicode Char into the PawString
                        parseChar(pstr, index, 2);
                        index+=2;
                        break;
                    }
                case 0x80:
                    {
                        ioc << cat_error << ta_bold << fg_red <<
                        "PawString Error: Invalid Character In String At Position: " << index << io_end;
                        return;
                    }
                default :
                    {
                        // Insert a standard char
                        parseChar(pstr, index, 1);
                        ++index;
                    }

            }
             ++ len;
        }
    }

    template <const int pawSize>
    void PawString<pawSize>::append(std::string pstr)
    {
        // Convert the std::string and call append
        append(pstr.c_str());
    }

    template <const int pawSize>
    void PawString<pawSize>::append(char pchar)
    {
        // Don't append if the PawString is full
        if(len >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red  << "PawString Error: "<<
            "Append() exceeds MAX_SIZE for PawString. Use larger PawString" <<io_end;
            return;
        }
        // Otherwise, add the char to the end of the PawString and increase size
        // Not sure if it would actually be beneficial to call parseChar() here
        master[len][0] = pchar;
        master[len][1] = '\0';
        len++;
    }

    template <const int pawSize>
    void PawString<pawSize>::append(PawChar pchar)
    {
        // Don't append if the PawString is full
        if(len >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "PawString Error: " <<
            "Append() exceeds MAX_SIZE for PawString. Use larger PawString" <<io_end;
            return;
        }
        // Add the PawChar to the end of the PawString
        master[len] = pchar;
        len++;
    }

    /***************************************************************************
    * When it comes to efficiency, we'll need to see if it is better to shift
    * every item to the right or to make three PawStrings (left of insert, insert,
    * and right of insert) and append them to each other.
    *************************************************************************/

    // Create a macro to avoid repeating code (yes, I see the irony of repeating this comment)
    #define INSERT_FUNCT \
    { \
        int insertSize = pstr.size(); \
        /* Check if the position is valid*/ \
        if(pos < 0 || pos > len ) \
        { \
            ioc << cat_error << ta_bold << fg_red << \
            "PawString Error: Index Out of Bounds"<<io_end; \
            return; \
        } \
        /* Don't insert if the insertion will overfill */ \
        if(pos >= MAX_SIZE || (len + insertSize > MAX_SIZE)) \
        {\
            ioc << cat_error << ta_bold << fg_red << \
            "PawString Error: Insert() exceeds MAX_SIZE. Use " \
            <<" different PawString size"<<io_end; \
            return; \
        } \
        /* If we are not inserting at the end, shift everything to the right */ \
        if(pos != len) \
        { \
            /* Shift to right how ever long the insert PawString is */ \
            for(int i = len - 1; i >= pos; i--) \
                master[i + insertSize] = master[i]; \
        } \
        /* Insert PawString into empty slots */ \
        for(int off = 0; off < insertSize; off++) \
            master[pos + off] = pstr[off]; \
        len += pstr.size(); \
    }
    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<8>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<16>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<32>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<64>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<128>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<256>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<512>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<1024>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<2048>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const PawString<4096>& pstr)
    {
        INSERT_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, const char* pstr)
    {
        // Convert to PawString then insert
        PawString<pawSize> temp = pstr;
        insert(pos, temp);
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, std::string pstr)
    {
        // Convert to PawString then insert
        PawString<pawSize> temp = pstr;
        insert(pos, temp);
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, char pchar)
    {
        // Don't insert if there will be overfilling
        if(len == MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "PawString Error: " <<
            "insert() exceeds MAX_SIZE. Use different PawString size"<<io_end;
            return;
        }
        // Make sure the index is valid
        if(pos < 0 || pos > len)
        {
            ioc << cat_error << ta_bold << fg_red << "PawString Error: Index Out of Bounds"<<io_end;
            return;
        }
        // Shift everything after the index over one slot
        for(int i = len - 1; i >= pos; i--)
            master[i + 1] = master[i];
        master[pos][0] = pchar;
        master[pos][1] = '\0';
        len++;
    }

    template <const int pawSize>
    void PawString<pawSize>::insert(int pos, PawChar pchar)
    {
        // Don't insert if there will be overfilling
        if(len == MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "PawString Error: " <<
            "Insert() exceeds MAX_SIZE. Use different PawString size"<<io_end;
            return;
        }
        // Make sure the index is valid
        if(pos < 0 || pos > len)
        {
            ioc << cat_error << ta_bold << fg_red  << "PawString Error: " <<
            " Index Out of Bounds"<<io_end;
            return;
        }
        // Shift everything after the index over one slot
        for(int i = len - 1; i >= pos; i--)
            master[i + 1] = master[i];
        master[pos] = pchar;
        len++;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::substr(int pos, int sublen)
    {
        // Check sublen flag. If -1, then go to the end of the PawString
        if(sublen == -1)
        {
            // Calculate the size from the position to the end of the PawString
            sublen = len - pos;
        }
        // Check for valid index
        if((pos >= MAX_SIZE) || (pos < 0))
        {
            ioc << cat_error << ta_bold << fg_red << "PawString Error:" <<
            " Index Out of Bounds" << io_end;
            return *this;
        }
        // If the substring size is too large throw an error
        else if(sublen + pos >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "PawString Error: " <<
            "Size exceeds limits of PawString"<<io_end;
            return *this;
        }
        else
        {
            // Create a new PawString and append each character that is found
            // in the substring
            PawString<pawSize> newPaw;
            for(int i = 0; i < sublen; i++)
            {
                newPaw.append(master[pos]);
                pos++;
            }
            return newPaw;
        }
    }

    template <const int pawSize>
    void PawString<pawSize>::push_back(char ch)
    {
        append(ch);
    }

    template <const int pawSize>
    void PawString<pawSize>::pop_back()
    {
        // Cannot pop an empty PawString
        if(len == 0)
            ioc << cat_error << ta_bold << fg_red << "PawString Error: " <<
            "Cannot POP an empty PawString" <<io_end;
        else
        {
            // Clear the PawChar at the end
            master[len - 1] = '\0';
            len--;
        }
    }

    #define SWAP_FUNCT \
    { \
        /* Cannot swap if they are not of the same PawString type */ \
        if(str.size() > MAX_SIZE) \
        { \
            ioc << cat_error << ta_bold << fg_red << "PawString Error" <<\
            ": The PawString argument is too large to" \
            << " swap with" <<io_end; \
        } \
        else \
        { \
            /* Swap the values */ \
            PawString<pawSize> temp = *this; \
            *this = str; \
            str = temp; \
        } \
    }
    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<8>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<16>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<32>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<64>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<128>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<256>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<512>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<1024>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<2048>& str)
    {
        SWAP_FUNCT;
    }

    template <const int pawSize>
    void PawString<pawSize>::swap(PawString<4096>& str)
    {
        SWAP_FUNCT;
    }


    template <const int pawSize>
    int PawString<pawSize>::length()
    {
        // Return the MAX_SIZE for PawString multiplied by number of bytes
        // in a PawChar (5)
        return (MAX_SIZE * 5);
    }

    template <const int pawSize>
    int PawString<pawSize>::max_size()
    {
        // Return the largest possible size for this PawString
        return MAX_SIZE;
    }

    template <const int pawSize>
    bool PawString<pawSize>::empty() const
    {
        return (len == 0);
    }

    template <const int pawSize>
    void PawString<pawSize>::clear()
    {
        // Reset all PawChar values
        for(int i=0; i < len; i++)
            master[i] = '\0';
        len = 0;
    }

    template <const int pawSize>
    PawChar PawString<pawSize>::operator [](int pos) const
    {
        if ((pos < len) && (pos >= 0))
            return master[pos];
        else
        {
            ioc << cat_error << ta_bold << fg_red << "PawString Error" <<
            ": INDEX OUT OF BOUNDS" <<io_end;
            PawChar err;
            return err;
        }
    }

    // Not sure about how to relate this to at()
    template <const int pawSize>
    PawChar& PawString<pawSize>::operator [](int pos)
    {
        if ((pos < len) && (pos >= 0))
            return master[pos];
        else
        {
            // Display error and return last character
            ioc << cat_error << ta_bold << fg_red << "PawString Error" <<
            ": INDEX OUT OF BOUNDS" <<io_end;
            return master[len - 1];
        }
    }

    #define ASSIGN_OP \
    { \
        int i = 0; \
        /* Copy each PawChar from the PawString argument */ \
        while((i < newPstr.size()) && (i <= MAX_SIZE)) \
        { \
            this->master[i] = newPstr[i]; \
            i++; \
        } \
        len = i; \
        return *this; \
    }
    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<8> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<16> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<32> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<64> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<128> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<256> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<512> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<1024> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<2048> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawString<4096> newPstr)
    {
        ASSIGN_OP;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(const char* str)
    {
        this->len = 0;
        int index = 0;
        // Loop to end of char*
        while(str[index] != '\0')
        {
            // Check if the PawString is full
            if(len > MAX_SIZE)
            {
                ioc << cat_error << ta_bold << fg_red << "PawString Error" <<
                ": Input String is Too Large" <<io_end;
                *this = PawString();
                return *this;
            }
            // Does it start with an F?
            if((str[index] & 0xF0) == 0xF0)
            {
                // Insert a 4 byte Unicode Char into the PawString
                parseChar(str, index, 4);
                index+=4;
            }
            // Does it start with an E?
            else if((str[index] & 0xF0) == 0xE0)
            {
                // Insert a 3 byte Unicode Char into the PawString
                parseChar(str, index, 3);
                index+=3;
            }
            // Does it start with a C?
            else if((str[index] & 0xF0) == 0xC0)
            {
                // Insert a 2 byte Unicode Char into the PawString
                parseChar(str, index, 2);
                index+=2;
            }
            // Check if the char is valid
            else if((str[index] & 0xF0) == 0x80)
            {
                ioc << cat_error << ta_bold << fg_red << "PawString Error: " <<
                " Invalid Character in String at Position: " << index <<io_end;
                break;
            }
            else
            {
                // Insert a 1-byte ASCII char
                parseChar(str, index, 1);
                index++;
            }
            this->len++; // Set the size for the PawString
        }
        return *this;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(std::string str)
    {
        // Convert the std::string and initialize a PawString
        *this = str.c_str();
        return *this;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(char ch)
    {
        // Directly set the first PawChar in the PawString
        this->master[0][0] = ch;
        this->master[0][1] = '\0';
        this->len = 1;
        return *this;
    }

    template <const int pawSize>
    PawString<pawSize> PawString<pawSize>::operator=(PawChar ch)
    {
        // Directly set the first PawChar in the PawString
        this->master[0] = ch;
        this->len = 1;
        return *this;
    }

    // Private function
    template <const int pawSize>
    void PawString<pawSize>::parseChar(const char* str, int index, int bytes)
    {
        // Bytes indicates the size of the desired parsing area while
        // index indicates the start of the parse area. Loop through the parse
        // area and add each character to the current PawChar in the PawString
        for(int i = 0; i < bytes; ++i)
            master[len][i] = str[index + i];
        master[len][bytes] = '\0'; // Terminate the PawChar
    }

    template class PawString<8>;
    template class PawString<16>;
    template class PawString<32>;
    template class PawString<64>;
    template class PawString<128>;
    template class PawString<256>;
    template class PawString<512>;
    template class PawString<1024>;
    template class PawString<2048>;
    template class PawString<4096>;
}
