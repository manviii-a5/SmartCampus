#include "../include/Booking.h"
#include <iostream>

Booking::Booking()
{
    requesterId = 0;
    resourceId = 0;
    status = "PENDING";
}

Booking::Booking(const std::string &bookingId,
                 long long requesterId,
                 const std::string &requesterType,
                 int resourceId,
                 const std::string &resourceName,
                 const std::string &date,
                 const std::string &startTime,
                 const std::string &endTime,
                 const std::string &status,
                 const std::string &requestTime)
{
    this->bookingId = bookingId;
    this->requesterId = requesterId;
    this->requesterType = requesterType;
    this->resourceId = resourceId;
    this->resourceName = resourceName;
    this->date = date;
    this->startTime = startTime;
    this->endTime = endTime;
    this->status = status;
    this->requestTime = requestTime;
}

std::string Booking::getBookingId() const { return bookingId; }
long long Booking::getRequesterId() const { return requesterId; }
std::string Booking::getRequesterType() const { return requesterType; }
int Booking::getResourceId() const { return resourceId; }
std::string Booking::getResourceName() const { return resourceName; }
std::string Booking::getDate() const { return date; }
std::string Booking::getStartTime() const { return startTime; }
std::string Booking::getEndTime() const { return endTime; }
std::string Booking::getStatus() const { return status; }
std::string Booking::getRequestTime() const { return requestTime; }

void Booking::setDate(const std::string &date)
{
    this->date = date;
}

void Booking::setStartTime(const std::string &startTime)
{
    this->startTime = startTime;
}

void Booking::setEndTime(const std::string &endTime)
{
    this->endTime = endTime;
}

void Booking::setStatus(const std::string &status)
{
    this->status = status;
}

bool Booking::isPending() const
{
    return status == "PENDING";
}

bool Booking::isApproved() const
{
    return status == "APPROVED";
}

bool Booking::isActive() const
{
    return status == "PENDING" ||
           status == "APPROVED" ||
           status == "CANCELLATION_PENDING";
}

void Booking::display() const
{
    std::cout << "\n========== BOOKING ==========\n";
    std::cout << "Booking ID    : " << bookingId << '\n';
    std::cout << "Requester ID  : " << requesterId << '\n';
    std::cout << "Requester Type: " << requesterType << '\n';
    std::cout << "Resource ID   : " << resourceId << '\n';
    std::cout << "Resource Name : " << resourceName << '\n';
    std::cout << "Date          : " << date << '\n';
    std::cout << "Start Time    : " << startTime << '\n';
    std::cout << "End Time      : " << endTime << '\n';
    std::cout << "Status        : " << status << '\n';
    std::cout << "Request Time  : " << requestTime << '\n';
}