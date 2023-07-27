## Config::addKey
Defined in header `config.hpp`

| |
| --- |
| void addKey(const std::string& new_key) |
| void addKey(const std::string& section, const std::string& new_key) |

Adds a new key to an existing section.

## Parameters
`section` - the section to add the new key to \
`new_key` - the key to add

## Notes
- If not section is provided, the key will be added to the empty section

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    std::string path = "config.txt";
    Config config(path);
    
    std::cout << config.doesKeyExist("new key") << std::endl;
    config.addKey("new key");
    std::cout << config.doesKeyExist("new key") << std::endl;
    return 0;
}
```

Output:
```
0
1
```
