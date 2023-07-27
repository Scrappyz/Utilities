## Config::modifyKeyValue
Defined in header `config.hpp`

| |
| --- |
| void modifyKeyValue(const std::string& key, const std::string& new_val) |
| void modifyKeyValue(const std::string& section, const std::string& key, const std::string& new_val) |

Changes the value of the given key in the given section.

## Paramters
`section` - the section of the key
`key` - the key to modify the value of
`new_val` - the new value

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    std::string path = "config.txt";
    Config config(path);
    
    config.addKeyValue("new key", "new value");
    std::cout << config.getValue("new key") << std::endl;
    config.modifyKeyValue("new key", "cool value");
    std::cout << config.getValue("new key") << std::endl;
    
    return 0;
}
```

Output:
```
new value
cool value
```