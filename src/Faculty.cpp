#include "../include/Faculty.h"
#include <iostream>

Faculty::Faculty()
{
    facultyId = 0;
}

Faculty::Faculty(long long facultyId,
                 const std::string &name,
                 const std::string &department,
                 const std::string &designation,
                 const std::string &email,
                 const std::string &phone,
                 const std::string &password)
{
    this->facultyId = facultyId;
    this->name = name;
    this->department = department;
    this->designation = designation;
    this->email = email;
    this->phone = phone;
    this->password = password;
}

long long Faculty::getFacultyId() const
{
    return facultyId;
}

std::string Faculty::getName() const
{
    return name;
}

std::string Faculty::getDepartment() const
{
    return department;
}

std::string Faculty::getDesignation() const
{
    return designation;
}

std::string Faculty::getEmail() const
{
    return email;
}

std::string Faculty::getPhone() const
{
    return phone;
}

std::string Faculty::getPassword() const
{
    return password;
}

void Faculty::setEmail(const std::string &email)
{
    this->email = email;
}

void Faculty::setPhone(const std::string &phone)
{
    this->phone = phone;
}

void Faculty::setPassword(const std::string &password)
{
    this->password = password;
}

bool Faculty::checkPassword(const std::string &password) const
{
    return this->password == password;
}

void Faculty::displayProfile() const
{
    std::cout << "\n========== FACULTY PROFILE ==========\n";
    std::cout << "Faculty ID  : " << facultyId << '\n';
    std::cout << "Name        : " << name << '\n';
    std::cout << "Department  : " << department << '\n';
    std::cout << "Designation : " << designation << '\n';
    std::cout << "Email       : " << email << '\n';
    std::cout << "Phone       : " << phone << '\n';
}