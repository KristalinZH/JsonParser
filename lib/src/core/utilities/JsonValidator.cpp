#include <regex>
#include "JsonValidator.hpp"

std::pair<bool, std::string> JsonValidator::validateNull(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition){
    std::string value(1, lastSymbol);
    char symbol = '\0';
    size_t counter = 1;
    
    while(stream.get(symbol)){
        counter++;
        value.append(1, symbol);

        if(counter == 4){
            break;
        }
    }

    if(!std::regex_match(value, std::regex("^null$"))){
        const std::string errorMessage = "Invalid null value!\nGot " + value + 
        " instead of null on row " + std::to_string(row)+" between positions " +
        std::to_string(lastRowPosition) + " and " + std::to_string(lastRowPosition + counter -1) + ".\n";
        return std::make_pair(false, errorMessage);
    }


    lastRowPosition += counter - 1;

    return  std::make_pair(true, value);

}

std::pair<bool, std::string> JsonValidator::validateBoolean(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition){
    std::string value(1, lastSymbol);
    char symbol = '\0';
    size_t counter = 1;
    
    const size_t maxReadSymbols = lastSymbol == 't' ? 4 : 5;

    while(stream.get(symbol)){
        counter++;
        value.append(1, symbol);

        if(counter == maxReadSymbols){
            break;
        }
    }

    if(!std::regex_match(value, std::regex("^(true|false)$"))){
        const std::string errorMessage = "Invalid boolean value!\nGot " + value + 
        " instead of true or false on row " + std::to_string(row)+" between positions " +
        std::to_string(lastRowPosition) + " and " + std::to_string(lastRowPosition + counter -1) + ".\n";

        return std::make_pair(false, errorMessage);
    }


    lastRowPosition += counter - 1;

    return  std::make_pair(true, value);

}

std::pair<bool, std::string> JsonValidator::validateNumber(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition){

    std::string value(1, lastSymbol);
    char symbol = '\0';
    size_t counter = 1;

    while(stream.get(symbol)){
        counter++;

        if(isspace(symbol) || symbol == ',' || symbol == '}' || symbol == ']'){
            stream.seekg(-1, std::ios::cur);
            counter--;
            break;
        }

        value.append(1, symbol);
    }

    if(!std::regex_match(value, std::regex(R"(^-?(0|[1-9]\d*)(\.\d+)?([eE][+-]?\d+)?$)"))){

        const std::string errorMessage = "Invalid number value!\nGot this: " + value +
        " instead of valid number on row " + std::to_string(row)+" between positions " + std::to_string(lastRowPosition) + 
        " and " + std::to_string(lastRowPosition + counter -1) + ".\n";

        return std::make_pair(false, errorMessage);
    }

    lastRowPosition += counter - 1;

    return std::make_pair(true, value);
}

std::pair<bool, std::string> JsonValidator::validateString(std::istream& stream, const char lastSymbol, const size_t row, size_t& lastRowPosition){

    std::string value(1, lastSymbol);
    char symbol = '\0';
    size_t counter = 1;
    bool isRevSolidusRead = false;

    while(stream.get(symbol)){
        counter++;

        if(symbol == '\\'){
            if(isRevSolidusRead && value[value.length() - 1] != '\\'){
                const std::string errorMessage = "Invalid string value!\nGot unescaped \\ in this: " + value +
                " on row " + std::to_string(row)+" between positions " + std::to_string(lastRowPosition) + 
                " and " + std::to_string(lastRowPosition + counter -1) + ".\n";

                return std::make_pair(false, errorMessage);
            }

            isRevSolidusRead = true;
        }

        else if(iscntrl(symbol)){

            if(value[value.length() - 1] != '\\'){
                const std::string errorMessage = "Invalid string value!\nGot control character or \\ in this: " + value +
                " on row " + std::to_string(row)+" between positions " + std::to_string(lastRowPosition) + 
                " and " + std::to_string(lastRowPosition + counter -1) + ".\n";

                return std::make_pair(false, errorMessage);
            }

            isRevSolidusRead = false;
        }

        else if(symbol == '\"' && value[value.length() - 1] != '\\'){
            value.append(1, symbol);
            break;
        }

        isRevSolidusRead = false;
        value.append(1, symbol);
    }

    if(value.length() < 2 || value[value.length() - 1] != '\"'){

        const std::string errorMessage = "Invalid string value!\nGot unclosed string value: " + value +
        " on row " + std::to_string(row)+" between positions " + std::to_string(lastRowPosition) + 
        " and " + std::to_string(lastRowPosition + counter -1) + ".\n";

        return std::make_pair(false, errorMessage);
    }

    lastRowPosition += counter - 1;

    return std::make_pair(true, value);
}

std::pair<bool, std::string> JsonValidator::validatePrimary(std::istream& stream, const char symbol, const size_t row, size_t& position, size_t& stateOfReading, const ReadingMode& mode, bool& isCommaFound, std::unordered_set<std::string>& objectKeys){
    size_t stateModeCase = stateOfReading;
    
    switch (mode)
    {
        case ReadingMode::ReadingArray:{
            stateModeCase = stateOfReading == 0 ? 2 : 3;
            break;
        }
        case ReadingMode::ReadingPrimary:{
            stateModeCase = 2;
            break;
        }
        default:
            break;
    }

    switch(stateModeCase){
        case 0:{
            isCommaFound = false;
            stateOfReading++;

            if(symbol != '\"'){
                const std::string errorMessage = "Invalid key found on row " + std::to_string(row)+" on position " 
                + std::to_string(position - 1) + ".\n";

                return std::make_pair(false, errorMessage);
            }

            const std::pair<bool, std::string> result = validateString(stream, symbol, row, position);
            if(!result.first){
                return result;
            }

            if(objectKeys.find(result.second) != objectKeys.end()){
                const std::string errorMessage = "Dublicate keys in same object found. The dublicate key: " + result.second + " is on row " + std::to_string(row)+" on position " 
                + std::to_string(position) + ".\n";

                return std::make_pair(false, errorMessage);
            }   

            objectKeys.insert(result.second);

            return std::make_pair(true, "It is valid!\n");
        }
        case 1:{
            stateOfReading++;

            if(symbol != ':'){
                const std::string errorMessage = "Key value pair separator ':' not found on row " + std::to_string(row)+" on position " 
                + std::to_string(position - 1) + ".\n";

                return std::make_pair(false, errorMessage);
            }

            return std::make_pair(true, "It is valid!\n"); 
        }
        case 2:{
            if(mode != ReadingMode::ReadingPrimary){
                stateOfReading++;
                isCommaFound = false;
            }

            if(!isdigit(symbol) && symbol != 'n' && symbol != 't' && symbol != 'f' && symbol != '-' && symbol != '\"'){
                const std::string errorMessage = "Invalid json value found on row " + std::to_string(row)+" starting on position " 
                + std::to_string(position - 1) + ".\n";

                return std::make_pair(false, errorMessage);
            }

            std::pair<bool, std::string> result;

            switch (symbol)
            {
                case 'n':{
                    result = validateNull(stream, symbol, row, position);
                    break;
                }
                case 't':
                case 'f':{
                    result = validateBoolean(stream, symbol, row, position);
                    break;
                }
                case '-':{
                    result = validateNumber(stream, symbol, row, position);
                    break;
                }
                case '\"':{
                    result = validateString(stream, symbol, row, position);
                    break;
                }
                default:{
                    if(!isdigit(symbol)){
                        const std::string errorMessage = "Invalid json value found on row " + std::to_string(row)+" starting on position " 
                        + std::to_string(position - 1) + ".\n";

                        return std::make_pair(false, errorMessage);
                    }

                    result = validateNumber(stream, symbol, row, position);

                    break;
                }
            }
            
            return result;
        }
        default:{
            if(symbol != ','){
                const std::string errorMessage = "Missing ',' on row " + std::to_string(row)+" before position " 
                + std::to_string(position - 1) + ".\n";

                return std::make_pair(false, errorMessage);
            }

            isCommaFound = true;
            stateOfReading = 0;

            return std::make_pair(true, "It is valid!\n");
        }

    }
}

std::pair<bool, std::string> JsonValidator::validate(std::istream& stream, size_t& row, size_t& position, char lastBrace, const ReadingMode& mode){

    std::unordered_set<std::string> objectKeys;

    char symbol = '\0';
    bool isClosingBrackedFound = false;
    bool isCommaFound = false;
    size_t stateOfReading = 0;

    while(stream.get(symbol)){

        position++;

        switch(symbol){
            case '\n':{
                row++;
                position = 0;
                break;
            }
            case '{':
            case '[':{

                ReadingMode newMode = symbol == '{' ? ReadingMode::ReadingObject : ReadingMode::ReadingArray;

                const std::pair<bool, std::string> result = validate(stream, row, position, symbol, newMode);

                if(!result.first){
                    return result;
                }

                isCommaFound = false;

                stateOfReading++;

                break;
            }
            case '}':
            case ']':{
                if(isCommaFound && mode != ReadingMode::ReadingPrimary){
                    const std::string errorMessage = "Additional comma found on row " + std::to_string(row)+" on position " 
                    + std::to_string(position) + ".\n";

                    return std::make_pair(false, errorMessage);
                }

                isClosingBrackedFound = true;
                break;
            }
            default:{
                if(isspace(symbol)){
                    break;
                }

                const std::pair<bool, std::string> result = validatePrimary(stream, symbol, row, position, stateOfReading, mode, isCommaFound, objectKeys);

                if(!result.first){
                    return result;
                }

                break;
            }
        }

        if(symbol == '}' || symbol == ']')
            break;
    }

    if(mode != ReadingMode::ReadingPrimary && !isClosingBrackedFound){

        const std::string errorMessage = "Missing closing bracket on row " + std::to_string(row)+" on position " 
        + std::to_string(position - 1) + ".\n";

        return std::make_pair(false, errorMessage);
    }

    if(mode == ReadingMode::ReadingPrimary && isClosingBrackedFound){
         const std::string errorMessage = "Additional closing bracket on row " + std::to_string(row)+" on position " 
        + std::to_string(position - 1) + ".\n";

        return std::make_pair(false, errorMessage);
    }

    if(mode != ReadingMode::ReadingPrimary && symbol - lastBrace != 2){
        const std::string errorMessage = "Mismatching closing bracket on row " + std::to_string(row)+" on position " 
        + std::to_string(position - 1) + ".\n";

        return std::make_pair(false, errorMessage);
    }

    return std::make_pair(true, "It is valid Json!\n");

}

std::pair<bool, std::string> JsonValidator::validateJson(std::istream& stream){
    size_t row = 1, position = 1;
    std::pair<bool, std::string> validationResult = validate(stream, row, position);
    return validationResult;
}