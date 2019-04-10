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

    OneChar& OneString::at(size_t pos)
    {
        if (pos > _elements)
        {
            throw std::out_of_range("OneString::at(): Index out of bounds.");
        }

        return internal[pos];
    }

    const OneChar& OneString::at(size_t pos) const
    {
        if (pos > _elements)
        {
            throw std::out_of_range("OneString::at(): Index out of bounds.");
        }

        return internal[pos];
    }

    OneChar& OneString::back()
    {
        // WARNING: If string is empty, this is undefined (but memory safe)
        // Return a reference to the last element in the string.
        return this->internal[_elements - 1];
    }

    const OneChar& OneString::back() const
    {
        // WARNING: If string is empty, this is undefined (but memory safe)
        // Return a reference to the last element in the string.
        return this->internal[_elements - 1];
    }

    size_t OneString::capacity() const
    {
        return _capacity;
    }

    size_t OneString::copy(char* arr, size_t max, size_t len, size_t pos) const
    {
        // Reminder: len and pos default to 0

        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::copy(): specified pos out of range");
        }

        // Remove one char from the max to account for the null terminator.
        --max;

        // The indices for the c-string and (this) onestring.
        size_t cstr_i = 0;
        size_t ostr_i = pos;

        // Account for unspecified len, or adjust so it doesn't blow past the end.
        if (len == 0 || len + pos > this->_elements)
        {
            len = this->_elements - pos;
        }

        while (cstr_i < max && ostr_i < len)
        {
            memcpy(arr + cstr_i, this->internal[ostr_i].internal, this->internal[ostr_i].size);
            cstr_i += this->internal[ostr_i].size;
            ++ostr_i;
        }

        arr[cstr_i] = '\0';

        return cstr_i;
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

    OneChar& OneString::front()
    {
        // WARNING: If string is empty, this is undefined (but memory safe)
        // Return a reference to the first element in the string.
        return this->internal[0];
    }

    const OneChar& OneString::front() const
    {
        // WARNING: If string is empty, this is undefined (but memory safe)
        // Return a reference to the last element in the string.
        return this->internal[0];
    }

    size_t OneString::length() const
    {
        return _elements;
    }

    OneString OneString::substr(size_t pos, size_t len) const
    {
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::substr(): specified pos out of range");
        }

        OneString r;
        // Calculate size of substr (number of elements)
        size_t elements_to_copy = (len > _elements - pos) ? (_elements - pos) : len;
        // Reserve necessary space in the new OneString
        r.reserve(elements_to_copy);
        // Copy the memory for the substring
        memcpy(r.internal, this->internal + pos, sizeof(OneChar) * elements_to_copy);
        // Record how many elements were copied.
        r._elements = elements_to_copy;
        return r;
    }

    size_t OneString::size() const
    {
        // Start counting at 1 to account for the null terminator.
        size_t bytes = 1;
        // Sum all of the byte lengths of the OneChars.
        for(size_t i = 0; i < _elements; ++i)
        {
            bytes += this->internal[i].size;
        }
        return bytes;
    }

    size_t OneString::size(size_t len, size_t pos) const
    {
        // Reminder: pos defaults to 0

        // Ensure the starting position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::size(): specified pos out of range");
        }

        // Start counting at 1 to account for the null terminator.
        size_t bytes = 1;

        // Sum all of the byte lengths of the OneChars in the range
        for(size_t i = pos; i < (pos + len) && i < _elements; ++i)
        {
            bytes += this->internal[i].size;
        }
        return bytes;
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
            if (!(this->internal[compare_to].equals_at(cstr + index))) { return false; }
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

    int OneString::compare(const char ch) const
    {
        int sizeDiff = this->_elements - 1;
        if (sizeDiff == 0)
        {
            return this->internal[0].compare(ch);
        }
        return sizeDiff;
    }

    int OneString::compare(const char* cstr) const
    {
        /* This algorithm will not return a meaningful integer; only its
         * relation to 0 will be useful */

        int sizeDiff = this->_elements - characterCount(cstr);

        if (sizeDiff == 0)
        {
            size_t j = 0;
            // If the strings are the same length, compare each character...
            for(size_t i = 0; i < this->_elements; ++i)
            {
                // Return the compare result of the first character mismatch
                int r = this->internal[i].compare(cstr+j);
                if ( r != 0) { return r; }

                j += OneChar::evaluateLength(cstr+j);
            }
        }
        return sizeDiff;
    }

    int OneString::compare(const std::string& str) const
    {
        return compare(str.c_str());
    }

    int OneString::compare(const OneChar& ochr) const
    {
        int sizeDiff = this->_elements - 1;
        if (sizeDiff == 0)
        {
            return this->internal[0].compare(ochr);
        }
        return sizeDiff;
    }

    int OneString::compare(const OneString& ostr) const
    {
        /* This algorithm will not return a meaningful integer; only its
         * relation to 0 will be useful */

        int sizeDiff = this->_elements - ostr._elements;
        if (sizeDiff == 0)
        {
            // If the strings are the same length, compare each character...
            for(size_t i = 0; i < this->_elements; ++i)
            {
                // Return the compare result of the first character mismatch
                int r = this->internal[i].compare(ostr.internal[i]);
                if ( r != 0) { return r; }
            }
        }
        return sizeDiff;
    }

    /*******************************************
    * Adding + Inserting
    ********************************************/

    OneString& OneString::assign(const char ch)
    {
        clear();
        reserve(1);
        this->internal[_elements++] = ch;
        return *this;
    }

    OneString& OneString::assign(const char* cstr)
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
        return *this;
    }

    OneString& OneString::assign(const std::string& str)
    {
        assign(str.c_str());
        return *this;
    }

    OneString& OneString::assign(const OneChar& ochr)
    {
        clear();
        reserve(1);
        this->internal[_elements++] = ochr;
        return *this;
    }

    OneString& OneString::assign(const OneString& ostr)
    {
        clear();
        reserve(ostr._elements);
        memcpy(this->internal, ostr.internal, sizeof(OneChar) * ostr._elements);
        _elements = ostr._elements;
        return *this;
    }

    OneString& OneString::append(const char ch)
    {
        expand(1);

        // Insert a 1-byte ASCII char
        internal[_elements++] = ch;
        return *this;
    }

    OneString& OneString::append(const char* cstr)
    {
        size_t index = 0;
        size_t len = characterCount(cstr);
        expand(len);

        // Loop through each character in the string literal
        while(cstr[index] != '\0')
        {
            index += internal[_elements++].parseFromString(cstr, index);
        }
        return *this;
    }

    OneString& OneString::append(const std::string& str)
    {
        // Parse the internal c string directly.
        append(str.c_str());
        return *this;
    }

    OneString& OneString::append(const OneChar& ochar)
    {
        expand(1);
        internal[_elements++] = ochar;
        return *this;
    }

    OneString& OneString::append(const OneString& ostr)
    {
        expand(ostr.length());

        size_t index = 0;
        while(!(ostr[index] == '\0'))
        {
            internal[index + _elements] = ostr[index];
            ++index;
        }

        _elements += ostr.length();

        return *this;
    }

    OneString& OneString::insert(size_t pos, char ch)
    {
        // Ensure the insertion position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::insert(): specified pos out of range");
        }

        // Calculate how many elements need to be shifted to make room (right partition)
        size_t elements_to_move = _elements - pos;
        // Reserve needed space
        expand(1);
        // Move the right partition to make room for the new element
        memmove(this->internal + pos + 1,
                this->internal + pos,
                sizeof(OneChar) * elements_to_move);
        // Insert the new element
        this->internal[pos] = ch;
        // Increase the element count
        ++_elements;

        return *this;
    }

    OneString& OneString::insert(size_t pos, char* cstr)
    {
        // Ensure the insertion position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::insert(): specified pos out of range");
        }

        size_t elements_to_insert = characterCount(cstr);
        // Calculate how many elements need to be shifted to make room (right partition)
        size_t elements_to_move = _elements - pos;
        // Reserve needed space
        expand(elements_to_insert);
        // Move the right partition to make room for the new element
        memmove(this->internal + pos + elements_to_insert,
                this->internal + pos,
                sizeof(OneChar) * elements_to_move);

        // Insert the new elements
        size_t index = 0;
        while(cstr[index] != '\0')
        {
            // Parse and store the character.
            index += internal[pos++].parseFromString(cstr, index);
        }
        // Increase the element count
        _elements += elements_to_insert;

        return *this;
    }

    OneString& OneString::insert(size_t pos, std::string& str)
    {
        return insert(pos, str.c_str());
    }

    OneString& OneString::insert(size_t pos, OneChar& ochr)
    {
        // Ensure the insertion position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::insert(): specified pos out of range");
        }

        // Calculate how many elements need to be shifted to make room (right partition)
        size_t elements_to_move = _elements - pos;
        // Reserve needed space
        expand(1);
        // Move the right partition to make room for the new element
        memmove(this->internal + pos + 1,
                this->internal + pos,
                sizeof(OneChar) * elements_to_move);
        // Insert the new element
        this->internal[pos] = ochr;
        // Increase the element count
        ++_elements;

        return *this;
    }

    OneString& OneString::insert(size_t pos, const OneString& ostr)
    {
        // Ensure the insertion position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::insert(): specified pos out of range");
        }

        size_t elements_to_insert = ostr._elements;
        // Calculate how many elements need to be shifted to make room (right partition)
        size_t elements_to_move = _elements - pos;
        // Reserve needed space
        expand(elements_to_insert);
        // Move the right partition to make room for the new element
        memmove(this->internal + pos + elements_to_insert,
                this->internal + pos,
                sizeof(OneChar) * elements_to_move);

        // Insert the new elements
        memcpy(this->internal + pos,
               ostr.internal,
               sizeof(OneChar) * elements_to_insert);
        // Increase the element count
        _elements += elements_to_insert;

        return *this;
    }

    void OneString::replace_setup(size_t pos, size_t len, size_t sublen)
    {
        // WARNING: pos and len are not validated. That MUST be done externally!

        // Calculate whether we're replacing 1:1, expanding, or erasing
        int difference = sublen - len;
        size_t pos_after = pos + len;
        size_t elements_after = _elements - pos_after;

        // If our replacement expands the string...
        if (difference > 0)
        {
            // Reserve the needed space
            expand(difference);

            // Move the right partition to make room, if necessary
            if (elements_after > 0)
            {
                memmove(this->internal + pos + len + difference,
                        this->internal + pos_after,
                        sizeof(OneChar) * elements_after);
            }

            // Update the element count
            _elements += difference;
        }
        // Otherwise, if our replacement shrinks the string...
        else if (difference < 0)
        {
            // Move the right partition back, erasing excess characters.
            if (elements_after > 0)
            {
                memmove(this->internal + pos + len + difference,
                        this->internal + pos_after,
                        sizeof(OneChar) * elements_after);
            }

            // Update the element count
            _elements += difference;
        }

        // If the string size won't change, we need no extra setup.
    }

    OneString& OneString::replace(size_t pos, size_t len, const char ch)
    {
        // Ensure the replacement position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::replace(): specified pos out of range");
        }

        // Adjust len so it doesn't run past the end of the string
        len = (len > _elements - pos) ? (_elements - pos) : len;

        // Rearrange the string memory to accommodate the new data
        replace_setup(pos, len, 1);

        // Write the data, using pos as our destination index.
        this->internal[pos] = ch;

        return *this;
    }

    OneString& OneString::replace(size_t pos, size_t len, const OneChar& ochr)
    {
        // Ensure the replacement position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::replace(): specified pos out of range");
        }

        // Adjust len so it doesn't run past the end of the string
        len = (len > _elements - pos) ? (_elements - pos) : len;

        // Rearrange the string memory to accommodate the new data
        replace_setup(pos, len, 1);

        // Write the data, using pos as our destination index.
        this->internal[pos] = ochr;

        return *this;
    }

    OneString& OneString::replace(size_t pos, size_t len, const char* cstr)
    {
        // Ensure the replacement position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::replace(): specified pos out of range");
        }

        // Adjust len so it doesn't run past the end of the string
        len = (len > _elements - pos) ? (_elements - pos) : len;

        // Rearrange the string memory to accommodate the new data
        replace_setup(pos, len, characterCount(cstr));

        // Write the data, using pos as our destination index.
        size_t index = 0;
        while(cstr[index] != '\0')
        {
            // Parse and store the character.
            index += internal[pos++].parseFromString(cstr, index);
        }

        return *this;
    }

    OneString& OneString::replace(size_t pos, size_t len, const std::string& str)
    {
        return replace(pos, len, str.c_str());
    }

    OneString& OneString::replace(size_t pos, size_t len, const OneString& ostr)
    {
        // Ensure the replacement position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::replace(): specified pos out of range");
        }

        // Adjust len so it doesn't run past the end of the string
        len = (len > _elements - pos) ? (_elements - pos) : len;

        // Rearrange the string memory to accommodate the new data
        replace_setup(pos, len, ostr._elements);

        /* Replace the characters directly. We use memmove so we can safely
         * use the same string as the destination AND the source.
         */
        memmove(this->internal + pos, ostr.internal, sizeof(OneChar) * ostr._elements);

        return *this;
    }

    OneString& OneString::replace(size_t pos, size_t len, const char* cstr, size_t subpos, size_t sublen)
    {
        // Ensure the replacement position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::replace(): specified pos out of range");
        }

        size_t cstr_len = strlen(cstr);
        if (subpos >= cstr_len)
        {
            throw std::out_of_range("OneString::replace(): specified subpos out of range");
        }

        // Adjust len so it doesn't run past the end of the string
        len = (len > _elements - pos) ? (_elements - pos) : len;
        // Adjust sublen so it doesn't run past the end of the c-string.
        sublen = (sublen > cstr_len - subpos) ? (cstr_len - subpos) : sublen;

        // Rearrange the string memory to accommodate the new data
        replace_setup(pos, len, sublen);

        // Repurpose sublen so it marks the end of the area we are to copy from
        sublen += subpos;

        // Replace the characters in the specified range, using pos and subpos as our indices.
        while(subpos < sublen)
        {
            // Parse and store the character.
            subpos += internal[pos++].parseFromString(cstr, subpos);
        }

        return *this;
    }

    OneString& OneString::replace(size_t pos, size_t len, const std::string& str, size_t subpos, size_t sublen)
    {
        return replace(pos, len, str.c_str(), subpos, sublen);
    }

    OneString& OneString::replace(size_t pos, size_t len, const OneString& ostr, size_t subpos, size_t sublen)
    {
        // Ensure the replacement position is in range.
        if (pos >= this->_elements)
        {
            throw std::out_of_range("OneString::replace(): specified pos out of range");
        }

        if (subpos >= ostr._elements)
        {
            throw std::out_of_range("OneString::replace(): specified subpos out of range");
        }

        // Adjust len so it doesn't run past the end of the string
        len = (len > _elements - pos) ? (_elements - pos) : len;
        // Adjust sublen so it doesn't run past the end of the c-string.
        sublen = (sublen > ostr._elements - subpos) ? (ostr._elements - subpos) : sublen;

        // Rearrange the string memory to accommodate the new data
        replace_setup(pos, len, sublen);

        /* Replace the characters directly. We use memmove so we can safely
         * use the same string as the destination AND the source.
         */
        memmove(this->internal + pos,
                ostr.internal + subpos,
                sizeof(OneChar) * sublen);

        return *this;
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

    OneString& OneString::erase(size_t pos, size_t len)
    {
        if (pos > _elements)
        {
            throw std::out_of_range("OneString::erase(): Index out of bounds.");
        }

        // Calculate the number of elements we need to REMOVE
        len = (len > _elements - pos) ? (_elements - pos) : len;

        // Calculate the number of elements we need to move
        size_t elements_to_move = _elements - pos - len;

        // Overwrite the elements
        memcpy(this->internal + pos, this->internal + pos + len, sizeof(OneChar) * elements_to_move);

        // Update the number of elements
        _elements = _elements - len;

        return *this;
    }

    void OneString::pop_back()
    {
        if(_elements > 0)
        {
            /* We don't actually need to delete anything. The space will be
            * reused or deallocated as needed by other functions. */
            --_elements;
        }
    }

    ///////////////////// REVIEW //////////////////////

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
}
