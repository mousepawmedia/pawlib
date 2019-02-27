#include "pawlib/onestring.hpp"

namespace pawlib
{
    /*******************************************
    * Constructors + Destructor
    *******************************************/
    OneString::OneString()
    :_capacity(BASE_SIZE), _elements(0)
    {
        masterArray = new OneChar[_capacity];
    }

    OneString::OneString(const char* str)
    :_capacity(BASE_SIZE), _elements(0)
    {
        masterArray = new OneChar[_capacity];
        append(str);
    }

    OneString::OneString(const std::string& str)
    :_capacity(BASE_SIZE), _elements(0)
    {
        masterArray = new OneChar[_capacity];
        append(str);
    }

    OneString::OneString(const OneString& str)
    :_capacity(BASE_SIZE), _elements(0)
    {
        masterArray = new OneChar[_capacity];
        append(str);
    }

    OneString::OneString(char ch)
    :_capacity(BASE_SIZE), _elements(0)
    {
        masterArray = new OneChar[_capacity];
        append(ch);
    }

    OneString::OneString(const OneChar& ch)
    :_capacity(BASE_SIZE), _elements(0)
    {
        masterArray = new OneChar[_capacity];
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

   //TODO: Rethink and rewrite.

    void OneString::parseChar(const char* str, size_t index, uint_fast8_t bytes)
    {
        (void)bytes;
        /*for(uint_fast8_t i = 0; i < bytes; ++i)
        {
            masterArray[this->_elements].addDirectly(str[index + i], i);
        }
        masterArray[this->_elements].addDirectly('\0', bytes);*/
        masterArray[this->_elements] = &(str[index]);
    }

    void OneString::parseChar(const std::string& str, size_t index, uint_fast8_t bytes)
    {
        (void)bytes;
        /*for(uint_fast8_t i = 0; i < bytes; ++i)
        {
            masterArray[this->_elements].addDirectly(str[index + i], i);
        }
       masterArray[this->_elements].addDirectly('\0', bytes);*/
       masterArray[this->_elements] = &(str[index]);
    }

    void OneString::parseChar(const char str, uint_fast8_t bytes)
    {
        (void)bytes;
        /*for(uint_fast8_t i = 0; i < bytes; ++i)
        {
            masterArray[this->_elements].addDirectly(str, i);
        }
       masterArray[this->_elements].addDirectly('\0', bytes);*/
       masterArray[this->_elements] = str;
    }

    void OneString::resize()
    {
        _capacity *= RESIZE_FACTOR;

        OneChar* tempArray = new OneChar[_capacity];

        // If an old array exists...
        if(this->masterArray != nullptr)
        {
            // TODO: Valgrind test thoroughly
            memmove(
                (void*) tempArray,
                (void*) this -> masterArray,
                sizeof(OneChar) * this->_elements
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

    OneChar OneString::at(size_t pos) const
    {
        if (pos > _elements)
        {
            throw std::out_of_range("OneString: Index out of bounds.");
        }

        return masterArray[pos];
    }

    bool OneString::empty() const
    {
        return (_elements == 0);
    }

    size_t OneString::capacity() const
    {
        return _capacity;
    }

    size_t OneString::length() const
    {
        return _elements;
    }

    const char* OneString::c_str() const
    {
        // TODO: Eliminate overallocation!
        size_t size = _elements * 4 + 1;
        char* r = new char[size];
        for(size_t i = 0; i < _elements; ++i)
        {
            strcat(r, masterArray[i].c_str());
        }
        r[size-1] = '\0';
        return r;
    }

    /*******************************************
    * Adding + Inserting
    ********************************************/

    void OneString::append(const OneString& ostr)
    {
        while (_elements + ostr.length() + 1 >= _capacity)
        {
            resize();
        }

        size_t index = 0;
        while(!(ostr[index] == '\0'))
        {
            masterArray[index + _elements] = ostr[index];
            index++;
        }

        _elements += ostr.length();
        masterArray[_elements] = '\0';
    }

    void OneString::append(const OneChar& ochar)
    {
        if(_elements + 1 >= _capacity)
        {
            resize();
        }

        masterArray[_elements] = ochar;
        _elements++;
        masterArray[_elements] = '\0';
    }

    void OneString::append(char ch)
    {
        // TODO: Switch this to a checkSize() function?
        if(_elements + 1 >= _capacity)
        {
            resize();
        }

        /* NOTE: Removed the Unicode parsing from function, as it would
         * not behave as expected by the end-user. Watch for edge cases!
         */

        // Insert a 1-byte ASCII char
        parseChar(ch, 1);

        ++_elements;
        masterArray[_elements] = '\0';
    }

    void OneString::append(const char* str)
    {
        size_t index = 0;

        // Loop through each character in the string literal
        while(str[index] != '\0')
        {
            // TODO: Switch this to a checkSize() function?
            if(_elements + 1 >= _capacity)
            {
                resize();
            }

            /* If a byte in Unicode starts with 11, it is the first byte in a
             * multi-byte character. The number of 1s at the beginning indicates
             * the number of bytes in the character.
             */
            switch(str[index] & 0xF0)
            {
                // Four-byte Unicode character (started with 11110...)
                case 0xF0:
                {
                    // Insert the next four bytes as a single OneChar.
                    parseChar(str, index, 4);
                    index += 4;
                    break;
                }
                // Three-byte Unicode character (started with 1110...)
                case 0xE0:
                {
                    // Insert the next three bytes as a single OneChar.
                    parseChar(str, index, 3);
                    index += 3;
                    break;
                }
                // Two-byte Unicode character (started with 1100...)
                case 0xC0:
                {
                    // Insert the next two bytes as a single OneChar.
                    parseChar(str, index, 2);
                    index += 2;
                    break;
                }
                /* Continuation character (started with 10...), so we're in the
                 * middle of a multi-byte Unicode character.
                 */
                case 0x80:
                {
                    /* We'll let the error pass silently. This is basically a
                     * "can't happen" scenario.
                     */
                    break;
                }
                // Single-byte character (started with 0...)
                default:
                {
                    // Insert this byte as a single OneChar.
                    parseChar(str, index, 1);
                    ++index;
                }
            }

            ++_elements;
        }
        // Insert the null terminator at the end of the string.
        masterArray[_elements] = '\0';
    }

    void OneString::append(const std::string& str)
    {
        // Parse the internal c string directly.
        append(str.c_str());
    }

    void OneString::insert(size_t pos, const OneString& ostr)
    {
        // TODO: Possible inefficiency. Potentially refactor.
        OneString left;
        OneString right;

        for(size_t i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ostr);
        this -> append(right);
    }

    void OneString::insert(size_t pos, std::string ostr)
    {
        OneString left;
        OneString right;

        for(size_t i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ostr);
        this -> append(right);
    }

    // the offending insert function
    void OneString::insert(size_t pos, char* ostr)
    {
        OneString left;
        OneString right;

        for(size_t i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ostr);
        this -> append(right);
    }

    void OneString::insert(size_t pos, char ochar)
    {
        OneString left;
        OneString right;

        for(size_t i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> masterArray[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ochar);
        this -> append(right);
    }

    void OneString::insert(size_t pos, OneChar& ochar)
    {
        OneString left;
        OneString right;

        for(size_t i = 0; i < pos; i++)
        {
            left.append(this -> masterArray[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
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
        _capacity = BASE_SIZE;
        masterArray = new OneChar[_capacity];
        _elements = 0;
    }

    void OneString::pop_back()
    {
        if(_elements == 0)
        {
            //ioc << cat_error << ta_bold << fg_red <<
            //"OneString Error: Can't POP an empty OneString" << io_end;
            // TODO: Exception instead
        }
        else
        {
            masterArray[_elements - 1] = '\0';
            _elements--;
        }
    }

    /*******************************************
    * Comparison
    ********************************************/

    bool OneString::equals(const OneString& ostr) const
    {
        if(_elements == ostr.length())
        {
            for(size_t i = 0; i < _elements; ++i)
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

        if(this->_elements == compareStr.length())
        {
            for (size_t i = 0; i < this->_elements; ++i)
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
        size_t mainIndex = 0;
        size_t smallIndex = 0;
        size_t charIndex = 0;
        size_t endIndex = length();

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
        size_t small_len = (this->_elements < ostr.length())? this->_elements: ostr.length();
        for(size_t i = 0; i < small_len; ++i)
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

        if((small_len == this->_elements) && (small_len != ostr.length()))
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

    OneString OneString::substr(size_t beginningIndex, size_t length)
    {
        OneString substr;

        if (beginningIndex > 0 && beginningIndex + length < _elements)
        {
            for(size_t i = 0; i < length; i++)
            {
                // We're implicitly including the \0 because of the +1
                substr.append(masterArray[beginningIndex + i]);
            }
        }
        else
        {
            throw std::out_of_range("OneString: Index out of bounds.");
        }
        return substr;
    }

    /*******************************************
    * Operators
    ********************************************/

    OneChar& OneString::operator[](size_t pos) const
    {
        if((pos <= _elements) && (pos >= 0))
        {
            return masterArray[pos];
        }
        else
        {
            throw std::out_of_range("OneString: Index out of bounds.");
        }
    }

    OneString& OneString::operator=(const std::string& str)
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

    bool OneString::operator==(const std::string& ostr)
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

    bool OneString::operator!=(const std::string& ostr)
    {
        return !(equals(ostr));
    }

    bool OneString::operator<(const char* ostr2)
    {
        return lessThanCharP(ostr2);
    }

    bool OneString::operator<(const std::string& ostr2)
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

    bool OneString::operator<=(const std::string& ostr2)
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

    bool OneString::operator>(const std::string& ostr2)
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

    bool OneString::operator>=(const std::string& ostr2)
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

    void OneString::operator+=(const std::string& ostr2)
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
