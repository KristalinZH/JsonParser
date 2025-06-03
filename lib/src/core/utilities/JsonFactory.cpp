#include <cctype>
#include "JsonFactory.hpp"
#include "JsonNull.hpp"
#include "JsonBoolean.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"
#include "JsonArray.hpp"

JsonValue* JsonFactory::create(const std::string& value) {
    if(value == "null") {
        return new JsonNull();
    }
    if(value == "true" || value == "false") {
        const bool bvalue = value == "true" ? true : false;
        return new JsonBoolean(bvalue);
    }
    if(value[0] == '-' || isdigit(value[0])){
        return new JsonNumber(value);
    }
    if(value[0] == '\"'){
        return new JsonString(value);
    }
    if(value == "[") {
        return new JsonArray();
    }
    return new JsonObject();
}

JsonValue* JsonFactory::create(const std::vector<JsonValue*>& values) {
    return new JsonArray(values);
}

JsonValue* JsonFactory::create(const std::list<std::string>& keys, const std::unordered_map<std::string, JsonValue*>& values) {
    return new JsonObject(keys, values);
}