#ifndef JSONVALUE
#define JSONVALUE

#include <iostream>
#include <string>

class JsonValueVisitor;

/**
 * @brief Enumeration of possible JSON value types
 */
enum class ValueType {
    Null,    ///< JSON null value
    Boolean, ///< JSON boolean value
    Number,  ///< JSON number value
    String,  ///< JSON string value
    Array,   ///< JSON array value
    Object   ///< JSON object value
};

/**
 * @brief Abstract base class for all JSON values
 */
class JsonValue {
    public:
        /**
         * @brief Gets the type of JSON value
         * @return ValueType of the JSON value
         */
        virtual ValueType getType() const = 0;

        /**
         * @brief Creates a deep copy of the JSON value
         * @return Pointer to the cloned value
         */
        virtual JsonValue* clone() const = 0;

        /**
         * @brief Prints JSON value to stream
         * @param stream Output stream to print to
         */
        virtual void print(std::ostream& stream) const = 0;

        /**
         * @brief Accepts a visitor for the Visitor pattern
         * @param visitor Reference to the visitor
         */
        virtual void accept(JsonValueVisitor& visitor) = 0;

        /**
         * @brief Virtual destructor
         */
        virtual ~JsonValue() = default;
};

/**
 * @brief Stream operator for JSON values
 * @param stream Output stream
 * @param jsonValue Pointer to JSON value to output
 * @return Reference to the output stream
 */
inline std::ostream& operator<<(std::ostream& stream, const JsonValue* jsonValue) {
    jsonValue -> print(stream);
    return stream;
}

/**
 * @brief Stream operator for ValueType enum
 * @param stream Output stream
 * @param type ValueType to output
 * @return Reference to the output stream
 */
inline std::ostream& operator<<(std::ostream& stream, const ValueType& type) {
    switch (type)
    {
        case ValueType::Null : {
            stream << "null";
            break;
        }
        case ValueType::Boolean : {
            stream << "boolean";
            break;
        }
        case ValueType::Number : {
            stream << "number";
            break;
        }
        case ValueType::String : {
            stream << "string";
            break;
        }
        case ValueType::Array : {
            stream << "array";
            break;
        }
        default : {
            stream << "object";
            break;
        }
    }

    return stream;
}

#endif