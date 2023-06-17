#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

class FileParser {
    private:
        std::vector<std::string> content;
        std::unordered_map<std::string, int> heading;
        std::string header_prefix;
    public:
        FileParser() : content(), heading(), header_prefix("---") {}
        FileParser(const std::string& file_path) : header_prefix("---")
        {
            set(file_path);
        }
        FileParser(const std::string& file_path, const std::string& prefix) : header_prefix(prefix)
        {
            set(file_path);
        }

        std::vector<std::string> getContent()
        {
            return content;
        }
        std::unordered_map<std::string, int> getHeading()
        {
            return heading;
        }
        std::string getLine(int line)
        {
            if(content.empty()) {
                return std::string();
            }
            return content[line];
        }
        int getLineNumber(const std::string& header)
        {
            return heading.at(header);
        }

        void set(const std::string& file_path)
        {
            std::string temp;
            std::ifstream file(file_path);
            if(file.is_open()) {
                int line = 1;
                while(getline(file, temp)) {
                    content.push_back(temp);
                    if(isHeader(temp)) {
                        std::string header;
                        int i = header_prefix.size();
                        while(i < temp.size() && (temp[i] == header_prefix[0] || temp[i] == ' ')) {
                            i++;
                        }
                        while(i < temp.size() && temp[i] != header_prefix[0]) {
                            header.push_back(temp[i]);
                            i++;
                        }
                        heading[header] = line;
                    }
                    line++;
                }
                file.close();
            } else {
                std::cerr << "[Error] Could not open file" << std::endl; 
            }
        }
        
        void setHeaderPrefix(const std::string& prefix)
        {
            header_prefix = prefix;
        }

        bool isHeader(const std::string& str)
        {
            for(int i = 0; i < header_prefix.size(); i++) {
                if(str[i] != header_prefix[i]) {
                    return false;
                }
            }
            return true;
        }

        void printContent()
        {
            for(int i = 0; i < content.size(); i++) {
                std::cout << content[i] << std::endl;
            }
        }

        void printHeading()
        {
            for(const auto& i : heading) {
                std::cout << i.first << " | " << i.second << std::endl;
            }
        }

        // To be added
};