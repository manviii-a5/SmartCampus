#ifndef CAMPUS_DATA_MANAGER_H
#define CAMPUS_DATA_MANAGER_H
#include <string>
namespace CampusDataManager
{
    bool initialize();
    void listBuildings();
    void addBuilding();
    void listRooms();
    void addRoom();
    void searchRoom();
    void listRoomsForBuilding(int buildingId);
}
#endif
