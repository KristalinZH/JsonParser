#ifndef JSONBOOLEAN
#define JSONBOOLEAN

#include "JsonValue.hpp"

class JsonBoolean : public JsonValue {
    public:
        JsonBoolean(const bool _value);
        ValueType getType() const override;
        JsonValue* clone() const override;
        void print(std::ostream& stream) const override;
        void accept(JsonValueVisitor& visitor) override;
    private:
        bool value;
};


#endif