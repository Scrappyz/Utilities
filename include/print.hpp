#pragma once

#include <iostream>
#include <iomanip>
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

template<typename T>
void print(const T& arg, char append = '\0')
{
    std::cout << arg << append;
}

template<typename T>
void printTable(const std::vector<std::vector<T>>& v)
{
    // Get the number of rows and columns in the table
    int numRows = v.size();
    int numCols = (numRows > 0) ? v[0].size() : 0;

    // Calculate the maximum width of each column based on the longest element
    std::vector<int> maxColWidths(numCols, 0);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            int elementWidth = std::to_string(v[i][j]).length();
            if (elementWidth > maxColWidths[j]) {
                maxColWidths[j] = elementWidth;
            }
        }
    }

    // Print the table header
    for (int j = 0; j < numCols; ++j) {
        std::cout << std::setw(maxColWidths[j]) << std::right << "Column " << j << " | ";
    }
    std::cout << std::endl;

    // Print the separator row
    for (int j = 0; j < numCols; ++j) {
        std::cout << "-+-" << std::string(maxColWidths[j], '-') << "-+-";
    }
    std::cout << std::endl;

    // Print each row of the table
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            std::cout << " | " << std::setw(maxColWidths[j]) << std::right << v[i][j] << " | ";
        }
        std::cout << std::endl;
    }
}


