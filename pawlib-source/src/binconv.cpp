#include "binconv.hpp"

string binconv::toBinary(bool b)
{
    string binary(8, '0');
    if(b)
        binary[7] = '1';
    return binary;
}

bool binconv::toBool(string binary)
{
    return binary[7] == '1';
}

int binconv::toTernary(string binary)
{
    return toLong(binary);
}

//returns a 32 bit representation by default. Can return a different size as desired
string binconv::toBinary(int num, int numBits)
{
    string binary(numBits, '0');
    for(int i = numBits - 1; i > -1; i--)
    {
        if(num % 2 == 1)
            binary[i] = '1';
        num /= 2;
    }
    return binary;
}

int binconv::toInt(string binary)
{
    return (int) toLong(binary);
}

string binconv::toBinary(long num, int numBits)
{
    string binary(numBits, '0');
    for(int i = numBits - 1; i > -1; i--)
    {
        if(num % 2 == 1)
            binary[i] = '1';
        num /= 2;
    }
    //ss.str();
    return binary;
}

long binconv::toLong(string binary)
{
    long value = 0;
    for(unsigned int i = 0; i < binary.length(); i++)
    {
        if(binary[binary.length() - 1 - i] == '1')
            value += pow(2, i);
    }
    return value;
}

//conversion from double to binary with single floating point precision
//returns a 32 bit representation
string binconv::toBinary(float num)
{
    //the number of bits used to store this type of number (8 bytes)
    int numBits = 32;
    //stores the new binary format
    string binary(numBits, '0');
    if(num != 0)
    {
        //stores a 0 if the number is positive
        if(num < 0)
        {
            //stores a 1 if negative
            binary[0] = '1';
            //convert the number to a positive number to be used later
            num -= num * 2;
        }
        //stores the number that is before the decimal point
        int beforeDecimal = (int) num;
        //stores the number that is after the decimal point
        double afterDecimal = num - beforeDecimal;
        //determines the size of characters in the number
        //Examples: 9 = 1, 10 = 2, 100 = 3
        int decimalIndex;
        if(beforeDecimal > 0)
            decimalIndex = (int)log2(beforeDecimal);
        else
            decimalIndex = 0;
        //convert the number before the decimal to binary
        //don't include the 1 from the mantissa
        for(int i = decimalIndex; i > 0; i--)
        {
            //the bits value is the remainer of the current number divided by 2
            //there are 9 bits before the mantissa value begins and we don't include the first mantissa bit
            if(beforeDecimal % 2 == 1)
                binary[i + 8] = '1';
            //divide by 2 to prepare for the next bit
            beforeDecimal /= 2;
        }
        //the starting point of the binary representation of the number after the decimal
        int pageIndex = decimalIndex + 9;
        //a temporary representation of the value after the decimal. afterDecimal is needed later
        double temp = afterDecimal;
        //keep going until all of the bits of the mantissa are used
        while(pageIndex < numBits)
        {
            //multiply the value by 2
            temp *= 2;
            //the binary representation is if the new value is greater than or euqal to 1 or not
            //if the number is greater than or equal to 1, subtract 1 to prepare for the next bit
            if((int)(temp / 1) == 1)
            {
                binary[pageIndex] = '1';
                temp -= 1;
            }
            else
            {
                int mike = 1;
            }
            pageIndex++;
        }
        //the exponent used for conversion
        int exponent;
        //if the absolute value of the number(taken earlier) is greater than 1
        if(num > 1)
        {
            //the single point precission bias is 127
            exponent = 127 + decimalIndex;
        }
        else
        {
            //determine how many places after the decimal the first non 0 number is
            for(pageIndex = 0; ((int)afterDecimal / 1) == 0; pageIndex++)
            {
                afterDecimal *= 2;
            }
            exponent = 127 - pageIndex;
        }
        //now convert the exponents value to binary
        //there are 8 bits for the exponent
        for(int i = 8; i > 0; i--)
        {
            if(exponent % 2 == 1)
                binary[i] = '1';
            exponent /= 2;
        }
    }
    return binary;
}

//converts the passed in binary string into a long
float binconv::toFloat(string binary)
{
    //the value starts at 0
    float val = 0;
    if(binary.find("1") == -1)
        return 0;
    //used to determine if the number is a positive or negative number
    int theSign = 1;
    //if the first bit is a 1, the number is negative
    if(binary[0] == '1')
        theSign = -1;
    //gets the bits that store the exponent
    string temp = binary.substr(1, 8);
    //convert the exponent bits to a number
    int theExponent = toInt(temp) - 127;
    //if the exponent is a positive number
    if(theExponent > 0.0)
    {
        //get the number before the decimal
        temp = binary.substr(9, theExponent);
        //convert the number before the decimal to a base 10 number
        for(int i = 0; i < theExponent; i++)
        {
            if(temp[theExponent - i - 1] == '1')
                val += pow(2, i);
        }
        //add the value of the 1 that was chopped off for the mantissa
        val += pow(2, theExponent);
        //get the value after the decimal
        temp = binary.substr(9 + theExponent, 32 - 9 - theExponent);
        //convert the number after the decimal  to a base 10 number
        for(unsigned int i = 0; i < temp.size(); i++)
        {
            if(temp[i] == '1')
            {
                val += (1 / pow(2, i + 1));
            }
        }
    }
    //If the exponent is a negative number
    else
    {
        //get the entire mantissa part of the format
        temp = binary.substr(9, 32 - 9);
        //get the value of the number by adding 1 over the current power of 2
        val += (1 / pow(2, -1 * theExponent));
        for(unsigned int i = 0; i < temp.size(); i++)
        {
            if(temp[i] == '1')
                val += (1 / pow(2, i + 1 + -1 * theExponent));
        }
    }
    //multiply the value by the sign to get the value and return it
    return theSign * val;
}

//conversion from double to binary with double floating point precision
//returns a 64 bit representation
string binconv::toBinary(double num)
{
    //the number of bits used to store this type of number (16 bytes)
    int numBits = 64;
    //stores the new binary format
    string binary(64, '0');
    if (num != 0)
    {
        //stores a 0 if the number is positive
        if(num < 0)
        {
            //stores a 1 if negative
            binary[0] = '1';
            //convert the number to a positive number to be used later
            num -= num * 2;
        }
        //stores the number that is before the decimal point
        int beforeDecimal = (int) num;
        //stores the number that is after the decimal point
        double afterDecimal = num - beforeDecimal;
        //determines the size of characters in the number
        //Examples: 9 = 1, 10 = 2, 100 = 3
        int decimalIndex;
        if(beforeDecimal > 0)
            decimalIndex = (int)log2(beforeDecimal);
        else
            decimalIndex = 0;
        //convert the number before the decimal to binary
        for(int i = decimalIndex; i > 0; i--)
        {
            //the bits value is the remainer of the current number divided by 2
            //there are 12 bits before the mantissa value starts
            if(beforeDecimal % 2 == 1)
                binary[i + 11] = '1';
            beforeDecimal /= 2;
        }
        //the starting point of the binary representation of the number after the decimal
        int pageIndex = decimalIndex + 12;
        //a temporary representation of the value after the decimal. afterDecimal is needed later
        double temp = afterDecimal;
        while(pageIndex < numBits)
        //keep going until all of the bits of the mantissa are used
        {
            //multiply the value by 2
            temp *= 2;
            //the binary representation is if the new value is greater than or euqal to 1 or not
            //if the number is greater than or equal to 1, subtract 1 to prepare for the next bit
            if((int)(temp / 1) == 1)
            {
                binary[pageIndex] = '1';
                temp -= 1;
            }
            //move on to the next index
            pageIndex++;
        }
        //the exponent used for conversion
        int exponent;
        pageIndex = 0;
        //if the absolute value of the number(taken earlier) is greater than 1
        if(num > 1)
        {
            //the single point precission bias is 1023
            exponent = 1023 + decimalIndex;
        }
        else
        {
            //determine how many places after the decimal the first non 0 number is
            for(pageIndex = 0; ((int)afterDecimal / 1) == 0; pageIndex++)
            {
                afterDecimal *= 2;
            }
            exponent = 1023 - pageIndex;
        }
        //now convert the exponents value to binary
        //there are 11 bits for the exponent
        for(int i = 11; i > 0; i--)
        {
            if(exponent % 2 == 1)
                binary[i] = '1';
            exponent /= 2;
        }
    }
    return binary;
}

double binconv::toDouble(string binary)
{
    //stores the new decimal value
    double val = 0;
    if(binary.find("1") == -1)
        return 0;
    int theSign = 1;
    //if the sign bit is set, the number needs to be multiplied by a negative 1 at the end
    if(binary[0] == '1')
        theSign = -1;
    //get the exponent bits
    string temp = binary.substr(1, 11);
    //convert the exponent to a base 10 number
    int theExponent = toInt(temp) - 1023;
    //if the exponent is a positive number
    if(theExponent > 0)
    {
        //get the binary values before the decimal
        temp = binary.substr(12, theExponent);
        //convert the number before the decimal to a base 10 number
        for(int i = 0; i < theExponent; i++)
        {
            if(temp[theExponent - i - 1] == '1')
                val += pow(2, i);
        }
        val += pow(2, theExponent);
        //get the binary after the decimal
        temp = binary.substr(12 + theExponent, 32 - 12 - theExponent);
        //convert the number after the decimal to a base 10 number
        for(unsigned int i = 0; i < temp.size(); i++)
        {
            if(temp[i] == '1')
            {
                val += (1 / pow(2, i + 1));
            }
        }
    }
    //if the exponent is a negative number
    else
    {
        //get the mantissa value
        temp = binary.substr(12, 32 - 12);
        val += (1 / pow(2, -1 * theExponent));
        for(unsigned int i = 0; i < temp.size(); i++)
        {
            if(temp[i] == '1')
                val += (1 / pow(2, i + 1 + -1 * theExponent));
        }
    }
    //multiply the value by the sign value
    return theSign * val;
}

string binconv::toBinary(char c)
{
    string binary(8, '0');
    int charVal = (int)c;
    for(int i = 7; i > -1; i--)
    {
        if(charVal % 2 == 1)
            binary.at(i) = '1';
        charVal /= 2;
    }
    return binary;
}

char binconv::toChar(string binary)
{
    return (char) toLong(binary);
}

string binconv::toBinary(string theString)
{
    stringstream ss;
    for(unsigned int i = 0; i < theString.size(); i++)
    {
        ss << toBinary(theString.at(i));
    }
    return ss.str();
}

string binconv::binaryToString(string binary)
{
    stringstream r;
    string character;
    for(int i = 0; i < binary.length() / 8; i++)
    {
        character = binary.substr(i * 8, 8);
        r << toChar(character);
    }
    return r.str();
}
