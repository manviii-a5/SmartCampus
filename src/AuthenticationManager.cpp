#include "AuthenticationManager.h"

#include "StudentManager.h"
#include "FacultyManager.h"
#include "Authentication.h"

namespace AuthenticationManager
{
    bool authenticateStudent(long long studentId,
                             const std::string &password)
    {
        Student *student = StudentManager::findStudent(studentId);

        if (student == NULL)
            return false;

        return student->checkPassword(password);
    }

    bool authenticateFaculty(long long facultyId,
                             const std::string &password)
    {
        Faculty *faculty = FacultyManager::findFaculty(facultyId);

        if (faculty == NULL)
            return false;

        return faculty->checkPassword(password);
    }

    bool authenticateAdministrator(const std::string &password)
    {
        Authentication authentication;

        return authentication.verifyAdminPassword(password);
    }
}