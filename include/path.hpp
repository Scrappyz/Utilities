#include <vector>
#include <filesystem>
#include <fstream>
#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <sys/stat.h>
#endif
#include <iostream>

namespace utility {
    namespace path {
        
        enum class CopyOption {None, Skip, Overwrite};
        enum class PathTraversal {NonRecursive, Recursive};

        namespace _private {
            
            std::filesystem::copy_options convertOption(const CopyOption& op)
            {
                if(op == CopyOption::Skip)
                    return std::filesystem::copy_options::skip_existing;
                else if(op == CopyOption::Overwrite)
                    return std::filesystem::copy_options::overwrite_existing;
                else
                    return std::filesystem::copy_options::none;
            }

        }

        bool isValidFilenameChar(char ch) // checks if character passed is a valid character for filenames
        {
            switch(ch) {
            #if defined(_WIN32)
                case '<':
                case '>':
                case ':':
                case '\"':
                case '/':
                case '\\':
                case '|':
                case '?':
                case '*':
            #else
                case '/':
            #endif
                    return false;
                default:
                    return true;
            }
        }

        bool isDirectorySeparator(char ch) // checks if the character passed is a directory separator
        {
            char preferred = std::filesystem::path::preferred_separator;
            return ch == preferred || ch == '/' && preferred == '\\';
        }

        bool hasFileExtension(const std::filesystem::path& path)
        {
            std::string temp = path.filename().empty() ? path.parent_path().filename().string() : path.filename().string();
            int i = temp.size()-1;
            while(i > 0 && (temp[i] == ' ' || isDirectorySeparator(temp[i]))) {
                i--;
            }
            while(i > 0 && temp[i] != '.' && !isDirectorySeparator(temp[i])) {
                i--;
            }

            return i >= 1 && i < temp.size()-1 && temp[i] == '.' && isValidFilenameChar(temp[i-1]);
        }

        std::string fileExtension(const std::filesystem::path& path) // returns the file extension of a given path
        {
            std::string temp = path.filename().empty() ? path.parent_path().filename().string() : path.filename().string();
            int i = temp.size()-1;
            while(i > 0 && (temp[i] == ' ' || isDirectorySeparator(temp[i]))) {
                i--;
            }
            while(i > 0 && temp[i] != '.' && !isDirectorySeparator(temp[i])) {
                i--;
            }

            std::string result;
            if(i >= 1 && i < temp.size()-1 && temp[i] == '.' && isValidFilenameChar(temp[i-1])) {
                for(int j = i+1; j < temp.size() && isValidFilenameChar(temp[j]); j++) {
                    result += temp[j];
                }
            }
            return result;
        }

        std::string filename(const std::filesystem::path& path) // returns the filename from a path
        {
            return path.filename().empty() ? path.parent_path().filename().string() : path.filename().string();
        }

        char directorySeparator() // returns the preferred directory separator of your operating system
        {
            return std::filesystem::path::preferred_separator;
        }

        std::string currentPath() // returns the current path you are in the command line
        {
            return std::filesystem::current_path().string();
        }

        std::string sourcePath() // returns the path to the executable
        {
            std::filesystem::path source_path;
            #if defined(_WIN32)
                char path[MAX_PATH];
                GetModuleFileName(NULL, path, MAX_PATH);
                source_path = path;
            #elif defined(__linux__)
                source_path = filesystem::canonical("/proc/self/exe");
            #else
                throw std::runtime_error("[Error][sourcePath] Unknown Operating System");
            #endif
            return source_path.parent_path().string();
        }

        // joinPath
        std::string joinPath(const std::filesystem::path& p1, const std::filesystem::path& p2)
        {
            bool pop_separator = p2.filename() == "." || p2.filename() == "..";
            std::string result;
            if(p1.empty() && p2.empty()) {
                return result;
            } else if(p1.empty()) {
                result = std::filesystem::weakly_canonical(p2).string();
                if(pop_separator) {
                    result.pop_back();
                }
                return result;
            } else if(p2.empty()) {
                pop_separator = p1.filename() == "." || p1.filename() == "..";
                result = std::filesystem::weakly_canonical(p1).string();
                if(pop_separator) {
                    result.pop_back();
                }
                return result;
            }

            result = std::filesystem::weakly_canonical(p1 / p2).string();
            if(pop_separator) {
                result.pop_back();
            }
            return result;
        }

        std::string joinPath(const std::vector<std::filesystem::path>& paths)
        {
            if(paths.empty()) {
                return std::string();
            } else if(paths.size() < 2) {
                return joinPath(paths[0], "");
            }

            std::filesystem::path result = paths[0];
            for(int i = 1; i < paths.size()-1; i++) {
                result /= paths[i];
            }
            result = std::filesystem::weakly_canonical(result / paths.back());

            bool pop_separator = paths.back().filename() == "." || paths.back().filename() == "..";
            if(pop_separator) {
                return result.parent_path().string();
            } else {
                return result.string();
            }
        }

        void create(const std::filesystem::path& path)
        {
            if(!std::filesystem::exists(path)) {
                if(hasFileExtension(path)) {
                    std::ofstream file(path);
                    file.close();
                } else {
                    std::filesystem::create_directories(path);
                }
            }
        }

        // copy
        void copy(const std::filesystem::path& from, std::filesystem::path to, const std::filesystem::copy_options& op = std::filesystem::copy_options::overwrite_existing)
        {
            if(std::filesystem::exists(from)) {
                if(std::filesystem::is_directory(from) && !from.filename().empty()) {
                    to /= from.filename();
                    std::filesystem::create_directories(to);
                } 
                if(std::filesystem::is_directory(from)) {
                    for(const auto& entry : std::filesystem::recursive_directory_iterator(from)) {
                        std::filesystem::path copy_to = to / std::filesystem::relative(entry.path(), from);
                        if(std::filesystem::is_directory(entry.path())) { 
                            std::filesystem::create_directories(copy_to);
                        } else {
                            std::filesystem::copy_file(entry, copy_to, op);
                        }
                    }
                } else {
                    std::filesystem::path copy_to = to / from.filename();
                    std::filesystem::copy_file(from, copy_to, op);
                }
            }
        }

        void remove(const std::filesystem::path& path)
        {
            if(std::filesystem::exists(path)) {
                if(std::filesystem::is_directory(path)) {
                    std::filesystem::remove_all(path);
                } else {
                    std::filesystem::remove(path);
                }
            }
        }

        void move(const std::filesystem::path& from, const std::filesystem::path& to, const std::filesystem::copy_options& op = std::filesystem::copy_options::overwrite_existing)
        {
            utility::path::copy(from, to, op);
            utility::path::remove(from);
        }

        std::string find(const std::filesystem::path& search_path, const std::string& pattern, const PathTraversal& pt = PathTraversal::NonRecursive)
        {
            if(std::filesystem::exists(search_path)) {
                if(pt == PathTraversal::NonRecursive) {
                    for(const auto& entry : std::filesystem::directory_iterator(search_path)) {
                        std::string filename = entry.path().filename().string();
                        if(filename == pattern) {
                            return entry.path().string();
                        }
                    }
                } else {
                    for(const auto& entry : std::filesystem::recursive_directory_iterator(search_path)) {
                        std::string filename = entry.path().filename().string();
                        if(filename == pattern) {
                            return entry.path().string();
                        }
                    }
                }
                return std::string();
            } else {
                throw std::logic_error("[Error][find] Path does not exist");
            }
        }

        std::vector<std::string> findAll(const std::filesystem::path& search_path, const std::string& pattern, const PathTraversal& pt = PathTraversal::NonRecursive)
        {
            if(std::filesystem::exists(search_path)) {
                std::vector<std::string> matches;
                if(pt == PathTraversal::NonRecursive) {
                    for(const auto& entry : std::filesystem::directory_iterator(search_path)) {
                        std::string filename = entry.path().filename().string();
                        if(filename == pattern) {
                            matches.push_back(entry.path().string());
                        }
                    }
                } else {
                    for(const auto& entry : std::filesystem::recursive_directory_iterator(search_path)) {
                        std::string filename = entry.path().filename().string();
                        if(filename == pattern) {
                            matches.push_back(entry.path().string());
                        }
                    }
                }
                return matches;
            } else {
                throw std::logic_error("[Error][findAll] Path does not exist");
            }
        }
    }
}