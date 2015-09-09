#include "iochannel.hpp"

namespace pawlib
{
    iochannel::iochannel()
    {
        ta = ta_none;
        fg = fg_none;
        bg = bg_none;
        base = base_dec;
        dirty_attributes = false;
    }

    iochannel::~iochannel()
    {
        //Destructor
    }

    iochannel& iochannel::operator<<(const bool& rhs)
    {
        const char* str = (rhs ? "TRUE" : "FALSE");
        inject(str);
        return *this;
    }

    iochannel& iochannel::operator<<(const bool* rhs)
    {
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

    iochannel& iochannel::operator<<(const int& rhs)
    {
        //size_t len = stdutils::intlen(rhs, base, true);
        //char str[len];
        //memcpy(str, stdutils::itoa(rhs, base), len);
        //inject(str);
        inject(stdutils::itos(rhs, base, numcase));
        return *this;
    }

    iochannel& iochannel::operator<<(const int* rhs)
    {
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

    iochannel& iochannel::operator<<(const float& rhs)
    {
        //We use the same functions as for doubles, so just static_cast.
        *this << static_cast<double>(rhs);
        return *this;
    }

    iochannel& iochannel::operator<<(const float* rhs)
    {
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

    iochannel& iochannel::operator<<(const double& rhs)
    {
        inject(stdutils::dtos(rhs, precision, sci).c_str());
        return *this;
    }

    iochannel& iochannel::operator<<(const double* rhs)
    {
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

    iochannel& iochannel::operator<<(const void* rhs)
    {
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

    iochannel& iochannel::operator<<(const char& rhs)
    {
        char ch[2] = {rhs, '\0'};
        inject(ch);
        return *this;
    }

    iochannel& iochannel::operator<<(const char* rhs)
    {
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
                inject(rhs, sizeof(rhs), false);
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

    iochannel& iochannel::operator<<(const std::string& rhs)
    {
        inject(rhs.c_str());
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatBase& rhs)
    {
        base = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const set_precision& rhs)
    {
        precision = rhs.precision;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatSciNotation& rhs)
    {
        sci = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatNumeralCase& rhs)
    {
        numcase = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatPointer& rhs)
    {
        ptr = rhs;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatMemorySeperators& rhs)
    {
        if(rhs == 0)
        {
            memformat = 0;
        }
        else
        {
            memformat = (memformat | rhs);
        }
    }

    iochannel& iochannel::operator<<(const IOFormatTextBG& rhs)
    {
        //Save the setting.
        bg = rhs;
        //Raise dirty flag for attributes.
        dirty_attributes = true;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatTextFG& rhs)
    {
        //Save the setting.
        fg = rhs;
        //Raise dirty flag for attributes.
        dirty_attributes = true;
        return *this;
    }

    iochannel& iochannel::operator<<(const IOFormatTextAttributes& rhs)
    {
        //Save the setting.
        ta = rhs;
        //Raise dirty flag for attributes.
        dirty_attributes = true;
        return *this;
    }

    iochannel& iochannel::operator<<(const read_size& rhs)
    {
        readsize = rhs.readsize;
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
                inject("\n");
                transmit();
                break;
            }
        }
        return *this;
    }

    void iochannel::inject(std::string str, bool recursive)
    {
        //If we just applied attributes, push them now.
        if(!recursive && apply_attributes())
        {
            inject(format);
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

    void iochannel::transmit()
    {
        if(msg != "")
        {
            switch(vrb)
            {
                case vrb_quiet:
                {
                    signal_v_quiet(msg);
                    /* Fall through, so the lower signals get emitted to.
                     * This allows outputs to connect to the HIGHEST
                     * verbosity they will allow, and get the rest regardless.
                     */
                }
                case vrb_normal:
                {
                    signal_v_normal(msg);
                    //Fall through.
                }
                case vrb_chatty:
                {
                    signal_v_chatty(msg);
                    //Fall through.
                }
                case vrb_tmi:
                {
                    signal_v_tmi(msg);
                    break;
                }
            }

            switch(cat)
            {
                case cat_normal:
                {
                    signal_c_normal(msg);
                    break;
                }
                case cat_debug:
                {
                    signal_c_debug(msg);
                    break;
                }
                case cat_warning:
                {
                    signal_c_warning(msg);
                    break;
                }
                case cat_error:
                {
                    signal_c_error(msg);
                    break;
                }
            }

            signal_all(msg);

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
                            printf("%s", msg.c_str());
                            break;
                        }
                        case echo_cout:
                        {
                            std::cout << msg.c_str();
                            break;
                        }
                    }
                }
            }

            //Reset the system in prep for the next message.
            clear_msg();
            reset_flags();
        }
    }

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

    void iochannel::configure_echo(IOEchoMode echo, IOFormatVerbosity echo_vrb, IOFormatCategory echo_cat)
    {
        echomode = echo;
        echovrb = echo_vrb;
        echocat = echo_cat;
    }

    void iochannel::clear_msg()
    {
        /*TODO: This function may need to be either expanded once we stop using
        std::vector, or just dropped in favor of `msg.clear()`
        */

        msg.clear();
        msg = "";
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
        precision = 14;
        sci = sci_auto;
        numcase = num_lower;
        ptr = ptr_value;
        readsize = 1;
        memformat = 3;

        //We reset the verbosity and category.
        vrb = vrb_normal;
        cat = cat_normal;
    }
}
