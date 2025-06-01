#include "JsonValueVisitor.hpp"

ValueType JsonNull::getType() const {
    return ValueType::Null;
}

JsonValue* JsonNull::clone() const {
    return new JsonNull();
}

void JsonNull::print(std::ostream& stream) const {
    stream << "null";
}

void JsonNull::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
