## path::isAbsolutePath
Defined in header `path.hpp`

| Declarations |
| --- |
| bool isAbsolutePath(const std::filesystem::path& path) |

## Parameters
`path` - the path to check

## Return Value
`true` if the path is an absolute path, `false` otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isAbsolutePath("bin/debug") << endl;
    cout << path::isAbsolutePath("D:/bin/debug") << endl;
    return 0;
}
```
Output:
```
0
1
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |