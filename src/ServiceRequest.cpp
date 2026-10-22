#include "../include/ServiceRequest.h"
#include <iostream>

ServiceRequest::ServiceRequest()
{
    requesterId = 0;
    status = "PENDING";
}

ServiceRequest::ServiceRequest(
    const std::string &requestId,
    long long requesterId,
    const std::string &requesterType,
    const std::string &category,
    const std::string &location,
    const std::string &description,
    const std::string &submissionDateTime)
{
    this->requestId = requestId;
    this->requesterId = requesterId;
    this->requesterType = requesterType;
    this->category = category;
    this->location = location;
    this->description = description;
    this->submissionDateTime = submissionDateTime;
    status = "PENDING";
}

std::string ServiceRequest::getRequestId() const { return requestId; }
long long ServiceRequest::getRequesterId() const { return requesterId; }
std::string ServiceRequest::getRequesterType() const { return requesterType; }
std::string ServiceRequest::getCategory() const { return category; }
std::string ServiceRequest::getLocation() const { return location; }
std::string ServiceRequest::getDescription() const { return description; }
std::string ServiceRequest::getSubmissionDateTime() const { return submissionDateTime; }
std::string ServiceRequest::getStatus() const { return status; }

bool ServiceRequest::editPendingRequest(
    const std::string &category,
    const std::string &location,
    const std::string &description)
{
    if (status != "PENDING")
        return false;

    this->category = category;
    this->location = location;
    this->description = description;

    return true;
}

bool ServiceRequest::cancelPendingRequest()
{
    if (status != "PENDING")
        return false;

    status = "CANCELLED";
    return true;
}

bool ServiceRequest::updateStatus(const std::string &newStatus)
{
    if (newStatus != "PENDING" &&
        newStatus != "IN_PROGRESS" &&
        newStatus != "RESOLVED")
    {
        return false;
    }

    if (status == "RESOLVED")
        return false;

    if (status == "IN_PROGRESS" && newStatus == "PENDING")
        return false;

    status = newStatus;
    return true;
}

void ServiceRequest::display() const
{
    std::cout << "\n========== SERVICE REQUEST ==========\n";
    std::cout << "Request ID  : " << requestId << '\n';
    std::cout << "Requester ID: " << requesterId << '\n';
    std::cout << "Type        : " << requesterType << '\n';
    std::cout << "Category    : " << category << '\n';
    std::cout << "Location    : " << location << '\n';
    std::cout << "Description : " << description << '\n';
    std::cout << "Submitted   : " << submissionDateTime << '\n';
    std::cout << "Status      : " << status << '\n';
}