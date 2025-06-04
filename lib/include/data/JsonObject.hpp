#ifndef JSONOBJECT
#define JSONOBJECT

#include <list>
#include <unordered_map>
#include <vector>
#include "JsonValue.hpp"

/**
 * @brief Class representing a JSON object containing key-value pairs
 * @inherit JsonValue
 */
class JsonObject : public JsonValue {
    public:
        /**
         * @brief Gets the type of JSON value
         * @return ValueType of the object
         */
        ValueType getType() const override;

        /**
         * @brief Creates a deep copy of the object
         * @return Pointer to the cloned object
         */
        JsonValue* clone() const override;

        /**
         * @brief Prints object content to stream
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
        JsonObject() = default;

        /**
         * @brief Constructor from keys and values
         * @param _keys List of keys
         * @param _objectData Map of key-value pairs
         */
        JsonObject(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData);

        /**
         * @brief Copy constructor
         * @param other Object to copy from
         */
        JsonObject(const JsonObject& other);

        /**
         * @brief Copy assignment operator
         * @param other Object to copy from
         * @return Reference to this object
         */
        JsonObject& operator=(const JsonObject& other);

        /**
         * @brief Move constructor
         * @param other Object to move from
         */
        JsonObject(JsonObject&& other) noexcept;

        /**
         * @brief Move assignment operator
         * @param other Object to move from
         * @return Reference to this object
         */
        JsonObject& operator=(JsonObject&& other) noexcept;

        /**
         * @brief Destructor
         */
        ~JsonObject();

        /**
         * @brief Gets the number of key-value pairs
         * @return Size of the object
         */
        size_t getSize() const;

        /**
         * @brief Gets all keys in the object
         * @return Vector of keys
         */
        std::vector<std::string> getKeys() const;

        /**
         * @brief Gets all values in the object
         * @return Vector of const pointers to values
         */
        std::vector<const JsonValue*> getValues() const;

        /**
         * @brief Checks if a key exists in the object
         * @param key Key to check
         * @return True if key exists, false otherwise
         */
        bool containsKey(const std::string& key) const;

        /**
         * @brief Adds a key-value pair to the object
         * @param key Key to add
         * @param value Pointer to value to add
         */
        void addKVP(const std::string& key, const JsonValue* const value);

        /**
         * @brief Edits an existing key-value pair
         * @param key Key to edit
         * @param value New value to set
         */
        void editKVP(const std::string& key, const JsonValue* const value);

        /**
         * @brief Removes a key-value pair
         * @param key Key to remove
         */
        void removeKVP(const std::string& key);

        /**
         * @brief Gets the value associated with a key
         * @param key Key to look up
         * @return Const pointer to the value
         */
        const JsonValue* getValue(const std::string& key) const;
    private:
        std::list<std::string> keys;  ///< List of keys maintaining insertion order
        std::unordered_map<std::string, JsonValue*> values;  ///< Map of key-value pairs

        /**
         * @brief Copies data from another object
         * @param _keys List of keys to copy
         * @param _objectData Map of values to copy
         */
        void copyData(const std::list<std::string>& _keys, const std::unordered_map<std::string, JsonValue*>& _objectData);

        /**
         * @brief Resets object data
         * @param _objectData Map of new values
         */
        void resetData(std::unordered_map<std::string, JsonValue*>& _objectData);

        /**
         * @brief Deletes all values in the object
         */
        void deleteData();
};


#endif