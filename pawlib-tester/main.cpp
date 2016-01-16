#include <iochannel.hpp>
#include <goldilocks.hpp>
#include <stdutils.hpp>
#include <sigc++/signal.h>
#include <sigc++/trackable.h>

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;
using namespace pawlib;

class TestFoo : public Test
{
    public:
        TestFoo(){}
        bool pre()
        {
            ioc << cat_testing << "Do Pre Stuff" << io_end;
            return true;
        }
        bool prefail()
        {
            ioc << cat_testing << "Do Prefail Stuff" << io_end;
            return true;
        }
        bool run()
        {
            ioc << cat_testing << "Do Test Stuff" << io_end;
            char str[5000] = {'\0'};
            for(int a=0;a<5000;a++)
            {
                str[a] = 'A';
            }
            return true;
        }
        bool postmortem()
        {
            ioc << cat_testing << "Do Postmortem Stuff" << io_end;
            return true;
        }
        bool post()
        {
            ioc << cat_testing << "Do Post Stuff" << io_end;
            return true;
        }
        ~TestFoo(){}
};

class TestFoo2 : public Test
{
    public:
        TestFoo2(){}
        bool pre()
        {
            ioc << cat_testing << "Do Pre Stuff" << io_end;
            return true;
        }
        bool prefail()
        {
            ioc << cat_testing << "Do Prefail Stuff" << io_end;
            return true;
        }
        bool run()
        {
            ioc << cat_testing << "Do Test Stuff" << io_end;
            std::string str = "";
            for(int a=0;a<5000;a++)
            {
                str.append("A");
            }
            return true;
        }
        bool postmortem()
        {
            ioc << cat_testing << "Do Postmortem Stuff" << io_end;
            return true;
        }
        bool post()
        {
            ioc << cat_testing << "Do Post Stuff" << io_end;
            return true;
        }
        ~TestFoo2(){}
};

void print(std::string msg, IOFormatVerbosity vrb, IOFormatCategory cat)
{
    //std::cout << msg;
}

int main()
{
    //This has to live here because evil.
    ioc.signal_all.connect(sigc::ptr_fun(print));
    //ioc << ta_bold << fg_blue << "===== PawLIB Tester =====\n" << io_end;

    testmanager.register_test("Foo", new TestFoo);
    testmanager.register_test("Bar", new TestFoo2);

    testmanager.run_test("Foo");
    testmanager.run_benchmark("Foo", 10000);
    testmanager.run_compare("Foo", "Bar", 10000);

    return 0;
}
