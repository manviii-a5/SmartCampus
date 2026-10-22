#ifndef BUILDING_H
#define BUILDING_H

#include <string>

class Building
{
private:
    int buildingId;
    std::string name;
    std::string type;
    bool hasBasement;
    int numberOfFloors;
    std::string status;
    std::string alias;

public:
    Building();

    Building(int buildingId,
             const std::string &name,
             const std::string &type,
             bool hasBasement,
             int numberOfFloors,
             const std::string &status,
             const std::string &alias = "");

    int getBuildingId() const;
    std::string getName() const;
    std::string getType() const;
    bool getHasBasement() const;
    int getNumberOfFloors() const;
    std::string getStatus() const;
    std::string getAlias() const;

    void setName(const std::string &name);
    void setType(const std::string &type);
    void setBasement(bool hasBasement);
    void setNumberOfFloors(int floors);
    void setStatus(const std::string &status);
    void setAlias(const std::string &alias);

    bool isActive() const;

    void display() const;
};

#endif