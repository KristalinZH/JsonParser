#ifndef JSONNUMBER
#define JSONNUMBER

#include "JsonValue.hpp"

/**
 * @brief Class representing a JSON number value
 * @inherit JsonValue
 */
class JsonNumber : public JsonValue {
    public:
        /**
         * @brief Constructor that initializes the number value
         * @param _value String representation of the number
         */
        JsonNumber(const std::string& _value);

        /**
         * @brief Gets the type of JSON value
         * @return ValueType of the number
         */
        ValueType getType() const override;

        /**
         * @brief Creates a deep copy of the number value
         * @return Pointer to the cloned number
         */
        JsonValue* clone() const override;

        /**
         * @brief Prints number value to stream
         * @param stream Output stream to print to
         */
        void print(std::ostream& stream) const override;

        /**
         * @brief Accepts a visitor for the Visitor pattern
         * @param visitor Reference to the visitor
         */
        void accept(JsonValueVisitor& visitor) override;
    private:
        std::string value;  ///< String representation of the number value
};


#endif