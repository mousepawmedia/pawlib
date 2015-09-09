#include <iochannel.hpp>
#include <stdutils.h>
#include <sigc++/signal.h>
#include <sigc++/trackable.h>

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;

void print(std::string msg)
{
    //std::cout << msg;
}

int main()
{
    iochannel ioc;
    //This has to live here because evil.
    ioc.signal_all.connect(sigc::ptr_fun(print));

    char* test = "My name is Jason C. McDonald, and I am a coder.\0";

    ioc << "Value: " << ptr_value << test << io_end;
    ioc << "Address: " << ptr_address << test << io_end;
    ioc << "Dump: " << ptr_memory << test << io_end;

    ioc << vrb_normal << fg_red << ta_bold << "Hello, " << fg_blue << "world!" << io_end;
    return 0;
}
