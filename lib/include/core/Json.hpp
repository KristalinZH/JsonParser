#ifndef JSON
#define JSON

#include "JsonValue.hpp"
#include "JsonEditor.hpp"
#include "JsonParser.hpp"
#include "JsonPrinter.hpp"
#include "JsonSearcher.hpp"
#include "JsonSerializer.hpp"
#include "JsonValidator.hpp"

/**
 * @brief Main class for JSON manipulation and operations
 */
class Json {
    public:
        /**
         * @brief Constructs a Json object from an input stream
         * @param stream Input stream containing JSON data
         */
        Json(std::istream& stream);

        /**
         * @brief Deleted copy constructor
         */
        Json(const Json& other) = delete;

        /**
         * @brief Deleted assignment operator
         */
        Json& operator=(const Json& other) = delete;

        /**
         * @brief Destructor
         */
        ~Json();

        /**
         * @brief Validates JSON content from an input stream
         * @param stream Input stream to validate
         * @return Validation result message
         */
        static std::string validate(std::istream& stream);

        /**
         * @brief Prints JSON content to output stream
         * @param stream Output stream to print to
         */
        void print(std::ostream& stream);

        /**
         * @brief Pretty prints JSON content to output stream
         * @param stream Output stream to print to
         */
        void prettyPrint(std::ostream& stream);

        /**
         * @brief Searches JSON content using regex pattern
         * @param stream Output stream for search results
         * @param searchRegex Regular expression pattern to search for
         */
        void search(std::ostream& stream, const std::string& searchRegex);

        /**
         * @brief Sets a value at specified path
         * @param path Path to set the value at
         * @param value Value to set
         */
        void set(const std::string& path, const std::string& value);

        /**
         * @brief Creates a new value at specified path
         * @param path Path to create the value at
         * @param value Value to create
         */
        void create(const std::string& path, const std::string& value);

        /**
         * @brief Erases value at specified path
         * @param path Path to the value to erase
         */
        void erase(const std::string& path);

        /**
         * @brief Moves value from one path to another
         * @param from Source path
         * @param to Destination path
         */
        void move(const std::string& from, const std::string& to);

        /**
         * @brief Saves JSON content to output stream
         * @param stream Output stream to save to
         * @param path Optional path to save specific part
         */
        void save(std::ostream& stream, const std::string& path);

    private:
        JsonValue* json;  ///< Pointer to the root JSON value

        /**
         * @brief Reads content from input stream
         * @param stream Input stream to read from
         * @return String containing stream content
         */
        static std::string readStreamContent(std::istream& stream);
};

#endif