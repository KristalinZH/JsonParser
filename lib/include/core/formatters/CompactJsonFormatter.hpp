#ifndef COMPACTJSONFORMATTER
#define COMPACTJSONFORMATTER

#include "JsonFormatter.hpp"

/**
 * @brief Formatter class that outputs JSON in a compact format without whitespace
 * @inherit JsonFormatter
 */
class CompactJsonFormatter : public JsonFormatter {
    public:
        /**
         * @brief Gets the singleton instance of CompactJsonFormatter
         * @return Reference to the CompactJsonFormatter instance
         */
        static CompactJsonFormatter& getInstance();

        /**
         * @brief Formats a JsonArray into a compact string representation
         * @param value Pointer to the JsonArray to format
         * @param indent Indentation level (unused in compact format)
         * @return Formatted string representation of the JsonArray
         */
        std::string format(const JsonArray* value, const size_t indent = 0) const override;

        /**
         * @brief Formats a JsonObject into a compact string representation
         * @param value Pointer to the JsonObject to format
         * @param indent Indentation level (unused in compact format)
         * @return Formatted string representation of the JsonObject
         */
        std::string format(const JsonObject* value, const size_t indent = 0) const override;
    private:
        /**
         * @brief Writes JSON value to output stream in compact format
         * @param os Output stream to write to
         * @param value Pointer to the JsonValue to write
         * @param indent Indentation level (unused in compact format)
         */
        void writeJsonIntoStream(std::ostream& os, const JsonValue* value, const size_t indent = 0) const override;

        /**
         * @brief Default constructor (private for singleton pattern)
         */
        CompactJsonFormatter() = default;

        /**
         * @brief Deleted copy constructor
         */
        CompactJsonFormatter(const CompactJsonFormatter&) = delete;

        /**
         * @brief Deleted assignment operator
         */
        CompactJsonFormatter& operator=(const CompactJsonFormatter&) = delete;
};

#endif