#include "Locator.h"
Locator::Locator(GamingField *field, Coordinates coord) {
    this->coord = coord;
    this->field = field;
}
ResultOfAbility Locator::Use() {
    size_t y = coord.y - 1;
    size_t x = coord.x - 1;
    if (x>=field->GetHorizontalLen()){
        throw CoordinatesError("Warning: the X is impossible!\n");
    }
    if (y>=field->GetVerticalLen()){
        throw CoordinatesError("Warning: the Y is impossible!\n");
    }
    for (size_t i = y; i < y + 2 && i < field->GetVerticalLen(); ++i) {
        for (size_t j = x; j < x + 2 && j < field->GetHorizontalLen(); ++j) {
            if (field->GetCells()[i][j].ship_on_field != nullptr && field->GetCells()[i][j].ship_on_field->IsAfloat()) {
                return ResultOfAbility::kFindShip;
            }
        }
    }
    return ResultOfAbility::kNotFoundShip;
}
void Locator::ChangeCoordinates(Coordinates coord_for_change) {
    coord = coord_for_change;
}

Locator::~Locator() {
    field = nullptr;
}
