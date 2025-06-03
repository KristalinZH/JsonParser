#include <sstream>
#include "JsonPrinter.hpp"

std::string JsonPrinter::print(const JsonValue* const jsonValue){

    JsonFormatConfig::setFormatterType(FormatterType::Compact);

    std::ostringstream os;

    os << jsonValue;

    JsonFormatConfig::setFormatterType(FormatterType::Pretty);

    return os.str();
}

std::string JsonPrinter::prettyPrint(const JsonValue* const jsonValue) {

    JsonFormatConfig::setFormatterType(FormatterType::Pretty);

    std::ostringstream os;

    os << jsonValue;

    return os.str();
}