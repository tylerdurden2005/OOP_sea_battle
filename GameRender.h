//
// Created by nikita on 19.12.24.
//

#ifndef OOPLABEL1_GAMERENDER_H
#define OOPLABEL1_GAMERENDER_H
#include "InputFromTerminal.h"
enum class RenderObjectType{
    kUserField,
    kOpponentField,
    kUserManager,
    kOpponentManager
};
template <typename RenderType>
class GameRender{
    RenderType render;
    GameStatus& game_status;
public:
    GameRender(GameStatus& game_status) : game_status(game_status){}
    void RenderingBasic(RenderObjectType type){
        if (type == RenderObjectType::kUserField){
            render.RenderField(game_status.GetUserField());
        }
        else if (type == RenderObjectType::kOpponentField){
            render.RenderField(game_status.GetOpponentField());
        }
        else if (type == RenderObjectType::kUserManager){
            render.RenderManager(game_status.GetUserManager(), RenderObjectType::kUserManager);
        }
        else if (type == RenderObjectType::kOpponentManager){
            render.RenderManager(game_status.GetOpponentManager(), RenderObjectType::kOpponentManager);
        }
    }
    ResultOfRound UpdateStatusOfGame(){
        if (game_status.GetAliveOpShips()== 0){
            render.VictoryText();
            return ResultOfRound::kUserWin;
        }
        else if (game_status.GetAliveUsShips() == 0){
            render.GameOverText();
            return ResultOfRound::kUserLose;
        }
        else{
            return ResultOfRound::kContinueGame;
        }
    }
    void SignalTurn(OwnerField type){
        render.SignalMessage(type);
    }
};
#endif //OOPLABEL1_GAMERENDER_H
