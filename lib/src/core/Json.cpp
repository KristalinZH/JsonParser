#include "Json.hpp"
#include "JsonFactory.hpp"
#include "Path.hpp"

Json::Json(std::istream& stream) {
    const std::string content = readStreamContent(stream);

    if(content == "") {
        throw std::runtime_error("Empty stream!");
    }

    std::istringstream contentStream(content);
    std::pair<bool, std::string> isValid = JsonValidator::validateJson(contentStream);

    if(!isValid.first) {
        throw std::runtime_error(isValid.second);
    }
    
    contentStream.clear();
    contentStream.str(content);
    contentStream.seekg(0);
    
    json = JsonParser::parse(contentStream);

}

Json::~Json() {
    delete json;
    json = nullptr;
}

std::string Json::validate(std::istream& stream) {
    const std::string content = readStreamContent(stream);

    std::istringstream contentStream(content);
    std::pair<bool, std::string> isValid = JsonValidator::validateJson(contentStream);

    if(isValid.first) {
        return "The json is valid!";
    }

    return isValid.second;
}

void Json::print(std::ostream& stream) {
    stream << JsonPrinter::print(json);
}

void Json::prettyPrint(std::ostream& stream) {
    stream << JsonPrinter::prettyPrint(json);
}

void Json::search(std::ostream& stream, const std::string& searchRegex) {

    if(json -> getType() != ValueType::Object && json -> getType() != ValueType::Array ) {
        std::ostringstream errorMessageSteam;
        errorMessageSteam << "Cannot perform search on type " << json -> getType();
        throw std::runtime_error(errorMessageSteam.str());
    }

    JsonSearcher searcher(searchRegex);

    json -> accept(searcher);

    std::vector<JsonValue*> searchResults = searcher.getResults();

    if(searchResults.size() == 0) {
        stream << "No matching results were found!";
        return;
    }

    JsonValue* arrayWithResults = JsonFactory::create(searchResults);

    stream << JsonPrinter::prettyPrint(arrayWithResults);

    delete arrayWithResults;

}

void Json::set(const std::string& path, const std::string& value) {

    if(!(Path::validatePath(json, path))) {
        throw std::runtime_error("Cannot perform set on path to non-existing element!");
    }

    if(json -> getType() != ValueType::Object) {
        std::ostringstream errorMessageSteam;
        errorMessageSteam << "Cannot perform set on type " << json -> getType();
        throw std::runtime_error(errorMessageSteam.str());
    }

    std::istringstream valueStream(value);

    std::pair<bool, std::string> isValid = JsonValidator::validateJson(valueStream);

    if(!isValid.first) {
        const std::string message = "Invalid value! " + isValid.second;
        throw std::runtime_error(message);
    }

    JsonEditor editor(json);

    json -> accept(editor);

    editor.set(path, value);
}

void Json::create(const std::string& path, const std::string& value) {

    if(json != nullptr && json -> getType() != ValueType::Object) {
        std::ostringstream errorMessageSteam;
        errorMessageSteam << "Cannot perform create on type " << json -> getType();
        throw std::runtime_error(errorMessageSteam.str());
    }

    if(Path::validatePath(json, path)) {
        throw std::runtime_error("Cannot perform create on path to already existing element!");
    }

    std::istringstream valueStream(value);

    std::pair<bool, std::string> isValid = JsonValidator::validateJson(valueStream);

    if(!isValid.first) {
        const std::string message = "Invalid value! " + isValid.second;
        throw std::runtime_error(message);
    }

    JsonEditor editor(json);

    json -> accept(editor);

    editor.create(path, value);
}

void Json::erase(const std::string& path) {

    if(json != nullptr && json -> getType() != ValueType::Object) {
        std::ostringstream errorMessageSteam;
        errorMessageSteam << "Cannot perform erase on type " << json -> getType();
        throw std::runtime_error(errorMessageSteam.str());
    }

    if(!(Path::validatePath(json, path))) {
        throw std::runtime_error("Cannot perform delete on path to non-existing element!");
    }

    JsonEditor editor(json);

    json -> accept(editor);

    editor.erase(path);
}

void Json::move(const std::string& from, const std::string& to) {
    
    if(json == nullptr) {
        throw std::runtime_error("Cannot perform move on deleted json!");
    }

    if(json -> getType() != ValueType::Object) {
        std::ostringstream errorMessageSteam;
        errorMessageSteam << "Cannot perform move on type " << json -> getType();
        throw std::runtime_error(errorMessageSteam.str());
    }

    if(!(Path::validatePath(json, from))) {
        throw std::runtime_error("Cannot perform move on path to non-existing element!");
    }

    JsonEditor editor(json);

    json -> accept(editor);

    editor.move(from, to);
}

void Json::save(std::ostream& stream, const std::string& path) {
    if(!(Path::validatePath(json, path))) {
        throw std::runtime_error("Cannot perform save on path to non-existing element!");
    }

    JsonSerializer::save(json, stream, path);
}

std::string Json::readStreamContent(std::istream& stream) {
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}