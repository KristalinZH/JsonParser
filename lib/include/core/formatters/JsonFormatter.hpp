#ifndef JSONFORMATTER
#define JSONFORMATTER

#include "JsonArray.hpp"
#include "JsonObject.hpp"

class JsonFormatter{
    public:
        virtual std::string format(const JsonArray& value, const size_t indent = 0) const = 0;
        virtual std::string format(const JsonObject& value, const size_t indent = 0) const = 0;
        virtual ~JsonFormatter() = default;
    protected:
        virtual void writeJsonIntoStream(std::ostream& os, const JsonValue& value, const size_t indent = 0) const = 0;
};

#endif