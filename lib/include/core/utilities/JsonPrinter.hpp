#ifndef JSONPRINTER
#define JSONPRINTER

#include "JsonFormatConfig.hpp"

/**
 * @brief Utility class for printing JSON values in different formats
 */
class JsonPrinter {
    public:
        /**
         * @brief Prints a JSON value in compact format
         * @param jsonValue Pointer to the constant JSON value to print
         * @return String representation of the JSON value
         */
        static std::string print(const JsonValue* const jsonValue);

        /**
         * @brief Prints a JSON value in pretty-printed format with indentation
         * @param jsonValue Pointer to the constant JSON value to print
         * @return Formatted string representation of the JSON value
         */
        static std::string prettyPrint(const JsonValue* const jsonValue);
};

#endif