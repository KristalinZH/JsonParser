#ifndef JSONBOOLEAN
#define JSONBOOLEAN

#include "JsonValue.hpp"

/**
 * @brief Class representing a JSON boolean value
 * @inherit JsonValue
 */
class JsonBoolean : public JsonValue {
    public:
        /**
         * @brief Constructor that initializes the boolean value
         * @param _value The boolean value to store
         */
        JsonBoolean(const bool _value);

        /**
         * @brief Gets the type of JSON value
         * @return ValueType of the boolean
         */
        ValueType getType() const override;

        /**
         * @brief Creates a deep copy of the boolean value
         * @return Pointer to the cloned boolean
         */
        JsonValue* clone() const override;

        /**
         * @brief Prints boolean value to stream
         * @param stream Output stream to print to
         */
        void print(std::ostream& stream) const override;

        /**
         * @brief Accepts a visitor for the Visitor pattern
         * @param visitor Reference to the visitor
         */
        void accept(JsonValueVisitor& visitor) override;
    private:
        bool value;  ///< The stored boolean value
};


#endif