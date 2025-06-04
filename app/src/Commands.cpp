#include <iostream>
#include <fstream>
#include <sstream>
#include "Commands.hpp"

/**
 * @brief Destructor for Commands class, cleans up json pointer
 */
Commands::~Commands() {
    if(json != nullptr) {
        delete json;
        json = nullptr;
    }
}

/**
 * @brief Opens a JSON file for processing
 * @param filename Path to the file to be opened
 */
void Commands::open(const std::string& filename) {

    if(fileName != "") {
        std::cout<<"File is already opened!\n";
    }

    std::ifstream inputStream(filename, std::ios::in);

    if(!inputStream.is_open()) {
        std::ofstream outputStream(filename, std::ios::out);

        outputStream << "{}";

        std::cout<<"There is no file " <<filename<<".\nSuccessfully created "<< filename<<'\n';

        inputStream.close();
        return;
    }

    try {
        json = new Json(inputStream);
        fileName = filename;
        std::cout<<"Successfully opened file " << filename << "!\n";
    }catch(std::runtime_error err) {
        if(json != nullptr) {
            delete json;
            json = nullptr;
        }
        std::cout<<err.what()<<'\n';
    }

    inputStream.close();
}

/**
 * @brief Closes the currently opened JSON file
 */
void Commands::close() {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    delete json;
    json = nullptr;
    std::cout<<"Successfuly closed file "<<fileName <<"!\n";
    fileName = "";

}

/**
 * @brief Saves changes to the currently opened file
 * @param path Optional path within JSON to save specific part
 */
void Commands::save(const std::string& path) {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    try {
        std::ostringstream outputStream;

        json->save(outputStream, path);

        std::ofstream fileStream(fileName, std::ios::trunc);

        fileStream << outputStream.str();

        fileStream.close();

        std::cout<<"Successfuly saved changes in file "<<fileName <<"!\n";
    }catch(std::runtime_error err) {
        std::cout<<err.what()<<'\n';
    }
}

/**
 * @brief Saves JSON content to a new file
 * @param filename Name of the new file
 * @param path Optional path within JSON to save specific part
 */
void Commands::saveAs(const std::string& filename, const std::string& path) {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    try {
        std::ofstream fileStream(filename, std::ios::out);

        if(!fileStream.is_open()) {
            std::cout<<"Couldn't open file "<<filename <<"!\n";
            return;
        }

        std::ostringstream outputStream;

        json->save(outputStream, path);

        fileStream << outputStream.str();

        fileStream.close();

        std::cout<<"Successfuly saved another file "<<fileName <<"!\n";
    }catch(std::runtime_error err) {
        std::cout<<err.what()<<'\n';
    }
}

/**
 * @brief Displays help information with available commands
 */
void Commands::help() {
    const std::string options = 
    "The following commands are supported:\n"
    "open <file>                opens file\n"
    "close                      closes currently opened file\n"
    "help                       prints list with available commands\n"
    "print                      prints current json\n"
    "pretty-print               prints prettified current json\n"
    "search <key>               prints list with data under this key or similiar to it\n"
    "set <path> <string>        sets json on path\n"
    "create <path> <string>	    creates json on path\n"
    "delete <path>              deltes json on path\n"
    "move <from> <to>           moves json from one path to another\n"
    "save [<path>]              save json from path or the whole json if path is not provided in currently opened file\n"
    "saveas <file> [<path>]     save json from path or the whole json if path is not provided in file\n"
    "clear                      clears previous messages on screen\n"
    "exit                       terminates the program\n";

    std::cout<<options;
}

/**
 * @brief Prints the current JSON content
 */
void Commands::print() {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    json->print(std::cout);
}

/**
 * @brief Prints the current JSON content in a formatted way
 */
void Commands::prettyPrint() {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    json->prettyPrint(std::cout);
}

/**
 * @brief Searches for a specific key in the JSON
 * @param key The key to search for
 */
void Commands::search(const std::string& key) {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    try {
        json->search(std::cout, key);
    }catch(std::runtime_error err) {
        std::cout<<err.what()<<'\n';
    }
}

/**
 * @brief Sets a value at a specific path in the JSON
 * @param path The path where to set the value
 * @param string The value to set
 */
void Commands::set(const std::string& path, const std::string& string) {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    try {
        json->set(path, string);
        std::cout<<"Successfuly set new json on path " << path<<"!\n";
    }catch(std::runtime_error err) {
        std::cout<<err.what()<<'\n';
    }
}

/**
 * @brief Creates a new value at a specific path in the JSON
 * @param path The path where to create the value
 * @param string The value to create
 */
void Commands::create(const std::string& path, const std::string& string) {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    try {
        json->create(path, string);
        std::cout<<"Successfuly created json on path " << path<<"!\n";
    }catch(std::runtime_error err) {
        std::cout<<err.what()<<'\n';
    }
}

/**
 * @brief Erases a value at a specific path in the JSON
 * @param path The path to the value to erase
 */
void Commands::erase(const std::string& path) {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    try {
        json->erase(path);
        std::cout<<"Successfuly deleted json on path " <<"!\n";
    }catch(std::runtime_error err) {
        std::cout<<err.what()<<'\n';
    }
}

/**
 * @brief Moves a value from one path to another in the JSON
 * @param from Source path
 * @param to Destination path
 */
void Commands::move(const std::string& from, const std::string& to) {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    try {
        json->move(from,to);
        std::cout<<"Successfuly moved json from path "<<from<<" to path " << to <<"!\n";
    }catch(std::runtime_error err) {
        std::cout<<err.what()<<'\n';
    }
}