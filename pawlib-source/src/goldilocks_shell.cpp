#include "pawlib/goldilocks_shell.hpp"

#define CLI_ARGCHECK(X) \
    if(i+X >= args) \
    { \
        ioc << "ERROR: " << tokens[i] << " requires " << X << " argument(s). " \
            << io_endline << "See --help" << io_end; \
        continue; \
    }

namespace pawlib
{
    int GoldilocksShell::command(int argc_s, char* argv[], unsigned int skip)
    {
        /* The return code; non-zero return codes are needed for failing CI
         * on test failure.
         */
        int r = 0;
        // Whether we've actually loaded something.
        bool loaded = false;

        // Convert our signed integer to unsigned.
        unsigned int argc = static_cast<unsigned int>(argc_s);

        // We are using std::string for the time being.
        std::vector<std::string> tokens;

        // If we have insufficient arguments to do anything...
        if(argc <= skip + 1)
        {
            return 0;
        }

        /* Parse through the arguments from the command line.
         * skipping the first element (the program invocation)
         * and any arguments we've been asked to skip.
         */
        for(unsigned int i = (1 + skip); i < argc; ++i)
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

        // The number of arguments we can actually work with. 1 based.
        unsigned int args = argc - (skip+1);

        // Loop thorugh each token...
        for(unsigned int i = 0; i < args; ++i)
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
                ioc << "    --run [item]    | Run the test or suite [item]. "  << io_endline;
                ioc << "    --benchmark [item]    | Runs the benchmark for [item]. " << io_endline;
                ioc << io_end;
            }
            // If load flag and subsequent argument are provided...
            else if(tokens[i] == "--load")
            {
                CLI_ARGCHECK(1);

                // If load succeeds, set the return code to 0, else 1 (error).
                r = this->testmanager->load_suite(tokens[++i]) ? 0 : 1;

                loaded = true;
            }
            // If list flag is provided...
            else if(tokens[i] == "--list")
            {
                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    this->testmanager->load_suite();
                    loaded = true;
                }

                // List all loaded tests.
                this->testmanager->list_tests(true);
            }
            // If listsuites flag is provided...
            else if(tokens[i] == "--listsuites")
            {
                // List all suites.
                this->testmanager->list_suites(true);
            }
            // If suite flag and subsequent argument are provided...
            else if(tokens[i] == "--suite")
            {
                CLI_ARGCHECK(1);

                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    this->testmanager->load_suite();
                    loaded = true;
                }

                // If run_suite succeeds, set the return code to 0, else 1 (error).
                r = this->testmanager->run_suite(tokens[++i]) ? 0 : 1;
            }
            // If test flag and subsequent argument are provided...
            else if(tokens[i] == "--test")
            {
                CLI_ARGCHECK(1);

                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    this->testmanager->load_suite();
                    loaded = true;
                }

                // If run_test succeeds, set the return code to 0, else 1 (error).
                r = this->testmanager->run_test(tokens[++i]) ? 0 : 1;
            }
            // If run flag and subsequent argument are provided...
            else if(tokens[i] == "--run")
            {
                CLI_ARGCHECK(1);

                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    this->testmanager->load_suite();
                    loaded = true;
                }

                // If run item succeeds, set the return code to 0, else 1 (error).
                r = this->testmanager->run(tokens[++i]) ? 0 : 1;
            }
            // If benchmark flag and subsequent argument are provided...
            else if(tokens[i] == "--benchmark")
            {
                CLI_ARGCHECK(1);

                // If nothing is loaded, load all the suites first.
                if(!loaded)
                {
                    this->testmanager->load_suite();
                    loaded = true;
                }

                /* If the focus test (A) beats its comparative, or the test is
                 * a dead heat, return success (0). Otherwise, return failure
                 * (1). We run with 100 iterations, print out advanced
                 * stats, and allow dead heat to count as success.
                 */
                r = this->testmanager->run_benchmark(tokens[++i], 100, true, true) ? 0 : 1;
            }
            // If the token is invalid...
            else
            {
                // Throw error and help prompt.
                ioc << "ERROR: Invalid command " << tokens[i] << io_endline;
                ioc << "See --help" << io_end;
            }

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

    void GoldilocksShell::interactive()
    {
        // Store user input.
        std::string buffer;
        // Split user input into tokens
        std::vector<std::string> tokens;

        // Display banner and help prompt.
        ioc << ta_bold << "Goldilocks Test Shell" << io_end;
        ioc << "Type 'help' for a list of commands." << io_end;

        // Display typing prompt.
        ioc << this->prompt << io_send;
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
                about(tokens);
            }
            else if(tokens[0] == "bench")
            {
                benchmark(tokens);
            }
            else if(tokens[0] == "benchmark")
            {
                benchmark(tokens);
            }
            else if(tokens[0] == "compare")
            {
                compare(tokens);
            }
            else if(tokens[0] == "list")
            {
                list(tokens);
            }
            else if(tokens[0] == "listsuites")
            {
                listsuites(tokens);
            }
            else if(tokens[0] == "load")
            {
                load(tokens);
            }
            else if(tokens[0] == "run")
            {
                run(tokens);
            }
            else if(tokens[0] == "suite")
            {
                ioc << fg_yellow << ta_bold << cat_warning
                << "[Deprecated] Use 'run [suite]' instead."
                << io_end;
                run(tokens);
            }
            else if(tokens[0] == "test")
            {
                ioc << fg_yellow << ta_bold << cat_warning
                    << "[Deprecated] Use 'run [test] (number)' instead."
                    << io_end;
                run(tokens);
            }
            else
            {
                ioc << ta_bold << cat_warning
                    << "Unrecognized command. Type 'help' for help." << io_end;
            }

            // Get more user input...
            // Clear the tokens vector to make room for new results.
            tokens.clear();
            // Display the prompt.
            ioc << this->prompt << io_send;
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

        ioc << ta_bold << this->prompt << "about [test]" << io_end;
        ioc << "Display the documentation for [test].\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "benchmark [test] (number)" << io_end;
        ioc << "Runs a benchmark on [test] with (number) repetitions.\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "compare [test1] [test2] (number)" << io_end;
        ioc << "Runs a comparative benchmark between [test1] and [test2] with (number) reps.\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "help" << io_end;
        ioc << "Displays the help screen.\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "list" << io_end;
        ioc << "Displays the available tests.\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "listsuites" << io_end;
        ioc << "Displays the available suites.\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "load" << io_end;
        ioc << "Loads all suites.\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "load [suite]" << io_end;
        ioc << "Loads the tests from [suite].\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "run [suite]" << io_end;
        ioc << "Runs all tests in [suite].\n" << io_end;
        ioc << "----" << io_end;

        ioc << ta_bold << this->prompt << "run [test] (number)" << io_end;
        ioc << "Runs [test] with (number) repetitions.\n" << io_end;
        ioc << "----" << io_end;

        ioc << "Back to you, Bob!\n" << io_end;
    }

    void GoldilocksShell::about(stringvector& tokens)
    {
        if(validate_arguments(tokens, 1))
        {
            this->testmanager->show_docs(tokens[1]);
        }
    }

    void GoldilocksShell::benchmark(stringvector& tokens)
    {
        uint8_t args = validate_arguments(tokens, 1, 2);

        if(args == 1)
        {
            this->testmanager->i_run_benchmark(tokens[1]);
        }
        else if(args == 2)
        {
            try
            {
                this->testmanager->i_run_benchmark(tokens[1], std::stoi(tokens[2]));
            }
            catch(std::invalid_argument)
            {
                ioc << fg_red << ta_bold << cat_error
                << "ERROR: " << tokens[2] << " is not a valid integer. "
                << "Please specify a valid number of reptitions for "
                << "the benchmark." << io_end;
            }
        }
    }

    void GoldilocksShell::compare(stringvector& tokens)
    {
        uint8_t args = validate_arguments(tokens, 2, 3);

        if(args == 2)
        {
            this->testmanager->i_run_compare(tokens[1], tokens[2]);
        }
        else if(args == 3)
        {
            try
            {
                this->testmanager->i_run_compare(tokens[1], tokens[2], std::stoi(tokens[3]));
            }
            catch(std::invalid_argument)
            {
                ioc << fg_red << ta_bold << cat_error
                << "ERROR: " << tokens[3] << " is not a valid integer. "
                << "Please specify a valid number of reptitions for "
                << "the benchmark." << io_end;
            }
        }
    }

    void GoldilocksShell::list(stringvector& tokens)
    {
        if(validate_arguments(tokens, 0) == 0)
        {
            this->testmanager->list_tests(true);
        }
    }

    void GoldilocksShell::listsuites(stringvector& tokens)
    {
        if(validate_arguments(tokens, 0) == 0)
        {
            this->testmanager->list_suites(true);
        }
    }

    void GoldilocksShell::load(stringvector& tokens)
    {
        uint8_t args = validate_arguments(tokens, 0, 1);

        if(args == 0)
        {
            // If we got no arguments, interactively load all suites.
            this->testmanager->i_load_suite();
        }
        else if(args == 1)
        {
            this->testmanager->load_suite(tokens[1]);
        }
    }

    void GoldilocksShell::run(stringvector& tokens)
    {
        uint8_t args = validate_arguments(tokens, 1, 2);

        if(args == 1)
        {
            this->testmanager->i_run(tokens[1]);
        }
        else if(args == 2)
        {
            try
            {
                this->testmanager->i_run(tokens[1], std::stoi(tokens[2]));
            }
            catch(std::invalid_argument)
            {
                ioc << fg_red << ta_bold << cat_error
                << "ERROR: " << tokens[2] << " is not a valid integer. "
                << "Please specify a valid number of reptitions for "
                << "the test." << io_end;
            }
        }
    }

    uint8_t GoldilocksShell::validate_arguments(stringvector& tokens,
        uint8_t min, uint8_t max)
    {
        // If the maximum value is undefined, set it to min.
        if(!max)
        {
            max = min;
        }

        // Get the arg count, offset to not count the command (first token)
        uint8_t args = tokens.size() - 1;

        // If there are not enough arguments, throw error and return 0.
        if(args < min)
        {
            ioc << fg_red << ta_bold << cat_error
                << "ERROR: Not enough arguments." << io_end;
            return 0;
        }
        // Else if there are too many arguments, throw error and return 0.
        else if(args > max)
        {
            ioc << fg_red << ta_bold << cat_error
                << "ERROR: Too many arguments." << io_end;
            return 0;
        }

        // If we get this far, there's no error; return the argument count.
        return args;
    }


}