## Config::addSection
Defined in header `config.hpp`

| |
| --- |
| void addSection(const std::string& new_section) |

Adds a new section.

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