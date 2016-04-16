#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <iochannel.hpp>
#include <pawstring.hpp>
#include <pawsort.hpp>
#include <stdutils.hpp>
#include <goldilocks.hpp>
#include <stdutils.hpp>

#include <TestSystem.hpp>

using pawlib::iochannel;

//Format enumerations.
using namespace pawlib::ioformat;
using namespace pawlib;
using namespace std;

void help();
void interactive();
void split(std::string, std::string, std::vector<std::string>&);

void print(std::string msg)
{
    std::cout << msg;
}

int main()
{
    //Set up signal handling.
    ioc.signal_all.add(&print);
    ioc.configure_echo(echo_none);
    ioc << ta_bold << fg_blue << "===== PawLIB Tester =====\n" << io_end;

    //Custom test code goes here.

    // Shift control to the interactive console.
    interactive();

    return 0;
}

void interactive()
{
    TestSystem* sys = new TestSystem();

    std::string buffer;
    std::vector<std::string> tokens;

    ioc << "Type \"help\" for a list of commands." << io_end;

    // Display typing prompt.
    ioc << ":" << io_send;
    // Get what the user typed.
    getline(std::cin, buffer);
    // Split the line into space-delimited tokens.
    split(buffer, " ", tokens);

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
        else if(tokens[0] == "test")
        {
            if(tokens.size() < 2)
            {
                ioc << fg_red << ta_bold << cat_error
                    << "ERROR: Not enough arguments." << io_end;
            }
            else if(tokens.size() == 2)
            {
                ioc << "Run test \"" << tokens[1] << "\"." << io_end;
                sys->testmanager->run_test(tokens[1]);
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
        split(buffer, " ", tokens);
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

    /*ioc << ta_bold << ":load [suite]" << io_end;
    ioc << "Loads the tests from [suite].\n" << io_end;
    ioc << "----" << io_end;*/

    ioc << ta_bold << ":test [test]" << io_end;
    ioc << "Runs [test].\n" << io_end;
    ioc << "----" << io_end;

    ioc << "Back to you, Bob!\n" << io_end;
}

void split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
    /* Store the original string in the array, so we can loop the rest
     * of the algorithm. */
    tokens.push_back(str);

    // Store the size of what we're splicing out.
    size_t splitLen = splitBy.size();
    // Create a string for temporarily storing the fragment we're processing.
    std::string frag;

    // Loop infinitely - break is internal.
    while(true)
    {
        // Store the split index in a 'size_t' (unsigned integer) type.
        size_t splitAt;

        /* Store the last string in the vector, which is the only logical
         * candidate for processing. */
        frag = tokens.back();
        /* The index where the split is. */
        splitAt = frag.find(splitBy);
        // If we didn't find a new split point...
        if(splitAt == string::npos)
        {
            // Break the loop and (implicitly) return.
            break;
        }
        /* Put everything from the left side of the split where the string
         * being processed used to be. */
        tokens.back() = frag.substr(0, splitAt);
        /* Push everything from the right side of the split to the next empty
         * index in the vector. */
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
}
