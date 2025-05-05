#include <algorithm>
#include "JsonObject.hpp"
#include "formatters/JsonFormatConfig.hpp"

JsonObject::JsonObject() = default;

JsonObject::JsonObject(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue>& _objectData) : keys(_keys), objectData(_objectData) {}

JsonObject::JsonObject(const JsonObject& other) : keys(other.keys), objectData(other.objectData) {}

JsonObject& JsonObject::operator=(const JsonObject& other){
    if(this != &other){
        keys = other.keys;
        objectData = other.objectData;
    }

    return *this;
}

JsonObject::JsonObject(JsonObject&& other) noexcept : keys(std::move(other.keys)),  objectData(std::move(other.objectData)) {}

JsonObject& JsonObject::operator=(JsonObject&& other) noexcept {
    if(this != &other){
        keys = std::move(other.keys);
        objectData = std::move(other.objectData);
    }

    return *this;
}

JsonObject::~JsonObject() = default;

size_t JsonObject::getSize() const {
    return objectData.size();
}

std::vector<std::string> JsonObject::getKeys() const {
    std::vector<std::string> vkeys(objectData.size());
    size_t index = 0;

    for(const std::string& key : keys){
        vkeys[index++] = key;
    }

    return vkeys;
}

std::vector<JsonValue> JsonObject::getValues() const {
    std::vector<JsonValue> values(objectData.size());
    size_t index = 0;

    for(const std::string& key : keys){
        values[index++] = objectData.at(key);
    }

    return values;
}

bool JsonObject::containsKey(const std::string& key) const {
    return objectData.find(key) != objectData.end();
}

void JsonObject::addKVP(const std::string& key, const JsonValue& value){
    if(containsKey(key)){
        const std::string message = "Key \"" + key + "\" already exists in JsonObject!";
        throw std::runtime_error(message);
    }

    objectData.emplace(key, value);
    keys.push_back(key);
}

void JsonObject::removeKVP(const std::string key){
    if(!containsKey(key)){
        const std::string message = "Key \"" + key + "\" does not exist in JsonObject!";
        throw std::runtime_error(message);
    }

    const auto& keyIterator = std::find(keys.begin(), keys.end(), key); 

    if(keyIterator == keys.end()){
        const std::string message = "Key \"" + key + "\" does not found in keys list!";
        throw std::runtime_error(message);
    }

    keys.erase(keyIterator);
    objectData.erase(key);
}

const JsonValue& JsonObject::getValue(const std::string key) const {
    if(!containsKey(key)){
        const std::string message = "Key \"" + key + "\" does not exist in JsonObject!";
        throw std::runtime_error(message);
    }

    return objectData.at(key);
}

void JsonObject::setValue(const std::string& key, const JsonValue& value){
    if(!containsKey(key)){
        const std::string message = "Key \"" + key + "\" does not exist in JsonObject!";
        throw std::runtime_error(message);
    }

    objectData.at(key) = value;
}

std::ostream& operator<<(std::ostream& os, const JsonObject& jsonObject){
    
    const std::shared_ptr<JsonFormatter> formatter = JsonFormatConfig::getFormatter();

    os << formatter -> format(jsonObject);

    return os;
}