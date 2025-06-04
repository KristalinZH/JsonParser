#include <cctype>
#include "JsonFactory.hpp"
#include "JsonNull.hpp"
#include "JsonBoolean.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"
#include "JsonArray.hpp"

/**
 * @brief Creates a JSON value from a string representation
 * @param value String representation of the JSON value
 * @return Pointer to the created JsonValue
 */
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

/**
 * @brief Creates a JSON array from a vector of values
 * @param values Vector of pointers to JSON values
 * @return Pointer to the created JsonArray
 */
JsonValue* JsonFactory::create(const std::vector<JsonValue*>& values) {
    return new JsonArray(values);
}

/**
 * @brief Creates a JSON object from keys and values
 * @param keys List of keys for the object
 * @param values Map of key-value pairs
 * @return Pointer to the created JsonObject
 */
JsonValue* JsonFactory::create(const std::list<std::string>& keys, const std::unordered_map<std::string, JsonValue*>& values) {
    return new JsonObject(keys, values);
}