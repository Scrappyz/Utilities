## path::remove
Defined in header `path.hpp`

| |
| --- |
| void remove(const std::filesystem::path& path) |

Deletes a path.

## Parameters
`path` - the path to delete

## Example
```
#include <iostream>
#include "path.hpp"

int main()
{
    std::string path = path::joinPath(path::sourcePath(), "test");
    path::remove(path);
    
    return 0;
}
```

Before:
```
source
|-- test
|-- temp.txt
```

After:
```
source
|-- temp.txt
```