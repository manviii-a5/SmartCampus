#include "../include/Building.h"
#include <iostream>

Building::Building()
{
    buildingId = 0;
    hasBasement = false;
    numberOfFloors = 0;
    status = "ACTIVE";
}

Building::Building(int buildingId,
                   const std::string &name,
                   const std::string &type,
                   bool hasBasement,
                   int numberOfFloors,
                   const std::string &status,
                   const std::string &alias)
{
    this->buildingId = buildingId;
    this->name = name;
    this->type = type;
    this->hasBasement = hasBasement;
    this->numberOfFloors = numberOfFloors;
    this->status = status;
    this->alias = alias;
}

int Building::getBuildingId() const
{
    return buildingId;
}

std::string Building::getName() const
{
    return name;
}

std::string Building::getType() const
{
    return type;
}

bool Building::getHasBasement() const
{
    return hasBasement;
}

int Building::getNumberOfFloors() const
{
    return numberOfFloors;
}

std::string Building::getStatus() const
{
    return status;
}

std::string Building::getAlias() const
{
    return alias;
}

void Building::setName(const std::string &name)
{
    this->name = name;
}

void Building::setType(const std::string &type)
{
    this->type = type;
}

void Building::setBasement(bool hasBasement)
{
    this->hasBasement = hasBasement;
}

void Building::setNumberOfFloors(int floors)
{
    this->numberOfFloors = floors;
}

void Building::setStatus(const std::string &status)
{
    this->status = status;
}

void Building::setAlias(const std::string &alias)
{
    this->alias = alias;
}

bool Building::isActive() const
{
    return status == "ACTIVE";
}

void Building::display() const
{
    std::cout << "\n========== BUILDING ==========\n";
    std::cout << "Building ID : " << buildingId << '\n';
    std::cout << "Name        : " << name << '\n';
    std::cout << "Type        : " << type << '\n';
    std::cout << "Basement    : "
              << (hasBasement ? "Yes" : "No") << '\n';
    std::cout << "Floors      : " << numberOfFloors << '\n';
    std::cout << "Status      : " << status << '\n';

    if (!alias.empty())
        std::cout << "Alias       : " << alias << '\n';
}