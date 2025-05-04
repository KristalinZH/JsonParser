#include "JsonObject.hpp"
#include "JsonArray.hpp"
#include "JsonValue.hpp"

JsonValue::JsonValue() : type(ValueType::Null) {
    value.booleanValue = nullptr;
}

JsonValue::JsonValue(const bool _value) : type(ValueType::Boolean) {
    value.booleanValue = new bool (_value);
}

JsonValue::JsonValue(const int _value) : type(ValueType::Int) {
    value.inumValue = new int (_value);
}

JsonValue::JsonValue(const double _value) : type(ValueType::Double) {
    value.dnumValue = new double (_value);
}

JsonValue::JsonValue(const char* const _value) :type(ValueType::String) {
    value.strValue = new std::string(_value);
}

JsonValue::JsonValue(const std::string& _value) : type(ValueType::String) {
    value.strValue = new std::string (_value);
}

JsonValue::JsonValue(const JsonArray& _value) : type(ValueType::Array) {
    value.jsonArrayValue = new JsonArray (_value);
}

JsonValue::JsonValue(const JsonObject& _value) : type(ValueType::Object) {
    value.jsonObjectValue = new JsonObject (_value);
}

JsonValue::JsonValue(const JsonValue& other){
    type = other.type;
    setValue(other);
}

JsonValue& JsonValue::operator=(const JsonValue& other){
    if(this != &other){
        clearValue();
        type = other.type;
        setValue(other);
    }

    return *this;
}

JsonValue::JsonValue(JsonValue&& other) noexcept {
    value.booleanValue = nullptr;
    type = std::move(other.type);
    std::swap(value.booleanValue, other.value.booleanValue);
}

JsonValue& JsonValue::operator=(JsonValue&& other) noexcept {
    if(this != &other){
        type = std::move(other.type);
        std::swap(value.booleanValue, other.value.booleanValue);
    }

    return *this;
}

JsonValue::~JsonValue(){
    clearValue();
}

ValueType JsonValue::getType() const {
    return type;
}

void JsonValue::setType(const ValueType& _type) {
    clearValue();
    type = _type;
}

bool JsonValue::getBValue() const {
    if(type != ValueType::Boolean)
        throw std::runtime_error("Mismatched value type in getBValue()!");

    if(value.booleanValue == nullptr)
        throw std::runtime_error("No initialized value in getBValue()!");

    return *value.booleanValue;
}

int JsonValue::getIValue() const {
    if(type != ValueType::Int)
        throw std::runtime_error("Mismatched value type in getIValue()!");

    if(value.inumValue == nullptr)
        throw std::runtime_error("No initialized value in getIValue()!");

    return *value.inumValue;
}

double JsonValue::getDValue() const {
    if(type != ValueType::Double)
        throw std::runtime_error("Mismatched value type in getDValue()!");

    if(value.dnumValue == nullptr)
        throw std::runtime_error("No initialized value in getDValue()!");

    return *value.dnumValue;
}

std::string JsonValue::getSValue() const {
    if(type != ValueType::String)
        throw std::runtime_error("Mismatched value type in getSValue()!");

    if(value.strValue == nullptr)
        throw std::runtime_error("No initialized value in getSValue()!");

    return *value.strValue;
}

JsonArray JsonValue::getAValue() const {
    if(type != ValueType::Array)
        throw std::runtime_error("Mismatched value type in getAValue()!");

    if(value.jsonArrayValue == nullptr)
        throw std::runtime_error("No initialized value in getAValue()!");

    return *value.jsonArrayValue;
}

JsonObject JsonValue::getOValue() const {
    if(type != ValueType::Object)
        throw std::runtime_error("Mismatched value type in getOValue()!");

    if(value.jsonObjectValue == nullptr)
        throw std::runtime_error("No initialized value in getOValue()!");

    return *value.jsonObjectValue;
}

void JsonValue::setBValue(const bool _value){
    if(type != ValueType::Boolean)
        throw std::runtime_error("Mismatched value type in setBValue()!");

    if(value.booleanValue == nullptr){
        value.booleanValue = new bool (_value);
        return;
    }
    
    *value.booleanValue = _value;
}

void JsonValue::setIValue(const int _value){
    if(type != ValueType::Int)
        throw std::runtime_error("Mismatched value type in setIValue()!");

    if(value.inumValue == nullptr){
        value.inumValue = new int (_value);
        return;
    }

    *value.inumValue = _value;
}

void JsonValue::setDValue(const double _value){
    if(type != ValueType::Double)
        throw std::runtime_error("Mismatched value type in setDValue()!");
    
    if(value.dnumValue == nullptr){
        value.dnumValue = new double (_value);
        return;
    }
        
    *value.dnumValue = _value;
}

void JsonValue::setSValue(const std::string& _value){
    if(type != ValueType::String)
        throw std::runtime_error("Mismatched value type in setSValue()!");

    if(value.strValue == nullptr){
        value.strValue = new std::string (_value);
        return;
    }

    *value.strValue = _value;
}

void JsonValue::setAValue(const JsonArray& _value){
    if(type != ValueType::Array)
        throw std::runtime_error("Mismatched value type in setAValue()!");

    if(value.jsonArrayValue == nullptr){
        value.jsonArrayValue = new JsonArray (_value);
        return;
    }

    *value.jsonArrayValue = _value;
}

void JsonValue::setOValue(const JsonObject& _value){
    if(type != ValueType::Object)
        throw std::runtime_error("Mismatched value type in setOValue()!");

    if(value.jsonObjectValue == nullptr){
        value.jsonObjectValue = new JsonObject (_value);
        return;
    }    

    *value.jsonObjectValue = _value;
}

std::ostream& operator<<(std::ostream& os, const JsonValue& jsonValue){
    switch(jsonValue.type) {

        case ValueType::Null : {
            os << "null";
            break;
        }

        case ValueType::Boolean : {
            os << (*jsonValue.value.booleanValue ? "true" : "false");
            break;
        }

        case ValueType::Int : {
            os << *jsonValue.value.inumValue;
            break;
        }

        case ValueType::Double : {
            os << *jsonValue.value.dnumValue;
            break;
        }

        case ValueType::String : {
            os << "\"" << *jsonValue.value.strValue << "\"";
            break;
        }

        case ValueType::Array : {
            os << *jsonValue.value.jsonArrayValue;
            break;
        }

        case ValueType::Object : {
            os << *jsonValue.value.jsonObjectValue;
            break;
        }

        default: {
            throw std::runtime_error("Invalid value type!");
        }

    }

    return os;
}

void JsonValue::clearValue(){
    switch(type) {

        case ValueType::Null : {
            value.booleanValue = nullptr;
            break;
        }

        case ValueType::Boolean : {
            delete value.booleanValue;
            value.booleanValue = nullptr;
            break;
        }

        case ValueType::Int : {
            delete value.inumValue;
            value.inumValue = nullptr;
            break;
        }

        case ValueType::Double : {
            delete value.dnumValue;
            value.dnumValue = nullptr;
            break;
        }

        case ValueType::String : {
            delete value.strValue;
            value.strValue = nullptr;
            break;
        }

        case ValueType::Array : {
            delete value.jsonArrayValue;
            value.jsonArrayValue = nullptr;
            break;
        }

        case ValueType::Object : {
            delete value.jsonObjectValue;
            value.jsonObjectValue = nullptr;
            break;
        }

        default: {
            throw std::runtime_error("Invalid value type in clearValue()!");
        }

    }
}

void JsonValue::setValue(const JsonValue& other){
    switch(other.type) {

        case ValueType::Null : {
            value.booleanValue = nullptr;
            break;
        }

        case ValueType::Boolean : {
            value.booleanValue = new bool (*other.value.booleanValue);
            break;
        }

        case ValueType::Int : {
            value.inumValue = new int (*other.value.inumValue);
            break;
        }

        case ValueType::Double : {
            value.dnumValue = new double (*other.value.dnumValue);
            break;
        }

        case ValueType::String : {
            value.strValue = new std::string (*other.value.strValue);
            break;
        }

        case ValueType::Array : {
            value.jsonArrayValue = new JsonArray (*other.value.jsonArrayValue);
            break;
        }

        case ValueType::Object : {
            value.jsonObjectValue = new JsonObject (*other.value.jsonObjectValue);
            break;
        }

        default: {
            throw std::runtime_error("Invalid value type in setValue()!");
        }

    }
}
