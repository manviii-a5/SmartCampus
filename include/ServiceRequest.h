#ifndef SERVICEREQUEST_H
#define SERVICEREQUEST_H

#include <string>

class ServiceRequest
{
private:
    std::string requestId;
    long long requesterId;
    std::string requesterType;
    std::string category;
    std::string location;
    std::string description;
    std::string submissionDateTime;
    std::string status;

public:
    ServiceRequest();

    ServiceRequest(const std::string &requestId,
                   long long requesterId,
                   const std::string &requesterType,
                   const std::string &category,
                   const std::string &location,
                   const std::string &description,
                   const std::string &submissionDateTime);

    std::string getRequestId() const;
    long long getRequesterId() const;
    std::string getRequesterType() const;
    std::string getCategory() const;
    std::string getLocation() const;
    std::string getDescription() const;
    std::string getSubmissionDateTime() const;
    std::string getStatus() const;

    bool editPendingRequest(const std::string &category,
                            const std::string &location,
                            const std::string &description);

    bool cancelPendingRequest();

    bool updateStatus(const std::string &newStatus);

    void display() const;
};

#endif