#ifndef COMMANDS
#define COMMANDS

#include "Json.hpp"

/**
 * @brief Class that handles JSON file operations and commands
 */
class Commands {
    public:
        /**
         * @brief Default constructor
         */
        Commands() = default;

        /**
         * @brief Deleted copy constructor
         */
        Commands(const Commands& cmds) = delete;

        /**
         * @brief Deleted assignment operator
         */
        Commands& operator=(const Commands& cmds) = delete;

        /**
         * @brief Destructor
         */
        ~Commands();

        /**
         * @brief Opens a JSON file
         * @param filename Name of the file to open
         */
        void open(const std::string& filename);

        /**
         * @brief Closes the currently opened file
         */
        void close();

        /**
         * @brief Saves the current JSON content
         * @param path Optional path to save specific part of JSON
         */
        void save(const std::string& path);

        /**
         * @brief Saves the JSON content to a new file
         * @param filename Name of the new file
         * @param path Optional path to save specific part of JSON
         */
        void saveAs(const std::string& filename, const std::string& path);

        /**
         * @brief Displays help information
         */
        void help();
        
        /**
         * @brief Prints the JSON content
         */
        void print();

        /**
         * @brief Prints the JSON content in a formatted way
         */
        void prettyPrint();

        /**
         * @brief Searches for a key in the JSON
         * @param key The key to search for
         */
        void search(const std::string& key);

        /**
         * @brief Sets a value at a specific path
         * @param path The path where to set the value
         * @param string The value to set
         */
        void set(const std::string& path, const std::string& string);

        /**
         * @brief Creates a new value at a specific path
         * @param path The path where to create the value
         * @param string The value to create
         */
        void create(const std::string& path, const std::string& string);

        /**
         * @brief Erases a value at a specific path
         * @param path The path to the value to erase
         */
        void erase(const std::string& path);

        /**
         * @brief Moves a value from one path to another
         * @param from Source path
         * @param to Destination path
         */
        void move(const std::string& from, const std::string& to);

    private:
        /**
         * @brief Name of the currently opened file
         */
        std::string fileName;

        /**
         * @brief Pointer to the JSON object
         */
        Json* json = nullptr;

        /**
         * @brief Helper function to delete JSON payload
         */
        void deltePayload();
};

#endif