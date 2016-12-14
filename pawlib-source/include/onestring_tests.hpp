/** Tests for OneString[PawLIB]
  * Version: 1.0
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

#ifndef PAWSTRING_TESTS_HPP
#define PAWSTRING_TESTS_HPP

#include <string>

#include <goldilocks.hpp>
#include <onestring.hpp>

namespace pawlib
{
    class TestString: public Test
    {
        public:
            enum TestType
            {
                // The strings are equal with no unicode chars
                SAME_NO_UNICODE,

                // The strings are equal with some unicode
                SAME_SOME_UNICODE,

                // The strings are equal and have only unicdoe chars
                SAME_ALL_UNICODE,

                // The strings are not equal, which can be determined by the first char
                NSAME_FIRST_CHAR,

                // The strings are equal until the middle character.
                NSAME_MIDDLE_CHAR,

                // The strings are equal except for the very last character
                NSAME_LAST_CHAR
            };

            explicit TestString(TestType type):tType(type)
            {
                switch(tType)
                {
                    case SAME_NO_UNICODE:
                    {
                        title = "QuickString: Compare, Same No Unicode";
                        docs = "Compares two identical strings containing no Unicode.";
                        break;
                    }
                    case SAME_SOME_UNICODE:
                    {
                        title = "QuickString: Compare, Same Some Unicode";
                        docs = "Compares two identical strings containing some Unicode.";
                        break;
                    }
                    case SAME_ALL_UNICODE:
                    {
                        title = "QuickString: Compare, Same All Unicode";
                        docs = "Compares two identical strings containing all Unicode.";
                        break;
                    }
                    case NSAME_FIRST_CHAR:
                    {
                        title = "QuickString: Compare, Diff First";
                        docs = "Compares two strings with the first character different.";
                        break;
                    }
                    case NSAME_MIDDLE_CHAR:
                    {
                        title = "QuickString: Compare, Diff Middle";
                        docs = "Compares two strings with the middle character different.";
                        break;
                    }
                    case NSAME_LAST_CHAR:
                    {
                        title = "QuickString: Compare, Diff Last";
                        docs = "Compares two strings with the last character different.";
                        break;
                    }
                }
            }

            virtual testdoc_t get_title() = 0;

            testdoc_t get_docs()
            {
               return docs;
            }

            bool pre()
            {
                switch(tType)
                {
                    case SAME_NO_UNICODE:
                    {
                        mainStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                         mainPStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                        compStr = mainStr;
                        compPStr = mainPStr;
                        break;
                    }

                    case SAME_SOME_UNICODE:
                    {
                        mainStr = "♬ We're going down, down in an earlier round. ♬"
                            "我A名B是C科D我E蝙F我G名H是I科J我K蝙L我M名N我O蝙P我Q蝙R我S名T我U蝙VWXYZ"
                            "This is a normal line containing no unicode. Everything is alphanumeric."
                            "ΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮ"
                            "This next line however contains some amounts of unicode. Not too much."
                            "A B C D E F G H I J K L M N O P Q R S ᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒ"
                            "However, these next lines will be many integrals and subsets, with notation."
                            "Calculate the integrals: ∫f(x) ∫f(gx) ∫ x ∫∫ f(x + 1) ∫s dx ∫ 3!"
                            "A ⊆ B C ⊆ B and C ⊆ AB ⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆"
                            "Now let's go for quite awhile without any unicode, in order to be sparing."
                            "⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷"
                            "Ooops I lied. My bad. Now I shall recite the alphabet so that we only have letters."
                            "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z now I know my ABCs"
                            "¶ When editing documents, paragraphs are usually marked with the ¶ symbol. ¶"
                            "☠a☠b☠c☠d☠e☠f☠g☠h☠i☠j☠k☠l☠m☠☠n☠o☠p☠q☠r☠s☠t☠☠u☠☠v☠w☠x☠y☠☠z☠☠"
                            "♬ Welcome to the end of eras. Ice has melted back to life. ♬♬";

                        mainPStr = "♬ We're going down, down in an earlier round. ♬"
                            "我A名B是C科D我E蝙F我G名H是I科J我K蝙L我M名N我O蝙P我Q蝙R我S名T我U蝙VWXYZ"
                            "This is a normal line containing no unicode. Everything is alphanumeric."
                            "ΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮ"
                            "This next line however contains some amounts of unicode. Not too much."
                            "A B C D E F G H I J K L M N O P Q R S ᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒ"
                            "However, these next lines will be many integrals and subsets, with notation."
                            "Calculate the integrals: ∫f(x) ∫f(gx) ∫ x ∫∫ f(x + 1) ∫s dx ∫ 3!"
                            "A ⊆ B C ⊆ B and C ⊆ AB ⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆"
                            "Now let's go for quite awhile without any unicode, in order to be sparing."
                            "⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷"
                            "Ooops I lied. My bad. Now I shall recite the alphabet so that we only have letters."
                            "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z now I know my ABCs"
                            "¶ When editing documents, paragraphs are usually marked with the ¶ symbol. ¶"
                            "☠a☠b☠c☠d☠e☠f☠g☠h☠i☠j☠k☠l☠m☠☠n☠o☠p☠q☠r☠s☠t☠☠u☠☠v☠w☠x☠y☠☠z☠☠"
                            "♬ Welcome to the end of eras. Ice has melted back to life. ♬♬";

                        compStr = mainStr;
                        compPStr = mainPStr;
                        break;

                    }


                    case SAME_ALL_UNICODE:
                    {
                        mainStr = "我的名字是斯科特我是蝙蝠我的名字是斯科特我是蝙蝠我的名字我是蝙蝠"
                            "我的名字是斯科特我是蝙蝠我的名字是斯科特我是蝙蝠我的名字我是蝙蝠我是蝙蝠我的名字我是蝙蝠"
                            "ΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮ"
                            "ΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮ"
                            "ჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯ"
                            "ᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒ"
                            "∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫"
                            "⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆"
                            "☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯"
                            "ððððððððððððððððððððððððððððððððððððððððððððððððððððððððððððð"
                            "⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷"
                            "䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦";

                        mainPStr = "我的名字是斯科特我是蝙蝠我的名字是斯科特我是蝙蝠我的名字我是蝙蝠"
                            "我的名字是斯科特我是蝙蝠我的名字是斯科特我是蝙蝠我的名字我是蝙蝠我是蝙蝠我的名字我是蝙蝠"
                            "ΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮ"
                            "ΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮΠΦΣψϢϮ"
                            "ჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯჯ"
                            "ᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒᨒ"
                            "∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫∫"
                            "⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆⊆"
                            "☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯☯"
                            "ððððððððððððððððððððððððððððððððððððððððððððððððððððððððððððð"
                            "⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷⛷"
                            "䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦";

                        compStr = mainStr;
                        compPStr = mainPStr;
                        break;
                    }

                    case NSAME_FIRST_CHAR:
                    {
                        mainStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                         mainPStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                        compStr = "Doming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                        compPStr = compStr;

                        break;

                    }
                    case NSAME_MIDDLE_CHAR:
                    {
                        mainStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                         mainPStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                        // Change love in the middle to live
                        compStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I live the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                         compPStr = compStr;

                         break;

                    }
                     case NSAME_LAST_CHAR:
                    {
                        mainStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                         mainPStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name.";

                        // Changing last char
                        compStr = "Coming in unannounced, drag my nails on the tile. I "
                            "just followed your scent. You can just follow my smile."
                            "All of your flaws are aligned with this mood of mine."
                            "Cutting me to the bone, nothing left to leave behind."
                            "You ought to keep me concealed, just like I was a weapon."
                            "I didn't come for a fight but I will fight till the end."
                            "And this one might be a battle, might not turn out okay."
                            "You know you look so Seattle, but you feel so LA. And I "
                            "love the way you hurt me. It's irresistible, yeah. I love"
                            "the way. I love the way. I love the way you hurt me, baby."
                            "I love the way. I love the way. I love the way you hurt me,"
                            " baby. I'm gonna get you to burst just like you were a "
                            "bubble. Frame me up on your wall just to keep me out of trouble."
                            "Like a moth getting trapped in the light by fixation."
                            "Truly free, love it baby, I'm talking no inflation. "
                            "Too many war wounds and not enough wars. "
                            "Too few rounds in the ring and not enough settled scores."
                            "Too many sharks, not enough blood in the waves."
                            "You know I give my love a four letter name?";

                        compPStr = compStr;

                        break;


                    }

                }
                return true;
            }

            virtual bool run()
            {
                return true;
            }
            ~TestString(){}

        protected:
            TestType tType;
            std::string mainStr;
            QuickString<2048> mainPStr;
            std::string compStr;
            QuickString<2048> compPStr;

            testdoc_t title;
            testdoc_t docs;
    };


    class TestPawCompare: public TestString
    {
        public:
            explicit TestPawCompare(TestType type):TestString(type)
            {}

            testdoc_t get_title()
            {
                return title + " (QuickString)";
            }

            bool run()
            {

                for(int i=0; i < 1000; ++i)
                {
                    if(mainPStr == compPStr){};
                }
                return true;
            }
            ~TestPawCompare(){}

    };


    class TestStdCompare: public TestString
    {
        public:
            explicit TestStdCompare(TestType type):TestString(type)
            {}

            testdoc_t get_title()
            {
                return title + " (std::string)";
            }

            bool run()
            {
                for(int i=0; i < 1000; ++i)
                {
                    if(mainStr == compStr){};
                }
                return true;

            }
            ~TestStdCompare(){}

    };

    class TestSuite_Onestring : public TestSuite
    {
        public:
            explicit TestSuite_Onestring(){}

            void load_tests();

            testdoc_t get_title()
            {
                return "PawLIB: QuickString Tests";
            }

            ~TestSuite_Onestring(){}
    };
}

#endif // PAWSTRING_TESTS_HPP
