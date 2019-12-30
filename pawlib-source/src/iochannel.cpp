#include "pawlib/iochannel.hpp"

template<typename T>
T operator&(const T& lhs, const T& rhs)
{
    return static_cast<T>
        (static_cast<int>(lhs) & static_cast<int>(rhs));
}
template IOCat operator&<IOCat>(const IOCat&, const IOCat&);
template IOCtrl operator&<IOCtrl>(const IOCtrl&, const IOCtrl&);
template IOFormatMemSep operator&<IOFormatMemSep>(const IOFormatMemSep&, const IOFormatMemSep&);

template<typename T>
T operator|(const T& lhs, const T& rhs)
{
    return static_cast<T>
        (static_cast<int>(lhs) | static_cast<int>(rhs));
}
template IOCat operator|<IOCat>(const IOCat&, const IOCat&);
template IOCtrl operator|<IOCtrl>(const IOCtrl&, const IOCtrl&);
template IOFormatMemSep operator|<IOFormatMemSep>(const IOFormatMemSep&, const IOFormatMemSep&);

template<typename T>
T operator^(const T& lhs, const T& rhs)
{
    return static_cast<T>
        (static_cast<int>(lhs) ^ static_cast<int>(rhs));
}
template IOCat operator^<IOCat>(const IOCat&, const IOCat&);
template IOCtrl operator^<IOCtrl>(const IOCtrl&, const IOCtrl&);
template IOFormatMemSep operator^<IOFormatMemSep>(const IOFormatMemSep&, const IOFormatMemSep&);

template<typename T>
T operator~(const T& rhs)
{
    return static_cast<T>(~static_cast<int>(rhs));
}
template IOCat operator~<IOCat>(const IOCat&);
template IOCtrl operator~<IOCtrl>(const IOCtrl&);
template IOFormatMemSep operator~<IOFormatMemSep>(const IOFormatMemSep&);

//Declaring global instance of ioc.
iochannel ioc;

iochannel::iochannel()
: msg(""),
    process_cat(IOCat::all),
    process_vrb(IOVrb::tmi),
    echo_mode(IOEchoMode::cout),
    echo_cat(IOCat::all),
    echo_vrb(IOVrb::tmi),
    fmt(IOFormat()),
    readsize(IOMemReadSize(1)),
    vrb(IOVrb::normal),
    cat(IOCat::normal),
    parse(maybe),
    dirty_attributes(false)
{}

//------------ DATA TYPES ------------//

iochannel& iochannel::operator<<(const bool& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}
    switch(fmt.fmt_bool)
    {
        case IOFormatBool::lower:
        {
            inject(rhs ? "true" : "false");
            break;
        }
        case IOFormatBool::upper:
        {
            inject(rhs ? "True" : "False");
            break;
        }
        case IOFormatBool::caps:
        {
            inject(rhs ? "TRUE" : "FALSE");
            break;
        }
        case IOFormatBool::numeral:
        {
            inject(rhs ? "1" : "0");
            break;
        }
        case IOFormatBool::scott:
        {
            inject(rhs ? "Yea" : "Nay");
            break;
        }
    }

    return *this;
}

iochannel& iochannel::operator<<(const tril& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}
    switch(fmt.fmt_bool)
    {
        case IOFormatBool::lower:
        {
            inject( (~rhs) ? "maybe"
            : (rhs ? "true" : "false"));
            break;
        }
        case IOFormatBool::upper:
        {
            inject( (~rhs) ? "Maybe"
            : (rhs ? "True" : "False"));
            break;
        }
        case IOFormatBool::caps:
        {
            inject( (~rhs) ? "MAYBE"
            : (rhs ? "TRUE" : "FALSE"));
            break;
        }
        case IOFormatBool::numeral:
        {
            inject( (~rhs) ? "2"
            : (rhs ? "1" : "0"));
            break;
        }
        case IOFormatBool::scott:
        {
            inject( (~rhs) ? "Maybe"
            : (rhs ? "Yea" : "Nay"));
            break;
        }
    }
    return *this;
}

iochannel& iochannel::operator<<(const char& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    switch(fmt.fmt_char_value)
    {
        //Output as character.
        case IOFormatCharValue::as_char:
        {
            //This will call the inject(char) function.
            inject(rhs);
            break;
        }
        //Output as integer.
        case IOFormatCharValue::as_int:
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

    //Inject the C string form of the string into the iochannel.
    inject(rhs.c_str());
    return *this;
}

iochannel& iochannel::operator<<(const onechar& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    //Inject the C string form of the string into the iochannel.
    inject(rhs.c_str());
    return *this;
}

iochannel& iochannel::operator<<(const onestring& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    //Inject the C string form of the string into the iochannel.
    inject(rhs.c_str());
    return *this;
}

iochannel& iochannel::operator<<(const std::exception& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    /* Inject the exception message into the iochannel. Assume that
        * the exception itself has been handled externally. */
    inject(rhs.what());
    return *this;
}

iochannel& iochannel::operator<<(const IOFormat& rhs)
{
    fmt = rhs;
    return *this;
}

iochannel& iochannel::operator<<(const IOCursor& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    //Run the command (ANSI or whatever).
    move_cursor(rhs);
    return *this;
}

iochannel& iochannel::operator<<(const IOMemReadSize& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    readsize = rhs;

    return *this;
}

iochannel& iochannel::operator<<(const IOVrb& rhs)
{
    //Set the verbosity.
    vrb = rhs;
    //Revalidate parsing.
    parse = maybe;
    return *this;
}

iochannel& iochannel::operator<<(const IOCat& rhs)
{
    //Set the category.
    cat = rhs;
    //Revalidate parsing.
    parse = maybe;
    return *this;
}

iochannel& iochannel::operator<<(const IOCtrl& rhs)
{
    /* We'll need to track whether we're supposed to ask the transmission
        * to clear the flags. Doing it ourselves in this function
        * was the cause of T1081. */
    bool keep = true;

    if(static_cast<bool>(rhs & IOCtrl::clear))
    {
        reset_attributes();
        keep = false;
    }

    if(static_cast<bool>(rhs & IOCtrl::r))
    {
        can_parse() ? inject("\r") : inject("");
    }

    if(static_cast<bool>(rhs & IOCtrl::n))
    {
        can_parse() ? inject("\n") : inject("");
    }

    if(static_cast<bool>(rhs & IOCtrl::send))
    {
        transmit(keep);
    }

    if(static_cast<bool>(rhs & IOCtrl::flush))
    {
        flush();
    }

    return *this;
}

void iochannel::move_cursor(const IOCursor& rhs)
{
    //TODO: We will need to switch formats. For now, just ANSI.
    switch(rhs)
    {
        case IOCursor::left:
            //NOTE: Watch this. \x1B is allegedly equal to \e, check it.
            inject("\x1B[1D");
            break;
        case IOCursor::right:
            //NOTE: Watch this. \x1B is allegedly equal to \e, check it.
            inject("\x1B[1C");
            break;
        default:
            // Can't happen unless you forgot to implement an IOCursor option!
            break;
    }
}

iochannel& iochannel::resolve_pointer(const char* rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    switch(fmt.fmt_ptr)
    {
        //If we are to print as value...
        case IOFormatPtr::value:
        {
            //We can just inject the C-string.
            inject(rhs);
            break;
        }
        //If we are to print as address...
        case IOFormatPtr::address:
        {
            //Inject raw address.
            inject(rhs, sizeof(*rhs), false);
            break;
        }
        //If we are to print the raw memory...
        case IOFormatPtr::memory:
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

    switch(fmt.fmt_ptr)
    {
        //If we are to print as value...
        case IOFormatPtr::value:
        {
            *this << "[iochannel cannot interpret value at pointer of this type.]";
            break;
        }
        //If we are to print as address...
        case IOFormatPtr::address:
        {
            //Inject raw address, overriding with byte read size 1.
            inject(rhs, 1, false);
            break;
        }
        //If we are to print the raw memory...
        case IOFormatPtr::memory:
        {
            //Inject raw address with the read_size() given by the user.
            inject(rhs, readsize.readsize, true);
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

    switch(fmt.fmt_ptr)
    {
        //If we are to print as value...
        case IOFormatPtr::value:
        {
            *this << *rhs;
            break;
        }
        //If we are to print as address...
        case IOFormatPtr::address:
        {
            //Inject raw address.
            inject(rhs, sizeof(*rhs), false);
            break;
        }
        //If we are to print the raw memory...
        case IOFormatPtr::memory:
        {
            //Inject address for memory dump.
            inject(rhs, sizeof(typeid(*rhs)), true);
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
template iochannel& iochannel::resolve_pointer<onechar>(const onechar*);
template iochannel& iochannel::resolve_pointer<onestring>(const onestring*);

template <typename T>
iochannel& iochannel::resolve_integer(const T& rhs)
{
    //If we cannot parse because of `shutup()` settings, abort.
    if(!can_parse()){return *this;}

    int len = stdutils::intlen(rhs, static_cast<int>(fmt.fmt_base), true) + 1;

    // Accepting defeat on VLAs - we'll just have to dynamically allocate.
    char* cstr = new char[len];
    std::fill_n(cstr, len, '\0');

    stdutils::itoa(cstr, rhs, static_cast<int>(fmt.fmt_base), len, static_cast<bool>(fmt.fmt_numeral_case));
    inject(cstr);

    delete[] cstr;

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

    /*char cstr[stdutils::floatlen(rhs, significands, sci, true) + 1];
    cstr[0] = '\0';*/

    // Accepting defeat on VLAs - we'll just have to dynamically allocate.
    uint32_t len = stdutils::floatlen(rhs, fmt.fmt_significands.significands,
                                        static_cast<bool>(fmt.fmt_sci_notation), true) + 1;
    char* cstr = new char[len];
    std::fill_n(cstr, len, '\0');

    //Convert the float to a cstring, and dump into cstr.
    stdutils::ftoa(cstr, rhs, fmt.fmt_significands.significands, static_cast<bool>(fmt.fmt_sci_notation));
    inject(cstr);

    delete[] cstr;

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
        format.append(stdutils::itos(static_cast<int>(fmt.fmt_text_attr)));

        if(fmt.fmt_text_bg != IOFormatTextBG::none)
        {
            format.append(";");
            format.append(stdutils::itos(static_cast<int>(fmt.fmt_text_bg)));
        }

        if(fmt.fmt_text_fg != IOFormatTextFG::none)
        {
            format.append(";");
            format.append(stdutils::itos(static_cast<int>(fmt.fmt_text_fg)));
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
    /* If we aren't sure about the parsing condition... */
    if(~parse)
    {
        /* If the verbosity is in range or the category is set to parse,
            * then set false. Otherwise, set true. */
        parse = ((vrb <= process_vrb) && static_cast<bool>(process_cat & cat)) ? true : false;
    }
    return parse;
}

void iochannel::clear_msg()
{
    msg.clear();
    msg = "";
}

void iochannel::configure_echo(IOEchoMode mode, IOVrb vrb, IOCat cat)
{
    echo_mode = mode;
    echo_vrb = vrb;
    echo_cat = cat;
}

void iochannel::flush()
{
    /* TODO: For non-standard outputs, this should attach a bytecode to
        * tell external outputs to flush.*/

    //Flush is essential for progress-style outputs (after \r and no \n).
    switch(echo_mode)
    {
        case IOEchoMode::cout:
        {
            std::cout << std::flush;
            break;
        }
        case IOEchoMode::printf:
        {
            fflush(stdout);
            break;
        }
        case IOEchoMode::none:
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
}

void iochannel::inject(const void* ptr, unsigned int len, bool dump)
{
    if(!dump)
    {
        uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
        inject(stdutils::ptrtos(address, static_cast<bool>(fmt.fmt_numeral_case)).c_str());
    }
    else if(dump)
    {
        unsigned int memsize = (len * 2) + 1;
        bool bytespacing = static_cast<bool>(fmt.fmt_mem_sep & IOFormatMemSep::byte);
        bool wordspacing = static_cast<bool>(fmt.fmt_mem_sep & IOFormatMemSep::word);
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

        /*char mem[memsize];
        mem[0] = '\0';*/
        // Accepting defeat on VLAs - we'll just have to dynamically allocate.
        char* mem = new char[memsize];
        std::fill_n(mem, memsize, '\0');

        stdutils::memdump(mem, ptr, len, false, static_cast<int>(fmt.fmt_mem_sep));
        inject(mem);
    }
}

void iochannel::shutup(IOCat cat)
{
    process_cat = process_cat & ~cat;
    if(process_cat == IOCat::none)
    {
        printf("WARNING: All message categories have been turned off!\n");
    }
    //Revalidate parsing.
    parse = maybe;
}

void iochannel::shutup(IOVrb vrb)
{
    //Set the processing verbosity.
    process_vrb = vrb;
    //Revalidate parsing.
    parse = maybe;
}

void iochannel::speakup()
{
    process_vrb = IOVrb::tmi;
    process_cat = IOCat::all;
    //Revalidate parsing.
    parse = maybe;
}

void iochannel::speakup(IOCat cat)
{
    //Allow the category through by turning on its bit.
    process_cat = process_cat | cat;
    //Revalidate parsing.
    parse = maybe;
}

void iochannel::speakup(IOVrb vrb)
{
    //Allow verbosity through by turning on its bit.
    if(process_vrb < vrb)
    {
        process_vrb = vrb;
    }
    //Revalidate parsing.
    parse = maybe;
}

void iochannel::reset_attributes()
{
    if(fmt.fmt_text_attr != IOFormatTextAttr::none
        || fmt.fmt_text_fg != IOFormatTextFG::none
        || fmt.fmt_text_bg != IOFormatTextBG::none)
    {
        fmt << IOFormatTextAttr::none;
        fmt << IOFormatTextFG::none;
        fmt << IOFormatTextBG::none;
        dirty_attributes = true;
        /* We must leave calling `apply_attributes()` to `inject()`,
            * otherwise the reset attributes will never get injected
            * into the broadcast stream.
            */
    }

}

void iochannel::reset_flags()
{
    //Reset all the flags.
    fmt = IOFormat();
    readsize = IOMemReadSize(1);

    //We reset the verbosity and category.
    vrb = IOVrb::normal;
    cat = IOCat::normal;
}

void iochannel::transmit(bool keep)
{
    if(msg != "")
    {
        switch(vrb)
        {
            case IOVrb::quiet:
            {
                // Dispatch the "quiet" verbosity signal.
                signal_v_quiet(msg, cat);
                /* Fall through, so the lower signals get emitted to.
                    * This allows outputs to connect to the HIGHEST
                    * verbosity they will allow, and get the rest regardless.
                    */
                [[fallthrough]];
            }
            case IOVrb::normal:
            {
                // Dispatch the "normal" verbosity signal.
                signal_v_normal(msg, cat);
                [[fallthrough]];
            }
            case IOVrb::chatty:
            {
                // Dispatch the "chatty" verbosity signal.
                signal_v_chatty(msg, cat);
                [[fallthrough]];
            }
            case IOVrb::tmi:
            {
                // Dispatch the "TMI" verbosity signal.
                signal_v_tmi(msg, cat);
                break;
            }
        }

        if(static_cast<bool>(cat & IOCat::normal))
        {
            // Dispatch the "normal" category signal.
            signal_c_normal(msg, vrb);
        }
        if(static_cast<bool>(cat & IOCat::debug))
        {
            // Dispatch the "debug" category signal.
            signal_c_debug(msg, vrb);
        }
        if(static_cast<bool>(cat & IOCat::warning))
        {
            // Dispatch the "warning" category signal.
            signal_c_warning(msg, vrb);
        }
        if(static_cast<bool>(cat & IOCat::error))
        {
            // Dispatch the "error" category signal.
            signal_c_error(msg, vrb);
        }
        if(static_cast<bool>(cat & IOCat::testing))
        {
            // Dispatch the "testing" category signal.
            signal_c_testing(msg, vrb);
        }

        // Dispatch the general purpose signals.
        signal_full(msg, vrb, cat);
        signal_all(msg);

        //If we are supposed to be echoing
        if(echo_mode != IOEchoMode::none)
        {
            //If the verbosity and category is correct...
            if(vrb <= echo_vrb && static_cast<bool>(cat | echo_cat))
            {
                switch(echo_mode)
                {
                    // If we're supposed to use `printf`...
                    case IOEchoMode::printf:
                    {
                        if(static_cast<bool>(cat & IOCat::error))
                        {
                            /* Route the message through stderr
                                * instead of stdout.*/
                            fprintf(stderr, "%s", msg.c_str());
                        }
                        else
                        {
                            /* Route the message through stdout. */
                            printf("%s", msg.c_str());
                        }
                        break;
                    }
                    // If we're supposed to use `std::cout`...
                    case IOEchoMode::cout:
                    {
                        if(static_cast<bool>(cat & IOCat::error))
                        {
                            /* Route the message through stderr
                                * instead of stdout.*/
                            std::cerr << msg.c_str();
                        }
                        else
                        {
                            /* Route the message through stdout. */
                            std::cout << msg.c_str();
                        }

                        break;
                    }
                    // This case is here for completeness...
                    case IOEchoMode::none:
                    {
                        // ...we should never reach this point!
                        break;
                    }
                }
            }
        }

        /* If we aren't flagged to keep formatting,
            * reset the system in prep for the next message. */
        if(!keep)
        {
            reset_flags();
        }

        // Clear the message out in preparation for the next.
        clear_msg();

    }
}

iochannel::~iochannel()
{
    //Destructor
}
