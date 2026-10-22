#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>

class Authentication
{
private:
    int failedAttempts;
    static const int MAX_ATTEMPTS = 3;

public:
    Authentication();

    bool validatePasswordPolicy(const std::string &password) const;

    void recordFailedAttempt();

    void resetAttempts();

    bool hasAttemptsRemaining() const;

    int getRemainingAttempts() const;

    bool verifyAdminPassword(const std::string &password) const;
};

#endif