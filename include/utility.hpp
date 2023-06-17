#pragma once

#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <algorithm>
#include <exception>
#include <type_traits>

namespace utility {
    namespace math {
        bool isPrime(int n)
        {
            if(n < 2) {
                return false;
            }

            for(int i = 2; i*i <= n; i++) {
                if(n % i == 0) {
                    return false;
                }
            }
            return true;
        }

        template<typename T>
        double getSum(const std::vector<T>& v)
        {
            static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "[Type Error][getSum] Vector type must be int or double");

            if(v.empty()) {
                return 0;
            }

            double sum = 0;
            for(int i = 0; i < v.size(); i++) {
                sum += v[i];
            }
            return sum;
        }

        template<typename T>
        double getSum(const std::initializer_list<T>& v)
        {
            return getSum(std::vector<T>(v));
        }

        template<typename T>
        double getMean(const std::vector<T>& v)
        {
            static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "[Type Error][getMean] Vector type must be int or double");

            if(v.empty()) {
                return 0;
            }

            return getSum(v) / v.size();
        }

        template<typename T>
        double getMean(const std::initializer_list<T>& v)
        {
            return getMean(std::vector<T>(v));
        }

        template<typename T>
        double getMedian(std::vector<T> v)
        {
            static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "[Type Error][getMedian] Vector type must be int or double");

            std::sort(v.begin(), v.end());
            return v.size() % 2 == 0 ? (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2.0 : v[v.size() / 2];
        }

        template<typename T>
        double getMedian(const std::initializer_list<T>& v)
        {
            return getMedian(std::vector<T>(v));
        }

        template<typename T>
        std::vector<T> getMode(const std::vector<T>& v)
        {
            static_assert(std::is_arithmetic_v<T> || std::is_same_v<T, std::string>, "[Type Error][getMode] Vector type must be primitive");

            if(v.empty()) {
                return v;
            }

            std::unordered_map<T, int> m;
            int freq = 0;
            for(int i = 0; i < v.size(); i++) {
                m[v[i]]++;
                if(m.at(v[i]) > freq) {
                    freq = m.at(v[i]);
                }
            }

            std::vector<T> modes;
            for(const auto& i : m) {
                if(i.second == freq) {
                    modes.push_back(i.first);
                }
            }
            return modes;
        }

        template<typename T>
        std::vector<T> getMode(const std::initializer_list<T>& v)
        {
            return getMode(std::vector<T>(v));
        }

        std::vector<std::string> getMode(const std::initializer_list<const char*>& v)
        {
            return getMode(std::vector<std::string>(v.begin(), v.end()));
        }

        template<typename T>
        double getMidrange(std::vector<T> v)
        {
            static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "[Type Error][getMedian] Vector type must be int or double");

            if(v.empty()) {
                return 0;
            }

            double low = v[0];
            double high = v[0];
            for(int i = 0; i < v.size(); i++) {
                if(v[i] < low) {
                    low = v[i];
                }
                if(v[i] > high) {
                    high = v[i];
                }
            }
            return (low + high) / 2;
        }

        template<typename T>
        double getMidrange(const std::initializer_list<T>& v)
        {
            return getMidrange(std::vector<T>(v));
        }
        
    }

    namespace string {
        std::string toupper(std::string str)
        {
            for(int i = 0; i < str.size(); i++) {
                str[i] = std::toupper(str[i]);
            }
            return str;
        }

        std::string tolower(std::string str)
        {
            for(int i = 0; i < str.size(); i++) {
                str[i] = std::tolower(str[i]);
            }
            return str;
        }

        bool equalIgnoreCase(const std::string& str1, const std::string& str2)
        {
            if(str1.size() != str2.size()) {
                return false;
            }

            for(int i = 0; i < str1.size(); i++) {
                if(std::tolower(str1[i]) != std::tolower(str2[i])) {
                    return false;
                }
            }
            return true;
        }

        void replaceAll(std::string& str, const std::string& replace, const std::string& replace_with)
        {
            if(replace.empty()) {
                return;
            }

            int i = 0;
            while(i < str.size()) {
                if(str[i] == replace[0]) {
                    int n = i;
                    int j = 0;
                    while(i < str.size() && j < replace.size() && str[i] == replace[j]) {
                        i++;
                        j++;
                    }
                    if(j >= replace.size()) {
                        str.replace(n, replace.size(), replace_with);
                    }
                } else {
                    i++;
                }
            }
        }

        void replaceAll(std::string& str, const std::vector<std::string>& replace, const std::string& replace_with)
        {
            for(int i = 0; i < replace.size(); i++) {
                replaceAll(str, replace[i], replace_with);
            }
        }

        std::string trim(const std::string& str)
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
                }
                trimmed.push_back(str[i]);
                i++;
            }
            return trimmed;
        }

        std::vector<std::string> split(const std::string& str, const std::string& separators)
        {
            std::vector<std::string> v;
            if(str.empty()) {
                return v;
            }

            std::unordered_set<char> reg;
            for(int i = 0; i < separators.size(); i++) {
                reg.insert(separators[i]);
            }

            std::string temp;
            int i = 0;
            while(i < str.size()) {
                while(reg.count(str[i]) > 0) {
                    i++;
                }
                if(i == str.size()-1 || reg.count(str[i+1]) > 0) {
                    temp += str[i];
                    v.push_back(temp);
                    temp.clear();
                    i += 2;
                } else {
                    temp += str[i];
                    i++;
                }
            }
            return v;
        }
    }

    namespace parse {
        int parseInteger(const std::string& str, int occurance = 0)
        {
            if(str.empty()) {
                throw std::logic_error("[Error][parseInteger] String is empty");
            }

            std::stringstream ss(str);
            int n = 0;
            if(occurance < 1) {
                if(!isdigit(str[0])) {
                    throw std::logic_error("[Error][parseInteger] No integer found");
                }
                ss >> n;
                return n;
            } else {
                char temp;
                int freq = 0;
                while(ss >> temp) {
                    if(isdigit(temp)) {
                        freq++;
                        ss.unget();
                        ss >> n;
                        if(freq == occurance) {
                            return n;
                        }
                    } 
                }
                throw std::logic_error("[Error][parseInteger] No integer found");
            }
        }

        int parseInteger(char ch)
        {
            return isdigit(ch) ? ch - '0' : throw std::logic_error("[Error][parseInteger] Argument is not a integer");
        }

        std::vector<int> parseIntegers(const std::string& str, int limit = -1)
        {
            std::vector<int> v;
            if(str.empty()) {
                throw std::logic_error("[Error][parseIntegers] String is empty");
            }

            std::stringstream ss(str);
            char temp;
            int n = 0;
            int counter = 0;
            while(ss >> temp) {
                if(limit >= 0 && counter == limit) {
                    return v;
                }
                if(isdigit(temp)) {
                    ss.unget();
                    ss >> n;
                    v.push_back(n);
                    counter++;
                }
            }
            return v;
        }

        double parseFloat(const std::string& str, int occurance = 0)
        {
            if(str.empty()) {
                throw std::logic_error("[Error][parseInteger] String is empty");
            }

            std::stringstream ss(str);
            double n = 0;
            if(occurance < 1) {
                if(!isdigit(str[0])) {
                    throw std::logic_error("[Error][parseFloat] No integer found");
                }
                ss >> n;
                return n;
            } else {
                char temp;
                int freq = 0;
                while(ss >> temp) {
                    if(isdigit(temp)) {
                        freq++;
                        ss.unget();
                        ss >> n;
                        if(freq == occurance) {
                            return n;
                        }
                    } 
                }
                throw std::logic_error("[Error][parseFloat] No integer found");
            }
        }

        std::vector<double> parseFloats(const std::string& str, int limit = -1)
        {
            std::vector<double> v;
            if(str.empty()) {
                throw std::logic_error("[Error][parseFloats] String is empty");
            }

            std::stringstream ss(str);
            char temp;
            double n = 0;
            int counter = 0;
            while(ss >> temp) {
                if(limit >= 0 && counter == limit) {
                    return v;
                }
                if(isdigit(temp)) {
                    ss.unget();
                    ss >> n;
                    v.push_back(n);
                    counter++;
                }
            }
            return v;
        }
    }

    namespace container {
        template<typename T>
        void replaceAll(std::vector<T>& v, const std::vector<T>& values_to_replace, const T& new_val)
        {
            std::unordered_set<T> s;
            for(int i = 0; i < values_to_replace.size(); i++) {
                s.insert(values_to_replace[i]);
            }

            for(int i = 0; i < v.size(); i++) {
                if(s.count(v[i]) > 0) {
                    v[i] = new_val;
                }
            }
        }

        template<typename T>
        void replaceAll(std::vector<T>& v, const std::initializer_list<T>& values_to_replace, const T& new_val)
        {
            replaceAll(v, std::vector<T>(values_to_replace), new_val);
        }

        template<typename T>
        void replaceAll(std::vector<T>& v, const T& value_to_replace, const T& new_val)
        {
            for(int i = 0; i < v.size(); i++) {
                if(v[i] == value_to_replace) {
                    v[i] = new_val;
                }
            }
        }
    }
}
