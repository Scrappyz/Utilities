## path::filename
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string filename(const std::filesystem::path& path) |

## Parameters
`path` - the path to extract the filename from

## Return Value
Returns the filename of a given path.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::filename("foo/bar/koo") << endl;
    cout << path::filename("foo/bar/koolaid/") << endl;
    cout << path::filename("foo/bar/koo.cpp") << endl;
    cout << path::filename("foo") << endl;

    return 0;
}
```
Output:
```
koo
koolaid
koo.cpp
foo
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |