#ifndef JSONSEARCHER
#define JSONSEARCHER

#include <string>
#include <regex>
#include "JsonArray.hpp"

class JsonSearcher{
    public:
        std::string search(const JsonValue& json,const std::regex& reg);
};

#endif