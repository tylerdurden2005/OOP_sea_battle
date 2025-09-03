#ifndef OOPLABEL1_LOCATOR_H
#define OOPLABEL1_LOCATOR_H
#include "Abilities.h"
class Locator : public Ability{
    Coordinates coord{};
    GamingField* field;
public:
    Locator(GamingField* field, Coordinates coord);
    ResultOfAbility Use() override;
    void ChangeCoordinates(Coordinates coord_for_change) override;
    ~Locator() override;
};
#endif //OOPLABEL1_LOCATOR_H
