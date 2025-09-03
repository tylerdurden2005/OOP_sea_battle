#ifndef OOPLABEL1_GAMESTATUS_H
#define OOPLABEL1_GAMESTATUS_H
#include "Manager.h"
#include "GamingField.h"
#include "AbilitiesManager.h"
#include "File.h"
class GameStatus{
    GamingField* user_field = nullptr;
    GamingField* opponent_field = nullptr;
    Manager* user_manager = nullptr;
    Manager* opponent_manager = nullptr;
    AbilitiesManager* user_abilities = nullptr;
    std::vector<Coordinates> user_cells_for_attack;
    size_t alive_user_ships;
    size_t alive_opponent_ships;
    std::vector<Coordinates> user_ships_coords;
    std::vector<Coordinates> opponent_ships_coords;
    std::string file_name = "Save.txt";
    friend class Game;
    friend class File;
public:
    void Save();
    void Load();
    void Clear();
    GamingField* GetUserField();
    GamingField* GetOpponentField();
    Manager* GetUserManager();
    Manager* GetOpponentManager();
    size_t GetAliveUsShips(){
        return alive_user_ships;
    }
    size_t GetAliveOpShips(){
        return alive_opponent_ships;
    }
    void ClearOpponent();
    ~GameStatus();
};

#endif //OOPLABEL1_GAMESTATUS_H
