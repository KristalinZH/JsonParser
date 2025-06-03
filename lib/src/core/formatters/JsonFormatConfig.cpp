#include "JsonFormatConfig.hpp"
#include "CompactJsonFormatter.hpp"
#include "PrettyJsonFormatter.hpp"

namespace {
    static FormatterType type = FormatterType::Pretty;
}

const JsonFormatter* JsonFormatConfig::getFormatter() {
    if(type == FormatterType::Compact){
        return &CompactJsonFormatter::getInstance();
    }

    return &PrettyJsonFormatter::getInstance();
}

void JsonFormatConfig::setFormatterType(const FormatterType& _type) {
    type = _type;
}