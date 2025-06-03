#include "JsonSerializer.hpp"
#include "Path.hpp"

void JsonSerializer::save(const JsonValue* const json, std::ostream& stream, const std::string& path) {
    const JsonValue* value = Path::getValue(json, path);
    stream << value;
}