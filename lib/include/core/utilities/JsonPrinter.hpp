#ifndef JSONPRINTER
#define JSONPRINTER

#include "JsonFormatConfig.hpp"

class JsonPrinter{
    public:
        std::string print(const JsonValue* const jsonValue);
        std::string prettyPrint(const JsonValue* const jsonValue);
};

#endif