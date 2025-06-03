#ifndef JSONSEARCHER
#define JSONSEARCHER

#include <string>
#include <regex>
#include "JsonValueVisitor.hpp"

class JsonSearcher : public JsonValueVisitor {
    public:
        void visit(JsonNull& jsonValue) override;
        void visit(JsonBoolean& jsonValue) override;
        void visit(JsonNumber& jsonValue) override;
        void visit(JsonString& jsonValue) override;
        void visit(JsonArray& jsonValue) override;
        void visit(JsonObject& jsonValue) override;
    
        std::vector<JsonValue*>getResults() const;

        JsonSearcher(const std::string& searchRegex);
        ~JsonSearcher();
    private:
        std::regex regex;
        std::vector<JsonValue*> searchResults;
};

#endif