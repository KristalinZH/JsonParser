#ifndef JSONOBJECT
#define JSONOBJECT

#include <list>
#include <unordered_map>
#include <vector>
#include "JsonValue.hpp"

class JsonObject : public JsonValue {
    public:
        ValueType getType() const override;
        JsonValue* clone() const override;
        void print(std::ostream& stream) const override;
        void accept(JsonValueVisitor& visitor) override;

        JsonObject() = default;
        JsonObject(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData);
        JsonObject(const JsonObject& other);
        JsonObject& operator=(const JsonObject& other);
        JsonObject(JsonObject&& other) noexcept;
        JsonObject& operator=(JsonObject&& other) noexcept;
        ~JsonObject();

        size_t getSize() const;
        std::vector<std::string> getKeys() const;
        std::vector<const JsonValue*> getValues() const;
        bool containsKey(const std::string& key) const;
        void addKVP(const std::string& key, const JsonValue* const value);
        void editKVP(const std::string& key, const JsonValue* const value);
        void removeKVP(const std::string& key);
        const JsonValue* getValue(const std::string& key) const;
    private:
        std::list<std::string> keys;
        std::unordered_map<std::string, JsonValue*> values;

        void copyData(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData);
        void resetData(std::unordered_map<std::string, JsonValue*>& _objectData);
        void deleteData();
};


#endif