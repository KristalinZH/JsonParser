#ifndef JSONSERIALIZER
#define JSONSERIALIZER

#include <iostream>
#include <string>
#include "JsonValue.hpp"

class JsonSerializer{
    public:
        void save(const JsonValue& json, std::ostream& stream, const std::string& path = "");
};

#endif