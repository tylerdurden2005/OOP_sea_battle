#include "Manager.h"
Manager::Manager(size_t num_of_ships, std::vector<size_t> &array_of_lengths) {
    num_ships = num_of_ships;
    Ship* ptr;
    for (size_t i : array_of_lengths){
        ptr = new Ship(i);
        all_ships.push_back(ptr);
    }
}

void Manager::GetInfoAboutShips() {
    for (size_t i=0; i<num_ships; ++i){
        all_ships[i]->InformationAboutShip();
    }
}
void Manager::SetSegments(std::vector<std::vector<SegmentStatus>>& new_segments){
    for (size_t i=0; i<num_ships; ++i){
        all_ships[i]->ChangeSegments(new_segments[i]);
    }
}
Ship &Manager::GetShip(size_t id) {
    return *all_ships[id];
}
size_t Manager::GetNumsOfShips(){
    return num_ships;
}
void Manager::DeleteShipById(size_t id) {
    delete all_ships[id];
    all_ships.erase(all_ships.begin() + id);
    num_ships--;
}

Manager::~Manager() {
    for (size_t i=0; i<num_ships; ++i){
        delete all_ships[i];
    }
    num_ships = 0;
}