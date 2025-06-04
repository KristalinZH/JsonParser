#include "JsonSearcher.hpp"

/**
 * @brief Visit method for JsonNull values
 * @param jsonValue Reference to JsonNull value
 */
void JsonSearcher::visit(JsonNull& jsonValue) {
    return;
}

/**
 * @brief Visit method for JsonBoolean values
 * @param jsonValue Reference to JsonBoolean value
 */
void JsonSearcher::visit(JsonBoolean& jsonValue) {
    return;
}

/**
 * @brief Visit method for JsonNumber values
 * @param jsonValue Reference to JsonNumber value
 */
void JsonSearcher::visit(JsonNumber& jsonValue) {
    return;
}

/**
 * @brief Visit method for JsonString values
 * @param jsonValue Reference to JsonString value
 */
void JsonSearcher::visit(JsonString& jsonValue) {
    return;
}

/**
 * @brief Visit method for JsonArray values, recursively searches nested arrays and objects
 * @param jsonValue Reference to JsonArray value
 */
void JsonSearcher::visit(JsonArray& jsonValue) {
    const size_t size = jsonValue.getSize();

    for(size_t i = 0; i < size; i++) {

        const JsonValue* value = jsonValue[i];

        if(value -> getType() == ValueType::Object || value -> getType() == ValueType::Array) {
            JsonValue* objValue = value -> clone();
            objValue -> accept(*this);
            delete objValue;
        }

    }

}

/**
 * @brief Visit method for JsonObject values, searches keys and recursively searches nested objects
 * @param jsonValue Reference to JsonObject value
 */
void JsonSearcher::visit(JsonObject& jsonValue) {
    std::vector<std::string> keys = jsonValue.getKeys();
    const size_t size = jsonValue.getSize();

    for(size_t i = 0; i < size; i++) {

        const JsonValue* value = jsonValue.getValue(keys[i]);

        if(std::regex_match(keys[i], regex)){
            searchResults.push_back(value -> clone());
        }

        if(value -> getType() == ValueType::Object || value -> getType() == ValueType::Array) {
            JsonValue* pcopy = const_cast<JsonValue*>(value);
            pcopy -> accept(*this);
        }
    }
}

/**
 * @brief Gets the collection of search results
 * @return Vector of pointers to matching JSON values
 */
std::vector<JsonValue*>JsonSearcher::getResults() const {
    return searchResults;
}

/**
 * @brief Constructor that initializes the search regex pattern
 * @param searchRegex Regular expression pattern to search for
 */
JsonSearcher::JsonSearcher(const std::string& searchRegex) : regex(std::regex(searchRegex)) {}

/**
 * @brief Destructor that cleans up search results
 */
JsonSearcher::~JsonSearcher() {
    for(JsonValue* value : searchResults) {
        delete value;
    }
}