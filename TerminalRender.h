//
// Created by nikita on 19.12.24.
//

#ifndef OOPLABEL1_TERMINALRENDER_H
#define OOPLABEL1_TERMINALRENDER_H
#include "GameRender.h"
class TerminalRender{
public:
    void RenderField(GamingField* field);
    void RenderManager(Manager* manager, RenderObjectType type);
    void VictoryText();
    void GameOverText();
    void SignalMessage(OwnerField type);
};
#endif //OOPLABEL1_TERMINALRENDER_H
