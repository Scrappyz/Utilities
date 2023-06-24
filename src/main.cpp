#include <iostream>
#include "path.hpp"
#include "print.hpp"

using namespace std;
namespace path = utility::path;
namespace out = utility::print;
namespace fs = std::filesystem;

int main()
{
    string source = path::sourcePath();
    string temp = path::joinPath(source, "temp/tempo/../");
    string temp1 = path::joinPath(source, "tempi/tempo/../");
    string temp2 = path::joinPath(source, "temp/temp1/");
    string temp3 = path::joinPath(source, "temp/my.txt");
    string temp4 = path::joinPath(source, "temp/gg/");
    //path::copy(path::joinPath(source, "temp/temp1/"), path::joinPath(source, "sandbox"));
    cout << temp << endl;
    cout << fs::exists(temp) << endl;
    cout << endl;
    cout << temp1 << endl;
    cout << fs::exists(temp1) << endl;
    cout << endl;
    cout << temp2 << endl;
    cout << fs::exists(temp2) << endl;
    cout << endl;
    cout << temp3 << endl;
    cout << fs::exists(temp3) << endl;
    cout << endl;
    cout << temp4 << endl;
    cout << fs::exists(temp4) << endl;
    return 0;
}