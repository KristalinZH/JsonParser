#include "formatters/JsonFormatConfig.hpp"
#include "formatters/CompactJsonFormatter.hpp"

namespace {
    std::shared_ptr<JsonFormatter> currentFormatter = std::make_shared<CompactJsonFormatter>();
}

void JsonFormatConfig::setFormatter(std::shared_ptr<JsonFormatter> formatter) {
    currentFormatter = formatter;
}

std::shared_ptr<JsonFormatter> JsonFormatConfig::getFormatter() {
    return currentFormatter;
}