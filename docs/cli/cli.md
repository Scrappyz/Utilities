## CLI Library
The CLI is a command-line parsing library that aims to simplify the development of console apps.

## Minimum C++ Version
- [C++11](https://en.cppreference.com/w/cpp/11)

## Includes
- [\<iostream>](https://en.cppreference.com/w/cpp/header/iostream)
- [\<vector>](https://en.cppreference.com/w/cpp/container/vector)
- [\<unordered_set>](https://en.cppreference.com/w/cpp/header/unordered_set)
- [\<unordered_map>](https://en.cppreference.com/w/cpp/header/unordered_map)

## Classes
Defined in header `cli.hpp`
| | |
| --- | --- |
| [CLI](Classes/CLI/CLI.md) | class to use to parse command-line arguments |
| [CLIException](Classes/CLIExeption/CLIException.md) | custom exception for CLI class |

## Usage
```
#include <iostream>
#include "cli.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    CLI cli(argc, argv);
    try {
        // declare the available subcommands in your program
        cli.setValidSubcommands({"add", "status", "remote add"});

        // declare the available flags for each subcommand
        cli.setValidFlags({"-h", "--help"}); // declare flag for empty subcommand
        cli.setValidFlags("add", {"-h", "--help", "--path"});
        cli.setValidFlags("status", {"-h", "--help", "-v", "--verbose"});
        cli.setValidFlags("remote add", {"-f", "--fetch", "--tags"});

        string subcmd = cli.getActiveSubcommand(); // the current subcommand
        vector<string> values; // will hold the values of flags or the active subcommand
        if(subcmd.empty()) {
            // do stuff with empty subcommand
            if(cli.isFlagActive("-h") || cli.isFlagActive("--help")) {
                // do stuff with the "-h" and "--help" flag
            }   
        } else if(subcmd == "add") {
            // do stuff with "add" subcommand
            if(cli.isFlagActive("--path")) {
                // do stuff with the "--path" flag

                // get the value of the "--path" flag and limit it to 1
                values = cli.getValueOf("--path", 1); 

                // do stuff with the value
            }
        } else if(subcmd == "status") {
            // do stuff with "status" subcommand
            if(cli.isFlagActive("-v") || cli.isFlagActive("--verbose")) {
                // do stuff with the "verbose" flag
            }
        } else if(subcmd == "remote add") {
            // do stuff with "remote add" subcommand
            if(cli.isFlagActive("-f") || cli.isFlagActive("--fetch")) {
                // do stuff with "fetch" flag

                // get the values of "-f" or "--fetch", whichever comes first
                values = cli.getValueOf({"-f", "--fetch"});

                // do stuff with values
            }
        }
    } catch(const CLIException& e) {
        cout << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```