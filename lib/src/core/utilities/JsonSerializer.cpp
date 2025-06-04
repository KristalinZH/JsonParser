#include "JsonSerializer.hpp"
#include "Path.hpp"

/**
 * @brief Saves a JSON value to an output stream
 * @param json Pointer to the constant JSON value to save
 * @param stream Output stream to write to
 * @param path Optional path within the JSON to save specific part
 */
void JsonSerializer::save(const JsonValue* const json, std::ostream& stream, const std::string& path) {
    const JsonValue* value = Path::getValue(json, path);
    stream << value;
}