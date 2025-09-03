#include "DoubleAttack.h"
DoubleAttack::DoubleAttack(GamingField *field, Coordinates coord) {
    this->coord = coord;
    this->field = field;
}

ResultOfAbility DoubleAttack::Use() {
    try{
        bool flag;
        flag = field->Attack(coord, true);
        if (flag){
            return ResultOfAbility::kAllDestroy;
        }
        return ResultOfAbility::kStillAlive;
    }
    catch(ProgramErrors& e){
        throw AbilityError(e.what());
    }
}
void DoubleAttack::ChangeCoordinates(Coordinates coord_for_change) {
    coord = coord_for_change;
}

DoubleAttack::~DoubleAttack() {
    field = nullptr;
}
