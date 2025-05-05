#ifndef JSONFORMATCONFIG
#define JSONFORMATCONFIG

#include <memory>
#include "JsonFormatter.hpp"

namespace JsonFormatConfig {
    void setFormatter(std::shared_ptr<JsonFormatter> formatter);
    std::shared_ptr<JsonFormatter> getFormatter();
}

#endif