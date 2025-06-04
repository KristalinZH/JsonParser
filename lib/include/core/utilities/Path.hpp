#ifndef PATHVALIDATOR
#define PATHVALIDATOR

#include <vector>
#include <string>
#include "JsonObject.hpp"

/**
 * @brief Utility class for JSON path operations and validation
 */
class Path {
    public:
        /**
         * @brief Validates if a path exists in the JSON structure
         * @param value Pointer to the root JSON value
         * @param path Path to validate
         * @return True if path is valid, false otherwise
         */
        static bool validatePath(const JsonValue* const value, const std::string& path);

        /**
         * @brief Gets the JSON value at the specified path
         * @param rootValue Pointer to the root JSON value
         * @param path Path to the desired value
         * @return Pointer to the JSON value at the path
         */
        static const JsonValue* getValue(const JsonValue* const rootValue, const std::string& path);

        /**
         * @brief Gets the last element in the path
         * @param rootValue Pointer to the root JSON value
         * @param path Path to traverse
         * @return Pointer to the last JSON value in the path
         */
        static const JsonValue* getLastElement(const JsonValue* const rootValue, const std::string& path);

        /**
         * @brief Gets the parent object of a path
         * @param rootValue Pointer to the root JSON value
         * @param path Path to the child element
         * @return Pointer to the parent JSON object
         */
        static const JsonObject* getParent(const JsonValue* const rootValue, const std::string& path);

        /**
         * @brief Extracts the key from a path
         * @param path Path to extract key from
         * @return The extracted key
         */
        static std::string getKey(const std::string& path);

        /**
         * @brief Gets the last segment of a path
         * @param rootValue Pointer to the root JSON value
         * @param path Full path
         * @return The last path segment
         */
        static std::string getLastPath(const JsonValue* const rootValue, const std::string& path);

        /**
         * @brief Gets the root segment of a path
         * @param path Path to extract root from
         * @return The root path segment
         */
        static std::string getRoot(const std::string& path);

        /**
         * @brief Gets the child segments of a path
         * @param path Path to extract children from
         * @return The child path segments
         */
        static std::string getChildren(const std::string& path);
};

#endif