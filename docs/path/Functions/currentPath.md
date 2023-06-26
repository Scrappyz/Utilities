## path::currentPath

| Declarations |
| --- |
| std::string currentPath() |

## Return Value
Returns the absolute path you are currently in.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::currentPath() << endl;

    return 0;
}
```
Output:
```
D:\Documents\Codes\VS Code\C++\Utility
```