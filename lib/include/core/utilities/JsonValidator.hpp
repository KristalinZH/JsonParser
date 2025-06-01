#ifndef JSONVALDIATOR
#define JSONVALDIATOR

#include <iostream>
#include <string>
#include <utility>
#include <unordered_set>

enum class ReadingMode{
    ReadingPrimary,
    ReadingArray,
    ReadingObject
};

class JsonValidator{
    public:
        std::pair<bool, std::string> validateJson(std::istream& stream);
    private:
        std::pair<bool, std::string> validateNull(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);
        std::pair<bool, std::string> validateBoolean(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);
        std::pair<bool, std::string> validateNumber(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);
        std::pair<bool, std::string> validateString(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition);
        std::pair<bool, std::string> validatePrimary(std::istream& stream, const char symbol, const size_t row, size_t& position, size_t& stateOfReading, const ReadingMode& mode, bool& isCommaFound, std::unordered_set<std::string>& objectKeys);
        std::pair<bool, std::string> validate(std::istream& stream, size_t& row, size_t& position, char lastBrace = '\0', const ReadingMode& mode = ReadingMode::ReadingPrimary);
};

#endif