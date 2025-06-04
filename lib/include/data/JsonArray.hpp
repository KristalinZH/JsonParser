#ifndef JSONARRAY
#define JSONARRAY

#include <vector>
#include "JsonValue.hpp"

/**
 * @brief Class representing a JSON array
 * @inherit JsonValue
 */
class JsonArray : public JsonValue {
    public:
        /**
         * @brief Gets the type of JSON value
         * @return ValueType of the array
         */
        ValueType getType() const override;

        /**
         * @brief Creates a deep copy of the array
         * @return Pointer to the cloned array
         */
        JsonValue* clone() const override;

        /**
         * @brief Prints array content to stream
         * @param stream Output stream to print to
         */
        void print(std::ostream& stream) const override;

        /**
         * @brief Accepts a visitor for the Visitor pattern
         * @param visitor Reference to the visitor
         */
        void accept(JsonValueVisitor& visitor) override;

        /**
         * @brief Default constructor
         */
        JsonArray() = default;

        /**
         * @brief Constructor from vector of JSON values
         * @param _arrayData Vector of pointers to JSON values
         */
        JsonArray(const std::vector<JsonValue*>& _arrayData);

        /**
         * @brief Copy constructor
         * @param other Array to copy from
         */
        JsonArray(const JsonArray& other);

        /**
         * @brief Copy assignment operator
         * @param other Array to copy from
         * @return Reference to this array
         */
        JsonArray& operator=(const JsonArray& other);

        /**
         * @brief Move constructor
         * @param other Array to move from
         */
        JsonArray(JsonArray&& other) noexcept;

        /**
         * @brief Move assignment operator
         * @param other Array to move from
         * @return Reference to this array
         */
        JsonArray& operator=(JsonArray&& other) noexcept;

        /**
         * @brief Destructor
         */
        ~JsonArray();

        /**
         * @brief Gets the size of the array
         * @return Number of elements in the array
         */
        size_t getSize() const;

        /**
         * @brief Array access operator
         * @param index Index of element to access
         * @return Pointer to the JSON value at index
         */
        JsonValue* operator[](const size_t index);

        /**
         * @brief Const array access operator
         * @param index Index of element to access
         * @return Const pointer to the JSON value at index
         */
        const JsonValue* operator[](const size_t index) const;

        /**
         * @brief Adds a value to the array
         * @param value Pointer to the JSON value to add
         */
        void addValue(const JsonValue* const value);     
    private:
        std::vector<JsonValue*> values;  ///< Vector storing JSON values

        /**
         * @brief Copies data from another array
         * @param _arrayData Vector of JSON values to copy
         */
        void copyData(const std::vector<JsonValue*>& _arrayData);

        /**
         * @brief Resets array data
         * @param _arrayData Vector of JSON values to reset with
         */
        void resetData(std::vector<JsonValue*>& _arrayData);

        /**
         * @brief Deletes all values in the array
         */
        void deleteData();
};


#endif