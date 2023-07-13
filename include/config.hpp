#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

class Config {
    private:
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config;

    public:
        // Constructors
        Config() : config() {}

        Config(const std::string& config_path) : config()
        {
            setConfig(config_path);
        }

        // Getters
        const std::string& getValueOf(const std::string& key) const
        {
            return config.at("").at(key);
        }

        const std::string& getValueOf(const std::string& section, const std::string& key) const
        {
            return config.at(section).at(key);
        }

        // Setters
        void setConfig(const std::string& config_path)
        {
            std::ifstream file(config_path);
            std::string temp;

            if(!file.is_open()) {
                throw std::runtime_error("[Error] Could not open configuration file at \"" + config_path + "\"");
            }

            std::string section;
            while(getline(file, temp)) {
                std::string key, value;

                if(temp.empty()) {
                    continue;
                }

                int i = 0;
                while(i < temp.size() && temp[i] == ' ') { // skip whitespaces
                    i++;
                }

                if(temp[i] == '#') { // is a comment
                    continue;
                }

                if(temp[i] == '[') {
                    section.clear();
                    i++;
                    while(i < temp.size() && temp[i] != ']') {
                        section.push_back(temp[i]);
                        i++;
                    }

                    if(config.count(section) < 1) {
                        config.insert({section, std::unordered_map<std::string, std::string>()});
                    }
                } else {
                    bool is_string = false;
                    if(temp[i] == '"' || temp[i] == '\'') {
                        is_string = true;
                        i++;
                    } 

                    while(i < temp.size()) {
                        if(!is_string && temp[i] == ' ' || (temp[i] == '\"' || temp[i] == '\'' || temp[i] == '=')) {
                            break;
                        }
                        key.push_back(temp[i]);
                        i++;
                    }

                    while(i < temp.size() && temp[i] != '=') { // move to '='
                        i++;
                    }

                    if(i >= temp.size()) { // is not a key value pair
                        continue;
                    }
                    i++;

                    while(i < temp.size() && temp[i] == ' ') { // skip whitespaces
                        i++;
                    }

                    is_string = false;
                    if(temp[i] == '"' || temp[i] == '\'') {
                        is_string = true;
                        i++;
                    }

                    while(i < temp.size()) {
                        if(!is_string && temp[i] == ' ' || (temp[i] == '\"' || temp[i] == '\'')) {
                            break;
                        }
                        value.push_back(temp[i]);
                        i++;
                    }

                    if(config.count(section) < 1) {
                        config.insert({section, std::unordered_map<std::string, std::string>()});
                    }
                    config.at(section).insert({key, value});
                }
            }
        }

        static void printData(const std::vector<std::string>& v)
        {
            for(const auto& i : v) {
                std::cout << i << std::endl;
            }
        }

        // Modifiers
        static void modifyValueInFile(const std::string& config_path, const std::string& section, const std::string& key, const std::string& new_val)
        {
            std::ifstream input(config_path);

            if(!input.is_open()) {
                throw std::runtime_error("[Error] Could not open configuration file at \"" + config_path + "\"");
            }

            std::vector<std::string> data;
            std::string temp;
            std::string current_section;
            while(getline(input, temp)) {
                while(!temp.empty() && temp.back() == ' ') {
                    temp.pop_back();
                }

                if(temp.empty()) {
                    data.push_back("");
                    continue;
                }

                int i = 0;
                while(i < temp.size() && temp[i] == ' ') {
                    i++;
                }

                if(temp[i] == '#') {
                    data.push_back(temp.substr(i, temp.size()-i));
                    continue;
                }

                if(temp[i] == '[') {
                    current_section.clear();
                    i++;
                    while(i < temp.size() && temp[i] != ']') {
                        current_section.push_back(temp[i]);
                        i++;
                    }
                    data.push_back("[" + current_section + "]");
                    continue;
                }

                if(current_section != section) {
                    data.push_back(temp.substr(i, temp.size()-i));
                    continue;
                }

                size_t f = temp.find(key);
                if(f != std::string::npos) {
                    std::string m;
                    i += key.size();
                    while(i < temp.size() && (temp[i] == ' ' || temp[i] == '=')) {
                        m.push_back(temp[i]);
                        i++;
                    }
                    data.push_back(key + m + new_val);
                    
                } else {
                    data.push_back(temp.substr(i, temp.size()-i));
                }
            }

            input.close();
            printData(data);
        }

        static void modifyValueInFile(const std::string& config_path, const std::string& key, const std::string& new_val)
        {
            modifyValueInFile(config_path, "", key, new_val);
        }
};