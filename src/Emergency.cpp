#include "Emergency.h"
#include <iostream>
#include <string>

Emergency::Emergency()
{
    reporterId = 0;
    priority = "LOW";
    status = "PENDING";
}

Emergency::Emergency(const std::string &emergencyId,
                     long long reporterId,
                     const std::string &reporterType,
                     const std::string &emergencyType,
                     const std::string &location,
                     const std::string &description,
                     const std::string &reportDateTime)
{
    this->emergencyId = emergencyId;
    this->reporterId = reporterId;
    this->reporterType = reporterType;
    this->emergencyType = emergencyType;
    this->location = location;
    this->description = description;
    this->reportDateTime = reportDateTime;

    responseTeam = "";
    dispatchDateTime = "";
    actionTaken = "";
    resolutionDateTime = "";
    status = "PENDING";

    determinePriority();
}

void Emergency::determinePriority()
{
    if (emergencyType == "Medical" ||
        emergencyType == "Fire")
    {
        priority = "CRITICAL";
    }
    else if (emergencyType == "Security" ||
             emergencyType == "Accident")
    {
        priority = "HIGH";
    }
    else if (emergencyType == "Infrastructure")
    {
        priority = "MEDIUM";
    }
    else
    {
        priority = "LOW";
    }
}

std::string Emergency::getEmergencyId() const { return emergencyId; }
long long Emergency::getReporterId() const { return reporterId; }
std::string Emergency::getReporterType() const { return reporterType; }
std::string Emergency::getEmergencyType() const { return emergencyType; }
std::string Emergency::getLocation() const { return location; }
std::string Emergency::getDescription() const { return description; }
std::string Emergency::getPriority() const { return priority; }
std::string Emergency::getStatus() const { return status; }
std::string Emergency::getResponseTeam() const { return responseTeam; }

void Emergency::setResponseTeam(const std::string &team)
{
    responseTeam = team;
}

void Emergency::setDispatchDateTime(const std::string &dateTime)
{
    dispatchDateTime = dateTime;
}

void Emergency::setActionTaken(const std::string &action)
{
    actionTaken = action;
}

void Emergency::setStatus(const std::string &status)
{
    this->status = status;
}

void Emergency::setResolutionDateTime(const std::string &dateTime)
{
    resolutionDateTime = dateTime;
}

bool Emergency::isActive() const
{
    return status == "PENDING" ||
           status == "HELP_DISPATCHED" ||
           status == "TEAM_RESPONDING";
}

void Emergency::display() const
{
    std::cout << "\n========== EMERGENCY ==========\n";
    std::cout << "Emergency ID : " << emergencyId << '\n';
    std::cout << "Reporter ID  : " << reporterId << '\n';
    std::cout << "Reporter Type: " << reporterType << '\n';
    std::cout << "Type         : " << emergencyType << '\n';
    std::cout << "Location     : " << location << '\n';
    std::cout << "Description  : " << description << '\n';
    std::cout << "Priority     : " << priority << '\n';
    std::cout << "Status       : " << status << '\n';
    std::cout << "Response Team: " << responseTeam << '\n';
}