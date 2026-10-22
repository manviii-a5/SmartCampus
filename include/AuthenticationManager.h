#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <string>

namespace AuthenticationManager
{
    bool authenticateStudent(long long studentId,
                             const std::string &password);

    bool authenticateFaculty(long long facultyId,
                             const std::string &password);

    bool authenticateAdministrator(const std::string &password);
}

#endif