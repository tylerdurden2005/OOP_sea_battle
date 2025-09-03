//
// Created by nikita on 19.12.24.
//

#ifndef OOPLABEL1_INPUTFROMTERMINAL_H
#define OOPLABEL1_INPUTFROMTERMINAL_H
#include "Game.h"
enum class CommandType{
    kStartGame,
    kLoadGame,
    kSaveGame,
    kClose,
    kRules,
    kPrintRender,
    kAttack
};
enum class InputSpecialCommand{
    kRenderSP,
};
enum class InvalidType{
    kInvalidAttack,
    kInvalidSave,
    kInvalidLoad
};
enum class OutSpecialCommand{
    kRenderUsField,
    kRenderOpField,
    kRenderUsManager,
    kRenderOpManager
};
class InputFromTerminal{
    std::map <char, CommandType> commands;
    std::string file_name = "commands.txt";
    size_t default_commands_size = 7;
    void DefaultCommands();
    void LoadData();
    bool CheckData();
public:
    InputFromTerminal();
    CommandType GetCommand();
    void KeyDesignations();
    void Rules();
    void InvalidCall(InvalidType type);
    OutSpecialCommand GetSpecialCommand(InputSpecialCommand type);
};
#endif //OOPLABEL1_INPUTFROMTERMINAL_H
