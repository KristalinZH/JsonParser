#include <sstream>
#include "JsonEditor.hpp"
#include "Path.hpp"
#include "JsonParser.hpp"
#include "JsonFactory.hpp"
#include "JsonPrinter.hpp"

void JsonEditor::visit(JsonNull& jsonValue) {
   return;
}

void JsonEditor::visit(JsonBoolean& jsonValue)  {
    return;
}

void JsonEditor::visit(JsonNumber& jsonValue)  {
    return;
}

void JsonEditor::visit(JsonString& jsonValue) {
    return;
}

void JsonEditor::visit(JsonArray& jsonValue) {
   return;
}

void JsonEditor::visit(JsonObject& jsonValue) {
    object = rootRef;
}

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

void JsonEditor::move(const std::string& from, const std::string& to) {
    const std::string& valueToMove = JsonPrinter::prettyPrint((Path::getValue(object, from)));

    erase(from);

    if(Path::validatePath(object, to)) {
        set(to, valueToMove);
        return;
    }

    create(to, valueToMove);
}

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

JsonEditor::JsonEditor(JsonValue*& _rootRef):rootRef(_rootRef) {}