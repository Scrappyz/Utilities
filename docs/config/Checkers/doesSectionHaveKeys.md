## Config::doesSectionHaveKeys
Defined in header `config.hpp`

| |
| --- |
| bool doesSectionHaveKeys(const std::string& section = "") |

Checks if the section contains any keys.

## Parameters
`section` - the section to check

## Return Value
Returns `true` if the given section has any keys, `false` otherwise.

## Notes
- Providing no arguments will check if there are keys in the empty section

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    Config config;
    std::cout << config.doesSectionHaveKeys() << std::endl; // no keys
    config.addKey("key1"); // add a key called "key1"
    std::cout << config.doesSectionHaveKeys() << std::endl; // now has keys

    config.addSection("section"); // add new section called "section"
    std::cout << config.doesSectionHaveKeys("section") << std::endl; // no keys
    config.addKey("section", "new key"); // add new key to "section"
    std::cout << config.doesSectionHaveKeys("section") << std::endl; // now has keys
    
    return 0;
}
```

Output:
```
0
1
0
1
```