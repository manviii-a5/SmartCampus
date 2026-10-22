#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking
{
private:
    std::string bookingId;
    long long requesterId;
    std::string requesterType;
    int resourceId;
    std::string resourceName;
    std::string date;
    std::string startTime;
    std::string endTime;
    std::string status;
    std::string requestTime;

public:
    Booking();

    Booking(const std::string &bookingId,
            long long requesterId,
            const std::string &requesterType,
            int resourceId,
            const std::string &resourceName,
            const std::string &date,
            const std::string &startTime,
            const std::string &endTime,
            const std::string &status,
            const std::string &requestTime);

    std::string getBookingId() const;
    long long getRequesterId() const;
    std::string getRequesterType() const;
    int getResourceId() const;
    std::string getResourceName() const;
    std::string getDate() const;
    std::string getStartTime() const;
    std::string getEndTime() const;
    std::string getStatus() const;
    std::string getRequestTime() const;

    void setDate(const std::string &date);
    void setStartTime(const std::string &startTime);
    void setEndTime(const std::string &endTime);
    void setStatus(const std::string &status);

    bool isPending() const;
    bool isApproved() const;
    bool isActive() const;

    void display() const;
};

#endif