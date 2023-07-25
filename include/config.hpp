#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

class Config {
    private:
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> config;

        static bool hasKey(const std::string& line, const std::string& key)
        {
            if(line.empty() || key.empty()) {
                return false;
            }

            int i = 0;
            while(i < line.size() && line[i] == ' ') {
                i++;
            }

            if(isQuotation(line[i])) {
                i++;
            }

            while(i < line.size()) {
                if(line[i] == '=') {
                    return false;
                }

                if(line[i] == key[0]) {
                    int j = 0;
                    while(i < line.size() && j < key.size() && line[i] == key[j]) {
                        i++;
                        j++;
                    }

                    while(i < line.size() && isQuotation(line[i])) {
                        i++;
                    }
                    
                    if(i >= line.size() && j >= key.size() || (line[i] == ' ' || line[i] == '=') && j >= key.size()) {
                        return true;
                    }
                } else {
                    i++;
                }
            }

            return false;
        } 

        static std::string trim(const std::string& str)
        {
            std::string trimmed;
            trimmed.reserve(str.size());
            
            int i = 0;
            while(i < str.size() && str[i] == ' ') {
                i++;
            }

            while(i < str.size()) {
                trimmed.push_back(str[i]);
                i++;
            }

            while(trimmed.back() == ' ') {
                trimmed.pop_back();
            }

            return trimmed;
        }

        static bool isQuotation(char ch)
        {
            return ch == '\'' || ch == '\"';
        }

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
            config.clear();
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

        void setConfigToFile(const std::string& config_path)
        {
            std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::string>>>> output;

            for(const auto& i : config) {
                std::string section = i.first;
                std::vector<std::pair<std::string, std::string>> keyval;
                for(const auto& j : i.second) {
                     keyval.push_back(std::make_pair(j.first, j.second));
                }
                output.push_back(std::make_pair(section, keyval));
            }

            // for(int i = 0; i < output.size(); i++) {
            //     std::cout << output[i].first << std::endl;
            //     for(int j = 0; j < output[i].second.size(); j++) {
            //         std::cout << output[i].second[j].first << " = " << output[i].second[j].second << std::endl;
            //     }
            // }

            std::ofstream file(config_path);

            for(int i = output.size()-1; i >= 0; i--) {
                if(!output[i].first.empty()) {
                    file << "[" << output[i].first << "]" << std::endl;
                }

                for(int j = output[i].second.size()-1; j >= 0; j--) {
                    size_t key_space = output[i].second[j].first.find(' ');
                    size_t value_space = output[i].second[j].second.find(' ');
                    std::string key = (key_space == std::string::npos ? output[i].second[j].first : "\"" + output[i].second[j].first + "\"");
                    std::string value = (value_space == std::string::npos ? output[i].second[j].second : "\"" + output[i].second[j].second + "\"");
                    file << key << " = " << value << std::endl;
                }
                
                file << std::endl;
            }
        }

        // Modifiers
        // static bool modifySectionInFile(const std::string& config_path, const std::string& section, const std::string& new_section)
        // {
        //     std::ifstream input(config_path);

        //     if(!input.is_open()) {
        //         throw std::runtime_error("[Error] Could not open configuration file at \"" + config_path + "\"");
        //     }

        //     std::string line;
        //     while(getline(input, line)) {
                
        //     }
        // }

        // static bool modifyKeyInFile(const std::string& config_path, const std::string& section, const std::string& key, const std::string& new_val)
        // {
        //     return true;
        // }

        // static bool modifyKeyInFile(const std::string& config_path, const std::string& key, const std::string& new_val)
        // {
        //     return true;
        // }

        // static bool modifyValueInFile(const std::string& config_path, const std::string& section, const std::string& key, const std::string& new_val)
        // {
        //     std::ifstream input(config_path);

        //     if(!input.is_open()) {
        //         throw std::runtime_error("[Error] Could not open configuration file at \"" + config_path + "\"");
        //     }

        //     std::vector<std::string> data;
        //     std::string line;
        //     std::string current_section;
        //     bool new_val_has_space = (new_val.find(' ') != std::string::npos);
        //     bool return_val = false;
        //     while(getline(input, line)) {
        //         line = trim(line);

        //         if(line.empty()) {
        //             data.push_back("");
        //             continue;
        //         }

        //         int i = 0;

        //         if(line[i] == '#') { // if comment, add it to data
        //             data.push_back(line);
        //             continue;
        //         }

        //         if(line[i] == '[') { // if section
        //             current_section.clear();
        //             i++;
        //             while(i < line.size() && line[i] != ']') {
        //                 current_section.push_back(line[i]);
        //                 i++;
        //             }
        //             data.push_back("[" + current_section + "]");
        //             continue;
        //         }

        //         if(current_section != section) { // do not modify if it is not the given section
        //             data.push_back(line);
        //             continue;
        //         }

        //         // check if the given key is in the current line
        //         if(hasKey(line, key)) {
        //             std::string keyval;
        //             if(isQuotation(line[i])) { // skip quotation
        //                 keyval.push_back(line[i]);
        //                 i++;
        //             }

        //             keyval.append(key);
        //             i += key.size();

        //             if(isQuotation(line[i])) { // skip quotation
        //                 keyval.push_back(line[i]);
        //                 i++;
        //             }

        //             while(i < line.size() && (line[i] == ' ' || line[i] == '=')) { // append the assign operator
        //                 keyval.push_back(line[i]);
        //                 i++;
        //             }

        //             if(new_val_has_space) { // add quotation to value if there are spaces
        //                 keyval.append("\"" + new_val + "\"");
        //             } else {
        //                 keyval.append(new_val);
        //             }

        //             int spaces = 0;
        //             while(i < line.size() && line[i] != '#') { // count spaces beyond value
        //                 if(line[i] == ' ') {
        //                     spaces++;
        //                 } else {
        //                     spaces = 0;
        //                 }
        //                 i++;
        //             }

        //             if(i >= line.size()) {
        //                 data.push_back(keyval);
        //                 return_val = true;
        //                 continue;
        //             }

        //             keyval.append(std::string(spaces, ' '));

        //             while(i < line.size()) {
        //                 keyval.push_back(line[i]);
        //                 i++;
        //             }

        //             data.push_back(keyval);
        //             return_val = true;
        //         } else {
        //             data.push_back(line);
        //         }
        //     }

        //     input.close();

        //     std::ofstream output(config_path);
        //     for(int i = 0; i < data.size(); i++) {
        //         output << data[i] << std::endl;
        //     }
        //     output.close();

        //     return return_val;
        // }

        // static bool modifyValueInFile(const std::string& config_path, const std::string& key, const std::string& new_val)
        // {
        //     return modifyValueInFile(config_path, "", key, new_val);
        // }
};