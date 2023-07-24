## path::absolutePath
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string absolutePath(const std::filesystem::path& path) |

## Parameters
`path` - the path to compose an absolute path for

## Return Value
Returns the absolute path of a given relative path.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::absolutePath("foo/bar") << endl;

    return 0;
}
```
Output:
```
D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\foo\bar
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |