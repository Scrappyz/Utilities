## path::isDirectorySeparator
Defined in header `path.hpp`

| Declarations |
| --- |
| bool isDirectorySeparator(char ch) |

## Parameters
`ch` - the character to check

## Return Value
`true` if the character is a directory separator, `false` otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isDirectorySeparator('/') << endl;
    cout << path::isDirectorySeparator('\\') << endl;
    cout << path::isDirectorySeparator('a') << endl;

    return 0;
}
```
Output:
```
1
1
0
```