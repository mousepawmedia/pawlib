#ifndef STDUTILS_H
#define STDUTILS_H

#include <cstring>
#include <cstdio>

//TODO: Replace with pawlib::string!
#include <string>

namespace pawlib
{
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

            /**Count the number of digits in an integer.
            * http://stackoverflow.com/a/1489873/472647
            * \param the number to count the digits in
            * \param the base, default 10
            * \param whether to count the negative sign as a digit
            * \return the number of digits in the integer*/
            static int intlen(int, int=10, bool=false);

            static char* itoa(int, int=10);
            static std::string itos(int, int=10);

            ~stdutils();
        protected:
        private:
    };
}

#endif // STDUTILS_H
