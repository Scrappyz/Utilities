## path::isDirectory
Defined in header `path.hpp`

| Declarations |
| --- |
| bool isDirectory(const std::filesystem::path& path) |

## Parameters
`path` - the path to check

## Return Value
Returns `true` if the path is a directory, `false` otherwise.

## Notes
- Returns `false` if the directory does not exists.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isDirectory("bin/Debug") << endl; // exists
    cout << path::isDirectory("temp") << endl; // not exists
    cout << path::isDirectory("bin/Debug/temp/test.txt") << endl; // not a directory

    return 0;
}
```
Output:
```
1
0
0
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |
