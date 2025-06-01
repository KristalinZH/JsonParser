#ifndef JSONNULL
#define JSONNULL

#include "JsonValue.hpp"

class JsonNull : public JsonValue {
    public:
        ValueType getType() const override;
        JsonValue* clone() const override;
        void print(std::ostream& stream) const override;
        void accept(JsonValueVisitor& visitor) override;
};


#endif