#include <algorithm>
#include "JsonValueVisitor.hpp"
#include "JsonFormatConfig.hpp"


ValueType JsonObject::getType() const {
    return ValueType::Object;
}

JsonValue* JsonObject::clone() const {
    return new JsonObject(*this);
}

void JsonObject::print(std::ostream& stream) const {
    stream << JsonFormatConfig::getFormatter() -> format(this);
}

void JsonObject::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}

JsonObject::JsonObject(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData) {
    copyData(_keys, _objectData);
}

JsonObject::JsonObject(const JsonObject& other) {
    copyData(other.keys, other.values);
}

JsonObject& JsonObject::operator=(const JsonObject& other) {
     if(this != &other) {
        deleteData();
        values.clear();
        copyData(other.keys, other.values);
    }

    return *this;
}

JsonObject::JsonObject(JsonObject&& other) noexcept {
    keys = other.keys;
    values = other.values;
    resetData(other.values);
}

JsonObject& JsonObject::operator=(JsonObject&& other) noexcept {
    if(this != &other){
        deleteData();
        values = other.values;
        resetData(other.values);
    }

    return *this;
}

JsonObject::~JsonObject() {
    deleteData();
}

void JsonObject::copyData(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData) {
    keys = _keys;

    for(auto it = _objectData.begin(); it != _objectData.end(); it++) {
        values.emplace(it -> first, it -> second -> clone());
    }
}

void JsonObject::resetData(std::unordered_map<std::string, JsonValue*>& _objectData) {
    for(auto it = _objectData.begin(); it != _objectData.end(); it++) {
        it -> second = nullptr;
    }
}

void JsonObject::deleteData() {
    for(auto it = values.begin(); it != values.end(); it++) {
        delete it -> second;

        it -> second = nullptr;
    }
}

size_t JsonObject::getSize() const {
    return values.size();
}

std::vector<std::string> JsonObject::getKeys() const {
    std::vector<std::string> _keys(values.size());
    size_t index = 0;

    for(const std::string& key : keys){
        _keys[index++] = key;
    }

    return _keys;
}

std::vector<const JsonValue*> JsonObject::getValues() const {
    std::vector<const JsonValue*> _values(values.size());
    size_t index = 0;

    for(const std::string& key : keys){
        _values[index++] = values.at(key) -> clone();
    }

    return _values;
}

bool JsonObject::containsKey(const std::string& key) const {
    return values.find(key) != values.end();
}

void JsonObject::addKVP(const std::string& key, const JsonValue* const value) {
    if(containsKey(key)){
        const std::string message = "Key \"" + key + "\" already exists in JsonObject!";
        throw std::runtime_error(message);
    }

    values.emplace(key, value -> clone());
    keys.push_back(key);
}

void JsonObject::editKVP(const std::string& key, const JsonValue* const value) {
    delete values.at(key);

    values[key] = value -> clone();
}

void JsonObject::removeKVP(const std::string& key) {
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

    delete values.at(key);
    values.erase(key);
}

const JsonValue* JsonObject::getValue(const std::string& key) const {
    if(!containsKey(key)){
        const std::string message = "Key \"" + key + "\" does not exist in JsonObject!";
        throw std::runtime_error(message);
    }

    return values.at(key);
}
