#include "pawlib/onestring.hpp"

namespace pawlib
{
    /*******************************************
    * Constructors + Destructor
    *******************************************/
    OneString::OneString()
    {
        capacity = BASE_SIZE;
        currElements = 0;
        masterArray = new OneChar[capacity];
    }

    OneString::OneString(const char* str)
    {
        capacity = BASE_SIZE;
        masterArray = new OneChar[capacity];
        append(str);
    }

    OneString::OneString(const std::string& str)
    {
        capacity = BASE_SIZE;
        masterArray = new OneChar[capacity];
        append(str);
    }

    OneString::OneString(const OneString& str)
    {
        capacity = BASE_SIZE;
        masterArray = new OneChar[capacity];
        append(str);
    }

    OneString::OneString(char ch)
    {
        capacity = BASE_SIZE;
        masterArray = new OneChar[capacity];
        append(ch);
    }

    OneString::OneString(const OneChar& ch)
    {
        capacity = BASE_SIZE;
        masterArray = new OneChar[capacity];
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
        //currElements = 0;
        int index = 0;

        while(str[index] != '\0')
        {
            if(currElements+ 1 >= capacity)
            {
                resize();
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
                // TODO: Is there a better way to handle this than with an error?
                ioc << cat_error << ta_bold << fg_red << "OneString Error: "
                    << " Invalid Character in String at Position: " << index
                    << io_end;
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

    OneString& OneString::assignHelper(char str)
    {
        if(currElements + 1 >= capacity)
        {
            resize();
        }

        if((str & 0xF0) == 0xF0)
        {
            // Insert a 4 byte Unicode Char into the OneString
            parseChar(str, 4);
        }
        // Does it start with an E?
        else if((str & 0xF0) == 0xE0)
        {
            // Insert a 3 byte Unicode Char into the OneString
            parseChar(str, 3);
        }
        // Does it start with a C?
        else if((str & 0xF0) == 0xC0)
        {
            // Insert a 2 byte Unicode Char into the OneString
            parseChar(str, 2);
        }
        // Check if the char is valid
        else if((str & 0xF0) == 0x80)
        {
            /* This indicates a continuation bit, which we would only get if we
             * have an INCOMPLETE Unicode character. Presently, it doesn't look
             * like we need to do anything in this scenario, including throwing
             * an error. Just move on quietly.
             */
        }
        else
        {
            // Insert a 1-byte ASCII char
            parseChar(str, 1);
        }

        currElements++;
        masterArray[currElements] = '\0';

        return *this;
    }

    OneString& OneString::assignHelper(std::string ostr)
    {
        int index = 0;
        while(ostr[index] != '\0')
        {
            if(currElements + 1 >= OneString::capacity)
            {
                OneString::resize();
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
                        return *this;
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

        return *this;
    }

    void OneString::parseChar(const char* str, int index, int bytes)
    {
        int theLength = length();

        for(int i = 0; i < bytes; ++i)
        {
            masterArray[theLength].addDirectly(str[index + i], i);
        }
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

    void OneString::parseChar(const char str, int bytes)
    {
        int theLength = length();

        for(int i = 0; i < bytes; ++i)
        {
            //master[length][i] = str[index + i];
            masterArray[theLength].addDirectly(str, i);
        }
       // master[length][bytes] = '\0';
       masterArray[theLength].addDirectly('\0', bytes);
    }

    void OneString::resize()
    {
        capacity *= RESIZE_FACTOR;

        OneChar* tempArray = new OneChar[capacity];

        // If an old array exists...
        if(this->masterArray != nullptr)
        {
            // TODO: Valgrind test thoroughly
            memmove(
                (void*) tempArray,
                (void*) this -> masterArray,
                sizeof(OneChar) * this->currElements
            );

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

    int OneString::getCapacity() const
    {
        return capacity;
    }

    int OneString::length() const
    {
        return currElements;
    }

    /*******************************************
    * Adding + Inserting
    ********************************************/

    // if characters have already been parsed,
    // we can move them as normal...
    void OneString::append(const OneString& ostr)
    {
        while (currElements + ostr.length() + 1 >= capacity)
        {
            resize();
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
        if(currElements + 1 >= capacity)
        {
            resize();
        }

        masterArray[currElements] = ochar;
        currElements++;
        masterArray[currElements] = '\0';
    }

    // ...otherwise, we have to check them
    // for their size (which assignHelper does)
    void OneString::append(char ochar)
    {
        assignHelper(ochar);
    }

    void OneString::append(const char* ostr)
    {
        assignHelper(ostr);
    }

    void OneString::append(const std::string& ostr)
    {
        // TODO: Benchmark the assignHelper() function; possibly change to macro?
        assignHelper(ostr);
    }

    void OneString::insert(int pos, const OneString& ostr)
    {
        // TODO: Possible inefficiency. Potentially refactor.
        OneString left;
        OneString right;

        for(int i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(int i = pos; i < this -> currElements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ostr);
        this -> append(right);
    }

    void OneString::insert(int pos, std::string ostr)
    {
        OneString left;
        OneString right;

        for(int i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(int i = pos; i < this -> currElements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ostr);
        this -> append(right);
    }

    // the offending insert function
    void OneString::insert(int pos, char* ostr)
    {
        OneString left;
        OneString right;

        for(int i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(int i = pos; i < this -> currElements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ostr);
        this -> append(right);
    }

    void OneString::insert(int pos, char ochar)
    {
        OneString left;
        OneString right;

        for(int i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(int i = pos; i < this -> currElements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ochar);
        this -> append(right);
    }

    /*void OneString::insert(int pos, OneChar* ochar)
    {
        OneString left;
        OneString right;

        for(int i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(int i = pos; i < this -> currElements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ochar);
        this -> append(right);
    }*/

    void OneString::insert(int pos, OneChar& ochar)
    {
        OneString left;
        OneString right;

        for(int i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(int i = pos; i < this -> currElements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ochar);
        this -> append(right);
    }

    void OneString::push_back(char ochar)
    {
        append(ochar);
    }

    void OneString::push_back(const char* ostr)
    {
        append(ostr);
    }

    void OneString::push_back(const std::string& ostr)
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
        capacity = BASE_SIZE;
        masterArray = new OneChar[capacity];
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
                // We're implicitly including the \0 because of the +1
                substr.append(masterArray[beginningIndex + i]);
            }
        }
        else
        {
            ioc << cat_error << ta_bold << fg_red <<
            "OneString Error : INDEX OUT OF BOUNDS" << io_end;
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
            "OneString Error : INDEX OUT OF BOUNDS" << io_end;
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

    bool OneString::operator!=(const OneString& ostr)
    {
        return !(equals(ostr));
    }

    bool OneString::operator!=(const char* ostr)
    {
        return !(equals(ostr));
    }

    bool OneString::operator!=(std::string ostr)
    {
        return !(equals(ostr));
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
