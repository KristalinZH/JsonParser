#ifndef JSON
#define JSON

#include "JsonValue.hpp"
#include "JsonEditor.hpp"
#include "JsonParser.hpp"
#include "JsonPrinter.hpp"
#include "JsonSearcher.hpp"
#include "JsonSerializer.hpp"
#include "JsonValidator.hpp"

class Json{
    public:
        Json() = delete;
        Json(const Json& other) = delete;
        Json& operator=(const Json& other) = delete;
        Json(Json&& other) noexcept = default;
        Json& operator=(Json&& other) noexcept = default;
        ~Json() = default;

        static Json parse(std::istream& stream);
        static std::pair<bool, std::string> validate(std::istream& stream);
        std::string print();
        std::pair<bool, std::string> search(const std::regex& reg);
        std::pair<bool, std::string> set(const std::string& path, const std::string value);
        std::pair<bool, std::string> create(const std::string& path, const std::string value);
        std::pair<bool, std::string> erase(const std::string& path);
        std::pair<bool, std::string> move(const std::string& from, const std::string& to);
        std::pair<bool, std::string> save(std::ostream& stream, const std::string& path = "");

    private:
        std::string streamContnent;
        std::shared_ptr<JsonValue> json;

        static JsonEditor editor;
        static JsonParser parser;
        static JsonPrinter printer;
        static JsonSearcher searcher;
        static JsonSerializer serializer;
        static JsonValidator validator; 

        explicit Json(const std::string& _streamContent, const std::shared_ptr<JsonValue>& _json);
};

#endif