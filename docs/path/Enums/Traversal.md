## path::Traversal
Defined in header `path.hpp`

| Members | Description |
| --- | --- |
| NonRecursive | will not traverse subdirectories (default) |
| Recursive | will traverse subdirectories |

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

void traverse(const filesystem::path& path, const path::Traversal& op = path::Traversal::NonRecursive)
{
    if(std::filesystem::exists(path)) {
        for(auto i = std::filesystem::recursive_directory_iterator(path); i != std::filesystem::recursive_directory_iterator(); i++) {
            if(op == path::Traversal::NonRecursive) {
                i.disable_recursion_pending();
            } 
            cout << i->path() << endl;
        }
    } else {
        throw std::runtime_error("[Error][find] Path does not exists");
    }
}

int main()
{
    traverse(path::currentPath());
    cout << "=======================" << endl;
    traverse(path::currentPath(), path::Traversal::Recursive);

    return 0;
}
```
Output:
```
"D:\\Documents\\Codes\\VS Code\\C++\\Utility\\bin\\Debug\\temp"
"D:\\Documents\\Codes\\VS Code\\C++\\Utility\\bin\\Debug\\Utility.exe"
=======================
"D:\\Documents\\Codes\\VS Code\\C++\\Utility\\bin\\Debug\\temp"
"D:\\Documents\\Codes\\VS Code\\C++\\Utility\\bin\\Debug\\temp\\another.txt"
"D:\\Documents\\Codes\\VS Code\\C++\\Utility\\bin\\Debug\\temp\\test.txt"
"D:\\Documents\\Codes\\VS Code\\C++\\Utility\\bin\\Debug\\Utility.exe"
```