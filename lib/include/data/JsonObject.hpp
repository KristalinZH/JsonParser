#ifndef JSONOBJECT
#define JSONOBJECT

#include <unordered_map>
#include <list>
#include <vector>
#include "JsonValue.hpp"

class JsonObject{
    public:
        JsonObject();
        explicit JsonObject(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue>& _objectData);
        JsonObject(const JsonObject& other);
        JsonObject& operator=(const JsonObject& other);
        JsonObject(JsonObject&& other) noexcept;
        JsonObject& operator=(JsonObject&& other) noexcept;
        ~JsonObject();

        size_t getSize() const;
        std::vector<std::string> getKeys() const;
        std::vector<JsonValue> getValues() const;
        bool containsKey(const std::string& key) const;
        void addKVP(const std::string& key, const JsonValue& value);
        void removeKVP(const std::string key);
        const JsonValue& getValue(const std::string key) const;
        void setValue(const std::string& key, const JsonValue& value);

        friend std::ostream& operator<<(std::ostream& os, const JsonObject& jsonObject);
    private:
        std::list<std::string> keys;
        std::unordered_map<std::string, JsonValue> objectData;
};

#endif