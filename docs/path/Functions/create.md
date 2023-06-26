## path::create
Defined in header `path.hpp`

| Declarations |
| --- |
| void create(const std::filesystem::path& path, const std::string& data = "") |
| void create(const std::filesystem::path& path, const std::vector&lt;std::string>& data) |

## Parameters
`path` - the file/directory to create \
`data` - the data to add to the file

## Notes
- You will be prompted to overwrite if the file you are creating already exists. 
- In the vector string `data`, each string is separated by a newline character.

## Example
### Example 1
```
#include <iostream>
#include "path.hpp"

using namespace std;

void showData(const filesystem::path& path)
{
    ifstream file(path);
    string temp;
    if(file.is_open()) {
        while(getline(file, temp)) {
            cout << temp << endl;
        }
    }
}

int main()
{
    string new_file = "temp/temp.txt";
    path::create(new_file, "hello world");
    showData(new_file);

    return 0;
}
```
Before running code:
```
Debug/
+-- temp/
    +-- test.txt
```
After running code:
```
Debug/
+-- temp/
    +-- temp.txt
    +-- test.txt
```
Output:
```
hello world
```

## Example 2
```
#include <iostream>
#include "path.hpp"

using namespace std;

void showData(const filesystem::path& path)
{
    ifstream file(path);
    string temp;
    if(file.is_open()) {
        while(getline(file, temp)) {
            cout << temp << endl;
        }
    }
}

int main()
{
    string new_file = "temp/temp.txt";
    vector<string> v = {"hello world", "my name is", "vendetta"};
    path::create(new_file, v);
    showData(new_file);

    return 0;
}
```
Before running code:
```
Debug/
+-- temp/
    +-- test.txt
```
After running code:
```
Debug/
+-- temp/
    +-- temp.txt
    +-- test.txt
```
Output:
```
hello world
my name is
vendetta
```