#include <iostream>
#include <fstream>
#include <sstream>
#include "Commands.hpp"

Commands::~Commands() {
    if(json != nullptr) {
        delete json;
        json = nullptr;
    }
}

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

void Commands::print() {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    json->print(std::cout);
}

void Commands::prettyPrint() {
    if(fileName == "") {
        std::cout<<"File must be opened!\n";
        return;
    }

    json->prettyPrint(std::cout);
}

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