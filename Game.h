
#ifndef OOPLABEL1_GAME_H
#define OOPLABEL1_GAME_H
#include "File.h"
#include "GameStatus.h"
enum class AgeOpponent{
    kNewOpponent,
    kRestartOpponent
};
enum class TypeGenerateCoordinates{
    kRotateStraightAngle,
    kRotateRightAngle,
    kInvertY,
    kInvertX
};
enum class ResultOfRound{
    kUserWin,
    kUserLose,
    kContinueGame,
};
enum class TypeOfGame{
    kEmptyGame,
    kGamePlaying
};

class Game{
    GameStatus game_status;
    void CheckValue(int& value);
    void GenerateOpponentsCoord(std::vector<Coordinates>& ships_coord, TypeGenerateCoordinates flag);
    void CreateUser();
    void CreateOpponent(AgeOpponent flag);
    //void Rounds(TypeOfGame flag = TypeOfGame::kNewGame);
    //ResultOfRound NewRound();
    void VictoryText();
    void GameOverText();
public:
    void OpponentTurn();
    void NextOpponent(){
        game_status.opponent_ships_coords = game_status.user_ships_coords;
        game_status.ClearOpponent();
        CreateOpponent(AgeOpponent::kRestartOpponent);
    }
    void GameStatusFree(){
        game_status.Clear();
    }
    GameStatus& GetGameStatus(){
        return game_status;
    }
    void UserTurn();
    void StartNewGame();
    void LoadGame();
    void SaveGame();
    //void Finish();
};
#endif //OOPLABEL1_GAME_H
