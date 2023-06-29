#include <iostream>
#include "cli.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    CLI cli;
    try {
        cli.setArguments({"MyProgram", "-hmv", "--helpme", "stuff"});
        cli.setValidSubcommands({});
        cli.setValidFlags({"-h", "--help", "-m", "-v", "--helpme"});
        cli.printSubcommandsAndFlags();

        cli.setArguments({"MyProgram", "--help", "--helpme", "stuff"});
        cli.printSubcommandsAndFlags();

        cli.setArguments({"MyProgram", "--helpme", "--help", "stuff"});
        cli.printSubcommandsAndFlags();
    } catch(const CLIException& e) {
        cout << e.what() << endl;
    }
    
    return 0;
}