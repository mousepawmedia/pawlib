#include "pawlib/onestring.hpp"

namespace pawlib
{
    /*******************************************
    * Constructors + Destructor
    *******************************************/
    OneString::OneString()
    :_capacity(BASE_SIZE), _elements(0), internal(nullptr)
    {
        this->internal = new OneChar[this->_capacity];
        assign('\0');
    }

    OneString::OneString(char ch)
    :_capacity(BASE_SIZE), _elements(0), internal(nullptr)
    {
        this->internal = new OneChar[this->_capacity];
        assign(ch);
    }

    OneString::OneString(const char* cstr)
    :_capacity(BASE_SIZE), _elements(0), internal(nullptr)
    {
        this->internal = new OneChar[this->_capacity];
        assign(cstr);
    }

    OneString::OneString(const std::string& str)
    :_capacity(BASE_SIZE), _elements(0), internal(nullptr)
    {
        this->internal = new OneChar[this->_capacity];
        append(str);
    }

    OneString::OneString(const OneChar& ochr)
    :_capacity(BASE_SIZE), _elements(0), internal(nullptr)
    {
        this->internal = new OneChar[this->_capacity];
        assign(ochr);
    }

    OneString::OneString(const OneString& ostr)
    :_capacity(BASE_SIZE), _elements(0), internal(nullptr)
    {
        this->internal = new OneChar[this->_capacity];
        assign(ostr);
    }

    OneString::~OneString()
    {
        if (internal != nullptr)
        {
            delete[] internal;
        }
    }

    /*******************************************
    * Access
    *******************************************/

    OneChar& OneString::at(size_t pos) const
    {
        if (pos > _elements)
        {
            throw std::out_of_range("OneString: Index out of bounds.");
        }

        return internal[pos];
    }

    size_t OneString::capacity() const
    {
        return _capacity;
    }

    const char* OneString::c_str() const
    {
        size_t n = size();
        char* r = new char[n];
        char* dest = r;
        for(size_t i = 0; i < _elements; ++i)
        {
            memcpy(dest, internal[i].internal, internal[i].size);
            dest += internal[i].size;
        }
        r[n-1] = '\0';
        return r;
    }

    bool OneString::empty() const
    {
        return (_elements == 0);
    }

    size_t OneString::length() const
    {
        return _elements;
    }

    size_t OneString::size() const
    {
        size_t bytes = 0;
        // Sum all of the byte lengths of the OneChars.
        for(size_t i = 0; i < _elements; ++i)
        {
            bytes += this->internal[i].size;
        }
        // Add one extra byte for the null terminator
        return bytes+1;
    }

    /*******************************************
    * Comparison
    ********************************************/

    bool OneString::equals(const char ch) const
    {
        return (this->_elements == 1 && this->internal[0] == ch);
    }

    bool OneString::equals(const char* cstr) const
    {
        size_t index = 0;
        size_t compare_to = 0;
        while(cstr[index] != '\0')
        {
            if (!this->internal[compare_to].equals(cstr + index)) { return false; }
            index += OneChar::evaluateLength(cstr + index);
            if(compare_to++ > this->_elements) { return false; }
        }

        return true;
    }

    bool OneString::equals(const std::string& str) const
    {
        return equals(str.c_str());
    }

    bool OneString::equals(const OneChar& ochr) const
    {
        return (this->_elements == 1 && this->internal[0] == ochr);
    }

    bool OneString::equals(const OneString& ostr) const
    {
        if (this->_elements != ostr._elements) { return false; }

        for (size_t index = 0; index < this->_elements; ++index)
        {
            if (this->internal[index] != ostr.internal[index]) { return false; }
        }
        return true;
    }

    /*******************************************
    * Adding + Inserting
    ********************************************/

    void OneString::assign(const char ch)
    {
        clear();
        reserve(1);
        this->internal[_elements++] = ch;
    }

    void OneString::assign(const char* cstr)
    {
        clear();

        size_t len = characterCount(cstr);
        reserve(len);

        // Loop through each character in the string literal
        size_t index = 0;
        while(cstr[index] != '\0')
        {
            // Parse and store the character.
            index += internal[_elements++].parseFromString(cstr, index);
        }
    }

    void OneString::assign(const std::string& str)
    {
        assign(str.c_str());
    }

    void OneString::assign(const OneChar& ochr)
    {
        clear();
        reserve(1);
        this->internal[_elements++] = ochr;
    }

    void OneString::assign(const OneString& ostr)
    {
        clear();
        reserve(ostr._elements);
        memcpy(ostr.internal, this->internal, sizeof(OneChar) * ostr._elements);
        _elements = ostr._elements;
    }

    void OneString::append(const char ch)
    {
        expand(1);

        // Insert a 1-byte ASCII char
        internal[_elements++] = ch;
    }

    void OneString::append(const char* cstr)
    {
        size_t index = 0;
        size_t len = characterCount(cstr);
        expand(len);

        // Loop through each character in the string literal
        while(cstr[index] != '\0')
        {
            index += internal[_elements++].parseFromString(cstr, index);
        }
    }

    void OneString::append(const std::string& str)
    {
        // Parse the internal c string directly.
        append(str.c_str());
    }

    void OneString::append(const OneChar& ochar)
    {
        expand(1);
        internal[_elements++] = ochar;
    }

    void OneString::append(const OneString& ostr)
    {
        expand(ostr.length());

        size_t index = 0;
        while(!(ostr[index] == '\0'))
        {
            internal[index + _elements] = ostr[index];
            ++index;
        }

        _elements += ostr.length();
    }

    /*******************************************
    * Removing
    ********************************************/

    void OneString::clear()
    {
        if (_elements > 0)
        {
            delete[] this->internal;
            internal = nullptr;
            _capacity = 0;
            reserve(BASE_SIZE);
            _elements = 0;
        }
    }

    ///////////////////// REVIEW //////////////////////

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
