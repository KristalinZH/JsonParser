#ifndef JSONFORMATCONFIG
#define JSONFORMATCONFIG

#include "JsonFormatter.hpp"

/**
 * @brief Configuration namespace for JSON formatting options
 */
namespace JsonFormatConfig {
    /**
     * @brief Gets the current JSON formatter instance
     * @return Pointer to the current JsonFormatter
     */
    const JsonFormatter* getFormatter();

    /**
     * @brief Sets the type of formatter to use
     * @param _type The FormatterType to set
     */
    void setFormatterType(const FormatterType& _type);
}

#endif