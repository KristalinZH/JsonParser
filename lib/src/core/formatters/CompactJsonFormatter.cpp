#include <sstream>
#include "formatters/CompactJsonFormatter.hpp"

std::string CompactJsonFormatter::format(const JsonArray& value, const size_t indent) const {
    const size_t size = value.getSize();

    if(size == 0)
        return std::string("[]");

    std::ostringstream output;

    output << '[';

    for(size_t i = 0; i < size - 1; i++){
        writeJsonIntoStream(output, value[i]);
        output << ',';
    }

    writeJsonIntoStream(output, value[size - 1]);

    output << ']';

    return output.str();
}

std::string CompactJsonFormatter::format(const JsonObject& value, const size_t indent) const {
    const size_t size = value.getSize();

    if(size == 0)
        return std::string("{}");

    std::ostringstream output;

    output << '{';

    std::vector<std::string> keys = value.getKeys();

    for(size_t i = 0; i < size - 1; i++){
        output << '\"' << keys[i] << '\"' << ':';
        writeJsonIntoStream(output, value.getValue(keys[i]));
        output << ',';
    }

    output << '\"' << keys[size - 1] << '\"' << ':';
    writeJsonIntoStream(output, value.getValue(keys[size - 1]));
    output << '}';

    return output.str();
}

void CompactJsonFormatter::writeJsonIntoStream(std::ostream& os, const JsonValue& value, const size_t indent) const {

    switch(value.getType()) {

        case ValueType::Null :
        case ValueType::Boolean :
        case ValueType::Int :
        case ValueType::Double : 
        case ValueType::String : {
            os << value;
            break;
        }

        case ValueType::Array : {
            os << format(value.getAValue());
            break;
        }

        case ValueType::Object : {
            os << format(value.getOValue());
            break;
        }

        default: {
            throw std::runtime_error("Invalid value type in CompactJsonFormatter!");
        }

    }
}