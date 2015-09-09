#ifndef STDUTILS_H
#define STDUTILS_H

#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdint>

//TODO: Replace with pawlib::string!
#include <string>

namespace pawlib
{
    ////const double PRECISION = 0.00000000000001;
    ////const int MAX_NUMBER_STRING_SIZE = 32;

    class stdutils
    {
        public:
            stdutils();

            /** Reverse a C-string. Algorithm from
            * http://stackoverflow.com/a/784567/472647
            * \param the C-string to reverse.
            * \param the reversed C-string
            */
            static char* strrev(char*);
            //TODO: Move this to pawlib::string!

            /**Count the number of digits/characters in an integer. Does not
             * count the null terminator.
             * http://stackoverflow.com/a/1489873/472647
             * \param the number to count the digits in
             * \param the base, default 10
             * \param whether to count the symbols
             * \return the number of digits in the integer*/
            static int intlen(int, int=10, bool=true);

            /**Count the number of digits/characters in an unsigned integer.
             * Does not count the null terminator.
             * http://stackoverflow.com/a/1489873/472647
             * \param the number to count the digits in
             * \param the base, default 10
             * \return the number of digits in the integer*/
            static int uintlen(unsigned int, int=10);

            /**Count the maximum (safest) estimated number of digits/characters
             * in a float/double. Does not count null terminator. WARNING: This
             * is designed to strategically overcount, to prevent fatal array size
             * errors. This is necessary, since floats are unpredictable by
             * nature.
             * http://stackoverflow.com/a/1489873/472647
             * \param the number to count the characters in
             * \param the precision (default 14)
             * \param whether to count the symbols
             * \return the number of digits in the float*/
            static int floatlen(double, int=14, int=1, bool=true);

            /**Convert an integer to a C-string.
             * \param the C-string to write to
             * \param the integer to convert
             * \param the base to convert in, default 10.
             * \param the length of the C-string, not counting the null
             * terminator. If 0 or omitted, this will be automatically
             * calculated.
             * \param whether to use capital letters for base > 10*/
            static void itoa(char*, int, int=10, int=0, bool=false);

            /**Convert an unsigned integer to a C-string.
             * \param the C-string to write to
             * \param the unsigned integer to convert
             * \param the base to convert in, default 10.
             * \param the length of the C-string, not counting the null
             * terminator. If 0 or omitted, this will be automatically
             * calculated.
             * \param whether to use capital letters for base > 10
             * \param whether this is interpreting a byte (use leading 0)*/
            static void uitoa(char*, unsigned int, int=10, int=0, bool=false, bool=false);

            /**Convert a double to a C-string.
             * \param the C-string to write to
             * \param the double to convert
             * \param the precision, as the number of significands (an integer)
             * \param whether to use scientific notation. 0=none, 1=automatic,
             * 2=force scientific notation.*/
            static void dtoa(char*, double, int=14, int=1);

            /**Convert an unsigned pointer integer to a Cstring.
             * Does not presently export the flag value, just the
             * memory address.
             * \param the C-string to write to
             * \param the pointer integer to convert
             * \param whether to use capital letters for base > 10*/
            static void ptrtoa(char*, uintptr_t, bool=false);

            /**Convert an int to a std::string.
             * \param the integer to convert
             * \param the base to convert
             * \param whether to use capital letters for base > 10
             * \return the string representing the integer.*/
            static std::string itos(int, int=10, bool=false);

            /**Convert a double to a std::string.
             * \param the integer to convert
             * \param the base to convert
             * \return the string representing the integer.*/
            static std::string dtos(double, int=14, int=1);

            /**Convert an unsigned pointer integer to a std::string.
             * \param the pointer integer to convert
             * \param whether to use capital letters for base > 10
             * \return the string representing the pointer.*/
            //static std::string ptrtos(uintptr_t);
            static std::string ptrtos(uintptr_t, bool=false);

            static void memdump(char*, const void*, unsigned int, bool=false, char=0);

            ~stdutils();
        protected:
        private:
    };
}

#endif // STDUTILS_H
