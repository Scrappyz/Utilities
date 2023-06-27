## path::rename
Defined in header `path.hpp`

| Declarations |
| --- |
| void rename(const std::filesystem::path& path, const std::string& new_name) |

## Parameters
`path` - the file/directory to rename
`new_name` - the name to be given

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    path::rename("temp/temp.txt", "hello.txt");

    return 0;
}
```
Before running code:
```
Debug/
+-- temp/
    +-- temp.txt
    +-- test.txt
```
After running code:
```
Debug/
+-- temp/
    +-- hello.txt
    +-- test.txt
```

## References
| | |
| --- | --- |
| [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) | represents a path |