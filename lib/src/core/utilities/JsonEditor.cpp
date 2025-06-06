#include <sstream>
#include "JsonEditor.hpp"
#include "Path.hpp"
#include "JsonParser.hpp"
#include "JsonFactory.hpp"
#include "JsonPrinter.hpp"

/**
 * @brief Constructor that initializes the root reference
 * @param _rootRef Reference to the root JSON value pointer
 */
JsonEditor::JsonEditor(JsonValue*& _rootRef):rootRef(_rootRef) {}

/**
 * @brief Visitor implementation for JsonNull values
 * @param jsonValue Reference to JsonNull value
 */
void JsonEditor::visit(JsonNull& jsonValue) {
   return;
}

/**
 * @brief Visitor implementation for JsonBoolean values
 * @param jsonValue Reference to JsonBoolean value
 */
void JsonEditor::visit(JsonBoolean& jsonValue)  {
    return;
}

/**
 * @brief Visitor implementation for JsonNumber values
 * @param jsonValue Reference to JsonNumber value
 */
void JsonEditor::visit(JsonNumber& jsonValue)  {
    return;
}

/**
 * @brief Visitor implementation for JsonString values
 * @param jsonValue Reference to JsonString value
 */
void JsonEditor::visit(JsonString& jsonValue) {
    return;
}

/**
 * @brief Visitor implementation for JsonArray values
 * @param jsonValue Reference to JsonArray value
 */
void JsonEditor::visit(JsonArray& jsonValue) {
   return;
}

/**
 * @brief Visitor implementation for JsonObject values
 * @param jsonValue Reference to JsonObject value
 */
void JsonEditor::visit(JsonObject& jsonValue) {
    object = rootRef;
}

/**
 * @brief Sets a value at the specified path
 * @param path Path where to set the value
 * @param value String representation of the value to set
 */
void JsonEditor::set(const std::string& path, const std::string& value) {

    if(object == nullptr) {
        create(path, value);
        return;
    }
    
    if(path == "") {
        delete rootRef;

        std::istringstream stream(value);

        rootRef = JsonParser::parse(stream);
        object = rootRef;

        return;
    }

    JsonObject* node = const_cast<JsonObject*>(Path::getParent(object, path));

    const std::string key = Path::getKey(path);

    std::istringstream stream(value);

    const JsonValue* newValue = JsonParser::parse(stream);

    node -> editKVP(key, newValue);

    delete newValue;
}

/**
 * @brief Creates a new value at the specified path
 * @param path Path where to create the value
 * @param value String representation of the value to create
 */
void JsonEditor::create(const std::string& path, const std::string& value) {

    if(object == nullptr) {
        const std::string root = Path::getRoot(path);
        JsonValue* recursiveValue = createFromPath(Path::getChildren(path), value);
        rootRef = new JsonObject({root}, {{root, recursiveValue}});
        object = rootRef;
        delete recursiveValue;
        return;
    }

    JsonValue* lastNode = const_cast<JsonValue*>(Path::getLastElement(object, path));

    const std::string newPath = Path::getLastPath(object, path);
    const std::string& root = Path::getRoot(newPath);

    JsonValue* recursiveValue = createFromPath(Path::getChildren(newPath), value);

    if(lastNode -> getType() == ValueType::Object){
        static_cast<JsonObject*>(lastNode) -> addKVP(root, recursiveValue);
    }
    else {

        size_t pos = path.find('/' + newPath);

        if(pos == 0) {
            pos = path.length();
        }

        const JsonValue* setObject = JsonFactory::create({root}, {{root, recursiveValue}});

        const std::string setValue = JsonPrinter::prettyPrint(setObject);

        delete setObject;

        set(path.substr(0, pos), setValue);
    }

    delete recursiveValue;

}

/**
 * @brief Erases a value at the specified path
 * @param path Path to the value to erase
 */
void JsonEditor::erase(const std::string& path) {

    if(path == "") {
        delete rootRef;
        rootRef = nullptr;
        object = rootRef;
        return;
    }

    JsonObject* node = const_cast<JsonObject*>(Path::getParent(object, path));
    const std::string key = Path::getKey(path);

    node -> removeKVP(key);
}

/**
 * @brief Moves a value from one path to another
 * @param from Source path
 * @param to Destination path
 */
void JsonEditor::move(const std::string& from, const std::string& to) {
    const std::string& valueToMove = JsonPrinter::prettyPrint((Path::getValue(object, from)));

    erase(from);

    if(Path::validatePath(object, to)) {

        JsonObject* node = const_cast<JsonObject*>(Path::getParent(object, to));

        const std::string key = Path::getKey(to);

        std::istringstream stream(valueToMove);

        const JsonValue* newValue = JsonParser::parse(stream);

        node -> addKVP(key, newValue);

        delete newValue;

        return;
    }

    create(to, valueToMove);
}

/**
 * @brief Creates a JSON value from a path and string value
 * @param path Path to create the value at
 * @param value String representation of the value
 * @return Pointer to the created JSON value
 */
JsonValue* JsonEditor::createFromPath(const std::string& path, const std::string& value) {

    const std::string root = Path::getRoot(path);

    if(path == "") {
        std::istringstream stream(value);
        return JsonParser::parse(stream);
    }

    JsonValue* recursiveValue = createFromPath(Path::getChildren(path), value);

    JsonValue* object = JsonFactory::create({root}, {{root, recursiveValue}});

    delete recursiveValue;

    return object;
}
