#ifndef JSONVALDIATOR
#define JSONVALDIATOR

#include <iostream>
#include <string>
#include <utility>
#include <unordered_set>

/**
 * @brief Enumeration for different JSON reading modes
 */
enum class ReadingMode {
    ReadingPrimary,  ///< Reading a primary value (null, boolean, number, string)
    ReadingArray,    ///< Reading an array
    ReadingObject    ///< Reading an object
};

/**
 * @brief Class for validating JSON syntax and structure
 */
class JsonValidator {
    public:
        /**
         * @brief Validates JSON content from an input stream
         * @param stream Input stream containing JSON data
         * @return Pair of boolean (valid/invalid) and error message string
         */
        static std::pair<bool, std::string> validateJson(std::istream& stream);
    private:
        /**
         * @brief Validates a JSON null value
         * @param stream Input stream to validate
         * @param lastSymbol Last character read
         * @param row Current row number
         * @param lastRowPosition Position in current row
         * @return Pair of validation result and error message
         */
        static std::pair<bool, std::string> validateNull(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);

        /**
         * @brief Validates a JSON boolean value
         * @param stream Input stream to validate
         * @param lastSymbol Last character read
         * @param row Current row number
         * @param lastRowPosition Position in current row
         * @return Pair of validation result and error message
         */
        static std::pair<bool, std::string> validateBoolean(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);

        /**
         * @brief Validates a JSON number value
         * @param stream Input stream to validate
         * @param lastSymbol Last character read
         * @param row Current row number
         * @param lastRowPosition Position in current row
         * @return Pair of validation result and error message
         */
        static std::pair<bool, std::string> validateNumber(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);

        /**
         * @brief Validates a JSON string value
         * @param stream Input stream to validate
         * @param lastSymbol Last character read
         * @param row Current row number
         * @param lastRowPosition Position in current row
         * @return Pair of validation result and error message
         */
        static std::pair<bool, std::string> validateString(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);

        /**
         * @brief Validates a primary JSON value
         * @param stream Input stream to validate
         * @param symbol Current symbol being processed
         * @param row Current row number
         * @param position Current position in row
         * @param stateOfReading Current reading state
         * @param mode Current reading mode
         * @param isCommaFound Flag indicating if comma was found
         * @param objectKeys Set of object keys for duplicate detection
         * @return Pair of validation result and error message
         */
        static std::pair<bool, std::string> validatePrimary(std::istream& stream, const char symbol, const size_t row, size_t& position, size_t& stateOfReading, const ReadingMode& mode, bool& isCommaFound, std::unordered_set<std::string>& objectKeys);

        /**
         * @brief Main validation function for JSON content
         * @param stream Input stream to validate
         * @param row Current row number
         * @param position Current position in row
         * @param lastBrace Last opening brace/bracket encountered
         * @param mode Current reading mode
         * @return Pair of validation result and error message
         */
        static std::pair<bool, std::string> validate(std::istream& stream, size_t& row, size_t& position, char lastBrace = '\0', const ReadingMode& mode = ReadingMode::ReadingPrimary);
};

#endif