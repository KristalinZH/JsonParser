#ifndef PRETTYJSONFORMATTER
#define PRETTYJSONFORMATTER

#include "JsonFormatter.hpp"

/**
 * @brief Formatter class that outputs JSON in a human-readable format with proper indentation
 * @inherit JsonFormatter
 */
class PrettyJsonFormatter : public JsonFormatter {
    public:
        /**
         * @brief Gets the singleton instance of PrettyJsonFormatter
         * @return Reference to the PrettyJsonFormatter instance
         */
        static PrettyJsonFormatter& getInstance();

        /**
         * @brief Formats a JsonArray into a pretty-printed string
         * @param value Pointer to the JsonArray to format
         * @param indent Current indentation level
         * @return Formatted string representation of the JsonArray
         */
        std::string format(const JsonArray* value, const size_t indent = 0) const override;

        /**
         * @brief Formats a JsonObject into a pretty-printed string
         * @param value Pointer to the JsonObject to format
         * @param indent Current indentation level
         * @return Formatted string representation of the JsonObject
         */
        std::string format(const JsonObject* value, const size_t indent = 0) const override;
    private:
        /**
         * @brief Writes JSON value to output stream with proper formatting
         * @param os Output stream to write to
         * @param value Pointer to the JsonValue to write
         * @param indent Current indentation level
         */
        void writeJsonIntoStream(std::ostream& os, const JsonValue* value, const size_t indent = 0) const override;

        /**
         * @brief Writes indentation spaces to the output stream
         * @param os Output stream to write to
         * @param indent Number of indentation levels
         */
        void writeIndentationIntoStream(std::ostream& os, const size_t indent) const;

        /**
         * @brief Default constructor (private for singleton pattern)
         */
        PrettyJsonFormatter() = default;

        /**
         * @brief Deleted copy constructor
         */
        PrettyJsonFormatter(const PrettyJsonFormatter&) = delete;

        /**
         * @brief Deleted assignment operator
         */
        PrettyJsonFormatter& operator=(const PrettyJsonFormatter&) = delete;
};

#endif