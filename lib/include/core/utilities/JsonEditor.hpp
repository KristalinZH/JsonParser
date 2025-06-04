#ifndef JSONEDITOR
#define JSONEDITOR

#include "JsonValueVisitor.hpp"

/**
 * @brief Class for editing JSON values using the visitor pattern
 * @inherit JsonValueVisitor
 */
class JsonEditor : public JsonValueVisitor {
    public:
        /**
         * @brief Visit method for JsonNull values
         * @param jsonValue Reference to the JsonNull value
         */
        void visit(JsonNull& jsonValue) override;

        /**
         * @brief Visit method for JsonBoolean values
         * @param jsonValue Reference to the JsonBoolean value
         */
        void visit(JsonBoolean& jsonValue) override;

        /**
         * @brief Visit method for JsonNumber values
         * @param jsonValue Reference to the JsonNumber value
         */
        void visit(JsonNumber& jsonValue) override;

        /**
         * @brief Visit method for JsonString values
         * @param jsonValue Reference to the JsonString value
         */
        void visit(JsonString& jsonValue) override;

        /**
         * @brief Visit method for JsonArray values
         * @param jsonValue Reference to the JsonArray value
         */
        void visit(JsonArray& jsonValue) override;

        /**
         * @brief Visit method for JsonObject values
         * @param jsonValue Reference to the JsonObject value
         */
        void visit(JsonObject& jsonValue) override;

        /**
         * @brief Sets a value at the specified path
         * @param path Path to the target location
         * @param value String representation of the value to set
         */
        void set(const std::string& path, const std::string& value);

        /**
         * @brief Creates a new value at the specified path
         * @param path Path where to create the value
         * @param value String representation of the value to create
         */
        void create(const std::string& path, const std::string& value);

        /**
         * @brief Erases a value at the specified path
         * @param path Path to the value to erase
         */
        void erase(const std::string& path);

        /**
         * @brief Moves a value from one path to another
         * @param from Source path
         * @param to Destination path
         */
        void move(const std::string& from, const std::string& to);

        /**
         * @brief Constructor that takes a reference to the root JSON value
         * @param _rootRef Reference to the root JSON value pointer
         */
        JsonEditor(JsonValue*& _rootRef);

    private:
        JsonValue*& rootRef;  ///< Reference to the root JSON value pointer
        JsonValue* object = nullptr;  ///< Pointer to the current JSON object being edited

        /**
         * @brief Creates a new JSON value from a path and string value
         * @param path Path where to create the value
         * @param value String representation of the value to create
         * @return Pointer to the created JSON value
         */
        JsonValue* createFromPath(const std::string& path, const std::string& value);
};

#endif