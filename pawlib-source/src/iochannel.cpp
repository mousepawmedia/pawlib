#include "iochannel.hpp"

namespace pawlib
{
    //Declaring global instance of ioc.
    iochannel ioc;

    iochannel::iochannel()
    {
        ta = ta_none;
        fg = fg_none;
        bg = bg_none;
        base = base_dec;
        dirty_attributes = false;
    }

    //------------ DATA TYPES ------------//

    iochannel& iochannel::operator<<(const bool& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}
        switch(boolstyle)
        {
            case bool_lower:
            {
                inject(rhs ? "true" : "false");
                break;
            }
            case bool_upper:
            {
                inject(rhs ? "True" : "False");
                break;
            }
            case bool_caps:
            {
                inject(rhs ? "TRUE" : "FALSE");
                break;
            }
            case bool_numeral:
            {
                inject(rhs ? "1" : "0");
                break;
            }
            case bool_scott:
            {
                inject(rhs ? "Yea" : "Nay");
                break;
            }
        }

        return *this;
    }

    iochannel& iochannel::operator<<(const char& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        switch(charval)
        {
            //Output as character.
            case char_char:
            {
                //This will call the inject(char) function.
                inject(rhs);
                break;
            }
            //Output as integer.
            case char_int:
            {
                resolve_integer(rhs);
                break;
            }
        }
        return *this;
    }

    iochannel& iochannel::operator<<(const std::string& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        inject(rhs.c_str());
        return *this;
    }

    //------------ ENUMERATIONS ------------//

    iochannel& iochannel::operator<<(const IOFormatBase& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        base = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatBool& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        boolstyle = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatCharValue& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        charval = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const set_precision& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        precision = rhs.precision;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatSciNotation& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        sci = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatNumeralCase& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        numcase = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatPointer& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        ptr = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatMemorySeparators& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        if(rhs == 0)
        {
            memformat = 0;
        }
        else
        {
            memformat = (memformat | rhs);
        }

        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatTextBG& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        //Save the setting.
        bg = rhs;
        //Raise dirty flag for attributes.
        dirty_attributes = true;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatTextFG& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        //Save the setting.
        fg = rhs;
        //Raise dirty flag for attributes.
        dirty_attributes = true;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatTextAttributes& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        //Save the setting.
        ta = rhs;
        //Raise dirty flag for attributes.
        dirty_attributes = true;
        return *this;
    }

    iochannel& iochannel::operator<<(const read_size& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        readsize = rhs.readsize;

        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatVerbosity& rhs)
    {
        //Set the verbosity.
        vrb = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatCategory& rhs)
    {
        //Set the category.
        cat = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOSpecial& rhs)
    {
        switch(rhs)
        {
            case io_end:
            {
                reset_attributes();
                //Fall through to twin.
            }
            case io_end_keep:
            {
                (can_parse()) ? inject("\n") : inject("");
                transmit(true);
                break;
            }
            case io_send:
            {
                reset_attributes();
                //Fall through to twin.
            }
            case io_send_keep:
            {
                inject("");
                transmit(true);
                break;
            }
            case io_endline:
            {
                reset_attributes();
                //Fall through to twin.
            }
            case io_endline_keep:
            {
                (can_parse()) ? inject("\n") : inject("");
                break;
            }
            case io_show:
            {
                reset_attributes();
                //Fall through to twin.
            }
            case io_show_keep:
            {
                (can_parse()) ? inject("\r") : inject("");
                //Fall through to flush.
            }
            case io_flush:
            {
                flush();
                break;
            }
        }
        return *this;
    }

    iochannel& iochannel::resolve_pointer(const char* rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        switch(ptr)
        {
            //If we are to print as value...
            case ptr_value:
            {
                //We can just inject the C-string.
                inject(rhs);
                break;
            }
            //If we are to print as address...
            case ptr_address:
            {
                //Inject raw address.
                inject(rhs, sizeof(*rhs), false);
                break;
            }
            //If we are to print the raw memory...
            case ptr_memory:
            {
                //Inject address for memory dump.
                inject(rhs, ((strlen(rhs) + 1) * sizeof(char)), true);
                break;
            }
        }
        return *this;
    }

    iochannel& iochannel::resolve_pointer(const void* rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        switch(ptr)
        {
            //If we are to print as value...
            case ptr_value:
            {
                *this << "[iochannel cannot interpret value at pointer of this type.]";
                break;
            }
            //If we are to print as address...
            case ptr_address:
            {
                //Inject raw address, overriding with byte read size 1.
                inject(rhs, 1, false);
                break;
            }
            //If we are to print the raw memory...
            case ptr_memory:
            {
                //Inject raw address with the read_size() given by the user.
                inject(rhs, readsize, true);
                break;
            }
        }
        return *this;
    }

    template <typename T>
    iochannel& iochannel::resolve_pointer(const T* rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        switch(ptr)
        {
            //If we are to print as value...
            case ptr_value:
            {
                *this << *rhs;
                break;
            }
            //If we are to print as address...
            case ptr_address:
            {
                //Inject raw address.
                inject(rhs, sizeof(*rhs), false);
                break;
            }
            //If we are to print the raw memory...
            case ptr_memory:
            {
                //Inject address for memory dump.
                inject(rhs, sizeof(*rhs), true);
                break;
            }
        }
        return *this;
    }
    template iochannel& iochannel::resolve_pointer<bool>(const bool*);
    template iochannel& iochannel::resolve_pointer<unsigned char>(const unsigned char*);
    template iochannel& iochannel::resolve_pointer<int>(const int*);
    template iochannel& iochannel::resolve_pointer<unsigned int>(const unsigned int*);
    template iochannel& iochannel::resolve_pointer<short int>(const short int*);
    template iochannel& iochannel::resolve_pointer<unsigned short int>(const unsigned short int*);
    template iochannel& iochannel::resolve_pointer<long int>(const long int*);
    template iochannel& iochannel::resolve_pointer<unsigned long int>(const unsigned long int*);
    template iochannel& iochannel::resolve_pointer<long long int>(const long long int*);
    template iochannel& iochannel::resolve_pointer<unsigned long long int>(const unsigned long long int*);
    template iochannel& iochannel::resolve_pointer<float>(const float*);
    template iochannel& iochannel::resolve_pointer<double>(const double*);
    template iochannel& iochannel::resolve_pointer<long double>(const long double*);
    template iochannel& iochannel::resolve_pointer<std::string>(const std::string*);

    template <typename T>
    iochannel& iochannel::resolve_integer(const T& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        int len = stdutils::intlen(rhs, base, true) + 1;
        char cstr[len] = {'\0'};
        stdutils::itoa(cstr, rhs, base, len, numcase);
        inject(cstr);
        return *this;
    }
    template iochannel& iochannel::resolve_integer<char>(const char&);
    template iochannel& iochannel::resolve_integer<unsigned char>(const unsigned char&);
    template iochannel& iochannel::resolve_integer<int>(const int&);
    template iochannel& iochannel::resolve_integer<unsigned int>(const unsigned int&);
    template iochannel& iochannel::resolve_integer<short int>(const short int&);
    template iochannel& iochannel::resolve_integer<unsigned short int>(const unsigned short int&);
    template iochannel& iochannel::resolve_integer<long int>(const long int&);
    template iochannel& iochannel::resolve_integer<unsigned long int>(const unsigned long int&);
    template iochannel& iochannel::resolve_integer<long long int>(const long long int&);
    template iochannel& iochannel::resolve_integer<unsigned long long int>(const unsigned long long int&);

    template <typename T>
    iochannel& iochannel::resolve_float(const T& rhs)
    {
        //If we cannot parse because of `shutup()` settings, abort.
        if(!can_parse()){return *this;}

        char cstr[stdutils::floatlen(rhs, precision, sci, true) + 1] = {'\0'};
        //Convert the float to a cstring, and dump into cstr.
        stdutils::ftoa(cstr, rhs, precision, sci);
        inject(cstr);
        return *this;
    }
    template iochannel& iochannel::resolve_float<float>(const float&);
    template iochannel& iochannel::resolve_float<double>(const double&);
    template iochannel& iochannel::resolve_float<long double>(const long double&);

    bool iochannel::apply_attributes()
    {
        bool r = false;
        //If we have unapplied attributes.
        if(dirty_attributes)
        {
            //TODO: We will need to switch formats. For now, just ANSI.
            format = "\033[";
            format.append(stdutils::itos(ta));

            if(bg > 0)
            {
                format.append(";");
                format.append(stdutils::itos(bg));
            }

            if(fg > 0)
            {
                format.append(";");
                format.append(stdutils::itos(fg));
            }

            format.append("m");

            //We took care of the attributes. Lower the dirty flag.
            dirty_attributes = false;
            r = true;
        }
        return r;
    }

    bool iochannel::can_parse()
    {
        /* If the verbosity is in range or the category is
         * set to parse, then return false. Otherwise,
         * return true.*/
        return ((vrb <= process_v) && (process_c & cat)) ? true : false;
    }

    void iochannel::clear_msg()
    {
        /*TODO: This function may need to be either expanded once we stop using
        std::vector, or just dropped in favor of `msg.clear()`
        */

        msg.clear();
        msg = "";
    }

    void iochannel::configure_echo(IOEchoMode echo, IOFormatVerbosity echo_vrb, IOFormatCategory echo_cat)
    {
        echomode = echo;
        echovrb = echo_vrb;
        echocat = echo_cat;
    }

    void iochannel::flush()
    {
        /* TODO: For non-standard outputs, this should attach a bytecode to
         * tell external outputs to flush.*/

        //Flush is essential for progress-style outputs (after \r and no \n).
        switch(echomode)
        {
            case echo_cout:
            {
                std::cout << std::flush;
                break;
            }
            case echo_printf:
            {
                fflush(stdout);
                break;
            }
            case echo_none:
            {
                break;
            }
        }
    }

    void iochannel::inject(char ch)
    {
        //If we just applied attributes, push them now.
        if(apply_attributes())
        {
            inject(format.c_str());
        }

        msg.push_back(ch);
        //TODO: Swap for pawlib::string
    }

    void iochannel::inject(const char* str, bool recursive)
    {
        //If we just applied attributes, push them now.
        if(!recursive && apply_attributes())
        {
            inject(format.c_str());
        }

        //Append to the message.
        msg.append(str);
        //TODO: Swap for pawlib::string

        ////apply_attributes() ? printf("%s", format) : 0;
        ////printf("%s", str);
    }

    void iochannel::inject(const void* ptr, unsigned int len, bool dump)
    {
        if(!dump)
        {
            uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
            inject(stdutils::ptrtos(address, numcase).c_str());
        }
        else if(dump)
        {
            unsigned int memsize = (len * 2) + 1;
            bool bytespacing = (memformat & (1 << 0));
            bool wordspacing = (memformat & (1 << 1));
            if(bytespacing)
            {
                //Add a space for each byte except the last.
                memsize += len-1;
            }
            if(wordspacing)
            {
                //Add a bar for each word.
                memsize += (len / 8);

                if(bytespacing)
                {
                    memsize += (len / 8);
                }

                if(len % 8 == 0)
                {
                    //Remove one bar.
                    memsize--;

                    if(bytespacing)
                    {
                        //Remove one space.
                        memsize--;
                    }
                }
            }

            char mem[memsize] = {'\0'};
            stdutils::memdump(mem, ptr, len, false, memformat);
            inject(mem);
        }
    }

    void iochannel::shutup(IOFormatCategory cat)
    {
        process_c = process_c & ~cat;
        if(process_c == 0)
        {
            printf("WARNING: All message categories have been turned off!\n");
        }
    }

    void iochannel::shutup(IOFormatVerbosity vrb)
    {
        //Set the processing verbosity.
        process_v = vrb;
    }

    void iochannel::speakup()
    {
        process_v = vrb_tmi;
        process_c = cat_all;
    }

    void iochannel::speakup(IOFormatCategory cat)
    {
        //Allow the category through by turning on its bit.
        process_c = process_c | cat;
    }

    void iochannel::reset_attributes()
    {
        if(ta > 0 || fg > 0 || bg > 0)
        {
            ta = ta_none;
            fg = fg_none;
            bg = bg_none;
            dirty_attributes = true;
            /* We must leave calling `apply_attributes()` to `inject()`,
             * otherwise the reset attributes will never get injected
             * into the broadcast stream.
             */
        }

    }

    void iochannel::reset_flags()
    {
        reset_attributes();

        //Reset the base.
        base = base_dec;
        boolstyle = bool_lower;
        charval = char_char;
        precision = 14;
        sci = sci_auto;
        numcase = num_lower;
        ptr = ptr_value;
        readsize = 1;
        memformat = 0;

        //We reset the verbosity and category.
        vrb = vrb_normal;
        cat = cat_normal;
    }

    void iochannel::transmit(bool keep)
    {
        if(msg != "")
        {
            switch(vrb)
            {
                case vrb_quiet:
                {
                    signal_v_quiet(msg, cat);
                    /* Fall through, so the lower signals get emitted to.
                     * This allows outputs to connect to the HIGHEST
                     * verbosity they will allow, and get the rest regardless.
                     */
                }
                case vrb_normal:
                {
                    signal_v_normal(msg, cat);
                    //Fall through.
                }
                case vrb_chatty:
                {
                    signal_v_chatty(msg, cat);
                    //Fall through.
                }
                case vrb_tmi:
                {
                    signal_v_tmi(msg, cat);
                    break;
                }
            }

            switch(cat)
            {
                case cat_normal:
                {
                    signal_c_normal(msg, vrb);
                    break;
                }
                case cat_debug:
                {
                    signal_c_debug(msg, vrb);
                    break;
                }
                case cat_warning:
                {
                    signal_c_warning(msg, vrb);
                    break;
                }
                case cat_error:
                {
                    signal_c_error(msg, vrb);
                    break;
                }
                case cat_testing:
                {
                    signal_c_testing(msg, vrb);
                    break;
                }
                case cat_all:
                {
                    //This has no corresponding signal.
                    break;
                }
            }

            signal_all(msg, vrb, cat);

            //If we are supposed to be echoing
            if(echomode != echo_none)
            {
                //If the verbosity and category is correct...
                if(vrb <= echovrb && (cat == echocat || echocat == cat_all))
                {
                    switch(echomode)
                    {
                        case echo_printf:
                        {
                            if(cat == cat_error)
                            {
                                fprintf(stderr, "%s", msg.c_str());
                            }
                            else
                            {
                                printf("%s", msg.c_str());
                            }
                            break;
                        }
                        case echo_cout:
                        {
                            if(cat == cat_error)
                            {
                                std::cerr << msg.c_str();
                            }
                            else
                            {
                                std::cout << msg.c_str();
                            }

                            break;
                        }
                        case echo_none:
                        {
                            //We should never reach this point!
                            break;
                        }
                    }
                }
            }

            //Reset the system in prep for the next message.
            if(!keep)
            {
                reset_flags();
            }

            clear_msg();

        }
    }

    iochannel::~iochannel()
    {
        //Destructor
    }
}
