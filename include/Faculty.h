#ifndef FACULTY_H
#define FACULTY_H

#include <string>

class Faculty
{
private:
    long long facultyId;
    std::string name;
    std::string department;
    std::string designation;
    std::string email;
    std::string phone;
    std::string password;

public:
    Faculty();

    Faculty(long long facultyId,
            const std::string &name,
            const std::string &department,
            const std::string &designation,
            const std::string &email,
            const std::string &phone,
            const std::string &password);

    long long getFacultyId() const;
    std::string getName() const;
    std::string getDepartment() const;
    std::string getDesignation() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getPassword() const;

    void setEmail(const std::string &email);
    void setPhone(const std::string &phone);
    void setPassword(const std::string &password);

    bool checkPassword(const std::string &password) const;

    void displayProfile() const;
};

#endif