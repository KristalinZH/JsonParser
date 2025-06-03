#ifndef JSONPRINTER
#define JSONPRINTER

#include "JsonFormatConfig.hpp"

class JsonPrinter {
    public:
        static std::string print(const JsonValue* const jsonValue);
        static std::string prettyPrint(const JsonValue* const jsonValue);
};

#endif