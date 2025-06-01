#include "JsonValueVisitor.hpp"
#include "JsonFormatConfig.hpp"

ValueType JsonArray::getType() const {
    return ValueType::Array;
}

JsonValue* JsonArray::clone() const {
    return new JsonArray(*this);
}

void JsonArray::print(std::ostream& stream) const {
    stream << JsonFormatConfig::getFormatter() -> format(this);
}

void JsonArray::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}

JsonArray::JsonArray(const std::vector<JsonValue*>& _arrayData) : values(std::vector<JsonValue*>(_arrayData.size(), nullptr)) {
    copyData(_arrayData);
}

JsonArray::JsonArray(const JsonArray& other) : values(std::vector<JsonValue*>(other.values.size(), nullptr)) {
    copyData(other.values);
}

JsonArray& JsonArray::operator=(const JsonArray& other) {
    if(this != &other) {
        deleteData();
        values.resize(other.values.size(), nullptr);
        copyData(other.values);
    }

    return *this;
}

JsonArray::JsonArray(JsonArray&& other) noexcept {
    values = other.values;
    resetData(other.values);
}

JsonArray& JsonArray::operator=(JsonArray&& other) noexcept {
    if(this != &other){
        deleteData();
        values = other.values;
        resetData(other.values);
    }

    return *this;
}

JsonArray::~JsonArray() {
    deleteData();
}

void JsonArray::copyData(const std::vector<JsonValue*>& _arrayData) {
    size_t size = _arrayData.size();


    for(size_t i = 0; i < size; i++){
        values[i] = _arrayData[i] -> clone();
    }
}

void JsonArray::resetData(std::vector<JsonValue*>& _arrayData) {
    size_t size = _arrayData.size();

    for(size_t i = 0; i < size; i++){
        _arrayData[i] = nullptr;
    }
}

void JsonArray::deleteData() {
    size_t size = values.size();

    for(size_t i = 0; i < size; i++){
        delete values[i];
        values[i] = nullptr;
    }
}

size_t JsonArray::getSize() const {
    return values.size();
}

JsonValue* JsonArray::operator[](const size_t index) {
    if(index >= values.size())
        throw std::out_of_range("Index out of range in JsonArray");

    return values[index];
}
const JsonValue* JsonArray::operator[](const size_t index) const {
    if(index >= values.size())
        throw std::out_of_range("Index out of range in JsonArray");

    return values[index];
}

void JsonArray::addValue(const JsonValue* const value) {
    values.push_back(value -> clone());
}