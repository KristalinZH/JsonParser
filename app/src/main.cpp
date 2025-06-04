#include <iostream>
#include <cstdlib>
#include "Commands.hpp"

/**
 * @brief Represents available commands in the JSON parser application
 */
enum class Command {
    Unknown,
    Open,
    Close,
    Help,
    Print,
    PrettyPrint,
    Search,
    Set,
    Create,
    Delete,
    Move,
    Save,
    SaveAs,
    Clear,
    Exit
};

/**
 * @brief Splits an input string into a vector of arguments
 * @param input The input string to split
 * @return Vector of string arguments
 */
std::vector<std::string> splitLine(const std::string& input) {
    std::vector<std::string> args;
    std::istringstream stream(input);
    std::string arg;
    
    while (stream >> arg) {
        args.push_back(arg);
    }
    
    return args;
}

/**
 * @brief Clears the console screen
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Converts a string command to the corresponding Command enum value
 * @param cmd String command to convert
 * @return Command enum value corresponding to the input string
 */
Command getCommand(const std::string& cmd) {
    std::string lowerCmd = cmd;
    std::transform(lowerCmd.begin(), lowerCmd.end(), lowerCmd.begin(), [](unsigned char c){ return std::tolower(c);});

    if (lowerCmd == "open") return Command::Open;
    if (lowerCmd == "close") return Command::Close;
    if (lowerCmd == "help") return Command::Help;
    if (lowerCmd == "print") return Command::Print;
    if (lowerCmd == "pretty-print") return Command::PrettyPrint;
    if (lowerCmd == "search") return Command::Search;
    if (lowerCmd == "set") return Command::Set;
    if (lowerCmd == "create") return Command::Create;
    if (lowerCmd == "delete") return Command::Delete;
    if (lowerCmd == "move") return Command::Move;
    if (lowerCmd == "save") return Command::Save;
    if (lowerCmd == "saveas") return Command::SaveAs;
    if (lowerCmd == "clear") return Command::Clear;
    if (lowerCmd == "exit") return Command::Exit;
    return Command::Unknown;
}

/**
 * @brief Executes the given command with provided arguments
 * @param cmds Reference to Commands object that handles JSON operations
 * @param args Vector of command arguments
 * @param shouldExecute Reference to boolean controlling program execution
 */
void performCommand(Commands& cmds, const std::vector<std::string>& args, bool& shouldExecute) {
    Command cmd = getCommand(args[0]);

    switch (cmd)
    {
        case Command::Open : {
            if(args.size() != 2) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.open(args[1]);
            break;
        }
        case Command::Close : {
            if(args.size() != 1) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.close();
            break;
        }
        case Command::Help : {
            if(args.size() != 1) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.help();
            break;
        }
        case Command::Print : {
            if(args.size() != 1) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.print();
            break;
        }
        case Command::PrettyPrint : {
            if(args.size() != 1) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.prettyPrint();
            break;
        }
        case Command::Search : {
            if(args.size() != 2) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.search(args[1]);
            break;
        }
        case Command::Set : {
            if(args.size() != 3) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.set(args[1], args[2]);
            break;
        }
        case Command::Create: {
            if(args.size() != 3) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.create(args[1], args[2]);
            break;
        }
        case Command::Delete : {
            if(args.size() != 2) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.erase(args[1]);
            break;
        }
        case Command::Move : {
            if(args.size() != 3) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            cmds.move(args[1], args[2]);
            break;
        }
        case Command::Save : {
            if(args.size() != 1 && args.size()!=2) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            std::string path = "";
            if(args.size()==2) {
                path = args[1];
            }

            cmds.save(path);
            break;
        }
        case Command::SaveAs : {
            if(args.size() != 2 && args.size()!=3) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            std::string path = "";
            if(args.size()==3) {
                path = args[2];
            }

            cmds.saveAs(args[1], path);
            break;
        }
        case Command::Clear : {
            if(args.size() != 1) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            clearScreen();
            break;
        }
        case Command::Exit: {
            if(args.size() != 1) {
                std::cout<<"Invalid number of arguments!\n";
                break;
            }

            shouldExecute = false;
            std::cout<<"Successfully exited the program!\n";
            break;
        }
        default: {
            std::cout<<"Invalid command "<<args[0]<<"!\n";
            break;
        }
    }
}

/**
 * @brief Main entry point of the JSON parser application
 * @return Exit status code
 */
int main(){
    Commands cmds;
    bool shouldExecute = true;
    cmds.help();
    std::string line;

    while(shouldExecute) {
        std::cout<<"Please enter command: ";
        getline(std::cin, line);

        if(line == ""){
            std::cout<<"Please enter command\n";
            continue;
        }

        std::vector<std::string> args = splitLine(line);

        performCommand(cmds, args, shouldExecute);
    }

    return 0;
}

