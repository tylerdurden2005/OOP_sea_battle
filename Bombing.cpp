#include "Bombing.h"
Bombing::Bombing(Manager* manager_ships){
    this->manager_ships = manager_ships;
}
ResultOfAbility Bombing::Use(){
    if (!ships.empty()){
        ships.clear();
    }
    for (size_t i = 0; i<manager_ships->GetNumsOfShips(); ++i){
        if (manager_ships->GetShip(i).IsAfloat()){
            ships.push_back(&(manager_ships->GetShip(i)));
        }
    }
    if (ships.empty()){
        throw AbilityError("All ships have been destroyed!\n");
    }
    size_t random_ship;
    std::srand(time(nullptr));
    random_ship = static_cast<size_t>(std::rand() % ships.size());
    Ship* ship_for_attack = ships[random_ship];
    size_t nums_of_alive = 0;
    std::vector<size_t> segments;
    for (size_t i=0; i<ship_for_attack->Len(); ++i){
        if (ship_for_attack->GetStatus(i) != SegmentStatus::kDestroyed){
            nums_of_alive++;
            segments.push_back(i);
        }
    }
    size_t random_segment;
    if (nums_of_alive == 1){
        random_segment = segments[0];
    }
    else {
        random_segment = segments[static_cast<size_t>(std::rand() % nums_of_alive)];
    }
    ship_for_attack->Hit(random_segment);
    if (!ship_for_attack->IsAfloat()){
        return ResultOfAbility::kAllDestroy;;
    }
    return ResultOfAbility::kStillAlive;
}

Bombing::~Bombing() {
    manager_ships = nullptr;
}
