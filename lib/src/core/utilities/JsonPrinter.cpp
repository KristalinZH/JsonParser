#include <sstream>
#include "JsonPrinter.hpp"

/**
 * @brief Prints a JSON value in compact format
 * @param jsonValue Pointer to the constant JSON value to print
 * @return String representation of the JSON value
 */
std::string JsonPrinter::print(const JsonValue* const jsonValue){

    JsonFormatConfig::setFormatterType(FormatterType::Compact);

    std::ostringstream os;

    os << jsonValue;

    JsonFormatConfig::setFormatterType(FormatterType::Pretty);

    return os.str();
}

/**
 * @brief Prints a JSON value in pretty-printed format
 * @param jsonValue Pointer to the constant JSON value to print
 * @return Formatted string representation of the JSON value
 */
std::string JsonPrinter::prettyPrint(const JsonValue* const jsonValue) {

    JsonFormatConfig::setFormatterType(FormatterType::Pretty);

    std::ostringstream os;

    os << jsonValue;

    return os.str();
}