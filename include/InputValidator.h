#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>

namespace InputValidator
{
    long long getValidStudentId();

    std::string getValidStudentName();

    std::string getValidCourse();

    std::string getValidBranch(const std::string &course);

    int getValidSemester(int maximumSemester);

    std::string getValidBuildingName();

    std::string getValidBuildingType();

    std::string getNonEmptyString(const std::string &prompt);

    bool isValidStudentName(const std::string &name);

    bool isValidEmail(const std::string &email);

    bool isValidPhone(const std::string &phone);

    bool isValidPassword(const std::string &password);
}

#endif