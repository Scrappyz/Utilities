#include <iostream>
#include "path.hpp"

using namespace std;

void printVector(const vector<string>& v)
{
    if(v.empty()) {
        cout << "EMPTY" << endl;
        return;
    }
    for(int i = 0; i < v.size(); i++) {
        cout << "\"" << v[i] << "\"" << endl; 
    }
}

int main()
{
<<<<<<< HEAD
    cout << path::isFile("bin/Debug/temp/test.txt") << endl; // exists
    cout << path::isFile("bin/Debug/temp/tt.txt") << endl; // not exists
    cout << path::isFile("bin/Debug") << endl; // not a file
=======
    printVector(path::findAll(path::currentPath(), "sub2test.txt")); // default to non-recursive
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", path::Traversal::Recursive));
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", 1)); // can only go as deep as 1 level
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", 2));
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", 3));
>>>>>>> C++-dev

    return 0;
}