#ifndef JSONFORMATCONFIG
#define JSONFORMATCONFIG

#include "JsonFormatter.hpp"

namespace JsonFormatConfig {
    const JsonFormatter* getFormatter();
    void setFormatterType(const FormatterType& _type);
}

#endif