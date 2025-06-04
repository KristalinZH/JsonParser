#include <algorithm>
#include "JsonValueVisitor.hpp"
#include "JsonFormatConfig.hpp"

/**
 * @brief Gets the type of JSON value
 * @return ValueType::Object
 */
ValueType JsonObject::getType() const {
    return ValueType::Object;
}

/**
 * @brief Creates a deep copy of the object
 * @return Pointer to the cloned object
 */
JsonValue* JsonObject::clone() const {
    return new JsonObject(*this);
}

/**
 * @brief Prints object content to stream
 * @param stream Output stream to print to
 */
void JsonObject::print(std::ostream& stream) const {
    stream << JsonFormatConfig::getFormatter() -> format(this);
}

/**
 * @brief Accepts a visitor for the Visitor pattern
 * @param visitor Reference to the visitor
 */
void JsonObject::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}

/**
 * @brief Constructor that initializes object with keys and values
 * @param _keys List of keys
 * @param _objectData Map of key-value pairs
 */
JsonObject::JsonObject(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData) {
    copyData(_keys, _objectData);
}

/**
 * @brief Copy constructor
 * @param other Object to copy from
 */
JsonObject::JsonObject(const JsonObject& other) {
    copyData(other.keys, other.values);
}

/**
 * @brief Copy assignment operator
 * @param other Object to copy from
 * @return Reference to this object
 */
JsonObject& JsonObject::operator=(const JsonObject& other) {
     if(this != &other) {
        deleteData();
        values.clear();
        copyData(other.keys, other.values);
    }

    return *this;
}

/**
 * @brief Move constructor
 * @param other Object to move from
 */
JsonObject::JsonObject(JsonObject&& other) noexcept {
    keys = other.keys;
    values = other.values;
    resetData(other.values);
}

/**
 * @brief Move assignment operator
 * @param other Object to move from
 * @return Reference to this object
 */
JsonObject& JsonObject::operator=(JsonObject&& other) noexcept {
    if(this != &other){
        deleteData();
        values = other.values;
        resetData(other.values);
    }

    return *this;
}

/**
 * @brief Destructor that cleans up object contents
 */
JsonObject::~JsonObject() {
    deleteData();
}

/**
 * @brief Helper method to deep copy object data
 * @param _keys List of keys to copy
 * @param _objectData Map of values to copy
 */
void JsonObject::copyData(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData) {
    keys = _keys;

    for(auto it = _objectData.begin(); it != _objectData.end(); it++) {
        values.emplace(it -> first, it -> second -> clone());
    }
}

/**
 * @brief Helper method to reset object data
 * @param _objectData Map of values to reset
 */
void JsonObject::resetData(std::unordered_map<std::string, JsonValue*>& _objectData) {
    for(auto it = _objectData.begin(); it != _objectData.end(); it++) {
        it -> second = nullptr;
    }
}

/**
 * @brief Helper method to delete object contents
 */
void JsonObject::deleteData() {
    for(auto it = values.begin(); it != values.end(); it++) {
        delete it -> second;

        it -> second = nullptr;
    }
}

/**
 * @brief Gets the number of key-value pairs
 * @return Size of the object
 */
size_t JsonObject::getSize() const {
    return values.size();
}

/**
 * @brief Gets all keys in order
 * @return Vector of keys
 */
std::vector<std::string> JsonObject::getKeys() const {
    std::vector<std::string> _keys(values.size());
    size_t index = 0;

    for(const std::string& key : keys){
        _keys[index++] = key;
    }

    return _keys;
}

/**
 * @brief Gets all values in order
 * @return Vector of values
 */
std::vector<const JsonValue*> JsonObject::getValues() const {
    std::vector<const JsonValue*> _values(values.size());
    size_t index = 0;

    for(const std::string& key : keys){
        _values[index++] = values.at(key) -> clone();
    }

    return _values;
}

/**
 * @brief Checks if a key exists
 * @param key Key to check
 * @return True if key exists, false otherwise
 */
bool JsonObject::containsKey(const std::string& key) const {
    return values.find(key) != values.end();
}

/**
 * @brief Adds a key-value pair
 * @param key Key to add
 * @param value Value to add
 * @throws std::runtime_error if key already exists
 */
void JsonObject::addKVP(const std::string& key, const JsonValue* const value) {
    if(containsKey(key)){
        const std::string message = "Key \"" + key + "\" already exists in JsonObject!";
        throw std::runtime_error(message);
    }

    values.emplace(key, value -> clone());
    keys.push_back(key);
}

/**
 * @brief Edits an existing key-value pair
 * @param key Key to edit
 * @param value New value to set
 */
void JsonObject::editKVP(const std::string& key, const JsonValue* const value) {
    delete values.at(key);

    values[key] = value -> clone();
}

/**
 * @brief Removes a key-value pair
 * @param key Key to remove
 * @throws std::runtime_error if key doesn't exist
 */
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

/**
 * @brief Gets the value for a key
 * @param key Key to look up
 * @return Pointer to the value
 * @throws std::runtime_error if key doesn't exist
 */
const JsonValue* JsonObject::getValue(const std::string& key) const {
    if(!containsKey(key)){
        const std::string message = "Key \"" + key + "\" does not exist in JsonObject!";
        throw std::runtime_error(message);
    }

    return values.at(key);
}
