#ifndef JSONSEARCHER
#define JSONSEARCHER

#include <string>
#include <regex>
#include "JsonValueVisitor.hpp"

/**
 * @brief Class for searching JSON values using regex patterns
 * @inherit JsonValueVisitor
 */
class JsonSearcher : public JsonValueVisitor {
    public:
        /**
         * @brief Visit method for JsonNull values
         * @param jsonValue Reference to the JsonNull value
         */
        void visit(JsonNull& jsonValue) override;

        /**
         * @brief Visit method for JsonBoolean values
         * @param jsonValue Reference to the JsonBoolean value
         */
        void visit(JsonBoolean& jsonValue) override;

        /**
         * @brief Visit method for JsonNumber values
         * @param jsonValue Reference to the JsonNumber value
         */
        void visit(JsonNumber& jsonValue) override;

        /**
         * @brief Visit method for JsonString values
         * @param jsonValue Reference to the JsonString value
         */
        void visit(JsonString& jsonValue) override;

        /**
         * @brief Visit method for JsonArray values
         * @param jsonValue Reference to the JsonArray value
         */
        void visit(JsonArray& jsonValue) override;

        /**
         * @brief Visit method for JsonObject values
         * @param jsonValue Reference to the JsonObject value
         */
        void visit(JsonObject& jsonValue) override;
    
        /**
         * @brief Gets the search results
         * @return Vector of pointers to matching JsonValue objects
         */
        std::vector<JsonValue*>getResults() const;

        /**
         * @brief Constructor that takes a regex pattern
         * @param searchRegex Regular expression pattern to search for
         */
        JsonSearcher(const std::string& searchRegex);

        /**
         * @brief Destructor
         */
        ~JsonSearcher();
    private:
        std::regex regex;  ///< Regular expression pattern for searching
        std::vector<JsonValue*> searchResults;  ///< Vector storing search results
};

#endif