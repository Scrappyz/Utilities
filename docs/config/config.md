## Config Library
The config library is a config file parser in C++ that aims to simplify the process of the reading and writing of configuration files.

## Dependencies
### Minimum C++ Version
- [C++11](https://en.cppreference.com/w/cpp/11)

### Includes
- [\<string>](https://en.cppreference.com/w/cpp/string/basic_string)
- [\<vector>](https://en.cppreference.com/w/cpp/container/vector)
- [\<unordered_map>](https://en.cppreference.com/w/cpp/container/unordered_map)
- [\<fstream>](https://en.cppreference.com/w/cpp/io/basic_fstream)

## Installation
1. Download [config.hpp](../../include/config.hpp)
2. Include `config.hpp` in your project

## Format
The config library is capable of parsing files that can be read in plain text such as `txt` files. It can parse plain text that follows this format:
```
# Comment
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "val 4"
"key 5" = "val 5"

[Section 1]
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "val 4"
"key 5" = "val 5"

[Section 2]
key1=val1
key2 = val2   # some commment
"key 3" = val3
key4 = "val 4"
"key 5" = "val 5"
```
Each group of keys can be divided into sections and each key can be assigned a value with the `=` symbol.

## Usage
### Initializing
```
#include <iostream>
#include "config.hpp"

using namespace std;

int main()
{
    std::string config_path = "config.txt";
    Config config(config_path); // initialize config with the contents of "config.txt"

    return 0;
}
```
Using a file with the format like in the [format](#format) section, we initialize the `Config` object by passing in the path to the configuration file. Initializing the `Config` file is only optional. If you want to use the `Config` object immediately, you can do so.

### Modifying
```
#include <iostream>
#include "config.hpp"

int main()
{
    Config config;

    // add new key with the name "main key" with a value of "main val"
    config.addKeyValue("main key", "main val");

    // add new key with the name "dir" with a value of "my/path/to/file"
    config.addKeyValue("dir", "my/path/to/file");

    // add new section called "section 1"
    config.addSection("section 1");

    // add a new key called "secKey" with a value of "secVal" in "section 1"
    config.addKeyValue("section 1", "secKey", "secVal");
    
    // add more keys to "section 1"
    config.addKeyValue("section 1", "secKey2", "secVal2");
    config.addKeyValue("section 1", "secKey3", "secVal3");

    // modify the value of "secKey2" in "section 1" to "wassup"
    config.modifyKeyValue("section 1", "secKey2", "wassup");

    // modify the name of "secKey3" to "hello"
    config.modifyKeyName("section 1", "secKey3", "hello");

    // delete key "secKey" from "section 1"
    config.removeKey("section 1", "secKey");

    // add another section called "section 2"
    config.addSection("section 2");

    // add a key with no value to "section 2"
    config.addKey("section 2", "noval");

    // rename "section 2" to "new section"
    config.modifySectionName("section 2", "new section");

    return 0;
}
```
We can modify the `Config` object by using its `add`, `remove`, and `modify` methods.

### Saving
```
#include <iostream>
#include "config.hpp"

int main()
{
    Config config;

    // add new key with the name "main key" with a value of "main val"
    config.addKeyValue("main key", "main val");

    // add new key with the name "dir" with a value of "my/path/to/file"
    config.addKeyValue("dir", "my/path/to/file");

    // add new section called "section 1"
    config.addSection("section 1");

    // add a new key called "secKey" with a value of "secVal" in "section 1"
    config.addKeyValue("section 1", "secKey", "secVal");
    
    // add more keys to "section 1"
    config.addKeyValue("section 1", "secKey2", "secVal2");
    config.addKeyValue("section 1", "secKey3", "secVal3");

    // modify the value of "secKey2" in "section 1" to "wassup"
    config.modifyKeyValue("section 1", "secKey2", "wassup");

    // modify the name of "secKey3" to "hello"
    config.modifyKeyName("section 1", "secKey3", "hello");

    // delete key "secKey" from "section 1"
    config.removeKey("section 1", "secKey");

    // add another section called "section 2"
    config.addSection("section 2");

    // add a key with no value to "section 2"
    config.addKey("section 2", "noval");

    // rename "section 2" to "new section"
    config.modifySectionName("section 2", "new section");

    // save to a file
    config.saveConfigToFile("config.txt");

    return 0;
}
```
We can save the contents of the `Config` object to a file. In this example, after modifying the `Config` object, we are saving its contents to a file named `config.txt`.

<br>

After saving, this is what the `config.txt` looks like:
```
"main key" = "main val"
dir = my/path/to/file

[section 1]
secKey2 = wassup
hello = secVal3

[new section]
noval = 
```

## Constructors
Defined in header `config.hpp`

| | |
| --- | --- |
| [(constructors)](Methods/constructors.md) | initializes the `Config` object with the contents of the given configuration file |

## Getters
Defined in header `config.hpp`

| | |
| --- | --- |
| [getValue](Getters/getValue.md) | returns the value of the key in the given section |

## Setters
Defined in header `config.hpp`

| | |
| --- | --- |
| [setConfigFromFile](Methods/setConfigFromFile.md) | initializes the `Config` object with the contents of the given configuration file |

## Modifiers
Defined in header `config.hpp`

| | |
| --- | --- |
| [addSection](Modifiers/addSection.md) | add a new section |
| [addKey](Modifiers/addKey.md) | add a new key |
| [addKeyValue](Modifiers/addKeyValue.md) | add a new key with a value |
| [removeSection](Modifiers/removeSection.md) | remove a section along with its keys |
| [removeKey](Modifiers/removeKey.md) | remove a key from a section |
| [modifySectionName](Modifiers/modifySectionName.md) | modify the name of a section |
| [modifyKeyName](Modifiers/modifyKeyName.md) | modify the name of a key from a section |
| [modifyKeyValue](Modifiers/modifyKeyValue.md) | modify the value of a key from a section |
| [clear](Modifiers/clear.md) | clears all contents of the `Config` object |
| [clearSection](Modifiers/clearSection.md) | deletes all keys from a section |
| [clearKeyValue](Modifiers/clearKeyValue.md) | clears the value of the given key |

## Checkers
Defined in header `config.hpp`

| | |
| --- | --- |
| [doesSectionExist](Checkers/doesSectionExist.md) | checks if a section exists |
| [doesSectionHaveKeys](Checkers/doesSectionHaveKeys.md) | checks if a section has keys |
| [doesKeyExist](Checkers/doesKeyExist.md) | checks if a key exists in a section |
| [doesKeyHaveValue](Checkers/doesKeyHaveValue.md) | checks if a key has a value |
| [isEmpty](Checkers/isEmpty.md) | checks if the `Config` object is empty |

## File Handling
Defined in header `config.hpp`

| | |
| --- | --- |
| [saveConfigToFile](<File Handling/saveConfigToFile.md>) | save the contents of the `Config` object to a file |

## Operators
Defined in header `config.hpp`

| | |
| --- | --- |
| [operator==](Operators/operator%3D%3D.md) | checks if two `Config` objects are equal |




