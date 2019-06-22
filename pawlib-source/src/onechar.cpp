#include "pawlib/onechar.hpp"

namespace pawlib
{
    onechar::onechar()
    : size(1), internal{'\0', '\0', '\0', '\0', '\0'}
    {
        // The default value of a onechar should be a null terminator
    }

    onechar::onechar(const char* cstr)
    : size(1), internal{'\0', '\0', '\0', '\0', '\0'}
    {
        // Extract the first ASCII or Unicode character from the c-string
        parse(cstr);
    }

    onechar::onechar(const std::string& str)
    : size(1), internal{'\0', '\0', '\0', '\0', '\0'}
    {
        // Extract the first ASCII or Unicode character from the std::string
        parse(str);
    }

    onechar::onechar(const char ch)
    : size(1), internal{'\0', '\0', '\0', '\0', '\0'}
    {
        // Store the ASCII character
        parse(ch);
    }

    onechar::onechar(const onechar& cpy)
    : size(cpy.size), internal{'\0', '\0', '\0', '\0', '\0'}
    {
        // Directly copy the contents of the internal array
        memcpy(this->internal, cpy.internal, cpy.size);
    }

    onechar::onechar(onechar&& mov)
    : size(mov.size)
    {
        // Directly copy the contents of the internal array
        // TODO: Is there a way just to steal the pointer?
        memcpy(this->internal, mov.internal, mov.size);
    }

    onechar& onechar::operator=(const onechar& cpy)
    {
        if (this != &cpy)
        {
            this->size = cpy.size;
            memcpy(this->internal, cpy.internal, cpy.size);
        }
        return *this;
    }

    onechar& onechar::operator=(onechar&& mov)
    {
        if (this != &mov)
        {
            this->size = mov.size;
            memcpy(this->internal, mov.internal, mov.size);

        }
        return *this;
    }

    void onechar::parse(const char ch)
    {
        // char is always ASCII (one byte)
        this->size = 1;
        // Store the character
        this->internal[0] = ch;
    }

    void onechar::parse(const char* cstr)
    {
        /* Determine the bytesize of the Unicode character
         * at the start of the c-string */
        this->size = evaluateLength(cstr);
        // Store the character via direct copy to internal array
        memcpy(this->internal, cstr, sizeof(char) * this->size);
    }

    void onechar::parse(const std::string& str)
    {
        // Extract the c-string from the std::string and parse it
        parse(str.c_str());
    }

    size_t onechar::parseFromString(const char* cstr, size_t index)
    {
        /* Determine the bytesize of the Unicode character
         * at the target location in the c-string */
        this->size = evaluateLength(cstr + index);
        // Store the character via direct copy to internal array
        memcpy(this->internal, cstr + index, sizeof(char) * this->size);
        // Return the number of characters we parsed in the c-string
        return this->size;
    }

    size_t onechar::parseFromString(const std::string& str, size_t index)
    {
        // Extract the c-string from the std::string and parse it
        return parseFromString(str.c_str(), index);
    }

    const char* onechar::c_str() const
    {
        return this->internal;
    }

    bool onechar::equals(const char cmp) const
    {
        return ((this->size == 1) && (this->internal[0] == cmp));
    }

    bool onechar::equals(const char* cmp) const
    {
        size_t cmpSize = evaluateLength(cmp);
        // If the string doesn't null-terminate after one character, mismatch.
        if (cmp[cmpSize] != '\0') {return false;}
        // Ensure the character size matches
        if (cmpSize != this->size) {return false;}
        return (memcmp(this->internal, cmp, cmpSize) == 0);
    }

    bool onechar::equals_at(const char* cmp) const
    {
        size_t cmpSize = evaluateLength(cmp);
        // Ensure the character size matches
        if (cmpSize != this->size) {return false;}
        return (memcmp(this->internal, cmp, cmpSize) == 0);
    }

    bool onechar::equals(const std::string& cmp) const
    {
        // Extract the c-string from the std::string and compare it directly
        return equals(cmp.c_str());
    }

    bool onechar::equals(const onechar& cmp) const
    {
        // Ensure the character bytelengths are the same
        if (this->size != cmp.size) { return false; }
        // Perform a raw memory comparison
        return (memcmp(this->internal, cmp.internal, this->size) == 0);
    }

    int onechar::compare(const char cmp) const
    {
        /* This algorithm will not return a meaningful integer; only its
         * relation to 0 will be useful */

        int sizeDiff = this->size - 1;
        // If the bytesize was the same...
        if (sizeDiff == 0)
        {
            // ...return the results of a direct memory comparison
            return memcmp(this->internal, &cmp, 1);
        }
        // Otherwise, return the difference in bytesize.
        return sizeDiff;
    }

    int onechar::compare(const char* cmp) const
    {
        /* This algorithm will not return a meaningful integer; only its
         * relation to 0 will be useful */

        int sizeDiff = this->size - evaluateLength(cmp);
        // If the bytesize was the same...
        if (sizeDiff == 0)
        {
            // ...return the results of a direct memory comparison
            return memcmp(this->internal, cmp, this->size);
        }
        // Otherwise, return the difference in bytesize.
        return sizeDiff;
    }

    int onechar::compare(const std::string& cmp) const
    {
        // Extract the c-string from the std::string and directly compare it.
        return compare(cmp.c_str());
    }

    int onechar::compare(const onechar& cmp) const
    {
        /* This algorithm will not return a meaningful integer; only its
         * relation to 0 will be useful */

        int sizeDiff = this->size - cmp.size;
        // If the bytesize was the same...
        if (sizeDiff == 0)
        {
            // ...return the results of a direct memory comparison
            return memcmp(this->internal, cmp.internal, this->size);
        }
        // Otherwise, return the difference in bytesize.
        return sizeDiff;
    }

}
