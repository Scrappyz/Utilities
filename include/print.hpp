#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

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


