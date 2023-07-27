## Config::addKeyValue
Defined in header `config.hpp`

| |
| --- |
| void addKeyValue(const std::string& new_key, const std::string& new_val) |
| void addKeyValue(const std::string& section, const std::string& new_key, const std::string& new_val) |

Adds a new key with value to an existing section.

## Parameters
`section` - the section to add the key to \
`new_key` - the new key \
`new_val` - the value of the new key

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
    
    std::cout << (config.doesKeyExist("new key") && config.doesKeyHaveValue("new key")) << std::endl;
    config.addKeyValue("new key", "new val");
    std::cout << (config.doesKeyExist("new key") && config.doesKeyHaveValue("new key")) << std::endl;

    return 0;
}
```

Output:
```
0
1
```
