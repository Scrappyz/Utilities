#include <iostream>
#include "cli.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    CLI cli;
    try {
        cli.setValidSubcommands({"stuff", "ei"});
        cli.setArguments({"MyProgram", "-hmv", "--help", "stuff"});
        cli.setValidSubcommands({});
        cli.setValidFlags({"-h", "--help", "-m", "-v"});
        cli.printSubcommandsAndFlags();
    } catch(const CLIException& e) {
        cout << e.what() << endl;
    }
    
    return 0;
}