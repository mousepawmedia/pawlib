#include "pawlib/onechar.hpp"

namespace pawlib
{
    /** Default constructor*/
    OneChar::OneChar(char* newChar)
    {
        int index = 0;
        
        // Add each non-terminating character to the char array.
        while (newChar[index] != '\0')
        {
            miniChar[index] = newChar[index];
            index++;
        }

        // Add a null terminator to the end of the char array
        miniChar[index] = '\0';
    }

    char OneChar::operator[](int pos) const
    {
        return miniChar[pos];
    }

    OneChar& OneChar::operator=(char newChar)
    {
        miniChar[0] = newChar;
        miniChar[1] = '\0';

        return *this;
    }

    OneChar& OneChar::operator=(const char* newChar)
    {
        int index = 0;
        
        // Add each non-terminating character to the char array.
        while (newChar[index] != '\0')
        {
            miniChar[index] = newChar[index];
            index++;
        }

        // Add a null terminator to the end of the char array
        miniChar[index] = '\0';

        return *this;
    }

    OneChar& OneChar::operator=(const OneChar& newChar)
    {
        int index = 0;
        
        // Add each non-terminating character to the char array.
        while (newChar[index] != '\0')
        {
            miniChar[index] = newChar[index];
            index++;
        }

        // Add a null terminator to the end of the char array
        miniChar[index] = '\0';

        return *this;
    }

    bool OneChar::operator==(char newChar)
    {
        return ((newChar == miniChar[0]) && (miniChar[1] == '\0'));
    }

    bool OneChar::operator==(OneChar& newChar) const
    {
        for (int index = 0; index != '\0'; index++)
        {
            if (miniChar[index] != newChar[index])
            {
                return false;
            }
        }

        return true;
    }

    bool OneChar::operator!=(char newChar) const
    {
        return !((newChar == miniChar[0]) && (miniChar[1] == '\0'));
    }

    bool OneChar::operator!=(OneChar& newChar) const
    {
        for (int index = 0; index != '\0'; index++)
        {
            if (miniChar[index] != newChar[index])
            {
                return true;
            }
        }

        return false;
    }

    void OneChar::print(std:: ostream& os) const
    {
        for (int index = 0; index < 5; index++)
        {
            os << miniChar[index];
        }
    }

    bool OneChar::lessOneChar(const OneChar& compChar)
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

    void OneChar::addDirectly(char newChar, int pos)
    {
        if (pos < 4)
        {
            miniChar[pos] = newChar;
            miniChar[pos + 1] = '\0';
        }
    }
}