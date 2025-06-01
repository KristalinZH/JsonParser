#ifndef JSONEDITOR
#define JSONEDITOR

#include "JsonValue.hpp"

class JsonEditor{
    public:
        void set(JsonValue& json, const std::string& path, const std::string value);
        void create(JsonValue& json,const std::string& path, const std::string value);
        void erase(JsonValue& json, const std::string& path);
        void move(JsonValue& json,const std::string& from, const std::string& to);
};

#endif