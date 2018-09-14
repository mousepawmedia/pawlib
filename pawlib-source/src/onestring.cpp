#include "pawlib/onestring.hpp"

namespace pawlib
{
    /*******************************************
    * Constructors + Destructor
    *******************************************/
    OneString::OneString()
    {
        MAX_SIZE = BASE_SIZE;
        currElements = 0;
        masterArray = new OneChar[MAX_SIZE];
    }

    OneString::OneString(const char* str)
    {
        MAX_SIZE = BASE_SIZE;
        masterArray = new OneChar[MAX_SIZE];
        append(str);
    }

    OneString::OneString(const std::string& str)
    {
        MAX_SIZE = BASE_SIZE;
        masterArray = new OneChar[MAX_SIZE];
        append(str);
    }

    OneString::OneString(const OneString& str)
    {
        MAX_SIZE = BASE_SIZE;
        masterArray = new OneChar[MAX_SIZE];
        append(str);
    }

    OneString::OneString(char ch)
    {
        MAX_SIZE = BASE_SIZE;
        masterArray = new OneChar[MAX_SIZE];
        append(ch);
    }

    OneString::OneString(const OneChar& ch)
    {
        MAX_SIZE = BASE_SIZE;
        masterArray = new OneChar[MAX_SIZE];
        append(ch);
    }

    OneString::~OneString()
    {
        if (masterArray != nullptr)
        {
            delete [] masterArray;
        }
    }

    /*******************************************
    * Helpers
    *******************************************/

    OneString& OneString::assignHelper(const char* str)
    {
        currElements = 0;
        int index = 0;

        while(str[index] != '\0')
        {
            if(currElements+ 1 >= MAX_SIZE)
            {
                doubleSize();
            }

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

            currElements++;
            masterArray[currElements] = '\0';
        }
        return *this;
    }

    void OneString::parseChar(const char* str, int index, int bytes)
    {
        int theLength = length();

        for(int i = 0; i < bytes; ++i)
        {
            //master[length][i] = str[index + i];
            masterArray[theLength].addDirectly(str[index + i], i);
        }
       // master[length][bytes] = '\0';
       masterArray[theLength].addDirectly('\0', bytes);
    }

    void OneString::parseChar(const std::string& str, int index, int bytes)
    {
        int theLength = length();

        for(int i = 0; i < bytes; ++i)
        {
            //master[length][i] = str[index + i];
            masterArray[theLength].addDirectly(str[index + i], i);
        }
       // master[length][bytes] = '\0';
       masterArray[theLength].addDirectly('\0', bytes);
    }

    void OneString::doubleSize()
    {
        MAX_SIZE *= 2;

        OneChar* tempArray = new OneChar[MAX_SIZE];

        // If an old array exists...
        if(this->masterArray != nullptr)
        {
            /*memmove(
                tempArray,
                this -> masterArray,
                sizeof(OneChar) * this->currElements
            );*/

            // copy the structure to new array
            int i = 0;
            while(!(this -> masterArray[i] == '\0'))
            {
                tempArray[i] = this -> masterArray[i];
                i++;
            }
            tempArray[i] = '\0';

            // Delete the old structure.
            delete[] masterArray;
            this->masterArray = nullptr;
        }

        // Store the new structure.
        this->masterArray = tempArray;
    }

    /*******************************************
    * Access
    *******************************************/

    OneChar OneString::at(int pos) const
    {
        if (pos < 0 || pos > currElements)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Index out of Bounds" << io_end;
        }

        return masterArray[pos];
    }

    bool OneString::empty() const
    {
        return (currElements == 0);
    }

    int OneString::max_size() const
    {
        return MAX_SIZE;
    }

    int OneString::length() const
    {
        return currElements;
    }

    /*******************************************
    * Adding + Inserting
    ********************************************/

    void OneString::append(const OneString& ostr)
    {
        while (currElements + ostr.length() + 1 >= MAX_SIZE)
        {
            doubleSize();
        }

        int index = 0;
        while(!(ostr[index] == '\0'))
        {
            masterArray[index + currElements] = ostr[index];
            index++;
        }

        currElements += ostr.length();
        masterArray[currElements] = '\0';
    }

    void OneString::append(const OneChar& ochar)
    {
        if(currElements + 1 >= MAX_SIZE)
        {
            doubleSize();
        }

        masterArray[currElements] = ochar;
        currElements++;
        masterArray[currElements] = '\0';
    }

    void OneString::append(char ochar)
    {
        if(currElements + 1 >= MAX_SIZE)
        {
            doubleSize();
        }

        masterArray[currElements].addDirectly(ochar, 0);
        currElements++;
        masterArray[currElements] = '\0';
    }

    void OneString::append(const char* ostr)
    {
        int index = 0;
        while(ostr[index] != '\0')
        {
            if(currElements + 1 >= OneString::MAX_SIZE)
            {
                doubleSize();
            }

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
            currElements++;
        }

        masterArray[currElements] = '\0';
    }

    void OneString::append(const std::string& ostr)
    {
        int index = 0;
        while(ostr[index] != '\0')
        {
            //need to change size() getting error with it, error with signed/unsigned
            if(currElements + 1 >= OneString::MAX_SIZE)
            {
                OneString::doubleSize();
            }

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
            currElements++;
        }
        masterArray[currElements] = '\0';
    }

    void OneString::insert(int pos, const OneString& ostr)
    {
        int insertSize = ostr.length();

        if(pos < 0 || pos > currElements)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Index out of Bounds" << io_end;
            return;
        }

        while(pos >= MAX_SIZE || (currElements + insertSize + 1 > MAX_SIZE))
        {
            doubleSize();
        }

        if(pos != currElements)
        {
            for(int i = currElements - 1; i >= pos; --i)
            {
                masterArray[i + insertSize] = masterArray[i];
            }
        }

        for(int off = 0; off < insertSize; ++off)
        {
            //invalid conversion from OneChar* to char
            masterArray[pos + off] = ostr[off];
        }

        currElements += ostr.length();

        masterArray[currElements] = '\0';
    }

    void OneString::insert(int pos, std::string ostr)
    {
        int insertSize = 0;

        while(ostr[insertSize] != '\0')
        {
            insertSize++;
        }

        if(pos < 0 || pos > currElements)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Index out of Bounds" << io_end;
            return;
        }

        while(pos >= MAX_SIZE || (currElements + insertSize + 1 > MAX_SIZE))
        {
            doubleSize();
        }

        if(pos != currElements)
        {
            for(int i = currElements - 1; i >= pos; --i)
            {
                masterArray[i + insertSize] = masterArray[i];
            }
        }

        for(int off = 0; off < insertSize; ++off)
        {
            //invalid conversion from OneChar* to char
            masterArray[pos + off] = ostr[off];
        }

        currElements += insertSize;
        masterArray[currElements] = '\0';
    }

    // the offending insert function
    void OneString::insert(int pos, char* ostr)
    {
        /*OneString temp = ostr;
        //temp not declared
        insert(pos, temp);*/

        int charLength = 0;

        // get the size of the characters being added
        while (ostr[charLength] != '\0')
        {
            charLength++;
        }

        while (currElements + charLength + 1 >= MAX_SIZE)
        {
            doubleSize();
        }

        for (int i = currElements; i >= pos; i--)
        {
            masterArray[i + charLength] = masterArray[i];
        }

        for (int i = 0; i < charLength; i++)
        {
            masterArray[pos] = ostr[i];
            pos++;
        }

        currElements = currElements + charLength;
    }

    void OneString::insert(int pos, char ochar)
    {
        if(currElements + 1 == MAX_SIZE)
        {
            doubleSize();
        }

        for(int i = currElements - 1; i >= pos; --i)
        {
            masterArray[i + 1] = masterArray[i];
        }

        masterArray[pos] = ochar;

        currElements++;
        masterArray[currElements] = '\0';
    }

    void OneString::insert(int pos, OneChar* ochar)
    {
        if(currElements + 1 == MAX_SIZE)
        {
            doubleSize();
        }

        if(pos < 0 || pos > currElements)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Index out of Bounds" << io_end;
            return;
        }

        for(int i = currElements - 1; i >= pos; --i)
        {
            masterArray[i + 1] = masterArray[i];
        }

        masterArray[pos] = *ochar;

        currElements++;
        masterArray[currElements] = '\0';
    }

    void OneString::insert(int pos, OneChar& ochar)
    {
        if(currElements + 1 == MAX_SIZE)
        {
            doubleSize();
        }

        if(pos < 0 || pos > currElements)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Index out of Bounds" << io_end;
            return;
        }

        for(int i = currElements - 1; i >= pos; --i)
        {
            masterArray[i + 1] = masterArray[i];
        }

        masterArray[pos] = ochar;

        currElements++;
        masterArray[currElements] = '\0';
    }

    void OneString::push_back(char ochar)
    {
        append(ochar);
    }

    void OneString::push_back(const char* ostr)
    {
        append(ostr);
    }

    void OneString::push_back(const std::string ostr)
    {
        append(ostr);
    }

    void OneString::push_back(const OneChar& ochar)
    {
        append(ochar);
    }

    /*******************************************
    * Removing
    ********************************************/

    void OneString::clear()
    {
        delete [] masterArray;
        masterArray = nullptr;
        MAX_SIZE = BASE_SIZE;
        masterArray = new OneChar[MAX_SIZE];
        currElements = 0;
    }

    void OneString::pop_back()
    {
        if(currElements == 0)
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error: Can't POP an empty OneString" << io_end;
        }
        else
        {
            masterArray[currElements - 1] = '\0';
            currElements--;
        }
    }

    /*******************************************
    * Comparison
    ********************************************/

    bool OneString::equals(const OneString& ostr) const
    {
        if(currElements == ostr.length())
        {
            for(int i = 0; i < currElements; ++i)
            {
                if(!(ostr[i] == masterArray[i]))
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool OneString::equals(std::string ostr) const
    {
        return equals(ostr.c_str());
    }

    bool OneString::equals(const char* ostr) const
    {
        OneString compareStr(ostr);

        int thisSize = length();
        if(thisSize == compareStr.length())
        {
            for (int i = 0; i < thisSize; ++i)
            {
                if(!(OneString::masterArray[i] == compareStr[i]))
                    return false;
            }
            return true;
        }
        return false;
    }

    bool OneString::lessThanCharP(const char* ostr)
    {
        int mainIndex = 0;
        int smallIndex = 0;
        int charIndex = 0;
        int endIndex = length();

        while(mainIndex < endIndex)
        {
            if(OneString::masterArray[mainIndex][smallIndex] > ostr[charIndex])
                return true;
            else if(OneString::masterArray[mainIndex][smallIndex] < ostr[charIndex])
                return true;
            if(OneString::masterArray[mainIndex][smallIndex + 1] != '\0')
                ++smallIndex;
            else
            {
                ++mainIndex;
                smallIndex = 0;
            }

            ++charIndex;
        }

        if(ostr[charIndex] != '\0')
            return true;
        return false;
    }

    //OneString does not name a type
    bool OneString::lessThanStr(const OneString& ostr)
    {
        int small_len = (length() < ostr.length())? length(): ostr.length();
        for(int i = 0; i < small_len; ++i)
        {
            if(OneString::masterArray[i] < (ostr[i]))
            {
                return true;
            }
            else
            {
                //if(!(master[i] == (ostr[i])))
                if(!(ostr[i] == (masterArray[i])))
                {
                    return false;
                }
            }
        }

        if((small_len == length()) && (small_len != ostr.length()))
        {
            return true;
        }
        return false;
    }


    /*******************************************
    * Other
    ********************************************/

    void OneString::swap(OneString& str)
    {
        OneString temp(*this);
        *this = str;
        str = temp;
    }

    OneString OneString::substr(int beginningIndex, int length)
    {
        OneString substr;

        if (beginningIndex > 0 && beginningIndex + length < currElements)
        {
            for(int i = 0; i < length; i++)
            {
                substr.append(masterArray[beginningIndex]);
                beginningIndex++;
            }
            substr.append('\0');
        }
        else
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error : IDEX OUT OF BOUNDS" << io_end;
        }
        return substr;
    }

    /*******************************************
    * Operators
    ********************************************/

    OneChar& OneString::operator[](int pos) const
    {
        if((pos <= currElements) && (pos >= 0))
        {
            return masterArray[pos];
        }
        else
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error : IDEX OUT OF BOUNDS" << io_end;
            return masterArray[currElements - 1];
        }
    }

    OneString& OneString::operator=(std::string str)
    {
        clear();
        append(str);
        return *this;
    }

    OneString& OneString::operator=(const char* str)
    {
        clear();
        append(str);
        return *this;
    }

    OneString& OneString::operator=(const OneChar& str)
    {
        clear();
        append(str);
        return *this;
    }

    OneString& OneString::operator=(char ch)
    {
        clear();
        append(ch);
        return *this;
    }

    OneString& OneString::operator=(OneChar* ch)
    {
        clear();
        append(*ch);
        return *this;
    }

    OneString& OneString::operator=(OneString& ostr)
    {
        clear();
        append(ostr);
        return *this;
    }

    bool OneString::operator==(const OneString& ostr)
    {
        return equals(ostr);
    }

    bool OneString::operator==(const char* ostr)
    {
        return equals(ostr);
    }

    bool OneString::operator==(std::string ostr)
    {
        return equals(ostr);
    }

    bool OneString::operator<(const char* ostr2)
    {
        return lessThanCharP(ostr2);
    }

    bool OneString::operator<(std::string ostr2)
    {
        return lessThanCharP(ostr2.c_str());
    }

    bool OneString::operator<(const OneString& ostr2)
    {
        return lessThanStr(ostr2);
    }

    bool OneString::operator<=(const OneString& ostr2)
    {
        return (((*this) < ostr2) || ((*this) == ostr2));
    }

    bool OneString::operator<=(const char* ostr2)
    {
        return (((*this) < ostr2)|| ((*this) == ostr2));
    }

    bool OneString::operator<=(std::string ostr2)
    {
        return (((*this) < ostr2)|| ((*this) == ostr2));
    }

    bool OneString::operator>(const OneString& ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneString::operator>(const char* ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneString::operator>(std::string ostr2)
    {
        return(!((*this) <= ostr2));
    }

    bool OneString::operator>=(const OneString& ostr2)
    {
        return(!((*this) < ostr2));
    }

    bool OneString::operator>=(const char* ostr2)
    {
        return(!((*this) < ostr2));
    }

    bool OneString::operator>=(std::string ostr2)
    {
        return(!((*this) < ostr2));
    }

    void OneString::operator+=(const OneString& ostr2)
    {
        append(ostr2);
    }

    void OneString::operator+=(const char* ostr2)
    {
        append(ostr2);
    }

    void OneString::operator+=(std::string ostr2)
    {
        append(ostr2);
    }

    void OneString::operator+=(char ochar)
    {
        append(ochar);
    }

    void OneString::operator+=(const OneChar& ochar)
    {
        append(ochar);
    }
}