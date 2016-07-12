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

            TestString():tType(SAME_NO_UNICODE){}

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
                            "⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗"
                            "㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦"
                            "¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"
                            "䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦"
                            "课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课"
                            "☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠"
                            "♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♬♬♬♬♬♬♬♬♬";

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
                            "⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗⨗"
                            "㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦㕦"
                            "¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"
                            "䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦䯦"
                            "课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课课"
                            "☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠☠"
                            "♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♿♬♬♬♬♬♬♬♬♬";

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
            OneString<1024> mainPStr;
            std::string compStr;
            OneString<1024> compPStr;

    };


    class TestPawCompare: public TestString
    {
        public:
            explicit TestPawCompare(TestType type)
            {
                tType = type;
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
            explicit TestStdCompare(TestType type)
            {
                tType = type;
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
            static void load_tests(TestManager*);
        protected:

        private:
    };
}

#endif // PAWSTRING_TESTS_HPP