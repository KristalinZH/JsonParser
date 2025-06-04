#ifndef JSONVALUEVISITOR
#define JSONVALUEVISITOR

#include "JsonNull.hpp"
#include "JsonBoolean.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"
#include "JsonArray.hpp"
#include "JsonObject.hpp"

/**
 * @brief Abstract visitor class for JSON values implementing the Visitor pattern
 */
class JsonValueVisitor {
    public:
        /**
         * @brief Visit method for JsonNull values
         * @param jsonValue Reference to JsonNull to visit
         */
        virtual void visit(JsonNull& jsonValue) = 0;

        /**
         * @brief Visit method for JsonBoolean values
         * @param jsonValue Reference to JsonBoolean to visit
         */
        virtual void visit(JsonBoolean& jsonValue) = 0;

        /**
         * @brief Visit method for JsonNumber values
         * @param jsonValue Reference to JsonNumber to visit
         */
        virtual void visit(JsonNumber& jsonValue) = 0;

        /**
         * @brief Visit method for JsonString values
         * @param jsonValue Reference to JsonString to visit
         */
        virtual void visit(JsonString& jsonValue) = 0;

        /**
         * @brief Visit method for JsonArray values
         * @param jsonValue Reference to JsonArray to visit
         */
        virtual void visit(JsonArray& jsonValue) = 0;

        /**
         * @brief Visit method for JsonObject values
         * @param jsonValue Reference to JsonObject to visit
         */
        virtual void visit(JsonObject& jsonValue) = 0;

        /**
         * @brief Virtual destructor
         */
        virtual ~JsonValueVisitor() = default; 
};


#endif