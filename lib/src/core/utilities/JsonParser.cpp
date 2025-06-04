#include "JsonParser.hpp"
#include "JsonFactory.hpp"

/**
 * @brief Parses a JSON null value from input stream
 * @param stream Input stream to parse from
 * @return String "null"
 */
std::string JsonParser::parseNull(std::istream& stream){
    char symbol = '\0';
    size_t counter = 1;
    
    while(stream >> symbol){
        counter++;

        if(counter == 4){
            break;
        }
    }

    return "null";

}

/**
 * @brief Parses a JSON boolean value from input stream
 * @param stream Input stream to parse from
 * @param lastSymbol Last character read ('t' or 'f')
 * @return String "true" or "false"
 */
std::string JsonParser::parseBoolean(std::istream& stream, const char lastSymbol) {

    char symbol = '\0';
    size_t counter = 1;
    
    const size_t maxReadSymbols = lastSymbol == 't' ? 4 : 5;

    while(stream >> symbol){
        counter++;

        if(counter == maxReadSymbols){
            break;
        }
    }

    return maxReadSymbols == 4 ? "true" : "false";
}

/**
 * @brief Parses a JSON number value from input stream
 * @param stream Input stream to parse from
 * @param lastSymbol Last character read (digit or minus)
 * @return String representation of the number
 */
std::string JsonParser::parseNumber(std::istream& stream, const char lastSymbol) {
    std::string value(1, lastSymbol);
    char symbol = '\0';
    while(stream >> symbol){

        if(isspace(symbol) || symbol == ',' || symbol == '}' || symbol == ']'){
            stream.seekg(-1, std::ios::cur);
            break;
        }

        value.append(1, symbol);
    }

    return value;
}

/**
 * @brief Parses a JSON string value from input stream
 * @param stream Input stream to parse from
 * @param lastSymbol Last character read (quote)
 * @return Parsed string including quotes
 */
std::string JsonParser::parseString(std::istream& stream, const char lastSymbol) {
    std::string value(1, lastSymbol);
    char symbol = '\0';

    while(stream.get(symbol)){
        if(symbol == '\"' && value[value.length() - 1] != '\\'){
            value.append(1, symbol);
            break;
        }

        value.append(1, symbol);
    }

    return value;
}

/**
 * @brief Parses a primary JSON value (null, boolean, number, or string)
 * @param stream Input stream to parse from
 * @param lastSymbol Last character read
 * @return Pointer to created JsonValue
 */
JsonValue* JsonParser::parsePrimary(std::istream& stream, const char lastSymbol) {

    std::string value = "";

    switch (lastSymbol)
    {
        case 'n' : {
            value = parseNull(stream);
            break;
        }
        case 't' :
        case 'f' : {
            value = parseBoolean(stream, lastSymbol);
            break;
        }
        case '\"' : {
            value = parseString(stream, lastSymbol);
            break;
        }
        default : {
            value = parseNumber(stream, lastSymbol);
            break;
        }
    }

    return JsonFactory::create(value);
}

/**
 * @brief Parses a JSON array or object
 * @param stream Input stream to parse from
 * @param lastBrace Opening brace/bracket character
 * @return Pointer to created JsonValue (array or object)
 */
JsonValue* JsonParser::parseJson(std::istream& stream, const char lastBrace) {

    char symbol = '\0';

    if(lastBrace != '[' && lastBrace != '{') {
        return parsePrimary(stream, lastBrace);    
    }

    if(lastBrace == '[') {
        std::vector<JsonValue*> arrayValues;

        while(stream >> symbol) {
            if(symbol == ']')
                break;
            
            if(symbol == ',') {
                continue;
            }

            JsonValue* value = nullptr;

            if(symbol == '[' || symbol == '{'){
                value = parseJson(stream, symbol);
            } else {
                value = parsePrimary(stream, symbol);
            }

            arrayValues.push_back(value);
        }

        JsonValue* value = JsonFactory::create(arrayValues);

        for(JsonValue* arrayValue : arrayValues)
            delete arrayValue;

        return value;
    }


    std::list<std::string> objectKeys;
    std::unordered_map<std::string, JsonValue*> objectValues;

    while(stream >> symbol) {

        if(symbol == '}')
            break;

        if(symbol == ',') {
            continue;
        }

        std::string key = parseString(stream, symbol);
        key = key.substr(1, key.length()-2);
        objectKeys.push_back(key);

        stream >> symbol;

        stream >> symbol;

        JsonValue* value = nullptr;

        if(symbol == '[' || symbol == '{'){
            value = parseJson(stream, symbol);
        } else {
            value = parsePrimary(stream, symbol);
        }

        objectValues.emplace(key, value);
    }

    JsonValue* value = JsonFactory::create(objectKeys, objectValues);
    
    for(auto& kvp : objectValues)
        delete kvp.second;
    
    return value;
    
}

/**
 * @brief Main entry point for parsing JSON from input stream
 * @param stream Input stream containing JSON data
 * @return Pointer to parsed JsonValue
 */
JsonValue* JsonParser::parse(std::istream& stream) {
    char symbol = '\0';

    stream >> symbol;

    return parseJson(stream, symbol);
}