## Config::isEmpty
Defined in header `config.hpp`

| |
| --- |
| bool isEmpty() |

Checks if the `Config` object is empty. Can be used to check if the `Config` object has been initialized.

## Return Value
Returns `true` if empty, `false` otherwise.

## Example
```
#include <iostream>
#include "config.hpp"

int main()
{
    Config config;
    std::cout << config.isEmpty() << std::endl;
    config.addKey("some key");
    std::cout << config.isEmpty() << std::endl;
    
    return 0;
}
```

Output:
```
1
0
```