## path::exists
Defined in header `path.hpp`

| Overloads |
| --- |
| bool exists(const std::filesystem& path) |

## Parameters
`path` - the path to check

## Return Value
`true` if the given path exists in the file system, `false` otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    string p1 = "this/path/exists";
    string p2 = "this/path/does/not/exists";
    cout << path::exists(p1) << endl;
    cout << path::exists(p2) << endl;
    
    return 0;
}
```
Output:
```
1
0
```