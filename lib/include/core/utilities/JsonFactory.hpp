#ifndef JSONFACTORY
#define JSONFACTORY

#include "JsonValue.hpp"
#include "JsonObject.hpp"

/**
 * @brief Factory class for creating different types of JSON values
 */
class JsonFactory {
    public:
        /**
         * @brief Creates a JSON value from a string representation
         * @param value String representation of the JSON value
         * @return Pointer to the created JsonValue
         */
        static JsonValue* create(const std::string& value);

        /**
         * @brief Creates a JSON array from a vector of JSON values
         * @param values Vector of pointers to JSON values
         * @return Pointer to the created JsonArray
         */
        static JsonValue* create(const std::vector<JsonValue*>& values);

        /**
         * @brief Creates a JSON object from keys and values
         * @param keys List of keys for the object
         * @param values Map of key-value pairs
         * @return Pointer to the created JsonObject
         */
        static JsonValue* create(const std::list<std::string>& keys, const std::unordered_map<std::string, JsonValue*>& values);
};

#endif