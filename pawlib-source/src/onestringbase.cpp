/*PawLib Library, version 1.3
* OneString Class
* OneString is a dynamic-allocation-free replacement for std::string
* Last Updated: November 12, 2015
*
* Scott Taylor
* MousePaw Games
*/

#include "onestringbase.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <iochannel.hpp>


namespace pawlib
{

    /*************************************************************************
    // The OneString functions begin here
    *************************************************************************/
    // Initialize the OneString with a len (size) of 0
    OneStringBase::OneStringBase():len(0)
    {
        // Initialize variables to standard values
        MAX_SIZE = 8;
        master = new AscChar[8];
        strType = QUICK_TYPE;
    }

    OneStringBase::OneStringBase(int tempSize, bool type):len(0)
    {
        // Allocate memory for OneString
        if(type == ONE_TYPE)
        {
            master = new UniChar[tempSize];
        }
        // Or allocate memory for QuickString
        else
        {
            master = new AscChar[tempSize];
        }

        MAX_SIZE = tempSize;
        strType = type;
    }

     // Single char initialization
    OneStringBase::OneStringBase(char ch, int tempSize, bool type):len(0)
    {
         // Allocate memory for OneString
        if(type == ONE_TYPE)
        {
            master = new UniChar[tempSize];
        }
        // Or allocate memory for QuickString
        else
        {
            master = new AscChar[tempSize];
        }

        MAX_SIZE = tempSize;
        strType = type;

        // Insert the char into the first OneChar in the OneChar array (master array)
        master[len][0] = ch;


        //Add null terminator if OneString type
        if(type == ONE_TYPE)
        {
            master[len][1] = '\0';
        }
        len = 1;
    }

    // OneChar initialization
    OneStringBase::OneStringBase(const OneChar& ch, int tempSize, bool type):len(0)
    {
         // Allocate memory for OneString
        if(type == ONE_TYPE)
        {
            master = new UniChar[tempSize];
        }
        // Or allocate memory for QuickString
        else
        {
            master = new AscChar[tempSize];
        }

        MAX_SIZE = tempSize;
        strType = type;

        // Insert the OneChar into the first position of the master array
        master[len] = ch;
        len = 1;
    }

    // Copy constructor for OneStringBase
    OneStringBase::OneStringBase(const OneStringBase& ostr, int tempSize, bool type):len(0)
    {
         /* Allocate memory for OneString*/
        if(type == ONE_TYPE)
        {
            master = new UniChar[tempSize];
        }
        /* Or allocate memory for QuickString */
        else
        {
            master = new AscChar[tempSize];
        }

        MAX_SIZE = tempSize;
        strType = type;
        int i = 0;

        /* Only copy upto the size of the other OneString or until the OneStringBase is full */
        while((i < ostr.size()) && (i < MAX_SIZE))
        {
            master[i] = *ostr[i];  /*copy*/
            i++;
        }
        len = i;   /*make sure to set len appropriately*/
    }

    bool OneStringBase::getType() const
    {
        return strType;
    }

    int OneStringBase::size() const
    {
        // Returns how many OneChars are in the OneString
        return len;
    }

    void OneStringBase::incLen()
    {
        ++len;
    }

    void OneStringBase::setLen(int newLen)
    {
        len = newLen;
    }

    OneChar& OneStringBase::at(int pos)
    {
        // Only return a true value if the position is within the proper bounds
        if ((pos < len) && (pos >= 0))
            return (master[pos]);
        else
        {
            // Give a warning and return an empty OneChar
            ioc << cat_error << ta_bold << fg_red  <<
             "OneString Error: Index Out of Bounds" <<io_end;
            return (master[len - 1]);
        }
    }

    bool OneStringBase::equals(const OneStringBase& ostr) const
    {
        /* Two OneStrings are only equal if they are the same size and
          have the exact same OneChars */
        if(len == ostr.size())
        {
            for(int i = 0; i < len; ++i)
            {
                if(!(master[i] == *ostr[i]))
                    return false;
            }
            return true;
        }
        return false;
    }


    bool OneStringBase::equals(std::string ostr) const
    {
        // Convert the std::string to a char* and call equals
        return equals(ostr.c_str());
    }

    void OneStringBase::append(const OneStringBase& ostr)
    {
        /* Don't append if combining the two OneStrings will overfill the OneStringBase*/
        if(len + ostr.size() > MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "OneStringBase Error: Append() exceeds " <<
            "MAX_SIZE for OneStringBase. Use larger OneStringBase" <<io_end;
        }
        else
        {
            /* Insert each OneChar at the very end of the OneStringBase*/
            for(int i= 0; i < ostr.size(); ++i)
            {
                master[len] = *ostr[i];
                len++;
            }
        }
    }

    void OneStringBase::append(std::string ostr)
    {
        // Convert the std::string and call append
        append(ostr.c_str());
    }

    void OneStringBase::append(char ochar)
    {
        // Don't append if the OneStringBase is full
        if(len >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red  << "OneString Error: "<<
            "Append() exceeds MAX_SIZE for OneString. Use larger OneString" <<io_end;
            return;
        }
        // Otherwise, add the char to the end of the OneStringBase and increase size
        // Not sure if it would actually be beneficial to call parseChar() here
        master[len][0] = ochar;

        //If we have a OneString, add the null terminator
        if(strType == ONE_TYPE)
        {
            master[len][1] = '\0';
        }
        len++;
    }

    void OneStringBase::append(const OneChar& ochar)
    {
        // Don't append if the OneStringBase is full
        if(len >= MAX_SIZE)
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "Append() exceeds MAX_SIZE for OneString. Use larger OneString" <<io_end;
            return;
        }
        // Add the OneChar to the end of the OneStringBase
        master[len] = ochar;
        len++;
    }

    /***************************************************************************
    * When it comes to efficiency, we'll need to see if it is better to shift
    * every item to the right or to make three OneStrings (left of insert, insert,
    * and right of insert) and append them to each other.
    *************************************************************************/
    void OneStringBase::insert(int pos, const OneStringBase& ostr)
    {
         int insertSize = ostr.size();
        /* Check if the position is valid*/
        if(pos < 0 || pos > len )
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneStringBase Error: Index Out of Bounds"<<io_end;
            return;
        }

        /* Don't insert if the insertion will overfill */
        if(pos >= MAX_SIZE || (len + insertSize > MAX_SIZE))
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneStringBase Error: Insert() exceeds MAX_SIZE. Use "
            <<" different OneStringBase size"<<io_end;
            return;
        }

        /* If we are not inserting at the end, shift everything to the right */
        if(pos != len)
        {
            /* Shift to right how ever long the insert OneStringBase is */
            for(int i = len - 1; i >= pos; i--)
                master[i + insertSize] = master[i];
        }
        /* Insert OneString into empty slots */
        for(int off = 0; off < insertSize; off++)
            master[pos + off] = *ostr[off];
        len += ostr.size();
    }

    void OneStringBase::insert(int pos, std::string ostr)
    {
        // Convert the std::string to c-string and call function
        insert(pos, ostr.c_str());
    }

    void OneStringBase::insert(int pos, char ochar)
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

        // If a OneString, add null terminator
        if(strType == ONE_TYPE)
        {
            master[pos][1] = '\0';
        }
        len++;
    }

    void OneStringBase::insert(int pos, OneChar* ochar)
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

        // Insert character
        master[pos] = *ochar;
        len++;
    }

    void OneStringBase::push_back(char ch)
    {
        append(ch);
    }

    void OneStringBase::push_back(const OneChar& ochar)
    {
        append(ochar);
    }

    void OneStringBase::pop_back()
    {
        // Cannot pop an empty OneString
        if(len == 0)
            ioc << cat_error << ta_bold << fg_red << "OneString Error: " <<
            "Cannot POP an empty OneString" <<io_end;
        else
        {
            // Clear the OneChar at the end, even though length is what's important
            master[len - 1] = '\0';
            len--;
        }
    }

    int OneStringBase::length()
    {
        // If QuickString, return the template size allocated
        if(strType == QUICK_TYPE)
        {
            return MAX_SIZE;
        }
        // If OneString, return the template size multiplied by the 5 slots
        // in each UniChar
        else
        {
            // Return the MAX_SIZE for OneString multiplied by number of bytes
            // in a OneChar (5)
            return (MAX_SIZE * 5);
        }
    }

    int OneStringBase::max_size()
    {
        // Return the largest possible size for this OneString
        return MAX_SIZE;
    }

    bool OneStringBase::empty() const
    {
        return (len == 0);
    }

    void OneStringBase::clear()
    {
        // Reset all OneChar values
        for(int i=0; i < len; i++)
            master[i] = '\0';
        len = 0;
    }

    // Operators

    OneChar* OneStringBase::operator [](int pos) const
    {
        if ((pos < len) && (pos >= 0))
            return &(master[pos]);
        else
        {
            ioc << cat_error << ta_bold << fg_red << "OneString Error" <<
            ": INDEX OUT OF BOUNDS" <<io_end;
           return &(master[len - 1]);
        }
    }

    // Not sure about how to relate this to at()
    OneChar& OneStringBase::operator [](int pos)
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

    OneStringBase& OneStringBase::operator=(const OneStringBase& newostr)
    {
        strType = newostr.getType();
        int i = 0;

        // Copy each OneChar from the OneString argument
        while((i < newostr.size()) && (i <= MAX_SIZE))
        {
            master[i] = *newostr[i];
            i++;
        }
        len = i;
        return *this;
    }

    OneStringBase& OneStringBase::operator=(const char* str)
    {
        *this = assignHelper(str);
        return *this;
    }

    OneStringBase& OneStringBase::operator=(std::string str)
    {
        // Convert the std::string and initialize a OneString
        *this = str.c_str();
        return *this;
    }

    OneStringBase& OneStringBase::operator=(char ch)
    {
        *this = assignChar(ch);
        return *this;
    }

    OneStringBase& OneStringBase::operator=(OneChar* ch)
    {
        // Directly set the first OneChar in the OneString
        this->master[0] = *ch;
        this->len = 1;
        return *this;
    }

    bool OneStringBase::operator==(const OneStringBase& ostr2)
    {
        // Goes to OneString version
        return equals(ostr2);
    }

    bool OneStringBase::operator==(const char* ostr2)
    {
        // Goes to char* version
        return equals(ostr2);
    }

    bool OneStringBase::operator==(std::string ostr2)
    {
        // Goes to string version
        return equals(ostr2);
    }

    bool OneStringBase::operator<(const OneStringBase& ostr2)
    {
        return lessThanStr(ostr2);
    }


    bool OneStringBase::operator<(const char* ostr2)
    {
        return lessThanCharP(ostr2);
    }


    bool OneStringBase::operator<(std::string ostr2)
    {
        return lessThanCharP(ostr2.c_str());
    }

    bool OneStringBase::operator<=(const OneStringBase& ostr2)
    {
        // Cannot call  greater-than because an infinite loop would occur
        return (((*this) < ostr2) || ((*this) == ostr2));
    }

    bool OneStringBase::operator<=(const char* ostr2)
    {
        return (((*this) < ostr2)|| ((*this) == ostr2));
    }

    bool OneStringBase::operator<=(std::string ostr2)
    {
        return (((*this) < ostr2)|| ((*this) == ostr2));
    }

    bool OneStringBase::operator>(const OneStringBase& ostr2)
    {
        // Call previously made functions
        return(!((*this) <= ostr2));
    }

    bool OneStringBase::operator>(const char* ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneStringBase::operator>(std::string ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneStringBase::operator>=(const OneStringBase& ostr2)
    {
        // Use previously made functions
        return(!((*this) < ostr2));
    }

    bool OneStringBase::operator>=(const char* ostr2)
    {
        // Use previously made functions
        return(!((*this) < ostr2));
    }

    bool OneStringBase::operator>=(std::string ostr2)
    {
        // Use previously made functions
        return(!((*this) < ostr2));
    }

    void OneStringBase::operator+=(const OneStringBase& ostr2)
    {
        append(ostr2);
    }

    void OneStringBase::operator+=(const char* ostr2)
    {
        append(ostr2);
    }

    void OneStringBase::operator+=(std::string ostr2)
    {
        append(ostr2);
    }

    void OneStringBase::operator+=(char ochar)
    {
        append(ochar);
    }

    void OneStringBase::operator+=(const OneChar& ochar)
    {
        append(ochar);
    }

}
