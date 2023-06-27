## path::find
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string find(const std::filesystem::path& search_path, const std::string& file_to_find, const Traversal& pt = Traversal::NonRecursive) |
| std::string find(const std::filesystem::path& search_path, const std::string& file_to_find, int max_depth) |

## Parameters
`search_path` - the path to search \
`file_to_find` - the file to find \
`pt` - the type of traversal to use (see [Traversal](../Enums/Traversal.md)) \
`max_depth` - the max depth to search for the file 

## Return Value
Returns the absolute path of the file if it is found, returns an empty string otherwise.

## Notes
- Returns immediately when the file you are searching is found
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
    |       +-- sub2hello.txt
    |       +-- sub2test.txt
    |       +-- sub3/
    |           +-- sub3hello.txt
    |           +-- sub4/
    |           |   +-- sub4hello.txt
    |           |   +-- sub4test.txt
    |           +-- sub4test.txt
    +-- test.txt
```
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << "\"" << path::find(path::currentPath(), "sub2test.txt") << "\"" << endl; // default to non-recursive
    cout << "\"" << path::find(path::currentPath(), "sub2test.txt", path::Traversal::Recursive) << "\"" << endl;
    cout << "\"" << path::find(path::currentPath(), "sub2test.txt", 1) << "\"" << endl; // can only go as deep as 1 level
    cout << "\"" << path::find(path::currentPath(), "sub2test.txt", 2) << "\"" << endl;
    cout << "\"" << path::find(path::currentPath(), "sub2test.txt", 3) << "\"" << endl;

    return 0;
}
```
Output:
```
""
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2\sub2test.txt"
""
""
"D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\temp\sub1\sub2\sub2test.txt"
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |
| [Traversal](../Enums/Traversal.md) | specifies what type of filesystem traversal to use |