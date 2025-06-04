#ifndef JSONFORMATTER
#define JSONFORMATTER

#include "JsonArray.hpp"
#include "JsonObject.hpp"

/**
 * @brief Enumeration of available JSON formatting types
 */
enum class FormatterType {
    Compact,  ///< Compact formatting without whitespace
    Pretty    ///< Pretty formatting with indentation and newlines
};

/**
 * @brief Abstract base class for JSON formatters
 */
class JsonFormatter{
    public:
        /**
         * @brief Formats a JsonArray into a string
         * @param value Pointer to the JsonArray to format
         * @param indent Current indentation level
         * @return Formatted string representation
         */
        virtual std::string format(const JsonArray* value, const size_t indent = 0) const = 0;

        /**
         * @brief Formats a JsonObject into a string
         * @param value Pointer to the JsonObject to format
         * @param indent Current indentation level
         * @return Formatted string representation
         */
        virtual std::string format(const JsonObject* value, const size_t indent = 0) const = 0;

        /**
         * @brief Virtual destructor
         */
        virtual ~JsonFormatter() = default;
    protected:
        /**
         * @brief Writes JSON value to an output stream
         * @param os Output stream to write to
         * @param value Pointer to the JsonValue to write
         * @param indent Current indentation level
         */
        virtual void writeJsonIntoStream(std::ostream& os, const JsonValue* value, const size_t indent = 0) const = 0;
};

#endif