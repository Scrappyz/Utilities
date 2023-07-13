#include <iostream>
#include "path.hpp"
#include "config.hpp"

using namespace std;

int main()
{
    std::string file_path = path::join(path::sourcePath(), "temp/test.txt");
    Config::modifyValueInFile(file_path, "nokey1", "fuck");
}