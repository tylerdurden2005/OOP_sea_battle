#ifndef OOPLABEL1_GAMINGFIELD_H
#define OOPLABEL1_GAMINGFIELD_H
#include "Ship.h"
enum class StatusCellOnField{
    kUnknown = '?',
    kEmpty = '_',
    kShip = 'S',
    kBoom = 'x'
};

enum class OwnerField{
    kMyField,
    kOpponentsField
};

struct Coordinates{
    size_t x;
    size_t y;
    bool operator==(const Coordinates& other) const {
        return (x == other.x) && (y == other.y);
    }
    bool operator!=(const Coordinates& other) const {
        return !(*this == other);
    }
};

struct Cell{
    StatusCellOnField status;
    Ship* ship_on_field;
    size_t segment;
};

class GamingField{
    size_t vertical_length;
    size_t horizontal_length;
    std::vector<std::vector<Cell>> field;
    OwnerField owner;
    void CheckCellsAroundShip(Coordinates ship_coord, size_t ship_length, OrientationType ship_orientation);
public:
    GamingField(size_t horizontal_length, size_t vertical_length, OwnerField owner = OwnerField::kMyField);
    void AddShip(Ship& boat, Coordinates boat_coord, OrientationType boat_orientation);
    bool Attack(Coordinates coord_for_attack, bool flag=false);
    //void PrintField();
    void ChangeOwner(OwnerField new_owner);
    OwnerField GetOwner(){
        return owner;
    }
    size_t GetHorizontalLen();
    size_t GetVerticalLen();
    GamingField(const GamingField& field_for_copy);
    std::vector<std::vector<Cell>>& GetCells();
    void ChangeStatusCells(std::vector<std::vector<StatusCellOnField>>& new_status);
    GamingField& operator=(const GamingField& field_for_copy);
    GamingField(GamingField&& move_field);
    GamingField& operator=(GamingField&& move_field);
    ~GamingField();
};
#endif //OOPLABEL1_GAMINGFIELD_H
