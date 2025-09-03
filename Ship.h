#ifndef OOPLABEL1_SHIP_H
#define OOPLABEL1_SHIP_H
#include "Errors.h"
enum class OrientationType {
    kVertical = 'v',
    kHorizontal = 'h'
};
enum class SegmentStatus{
    kDestroyed,
    kHalfHealth,
    kFullHealth
};
class Ship{
    size_t length_of_ship;
    std::vector<SegmentStatus> ship_cells;
    OrientationType ship_orientation;
public:
    Ship(size_t length_of_ship, OrientationType ship_orientation = OrientationType::kHorizontal);
    void Hit(size_t cell_number, bool flag=false);
    void ChangeOrientation(OrientationType orientation);
    OrientationType GetOrientation();
    void InformationAboutShip();
    SegmentStatus GetStatus(size_t id_segment);
    void ChangeSegments(std::vector<SegmentStatus>& new_segments);
    bool IsAfloat();
    size_t Len();
};
#endif //OOPLABEL1_SHIP_H
