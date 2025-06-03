#ifndef JSON
#define JSON

#include "JsonValue.hpp"
#include "JsonEditor.hpp"
#include "JsonParser.hpp"
#include "JsonPrinter.hpp"
#include "JsonSearcher.hpp"
#include "JsonSerializer.hpp"
#include "JsonValidator.hpp"

class Json {
    public:
        Json(std::istream& stream);
        Json(const Json& other) = delete;
        Json& operator=(const Json& other) = delete;
        ~Json();

        static std::string validate(std::istream& stream);
        void print(std::ostream& stream);
        void prettyPrint(std::ostream& stream);
        void search(std::ostream& stream, const std::string& searchRegex);
        void set(const std::string& path, const std::string& value);
        void create(const std::string& path, const std::string& value);
        void erase(const std::string& path);
        void move(const std::string& from, const std::string& to);
        void save(std::ostream& stream, const std::string& path);

    private:
        JsonValue* json;

        static std::string readStreamContent(std::istream& stream);
};

#endif