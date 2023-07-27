## Config::modifySectionName
Defined in header `config.hpp`

| |
| --- |
| void modifySectionName(const std::string& section, const std::string& new_section) |

Modify the name of a section.

## Parameters
`section` - the section to rename \
`new_section` - the new name

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    std::string path = "config.txt";
    Config config(path);
    
    config.addSection("new section");
    std::cout << config.doesSectionExist("new section") << std::endl;
    std::cout << config.doesSectionExist("renamed section") << std::endl;
    config.modifySectionName("new section", "renamed section");
    std::cout << config.doesSectionExist("new section") << std::endl;
    std::cout << config.doesSectionExist("renamed section") << std::endl;

    return 0;
}
```

Output:
```
1
0
0
1
```