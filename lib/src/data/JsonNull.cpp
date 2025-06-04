#include "JsonValueVisitor.hpp"

/**
 * @brief Gets the type of JSON value
 * @return ValueType::Null
 */
ValueType JsonNull::getType() const {
    return ValueType::Null;
}

/**
 * @brief Creates a deep copy of the null value
 * @return Pointer to the cloned null value
 */
JsonValue* JsonNull::clone() const {
    return new JsonNull();
}

/**
 * @brief Prints null value to stream
 * @param stream Output stream to print to
 */
void JsonNull::print(std::ostream& stream) const {
    stream << "null";
}

/**
 * @brief Accepts a visitor for the Visitor pattern
 * @param visitor Reference to the visitor
 */
void JsonNull::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
