#ifndef PATHVALIDATOR
#define PATHVALIDATOR

#include <vector>
#include <string>
#include "JsonObject.hpp"

class Path {
    public:
        static bool validatePath(const JsonValue* const value, const std::string& path);
        static const JsonValue* getValue(const JsonValue* const rootValue, const std::string& path);
        static const JsonValue* getLastElement(const JsonValue* const rootValue, const std::string& path);
        static const JsonObject* getParent(const JsonValue* const rootValue, const std::string& path);
        static std::string getKey(const std::string& path);
        static std::string getLastPath(const JsonValue* const rootValue, const std::string& path);
        static std::string getRoot(const std::string& path);
        static std::string getChildren(const std::string& path);
};

#endif