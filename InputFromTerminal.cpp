//
// Created by nikita on 19.12.24.
//
#include "InputFromTerminal.h"

void InputFromTerminal::DefaultCommands() {
    commands.clear();
    commands['g'] = CommandType::kStartGame;
    commands['a'] = CommandType::kAttack;
    commands['l'] = CommandType::kLoadGame;
    commands['s'] = CommandType::kSaveGame;
    commands['c'] = CommandType::kClose;
    commands['r'] = CommandType::kRules;
    commands['p'] = CommandType::kPrintRender;
}

void InputFromTerminal::LoadData() {
    std::ifstream file_stream(file_name);
    if (file_stream){
        bool flag_default = false;
        int nums_commands;
        std::string input;
        file_stream >> nums_commands;
        file_stream.ignore();
        char symbol_for_command;
        for (size_t i=0; i<nums_commands; ++i){
            file_stream >> symbol_for_command;
            if (commands.count(symbol_for_command) >=1) { //not_unique key
                flag_default = true;
                break;
            }
            file_stream.ignore();
            std::getline(file_stream, input);
            if (input == "StartNewGame"){
                commands[symbol_for_command] = CommandType::kStartGame;
            }
            else if (input == "LoadGame"){
                commands[symbol_for_command] = CommandType::kLoadGame;
            }
            else if (input == "Attack"){
                commands[symbol_for_command] = CommandType::kAttack;
            }
            else if (input == "End"){
                commands[symbol_for_command] = CommandType::kClose;
            }
            else if (input == "SaveGame"){
                commands[symbol_for_command] = CommandType::kSaveGame;
            }
            else if (input == "Rules"){
                commands[symbol_for_command] = CommandType::kRules;
            }
            else if (input == "Render"){
                commands[symbol_for_command] = CommandType::kPrintRender;
            }
            else{ // unknown command
                flag_default = true;
                break;
            }
        }
        file_stream.close();
        if (!flag_default){ //false
            flag_default = CheckData();
            if (!flag_default) { //false
                return;
            }
        }
    }
    //default
    std::cout << "Error: Unable to read commands from file: \"" << file_name << "\"!\n";
    std::cout << "Use default values.\n";
    DefaultCommands();
}

bool InputFromTerminal::CheckData() {
    if (commands.size() < default_commands_size || commands.size() > default_commands_size) return true;
    std::vector<CommandType> all_types;
    for (auto& i : commands){
        all_types.push_back(i.second);
    }
    bool unique = true;
    for (size_t i=0; i< all_types.size()-1; ++i){
        auto type = all_types[i];
        for (size_t j=i+1; j<all_types.size(); ++j){
            if (all_types[j] == type){
                unique = false;
                break;
            }
        }
        if (!unique) break;
    }
    if (unique) return false; // default = false
    else return true;
}
InputFromTerminal::InputFromTerminal() {
    LoadData();
}

CommandType InputFromTerminal::GetCommand() {
    char command;
    while (true) {
        std::cin >> command;
        std::cin.ignore();
        if (commands.count(command)) {
            return commands[command];
        }
        else {
            std::cout << "You entered an unknown command: ";
            std::cout << command  << "\n";
            std::cout << "Try again: ";
        }
    }
}

OutSpecialCommand InputFromTerminal::GetSpecialCommand(InputSpecialCommand type) {
    if (type == InputSpecialCommand::kRenderSP){
        std::cout << "Enter: \"f1\" to see your field, \"m1\" to see status of your ships, \"f2\" to see opponent field, \"m2 to see status of opponent ships.\n";
        std::string input;
        std::getline(std::cin, input);
        while (input != "f1" && input != "f2" && input != "m1" && input != "m2"){
            std::cout << "You entered an unknown command: ";
            std::cout << input  << "\n";
            std::cin.clear();
            std::cin.sync();
            std::getline(std::cin, input);
        }
        if (input == "f1") return OutSpecialCommand::kRenderUsField;
        else if (input == "f2") return OutSpecialCommand::kRenderOpField;
        else if (input == "m1") return OutSpecialCommand::kRenderUsManager;
        else return OutSpecialCommand::kRenderOpManager;
    }
}

void InputFromTerminal::KeyDesignations() {
    /*std::cout << "\t\tKeys:\n"
                 "\'g\' - start new game\n"
                 "\'l\' - load old game\n"
                 "\'s\' - save game\n"
                 "\'a\' - attack your opponent\n"
                 "\'c\' - close program\n"
                 "\'r\' - show rules\n"
                 "\'p\' - render fields/ships\n";*/
    for (auto& i : commands){
        if (i.second == CommandType::kStartGame){
            std::cout << "\'" << i.first << "\' - start new game\n";
        }
        else if (i.second == CommandType::kAttack){
            std::cout << "\'" << i.first << "\' - attack your opponent\n";
        }
        else if (i.second == CommandType::kSaveGame){
            std::cout << "\'" << i.first << "\' - save game\n";
        }
        else if (i.second == CommandType::kLoadGame){
            std::cout << "\'" << i.first << "\' - load old game\n";
        }
        else if (i.second == CommandType::kRules){
            std::cout << "\'" << i.first << "\' - show rules\n";
        }
        else if (i.second == CommandType::kPrintRender){
            std::cout << "\'" << i.first << "\' - render fields/ships\n";
        }
        else if (i.second == CommandType::kClose){
            std::cout << "\'" << i.first << "\' - close program\n";
        }
    }
}

void InputFromTerminal::InvalidCall(InvalidType type) {
    if (type == InvalidType::kInvalidSave){
        std::cout << "Error: something's wrong with the file or you're trying to save an empty one.\n";
    }
    else if (type == InvalidType::kInvalidAttack){
        std::cout << "Error: there's nothing to attack.\n";
    }
    else{
        std::cout << "Error: something's wrong with the file or you're trying to load an empty one.\n";
    }
}

void InputFromTerminal::Rules() {
    std::cout << "\nWelcome to the game of Sea battle!\n"
                 " This is not exactly the classic version. "
                 "Here you can create a field of any size with any number of ships, use abilities, as well as save the game and load the game. "
                 "Against you will be a ferocious computer, which when you lose can resurrect and continue the game, you have 1 life.\n"
                 "1) In this game each ship's cell has two lives."
                 "2) When it's your turn to play you can attack as in the classic variant or use an available ability. "
                 "There are 3 abilities in the game: "
                 "scanner (scans a 2x2 area),\n"
                 "fire (attacks a random enemy ship),\n"
                 "double damage (attacking a ship does full damage).\n"
                 "Next proceed as follows\n";
}
