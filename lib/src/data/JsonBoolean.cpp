#include "JsonValueVisitor.hpp"

JsonBoolean::JsonBoolean(const bool _value) : value(_value) {}

ValueType JsonBoolean::getType() const {
    return ValueType::Boolean;
}

JsonValue* JsonBoolean::clone() const {
    return new JsonBoolean(value);
}

void JsonBoolean::print(std::ostream& stream) const {
    stream << (value ? "true" : "false");
}

void JsonBoolean::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
