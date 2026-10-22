#include "../include/Authentication.h"
#include <cctype>

Authentication::Authentication()
{
    failedAttempts = 0;
}

bool Authentication::validatePasswordPolicy(
    const std::string &password) const
{
    if (password.length() < 8)
        return false;

    bool uppercase = false;
    bool lowercase = false;
    bool digit = false;
    bool special = false;

    for (std::string::size_type i = 0; i < password.length(); i++)
    {
        unsigned char ch = static_cast<unsigned char>(password[i]);

        if (std::isupper(ch))
            uppercase = true;
        else if (std::islower(ch))
            lowercase = true;
        else if (std::isdigit(ch))
            digit = true;
        else
            special = true;
    }

    return uppercase && lowercase && digit && special;
}

void Authentication::recordFailedAttempt()
{
    if (failedAttempts < MAX_ATTEMPTS)
        failedAttempts++;
}

void Authentication::resetAttempts()
{
    failedAttempts = 0;
}

bool Authentication::hasAttemptsRemaining() const
{
    return failedAttempts < MAX_ATTEMPTS;
}

int Authentication::getRemainingAttempts() const
{
    return MAX_ATTEMPTS - failedAttempts;
}

bool Authentication::verifyAdminPassword(
    const std::string &password) const
{
    return password == "CampusAdmin@MDSA";
}