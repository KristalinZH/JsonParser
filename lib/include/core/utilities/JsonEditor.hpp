#ifndef JSONEDITOR
#define JSONEDITOR

#include "JsonValueVisitor.hpp"

class JsonEditor : public JsonValueVisitor {
    public:
        void visit(JsonNull& jsonValue) override;
        void visit(JsonBoolean& jsonValue) override;
        void visit(JsonNumber& jsonValue) override;
        void visit(JsonString& jsonValue) override;
        void visit(JsonArray& jsonValue) override;
        void visit(JsonObject& jsonValue) override;


        void set(const std::string& path, const std::string& value);
        void create(const std::string& path, const std::string& value);
        void erase(const std::string& path);
        void move(const std::string& from, const std::string& to);

        JsonEditor(JsonValue*& _rootRef);

    private:
        JsonValue*& rootRef;
        JsonValue* object = nullptr;

        JsonValue* createFromPath(const std::string& path, const std::string& value);
    
};

#endif