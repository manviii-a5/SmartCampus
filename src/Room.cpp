#include "../include/Room.h"
#include <iostream>

Room::Room()
{
    roomId = 0;
    buildingId = 0;
    capacity = 0;
    status = "AVAILABLE";
}

Room::Room(int roomId,
           int buildingId,
           const std::string &floor,
           const std::string &roomNumber,
           const std::string &roomType,
           int capacity,
           const std::string &status)
{
    this->roomId = roomId;
    this->buildingId = buildingId;
    this->floor = floor;
    this->roomNumber = roomNumber;
    this->roomType = roomType;
    this->capacity = capacity;
    this->status = status;
}

int Room::getRoomId() const
{
    return roomId;
}

int Room::getBuildingId() const
{
    return buildingId;
}

std::string Room::getFloor() const
{
    return floor;
}

std::string Room::getRoomNumber() const
{
    return roomNumber;
}

std::string Room::getRoomType() const
{
    return roomType;
}

int Room::getCapacity() const
{
    return capacity;
}

std::string Room::getStatus() const
{
    return status;
}

void Room::setFloor(const std::string &floor)
{
    this->floor = floor;
}

void Room::setRoomNumber(const std::string &roomNumber)
{
    this->roomNumber = roomNumber;
}

void Room::setRoomType(const std::string &roomType)
{
    this->roomType = roomType;
}

void Room::setCapacity(int capacity)
{
    this->capacity = capacity;
}

void Room::setStatus(const std::string &status)
{
    this->status = status;
}

bool Room::isAvailable() const
{
    return status == "AVAILABLE";
}

void Room::display() const
{
    std::cout << "\n========== ROOM ==========\n";
    std::cout << "Room ID     : " << roomId << '\n';
    std::cout << "Building ID : " << buildingId << '\n';
    std::cout << "Floor       : " << floor << '\n';
    std::cout << "Room        : " << roomNumber << '\n';
    std::cout << "Room Type   : " << roomType << '\n';
    std::cout << "Capacity    : " << capacity << '\n';
    std::cout << "Status      : " << status << '\n';
}