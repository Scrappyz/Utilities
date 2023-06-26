## path::findAll
Defined in header `path.hpp`

| Declarations |
| --- |
| std::vector&lt;std::string> findAll(const std::filesystem::path& search_path, const std::string& file_to_find, const Traversal& pt = Traversal::NonRecursive) |
| std::vector&lt;std::string> findAll(const std::filesystem::path& search_path, const std::string& file_to_find, int max_depth) |

## Parameter
`search_path` - the path to search \
`file_to_find` - the file to find \
`pt` - the type of traversal to use \
`max_depth` - the max depth to search for the file 

## Return Value
Returns a vector of absolute paths of the file you are trying to find, returns an empty vector if none is found.

## Notes
- Depth starts at `0` where `0` is the directory of the `search_path`

## Example
File tree:
```
Debug/
+-- temp/
    +-- hello.txt
    +-- sub1/
    |   +-- sub1hello.txt
    |   +-- sub1test.txt
    |   +-- sub2/
    |   |   +-- sub2hello.txt
    |   |   +-- sub2test.txt
    |   |   +-- sub3/
    |   |       +-- sub2test.txt
    |   |       +-- sub3hello.txt
    |   |       +-- sub4/
    |   |       |   +-- sub4hello.txt
    |   |       |   +-- sub4test.txt
    |   |       +-- sub4test.txt
    |   +-- sub2test.txt
    +-- sub2test.txt
    +-- test.txt
```
```
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
    printVector(path::findAll(path::currentPath(), "sub2test.txt")); // default to non-recursive
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", path::Traversal::Recursive));
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", 1)); // can only go as deep as 1 level
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", 2));
    cout << "=====================================================" << endl;
    printVector(path::findAll(path::currentPath(), "sub2test.txt", 3));

    return 0;
}
```
Output:
```
EMPTY
=====================================================
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2\sub2test.txt"
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2\sub3\sub2test.txt"
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2test.txt"
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub2test.txt"
=====================================================
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub2test.txt"
=====================================================
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2test.txt"
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub2test.txt"
=====================================================
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2\sub2test.txt"
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2test.txt"
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub2test.txt"
```