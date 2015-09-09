#include "stdutils.h"

namespace pawlib
{
    stdutils::stdutils()
    {
        //ctor
    }

    char* stdutils::strrev(char* str)
    {
        if (str != NULL)
        {
            char *src;
            size_t len;

            len = strlen (str);
            if (len > 1)
            {
                char *dst;
                src = str;
                dst = src + len - 1;
                while (src < dst)
                {
                    char tmp = *src;
                    *src++ = *dst;
                    *dst-- = tmp;
                }
            }
        }
        return str;
    }

    int stdutils::intlen(int number, int base, bool count_neg)
    {
        if(base < 2 || base > 36)
        {
            return -1;
        }
        int digits = 0;
        if (number < 0 && count_neg)
        {
            digits = 1;
        }
        //Else if the number is literally "0"...
        else if(number == 0)
        {
            digits = 1;
        }
        while (number)
        {
            number /= base;
            digits++;
        }

        return digits;
    }

    int stdutils::uintlen(unsigned int number, int base)
    {
        if(base < 2 || base > 36)
        {
            return -1;
        }
        unsigned int digits = 0;

        //If the number is literally "0"...
        if(number == 0)
        {
            digits = 1;
        }
        while (number)
        {
            number /= base;
            digits++;
        }

        return digits;
    }

    int stdutils::floatlen(double val, int precision, int sci, bool count_sym)
    {
        int len = 0;

        //Flag if the number is negative.
        bool neg = val < 0;

        //If we have a negative value...
        if(neg)
        {
            //Flip the value.
            val = -val;
            //If we're counting symbols, add one for the negative sign.
            if(count_sym){len++;}
        }

        //Calculate the magnitude.
        int m = log10(val);

        //Determine if we're using scientific notation.
        bool useExp = (
            ((sci == 1) && (m >= 14 || (neg && m >= 9) || m <= -9)) ||
            (sci == 2)
        );

        /* The maximum number of digits is usually the significand, which is our
         * 'precision' variable.*/
        len += precision;

        /* Sometimes, the whole part goes past the size of the significand,
         * so add the intlen of the whole part of the float.*/
        len += intlen(static_cast<int>(val), 10, false);

        //If we're using an exponent AND we're counting symbols.
        if(useExp && count_sym)
        {
            /* We add the intlen of the absolute value of the magnitude,
             * plus one for the sign and one for the 'e'.*/
            len += (intlen(m, 10, false) + 2);
        }

        //If we're counting symbols, add one for the decimal point.
        if(count_sym){len++;}

        //Return the finished maximum length.
        return len;
    }

    void stdutils::ptrtoa(char* str, uintptr_t val, bool use_caps)
    {
        /* 64-bits, plus sign and 0x.*/
        ////int len = 67;
        //TODO: Use 32-bit on 32-bit system.

        /*Declare a new C-string.*/
        //char str[len+1] = {'\0'};

        //The current position is length - 1 (to offset)
        char* pos = str;

        /*if (val < 0)
        {
            //Make the number positive;
            val *= -1;
            //Place the symbol at the start of the string.
            //// *pos = '-';
        }*/


        if (val == 0)
        {
            //Write out a literal 0
            *(pos++) = '0';
        }

        while (val)
        {
            uintptr_t digit = val % 16;

            /*To get the corresponding character, just add 48 for a numeral,
            or 55 for a letter. We don't have to worry about verifying that
            the character is appropriate for the base, as the `i % base` will
            never yield a value more than the base.
            */

            //48 [0] - 57 [9] (+48)
            if(/*digit >= 0 && */digit <= 9)
            {
                *(pos++) = static_cast<char>(digit+48);
            }
            //65 [A] - 90 [Z] (+55) or 97 [a] - 122 [z] (+87)
            else if(digit >= 10 && digit <= 35)
            {
                int offset = (use_caps ? 55 : 87);
                *(pos++) = static_cast<char>(digit+offset);
            }

            //Divide the number by the base to remove the last parsed digit.
            val /= 16;
        }

        //Add the hexadecimal indicator 0x".
        *(pos++) = 'x';
        *(pos++) = '0';

        //Reverse the string.
        char temp[strlen(str)] = {'\0'};
        strcpy(temp, str);
        strcpy(str, strrev(temp));
    }

    void stdutils::uitoa(char* str, unsigned int val, int base, int len, bool use_caps, bool byte)
    {
        len = (len == 0) ? uintlen(val, base) : len;

        char* pos = str;

        bool leadZero = false;
        if(val < base && byte)
        {
            leadZero = true;
        }

        if (val == 0)
        {
            //Write out a literal 0
            *(pos++) = '0';
        }

        while (val)
        {
            unsigned int digit = val % base;

            /*To get the corresponding character, just add 48 for a numeral,
            or 55 for a letter. We don't have to worry about verifying that
            the character is appropriate for the base, as the `i % base` will
            never yield a value more than the base.
            */

            //48 [0] - 57 [9] (+48)
            if(/*digit >= 0 && */digit <= 9)
            {
                *(pos++) = static_cast<char>(digit+48);
            }
            //65 [A] - 90 [Z] (+55) or 97 [a] - 122 [z] (+87)
            else if(digit >= 10 && digit <= 35)
            {
                unsigned int offset = (use_caps ? 55 : 87);
                *(pos++) = static_cast<char>(digit+offset);
            }

            //Divide the number by the base to remove the last parsed digit.
            val /= base;
        }

        if(leadZero)
        {
            *(pos++) = '0';
        }

        //Reverse the string.
        char temp[strlen(str)] = {'\0'};
        strcpy(temp, str);
        strcpy(str, strrev(temp));
    }

    void stdutils::itoa(char* str, int val, int base, int len, bool use_caps)
    {
        /*Adapted from comp.lang.c++, Re: Integer to Ustring
        Christian Gollwitzer <auriocus@gmx.de>
        Wed, 17 Jun 2015 09:20:13 +0200

        ...
        Formatting integers is usually done by
        the divide and mod algorithm, which works like this

        if (i<0) { print "-"; i=-i }

        i=12345678
        while i {
           print i % 10
           i = i/10
        }

        Afterwards you reverse the digits.
        */

        /* If no length was provided, get the length of the integer,
         * including negative sign.*/
        len = (len == 0) ? intlen(val, base, true) : len;

        char* pos = str;

        bool neg = false;
        if (val < 0)
        {
            //Make the number positive;
            val *= -1;
            neg = true;
        }

        if (val == 0)
        {
            //Write out a literal 0
            *(pos++) = '0';
        }

        while (val)
        {
            int digit = val % base;

            /*To get the corresponding character, just add 48 for a numeral,
            or 55 for a letter. We don't have to worry about verifying that
            the character is appropriate for the base, as the `i % base` will
            never yield a value more than the base.
            */

            //48 [0] - 57 [9] (+48)
            if(digit >= 0 && digit <= 9)
            {
                *(pos++) = static_cast<char>(digit+48);
            }
            //65 [A] - 90 [Z] (+55) or 97 [a] - 122 [z] (+87)
            else if(digit >= 10 && digit <= 35)
            {
                int offset = (use_caps ? 55 : 87);
                *(pos++) = static_cast<char>(digit+offset);
            }

            //Divide the number by the base to remove the last parsed digit.
            val /= base;
        }

        if(neg)
        {
            //Place the symbol at the start of the string.
            *(pos++) = '-';
        }

        //Reverse the string.
        char temp[strlen(str)] = {'\0'};
        strcpy(temp, str);
        strcpy(str, strrev(temp));
    }

    void stdutils::dtoa(char* str, double val, int precision, int sci)
    {
        //If the value is not a number...
        if (isnan(val))
        {
            //The string is "NaN".
            strcpy(str, "NaN");
        }
        //If the value is infinite.
        else if (isinf(val))
        {
            //The string is "Inf".
            strcpy(str, "Inf");
            //TODO: What about negative infinity?
        }
        //If the value is 0.
        else if (val == 0.0)
        {
            //Just print out 0.
            strcpy(str, "0");
        }
        else
        {
            //A single digit.
            int digit;
            int m1;
            char* c = str;

            //Convert "precision" (actually significand) to precision decimal.
            double p = 1 / pow(10, precision);

            //Determine whether the number is negative.
            bool neg = (val < 0);
            //If negative...
            if (neg)
            {
                //Invert the value.
                val = -val;
                //Start the string with a negative sign.
                *(c++) = '-';
            }
            //That last step was important, because we can't log10 a negative.

            /* Calculate magnitude (distance from highest digit to decimal).
             * We can truncate the decimal, as it isn't import here.
             * Thus, we just use int.*/
            int m = log10(val);

            /* Flag whether we use scientific notation. In auto-mode (sci=1),
             * we'll want to use it when our magnitude is over 14 or
             less than -9. Otherwise, we force its use when (sci=2).*/
            //NOTE: Swapped from int to bool for efficiency.
            bool useExp = (
                ((sci == 1) && (m >= 14 || (neg && m >= 9) || m <= -9)) ||
                (sci == 2)
            );

            //If we are using scientific notation...
            if (useExp)
            {
                //If the magnitude is negative.
                if (m < 0)
                {
                    //Set the initial magnitude to -1.
                    m -= 1;
                    //NOTE: Why are we doing this? What about 0.000024 (m=-4)
                }
                //Convert the value to scientific notation.
                val = val / pow(10.0, m);
                //Store the magnitude for later reference.
                m1 = m;
                //We are now at magnitude 0 after conversion.
                m = 0;
            }

            //If the magnitude is less than 1...
            if (m < 1)
            {
                //Reset the magnitude to 0.
                m = 0;
            }

            //Convert the number.
            /* While the value is greater than our precision and magnitude is
             * not negative.*/
            while (val > p || m >= 0)
            {
                //Set our weight to 10^m.
                double weight = pow(10.0, m);

                //Weight (place value) is greater than 0 and not infinite.
                if (weight > 0 && !isinf(weight))
                {
                    //Digit is floor of value / place value.
                    digit = floor(val / weight);

                    //Remove the number we just parsed out.
                    val -= (digit * weight);

                    //Append the digit to the string.
                    //TODO: Replace this.
                    *(c++) = '0' + digit;
                }
                //If our magnitude is 0 and our value is > 0.
                if (m == 0 && val > 0)
                {
                    //Append a decimal point.
                    *(c++) = '.';
                }

                //Decrement the magnitude.
                m--;
            }
            //If we are using scientific notation (exponent)...
            if (useExp)
            {
                //Append the 'e' symbol.
                *(c++) = 'e';
                //if the exponent is positive
                if (m1 >= 0)
                {
                    //Append the '+' symbol.
                    *(c++) = '+';
                }
                //else if the exponent is negative
                else
                {
                    //Append the '-' symbol.
                    *(c++) = '-';
                    //Invert the exponent.
                    m1 = -m1;
                }
                //Reset our magnitude to 0, so we can reuse it as an iterator.
                m = 0;

                //While the exponent is > 0.
                while (m1 > 0)
                {
                    //Convert and append digits.
                    *(c++) = '0' + m1 % 10;
                    m1 /= 10;
                    //Increment m.
                    m++;
                }

                //Move back in the string by m.
                c -= m;

                //Reverse the string.
                char temp[strlen(c)] = {'\0'};
                strcpy(temp, c);
                strcpy(c, strrev(temp));

                /* We don't use the XOR method because it is generally less
                 * efficient than just swapping with temporary.*/
                /*
                for (int i = 0, j = m-1; i<j; i++, j--)
                {
                    c[i] ^= c[j];
                    c[j] ^= c[i];
                    c[i] ^= c[j];
                }*/
                //Move to the end of the string.
                c += m;
            }
            //Append the null terminator.
            *(c) = '\0';
        }
    }

    std::string stdutils::itos(int val, int base, bool use_caps)
    {
        int len = intlen(val, base, true);
        char cstr[len+1] = {'\0'};
        itoa(cstr, val, base, len, use_caps);
        std::string str = cstr;
        return str;
    }

    std::string stdutils::dtos(double val, int precision, int sci)
    {
        /* Declare a new C-string with the size equal to the estimated
         * maximum number of characters in the float, plus 1 for the null
         * terminator.*/
        char cstr[floatlen(val, precision, sci, true) + 1] = {'\0'};
        //Convert the float to a cstring, and dump into cstr.
        dtoa(cstr, val, precision, sci);
        //Convert the cstring into a string.
        std::string str = cstr;
        //Return the string.
        return str;
    }

    std::string stdutils::ptrtos(uintptr_t val, bool use_caps)
    {
        //TODO: Allow for 32-bit systems as well.
        char cstr[67] = {'\0'};
        ptrtoa(cstr, val, use_caps);
        std::string str = cstr;
        return str;
    }

    void stdutils::memdump(char* str, const void* mem, unsigned int bytes, bool use_caps, char memformat)
    {
        bool bytespacing = memformat & (1 << 0);
        bool wordspacing = memformat & (1 << 1);
        char byte[3] = {'\0'};
        const uint8_t* p = reinterpret_cast<const uint8_t*>(mem);
        for (unsigned int i = 0; i < bytes; i++)
        {
            uitoa(byte, p[i], 16, 2, use_caps, true);
            strcat(str, byte);
            //If we use byte spacing and we're not on the last byte...
            if(bytespacing && i != (bytes-1))
            {
                strcat(str, " ");
            }

            //If we use word spacing and we're between words (and not on last byte).
            if(wordspacing && (i+1)%8 == 0 && i != (bytes-1))
            {
                strcat(str, "|");
                if(bytespacing)
                {
                    strcat(str, " ");
                }
            }
        }
    }

    stdutils::~stdutils()
    {
        //dtor
    }
}

/*
//This is the pointer conversion used by printf("%p", ...)
//https://sourceware.org/git/?p=glibc.git;a=blob;f=stdio-common/vfprintf.c
LABEL (form_pointer):
{
    const void *ptr;
    if (fspec == NULL)
        ptr = va_arg (ap, void *);
    else
        ptr = args_value[fspec->data_arg].pa_pointer;
    if (ptr != NULL)
    {
        // If the pointer is not NULL, write it as a %#x spec.
        base = 16;
        number.word = (unsigned long int) ptr;
        is_negative = 0;
        alt = 1;
        group = 0;
        spec = L_('x');
        goto LABEL (number);
    }
    else
    {
        // Write "(nil)" for a nil pointer.
        string = (CHAR_T *) L_("(nil)");
        // Make sure the full string "(nil)" is printed.
        if (prec < 5)
            prec = 5;
        is_long = 0;        // This is no wide-char string.
        goto LABEL (print_string);
    }
 }

LABEL (number):
{
    if (prec < 0)
     // Supply a default precision if none was given.
        prec = 1;
    else
    {
        // We have to take care for the '0' flag.  If a precision
        // is given it must be ignored.
        pad = L_(' ');
    }

    // If the precision is 0 and the number is 0 nothing has to
    // be written for the number, except for the 'o' format in
    // alternate form.
    if (prec == 0 && number.word == 0)
    {
        string = workend;
        if (base == 8 && alt)
        *--string = L_('0');
    }
    else
    {
        // Put the number in WORK.
        string = _itoa_word (number.word, workend, base,
                             spec == L_('X'));
        if (group && grouping)
            string = group_number (string, workend, grouping,
                                   thousands_sep);

        if (use_outdigits && base == 10)
            string = _i18n_number_rewrite (string, workend, workend);
    }
 }
 */
