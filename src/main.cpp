#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::joinPath("a/b/c/d", "e/f/g") << endl;
    cout << path::joinPath("a/b/c/d", "e/f/g/") << endl; // separator at the end will be preserved
    cout << path::joinPath("a/b/c/d", "../..") << endl;
    cout << path::joinPath("a/b/c/d", "../../") << endl; // separator at the end will be preserved
    cout << path::joinPath({"a/b/c/d", "../..", "e/f/g", "h/i/.."}) << endl;
    cout << path::joinPath({"a/b/c/d", "../..", "e/f/g", "h/i/../"}) << endl; // preserve end separator

    return 0;
}