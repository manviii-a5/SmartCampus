#include "../include/Administrator.h"
#include <iostream>

Administrator::Administrator()
{
    adminName = "";
}

Administrator::Administrator(const std::string &adminName)
{
    this->adminName = adminName;
}

std::string Administrator::getAdminName() const
{
    return adminName;
}

void Administrator::setAdminName(const std::string &adminName)
{
    this->adminName = adminName;
}

void Administrator::displayProfile() const
{
    std::cout << "\n========== ADMINISTRATOR ==========\n";
    std::cout << "Admin Name: " << adminName << '\n';
}