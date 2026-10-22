#ifndef CAMPUS_SERVICES_H
#define CAMPUS_SERVICES_H
#include <string>
namespace CampusServices
{
    void userMenu(long long userId, const std::string &role);
    void adminResources();
    void adminBookings();
    void adminEmergencies();
    void adminServiceRequests();
}
#endif
