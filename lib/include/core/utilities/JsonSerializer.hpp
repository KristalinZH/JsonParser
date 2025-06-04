#ifndef JSONSERIALIZER
#define JSONSERIALIZER

#include <iostream>
#include "Path.hpp"
#include "JsonValue.hpp"

/**
 * @brief Class for serializing JSON values to output streams
 */
class JsonSerializer {
    public:
        /**
         * @brief Saves a JSON value to an output stream
         * @param json Pointer to the constant JSON value to save
         * @param stream Output stream to write to
         * @param path Optional path within the JSON to save specific part
         */
        static void save(const JsonValue* const json, std::ostream& stream, const std::string& path);
};

#endif