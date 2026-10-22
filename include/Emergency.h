#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <string>

class Emergency
{
private:
    std::string emergencyId;
    long long reporterId;
    std::string reporterType;
    std::string emergencyType;
    std::string location;
    std::string description;
    std::string priority;
    std::string reportDateTime;
    std::string responseTeam;
    std::string dispatchDateTime;
    std::string actionTaken;
    std::string status;
    std::string resolutionDateTime;

public:
    Emergency();

    Emergency(const std::string &emergencyId,
              long long reporterId,
              const std::string &reporterType,
              const std::string &emergencyType,
              const std::string &location,
              const std::string &description,
              const std::string &reportDateTime);

    std::string getEmergencyId() const;
    long long getReporterId() const;
    std::string getReporterType() const;
    std::string getEmergencyType() const;
    std::string getLocation() const;
    std::string getDescription() const;
    std::string getPriority() const;
    std::string getStatus() const;
    std::string getResponseTeam() const;

    void setResponseTeam(const std::string &team);
    void setDispatchDateTime(const std::string &dateTime);
    void setActionTaken(const std::string &action);
    void setStatus(const std::string &status);
    void setResolutionDateTime(const std::string &dateTime);

    bool isActive() const;

    void display() const;

private:
    void determinePriority();
};

#endif