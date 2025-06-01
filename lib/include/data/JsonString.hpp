#ifndef JSONSTRING
#define JSONSTRING

#include "JsonValue.hpp"

class JsonString : public JsonValue {
    public:
        JsonString(const std::string& _value);
        ValueType getType() const override;
        JsonValue* clone() const override;
        void print(std::ostream& stream) const override;
        void accept(JsonValueVisitor& visitor) override;
    private:
        std::string value;
};


#endif