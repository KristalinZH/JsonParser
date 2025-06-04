#ifndef JSONNULL
#define JSONNULL

#include "JsonValue.hpp"

/**
 * @brief Class representing a JSON null value
 * @inherit JsonValue
 */
class JsonNull : public JsonValue {
    public:
        /**
         * @brief Gets the type of JSON value
         * @return ValueType of null
         */
        ValueType getType() const override;

        /**
         * @brief Creates a deep copy of the null value
         * @return Pointer to the cloned null value
         */
        JsonValue* clone() const override;

        /**
         * @brief Prints null value to stream
         * @param stream Output stream to print to
         */
        void print(std::ostream& stream) const override;

        /**
         * @brief Accepts a visitor for the Visitor pattern
         * @param visitor Reference to the visitor
         */
        void accept(JsonValueVisitor& visitor) override;
};


#endif