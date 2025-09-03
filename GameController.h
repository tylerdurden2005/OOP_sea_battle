//
// Created by nikita on 19.12.24.
//

#ifndef OOPLABEL1_GAMECONTROLLER_H
#define OOPLABEL1_GAMECONTROLLER_H
#include "GameRender.h"
template <typename InputType, typename  RenderType>
class GameController{
    Game& game;
    InputType input_type;
    GameRender<RenderType> render;
public:
    GameController(Game& our_game) : game(our_game), render(our_game.GetGameStatus()){}
    void Start(){
        input_type.KeyDesignations();
        TypeOfGame status_of_game = TypeOfGame::kEmptyGame;
        while (true){
            CommandType type = input_type.GetCommand();
            if (type == CommandType::kStartGame){
                if (status_of_game == TypeOfGame::kEmptyGame){
                    game.StartNewGame();
                    status_of_game = TypeOfGame::kGamePlaying;
                }
                else {
                    game.GameStatusFree();
                    game.StartNewGame();
                }
            }
            else if (type == CommandType::kClose){
                status_of_game = TypeOfGame::kEmptyGame;
                return;
            }
            else if (type == CommandType::kLoadGame){
                try{
                    game.LoadGame();
                    status_of_game = TypeOfGame::kGamePlaying;
                }
                catch (ProgramErrors& e){
                    input_type.InvalidCall(InvalidType::kInvalidLoad);
                }
            }
            else if (type == CommandType::kSaveGame){
                if (status_of_game == TypeOfGame::kGamePlaying){
                    try{
                        game.SaveGame();
                    }
                    catch (ProgramErrors& e){
                        input_type.InvalidCall(InvalidType::kInvalidSave);
                    }
                }
                else input_type.InvalidCall(InvalidType::kInvalidSave);
            }
            else if (type == CommandType::kRules){
                input_type.Rules();
                input_type.KeyDesignations();
            }
            else if (type == CommandType::kAttack){
                if (status_of_game == TypeOfGame::kGamePlaying){
                    render.SignalTurn(OwnerField::kMyField);
                    game.UserTurn();
                    ResultOfRound result = render.UpdateStatusOfGame();
                    //ResultOfRound result = game.IsGameFinish();
                    if (result == ResultOfRound::kContinueGame){
                        render.SignalTurn(OwnerField::kOpponentsField);
                        game.OpponentTurn();
                        result = render.UpdateStatusOfGame();
                        //result = game.IsGameFinish();
                    }
                    if (result == ResultOfRound::kUserLose){
                        return;
                    }
                    else if (result == ResultOfRound::kUserWin){
                        game.NextOpponent();
                    }
                }
                else{
                    input_type.InvalidCall(InvalidType::kInvalidAttack);
                }
            }
            else if (type == CommandType::kPrintRender){
                OutSpecialCommand special_out = input_type.GetSpecialCommand(InputSpecialCommand::kRenderSP);
                if (special_out == OutSpecialCommand::kRenderUsField){
                    render.RenderingBasic(RenderObjectType::kUserField);
                }
                else if (special_out == OutSpecialCommand::kRenderOpField){
                    render.RenderingBasic(RenderObjectType::kOpponentField);
                }
                else if (special_out == OutSpecialCommand::kRenderUsManager){
                    render.RenderingBasic(RenderObjectType::kUserManager);
                }
                else if (special_out == OutSpecialCommand::kRenderOpManager){
                    render.RenderingBasic(RenderObjectType::kOpponentManager);
                }
            }

        }
    }
};
#endif //OOPLABEL1_GAMECONTROLLER_H
