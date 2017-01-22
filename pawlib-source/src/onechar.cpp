#include "pawlib/onechar.hpp"

namespace pawlib
{
    /*************************************************************************
    // The UniChar functions start here
    **************************************************************************/
    UniChar::UniChar(const char* newChar)
    {
        // We need to check that the input is only Unicode and not conventional
        // strings. This can be done by checking the first character. Since
        // Unicode chars are large hex numbers, they will be negative.
        if(newChar[0] < 0 )
        {
            int index;
            // Add each non-terminating character to the char array.
            for(index = 0; newChar[index] != '\0'; index++)
            {
                miniChar[index] = newChar[index];
            }
            // Add a null terminator to the end of the char array
            miniChar[index] = '\0';
        }
        else
        {
            ioc << cat_error << "WARNING: " " is only for using multi-byte "
            << "Unicode chars. Use ' ' for ASCII characters." <<io_end;
        }
    }

    char UniChar::operator[](int pos) const
    {
        return miniChar[pos];
    }

    char& UniChar::operator[](int pos)
    {
        return miniChar[pos];
    }

    OneChar& UniChar::operator=(char newChar)
    {
        // Due to the nature of char, we know it is one byte
        // Add the char to the beginning of an array of chars,
        // and then add a null terminator to the next position in the array.
        this->miniChar[0] = newChar;
        this->miniChar[1] = '\0';
        return *this;
    }

    OneChar& UniChar::operator=(const char* newChar)
    {
        // We need to check that the input is only Unicode and not conventional
        // strings. This can be done by checking the first character. Since
        // Unicode chars are large hex numbers, they will be negative.
        if(newChar[0] < 0 )
        {
            int index;
            // Add each non-terminating character to the char array.
            for(index = 0; newChar[index] != '\0'; index++)
            {
                this->miniChar[index] = newChar[index];
            }
            // Add a null terminator to the end of the char array
            this->miniChar[index] = '\0';
        }
        else
        {
            ioc << cat_error << "WARNING: " " is only for using multi-byte "
            << "Unicode chars. Use ' ' for ASCII characters." <<io_end;
        }
        return *this;
    }


    OneChar& UniChar::operator=(const OneChar& newChar)
    {
        // Create from UniChar
        if(newChar.getId() == UNICODE)
        {
            int index;
            // Add each non-terminating character to the char array.
            for(index = 0; newChar[index] != '\0'; index++)
            {
                miniChar[index] =  newChar[index];
            }
            // Add a null-terminator to the end of the char array
            miniChar[index] = '\0';
        }
        // Create from AscChar
        else
        {
            miniChar[0] = newChar[0];
            miniChar[1] = '\0';
        }
        return *this;
    }

    void UniChar::print( std::ostream& os) const
    {
		// To display the full OneChar we loop through the char array
        // until a null-terminator is found.
        for(int i = 0; miniChar[i] != '\0'; ++i)
        {
            os<< miniChar[i];
        }
	}

	bool UniChar::lessOneChar(const OneChar& compChar)
	{
	    // If comparing to another UniChar, loop through all indexes.
	    if(compChar.getId() == UNICODE)
        {
            int i;
            for(i = 0; miniChar[i] != '\0'; ++i)
            {
                // If the input has reached the end, then the input is smaller
                if(compChar[i] == '\0')
                {
                    return false;
                }

                // If smaller, then we know the input is larger
                if(miniChar[i] < compChar[i])
                {
                    return true;
                }
                // If larger, then we know the input is smaller
                else if(miniChar[i] > compChar[i])
                {
                    return false;
                }
            }

            // If we made it through the loop, and there is more input
            // then the current character is smaller
            if(compChar[i] != '\0')
            {
                return true;
            }
            return false;
        }
        // If comparing to AscChar, just look at first character
        else
        {
            // Just look at first character and make sure it's the only
            // character in the array
            return ((miniChar[0] < compChar[0]) && (miniChar[1] == '\0'));
        }
	}

    bool UniChar::operator==(const OneChar& newChar)
    {
        // Compare to UNICODE
        if(newChar.getId() == UNICODE)
        {
            // Two OneChars are equal if every value in their arrays are equivalent
            for(int i = 0; newChar[i] != '\0'; ++i)
            {
                if(miniChar[i] != newChar[i])
                {
                    return false;
                }
            }
            return true;
        }
        // Compare to ASCII
        else
        {
            return((miniChar[1] == '\0') && (miniChar[0] == newChar[0]) );
        }
    }

    bool UniChar::operator==(char newChar)
    {
        // Compare to the first char in the char array,
        // And make sure the OneChar is only 1 byte.
        return ((newChar == miniChar[0]) && (miniChar[1] == '\0'));
    }

    bool operator==(const UniChar& ochr, char* newChar)
    {
        for(int i = 0; newChar[i] != '\0'; ++i)
        {
            // Check if each position in the char* is equal to the
            // same position in the OneChar
            if(ochr.miniChar[i] != newChar[i])
            {
                return false;
            }
        }
        return true;
    }


    /*************************************************************
     * AscChar functions
     *************************************************************/

    char AscChar::operator[](int pos) const
    {
        // We don't actually use the parameter
        (void)pos;

        //It doesn't matter what number is given. Just return the char
        return masterChar;
    }

    char& AscChar::operator[](int pos)
    {
        (void) pos;

        //It doesn't matter what number is give. Just return the char
        return masterChar;
    }

	OneChar& AscChar::operator=(char newChar)
	{
	    this->masterChar = newChar;
	    return *this;
	}


    OneChar& AscChar::operator=(const char* newChar)
    {
        this->masterChar = newChar[0];
        return *this;
    }


    OneChar& AscChar::operator=(const OneChar& newChar)
    {
        // Either mode, setting 0 will give the right result
        this->masterChar = newChar[0];
        return *this;
    }


	void AscChar::print( std::ostream& os) const
    {
		os << masterChar;
	}

	bool AscChar::lessOneChar(const OneChar& compChar)
	{
	    // If comparing to UniChar, compare to first char in array and
	    // check that the second char is the terminator
	    if(compChar.getId() == ASCII)
        {
            return ((masterChar < compChar[0]) && (compChar[1] == '\0'));
        }
        // If comparing to AscChar, do straight comparison
        else
        {
            return (masterChar < compChar[0]);
        }
	}


	bool AscChar::operator==(const OneChar& newChar)
	{
	    // Compare to ASCII
        if(newChar.getId() == ASCII)
        {
            // Directly compare the chars
            return(masterChar == newChar[0]);
        }
	     // Compare to UNICODE
        else
        {
            // Check that newChar is only one character and then compare
            return((newChar[1] == '\0') && (masterChar == newChar[0]) );
        }

	}

	bool AscChar::operator==(char newChar)
	{
	    return (masterChar == newChar);
	}


    bool operator==(const AscChar& ochr, char* newChar)
    {
        // Return if correct character and only one char long
        return((ochr[0] == newChar[0]) && (newChar[1] == '\0'));
    }


    bool operator<(const AscChar& ochr, const AscChar &newChar)
    {
        return (ochr[0] < newChar[0]);
    }



}
