#ifndef PAWLIB_IOCHANNEL_H
#define PAWLIB_IOCHANNEL_H

#include <iostream>

/*We are only using std::string and std::queue temporarily.
These need to be swapped out for pawlib alternatives ASAP.*/
#include <string>
#include <queue>

namespace pawlib
{
    /**An iochannel allows console output to be custom routed to one or more
    * text-based output channels, including the terminal. It supports various
    * advanced functions, formatting and colors, and message priority.*/
    class iochannel
    {
        public:
            /**The standard ANSI text attributes.*/
            enum TextAttributes
            {
                ///Turn of all attributes.
                TA_NONE = 0,
                ///Bold text.
                TA_BOLD = 1,
                ///Underlined text.
                TA_UNDERLINE = 4,
                ///Blinking text.
                TA_BLINK = 5,
                ///Inverted text colors, also known as "reverse video".
                TA_INVERT = 6
            };
            /**The standard ANSI text foreground colors.*/
            enum TextFGColor
            {
                ///Black text.
                FG_BLACK = 30,
                ///Red text.
                FG_RED = 31,
                ///Green text
                FG_GREEN = 32,
                ///Yellow text.
                FG_YELLOW = 33,
                ///Blue text.
                FG_BLUE = 34,
                ///Magenta text.
                FG_MAGENTA = 35,
                ///Cyan text.
                FG_CYAN = 36,
                ///White text.
                FG_WHITE = 37
            };
            /**The standard ANSI text background colors.*/
            enum TextBGColor
            {
                ///Black text background.
                BG_BLACK = 40,
                ///Red text background.
                BG_RED = 41,
                ///Green text background.
                BG_GREEN = 42,
                ///Yellow text background.
                BG_YELLOW = 43,
                ///Blue text background.
                BG_BLUE = 44,
                ///Magenta text background.
                BG_MAGENTA = 45,
                ///Cyan text background.
                BG_CYAN = 46,
                ///White text background.
                BG_WHITE = 47
            };

            /**Declares a new iochannel instance.*/
            iochannel();
            ~iochannel();
        protected:
            ///The queue of messages.
            std::queue<std::string> msgs;
        private:
    };
}


#endif // PAWLIB_BROADCAST_H
