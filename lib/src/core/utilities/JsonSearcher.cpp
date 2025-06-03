#include "JsonSearcher.hpp"

void JsonSearcher::visit(JsonNull& jsonValue) {
    return;
}

void JsonSearcher::visit(JsonBoolean& jsonValue) {
    return;
}

void JsonSearcher::visit(JsonNumber& jsonValue) {
    return;
}

void JsonSearcher::visit(JsonString& jsonValue) {
    return;
}

void JsonSearcher::visit(JsonArray& jsonValue) {
    const size_t size = jsonValue.getSize();

    for(size_t i = 0; i < size; i++) {

        const JsonValue* value = jsonValue[i];

        if(value -> getType() == ValueType::Object) {
            JsonValue* objValue = value -> clone();
            objValue -> accept(*this);
            delete objValue;
        }

    }

}

void JsonSearcher::visit(JsonObject& jsonValue) {
    std::vector<std::string> keys = jsonValue.getKeys();
    const size_t size = jsonValue.getSize();

    for(size_t i = 0; i < size; i++) {

        const JsonValue* value = jsonValue.getValue(keys[i]);

        if(std::regex_match(keys[i], regex)){
            searchResults.push_back(value -> clone());
        }

        if(value -> getType() == ValueType::Object) {
            JsonValue* pcopy = const_cast<JsonValue*>(value);
            pcopy -> accept(*this);
        }
    }
}

std::vector<JsonValue*>JsonSearcher::getResults() const {
    return searchResults;
}

JsonSearcher::JsonSearcher(const std::string& searchRegex) : regex(std::regex(searchRegex)) {}

JsonSearcher::~JsonSearcher() {
    for(JsonValue* value : searchResults) {
        delete value;
    }
}