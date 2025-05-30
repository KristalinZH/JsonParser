#ifndef PRETTYJSONFORMATTER
#define PRETTYJSONFORMATTER

#include "JsonFormatter.hpp"

class PrettyJsonFormatter : public JsonFormatter{
    public:
        std::string format(const JsonArray& value, const size_t indent = 0) const override;
        std::string format(const JsonObject& value, const size_t indent = 0) const override;
    private:
        void writeJsonIntoStream(std::ostream& os, const JsonValue& value, const size_t indent = 0) const override;
        void writeIndentationIntoStream(std::ostream& os, const size_t indent) const;
};

#endif