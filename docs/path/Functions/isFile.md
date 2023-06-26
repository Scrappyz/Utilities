## path::isFile
Defined in header `path.hpp`

| Declarations |
| --- |
| bool isFile(const std::filesystem::path& path) |

## Parameters
`path` - the path to check

## Return Value
Returns `true` if the path is a file, `false` otherwise.

## Notes
- Returns `false` if the path does not exists.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isFile("bin/Debug/temp/test.txt") << endl; // exists
    cout << path::isFile("bin/Debug/temp/tt.txt") << endl; // not exists
    cout << path::isFile("bin/Debug") << endl; // not a file

    return 0;
}
```
Output:
```
1
0
0
```