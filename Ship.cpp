#include "Ship.h"

Ship::Ship(size_t length_of_ship, OrientationType ship_orientation) {
    this->length_of_ship = length_of_ship;
    ship_cells.reserve(this->length_of_ship);
    ship_cells.assign(this->length_of_ship, SegmentStatus::kFullHealth);
    this->ship_orientation = ship_orientation;
}

void Ship::Hit(size_t cell_number, bool flag) {
    if (ship_cells[cell_number] == SegmentStatus::kFullHealth){
        ship_cells[cell_number] = SegmentStatus::kHalfHealth;
        if (flag){
            ship_cells[cell_number] = SegmentStatus::kDestroyed;
        }
    }
    else if (ship_cells[cell_number] == SegmentStatus::kHalfHealth){
        ship_cells[cell_number] = SegmentStatus::kDestroyed;
    }
    else{
        throw AttackError("This cell is already destroyed! Try again.\n");
    }
}

OrientationType Ship::GetOrientation() {
    return ship_orientation;
}
void Ship::ChangeSegments(std::vector<SegmentStatus>& new_segments){
    ship_cells = new_segments;
}
void Ship::ChangeOrientation(OrientationType orientation) {
    ship_orientation = orientation;
}

void Ship::InformationAboutShip() {
    std::cout << "Length of ship: " << length_of_ship << "\n";
    if (ship_orientation == OrientationType::kVertical){
        std::cout << "Orientation of ship: Vertical\n";
    }
    else if (ship_orientation == OrientationType::kHorizontal){
        std::cout << "Orientation of ship: Horizontal\n";
    }
    std::cout << "Ship status: \n";
    size_t id_cells=0;
    for (SegmentStatus i : ship_cells){
        id_cells++;
        if (i==SegmentStatus::kFullHealth) std::cout << "---- " << id_cells << " cell: Full Health\n";
        else if(i == SegmentStatus::kHalfHealth) std::cout << "---- " << id_cells << " cell: Half Health\n";
        else std::cout << "---- " << id_cells << " cell: Destroyed\n";
    }
}
bool Ship::IsAfloat() {
    for (size_t i = 0; i<length_of_ship; ++i){
        if (this->GetStatus(i) != SegmentStatus::kDestroyed){
            return true;
        }
    }
    return false;
}
SegmentStatus Ship::GetStatus(size_t id_segment) {
    return ship_cells[id_segment];
}

size_t Ship::Len() {
    return length_of_ship;
}