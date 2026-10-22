#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room
{
private:
    int roomId;
    int buildingId;
    std::string floor;
    std::string roomNumber;
    std::string roomType;
    int capacity;
    std::string status;

public:
    Room();

    Room(int roomId,
         int buildingId,
         const std::string &floor,
         const std::string &roomNumber,
         const std::string &roomType,
         int capacity,
         const std::string &status);

    int getRoomId() const;
    int getBuildingId() const;
    std::string getFloor() const;
    std::string getRoomNumber() const;
    std::string getRoomType() const;
    int getCapacity() const;
    std::string getStatus() const;

    void setFloor(const std::string &floor);
    void setRoomNumber(const std::string &roomNumber);
    void setRoomType(const std::string &roomType);
    void setCapacity(int capacity);
    void setStatus(const std::string &status);

    bool isAvailable() const;

    void display() const;
};

#endif