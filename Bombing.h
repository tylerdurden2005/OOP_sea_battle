#ifndef OOPLABEL1_BOMBING_H
#define OOPLABEL1_BOMBING_H
#include "Abilities.h"
class Bombing : public Ability{
    std::vector<Ship*> ships;
    Manager* manager_ships;
public:
    Bombing(Manager* manager_ships);
    ResultOfAbility Use() override;
    void ChangeCoordinates(Coordinates coord) override {};
    ~Bombing() override;
};
#endif //OOPLABEL1_BOMBING_H
