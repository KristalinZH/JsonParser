#ifndef JSONSERIALIZER
#define JSONSERIALIZER

#include <iostream>
#include "Path.hpp"
#include "JsonValue.hpp"

class JsonSerializer {
    public:
        static void save(const JsonValue* const json, std::ostream& stream, const std::string& path);
};

#endif