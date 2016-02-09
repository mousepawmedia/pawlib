/* PawString, version 1.0 [PawLIB]
 *
 * PawString is a multi-sized, Unicode-compatible replacement
 * for std::string. PawString contains all the
 * basic functions found in std::string all while
 * avoiding dynamic allocation whenever possible.
 * To handle Unicode, each PawString is made of PawChars,
 * which are enhanced characters.
 *
 * Last Updated: 6 February 2016
 * Author: Scott Taylor
 */

#ifndef PAWSTRING_HPP
#define PAWSTRING_HPP
#include <unicode/uchar.h>
#include <iostream>
#include <iochannel.hpp>

//const int MAX_SIZE = 8;
namespace pawlib
{
    /* PawChar is a special array of of chars
    It's purpose is to allow for Unicode characters in Pawstring */
    class PawChar
    {
        public:
            /**Default constructor
             * \return Returns a new PawChar with only one character: '\0' */
            PawChar();

            /**Retrieve char from PawChar
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the PawChar
             * \return returns the char located at pos */
            char operator[](int pos) const;

            /**Retrieve char from PawChar
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the PawChar
             * \return returns the char reference located at pos */
            char& operator[](int pos);

            // Overload all necessary operators

            /**Construct new PawChar
             * \param the char to initialize PawChar with
             * \return a new PawChar containing a char and '\0' */
            PawChar operator=(char newChar);

             /**Construct new PawChar from Unicode character
             * \param the 2-4 byte Unicode character to put in PawChar
             * \return a new PawChar containing a Unicode character and '\0' */
            PawChar operator=(char* newChar);

            /**Copy from another PawChar
             * \param the PawChar to copy from
             * \return a new PawChar copied from newChar */
            PawChar operator=(PawChar newChar);

            /**Operator to output a PawChar
             * \param the ostream to output on
             * \param the PawChar to output
             * \return outputs the PawChar as a single character */
            friend std::ostream& operator<<(std::ostream& os, const PawChar& pchr);

            /**Compares PawChar to another PawChar
             * \param the primary PawChar
             * \param the PawChar being compared to
             * \return true if the PawChars are exactly equal. false otherwise */
            friend bool operator==(const PawChar& pchr, const PawChar &newChar);

            /**Compares PawChar to a char*
             * Used for Unicode comparisons
             * \param the primary PawChar
             * \param the char* to be compared to (needs to be parsed)
             * \return true if the two are exactly equal. false otherwise */
            friend bool operator==(const PawChar& pchr, char* newChar);

            /**Compares PawChar to a single char
             * \param the primary PawChar
             * \param the char to be compared to
             * \return true if the two are exactly equal. false otherwise */
            friend bool operator==(const PawChar& pchr, char newChar);

            /**Determines if a PawChar is less than another
             * \param the primary PawChar
             * \param the PawChar being compared to
             * \return true if pchr's value is less than newChar */
            friend bool operator<(const PawChar& pchr, const PawChar &newChar);
        private:
            char miniChar[5];
    };

    /* The purpose of PawString is to provide the functionality of std::string
     * but without dynamic allocation and with increased support for Unicode
     * Characters. As a templated class, the possible types of PawString are:
     * PawString<8>, PawString<16>, PawString<32>, PawString<64>, PawString<128>,
     * and any other future forward declarations. The difference between each of these
     * PawString types is the MAX_SIZE of each. PawString<8> can hold a maximum of 8 PawChars
     * while PawString<32> can hold up to 32 PawChars. Each PawString
     * class contains a master array that is an array of PawChars. The size of
     * the master array is determined by the MAX_SIZE for the class.
     * When expanding the possible PawString sizes, one must add the forward declaration
     * to the end of PawString.cpp and the corresponding declarations/implementation for
     * the copy constructor, equals(), append(), insert(), swap(), and operator=().*/
    template <const int pawSize>
    class PawString
    {
        public:

            /**Default constructor
             * \return an empty PawString with size 0 */
            explicit PawString();

            /**Create a PawString from std::string
             * \param the string to be converted to PawString
             * \return a PawString representation of str.
             *         All Unicode will be parsed appropriately. */
            PawString(std::string str);

            /**Create a PawString from const char*
             * Note: Double quotes default to const char*
             * \param the const char* to be converted to PawString
             * \return a PawString representation of str.
             *         All Unicode will be parsed appropriately. */
            PawString(const char* str);

            /**Create a PawString from a single char
             * \param the char to be converted to PawString
             * \return a PawString representation of ch. */
            PawString(char ch);

            /**Create a PawString from a PawChar
             * \param the PawChar to be converted to PawString
             * \return a PawString representation of ch */
            PawString(PawChar ch);

            /* Inorder to interact with other PawString types, a function must
             * be made for every possible PawString. Trying to use templates to
             * alleviate this problem only resulted in bugs. This method, while
             * being larger code-wise, is much safer. */

            /**Copy Constructor for PawString<8>
             * \param the the PawString<8> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<8>& pstr);

            /**Copy Constructor for PawString<16>
             * \param the the PawString<16> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<16>& pstr);

            /**Copy Constructor for PawString<32>
             * \param the the PawString<32> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<32>& pstr);

            /**Copy Constructor for PawString<64>
             * \param the the PawString<64> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<64>& pstr);

            /**Copy Constructor for PawString<128>
             * \param the the PawString<128> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<128>& pstr);

            /**Copy Constructor for PawString<256>
             * \param the the PawString<256> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<256>& pstr);

            /**Copy Constructor for PawString<512>
             * \param the the PawString<512> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<512>& pstr);

            /**Copy Constructor for PawString<1024>
             * \param the the PawString<1024> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<1024>& pstr);

            /**Copy Constructor for PawString<2048>
             * \param the the PawString<2048> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<2048>& pstr);

            /**Copy Constructor for PawString<4096>
             * \param the the PawString<4096> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString(const PawString<4096>& pstr);

            // String functions

            /**Determine number of PawChars in a PawString
             * \return an int that represents the number of PawChars in the PawString */
            int size() const;

            /**Returns the PawChar found at a specific index
             * \param an int to represent the desired index
             * \return the PawChar found at pos */
            PawChar at(int pos);

            /**Tests for equality with another PawString
             * \param a PawString<8> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<8>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<16> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<16>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<32> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<32>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<64> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<64>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<128> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<128>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<256> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<256>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<512> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<512>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<1024> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<1024>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<2048> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<2048>& pstr) const;

            /**Tests for equality with another PawString
             * \param a PawString<4096> to be tested for equality
             * \return true if the master array is equivalent to the PawString. */
            bool equals(const PawString<4096>& pstr) const;

            /**Tests for equality with a const char*
             * \param a const char* to be tested for equality
             * \return true if the master array is equivalent to the const char*. */
            bool equals(const char* pstr)const;

            /**Tests for equality with a std::string
             * \param a std::string to be tested for equality
             * \return true if the master array is equivalent to the std::string. */
            bool equals(std::string pstr) const;

            /**Adds a PawString<8> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<8>& pstr);

            /**Adds a PawString<16> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<16>& pstr);

            /**Adds a PawString<32> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<32>& pstr);

            /**Adds a PawString<64> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<64>& pstr);

            /**Adds a PawString<128> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<128>& pstr);

            /**Adds a PawString<256> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<256>& pstr);

            /**Adds a PawString<512> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<512>& pstr);

            /**Adds a PawString<1024> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<1024>& pstr);

            /**Adds a PawString<2048> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<2048>& pstr);

            /**Adds a PawString<4096> onto the end of the master array
             * \param the PawString to be added to the end of the master array */
            void append(const PawString<4096>& pstr);

            /**Adds a const char* onto the end of the master array
             * \param the const char* to be added to the end of the master array */
            void append(const char* pstr);

            /**Adds a std::string to the end of the master array
             * \param the std::string to be added to the end of the master array */
            void append(std::string pstr);

            /**Adds a char onto the end of the master array
             * \param the char to be added to the end of the master array */
            void append(char pchar);

            /**Adds a PawChar onto the end of the master array
             * \param the PawChar to be added to the end of the master array */
            void append(PawChar pchar);

            /**Inserts a PawString<8> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<8> to be inserted */
            void insert(int pos, const PawString<8>& pstr);

            /**Inserts a PawString<16> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<16> to be inserted */
            void insert(int pos, const PawString<16>& pstr);

            /**Inserts a PawString<32> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<32> to be inserted */
            void insert(int pos, const PawString<32>& pstr);

            /**Inserts a PawString<64> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<64> to be inserted */
            void insert(int pos, const PawString<64>& pstr);

            /**Inserts a PawString<128> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<128> to be inserted */
            void insert(int pos, const PawString<128>& pstr);

            /**Inserts a PawString<256> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<256> to be inserted */
            void insert(int pos, const PawString<256>& pstr);

            /**Inserts a PawString<512> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<512> to be inserted */
            void insert(int pos, const PawString<512>& pstr);

            /**Inserts a PawString<1024> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<1024> to be inserted */
            void insert(int pos, const PawString<1024>& pstr);

            /**Inserts a PawString<2048> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<2048> to be inserted */
            void insert(int pos, const PawString<2048>& pstr);

            /**Inserts a PawString<4096> into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawString<4096> to be inserted */
            void insert(int pos, const PawString<4096>& pstr);

            /**Inserts a char* into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the const char* to be inserted */
            void insert(int pos, const char* pstr);

            /**Inserts a std::string into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the std::string to be inserted */
            void insert(int pos, std::string pstr);

            /**Inserts a char into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the char to be inserted */
            void insert(int pos, char pchar);

            /**Inserts a PawChar into the master array at a specific position
             * \param an int that indicates the position to insert at
             * \param the PawChar to be inserted */
            void insert(int pos, PawChar pchar);

            /**Creates a substring from the master array
             * \param an int that corresponds to the start of the substring
             * \param an int for the size of the substring. Defaults to -1 to
             * indicate that the substring goes to the end of the master array
             * \return a PawString that is a substring of the master array*/
            PawString substr(int pos, int sublen = -1);

            /**Appends a single char to the end of a PawString
             * Same as append(char)
             * \param the char to be appended */
             void push_back(char ch);

             /**Erases the last PawChar of the PawString and reduces len */
             void pop_back();

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<8> to be swapped with */
             void swap(PawString<8>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<16> to be swapped with */
             void swap(PawString<16>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<32> to be swapped with */
             void swap(PawString<32>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<64> to be swapped with */
             void swap(PawString<64>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<128> to be swapped with */
             void swap(PawString<128>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<256> to be swapped with */
             void swap(PawString<256>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<512> to be swapped with */
             void swap(PawString<512>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<1024> to be swapped with */
             void swap(PawString<1024>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<2048> to be swapped with */
             void swap(PawString<2048>& str);

             /**Exchanges the master array for the contents of str while
              * the contents of str become that of the master array
              * \param the reference to the PawString<4096> to be swapped with */
             void swap(PawString<4096>& str);

             /**Returns total number of bytes used
              * \return an int that indicates how many bytes the PawString is */
             int length();

             /**Returns the largest a specific PawString can be
              * \return an int that indicates the max_size for a specific class */
             int max_size();

             /**Determines if a PawString is empty or not
              * \return true if len == 0, false otherwise */
             bool empty() const;

             /**Erases contents of the PawString. Len becomes 0 */
             void clear();


            /**Retrieve PawChar from PawString
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the PawString
             * \return returns the PawChar located at pos */
            PawChar operator [](int pos) const;

             /**Retrieve PawChar from PawString
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the PawString
             * \return returns the PawChar located at pos */
            PawChar& operator [](int pos);

            /**Copy Constructor for assignment operator PawString<8>
             * \param the PawString<8> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<8> newPstr);

            /**Copy Constructor for assignment operator PawString<16>
             * \param the PawString<16> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<16> newPstr);

            /**Copy Constructor for assignment operator PawString<32>
             * \param the PawString<32> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<32> newPstr);

            /**Copy Constructor for assignment operator PawString<64>
             * \param the PawString<64> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<64> newPstr);

            /**Copy Constructor for assignment operator PawString<64>
             * \param the PawString<128> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<128> newPstr);

            /**Copy Constructor for assignment operator PawString<64>
             * \param the PawString<256> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<256> newPstr);

            /**Copy Constructor for assignment operator PawString<64>
             * \param the PawString<512> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<512> newPstr);

            /**Copy Constructor for assignment operator PawString<64>
             * \param the PawString<1024> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<1024> newPstr);

            /**Copy Constructor for assignment operator PawString<64>
             * \param the PawString<2048> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<2048> newPstr);

            /**Copy Constructor for assignment operator PawString<64>
             * \param the PawString<4096> to be copied
             * \return a new PawString that is a deep copy of pstr */
            PawString operator=(PawString<4096> newPstr);

            /**Create a PawString from std::string with assignment operator
             * \param the std::string to be converted to PawString
             * \return a PawString representation of str.
             *         All Unicode will be parsed appropriately. */
            PawString operator=(std::string str);

            /**Create a PawString from const char* with assignment operator
             * Note: Double quotes default to const char*
             * \param the const char* to be converted to PawString
             * \return a PawString representation of str.
             *         All Unicode will be parsed appropriately. */
            PawString operator=(const char* str);

            /**Create a PawString from a single char with assignment operator
             * \param the char to be converted to PawString
             * \return a PawString representation of ch. */
            PawString operator=(char ch);

            /**Create a PawString from a PawChar with assignment operator
             * \param the PawChar to be converted to PawString
             * \return a PawString representation of ch. */
            PawString operator=(PawChar ch);

            // Comparison operators

            // Because these friend functions are defined in the header, templates
            // can be used to account for different PawString sizes getting passed
            // as arguments. The left hand side will be the PawString type of
            // the current instance.
            /**Tests for equality with another PawString of varying sizes
             * \param the left-hand PawString operand
             * \param a PawString (of different sizes) to be tested for equality
             * \return true if both PawStrings are exactly equivalent. */
            template<const int pawSize2>
            friend bool operator==(const PawString& pstr1, const PawString<pawSize2>& pstr2)
            {
                // Goes to PawString version
                return pstr1.equals(pstr2);
            };

            /**Tests for equality with another PawString
             * \param the left-hand PawString operand
             * \param a const char* to be tested for equality
             * \return true if the PawString is equivalent to the char* */
            friend bool operator==(const PawString& pstr1, const char* pstr2)
            {
                // Goes to char* version
                return pstr1.equals(pstr2);
            };

            /**Tests for equality with another PawString
             * \param the left-hand PawString operand
             * \param a std::string to be tested for equality
             * \return true if the PawString is equivalent to the std::string */
            friend bool operator==(const PawString& pstr1, std::string pstr2)
            {
                // Goes to string version
                return pstr1.equals(pstr2);
            };


            /**The less-than operator
             * \param the left-hand PawString operand
             * \param the right-hand PawString operand
             * \return true if the left-hand operand is less than the right-hand */
            template<const int pawSize2>
            friend bool operator<(const PawString& pstr1, const PawString<pawSize2>& pstr2)
            {
                // Only loop as far as the smallest string
                int small_len = (pstr1.size() < pstr2.size())? pstr1.size(): pstr2.size();
                for(int i = 0; i< small_len; i++)
                {
                    if(pstr1[i] < pstr2[i])
                    return true;
                }

                // If they made it through the loop and pstr1 is smaller
                // then return true
                if((small_len == pstr1.size()) && (small_len != pstr2.size()))
                    return true;
                return false;
            };

            /**The less-than operator
             * \param the left-hand PawString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is less than the right-hand */
            friend bool operator<(const PawString& pstr1, const char* pstr2)
            {
                // Call the PawString version
                PawString<pawSize> convert = pstr2;
                return (pstr1 < convert);
            };

            /**The less-than operator
             * \param the left-hand PawString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is less than the right-hand */
            friend bool operator<(const PawString& pstr1, std::string pstr2)
            {
                // Call the PawString version
                PawString<pawSize> convert = pstr2;
                return (pstr1 < convert);
            };

            /**The less-than-or-equal operator
             * \param the left-hand PawString operand
             * \param the right-hand PawString operand
             * \return true if the left-hand operand is less than or equal
             *         the right-hand */
            template<const int pawSize2>
            friend bool operator<=(const PawString& pstr1, const PawString<pawSize2>& pstr2)
            {
                // Cannot call ! greater-than because an infinite loop would occur
                return ((pstr1 < pstr2)|| (pstr1 == pstr2));
            };

             /**The less-than-or-equal operator
             * \param the left-hand PawString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is less than or equal
             *         the right-hand */
            friend bool operator<=(const PawString& pstr1, const char* pstr2)
            {
                // Call the PawString version
                PawString<pawSize> convert = pstr2;
                return (pstr1 <= convert);
            };

             /**The less-than-or-equal operator
             * \param the left-hand PawString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is less than or equal
             *         the right-hand */
            friend bool operator<=(const PawString& pstr1, std::string pstr2)
            {
                PawString<pawSize> convert = pstr2;
                return (pstr1 <= convert);
            };

             /**The greater-than operator
             * \param the left-hand PawString operand
             * \param the right-hand PawString operand
             * \return true if the left-hand operand is greater than the right-hand */
            template<const int pawSize2>
            friend bool operator>(const PawString& pstr1, const PawString<pawSize2>& pstr2)
            {
                // Call previously made functions
                return(!(pstr1 <= pstr2));
            };

            /**The greater-than operator
             * \param the left-hand PawString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is greater than the right-hand */
            friend bool operator>(const PawString& pstr1, const char* pstr2)
            {
                PawString<pawSize> convert = pstr2;
                return(pstr1 > convert);
            };

            /**The greater-than operator
             * \param the left-hand PawString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is greater than the right-hand */
            friend bool operator>(const PawString& pstr1, std::string pstr2)
            {
                PawString<pawSize> convert = pstr2;
                return(pstr1 > convert);
            };

            /**The greater-than-or-equal operator
             * \param the left-hand PawString operand
             * \param the right-hand PawString operand
             * \return true if the left-hand operand is greater than or equal
             *         to the right-hand */
            template<const int pawSize2>
            friend bool operator>=(const PawString& pstr1, const PawString<pawSize2>& pstr2)
            {
                // Use previously made functions
                return(!(pstr1 < pstr2));
            };

            /**The greater-than-or-equal operator
             * \param the left-hand PawString operand
             * \param the right-hand const char* operand
             * \return true if the left-hand operand is greater than or equal
             *         to the right-hand */
            friend bool operator>=(const PawString& pstr1, const char* pstr2)
            {
                PawString<pawSize> convert = pstr2;
                return(pstr1 >= convert);
            };

            /**The greater-than-or-equal operator
             * \param the left-hand PawString operand
             * \param the right-hand std::string operand
             * \return true if the left-hand operand is greater than or equal
             *         to the right-hand */
            friend bool operator>=(const PawString& pstr1, std::string pstr2)
            {
                PawString<pawSize> convert = pstr2;
                return(pstr1 >= convert);
            };

            /**Appends a PawString onto the end of another PawString
             * \param the left-hand PawString operand to be appended to
             * \param the PawString to be appended onto the left-hand operand*/
            template<const int pawSize2>
            friend void operator+=(PawString& pstr1, const PawString<pawSize2>& pstr2)
            {
                pstr1.append(pstr2);
            };

            /**Appends a const char* onto the end of another PawString
             * \param the left-hand PawString operand to be appended to
             * \param the const char* to be appended onto the left-hand operand*/
            friend void operator+=(PawString& pstr1, const char* pstr2)
            {
                pstr1.append(pstr2);
            };

            /**Appends a std::string onto the end of another PawString
             * \param the left-hand PawString operand to be appended to
             * \param the std::string to be appended onto the left-hand operand*/
            friend void operator+=(PawString& pstr1, std::string pstr2)
            {
                pstr1.append(pstr2);
            };

            /**Appends a char onto the end of another PawString
             * \param the left-hand PawString operand to be appended to
             * \param the char to be appended onto the left-hand operand*/
            friend void operator+=(PawString& pstr1, char pchar)
            {
                pstr1.append(pchar);
            };

            /**Appends a PawChar onto the end of another PawString
             * \param the left-hand PawString operand to be appended to
             * \param the PawChar to be appended onto the left-hand operand*/
            friend void operator+=(PawString& pstr1, PawChar pchar)
            {
                pstr1.append(pchar);
            };

            /*******************************************************************
            * CURRENT WORKING SOLUTION TO OPERATOR+ ISSUE
            ********************************************************************/
            // Define Macro to associate code to each operator+ function
            #define ADDOP_FUNCT \
            { \
                /* We don't want to alter the left-hand side, so we create a copy*/\
                PawString cpyStr = lhs;\
                /* Append the right-hand side */\
                cpyStr.append(rhs);\
                return cpyStr;\
            }

            /**Appends the right hand operator onto the left hand operator
             * What makes this different from += is that + may be used
             * multiple times per line of code
             * The rhs param can be either a PawString, char, const char*,
             * PawChar, or std::string.
             * \param the left-hand PawString to be added to
             * \param the right-hand argument to be appended
             * \return the PawString result of joining the lhs and rhs*/
            template <class R>
            friend PawString operator+(const PawString& lhs, R rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a PawString to a char*
             * \param the left-hand char* to be added to
             * \param the right-hand PawString to be appended
             * \return the PawString result of joining the lhs and rhs*/
            friend PawString operator+(const char* lhs,  PawString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a PawString to a char
             * \param the left-hand char to be added to
             * \param the right-hand PawString to be appended
             * \return the PawString result of joining the lhs and rhs*/
            friend PawString operator+(char lhs,  PawString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a PawString to a std::string
             * \param the left-hand std::string to be added to
             * \param the right-hand PawString to be appended
             * \return the PawString result of joining the lhs and rhs*/
            friend PawString operator+(std::string lhs,  PawString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Appends a PawString to a PawChar
             * \param the left-hand PawChar to be added to
             * \param the right-hand PawString to be appended
             * \return the PawString result of joining the lhs and rhs*/
            friend PawString operator+(PawChar lhs, PawString rhs)
            {
                ADDOP_FUNCT;
            };

            /**Operator to output a PawString
             * \param the ostream to output on
             * \param the PawString to output
             * \return outputs the PawString as a cohesive string */
            friend std::ostream& operator<<(std::ostream& os, const PawString& pstr)
            {
                // Loop through and output each PawChar. Since PawChar has its
                // own operator<< overload everything shall be displayed neatly
                for(int i = 0; i < pstr.size(); i++)
                    os << pstr.master[i];
                return os;
            };

            /**Inputs a PawString from the user so long as there are no spaces
             * \param the istream to receive input from
             * \param the PawString to be input
             * \return an istream containing the inputted PawString */
            friend std::istream& operator>>(std::istream& in, PawString& pstr)
            {
                std::string temp;
                in >> temp;
                pstr = temp;
                return in;
            };

        private:
             /**Parses char* into PawString based on size
             * Used primarily for Unicode Characters within PawString(const char*)
             * \param the const char* to be parsed
             * \param an int to represent the index to parse the char* at
             * \param an int to represent the number of bytes in the char* */
            void parseChar(const char* str, int index, int bytes);


            int len;
            int MAX_SIZE = pawSize ;
            PawChar master[pawSize];
    };

    //#include "../src/PawString.cpp"

}
#endif // PAWSTRING_HPP
