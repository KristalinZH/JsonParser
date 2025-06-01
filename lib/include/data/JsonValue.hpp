#ifndef JSONVALUE
#define JSONVALUE

#include <iostream>
#include <string>

class JsonValueVisitor;

enum class ValueType {
    Null,
    Boolean,
    Number,
    String,
    Array,
    Object
};

class JsonValue {
    public:
        virtual ValueType getType() const = 0;
        virtual JsonValue* clone() const = 0;
        virtual void print(std::ostream& stream) const = 0;
        virtual void accept(JsonValueVisitor& visitor) = 0;
        virtual ~JsonValue() = default;
};

inline std::ostream& operator<<(std::ostream& stream, const JsonValue* jsonValue) {
    jsonValue -> print(stream);
    return stream;
}

#endif