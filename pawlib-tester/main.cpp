#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <core_types.hpp>
#include <iochannel.hpp>
#include <onestringbase.hpp>
#include <onestring.hpp>
#include <quickstring.hpp>
#include <onechar.hpp>
#include <pawsort.hpp>
#include <stdutils.hpp>
#include <goldilocks.hpp>
#include <stdutils.hpp>

#include <TestSystem.hpp>

#include <pool.hpp>

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;
using namespace pawlib;
using namespace std;

void help();
void basicStringFunc();
int command(TestSystem* sys, unsigned int argc, char* argv[]);
void interactive(TestSystem* sys);

void print(std::string msg)
{
    std::cout << msg;
}

int main(int argc, char* argv[])
{
    //Set up signal handling.
    ioc.signal_all.add(&print);
    ioc.configure_echo(echo_none);

    TestSystem* sys = new TestSystem();
    (void) sys;
    (void) argc;
    (void) argv;

    // If we got command-line arguments.
    if(argc > 1)
    {
        return command(sys, static_cast<unsigned int>(argc), argv);
    }
    else
    {
        ioc << ta_bold << fg_blue << "===== PawLIB Tester =====\n" << io_end;

        // Custom test code goes here.

        // Shows that OneString and QuickString do operate correctly
        // basicStringFunc();

        // Shift control to the interactive console.
        interactive(sys);
    }

    delete sys;
    sys = 0;

    return 0;
}

void basicStringFunc()
{
    AscChar thing;
    thing = "h";
    UniChar thing1;
    thing1 = "¿";
    std::cout << thing1 <<std::endl;

    // Constructors and == (operator== calls equals())
    OneString<8> attempt("eight88");
    OneString<16> attempt1(attempt);
    std::cout<< "The two strings are equal: " << (attempt == attempt1) <<std::endl;
    attempt.append("¿");
    std::cout << attempt <<std::endl;
    std::cout << attempt[7] <<std::endl;
    std::cout << attempt.at(7) <<std::endl;
    std::cout<< "The two strings are equal: " << (attempt == attempt1) <<std::endl;
    std::cout << attempt.size() <<std::endl;
    std::cout<< attempt[4] <<std::endl;

    // Append functions
    OneString<16> appendIt;
    appendIt.append('h');
    appendIt.append("¿");
    appendIt.append('h');
    appendIt.append(thing1);
    appendIt.append(thing);
    appendIt.append(attempt);

//    attempt1.equals(attempt);
    //std::cout << attempt[5] <<std::endl;
    std::cout<< appendIt <<std::endl;

    // Insert functions
    OneString<16> insertStr("beti");
    std::cout<< insertStr <<std::endl;
    insertStr.insert(2, "au");
    std::cout<< insertStr <<std::endl;
    insertStr.insert(6, 'f');
    std::cout<< insertStr <<std::endl;
    OneString<8> insert2("ul");
    insertStr.insert(insertStr.size(), insert2);
    std::cout<< insertStr <<std::endl;

    /* NOTE: MUST ADD CODE TO LOOK FOR ASSIGNING LARGE STRING TO SMALLER */
    // Assignment
    OneString<32> assign1 = "⚡ ⛐  ⛳  ♫ ☯ ☭";
    std::cout<< assign1 <<std::endl;
    OneString<64> assign2 = assign1;
    std::cout<< assign2 <<std::endl;
    std::cout<< assign2.at(2) <<std::endl;

    // Input test
    OneString<8> input;
    std::cin >> input;
    std::cout<< input <<std::endl;

    //OneString<8> overFlow = "ThisIsTooLong";
    // Substring test
    OneString<32> subTest = "Let's Pick Words";
    std::cout<< subTest.substr(6) <<std::endl;
    std::cout<< subTest.substr(6, 2) <<std::endl;

    // Overflow test
    OneString<32> bigNum = "123456789101112";
    OneString<8> overFlow = bigNum;
    std::cout<< overFlow <<std::endl;
    std::cout<< overFlow.size() <<std::endl;

    // Operator+ test
    OneString<64> add1 = '!';
    AscChar space;
    space = ' ';
    OneString<64> add2 = "At Th";
    OneString<16> add3 = " Dis";
    OneString<8> add4 = "co";
    UniChar music;
    music = "♫";
    OneString<32> finalAdd = "Panic" + add1 +  space + add2 + 'e' + add3 + add4 + music;
    std::cout<< finalAdd <<std::endl;
    std::cout<< "String size is: " << finalAdd.size() <<std::endl;

    // Pop_back
    finalAdd.pop_back();
    finalAdd.pop_back();
    std::cout<< finalAdd <<std::endl;
    std::cout<< "String size is: " << finalAdd.size() <<std::endl;

    // Push_back
    finalAdd.push_back('a');
    std::cout<< finalAdd <<std::endl;
    std::cout<< "String size is: " << finalAdd.size() <<std::endl;
    finalAdd.pop_back();
    UniChar accent;
    accent = "ó";
    finalAdd.push_back(accent);
    std::cout<< finalAdd <<std::endl;
    std::cout<< "String size is: " << finalAdd.size() <<std::endl;
    finalAdd.pop_back();
    AscChar anotherVowel;
    anotherVowel = 'o';
    finalAdd.push_back(anotherVowel);
    std::cout<< finalAdd <<std::endl;
    std::cout<< "String size is: " << finalAdd.size() <<std::endl;


    // Swap
    OneString<32> swapStr = "Fallout Boy";
    swapStr.swap(finalAdd);
    std::cout<< finalAdd <<std::endl;
    std::cout<< "String size is: " << finalAdd.size() <<std::endl;
     std::cout<< swapStr <<std::endl;
    std::cout<< "String size is: " << swapStr.size() <<std::endl;
    std::cout<< "SwapStr is Fallout Boy: "<< (swapStr == "Fallout Boy") <<std::endl;
    std::cout<< "SwapStr is Panic! At The Disco: " << (swapStr == "Panic! At The Disco") <<std::endl;
    swapStr.append("♫");
    std::cout<< "SwapStr is Panic! At The Disco♫: "<< (swapStr == "Panic! At The Disco♫")<<std::endl;

    // Sizes
    OneString<512> largeSpace = "This OneString has a lot of space in it";
    std::cout<< largeSpace <<std::endl;
    std::cout<< "It's size, or number of characters, is : " << largeSpace.size() <<std::endl;
    std::cout<< "It's length, or number of bytes, is : " << largeSpace.length() <<std::endl;
    std::cout<< "It's maximum size is : " << largeSpace.max_size() <<std::endl;

    // Empty and Clear
    OneString<16> emptyStr = "This isn't empty";
    std::cout<< emptyStr << std::endl;
    std::cout<< "Is this string empty? " << emptyStr.empty() <<std::endl;
    std::cout<< "Size :"<< emptyStr.size() <<std::endl;
    emptyStr.clear();
    std::cout<< "What about after we clear it?" <<std::endl;
    std::cout<<  emptyStr << std::endl;
    std::cout<< "Is this string empty? " << emptyStr.empty() <<std::endl;
    std::cout<< "Size : " << emptyStr.size() <<std::endl;

    // Comparisons
    OneString<8> compStr("abc123");
    std::cout<< "Is abc123 smaller than abc124? " << (compStr < "abc124") <<std::endl;
    std::cout<< "Is abc123 greater than abc123? " << (compStr > "abc123") <<std::endl;
    std::cout<< "Is abc123 greater than OR EQUAL to abc123? " << (compStr >= "abc123") <<std::endl;
    std::cout<< "Is abc123 smaller than abc1234? " << (compStr < "abc1234") <<std::endl;
    std::cout<< "Is abc123 smaller than OR EQUAL to  abc12? " << (compStr <= "abc12") <<std::endl;

    // Repeat with OneStrings
    std::cout<< "Repeat with OneStrings" <<std::endl;
    OneString<8> comp1 = "abc124";
    OneString<16> comp2 = compStr;
    OneString<64> comp3 = comp2;
    OneString<128> comp4 = "abc1234";
    OneString<256> comp5 = "abc12";
    std::cout<< "Is abc123 smaller than abc124? " << (compStr < comp1) <<std::endl;
    std::cout<< "Is abc123 greater than abc123? " << (compStr > comp2) <<std::endl;
    std::cout<< "Is abc123 greater than OR EQUAL to abc123? " << (compStr >= comp3) <<std::endl;
    std::cout<< "Is abc123 smaller than abc1234? " << (compStr < comp4) <<std::endl;
    std::cout<< "Is abc123 smaller than OR EQUAL to  abc12? " << (compStr <= comp5) <<std::endl;

    // Plus equal
    UniChar key;
    key = "\xF0\x9F\x90\xAD";
    OneString<8> plusEq = "Paw";
    OneString<16> plusFinal = "Mouse";
    plusFinal += plusEq;
    plusFinal += " Gam";
    AscChar theE;
    theE = 'e';
    plusFinal += theE;
    plusFinal += 's';
    plusFinal += key;
    plusFinal += "\xF0\x9F\x90\xBE";
    plusFinal += 'C';
    std::cout<< plusFinal <<std::endl;
    //OneString<8> plusEq =
//    OneString<32> addit = "Sc";
//    OneString<32> addit1 = addit + "ott";

    // QuickString
    QuickString<16> firstQuick = "Hello World";
    std::cout << firstQuick <<std::endl;
    std::cout << firstQuick[3] <<std::endl;
    std::cout << firstQuick.size() <<std::endl;

    // Swap
    QuickString<32> swap1 = "Paramore";
    QuickString<32> swap2 = "All Time Low";
    swap1.swap(swap2);
    std::cout << swap1 <<std::endl;
    std::cout << swap2 <<std::endl;

    // Equals, pop_back, insert, append
    QuickString<32> newBand = swap2;
    std::cout << "The two strings are 'Paramore': " << (swap2 == newBand) <<std::endl;
    swap2.insert(4, "LES");
    swap2.pop_back();
    swap2.pop_back();
    swap2.pop_back();
    swap2.pop_back();
    swap2 += 'S';
    std::cout << swap2 <<std::endl;
    std::cout << newBand <<std::endl;
    std::cout << "The two strings are 'Paramore': " << (swap2 == newBand) <<std::endl;

}

int command(TestSystem* sys, unsigned int argc, char* argv[])
{
    int r = 0;
    bool loaded = false;

    std::vector<std::string> tokens;

    for(unsigned int i = 1; i < argc; ++i)
    {
        std::string str = argv[i];
        if(str == "--load")
        {
            loaded = true;
        }
        tokens.push_back(str);
    }

    for(unsigned int i = 0; i < argc-1; ++i)
    {
        if(tokens[i] == "--help")
        {
            ioc << "Usage: ./pawlib-tester [command] [argument]" << io_endline;
            ioc << "    --help          | Show this screen. "  << io_endline;
            ioc << "    --list          | List all tests. "  << io_endline;
            ioc << "    --listsuites    | List all suites. "  << io_endline;
            ioc << "    --load [suite]  | Load the suite [suite]. "
                << "If unspecified, all suites will be loaded." << io_endline;
            ioc << "    --suite [suite] | Run the suite [suite]. "  << io_endline;
            ioc << "    --test [test]   | Run the test [test]. "  << io_endline;
            ioc << io_end;
        }
        else if(i <= i+1 && tokens[i] == "--load")
        {
            // If load succeeds, set the return code to 0, else 1 (error).
            r = sys->testmanager->load_suite(tokens[++i]) ? 0 : 1;
            loaded = true;
        }
        else if(tokens[i] == "--list")
        {
            if(!loaded)
            {
                sys->testmanager->load_suite();
            }

            // List all loaded tests.
            sys->testmanager->list_tests(true);
        }
        else if(tokens[i] == "--listsuites")
        {
            // List all suites.
            sys->testmanager->list_suites(true);
        }
        else if(i <= i+1 && tokens[i] == "--suite")
        {
            if(!loaded)
            {
                sys->testmanager->load_suite();
            }

            // If run_suite succeeds, set the return code to 0, else 1 (error).
            r = sys->testmanager->run_suite(tokens[++i]) ? 0 : 1;
        }
        else if(i <= i+1 && tokens[i] == "--test")
        {
            if(!loaded)
            {
                sys->testmanager->load_suite();
            }

            // If run_test succeeds, set the return code to 0, else 1 (error).
            r = sys->testmanager->run_test(tokens[++i]) ? 0 : 1;
        }
        else
        {
            ioc << "ERROR: Invalid command " << tokens[i] << io_endline;
            ioc << "See ./pawlib-tester --help" << io_end;
        }
        // We will add compare later, as it requires an expected outcome.

        if(r > 0)
        {
            break;
        }
    }

    return r;
}

void interactive(TestSystem* sys)
{
    std::string buffer;
    std::vector<std::string> tokens;

    ioc << "Type \"help\" for a list of commands." << io_end;

    // Display typing prompt.
    ioc << ":" << io_send;
    // Get what the user typed.
    getline(std::cin, buffer);
    // Split the line into space-delimited tokens.
    stdutils::stdsplit(buffer, " ", tokens);

    //Loop while command is not the pseudocommand "exit"...
    while(tokens[0] != "exit")
    {
        if(tokens[0] == "help")
        {
            help();
        }
        else if(tokens[0] == "about")
        {
            sys->testmanager->show_docs(tokens[1]);
        }
        else if(tokens[0] == "benchmark")
        {
            if(tokens.size() < 2)
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Not enough arguments." << io_end;
            }
            else if(tokens.size() == 2)
            {
                sys->testmanager->i_run_benchmark(tokens[1]);
            }
            else if(tokens.size() == 3)
            {
                try
                {
                    sys->testmanager->i_run_benchmark(tokens[1], std::stoi(tokens[2]));
                }
                catch(std::invalid_argument)
                {
                    ioc << fg_red << ta_bold << cat_error
                    << "ERROR: " << tokens[2] << " is not a valid integer. "
                    << "Please specify a valid number of reptitions for "
                    << "the benchmark." << io_end;
                }
            }
            else
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Too many arguments." << io_end;
            }
        }
        else if(tokens[0] == "compare")
        {
            if(tokens.size() < 3)
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Not enough arguments." << io_end;
            }
            else if(tokens.size() == 3)
            {
                sys->testmanager->i_run_compare(tokens[1], tokens[2]);
            }
            else if(tokens.size() == 4)
            {
                try
                {
                    sys->testmanager->i_run_compare(tokens[1], tokens[2], std::stoi(tokens[3]));
                }
                catch(std::invalid_argument)
                {
                    ioc << fg_red << ta_bold << cat_error
                    << "ERROR: " << tokens[3] << " is not a valid integer. "
                    << "Please specify a valid number of reptitions for "
                    << "the benchmark." << io_end;
                }
            }
            else
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Too many arguments." << io_end;
            }
        }
        else if(tokens[0] == "list")
        {
            sys->testmanager->list_tests(true);
        }
        else if(tokens[0] == "listsuites")
        {
            sys->testmanager->list_suites(true);
        }
        else if(tokens[0] == "load")
        {
            if(tokens.size() < 2)
            {
                // If we got no arguments, interactively load all suites.
                sys->testmanager->i_load_suite();
            }
            else if(tokens.size() == 2)
            {
                sys->testmanager->load_suite(tokens[1]);
            }
            else
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Too many arguments." << io_end;
            }
        }
        else if(tokens[0] == "suite")
        {
            if(tokens.size() < 2)
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Not enough arguments." << io_end;
            }
            else if(tokens.size() == 2)
            {
                sys->testmanager->i_run_suite(tokens[1]);
            }
            else
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Too many arguments." << io_end;
            }
        }
        else if(tokens[0] == "test")
        {
            if(tokens.size() < 2)
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Not enough arguments." << io_end;
            }
            else if(tokens.size() == 2)
            {
                sys->testmanager->i_run_test(tokens[1]);
            }
            else
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Too many arguments." << io_end;
            }
        }
        else
        {
            ioc << ta_bold << cat_warning
                << "Unrecognized command. Type \"help\" for help." << io_end;
        }

        // Get more user input...
        // Clear the tokens vector to make room for new results.
        tokens.clear();
        // Display the prompt.
        ioc << ":" << io_send;
        // Get the line the user just typed.
        getline(std::cin, buffer);
        // Split the line into space-delimited tokens.
        stdutils::stdsplit(buffer, " ", tokens);
    }
    // Once the command (first token) is "exit", we quit.
}

void help()
{
    ioc << "-- HELP --" << io_end;
    ioc << "[SYNTAX: command [required param] (optional param)\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":about [test]" << io_end;
    ioc << "Display the documentation for [test].\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":benchmark [test] (number)" << io_end;
    ioc << "Runs a benchmark on [test] with (number) repetitions.\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":compare [test1] [test2] (number)" << io_end;
    ioc << "Runs a comparative benchmark between [test1] and [test2] with (number) reps.\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":help" << io_end;
    ioc << "Displays the help screen.\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":list" << io_end;
    ioc << "Displays the available tests.\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":listsuites" << io_end;
    ioc << "Displays the available suites.\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":load" << io_end;
    ioc << "Loads all suites.\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":load [suite]" << io_end;
    ioc << "Loads the tests from [suite].\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":suite [suite]" << io_end;
    ioc << "Runs all tests in [suite].\n" << io_end;
    ioc << "----" << io_end;

    ioc << ta_bold << ":test [test]" << io_end;
    ioc << "Runs [test].\n" << io_end;
    ioc << "----" << io_end;

    ioc << "Back to you, Bob!\n" << io_end;
}
