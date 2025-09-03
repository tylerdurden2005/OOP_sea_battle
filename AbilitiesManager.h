#ifndef OOPLABEL1_ABILITIESMANAGER_H
#define OOPLABEL1_ABILITIESMANAGER_H
#include "DoubleAttack.h"
#include "Locator.h"
#include "Bombing.h"
enum class TypesAbility{
    kDoubleAttack,
    kLocator,
    kBombing,
    kNothing
};
class AbilitiesManager{
    std::queue<std::pair<Ability*, TypesAbility>> abilities;
    GamingField* field;
    Manager* ship_manager;
    std::vector<TypesAbility> abilities_vector;
public:
    AbilitiesManager(GamingField* field,  Manager* manager);
    AbilitiesManager(std::vector<TypesAbility>& abilities_for_define, GamingField* game_field, Manager* manager);
    void UseSKill(Coordinates coord = {0, 0});
    void AddAbility();
    TypesAbility CurrentAbility();
    size_t GetQueueSize();
    void Clear();
    std::vector<TypesAbility>& GetAbilities();
    void ChangePointers(GamingField* new_filed, Manager* new_manger);
    ~AbilitiesManager();
};
#endif //OOPLABEL1_ABILITIESMANAGER_H
