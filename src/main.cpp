#include <iostream>
#include "cli.hpp"
#include "print.hpp"

using namespace std;
namespace out = utility::print;

int main(int argc, char* argv[])
{
    CLI cli(argc, argv);
    try {
        cli.setArguments({"MyProgram", "remote", "add", "stuff", "shit"});
        // declare the available subcommands in your program
        cli.setValidSubcommands({"add", "status", "remote add"});

        // declare the available flags for each subcommand
        cli.setValidFlags({"-h", "--help"}); // declare flag for empty subcommand
        cli.setValidFlags("add", {"-h", "--help", "--path"});
        cli.setValidFlags("status", {"-h", "--help", "-v", "--verbose"});
        cli.setValidFlags("remote add", {"-f", "--fetch", "--tags"});

        string subcmd = cli.getActiveSubcommand(); // the current subcommand
        vector<string> values; // will hold the values of flags or the active subcommand
        values = cli.getValueOf(1);
        out::print(values);
    } catch(const CLIException& e) {
        cout << e.what() << endl;
        return 1;
    }
    
    return 0;
}