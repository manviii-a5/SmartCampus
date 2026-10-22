#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <string>

namespace IDGenerator
{
    bool initialize();

    std::string generateBuildingID();
    std::string generateRoomID();
    std::string generateResourceID();
    std::string generateBookingID();
    std::string generateEmergencyID();
    std::string generateServiceRequestID();
}

#endif