#include <sstream>
#include "PrettyJsonFormatter.hpp"

/**
 * @brief Gets the singleton instance of PrettyJsonFormatter
 * @return Reference to the PrettyJsonFormatter instance
 */
PrettyJsonFormatter& PrettyJsonFormatter::getInstance() {
    static PrettyJsonFormatter instance;
    return instance;
}

/**
 * @brief Formats a JsonArray into a pretty-printed string
 * @param value Pointer to the JsonArray to format
 * @param indent Current indentation level
 * @return Formatted string representation of the array
 */
std::string PrettyJsonFormatter::format(const JsonArray* value, const size_t indent) const {
    const size_t size = value -> getSize();

    if(size == 0)
        return std::string("[]");

    std::ostringstream output;

    output << "[\n";

    for(size_t i = 0; i < size - 1; i++){
        writeIndentationIntoStream(output, indent + 1);
        writeJsonIntoStream(output, (*value)[i], indent + 1);
        output << ",\n";
    }

    writeIndentationIntoStream(output, indent + 1);
    writeJsonIntoStream(output, (*value)[size - 1], indent + 1);
    output << '\n';

    writeIndentationIntoStream(output, indent);
    output << "]";
    if(indent == 0)
        output << '\n';

    return output.str();
}

/**
 * @brief Formats a JsonObject into a pretty-printed string
 * @param value Pointer to the JsonObject to format
 * @param indent Current indentation level
 * @return Formatted string representation of the object
 */
std::string PrettyJsonFormatter::format(const JsonObject* value, const size_t indent) const {
    const size_t size = value -> getSize();

    if(size == 0)
        return std::string("{}");

    std::ostringstream output;

    output << "{\n";

    std::vector<std::string> keys = value -> getKeys();

    for(size_t i = 0; i < size - 1; i++){
        writeIndentationIntoStream(output, indent + 1);
        output << '\"' << keys[i] << '\"' <<  " : ";
        writeJsonIntoStream(output, value -> getValue(keys[i]), indent + 1);
        output << ",\n";
    }

    writeIndentationIntoStream(output, indent + 1);
    output << '\"' << keys[size - 1] << '\"' << " : ";
    writeJsonIntoStream(output, value -> getValue(keys[size - 1]), indent + 1);
    output << "\n";

    writeIndentationIntoStream(output, indent);
    output << "}";

    if(indent == 0)
        output << '\n';

    return output.str();
}

/**
 * @brief Writes JSON value to output stream with proper formatting
 * @param os Output stream to write to
 * @param value Pointer to the JsonValue to write
 * @param indent Current indentation level
 * @throws std::runtime_error if value type is invalid
 */
void PrettyJsonFormatter::writeJsonIntoStream(std::ostream& os, const JsonValue* value, const size_t indent) const {

    switch(value -> getType()) {

        case ValueType::Null :
        case ValueType::Boolean :
        case ValueType::Number :
        case ValueType::String : {
            os << value;
            break;
        }

        case ValueType::Array : {
            os << format(static_cast<const JsonArray*>(value), indent);
            break;
        }

        case ValueType::Object : {
            os << format(static_cast<const JsonObject*>(value), indent);
            break;
        }

        default: {
            throw std::runtime_error("Invalid value type in CompactJsonFormatter!");
        }

    }
}

/**
 * @brief Writes indentation spaces to the output stream
 * @param os Output stream to write to
 * @param indent Number of indentation levels
 */
void PrettyJsonFormatter::writeIndentationIntoStream(std::ostream& os, const size_t indent) const {
    for(size_t i = 0; i < indent * 2; i++){
        os << ' ';
    }
}