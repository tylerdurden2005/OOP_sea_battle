#include "GamingField.h"

void GamingField::CheckCellsAroundShip(Coordinates ship_coord, size_t ship_length, OrientationType ship_orientation) {
    if (ship_coord.x > horizontal_length){
        throw PlacementError("Warning: Ship can't add on these coordinates, the X is impossible!\n");
    }
    if (ship_coord.y > vertical_length){
        throw PlacementError("Warning: Ship can't add on these coordinates, the Y is impossible!\n");
    }
    if (ship_orientation==OrientationType::kHorizontal && ship_coord.x - 1 + ship_length -1 >= horizontal_length){
        throw PlacementError("Warning: Ship can't add on these coordinates, it will go beyond the horizontal length!\n");
    }
    if (ship_orientation==OrientationType::kVertical && ship_coord.y - 1 + ship_length -1 >= vertical_length){
        throw PlacementError("Warning: Ship can't add on these coordinates, it will go beyond the vertical length!\n");
    }
    size_t x_left, y_left;
    if (ship_coord.x == 1 ) x_left = 0;
    else{
        x_left = ship_coord.x-2;
    }
    if (ship_coord.y ==1) y_left = 0;
    else{
        y_left = ship_coord.y -2;
    }
    size_t x_right, y_right;
    if (ship_orientation == OrientationType::kHorizontal){
        if (x_left == 0) x_right = ship_length;
        else x_right = x_left + ship_length + 1;
        if (y_left == 0) y_right = 1;
        else y_right = y_left + 2;
    }
    else{
        if (x_left == 0) x_right = 1;
        else x_right = x_left + 2;
        if (y_left == 0) y_right = ship_length;
        else y_right = y_left + ship_length + 1;
    }
    int flag = 0;
    for (size_t i = y_left; i<=y_right && i<vertical_length; ++i){
        for (size_t j = x_left; j<=x_right && j<horizontal_length; ++j){
            if (field[i][j].ship_on_field != nullptr){
                flag = 1;
                break;
            }
        }
        if (flag == 1) break;
    }
    if (flag == 1){
        //std::cout << "Warning: Ship can't add on these coordinates, another ship is nearby!\n";
        //return false;
        throw PlacementError("Warning: Ship can't add on these coordinates, another ship is nearby!\n");
    }
    //else return true;
}

GamingField::GamingField(size_t horizontal_length, size_t vertical_length, OwnerField owner) {
    this->horizontal_length = horizontal_length;
    this->vertical_length = vertical_length;
    this->owner = owner;
    field.resize(vertical_length, std::vector<Cell>(horizontal_length));
    for (size_t i=0; i!=vertical_length; ++i){
        for (size_t j=0; j!=horizontal_length; ++j){
            if (owner != OwnerField::kOpponentsField) field[i][j].status = StatusCellOnField::kEmpty;
            else field[i][j].status = StatusCellOnField::kUnknown;
            field[i][j].ship_on_field = nullptr;
        }
    }
}

bool GamingField::Attack(Coordinates coord_for_attack, bool flag){
    size_t x = coord_for_attack.x - 1;
    size_t y = coord_for_attack.y - 1;
    if (x>=horizontal_length){
        throw CoordinatesError("Warning: the X is impossible!\n");
    }
    if (y>=vertical_length){
        throw CoordinatesError("Warning: the Y is impossible!\n");
    }
    if (field[y][x].ship_on_field != nullptr){
        field[y][x].ship_on_field->Hit(field[y][x].segment, flag);
        if (field[y][x].status==StatusCellOnField::kUnknown){
            field[y][x].status = StatusCellOnField::kShip;
        }
        if (field[y][x].ship_on_field->GetStatus(field[y][x].segment) == SegmentStatus::kDestroyed){
            field[y][x].status = StatusCellOnField::kBoom;
        }
        if (!field[y][x].ship_on_field->IsAfloat()){
            return true;
        }
    }
    else{
        if (owner == OwnerField::kOpponentsField){
            if (field[y][x].status==StatusCellOnField::kUnknown){
                field[y][x].status = StatusCellOnField::kEmpty;
            }
            else{
                throw AttackError("Warning: this cell has already been attacked! Try again:\n");
            }
        }
        else{
            if (field[y][x].status==StatusCellOnField::kBoom){
                throw AttackError("Warning: this cell has already been attacked! Try again:\n");
            }
            else{
                field[y][x].status = StatusCellOnField::kBoom;
            }
        }
    }
    return false;
}

void GamingField::AddShip(Ship &boat, Coordinates boat_coord, OrientationType boat_orientation) {
    boat.ChangeOrientation(boat_orientation);
    try{
        CheckCellsAroundShip(boat_coord, boat.Len(), boat.GetOrientation());
    }
    catch(PlacementError& e){
        std::cout << e.what();
        throw PlacementError("");
    }
    if (boat_orientation == OrientationType::kHorizontal){
        size_t segment = 0;
        for (size_t i = boat_coord.x -1; i<boat_coord.x + boat.Len()-1; ++i){
            field[boat_coord.y-1][i].segment = segment++;
            field[boat_coord.y-1][i].ship_on_field = &boat;
            if (owner != OwnerField::kOpponentsField){
                field[boat_coord.y-1][i].status = StatusCellOnField::kShip;
            }
        }
    }
    else{
        size_t segment = 0;
        for (size_t i = boat_coord.y -1; i<boat_coord.y + boat.Len()-1; ++i){
            field[i][boat_coord.x-1].segment = segment++;
            field[i][boat_coord.x-1].ship_on_field = &boat;
            if (owner != OwnerField::kOpponentsField){
                field[i][boat_coord.x-1].status = StatusCellOnField::kShip;
            }
        }
    }
}

void GamingField::ChangeOwner(OwnerField new_owner) { //for tests opponent
    owner = new_owner;
    for (std::vector<Cell>& i : field){
        for(Cell& j : i){
            j.status=StatusCellOnField::kUnknown;
        }
    }
}
std::vector<std::vector<Cell>>& GamingField::GetCells(){
    return field;
}
size_t GamingField::GetHorizontalLen(){
    return horizontal_length;
}
size_t GamingField::GetVerticalLen(){
    return vertical_length;
}
GamingField::GamingField(const GamingField &field_for_copy) {
    std::cout << "Copy constructor\n";
    horizontal_length = field_for_copy.horizontal_length;
    vertical_length = field_for_copy.vertical_length;
    owner = field_for_copy.owner;
    field = field_for_copy.field;
}
void GamingField::ChangeStatusCells(std::vector<std::vector<StatusCellOnField>>& new_status){
    for (size_t i=0; i<vertical_length; ++i){
        for (size_t j=0; j< horizontal_length; ++j){
            field[i][j].status = new_status[i][j];
        }
    }
}
GamingField& GamingField::operator=(const GamingField &field_for_copy) {
    if (this != &field_for_copy){
        std::cout << "Copy =\n";
        horizontal_length = field_for_copy.horizontal_length;
        vertical_length = field_for_copy.vertical_length;
        owner = field_for_copy.owner;
        field = field_for_copy.field;
    }
    return *this;
}

GamingField::GamingField(GamingField &&move_field) {
    std::cout << "Move constructor\n";
    std::swap(vertical_length, move_field.vertical_length);
    std::swap(horizontal_length, move_field.horizontal_length);
    std::swap(owner, move_field.owner);
    field = std::move(move_field.field);
}

GamingField &GamingField::operator=(GamingField &&move_field) {
    if (this != &move_field){
        std::cout << "Move =\n";
        std::swap(vertical_length, move_field.vertical_length);
        std::swap(horizontal_length, move_field.horizontal_length);
        std::swap(owner, move_field.owner);
        field = std::move(move_field.field);
    }
    return *this;
}
/*
void GamingField::PrintField() {
    if (owner == OwnerField::kMyField) {
        std::cout << "Your Field:\n";
    }
    else{
        std::cout << "Opponent Field:\n";
    }
    for (size_t i = 0; i<horizontal_length+1; ++i){
        std::cout << "[" << i << "] ";
    }
    std::cout << "\n";
    size_t h_column = 1;
    size_t row = 1;
    for (std::vector<Cell>& i : field){
        if (h_column < 10) {
            std::cout << "[" << h_column++ << "] ";
        }
        else {
            std::cout << "[" << h_column++ << "]";
        }
        for (Cell& j : i){
            row++;
            if (row >=10) {
                std::cout << " " <<static_cast<char>(j.status) << "  ";
            }
            else {
                std::cout << " " <<static_cast<char>(j.status) << "  ";
            }
        }
        std::cout << '\n';
    }
    std::cout << "-----------------------------------\n";
}
*/
GamingField::~GamingField() {
    horizontal_length = 0;
    vertical_length = 0;
    for (std::vector<Cell>& i : field){
        for (Cell& j : i){
            j.ship_on_field = nullptr;
            j.segment = 0;
            j.status = StatusCellOnField::kEmpty;
        }
    }
}