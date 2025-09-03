
#include "TerminalRender.h"
#include "GameController.h"


int main() {
    Game game;
    GameController<InputFromTerminal, TerminalRender> game_controller(game);
    game_controller.Start();
}












