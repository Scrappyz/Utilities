#include <iostream>
#include "path.hpp"
#include "print.hpp"

using namespace std;
namespace path = utility::path;
namespace out = utility::print;
namespace fs = std::filesystem;

string joinPathString(const fs::path& p1, const fs::path& p2)
{
    return fs::weakly_canonical(p1 / p2).string();
}

int main()
{
    string source = path::sourcePath();
    string temp = joinPathString(source, "temp/tempo/../");
    string temp1 = joinPathString(source, "tempi/tempo/../");
    string temp2 = joinPathString(source, "temp/temp1/");
    string temp3 = joinPathString(source, "temp/my.txt");
    string temp4 = joinPathString(source, "temp/gg/");
    string temp5 = joinPathString(source, "temp/gg.txt/");
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
    cout << endl;
    cout << temp5 << endl;
    cout << fs::exists(temp5) << endl;

    cout << "===========================" << endl;
    cout << path::joinPath(source, "temp/tempo/..") << endl;
    cout << path::joinPath(source, "tempi/tempo/../") << endl;
    cout << path::joinPath(source, "temp/temp1/") << endl;
    cout << path::joinPath(source, "temp/my.txt") << endl;
    cout << path::joinPath(source, "temp/gg/") << endl;
    cout << path::joinPath(source, "temp/gg.txt") << endl;
    cout << endl;
    cout << fs::path("..").filename() << endl;
    cout << fs::path("../..").filename() << endl;
    cout << fs::path("../../").filename() << endl;
    return 0;
}