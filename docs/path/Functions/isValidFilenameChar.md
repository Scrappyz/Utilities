## path::isValidFilenameChar
Defined in header `path.hpp`

| Declarations |
| --- |
| bool isValidFilenameChar(char ch) |

## Parameters
`ch` - the character to check

## Return Value
`true` if the character is usable in filenames, `false` otherwise.

## Example
```
#include <iostream>
#include "path.hpp"

using namespace std;

int main()
{
    cout << path::isValidFilenameChar('<') << endl;
    cout << path::isValidFilenameChar('*') << endl;
    cout << path::isValidFilenameChar('/') << endl;
    cout << path::isValidFilenameChar('\\') << endl;
    cout << path::isValidFilenameChar('a') << endl;

    return 0;
}
```
Output:
```
0
0
0
0
1
```
