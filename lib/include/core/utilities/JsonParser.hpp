#ifndef JSONPARSER
#define JSONPARSER

#include <memory>
#include "JsonObject.hpp"

class JsonParser{
    public:
        std::pair<std::string, std::unique_ptr<JsonValue>> parse();
};

#endif