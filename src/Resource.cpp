#include "../include/Resource.h"
#include <iostream>

Resource::Resource()
{
    resourceId = 0;
    locationId = 0;
    status = "ACTIVE";
}

Resource::Resource(int resourceId,
                   const std::string &resourceName,
                   const std::string &resourceType,
                   const std::string &locationType,
                   int locationId,
                   const std::string &status)
{
    this->resourceId = resourceId;
    this->resourceName = resourceName;
    this->resourceType = resourceType;
    this->locationType = locationType;
    this->locationId = locationId;
    this->status = status;
}

int Resource::getResourceId() const
{
    return resourceId;
}

std::string Resource::getResourceName() const
{
    return resourceName;
}

std::string Resource::getResourceType() const
{
    return resourceType;
}

std::string Resource::getLocationType() const
{
    return locationType;
}

int Resource::getLocationId() const
{
    return locationId;
}

std::string Resource::getStatus() const
{
    return status;
}

void Resource::setResourceName(const std::string &name)
{
    resourceName = name;
}

void Resource::setResourceType(const std::string &type)
{
    resourceType = type;
}

void Resource::setLocationType(const std::string &type)
{
    locationType = type;
}

void Resource::setLocationId(int id)
{
    locationId = id;
}

void Resource::setStatus(const std::string &status)
{
    this->status = status;
}

bool Resource::isBookable() const
{
    return status == "ACTIVE";
}

void Resource::display() const
{
    std::cout << "\n========== RESOURCE ==========\n";
    std::cout << "Resource ID   : " << resourceId << '\n';
    std::cout << "Resource Name : " << resourceName << '\n';
    std::cout << "Resource Type : " << resourceType << '\n';
    std::cout << "Location Type : " << locationType << '\n';
    std::cout << "Location ID   : " << locationId << '\n';
    std::cout << "Status        : " << status << '\n';
}