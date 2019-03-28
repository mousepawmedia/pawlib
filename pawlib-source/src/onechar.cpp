#include "pawlib/onechar.hpp"

namespace pawlib
{
    OneChar::OneChar()
    : size(1)
    {
        // The default value of a OneChar should be a null terminator
        internal[0] = '\0';
    }

    OneChar::OneChar(const char* cstr)
    : size(1)
    {
        // Extract the first ASCII or Unicode character from the c-string
        parse(cstr);
    }

    OneChar::OneChar(const std::string& str)
    : size(1)
    {
        // Extract the first ASCII or Unicode character from the std::string
        parse(str);
    }

    OneChar::OneChar(const char ch)
    : size(1)
    {
        // Store the ASCII character
        parse(ch);
    }

    OneChar::OneChar(const OneChar& cpy)
    : size(1)
    {
        // Make this a copy of the OneChar
        copy(cpy);
    }

    void OneChar::copy(const OneChar& cpy)
    {
        // Copy the size
        this->size = cpy.size;
        // Directly copy the contents of the internal array
        memcpy(this->internal, cpy.internal, cpy.size);
    }

    void OneChar::parse(const char ch)
    {
        // char is always ASCII (one byte)
        this->size = 1;
        // Store the character
        this->internal[0] = ch;
    }

    void OneChar::parse(const char* cstr)
    {
        /* Determine the bytesize of the Unicode character
         * at the start of the c-string */
        this->size = evaluateLength(cstr);
        // Store the character via direct copy to internal array
        memcpy(this->internal, cstr, sizeof(char) * this->size);
    }

    void OneChar::parse(const std::string& str)
    {
        // Extract the c-string from the std::string and parse it
        parse(str.c_str());
    }

    size_t OneChar::parseFromString(const char* cstr, size_t index)
    {
        /* Determine the bytesize of the Unicode character
         * at the target location in the c-string */
        this->size = evaluateLength(cstr + index);
        // Store the character via direct copy to internal array
        memcpy(this->internal, cstr + index, sizeof(char) * this->size);
        // Return the number of characters we parsed in the c-string
        return this->size;
    }

    size_t OneChar::parseFromString(const std::string& str, size_t index)
    {
        // Extract the c-string from the std::string and parse it
        return parseFromString(str.c_str(), index);
    }

    const char* OneChar::c_str() const
    {
        /* Allocate a c-string just large enough to accomidate the character
         * and a null terminator. The end-user will need to deallocate this
         * via delete[], the same way they would with std::string::c_str() */
        char* r = new char[size+1];
        // Directly copy the contents of the internal array to the c-string
        memcpy(r, this->internal, sizeof(char)*this->size);
        // End the c-string with a null terminator
        r[size] = '\0';
        return r;
    }

    bool OneChar::equals(const char cmp) const
    {
        return ((this->size == 1) && (this->internal[0] == cmp));
    }

    bool OneChar::equals(const char* cmp) const
    {
        size_t cmpSize = evaluateLength(cmp);
        // If the string doesn't null-terminate after one character, mismatch.
        if (cmp[cmpSize] != '\0') {return false;}
        // Ensure the character size matches
        if (cmpSize != this->size) {return false;}
        return (memcmp(this->internal, cmp, cmpSize) == 0);
    }

    bool OneChar::equals_at(const char* cmp) const
    {
        size_t cmpSize = evaluateLength(cmp);
        // Ensure the character size matches
        if (cmpSize != this->size) {return false;}
        return (memcmp(this->internal, cmp, cmpSize) == 0);
    }

    bool OneChar::equals(const std::string& cmp) const
    {
        // Extract the c-string from the std::string and compare it directly
        return equals(cmp.c_str());
    }

    bool OneChar::equals(const OneChar& cmp) const
    {
        // Ensure the character bytelengths are the same
        if (this->size != cmp.size) { return false; }
        // Perform a raw memory comparison
        return (memcmp(this->internal, cmp.internal, this->size) == 0);
    }

    int OneChar::compare(const char cmp) const
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

    int OneChar::compare(const char* cmp) const
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

    int OneChar::compare(const std::string& cmp) const
    {
        // Extract the c-string from the std::string and directly compare it.
        return compare(cmp.c_str());
    }

    int OneChar::compare(const OneChar& cmp) const
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
