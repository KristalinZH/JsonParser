#include "JsonArray.hpp"
#include "formatters/JsonFormatConfig.hpp"

JsonArray::JsonArray() = default;

JsonArray::JsonArray(const std::vector<JsonValue>& _arrayData) : arrayData(_arrayData) {}

JsonArray::JsonArray(const JsonArray& other) : arrayData(other.arrayData) {}

JsonArray& JsonArray::operator=(const JsonArray& other){
    if(this != &other){
        arrayData = other.arrayData;
    }

    return *this;
}

JsonArray::JsonArray(JsonArray&& other) noexcept : arrayData(std::move(other.arrayData)) {}

JsonArray& JsonArray::operator=(JsonArray&& other) noexcept {
    if(this != &other){
        arrayData = std::move(other.arrayData);
    }

    return *this;
}

JsonArray::~JsonArray() = default;

size_t JsonArray::getSize() const {
    return arrayData.size();
}

JsonValue& JsonArray::operator[](const size_t index) {
    if(index >= arrayData.size())
        throw std::out_of_range("Index out of range in JsonArray");

    return arrayData[index];
}

const JsonValue& JsonArray::operator[](const size_t index) const {
    if(index >= arrayData.size())
        throw std::out_of_range("Index out of range in JsonArray");

    return arrayData[index];
}

void JsonArray::addValue(const JsonValue& value){
    arrayData.push_back(value);
}

std::ostream& operator<<(std::ostream& os, const JsonArray& jsonArray){

    const std::shared_ptr<JsonFormatter> formatter = JsonFormatConfig::getFormatter();

    os << formatter -> format(jsonArray);

    return os;
}