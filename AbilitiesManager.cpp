#include "AbilitiesManager.h"

AbilitiesManager::AbilitiesManager(GamingField *field, Manager *manager) {
    this->field = field;
    ship_manager = manager;
    std::vector<size_t> variety = {0,1,2};
    std::srand(time(nullptr));
    for (size_t i =0; i< 3; ++i){
        size_t kick;
        if (variety.size() != 1){
            kick = std::rand() % variety.size();
        }
        else kick = 0;
        if (variety[kick] == 0){
            abilities.emplace(new DoubleAttack(field, {0,0}), TypesAbility::kDoubleAttack);
        }
        else if (variety[kick] == 1){
            abilities.emplace(new Locator(field, {0,0}), TypesAbility::kLocator);
        }
        else{
            abilities.emplace(new Bombing(ship_manager), TypesAbility::kBombing);
        }
        variety.erase(variety.begin()+kick);
        abilities_vector.push_back(abilities.back().second);
    }
}

void AbilitiesManager::UseSKill(Coordinates coord) {
    if (abilities.empty()){
        throw AbilityError("Nothing using, you don`t have abilities!\n");
    }
    auto* ability = abilities.front().first;
    ability->ChangeCoordinates(coord);
    try{
        ResultOfAbility flag = ability->Use();
        if (flag == ResultOfAbility::kAllDestroy){
            AddAbility();
        }
        else if (flag == ResultOfAbility::kFindShip){
            std::cout << "You find a ship!\n";
        }
        else if (flag == ResultOfAbility::kNotFoundShip){
            std::cout << "There are no ships here!\n";
        }
        delete ability;
        abilities.pop();
        abilities_vector.erase(abilities_vector.begin());
        std::cout << "Success ability.\n";
    }
    catch(ProgramErrors& e){
        throw AbilityError(e.what());
    }
}

void AbilitiesManager::AddAbility() {
    std::srand(time(nullptr));
    size_t random_ability = std::rand() % 3;
    if (random_ability == static_cast<size_t>(TypesAbility::kDoubleAttack)){
        abilities.emplace(new DoubleAttack(field, {0,0}), TypesAbility::kDoubleAttack);
    }
    else if(random_ability == static_cast<size_t>(TypesAbility::kLocator)){
        abilities.emplace(new Locator(field, {0,0}), TypesAbility::kLocator);
    }
    else{
        abilities.emplace(new Bombing(ship_manager), TypesAbility::kBombing);
    }
    abilities_vector.push_back(abilities.back().second);
}

size_t AbilitiesManager::GetQueueSize() {
    return abilities.size();
}
std::vector<TypesAbility>& AbilitiesManager::GetAbilities(){
    return abilities_vector;
}
AbilitiesManager::AbilitiesManager(std::vector<TypesAbility>& abilities_for_define, GamingField* game_field, Manager* manager){
    field = game_field;
    ship_manager = manager;
    if (abilities_for_define[0] == TypesAbility::kNothing) return;
    for (auto i : abilities_for_define){
        if (i==TypesAbility::kDoubleAttack){
            abilities.emplace(new DoubleAttack(field, {0,0}), TypesAbility::kDoubleAttack);
        }
        else if (i==TypesAbility::kLocator){
            abilities.emplace(new Locator(field, {0,0}), TypesAbility::kLocator);
        }
        else if (i==TypesAbility::kBombing){
            abilities.emplace(new Bombing(ship_manager), TypesAbility::kBombing);
        }
        abilities_vector.push_back(i);
    }
}

void AbilitiesManager::ChangePointers(GamingField* new_filed, Manager* new_manger) {
    field = new_filed;
    ship_manager = new_manger;
}
TypesAbility AbilitiesManager::CurrentAbility() {
    if (abilities.empty()){
        std::cout << "You have 0 abilities, just attack!\n";
        return TypesAbility::kNothing;
    }
    else if (abilities.front().second == TypesAbility::kDoubleAttack){
        std::cout << "You have skill: \"Double Attack\"\n";
        return TypesAbility::kDoubleAttack;
    }
    else if (abilities.front().second == TypesAbility::kLocator){
        std::cout << "You have skill: \"Locator\"\n";
        return TypesAbility::kLocator;
    }
    else{
        std::cout << "You have skill: \"Bombing\"\n";
        return TypesAbility::kBombing;
    }
}
void AbilitiesManager::Clear(){
    while (!abilities.empty()){
        auto* ptr = abilities.front().first;
        delete ptr;
        ptr = nullptr;
        abilities.pop();
    }
    abilities_vector.clear();
    field = nullptr;
    ship_manager = nullptr;
}
AbilitiesManager::~AbilitiesManager() {
    Clear();
}