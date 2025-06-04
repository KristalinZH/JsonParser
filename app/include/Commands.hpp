#ifndef COMMANDS
#define COMMANDS

#include "Json.hpp"

class Commands {
    public:
        Commands() = default;
        Commands(const Commands& cmds) = delete;
        Commands& operator=(const Commands& cmds) = delete;
        ~Commands();

        void open(const std::string& filename);
        void close();
        void save(const std::string& path);
        void saveAs(const std::string& filename, const std::string& path);
        void help();
        
        void print();
        void prettyPrint();
        void search(const std::string& key);
        void set(const std::string& path, const std::string& string);
        void create(const std::string& path, const std::string& string);
        void erase(const std::string& path);
        void move(const std::string& from, const std::string& to);

    private:
        std::string fileName;
        Json* json = nullptr;

        void deltePayload();
};

#endif