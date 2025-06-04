#include "JsonValueVisitor.hpp"

/**
 * @brief Constructor that initializes the number value
 * @param _value String representation of the number
 */
JsonNumber::JsonNumber(const std::string& _value) : value(_value) {}

/**
 * @brief Gets the type of JSON value
 * @return ValueType::Number
 */
ValueType JsonNumber::getType() const {
    return ValueType::Number;
}

/**
 * @brief Creates a deep copy of the number value
 * @return Pointer to the cloned number
 */
JsonValue* JsonNumber::clone() const {
    return new JsonNumber(value);
}

/**
 * @brief Prints number value to stream
 * @param stream Output stream to print to
 */
void JsonNumber::print(std::ostream& stream) const {
    stream << value;
}

/**
 * @brief Accepts a visitor for the Visitor pattern
 * @param visitor Reference to the visitor
 */
void JsonNumber::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
