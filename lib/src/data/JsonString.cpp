#include "JsonValueVisitor.hpp"

/**
 * @brief Constructor that initializes the string value
 * @param _value String value to store
 */
JsonString::JsonString(const std::string& _value) : value(_value) {}

/**
 * @brief Gets the type of JSON value
 * @return ValueType::String
 */
ValueType JsonString::getType() const {
    return ValueType::String;
}

/**
 * @brief Creates a deep copy of the string value
 * @return Pointer to the cloned string
 */
JsonValue* JsonString::clone() const {
    return new JsonString(value);
}

/**
 * @brief Prints string value to stream
 * @param stream Output stream to print to
 */
void JsonString::print(std::ostream& stream) const {
    stream << value;
}

/**
 * @brief Accepts a visitor for the Visitor pattern
 * @param visitor Reference to the visitor
 */
void JsonString::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
