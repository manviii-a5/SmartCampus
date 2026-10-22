#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>

class Administrator
{
private:
    std::string adminName;

public:
    Administrator();
    explicit Administrator(const std::string &adminName);

    std::string getAdminName() const;

    void setAdminName(const std::string &adminName);

    void displayProfile() const;
};

#endif