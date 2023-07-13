#include <iostream>
#include "path.hpp"
#include "config.hpp"

using namespace std;

int main()
{
    std::string file_path = path::join(path::sourcePath(), "temp/test.txt");
    Config::modifyValueInFile(file_path, "section 1", "s2", "D:/Docume h Code");
    Config::modifyValueInFile(file_path, "section 1", "s3", "cunn");
    Config::modifyValueInFile(file_path, "nokey", "cookie");
    std::cout << Config::modifyValueInFile(file_path, "s2", "new val") << std::endl;
}