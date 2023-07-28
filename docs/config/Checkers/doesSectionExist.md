## Config::doesSectionExist
Defined in header `config.hpp`

| |
| --- |
| bool doesSectionExist(const std::string& section) |

## Parameters
`section` - the section to check

## Return Value
Returns `true` if the section exists, `false` otherwise

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    std::string path = "config.txt";
    Config config(path);
    
    std::cout << config.doesSectionExist("new section") << std::endl;
    config.addSection("new section");
    std::cout << config.doesSectionExist("new section") << std::endl;
    return 0;
}
```

Output:
```
0
1
```