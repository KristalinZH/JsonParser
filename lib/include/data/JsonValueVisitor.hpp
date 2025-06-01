#ifndef JSONVALUEVISITOR
#define JSONVALUEVISITOR

#include "JsonNull.hpp"
#include "JsonBoolean.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"
#include "JsonArray.hpp"
#include "JsonObject.hpp"

class JsonValueVisitor {
    public:
        virtual void visit(JsonNull& jsonValue) = 0;
        virtual void visit(JsonBoolean& jsonValue) = 0;
        virtual void visit(JsonNumber& jsonValue) = 0;
        virtual void visit(JsonString& jsonValue) = 0;
        virtual void visit(JsonArray& jsonValue) = 0;
        virtual void visit(JsonObject& jsonValue) = 0;
        virtual ~JsonValueVisitor() = default; 
};


#endif