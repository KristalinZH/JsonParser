#include "Json.hpp"
#include "JsonFactory.hpp"
#include "Path.hpp"

/**
 * @brief Constructor that initializes JSON from input stream
 * @param stream Input stream containing JSON data
 * @throws std::runtime_error if stream is empty or JSON is invalid
 */
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

/**
 * @brief Destructor that cleans up JSON data
 */
Json::~Json() {
    delete json;
    json = nullptr;
}

/**
 * @brief Validates JSON content from input stream
 * @param stream Input stream to validate
 * @return Validation result message
 */
std::string Json::validate(std::istream& stream) {
    const std::string content = readStreamContent(stream);

    std::istringstream contentStream(content);
    std::pair<bool, std::string> isValid = JsonValidator::validateJson(contentStream);

    if(isValid.first) {
        return "The json is valid!";
    }

    return isValid.second;
}

/**
 * @brief Prints JSON content to output stream in compact format
 * @param stream Output stream to print to
 */
void Json::print(std::ostream& stream) {
    stream << JsonPrinter::print(json);
}

/**
 * @brief Prints JSON content to output stream in pretty format
 * @param stream Output stream to print to
 */
void Json::prettyPrint(std::ostream& stream) {
    stream << JsonPrinter::prettyPrint(json);
}

/**
 * @brief Searches JSON content using regex pattern
 * @param stream Output stream for search results
 * @param searchRegex Regular expression pattern to search for
 * @throws std::runtime_error if search cannot be performed
 */
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

/**
 * @brief Sets a value at specified path
 * @param path Path to set the value at
 * @param value String representation of value to set
 * @throws std::runtime_error if path is invalid or value is malformed
 */
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

/**
 * @brief Creates a new value at specified path
 * @param path Path to create the value at
 * @param value String representation of value to create
 * @throws std::runtime_error if path exists or value is malformed
 */
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

/**
 * @brief Erases value at specified path
 * @param path Path to the value to erase
 * @throws std::runtime_error if path is invalid
 */
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

/**
 * @brief Moves value from one path to another
 * @param from Source path
 * @param to Destination path
 * @throws std::runtime_error if source path is invalid
 */
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

/**
 * @brief Saves JSON content to output stream
 * @param stream Output stream to save to
 * @param path Optional path to save specific part
 * @throws std::runtime_error if path is invalid
 */
void Json::save(std::ostream& stream, const std::string& path) {
    if(!(Path::validatePath(json, path))) {
        throw std::runtime_error("Cannot perform save on path to non-existing element!");
    }

    JsonSerializer::save(json, stream, path);
}

/**
 * @brief Helper method to read entire stream content
 * @param stream Input stream to read from
 * @return String containing stream content
 */
std::string Json::readStreamContent(std::istream& stream) {
    return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}