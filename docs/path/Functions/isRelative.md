## path::isRelative
Defined in `path.hpp`

| Declarations |
| --- |
| bool isRelative(const std::filesystem::path& path) |

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
    cout << path::isRelative("bin/debug") << endl;
    cout << path::isRelative("D:/bin/debug") << endl;
    return 0;
}
```
Output:
```
1
0
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |
