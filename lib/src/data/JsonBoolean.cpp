#include "JsonValueVisitor.hpp"

/**
 * @brief Constructor that initializes the boolean value
 * @param _value The boolean value to store
 */
JsonBoolean::JsonBoolean(const bool _value) : value(_value) {}

/**
 * @brief Gets the type of JSON value
 * @return ValueType::Boolean
 */
ValueType JsonBoolean::getType() const {
    return ValueType::Boolean;
}

/**
 * @brief Creates a deep copy of the boolean value
 * @return Pointer to the cloned boolean
 */
JsonValue* JsonBoolean::clone() const {
    return new JsonBoolean(value);
}

/**
 * @brief Prints boolean value to stream
 * @param stream Output stream to print to
 */
void JsonBoolean::print(std::ostream& stream) const {
    stream << (value ? "true" : "false");
}

/**
 * @brief Accepts a visitor for the Visitor pattern
 * @param visitor Reference to the visitor
 */
void JsonBoolean::accept(JsonValueVisitor& visitor) {
    visitor.visit(*this);
}
