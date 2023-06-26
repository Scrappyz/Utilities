## path::absolute
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string absolute(const std::filesystem::path& path) |

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
    cout << path::absolute("foo/bar") << endl;

    return 0;
}
```
Output:
```
D:\Documents\Codes\VS Code\C++\Utility\bin\Debug\foo\bar
```