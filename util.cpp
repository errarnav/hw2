#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> words;
    std::string current = "";
    
    for(size_t i = 0; i < rawWords.length(); i++) {
        char c = rawWords[i];
        
        if(isalnum(c)) {
            current += tolower(c);
        } else {
            if(current.length() >= 2) {
                words.insert(current);
            }
            current = "";
        }
    }
    
    if(current.length() >= 2) {
        words.insert(current);
    }
    
    return words;
}

std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}