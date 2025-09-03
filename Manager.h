#ifndef OOPLABEL1_MANAGER_H
#define OOPLABEL1_MANAGER_H
#include "Ship.h"

class Manager{
        size_t num_ships;
        std::vector<Ship*> all_ships;
        public:
        Manager(size_t num_of_ships, std::vector<size_t>& array_of_lengths);
        void GetInfoAboutShips();
        size_t GetNumsOfShips();
        void SetSegments(std::vector<std::vector<SegmentStatus>>& new_segments);
        Ship& GetShip(size_t id);
        void DeleteShipById(size_t id);
        ~Manager();
};
#endif //OOPLABEL1_MANAGER_H
