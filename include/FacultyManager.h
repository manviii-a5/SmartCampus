#ifndef FACULTYMANAGER_H
#define FACULTYMANAGER_H

#include <string>

#include "Faculty.h"

namespace FacultyManager
{
    bool loadFaculty();

    bool saveFaculty();

    bool registerFaculty(const Faculty &faculty);

    Faculty *findFaculty(long long facultyId);

    bool facultyExists(long long facultyId);

    void displayAllFaculty();

    void displayFacultyProfile(long long facultyId);

    int getFacultyCount();
}

#endif