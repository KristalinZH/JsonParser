#include "JsonValueVisitor.hpp"

JsonNumber::JsonNumber(const std::string& _value) : value(_value) {}

ValueType JsonNumber::getType() const {
    return ValueType::Number;
}

JsonValue* JsonNumber::clone() const {
    return new JsonNumber(value);
}

void JsonNumber::print(std::ostream& stream) const {
    stream << value;
}

void JsonNumber::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
