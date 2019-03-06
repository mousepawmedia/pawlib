#include "pawlib/onechar.hpp"

namespace pawlib
{
    OneChar::OneChar()
    : size(1)
    {
        internal[0] = '\0';
    }

    /** Default constructor*/
    OneChar::OneChar(const char* cstr)
    : size(1)
    {
        parse(cstr);
    }

    OneChar::OneChar(const char ch)
    : size(1)
    {
        parse(ch);
    }

    OneChar::OneChar(const OneChar& cpy)
    : size(1)
    {
        copy(cpy);
    }

    void OneChar::copy(const OneChar& cpy)
    {
        this->size = cpy.size;
        memcpy(this->internal, cpy.internal, cpy.size);
    }


    void OneChar::parse(const char ch)
    {
        this->size = 1;
        this->internal[0] = ch;
    }

    void OneChar::parse(const char* cstr)
    {
        this->size = evaluateLength(cstr);
        memcpy(this->internal, cstr, sizeof(char) * this->size);
    }

    void OneChar::parse(const std::string& str)
    {
        const char* cstr = str.c_str();
        this->size = evaluateLength(cstr);
        memcpy(this->internal, cstr, sizeof(char) * this->size);
    }

    size_t OneChar::parseFromString(const char* cstr, size_t index)
    {
        this->size = evaluateLength(cstr + index);
        memcpy(this->internal, cstr + index, sizeof(char) * this->size);
        return this->size;
    }

    size_t OneChar::parseFromString(const std::string str, size_t index)
    {
        return parseFromString(str.c_str(), index);
    }

    OneChar& OneChar::operator=(char ch)
    {
        parse(ch);
        return *this;
    }

    OneChar& OneChar::operator=(const char* cstr)
    {
        parse(cstr);
        return *this;
    }

    OneChar& OneChar::operator=(const std::string& str)
    {
        parse(str);
        return *this;
    }

    OneChar& OneChar::operator=(const OneChar& cpy)
    {
        copy(cpy);
        return *this;
    }

    bool OneChar::equals(const char cmp) const
    {
        return ((this->size == 1) && (this->internal[0] == cmp));
    }

    bool OneChar::equals(const char* cmp) const
    {
        uint_least8_t cmpSize = evaluateLength(cmp);
        // If the string doesn't null-terminate after one character, mismatch.
        if (cmp[cmpSize] != '\0') {return false;}
        // Ensure the character size matches
        if (cmpSize != this->size) {return false;}
        return (memcmp(this->internal, cmp, cmpSize) == 0);
    }

    bool OneChar::equals(const std::string& cmp) const
    {
        return equals(cmp.c_str());
    }

    bool OneChar::equals(const OneChar& cmp) const
    {
        if (this->size != cmp.size)
        {
            return false;
        }
        // Perform a raw memory comparison
        return (memcmp(this->internal, cmp.internal, this->size) == 0);
    }

    // TODO: Relocate all of the following operator (aliases) to onechar.hpp
    bool OneChar::operator==(const char cmp) const
    {
        return equals(cmp);
    }

    bool OneChar::operator==(const char* cmp) const
    {
        return equals(cmp);
    }

    bool OneChar::operator==(const std::string& cmp) const
    {
        return equals(cmp);
    }

    bool OneChar::operator==(const OneChar& cmp) const
    {
        return equals(cmp);
    }

    bool OneChar::operator!=(const char cmp) const
    {
        return !equals(cmp);
    }

    bool OneChar::operator!=(const char* cmp) const
    {
        return !equals(cmp);
    }

    bool OneChar::operator!=(const std::string& cmp) const
    {
        return !equals(cmp);
    }

    bool OneChar::operator!=(const OneChar& cmp) const
    {
        return !equals(cmp);
    }

    char OneChar::operator[](int pos) const
    {
        // TODO: Do we need this?
        return this->internal[pos];
    }

    void OneChar::print(std:: ostream& os) const
    {
        for (int index = 0; index < 5 || this->internal[index] == '\0'; ++index)
        {
            os << this->internal[index];
        }
    }

    const char* OneChar::c_str() const
    {
        // TODO: Will this cause memory leaks?
        char* r = new char[size+1];
        for (size_t i = 0; i < size; ++i)
        {
            r[i] = internal[i];
        }
        // memcpy(r, this->internal, sizeof(char)*this->size);
        r[size] = '\0';
        return r;
    }

    // TODO: Add c_str(char*)

    uint8_t OneChar::compare(const char cmp) const
    {
        // TODO: See notes in OneString::compare(const OneChar&)
        uint8_t sizeDiff = this->size - 1;
        if (sizeDiff == 0)
        {
            return memcmp(this->internal, &cmp, 1);
        }
        else
        {
            return sizeDiff;
        }
    }

    uint8_t OneChar::compare(const char* cmp) const
    {
        // TODO: See notes in OneString::compare(const OneChar&)
        uint8_t sizeDiff = this->size - evaluateLength(cmp);
        if (sizeDiff == 0)
        {
            return memcmp(this->internal, &cmp, this->size);
        }
        else
        {
            return sizeDiff;
        }
    }

    uint8_t OneChar::compare(const OneChar& cmp) const
    {
        uint8_t sizeDiff = this->size - cmp.size;
        if (sizeDiff == 0)
        {
            // TODO: Should we use strcmp instead?
            return memcmp(this->internal, cmp.internal, this->size);
        }
        else
        {
            // TODO: I'd rather we return which character is different.
            return sizeDiff;
        }
    }
}
