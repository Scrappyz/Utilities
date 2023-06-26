## Path library
The Path library aims to simplify and improve the process of performing operations on file systems with the `<filesystem>` library.

## Minimum C++ Version
- `C++17`

## Includes
- `<iostream>`
- `<vector>`
- `<fstream>`
- `<filesystem>`
### Windows
- `<windows.h>`
### Linux
- `<unistd.h>`
- `<sys/stat.h>`

## Enums
Defined in header `path.hpp` \
Defined in namespace `path`

| Enum | Description |
| --- | --- |
| [CopyOption](Enums/CopyOption.md) | specifies what to automatically do with existing files |
| [Traversal](Enums/Traversal.md) | specifies what type of filesystem traversal to use |
| [SizeMetric](Enums/SizeMetric.md) | specifies what unit of measurement to use in file sizes |

## Functions
Defined in header `path.hpp` \
Defined in namespace `path`

| Function | Description |
| --- | --- |
| [exists](Functions/exists.md) | checks if the given path exists |
| [isAbsolute](Functions/isAbsolute.md) | checks if the given path is an absolute path |
| [isRelative](Functions/isRelative.md) | checks if the given path is a relative path |
| [isValidFilenameChar](Functions/isValidFilenameChar.md) | checks if the given character is valid for filenames |
| [isDirectorySeparator](Functions/isDirectorySeparator.md) | checks if a given character is a directory separator character |
| [fileExtension](Functions/fileExtension.md) | returns the file extension of a given path or filename |
| [hasFileExtension](Functions/hasFileExtension.md) | checks if a given path or filename has an extension |
| [isDirectory](Functions/isDirectory.md) | checks if a given path is a directory |
| [isFile](Functions/isFile.md) | checks if a given path is a file |
| [filename](Functions/filename.md) | returns the filename of a given path |
| [fileSize](Functions/fileSize.md) | returns the file size of a given path |
| [directorySeparator](Functions/directorySeparator.md) | returns a directory separator character |
| [absolute](Functions/absolute.md) | returns the absolute path of a given relative path |
| [relative](Functions/relative.md) | returns a path relative to another path |
| [currentPath](Functions/currentPath.md) | returns the absolute path you are currently in |
| [sourcePath](Functions/sourcePath.md) | returns the absolute path to the executable |
| [rootName](Functions/rootName.md) | returns the name of the root |
| [joinPath](Functions/joinPath.md) | concatenates two or more paths together |






