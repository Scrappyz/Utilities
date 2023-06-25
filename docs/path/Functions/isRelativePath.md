## path::isRelativePath
Defined in `path.hpp`

| Overloads |
| --- |
| bool isRelativePath(const std::filesystem::path& path) |

## Parameters
`path` - the path to check

## Return Value
`true` if the path is relative, `false` otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isRelativePath("bin/debug") << endl;
    cout << path::isRelativePath("D:/bin/debug") << endl;
    return 0;
}
```
Output:
```
1
0
```
