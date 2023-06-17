#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <initializer_list>
#include <type_traits>

namespace utility {
    namespace print {
        template<typename T>
        void print(const std::vector<T>& v, char append = '\0', const std::string& separator = ", ") 
        {
            std::cout << "{";
            for (std::size_t i = 0; i < v.size(); i++) {
                if constexpr (std::is_scalar_v<T> || std::is_same_v<T, std::string>) {
                    std::cout << v[i];
                } else {
                    print(v[i], '\0', separator);
                }

                if (i != v.size() - 1) {
                    std::cout << separator;
                }
            }
            std::cout << "}" << append;
        }

        template<typename T1, typename T2>
        void print(const std::vector<std::pair<T1, T2>>& p, char append = '\0', const std::string& separator = ", ")
        {
            std::cout << "{";
            for (std::size_t i = 0; i < p.size(); ++i) {
                std::cout << "(" << p[i].first << ", " << p[i].second << ")";

                if (i != p.size() - 1) {
                    std::cout << separator;
                }
            }
            std::cout << "}" << append;
        }

        template<typename K, typename V>
        void print(const std::map<K, V>& m, char append = '\0', const std::string& separator = ", ")
        {
            std::cout << "{";
            for(typename std::map<K, V>::const_iterator it = m.begin(); it != m.end(); it++) {
                std::cout << "[" << (*it).first << " : " << (*it).second << "]";
                if(std::next(it) != m.end()) {
                    std::cout << separator;
                }
            }
            std::cout << "}" << append;
        }

        template<typename K, typename V>
        void print(const std::unordered_map<K, V>& m, char append = '\0', const std::string& separator = ", ")
        {
            std::cout << "{";
            for(typename std::unordered_map<K, V>::const_iterator it = m.begin(); it != m.end(); it++) {
                std::cout << "[" << (*it).first << " : " << (*it).second << "]";
                if(std::next(it) != m.end()) {
                    std::cout << separator;
                }
            }
            std::cout << "}" << append;
        }

        template<typename T>
        void print(const std::set<T>& s, char append = '\0', const std::string& separator = ", ")
        {
            std::cout << "{";
            for(auto it = s.begin(); it != s.end(); it++) {
                std::cout << *it;
                if(std::next(it) != s.end()) {
                    std::cout << separator;
                }
            }
            std::cout << "}" << append;
        }

        template<typename T>
        void print(const std::unordered_set<T>& us, char append = '\0', const std::string& separator = ", ")
        {
            std::cout << "{";
            for(auto it = us.begin(); it != us.end(); it++) {
                std::cout << *it;
                if(std::next(it) != us.end()) {
                    std::cout << separator;
                }
            }
            std::cout << "}" << append;
        }

        template<typename T>
        void printIterators(const std::vector<T>& v, const std::initializer_list<int>& index, bool prompt = true)
        {
            std::cout << "===========================" << std::endl;
            char ch = 'i';
            std::cout << "Iterators: [";
            for(auto it = index.begin(); it != index.end(); it++) {
                std::cout << ch << " = " << *it;
                if(it < index.end()-1) {
                    std::cout << ", ";
                }
                ch++;
            }
            std::cout << "]" << std::endl;

            std::vector<int> pos; // get the positions of the elements in str
            std::string str;
            for(int i = 0; i < v.size(); i++) {
                if(i == 0) {
                    str += "{";
                }
                std::string temp;
                if constexpr(std::is_same<T, std::string>::value) {
                    temp = v[i];
                } else {
                    temp = std::to_string(v[i]);
                }
                int k = str.size() + (temp.size() / 2);
                if(temp.size() % 2 == 0) { // not necessary, for format only
                    k--;
                }
                pos.push_back(k);
                str += temp;
                if(i < v.size()-1) {
                    str += ", ";
                } else {
                    str += "}";
                }
            }
            
            std::cout << str << std::endl;

            ch = 'i';
            int j = 0;
            for(auto it = index.begin(); it != index.end(); it++) {
                if(*it < 0 || *it >= v.size()) {
                    continue;
                }
                while(j < pos[*it]) {
                    std::cout << " ";
                    j++;
                }
                std::cout << ch << std::endl;
                ch++; // increment ch so a new iterator is displayed
                j = 0;
            }
            std::cout << "===========================" << std::endl;
            if(prompt) {
                std::cout << "Press enter to continue...";
                if(std::cin.get() != '\n') {
                    std::cin.ignore(256, '\n');
                    std::cin.clear();
                }
            }
        }

        void printIterators(const std::string& str, const std::initializer_list<int>& index, bool prompt = true)
        {
            std::cout << "===========================" << std::endl;
            char ch = 'i';
            std::cout << "Iterators: [";
            for(auto it = index.begin(); it != index.end(); it++) {
                std::cout << ch << " = " << *it;
                if(it < index.end()-1) {
                    std::cout << ", ";
                }
                ch++;
            }
            std::cout << "]" << std::endl;

            std::vector<int> pos;
            std::string temp;
            for(int i = 0; i < str.size(); i++) {
                if(i == 0) {
                    temp += "{";
                }
                temp += str[i];
                pos.push_back(temp.size()-1);
                if(i < str.size()-1) {
                    temp += ", ";
                } else {
                    temp += "}";
                }
            }
            
            std::cout << temp << std::endl;

            ch = 'i';
            int j = 0;
            for(auto it = index.begin(); it != index.end(); it++) {
                if(*it < 0 || *it >= str.size()) {
                    continue;
                }
                while(j < pos[*it]) {
                    std::cout << " ";
                    j++;
                }
                std::cout << ch << std::endl;
                ch++; // increment ch so a new iterator is displayed
                j = 0;
            }
            std::cout << "===========================" << std::endl;
            if(prompt) {
                std::cout << "Press enter to continue...";
                if(std::cin.get() != '\n') {
                    std::cin.ignore(256, '\n');
                    std::cin.clear();
                }
            }
        }
    }
}



