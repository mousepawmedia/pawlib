#include "pawlib/goldilocks_shell.hpp"

#define CLI_ARGCHECK(X) \
    if(i+X >= args) \
    { \
        ioc << "ERROR: " << tokens[i] << " requires " << X << " argument(s). " \
            << IOCtrl::n << "See --help" << IOCtrl::endl; \
        continue; \
    }

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
            ioc << "Usage: ./pawlib-tester [command] [argument]" << IOCtrl::n;
            ioc << "    --help          | Show this screen. "  << IOCtrl::n;
            ioc << "    --list          | List all tests. "  << IOCtrl::n;
            ioc << "    --listsuites    | List all suites. "  << IOCtrl::n;
            ioc << "    --load [suite]  | Load the suite [suite]. "
                << "If unspecified, all suites will be loaded." << IOCtrl::n;
            ioc << "    --run [item]    | Run the test or suite [item]. "  << IOCtrl::n;
            ioc << "    --benchmark [item]    | Runs the benchmark for [item]. " << IOCtrl::n;
            ioc << IOCtrl::endl;
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
            ioc << "ERROR: Invalid command " << tokens[i] << IOCtrl::n;
            ioc << "See --help" << IOCtrl::endl;
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
    ioc << IOFormatTextAttr::bold << "Goldilocks Test Shell" << IOCtrl::endl;
    ioc << "Type 'help' for a list of commands." << IOCtrl::endl;

    // Display typing prompt.
    ioc << this->prompt << IOCtrl::end;
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
            ioc << IOFormatTextFG::yellow << IOFormatTextAttr::bold << IOCat::warning
            << "[Deprecated] Use 'run [suite]' instead."
            << IOCtrl::endl;
            run(tokens);
        }
        else if(tokens[0] == "test")
        {
            ioc << IOFormatTextFG::yellow << IOFormatTextAttr::bold << IOCat::warning
                << "[Deprecated] Use 'run [test] (number)' instead."
                << IOCtrl::endl;
            run(tokens);
        }
        else
        {
            ioc << IOFormatTextAttr::bold << IOCat::warning
                << "Unrecognized command. Type 'help' for help." << IOCtrl::endl;
        }

        // Get more user input...
        // Clear the tokens vector to make room for new results.
        tokens.clear();
        // Display the prompt.
        ioc << this->prompt << IOCtrl::end;
        // Get the line the user just typed.
        getline(std::cin, buffer);
        // Split the line into space-delimited tokens.
        stdutils::stdsplit(buffer, " ", tokens);
    }
    // Once the command (first token) is "exit", we quit.
}

void GoldilocksShell::help()
{
    ioc << "-- HELP --" << IOCtrl::endl;
    ioc << "[SYNTAX: command [required param] (optional param)\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "about [test]" << IOCtrl::endl;
    ioc << "Display the documentation for [test].\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "benchmark [test] (number)" << IOCtrl::endl;
    ioc << "Runs a benchmark on [test] with (number) repetitions.\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "compare [test1] [test2] (number)" << IOCtrl::endl;
    ioc << "Runs a comparative benchmark between [test1] and [test2] with (number) reps.\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "help" << IOCtrl::endl;
    ioc << "Displays the help screen.\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "list" << IOCtrl::endl;
    ioc << "Displays the available tests.\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "listsuites" << IOCtrl::endl;
    ioc << "Displays the available suites.\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "load" << IOCtrl::endl;
    ioc << "Loads all suites.\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "load [suite]" << IOCtrl::endl;
    ioc << "Loads the tests from [suite].\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "run [suite]" << IOCtrl::endl;
    ioc << "Runs all tests in [suite].\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << IOFormatTextAttr::bold << this->prompt << "run [test] (number)" << IOCtrl::endl;
    ioc << "Runs [test] with (number) repetitions.\n" << IOCtrl::endl;
    ioc << "----" << IOCtrl::endl;

    ioc << "Back to you, Bob!\n" << IOCtrl::endl;
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
        catch(const std::invalid_argument&)
        {
            ioc << IOFormatTextFG::red << IOFormatTextAttr::bold << IOCat::error
            << "ERROR: " << tokens[2] << " is not a valid integer. "
            << "Please specify a valid number of reptitions for "
            << "the benchmark." << IOCtrl::endl;
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
        catch(const std::invalid_argument&)
        {
            ioc << IOFormatTextFG::red << IOFormatTextAttr::bold << IOCat::error
            << "ERROR: " << tokens[3] << " is not a valid integer. "
            << "Please specify a valid number of reptitions for "
            << "the benchmark." << IOCtrl::endl;
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
        catch(const std::invalid_argument&)
        {
            ioc << IOFormatTextFG::red << IOFormatTextAttr::bold << IOCat::error
            << "ERROR: " << tokens[2] << " is not a valid integer. "
            << "Please specify a valid number of reptitions for "
            << "the test." << IOCtrl::endl;
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
        ioc << IOFormatTextFG::red << IOFormatTextAttr::bold << IOCat::error
            << "ERROR: Not enough arguments." << IOCtrl::endl;
        return 0;
    }
    // Else if there are too many arguments, throw error and return 0.
    else if(args > max)
    {
        ioc << IOFormatTextFG::red << IOFormatTextAttr::bold << IOCat::error
            << "ERROR: Too many arguments." << IOCtrl::endl;
        return 0;
    }

    // If we get this far, there's no error; return the argument count.
    return args;
}
