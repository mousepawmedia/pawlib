#include "pawlib/onestring.hpp"

namespace pawlib
{
    /*******************************************
    * Constructors + Destructor
    *******************************************/
    OneString::OneString()
    :_capacity(BASE_SIZE), _elements(0)
    {
        this->internal = new OneChar[_capacity];
    }

    OneString::OneString(const char* str)
    :_capacity(BASE_SIZE), _elements(0)
    {
        this->internal = new OneChar[_capacity];
        append(str);
    }

    OneString::OneString(const std::string& str)
    :_capacity(BASE_SIZE), _elements(0)
    {
        this->internal = new OneChar[_capacity];
        append(str);
    }

    OneString::OneString(const OneString& str)
    :_capacity(BASE_SIZE), _elements(0)
    {
        this->internal = new OneChar[_capacity];
        append(str);
    }

    OneString::OneString(char ch)
    :_capacity(BASE_SIZE), _elements(0)
    {
        this->internal = new OneChar[_capacity];
        append(ch);
    }

    OneString::OneString(const OneChar& ch)
    :_capacity(BASE_SIZE), _elements(0)
    {
        this->internal = new OneChar[_capacity];
        append(ch);
    }

    OneString::~OneString()
    {
        if (internal != nullptr)
        {
            delete [] internal;
        }
    }

    void OneString::resize()
    {
        _capacity *= RESIZE_FACTOR;

        OneChar* tempArray = new OneChar[_capacity];

        // If an old array exists...
        if(this->internal != nullptr)
        {
            // TODO: Valgrind test thoroughly
            memmove(
                (void*) tempArray,
                (void*) this -> internal,
                sizeof(OneChar) * this->_elements
            );

            // Delete the old structure.
            delete[] internal;
            this->internal = nullptr;
        }

        // Store the new structure.
        this->internal = tempArray;
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

        return internal[pos];
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
        size_t size = _elements * 5 + 1;
        char* r = new char[size];
        for(size_t i = 0; i < _elements; ++i)
        {
            strcat(r, internal[i].c_str());
        }
        r[size-1] = '\0';
        return r;
    }

    /*******************************************
    * Adding + Inserting
    ********************************************/

    void OneString::append(const OneString& ostr)
    {
        checkResize(ostr.length() + 1);

        size_t index = 0;
        while(!(ostr[index] == '\0'))
        {
            internal[index + _elements] = ostr[index];
            index++;
        }

        _elements += ostr.length();
        internal[_elements] = '\0';
    }

    void OneString::append(const OneChar& ochar)
    {
        checkResize(1);

        internal[_elements] = ochar;
        _elements++;
        internal[_elements] = '\0';
    }

    void OneString::append(char ch)
    {
        checkResize(1);

        // Insert a 1-byte ASCII char
        internal[_elements].parse(ch);

        ++_elements;
        // TODO: Ensure this is the default value of a OneChar()!
        internal[_elements] = '\0';
    }

    void OneString::append(const char* str)
    {
        size_t index = 0;

        // Loop through each character in the string literal
        while(str[index] != '\0')
        {
            checkResize(1);

            index += internal[_elements].parseFromString(str, index);
            ++_elements;
        }
        // Insert the null terminator at the end of the string.
        internal[_elements] = '\0';
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
            left.append(this -> internal[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> internal[i]);
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
            left.append(this -> internal[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> internal[i]);
        }

        this -> clear();

        this -> append(left);
        this -> append(ostr);
        this -> append(right);
    }

    void OneString::insert(size_t pos, char* ostr)
    {
        OneString left;
        OneString right;

        for(size_t i = 0; i < pos; i++)
        {
            left.append(this -> internal[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> internal[i]);
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
            left.append(this -> internal[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> internal[i]);
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
            left.append(this -> internal[i]);
        }

        for(size_t i = pos; i < this -> _elements; i++)
        {
            right.append(this -> internal[i]);
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
        delete [] internal;
        internal = nullptr;
        _capacity = BASE_SIZE;
        internal = new OneChar[_capacity];
        _elements = 0;
    }

    void OneString::pop_back()
    {
        if(_elements == 0)
        {
            throw std::out_of_range("OneString: Cannot pop from an empty string.");
        }
        else
        {
            internal[_elements - 1] = '\0';
            --_elements;
        }
    }

    /*******************************************
    * Comparison
    ********************************************/

    bool OneString::equals(const OneString& ostr) const
    {
        if(_elements == ostr._elements)
        {
            for(size_t i = 0; i < _elements; ++i)
            {
                if(!(ostr[i] == internal[i]))
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
                if(!(OneString::internal[i] == compareStr[i]))
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
            if(OneString::internal[mainIndex][smallIndex] > ostr[charIndex])
                return true;
            else if(OneString::internal[mainIndex][smallIndex] < ostr[charIndex])
                return true;
            if(OneString::internal[mainIndex][smallIndex + 1] != '\0')
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
            if(OneString::internal[i] < (ostr[i]))
            {
                return true;
            }
            else
            {
                //if(!(master[i] == (ostr[i])))
                if(!(ostr[i] == (internal[i])))
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
                substr.append(internal[beginningIndex + i]);
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
            return internal[pos];
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
