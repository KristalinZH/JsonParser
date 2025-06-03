#ifndef JSONFACTORY
#define JSONFACTORY

#include "JsonValue.hpp"
#include "JsonObject.hpp"

class JsonFactory {
    public:
        static JsonValue* create(const std::string& value);
        static JsonValue* create(const std::vector<JsonValue*>& values);
        static JsonValue* create(const std::list<std::string>& keys, const std::unordered_map<std::string, JsonValue*>& values);
};

#endif