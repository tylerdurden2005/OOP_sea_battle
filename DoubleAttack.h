#ifndef OOPLABEL1_DOUBLEATTACK_H
#define OOPLABEL1_DOUBLEATTACK_H
#include "Abilities.h"
class DoubleAttack : public Ability{
    Coordinates coord{};
    GamingField* field;
public:
    DoubleAttack(GamingField* field, Coordinates coord);
    ResultOfAbility Use() override;
    void ChangeCoordinates(Coordinates coord_for_change) override;
    ~DoubleAttack() override;
};
#endif //OOPLABEL1_DOUBLEATTACK_H
