#ifndef OOPLABEL1_ABILITIES_H
#define OOPLABEL1_ABILITIES_H
#include "Manager.h"
#include "GamingField.h"
enum class ResultOfAbility{
    kFindShip,
    kNotFoundShip,
    kAllDestroy,
    kStillAlive
};
class Ability{
public:
    virtual ResultOfAbility Use() = 0;
    virtual ~Ability() = default;
    virtual void ChangeCoordinates(Coordinates coord) = 0;
};
#endif //OOPLABEL1_ABILITIES_H
