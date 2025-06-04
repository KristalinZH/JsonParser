#ifndef JSONSTRING
#define JSONSTRING

#include "JsonValue.hpp"

/**
 * @brief Class representing a JSON string value
 * @inherit JsonValue
 */
class JsonString : public JsonValue {
    public:
        /**
         * @brief Constructor that initializes the string value
         * @param _value The string value to store
         */
        JsonString(const std::string& _value);

        /**
         * @brief Gets the type of JSON value
         * @return ValueType of the string
         */
        ValueType getType() const override;

        /**
         * @brief Creates a deep copy of the string value
         * @return Pointer to the cloned string
         */
        JsonValue* clone() const override;

        /**
         * @brief Prints string value to stream
         * @param stream Output stream to print to
         */
        void print(std::ostream& stream) const override;

        /**
         * @brief Accepts a visitor for the Visitor pattern
         * @param visitor Reference to the visitor
         */
        void accept(JsonValueVisitor& visitor) override;
    private:
        std::string value;  ///< The stored string value
};


#endif