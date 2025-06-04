#include "Path.hpp"
#include "JsonObject.hpp"

/**
 * @brief Validates if a path exists in the JSON structure
 * @param value Pointer to the JSON value to validate against
 * @param path Path to validate
 * @return True if path is valid, false otherwise
 */
bool Path::validatePath(const JsonValue* const value, const std::string& path) {

    if(value == nullptr) {
        return false;
    }

    if(path[path.length() - 1] == '/') {
        return false;
    }

    if(path == "")
        return true;

    if(value -> getType() != ValueType::Object)
        return false;

    const std::string root = getRoot(path);
    const JsonObject* pobj = static_cast<const JsonObject*>(value);

    if(!(pobj -> containsKey(root)))
        return false;

    return validatePath(pobj -> getValue(root), getChildren(path));
}

/**
 * @brief Gets the JSON value at the specified path
 * @param rootValue Pointer to the root JSON value
 * @param path Path to traverse
 * @return Pointer to the JSON value at the path
 */
const JsonValue* Path::getValue(const JsonValue* const rootValue, const std::string& path) {
    if(path == "")
        return rootValue;

    const std::string root = getRoot(path);
    const JsonObject* pobj = static_cast<const JsonObject*>(rootValue);
    return getValue(pobj -> getValue(root), getChildren(path));
}

/**
 * @brief Gets the last element in the path
 * @param rootValue Pointer to the root JSON value
 * @param path Path to traverse
 * @return Pointer to the last JSON value in the path
 */
const JsonValue* Path::getLastElement(const JsonValue* const rootValue, const std::string& path) {

    if(rootValue -> getType() != ValueType::Object) {
        return rootValue;
    }

    const JsonObject* pobj = static_cast<const JsonObject*>(rootValue);
    const std::string root = getRoot(path);

    if(!(pobj -> containsKey(root))) {
        return pobj;
    }

    return getLastElement(pobj -> getValue(root), getChildren(path));
}

/**
 * @brief Gets the parent object of a path
 * @param rootValue Pointer to the root JSON value
 * @param path Path to traverse
 * @return Pointer to the parent JSON object
 */
const JsonObject* Path::getParent(const JsonValue* const rootValue, const std::string& path) {

    if(getChildren(path) == "") {
        return static_cast<const JsonObject*>(rootValue);
    }

    const std::string root = getRoot(path);
    const JsonObject* pobj = static_cast<const JsonObject*>(rootValue);
    return getParent(pobj -> getValue(root), getChildren(path));
}

/**
 * @brief Gets the key from the last segment of a path
 * @param path Path to extract key from
 * @return The extracted key
 */
std::string Path::getKey(const std::string& path) {
    if(getChildren(path) == "") {
        return path;
    }

    return getKey(getChildren(path));
}

/**
 * @brief Gets the last valid path segment
 * @param rootValue Pointer to the root JSON value
 * @param path Path to process
 * @return The last valid path segment
 */
std::string Path::getLastPath(const JsonValue* const rootValue, const std::string& path) {

    if(rootValue -> getType() != ValueType::Object) {
        return path;
    }

    const JsonObject* pobj = static_cast<const JsonObject*>(rootValue);
    const std::string root = getRoot(path);

    if(!(pobj -> containsKey(root))) {
        return path;
    }

    return getLastPath(pobj -> getValue(root), getChildren(path));
}

/**
 * @brief Gets the root segment of a path
 * @param path Path to extract root from
 * @return The root segment (before first '/')
 */
std::string Path::getRoot(const std::string& path) {
    const size_t slash_pos = path.find('/');

    if (slash_pos == std::string::npos) {
        return path;
    }

    return path.substr(0, slash_pos);
}

/**
 * @brief Gets the children segments of a path
 * @param path Path to extract children from
 * @return Everything after the first '/' or empty string
 */
std::string Path::getChildren(const std::string& path) {

    const size_t slash_pos = path.find('/');

    if (slash_pos == std::string::npos || slash_pos + 1 >= path.length()) {
        return "";
    }
    
    return path.substr(slash_pos + 1);

}