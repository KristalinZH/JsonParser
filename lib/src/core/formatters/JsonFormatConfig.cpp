#include "JsonFormatConfig.hpp"
#include "CompactJsonFormatter.hpp"
#include "PrettyJsonFormatter.hpp"

/**
 * @brief Anonymous namespace for internal configuration state
 */
namespace {
    static FormatterType type = FormatterType::Pretty;  ///< Current formatter type
}

/**
 * @brief Gets the current JSON formatter instance
 * @return Pointer to the current JsonFormatter
 */
const JsonFormatter* JsonFormatConfig::getFormatter() {
    if(type == FormatterType::Compact){
        return &CompactJsonFormatter::getInstance();
    }

    return &PrettyJsonFormatter::getInstance();
}

/**
 * @brief Sets the type of formatter to use
 * @param _type The FormatterType to set
 */
void JsonFormatConfig::setFormatterType(const FormatterType& _type) {
    type = _type;
}