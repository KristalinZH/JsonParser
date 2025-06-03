#ifndef JSONPARSER
#define JSONPARSER

#include "JsonObject.hpp"

class JsonParser {
    public:
        static JsonValue* parse(std::istream& stream);
    private:
        static std::string parseNull(std::istream& stream);
        static std::string parseBoolean(std::istream& stream, const char lastSymbol);
        static std::string parseNumber(std::istream& stream, const char lastSymbol);
        static std::string parseString(std::istream& stream, const char lastSymbol);
        static JsonValue* parsePrimary(std::istream& stream, const char lastSymbol);
        static JsonValue* parseJson(std::istream& stream, const char lastBrace);
};

#endif