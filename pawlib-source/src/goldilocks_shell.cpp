#include "pawlib/goldilocks_shell.hpp"

namespace pawlib
{
    TestCatalog::TestCatalog()
    {
        // Initialize a new Goldilocks testmanager.
        testmanager = new TestManager;
    }

    TestCatalog::~TestCatalog()
    {
        delete testmanager;
        testmanager = 0;
    }

    int GoldilocksShell::command(TestCatalog* sys, unsigned int argc, char* argv[])
    {
        /* The return code; non-zero return codes are needed for failing CI
         * on test failure.
         */
        int r = 0;
        // Whether we've actually loaded something.
        bool loaded = false;

        // We are using std::string for the time being.
        std::vector<std::string> tokens;

        // Parse through the arguments from the command line.
        for(unsigned int i = 1; i < argc; ++i)
        {
            // Store the currently focused arg as a std::string
            std::string str = argv[i];
            // If the argument is the "--load" flag...
            if(str == "--load")
            {
                // We loaded something! Mark that.
                loaded = true;
            }
            // Store the argument.
            tokens.push_back(str);
        }

        // Loop thorugh each token...
        for(unsigned int i = 0; i < argc-1; ++i)
        {
            // If help flag is provided...
            if(tokens[i] == "--help")
            {
                // Display CLI help
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
            // If load flag and subsequent argument are provided...
            else if(i <= i+1 && tokens[i] == "--load")
            {
                // If load succeeds, set the return code to 0, else 1 (error).
                r = sys->testmanager->load_suite(tokens[++i]) ? 0 : 1;
                loaded = true;
            }
            // If list flag is provided...
            else if(tokens[i] == "--list")
            {
                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    sys->testmanager->load_suite();
                    loaded = true;
                }

                // List all loaded tests.
                sys->testmanager->list_tests(true);
            }
            // If listsuites flag is provided...
            else if(tokens[i] == "--listsuites")
            {
                // List all suites.
                sys->testmanager->list_suites(true);
            }
            // If suite flag and subsequent argument are provided...
            else if(i <= i+1 && tokens[i] == "--suite")
            {
                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    sys->testmanager->load_suite();
                    loaded = true;
                }

                // If run_suite succeeds, set the return code to 0, else 1 (error).
                r = sys->testmanager->run_suite(tokens[++i]) ? 0 : 1;
            }
            // If test flag and subsequent argument are provided...
            else if(i <= i+1 && tokens[i] == "--test")
            {
                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    sys->testmanager->load_suite();
                    loaded = true;
                }

                // If run_test succeeds, set the return code to 0, else 1 (error).
                r = sys->testmanager->run_test(tokens[++i]) ? 0 : 1;
            }
            // If the token is invalid...
            else
            {
                // Throw error and help prompt.
                ioc << "ERROR: Invalid command " << tokens[i] << io_endline;
                ioc << "See --help" << io_end;
            }
            // TODO: We will add compare later, as it requires an expected outcome.

            // If the return code is greater than 0...
            if(r > 0)
            {
                // Immediately drop out of loop.
                break;
            }
        }

        // Return code (default 0)
        return r;
    }

    void GoldilocksShell::interactive(TestCatalog* sys)
    {
        // Store user input.
        std::string buffer;
        // Split user input into tokens
        std::vector<std::string> tokens;

        // Display banner and help prompt.
        ioc << ta_bold << "Goldilocks Test Shell" << io_end;
        ioc << "Type \"help\" for a list of commands." << io_end;

        // Display typing prompt.
        ioc << ":" << io_send;
        // Get what the user typed.
        getline(std::cin, buffer);
        // Split the line into space-delimited tokens.
        stdutils::stdsplit(buffer, " ", tokens);

        // Loop while command is not the pseudocommand "exit"...
        while(tokens[0] != "exit")
        {
            if(tokens[0] == "help")
            {
                help();
            }
            else if(tokens[0] == "about")
            {
                if(tokens.size() < 2)
                {
                    ioc << fg_red << ta_bold << cat_error
                        << "ERROR: Not enough arguments." << io_end;
                }
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
                else if(tokens.size() == 3)
                {
                    try
                    {
                        sys->testmanager->i_run_test(tokens[1], std::stoi(tokens[2]));
                    }
                    catch(std::invalid_argument)
                    {
                        ioc << fg_red << ta_bold << cat_error
                        << "ERROR: " << tokens[2] << " is not a valid integer. "
                        << "Please specify a valid number of reptitions for "
                        << "the test." << io_end;
                    }
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

    void GoldilocksShell::help()
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

        ioc << ta_bold << ":test [test] (number)" << io_end;
        ioc << "Runs [test] with (number) repetitions.\n" << io_end;
        ioc << "----" << io_end;

        ioc << "Back to you, Bob!\n" << io_end;
    }

}