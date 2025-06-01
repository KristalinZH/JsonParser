#include <sstream>
#include "JsonPrinter.hpp"

std::string JsonPrinter::print(const JsonValue* const jsonValue){

    JsonFormatConfig::setFormatterType(FormatterType::Compact);

    std::ostringstream os;

    os << jsonValue;


    return os.str();
}

std::string prettyPrint(const JsonValue* const jsonValue) {

    JsonFormatConfig::setFormatterType(FormatterType::Pretty);

    std::ostringstream os;

    os << jsonValue;

    return os.str();
}