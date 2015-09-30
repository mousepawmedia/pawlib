#include <iochannel.hpp>
#include <stdutils.h>
#include <sigc++/signal.h>
#include <sigc++/trackable.h>

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;
using namespace pawlib;

void print(std::string msg, IOFormatVerbosity vrb, IOFormatCategory cat)
{
    //std::cout << msg;
}

int main()
{
    //iochannel ioc;
    //This has to live here because evil.
    ioc.signal_all.connect(sigc::ptr_fun(print));

    signed char c = -123;
    signed short int si = -12345;
    signed int i = -123456789;
    signed long int li = -123456789123456789;

    unsigned char uc = 123;
    unsigned short int usi = 12345;
    unsigned int ui = 123456789;
    unsigned long int uli = 123456789123456789;


    ioc << c << io_end;
    ioc << si << io_end;
    ioc << i << io_end;
    ioc << li << io_end;
    ioc << uc << io_end;
    ioc << usi << io_end;
    ioc << ui << io_end;
    ioc << uli << io_end;

    ioc << "Hello, world!" << io_end;

    return 0;
}
