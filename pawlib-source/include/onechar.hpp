/** OneChar [PawLIB]
  * Version: 0.3
  *
  * OneChar is a base class for the characters that make up
  * OneString and QuickString. OneChar is an abstract class. The two types of
  * OneChars are UniChar and AscChar. UniChar is an array of characters
  * used to represent Unicode characters. An AscChar is a standard ASCII
  * character with the standard functionality needed for OneString.
  *
  * Author(s): Scott Taylor
  */

/* LICENSE
 * Copyright (c) 2016 MousePaw Games.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef ONECHAR_HPP
#define ONECHAR_HPP
#include <iostream>
#include <iochannel.hpp>

// Constants for ASCII and Unicode
const bool ASCII = 0;
const bool UNICODE = 1;

namespace pawlib
{
    /* OneChar is the base class for UniChar and AscChar. It is meant to
    provide some basic functions and require others to be defined in the
    derived classes */
    class OneChar
    {
        public:
            /** Default constructor
             * \return a OneChar initialized as an ASCII character */
            explicit OneChar()
            {
				// Set to ascii by default
				charId = ASCII;
			};

			/** Mode constructor
			 * \param a bool to indicate whether the OneChar should be ASCII or Unicode
			 * \return */
			explicit OneChar(bool mode)
			{
				// Set the mode appropriately
				charId = mode;
			};

			/** Get the type of the OneChar
			 * \return a bool representing either ASCII or Unicode*/
			bool getId() const
			{
			    // Return the ID
			    return charId;
			}


			// Declare functions that must be defined in derived classes

			/**Retrieve char from OneChar
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the OneChar
             * \return returns the char located at pos */
			virtual char operator[](int pos) const = 0;

            /**Retrieve char from OneChar
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the OneChar
             * \return returns the reference of the char located at pos */
            virtual char& operator[](int pos) = 0;

            /** Assignment operator for char
             * \param the char to be initialized from
             * \return an initialized OneChar, either AscChar or UniChar*/
            virtual OneChar& operator=(char newChar) = 0;

            /** Assignment operator for const char*
             * \param the const char* to be initialized from
             * \return an initialized OneChar, either AscChar or UniChar*/
            virtual OneChar& operator=(const char* newChar) = 0;

            /** Assignment operator for OneChar
             * \param the base class OneChar to be initialized from
             * \return an initialized OneChar, either AscChar or UniChar*/
            virtual OneChar& operator=(const OneChar& newChar) = 0;

            /** Equals operator for OneChar
             * \param the base class OneChar to be compared to
             * \return true if the param is equal to the current OneChar */
            virtual bool operator==(const OneChar& newChar) = 0;

            /** Equals operator for char
             * \param the char to be compared to
             * \return true if the param is equal to the current OneChar */
            virtual bool operator==(char newChar) = 0;

            /** Helper function for operator<<
             * \param std::ostream to put output on */
            virtual void print( std::ostream& os) const = 0;

            /** Helper function for operator<
             * \param the OneChar to be compared to
             * \return true if the OneChar is equal to the current class */
            virtual bool lessOneChar(const OneChar& compChar) = 0;

            // Other functions

             /**Determines if a OneChar is less than another
             * \param the OneChar being compared to.
             * \return true if ochr's value is less than newChar */
            bool operator<(const OneChar& compChar)
            {
                return lessOneChar(compChar);
            }


            /** Output operator
             * \param std::ostream to display output on
             * \param the OneChar to be output (either AscChar or UniChar)
             * \return the std::ostream to output */
            friend std::ostream& operator<<( std::ostream& os, const OneChar& ostr )
            {
				ostr.print( os );
				return os;
			};


         private:

			bool charId;   		// Keeps track of character type
    };

    /* OneChar is a special array of of chars
    It's purpose is to allow for Unicode characters in OneString */
    class UniChar: public OneChar
    {
		public:
			// Initialize the OneChar
			explicit UniChar():OneChar(UNICODE){miniChar[0] = '\0';};


            /**Create UniChar from const char*
             * \param the const char* to initialize the UniChar */
             // cppcheck-suppress noExplicitConstructor
			UniChar(const char* newChar);

            /**Retrieve char from UniChar
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the UniChar
             * \return returns the char located at pos */
            char operator[](int pos) const;

            /**Retrieve char from UniChar
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the UniChar
             * \return returns the char reference located at pos */
            char& operator[](int pos);

            /**Construct new UniChar
             * \param the char to initialize UniChar with
             * \return a new UniChar containing a char and '\0' */
            OneChar& operator=(char newChar);

             /**Construct new UniChar from Unicode character
             * \param the 2-4 byte Unicode character to put in UniChar
             * \return a new UniChar containing a Unicode character and '\0' */
            OneChar& operator=(const char* newChar);

            /**Copy from another UniChar
             * \param the UniChar to copy from
             * \return a new UniChar copied from newChar */
            OneChar& operator=(const OneChar& newChar);

            /**Operator to output a UniChar
             * \param the ostream to output on */
            virtual void print( std::ostream& os) const;

             /**Determines if a OneChar is less than another
             * \param the OneChar being compared to.
             * \return true if ochr's value is less than newChar */
            bool lessOneChar(const OneChar& compChar);

            /**Compares UniChar to a OneChar
             * \param the OneChar being compared to
             * \return true if the OneChars are exactly equal. false otherwise */
            bool operator==(const OneChar& newChar);

            /**Compares UniChar to a single char
             * \param the char to be compared to
             * \return true if the two are exactly equal. false otherwise */
            bool operator==(char newChar);

            /**Compares UniChar to a char*
             * Used for Unicode comparisons
             * \param the primary UniChar
             * \param the char* to be compared to (needs to be parsed)
             * \return true if the two are exactly equal. false otherwise */
            friend bool operator==(const UniChar& ochr, char* newChar);

        private:
            char miniChar[5];
    };

    class AscChar: public OneChar
    {
        public:
            // Initialize the OneChar
			AscChar():OneChar(ASCII){masterChar = '\0';};

			/**Retrieve char from UniChar
             * This takes care of the "getting" part of the index operator
             * \param the desired position within in the UniChar
             * \return returns the char located at pos */
            char operator[](int pos) const;

            /**Retrieve char from UniChar
             * This takes care of the "setting" part of the index operator
             * \param the desired position within in the UniChar
             * \return returns the char reference located at pos */
            char& operator[](int pos);

            /**Construct new AscChar
             * \param the char to initialize AscChar with
             * \return a new AscChar containing a char */
            OneChar& operator=(char newChar);

             /**Construct new AscChar from Unicode character
             * \param the 2-4 byte Unicode character to put in AscChar
             * \return a new AscChar containing a Unicode character */
            OneChar& operator=(const char* newChar);

            /**Copy from another AscChar
             * \param the AscChar to copy from
             * \return a new AscChar copied from newChar */
            OneChar& operator=(const OneChar& newChar);

            /**Operator to output a AscChar
             * \param the ostream to output on */
            virtual void print( std::ostream& os) const;

            /**Determines if a OneChar is less than another
             * \param the OneChar being compared to.
             * \return true if ochr's value is less than newChar */
            bool lessOneChar(const OneChar& compChar);

            /**Compares AscChar to another OneChar
             * \param the OneChar being compared to
             * \return true if the OneChars are exactly equal. false otherwise */
            bool operator==(const OneChar& newChar);

            /**Compares AscChar to a char
             * \param the char to be compared to
             * \return true if the AscChar and char are the same */
            bool operator==(char newChar);

            /**Compares AscChar to a char*
             * Used for Unicode comparisons
             * \param the primary AscChar
             * \param the char* to be compared to (needs to be parsed)
             * \return true if the two are exactly equal. false otherwise */
            friend bool operator==(const AscChar& ochr, char* newChar);

            /**Compares AscChar to a single char
             * \param the primary AscChar
             * \param the char to be compared to
             * \return true if the two are exactly equal. false otherwise */
            friend bool operator==(const AscChar& ochr, char newChar);

	    private:
			char masterChar;
    };
}
#endif // ONECHAR_HPP
