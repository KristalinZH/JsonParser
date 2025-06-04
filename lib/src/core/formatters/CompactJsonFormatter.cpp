#include <sstream>
#include "CompactJsonFormatter.hpp"

/**
 * @brief Gets the singleton instance of CompactJsonFormatter
 * @return Reference to the CompactJsonFormatter instance
 */
CompactJsonFormatter& CompactJsonFormatter::getInstance() {
    static CompactJsonFormatter instance;
    return instance;
}

/**
 * @brief Formats a JsonArray into a compact string representation
 * @param value Pointer to the JsonArray to format
 * @param indent Indentation level (unused in compact format)
 * @return Formatted string representation of the array
 */
std::string CompactJsonFormatter::format(const JsonArray* value, const size_t indent) const {
    const size_t size = value -> getSize();

    if(size == 0)
        return std::string("[]");

    std::ostringstream output;

    output << '[';

    for(size_t i = 0; i < size - 1; i++){
        writeJsonIntoStream(output, (*value)[i]);
        output << ',';
    }

    writeJsonIntoStream(output, (*value)[size - 1]);

    output << ']';

    return output.str();
}

/**
 * @brief Formats a JsonObject into a compact string representation
 * @param value Pointer to the JsonObject to format
 * @param indent Indentation level (unused in compact format)
 * @return Formatted string representation of the object
 */
std::string CompactJsonFormatter::format(const JsonObject* value, const size_t indent) const {
    const size_t size = value -> getSize();

    if(size == 0)
        return std::string("{}");

    std::ostringstream output;

    output << '{';

    std::vector<std::string> keys = value -> getKeys();

    for(size_t i = 0; i < size - 1; i++){
        output << '\"' << keys[i] << '\"' << ':';
        writeJsonIntoStream(output, value -> getValue(keys[i]));
        output << ',';
    }

    output << '\"' << keys[size - 1] << '\"' << ':';
    writeJsonIntoStream(output, value -> getValue(keys[size - 1]));
    output << '}';

    return output.str();
}

/**
 * @brief Writes JSON value to output stream in compact format
 * @param os Output stream to write to
 * @param value Pointer to the JsonValue to write
 * @param indent Indentation level (unused in compact format)
 * @throws std::runtime_error if value type is invalid
 */
void CompactJsonFormatter::writeJsonIntoStream(std::ostream& os, const JsonValue* value, const size_t indent) const {

    switch(value -> getType()) {

        case ValueType::Null :
        case ValueType::Boolean :
        case ValueType::Number : 
        case ValueType::String : {
            os << value;
            break;
        }

        case ValueType::Array : {
            os << format(static_cast<const JsonArray*>(value));
            break;
        }

        case ValueType::Object : {
            os << format(static_cast<const JsonObject*>(value));
            break;
        }

        default: {
            throw std::runtime_error("Invalid value type in CompactJsonFormatter!");
        }

    }
}