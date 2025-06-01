#ifndef JSONNUMBER
#define JSONNUMBER

#include "JsonValue.hpp"

class JsonNumber : public JsonValue {
    public:
        JsonNumber(const std::string& _value);
        ValueType getType() const override;
        JsonValue* clone() const override;
        void print(std::ostream& stream) const override;
        void accept(JsonValueVisitor& visitor) override;
    private:
        std::string value;
};


#endif