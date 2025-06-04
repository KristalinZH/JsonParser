#include "JsonValueVisitor.hpp"
#include "JsonFormatConfig.hpp"

/**
 * @brief Gets the type of JSON value
 * @return ValueType::Array
 */
ValueType JsonArray::getType() const {
    return ValueType::Array;
}

/**
 * @brief Creates a deep copy of the array
 * @return Pointer to the cloned array
 */
JsonValue* JsonArray::clone() const {
    return new JsonArray(*this);
}

/**
 * @brief Prints array content to stream
 * @param stream Output stream to print to
 */
void JsonArray::print(std::ostream& stream) const {
    stream << JsonFormatConfig::getFormatter() -> format(this);
}

/**
 * @brief Accepts a visitor for the Visitor pattern
 * @param visitor Reference to the visitor
 */
void JsonArray::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}

/**
 * @brief Constructor that initializes array with vector of values
 * @param _arrayData Vector of JSON values to copy
 */
JsonArray::JsonArray(const std::vector<JsonValue*>& _arrayData) : values(std::vector<JsonValue*>(_arrayData.size(), nullptr)) {
    copyData(_arrayData);
}

/**
 * @brief Copy constructor
 * @param other Array to copy from
 */
JsonArray::JsonArray(const JsonArray& other) : values(std::vector<JsonValue*>(other.values.size(), nullptr)) {
    copyData(other.values);
}

/**
 * @brief Copy assignment operator
 * @param other Array to copy from
 * @return Reference to this array
 */
JsonArray& JsonArray::operator=(const JsonArray& other) {
    if(this != &other) {
        deleteData();
        values.resize(other.values.size(), nullptr);
        copyData(other.values);
    }

    return *this;
}

/**
 * @brief Move constructor
 * @param other Array to move from
 */
JsonArray::JsonArray(JsonArray&& other) noexcept {
    values = other.values;
    resetData(other.values);
}

/**
 * @brief Move assignment operator
 * @param other Array to move from
 * @return Reference to this array
 */
JsonArray& JsonArray::operator=(JsonArray&& other) noexcept {
    if(this != &other){
        deleteData();
        values = other.values;
        resetData(other.values);
    }

    return *this;
}

/**
 * @brief Destructor that cleans up array contents
 */
JsonArray::~JsonArray() {
    deleteData();
}

/**
 * @brief Helper method to deep copy array data
 * @param _arrayData Vector of values to copy
 */
void JsonArray::copyData(const std::vector<JsonValue*>& _arrayData) {
    size_t size = _arrayData.size();


    for(size_t i = 0; i < size; i++){
        values[i] = _arrayData[i] -> clone();
    }
}

/**
 * @brief Helper method to reset array data
 * @param _arrayData Vector of values to reset
 */
void JsonArray::resetData(std::vector<JsonValue*>& _arrayData) {
    size_t size = _arrayData.size();

    for(size_t i = 0; i < size; i++){
        _arrayData[i] = nullptr;
    }
}

/**
 * @brief Helper method to delete array contents
 */
void JsonArray::deleteData() {
    size_t size = values.size();

    for(size_t i = 0; i < size; i++){
        delete values[i];
        values[i] = nullptr;
    }
}

/**
 * @brief Gets the size of the array
 * @return Number of elements in array
 */
size_t JsonArray::getSize() const {
    return values.size();
}

/**
 * @brief Array access operator
 * @param index Index of element to access
 * @return Pointer to the JSON value at index
 * @throws std::out_of_range if index is invalid
 */
JsonValue* JsonArray::operator[](const size_t index) {
    if(index >= values.size())
        throw std::out_of_range("Index out of range in JsonArray");

    return values[index];
}

/**
 * @brief Const array access operator
 * @param index Index of element to access
 * @return Const pointer to the JSON value at index
 * @throws std::out_of_range if index is invalid
 */
const JsonValue* JsonArray::operator[](const size_t index) const {
    if(index >= values.size())
        throw std::out_of_range("Index out of range in JsonArray");

    return values[index];
}

/**
 * @brief Adds a value to the array
 * @param value Pointer to the JSON value to add
 */
void JsonArray::addValue(const JsonValue* const value) {
    values.push_back(value -> clone());
}