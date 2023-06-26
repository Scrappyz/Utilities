## path::hasFileExtension
Defined in header `path.hpp`

| Declarations |
| --- |
| bool hasFileExtension(const std::filesystem::path& path) |

## Parameters
`path` - the path or filename to check

## Return Value
`true` if the path or filename has a file extension, `false` otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::hasFileExtension("test.txt") << endl;
    cout << path::hasFileExtension(".git") << endl;
    cout << path::hasFileExtension("a.txt") << endl;
    cout << path::hasFileExtension("test..txt") << endl;
    cout << path::hasFileExtension("test.num.txt") << endl;
    cout << path::hasFileExtension("foo/bar/koo") << endl;
    cout << path::hasFileExtension("foo/bar/koo.cpp") << endl;

    return 0;
}
```
Output:
```
1
0
1
1
1
0
1
```