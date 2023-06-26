## path::relative
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string relative(const std::filesystem::path& path, const std::filesystem::path& base_path = std::filesystem::current_path()) |

## Parameters
`path` - an existing path \
`base_path` - a path which `path` will be made relative to

## Return Value
Returns a path relative to the base path.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::relative("foo/bar/koo/aid", "foo/bar") << endl;

    return 0;
}
```
Output:
```
koo/aid
```