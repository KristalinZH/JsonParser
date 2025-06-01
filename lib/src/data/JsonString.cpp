#include "JsonValueVisitor.hpp"

JsonString::JsonString(const std::string& _value) : value(_value) {}

ValueType JsonString::getType() const {
    return ValueType::String;
}

JsonValue* JsonString::clone() const {
    return new JsonString(value);
}

void JsonString::print(std::ostream& stream) const {
    stream << value;
}

void JsonString::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
