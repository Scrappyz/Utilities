## Config::removeSection
Defined in header `config.hpp`

| |
| --- |
| void removeSection(const std::string& section) |

Removes an existing section.

## Parameters
`section` - the section to remove

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
    config.removeSection("new section");
    std::cout << config.doesSectionExist("new section") << std::endl;

    return 0;
}
```
Output:
```
0
1
0
```