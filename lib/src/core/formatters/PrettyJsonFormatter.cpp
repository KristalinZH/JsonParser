#include <sstream>
#include "formatters/PrettyJsonFormatter.hpp"

std::string PrettyJsonFormatter::format(const JsonArray& value, const size_t indent) const {
    const size_t size = value.getSize();

    if(size == 0)
        return std::string("[]");

    std::ostringstream output;

    output << "[\n";

    for(size_t i = 0; i < size - 1; i++){
        writeIndentationIntoStream(output, indent + 1);
        writeJsonIntoStream(output, value[i], indent + 1);
        output << ",\n";
    }

    writeIndentationIntoStream(output, indent + 1);
    writeJsonIntoStream(output, value[size - 1], indent + 1);
    output << '\n';

    writeIndentationIntoStream(output, indent);
    output << "]";
    if(indent == 0)
        output << '\n';

    return output.str();
}

std::string PrettyJsonFormatter::format(const JsonObject& value, const size_t indent) const {
    const size_t size = value.getSize();

    if(size == 0)
        return std::string("{}");

    std::ostringstream output;

    output << "{\n";

    std::vector<std::string> keys = value.getKeys();

    for(size_t i = 0; i < size - 1; i++){
        writeIndentationIntoStream(output, indent + 1);
        output << '\"' << keys[i] << '\"' <<  " : ";
        writeJsonIntoStream(output, value.getValue(keys[i]), indent + 1);
        output << ",\n";
    }

    writeIndentationIntoStream(output, indent + 1);
    output << '\"' << keys[size - 1] << '\"' << " : ";
    writeJsonIntoStream(output, value.getValue(keys[size - 1]), indent + 1);
    output << "\n";

    writeIndentationIntoStream(output, indent);
    output << "}";

    if(indent == 0)
        output << '\n';

    return output.str();
}

void PrettyJsonFormatter::writeJsonIntoStream(std::ostream& os, const JsonValue& value, const size_t indent) const {

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
            os << format(value.getAValue(), indent);
            break;
        }

        case ValueType::Object : {
            os << format(value.getOValue(), indent);
            break;
        }

        default: {
            throw std::runtime_error("Invalid value type in CompactJsonFormatter!");
        }

    }
}

void PrettyJsonFormatter::writeIndentationIntoStream(std::ostream& os, const size_t indent) const {
    for(size_t i = 0; i < indent * 2; i++){
        os << ' ';
    }
}