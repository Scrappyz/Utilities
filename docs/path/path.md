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

| Name | Description |
| --- | --- |
| [CopyOption](Enums/CopyOption.md) | specifies what to automatically do with existing files |
| [Traversal](Enums/Traversal.md) | specifies what type of filesystem traversal to use |
| [SizeMetric](Enums/SizeMetric.md) | specifies what unit of measurement to use in file sizes |

## Functions
Defined in header `path.hpp` \
Defined in namespace `path`

| Function | Description |
| --- | --- |
| [absolute](Functions/absolute.md) | returns the absolute path of a given relative path |
| [copy](Functions/copy.md) | copies a file or directory |
| [create](Functions/create.md) | creates a new file or directory |
| [currentPath](Functions/currentPath.md) | returns the absolute path you are currently in |
| [directorySeparator](Functions/directorySeparator.md) | returns a directory separator character |
| [exists](Functions/exists.md) | checks if the given path exists |
| [fileExtension](Functions/fileExtension.md) | returns the file extension of a given path or filename |
| [fileSize](Functions/fileSize.md) | returns the file size of a given path |
| [filename](Functions/filename.md) | returns the filename of a given path |
| [find](Functions/find.md) | finds a given file |
| [findAll](Functions/findAll.md) | finds multiple of the same file |
| [hasFileExtension](Functions/hasFileExtension.md) | checks if a given path or filename has an extension |
| [isAbsolute](Functions/isAbsolute.md) | checks if the given path is an absolute path |
| [isDirectorySeparator](Functions/isDirectorySeparator.md) | checks if a given character is a directory separator character |
| [isRelative](Functions/isRelative.md) | checks if the given path is a relative path |
| [isValidFilenameChar](Functions/isValidFilenameChar.md) | checks if the given character is valid for filenames |
| [joinPath](Functions/joinPath.md) | concatenates two or more paths together |
| [move](Functions/move.md) | moves a file or directory |
| [relative](Functions/relative.md) | returns a path relative to another path |
| [rename](Functions/rename.md) | renames a file or directory |
| [rootName](Functions/rootName.md) | returns the name of the root |
| [sourcePath](Functions/sourcePath.md) | returns the absolute path to the executable |






