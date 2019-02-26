#include "pawlib/onechar.hpp"

namespace pawlib
{
    OneChar::OneChar()
    : size(0)
    {}

    /** Default constructor*/
    OneChar::OneChar(const char* cstr)
    : size(0)
    {
        /*int index = 0;
        // Add each non-terminating character to the char array.
        while (newChar[index] != '\0')
        {
            this->internal[index] = newChar[index];
            ++index;
        }

        // Add a null terminator to the end of the char array
        this->internal[index] = '\0';*/

        // Same as OneChar::parse(const char*);
        this->size = evaluateLength(cstr);
        memcpy(this->internal, cstr, sizeof(char) * this->size);
    }

    OneChar::OneChar(const char ch)
    :size(1)
    {
        // Same as OneChar::parse(char)
        memcpy(this->internal, &ch, sizeof(char));
    }

    OneChar::OneChar(const OneChar& cpy)
    : size(cpy.size)
    {
        // Same as OneChar::copy(OneChar&)
        memcpy(this->internal, cpy.internal, this->size);
    }

    void OneChar::parse(const char ch)
    {
        this->size = 1;
        // TODO: Is this actually faster or more reliable than raw assignment?
        memcpy(this->internal, &ch, sizeof(char));
    }

    void OneChar::parse(const char* cstr)
    {
        this->size = evaluateLength(cstr);
        memcpy(this->internal, cstr, sizeof(char) * this->size);
    }

    void OneChar::copy(const OneChar& cpy)
    {
        memcpy(this->internal, cpy.internal, cpy.size);
    }

    OneChar& OneChar::operator=(char ch)
    {
        /*this->internal[0] = newChar;
        this->internal[1] = '\0';
        */
        parse(ch);
        return *this;
    }

    OneChar& OneChar::operator=(const char* cstr)
    {
        /*int index = 0;

        // Add each non-terminating character to the char array.
        while (newChar[index] != '\0')
        {
            this->internal[index] = newChar[index];
            index++;
        }

        // Add a null terminator to the end of the char array
        this->internal[index] = '\0';*/

        parse(cstr);
        return *this;
    }

    OneChar& OneChar::operator=(const OneChar& cpy)
    {
        /*int index = 0;

        // Add each non-terminating character to the char array.
        while (newChar[index] != '\0')
        {
            this->internal[index] = newChar[index];
            index++;
        }

        // Add a null terminator to the end of the char array
        this->internal[index] = '\0';*/

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
        //return ((newChar == this->internal[0]) && (this->internal[1] == '\0'));
        return equals(cmp);
    }

    bool OneChar::operator==(const char* cmp) const
    {
        return equals(cmp);
    }

    bool OneChar::operator==(const OneChar& cmp) const
    {
        /*for (int index = 0; index != '\0'; index++)
        {
            if (this->internal[index] != newChar[index])
            {
                return false;
            }
        }
        return true;*/
        return equals(cmp);
    }

    bool OneChar::operator!=(const char cmp) const
    {
        //return !((newChar == this->internal[0]) && (this->internal[1] == '\0'));
        return !equals(cmp);
    }

    bool OneChar::operator!=(const char* cmp) const
    {
        //return !((newChar == this->internal[0]) && (this->internal[1] == '\0'));
        return !equals(cmp);
    }

    bool OneChar::operator!=(const OneChar& cmp) const
    {
        /*for (int index = 0; index != '\0'; index++)
        {
            if (this->internal[index] != newChar[index])
            {
                return true;
            }
        }

        return false;*/
        return !equals(cmp);
    }

    char OneChar::operator[](int pos) const
    {
        // TODO: Why do we need this?
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
        char* r = new char[this->size+1];
        strcat(r, this->internal);
        strcat(r, "\0");
        return r;
    }

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

    /*void OneChar::addDirectly(char newChar, int pos)
    {
        if (pos < 4)
        {
            this->internal[pos] = newChar;
            this->internal[pos + 1] = '\0';
        }
    }*/
}
