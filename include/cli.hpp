#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class CLIException : std::exception {
    private:
        std::string error_message;

    public: 
        CLIException(const std::string& message) : error_message(message) {}

        const char* what() const noexcept override
        {
            return error_message.c_str();
        }
};

class CLI {
    private:
        std::vector<std::string> args;
        std::unordered_map<std::string, std::unordered_map<std::string, int>> subcommands; // valid subcommands and their valid flags
        std::string active_subcommand; // the current active subcommand
        int active_subcommand_end_pos; // stores the position the active subcommand ends in the arguement list
        int max_subcommand_chain_count; // keeps track of how many subcommand words can be chained

        void setActiveSubcommand(int start = 1)
        {
            if(start < 0 || start >= args.size()) {
                return;
            }

            active_subcommand.clear();
            active_subcommand_end_pos = 0;
            if(subcommands.size() < 2) {
                return;
            }

            int chain_end_pos = start + max_subcommand_chain_count - 1;
            if(chain_end_pos >= args.size()) {
                chain_end_pos = args.size()-1;
            }
            std::string temp;
            for(int i = start; i <= chain_end_pos; i++) {
                temp.append(args[i]);   
                if(isValidSubcommand(temp)) {
                    active_subcommand = temp;
                    active_subcommand_end_pos = i;
                }
                temp.push_back(' ');
            }
        }

        void setFlags(const std::string& subcmd, int start = -1) // initialize values of flags from args
        {
            if(subcommands.at(active_subcommand).empty()) {
                return;
            }

            if(start < 0) {
                start = active_subcommand_end_pos + 1;
            }

            for(int i = start; i < args.size(); i++) { 
                if(isFlagFormat(args[i])) {
                    std::string flag;
                    std::string temp = trim(args[i]);
                    bool is_flag_word = (args[i][0] == '-' && args[i][1] == '-');

                    if(is_flag_word) {
                        if(isValidFlag(temp)) {
                            subcommands.at(subcmd)[temp] = i;
                        }
                    } else {
                        int j = 0;
                        while(j < temp.size() && isFlagPrefix(temp[j])) {
                            flag.push_back(temp[j]);
                            j++;
                        }

                        while(j < temp.size()) {
                            flag.push_back(temp[j]);
                            if(!isFlagPrefix(temp[j]) && isValidFlag(flag)) {
                                subcommands.at(subcmd)[flag] = i;
                                flag.pop_back();
                            }
                            j++;
                        }
                    }
                }
            }
        }

        void resetFlags(const std::string& subcmd) // uninitializes all flags of a subcommand
        {
            if(!isValidSubcommand(subcmd) || subcommands.at(subcmd).empty()) {
                return;
            }
            for(auto& i : subcommands.at(subcmd)) {
                i.second = -1;
            }
        }

        void clearSubcommands()
        {
            subcommands.clear();
            subcommands.insert({"", std::unordered_map<std::string, int>()});
            max_subcommand_chain_count = 0;
        }

        std::string trim(const std::string& str) // removes trailing whitespace
        {
            std::string trimmed;
            trimmed.reserve(str.size());
            int i = 0;
            while(i < str.size() && str[i] == ' ') {
                i++;
            }
            while(i < str.size()) {
                if(str[i] == ' ') {
                    while(i < str.size() && str[i] == ' ') {
                        i++;
                    }
                    if(i >= str.size()) {
                        break;
                    } else {
                        trimmed.push_back(' ');
                    }
                } else if(str[i] == '=') { // turns flags such as "--flag=value" to "--flag"
                    return trimmed;
                }
                trimmed.push_back(str[i]);
                i++;
            }
            return trimmed;
        }

        bool isFlagPrefix(char ch) const // checks if a character is flag prefix
        {
            return ch == '-';
        }

        bool isFlagFormat(const std::string& flag) const // checks if a string is in a flag format
        {
            std::string temp;
            for(int i = 0; isFlagPrefix(flag[i]); i++) {
                temp.push_back(flag[i]);
            }
            return !temp.empty() && temp.size() <= 2 && temp.size() != flag.size();
        } 

    public:
        CLI() : args(), subcommands(), active_subcommand(), active_subcommand_end_pos(), max_subcommand_chain_count()
        {
            subcommands.insert({"", std::unordered_map<std::string, int>()}); // for when no active_subcommand is provided
        }

        CLI(int argc, char** argv) 
        : args(), subcommands(), active_subcommand(), active_subcommand_end_pos(), max_subcommand_chain_count()
        {
            setArguments(argc, argv);
        }

        CLI(const std::vector<std::string>& args) 
        : args(), subcommands(), active_subcommand(), active_subcommand_end_pos(), max_subcommand_chain_count()
        {
            setArguments(args);
        }

        // Getters
        const std::vector<std::string>& getArguments() const
        {
            return args;
        }

        const std::unordered_map<std::string, std::unordered_map<std::string, int>>& getSubcommands() const
        {
            return subcommands;
        }

        std::unordered_set<std::string> getValidSubcommands() const
        {
            std::unordered_set<std::string> valid_subcommands;
            for(const auto& i : subcommands) {
                valid_subcommands.insert(i.first);
            }
            return valid_subcommands;
        }

        std::unordered_map<std::string, int> getFlags(std::string subcmd = "") const
        {
            if(subcmd.empty()) {
                subcmd = active_subcommand;
            }

            return isValidSubcommand(subcmd) ? subcommands.at(subcmd) : throw CLIException("[Error][" + std::string(__func__) + "] \"" + subcmd + "\" is not a valid subcommand");
        }

        std::unordered_set<std::string> getValidFlags(std::string subcmd = "") const
        {
            if(subcmd.empty()) {
                subcmd = active_subcommand;
            }

            if(!isValidSubcommand(subcmd)) {
                throw CLIException("[Error][" + std::string(__func__) + "] \"" + subcmd + "\" is not a valid subcommand");
            }

            std::unordered_set<std::string> flags;
            for(const auto& i : subcommands.at(subcmd)) {
                flags.insert(i.first);
            }

            return flags;
        }

        std::unordered_set<std::string> getActiveFlags(std::string subcmd = "") const
        {
            if(subcmd.empty()) {
                subcmd = active_subcommand;
            }

            if(!isValidSubcommand(subcmd)) {
                throw CLIException("[Error][" + std::string(__func__) + "] \"" + subcmd + "\" is not a valid subcommand");
            }

            std::unordered_set<std::string> flags;
            for(const auto& i : subcommands.at(subcmd)) {
                if(i.second >= 0) {
                    flags.insert(i.first);
                }
            }

            return flags;
        }

        const std::string& getActiveSubcommand() const
        {
            return active_subcommand;
        }

        int getActiveSubcommandEndPosition() const
        {
            return active_subcommand_end_pos;
        }

        std::string getArgumentAt(int start, int end = -1) const
        {
            if(start < 0 || start >= args.size()) {
                throw CLIException("[Error][" + std::string(__func__) + "] Index is out of range");
            }

            if(end < 0 || end >= args.size()) {
                return args[start];
            } 

            std::string result;
            for(int i = start; i <= end; i++) {
                result.append(args[i]);
                if(i < end) {
                    result.push_back(' ');
                }
            }

            return result;
        }

        int getFlagPosition(const std::string& flag) const
        {
            return getFlagPosition(active_subcommand, flag);
        }

        int getFlagPosition(const std::string& subcmd, const std::string& flag) const
        {
            if(!isValidSubcommand(subcmd)) {
                throw CLIException("[Error][" + std::string(__func__) + "] \"" + subcmd + "\" is not a valid subcommand");
            } else if(subcommands.at(subcmd).count(flag) < 1) {
                throw CLIException("[Error][" + std::string(__func__) + "] \"" + flag + "\" is not a valid flag");
            }
            return subcommands.at(subcmd).at(flag);
        }

        std::vector<std::string> getValuesOf(int limit = -1) const
        {
            return getValuesOf(active_subcommand, limit);
        }

        std::vector<std::string> getValuesOf(const std::initializer_list<std::string>& flags, int limit = -1) const
        {
            return getValuesOf(std::vector<std::string>(flags));
        }

        std::vector<std::string> getValuesOf(const std::vector<std::string>& flags, int limit = -1) const
        {
            for(int i = 0; i < flags.size(); i++) {
                if(isFlagActive(flags[i])) {
                    return getValuesOf(flags[i], limit);
                }
            }
            return std::vector<std::string>();
        }

        std::vector<std::string> getValuesOf(const std::string& str, int limit = -1) const
        {
            std::vector<std::string> values;
            if(limit == 0) {
                return values;
            }

            if(isValidFlag(str)) {
                int flag_pos = subcommands.at(active_subcommand).at(str);
                if(flag_pos < 0) {
                    throw CLIException("[Error][getValuesOf] Flag \"" + str + "\" is not set");
                }

                std::string temp = args[flag_pos];
                int equal = temp.find_first_of("=");
                if(equal != std::string::npos) {
                    values.push_back(temp.substr(equal + 1, temp.size() - equal));
                } 
                
                for(int i = flag_pos + 1; i < args.size(); i++) {
                    if(isFlagFormat(args[i]) || limit > 0 && values.size() >= limit) {
                        break;
                    }
                    values.push_back(args[i]);
                }
            } else if(str == active_subcommand) {
                for(int i = active_subcommand_end_pos + 1; i < args.size(); i++) {
                    if(isFlagFormat(args[i]) || limit > 0 && values.size() >= limit) {
                        break;
                    }
                    values.push_back(args[i]);
                }
            } else {
                throw CLIException("[Error][getValuesOf] Argument \"" + str + "\" is neither a set flag or an active subcommand");
            }
            return values;
        }

        std::unordered_map<std::string, std::vector<std::string>> getFlagValues() const
        {
            std::unordered_map<std::string, std::vector<std::string>> values;
            values.insert({"", getValuesOf(active_subcommand)});
            for(const auto& i : subcommands.at(active_subcommand)) {
                if(i.second >= 0) {
                    values.insert({i.first, getValuesOf(i.first)});
                }
            }

            return values;
        }

        // Setters
        void setArguments(int argc, char** argv)
        {
            if(argc > 0) {
                setArguments(std::vector<std::string>(argv, argv+argc));
            }
        }

        void setArguments(const std::vector<std::string>& args)
        {
            this->args = args;
            if(subcommands.empty()) {
                subcommands.insert({"", std::unordered_map<std::string, int>()});
            }
            resetFlags(active_subcommand); // reset the flags of the old subcommand
            setActiveSubcommand(); // set the new subcommand
            setFlags(active_subcommand); // set the flags for the new subcommand
        }

        void setValidSubcommands(const std::vector<std::string>& valid_subs)
        {
            clearSubcommands(); // clear old subcommands
            for(int i = 0; i < valid_subs.size(); i++) {
                std::string temp = trim(valid_subs[i]);

                if(temp.empty() || isValidSubcommand(temp)) {
                    continue;
                }

                int max_word_count = 1;
                for(int j = 0; j < temp.size(); j++) {
                    if(temp[j] == ' ') {
                        max_word_count++;
                    }
                }

                if(max_word_count > max_subcommand_chain_count) {
                    max_subcommand_chain_count = max_word_count;
                }

                subcommands.insert({temp, std::unordered_map<std::string, int>()});
            }

            if(!args.empty()) { // reset the new active subcommand
                setActiveSubcommand();
            }
        }

        void setValidFlags(const std::vector<std::string>& valid_flags)
        {
            setValidFlags("", valid_flags);
        }

        void setValidFlags(const std::string& subcmd, const std::vector<std::string>& valid_flags) // initializes the keys of flags
        {
            if(!isValidSubcommand(subcmd)) {
                throw CLIException("[Error][" + std::string(__func__) + "()] Invalid subcommand \"" + subcmd + "\"");
            }
                
            subcommands.at(subcmd).clear(); // clear the old flags of the given subcommand
            for(int i = 0; i < valid_flags.size(); i++) {
                std::string flag = trim(valid_flags[i]);

                if(flag.size() < 2) {
                    subcommands.at(subcmd).clear();
                    throw CLIException("[Error][" + std::string(__func__) + "] \"" + flag + "\" is not a valid flag");
                } else if(!isFlagFormat(flag)) {
                    subcommands.at(subcmd).clear();
                    throw CLIException("[Error][" + std::string(__func__) + "] \"" + flag + "\" does not have a proper prefix");
                }

                subcommands.at(subcmd).insert({flag, -1});
            }
            
            if(subcmd == active_subcommand) { // set the flags only if the given subcommand is equal to the active subcommand
                setFlags(subcmd);
            }
        }

        // Checkers
        bool isValidSubcommand(const std::string& subcmd) const
        {
            return subcommands.count(subcmd) > 0;
        }

        bool isActiveSubcommand(const std::string& subcmd = "") const 
        {
            return active_subcommand == subcmd;
        }

        bool noActiveSubcommand() const 
        {
            return active_subcommand.empty();
        }

        bool isFlagActive(const std::string& flag) const
        {
            return isFlagActive(active_subcommand, flag);
        }

        bool isFlagActive(const std::string& subcmd, const std::string& flag) const // checks if a flag is initialized
        {
            if(!isValidSubcommand(subcmd)) {
                throw CLIException("[Error][" + std::string(__func__) + "] \"" + subcmd + "\" is not a valid subcommand");
            } else if(subcommands.at(subcmd).count(flag) < 1) {
                throw CLIException("[Error][" + std::string(__func__) + "] \"" + flag + "\" is not a valid flag");
            }
            return subcommands.at(subcmd).at(flag) >= 0;
        }

        bool isValidFlag(const std::string& flag) const 
        {
            return isValidFlag(active_subcommand, flag);
        }

        bool isValidFlag(const std::string& subcmd, const std::string& flag) const // checks if flag is valid
        {
            if(!isValidSubcommand(subcmd)) {
                throw CLIException("[Error][" + std::string(__func__) + "] \"" + subcmd + "\" is not a valid subcommand");
            }
            return subcommands.at(subcmd).count(flag) > 0;
        }

        // Modifiers
        void clear()
        {
            args.clear();
            subcommands.clear();
            subcommands.insert({"", std::unordered_map<std::string, int>()});
            active_subcommand.clear();
            active_subcommand_end_pos = 0;
            max_subcommand_chain_count = 0;
        }
};