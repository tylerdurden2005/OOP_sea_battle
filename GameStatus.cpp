#include "File.h"
#include "GameStatus.h"
void GameStatus::Clear() {
    delete user_field;
    delete opponent_field;
    delete user_manager;
    delete opponent_manager;
    delete user_abilities;
    user_cells_for_attack.clear();
    user_ships_coords.clear();
    opponent_ships_coords.clear();
}
void GameStatus::ClearOpponent() {
    delete opponent_field;
    delete opponent_manager;
}
GameStatus::~GameStatus() {
    Clear();
}
void GameStatus::Save() {
    try{
        File file(file_name, std::ios::out);
        file << *this;
    }
    catch (ProgramErrors& e){
        throw ProgramErrors(e.what());
    }
}
void GameStatus::Load() {
    try {
        File file(file_name, std::ios::in);
        file >> *this;
    }
    catch (ProgramErrors& e){
        throw ProgramErrors(e.what());
    }
}

GamingField *GameStatus::GetUserField() {
    return user_field;
}
GamingField *GameStatus::GetOpponentField(){
    return opponent_field;
}
Manager* GameStatus::GetOpponentManager() {
    return opponent_manager;
}

Manager *GameStatus::GetUserManager() {
    return  user_manager;
}