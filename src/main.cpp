#include <iostream>
#include "path.hpp"
#include "cli.hpp"
#include "print.hpp"

using namespace std;
namespace out = utility::print;

int main(int argc, char* argv[])
{
    CLI cli;
    try {
        cli.setArguments({"MyProgram", "--flag=value", "fval1", "fval2"});
        cli.setValidFlags({"--flag"});
        out::print(cli.getValueOf("--flag"), '\n');
    } catch(const CLIException& e) {
        cout << e.what() << endl;
    }
    cout << path::sourcePath() << endl;
    
    return 0;
}