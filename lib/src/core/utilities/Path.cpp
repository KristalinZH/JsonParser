#include "Path.hpp"
#include "JsonObject.hpp"

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

const JsonValue* Path::getValue(const JsonValue* const rootValue, const std::string& path) {
    if(path == "")
        return rootValue;

    const std::string root = getRoot(path);
    const JsonObject* pobj = static_cast<const JsonObject*>(rootValue);
    return getValue(pobj -> getValue(root), getChildren(path));
}

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

const JsonObject* Path::getParent(const JsonValue* const rootValue, const std::string& path) {

    if(getChildren(path) == "") {
        return static_cast<const JsonObject*>(rootValue);
    }

    const std::string root = getRoot(path);
    const JsonObject* pobj = static_cast<const JsonObject*>(rootValue);
    return getParent(pobj -> getValue(root), getChildren(path));
}

std::string Path::getKey(const std::string& path) {
    if(getChildren(path) == "") {
        return path;
    }

    return getKey(getChildren(path));
}

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

std::string Path::getRoot(const std::string& path) {
    const size_t slash_pos = path.find('/');

    if (slash_pos == std::string::npos) {
        return path;
    }

    return path.substr(0, slash_pos);
}

std::string Path::getChildren(const std::string& path) {

    const size_t slash_pos = path.find('/');

    if (slash_pos == std::string::npos || slash_pos + 1 >= path.length()) {
        return "";
    }
    
    return path.substr(slash_pos + 1);

}