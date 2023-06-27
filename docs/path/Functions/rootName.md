## path::rootName
Defined in header `path.hpp`

| Declarations |
| --- |
| std::string rootName(const std::filesystem::path& path) |

## Parameters
`path` - the path to extract the root name from 

## Return Value
Returns the name of the root or drive if the path exists, returns an empty string otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << "\"" << path::rootName("temp") << "\"" << endl;
    cout << "\"" << path::rootName(path::sourcePath()) << "\"" << endl;

    return 0;
}
```
Output:
```
""
"D:"
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |
