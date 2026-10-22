#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student
{
private:
    long long studentId;
    std::string name;
    std::string course;
    std::string branch;
    int semester;
    std::string email;
    std::string phone;
    std::string password;

public:
    Student();

    Student(long long studentId,
            const std::string &name,
            const std::string &course,
            const std::string &branch,
            int semester,
            const std::string &email,
            const std::string &phone,
            const std::string &password);

    long long getStudentId() const;
    std::string getName() const;
    std::string getCourse() const;
    std::string getBranch() const;
    int getSemester() const;
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