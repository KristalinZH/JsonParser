#ifndef COMPACTJSONFORMATTER
#define COMPACTJSONFORMATTER

#include "JsonFormatter.hpp"

class CompactJsonFormatter : public JsonFormatter{
    public:
        static CompactJsonFormatter& getInstance();

        std::string format(const JsonArray* value, const size_t indent = 0) const override;
        std::string format(const JsonObject* value, const size_t indent = 0) const override;
    private:
        void writeJsonIntoStream(std::ostream& os, const JsonValue* value, const size_t indent = 0) const override;

        CompactJsonFormatter() = default;
        CompactJsonFormatter(const CompactJsonFormatter&) = delete;
        CompactJsonFormatter& operator=(const CompactJsonFormatter&) = delete;
};

#endif