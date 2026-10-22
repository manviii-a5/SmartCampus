#include "../include/Student.h"
#include <iostream>

Student::Student()
{
    studentId = 0;
    semester = 0;
}

Student::Student(long long studentId,
                 const std::string &name,
                 const std::string &course,
                 const std::string &branch,
                 int semester,
                 const std::string &email,
                 const std::string &phone,
                 const std::string &password)
{
    this->studentId = studentId;
    this->name = name;
    this->course = course;
    this->branch = branch;
    this->semester = semester;
    this->email = email;
    this->phone = phone;
    this->password = password;
}

long long Student::getStudentId() const
{
    return studentId;
}

std::string Student::getName() const
{
    return name;
}

std::string Student::getCourse() const
{
    return course;
}

std::string Student::getBranch() const
{
    return branch;
}

int Student::getSemester() const
{
    return semester;
}

std::string Student::getEmail() const
{
    return email;
}

std::string Student::getPhone() const
{
    return phone;
}

std::string Student::getPassword() const
{
    return password;
}

void Student::setEmail(const std::string &email)
{
    this->email = email;
}

void Student::setPhone(const std::string &phone)
{
    this->phone = phone;
}

void Student::setPassword(const std::string &password)
{
    this->password = password;
}

bool Student::checkPassword(const std::string &password) const
{
    return this->password == password;
}

void Student::displayProfile() const
{
    std::cout << "\n========== STUDENT PROFILE ==========\n";
    std::cout << "Student ID : " << studentId << '\n';
    std::cout << "Name       : " << name << '\n';
    std::cout << "Course     : " << course << '\n';
    std::cout << "Branch     : " << branch << '\n';
    std::cout << "Semester   : " << semester << '\n';
    std::cout << "Email      : " << email << '\n';
    std::cout << "Phone      : " << phone << '\n';
}