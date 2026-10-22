#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource
{
private:
    int resourceId;
    std::string resourceName;
    std::string resourceType;
    std::string locationType;
    int locationId;
    std::string status;

public:
    Resource();

    Resource(int resourceId,
             const std::string &resourceName,
             const std::string &resourceType,
             const std::string &locationType,
             int locationId,
             const std::string &status);

    int getResourceId() const;
    std::string getResourceName() const;
    std::string getResourceType() const;
    std::string getLocationType() const;
    int getLocationId() const;
    std::string getStatus() const;

    void setResourceName(const std::string &name);
    void setResourceType(const std::string &type);
    void setLocationType(const std::string &type);
    void setLocationId(int id);
    void setStatus(const std::string &status);

    bool isBookable() const;

    void display() const;
};

#endif