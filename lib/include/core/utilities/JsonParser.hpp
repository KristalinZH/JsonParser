#ifndef JSONPARSER
#define JSONPARSER

#include "JsonObject.hpp"

/**
 * @brief Parser class for converting JSON text into JsonValue objects
 */
class JsonParser {
    public:
        /**
         * @brief Parses JSON content from an input stream
         * @param stream Input stream containing JSON data
         * @return Pointer to the parsed JsonValue
         */
        static JsonValue* parse(std::istream& stream);
    private:
        /**
         * @brief Parses a JSON null value
         * @param stream Input stream to parse from
         * @return String representation of null value
         */
        static std::string parseNull(std::istream& stream);

        /**
         * @brief Parses a JSON boolean value
         * @param stream Input stream to parse from
         * @param lastSymbol Last character read from stream
         * @return String representation of boolean value
         */
        static std::string parseBoolean(std::istream& stream, const char lastSymbol);

        /**
         * @brief Parses a JSON number value
         * @param stream Input stream to parse from
         * @param lastSymbol Last character read from stream
         * @return String representation of number value
         */
        static std::string parseNumber(std::istream& stream, const char lastSymbol);

        /**
         * @brief Parses a JSON string value
         * @param stream Input stream to parse from
         * @param lastSymbol Last character read from stream
         * @return Parsed string value
         */
        static std::string parseString(std::istream& stream, const char lastSymbol);

        /**
         * @brief Parses a primary JSON value (null, boolean, number, or string)
         * @param stream Input stream to parse from
         * @param lastSymbol Last character read from stream
         * @return Pointer to the parsed JsonValue
         */
        static JsonValue* parsePrimary(std::istream& stream, const char lastSymbol);

        /**
         * @brief Parses a JSON object or array
         * @param stream Input stream to parse from
         * @param lastBrace Opening brace/bracket character
         * @return Pointer to the parsed JsonValue
         */
        static JsonValue* parseJson(std::istream& stream, const char lastBrace);
};

#endif