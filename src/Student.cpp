#include <iostream>
#include "Student.h"

Student::Student()
{
    studentId = 0;
    name = "";
    course = "";
    branch = "";
    semester = 0;
}

Student::Student(
    int studentId,
    const std::string& name,
    const std::string& course,
    const std::string& branch,
    int semester
)
{
    this->studentId = studentId;
    this->name = name;
    this->course = course;
    this->branch = branch;
    this->semester = semester;
}

int Student::getStudentId() const
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

void Student::display() const
{
    std::cout << "Student ID : " << studentId << "\n";
    std::cout << "Name       : " << name << "\n";
    std::cout << "Course     : " << course << "\n";
    std::cout << "Branch     : " << branch << "\n";
    std::cout << "Semester   : " << semester << "\n";
}