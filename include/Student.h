#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student
{
private:
    int studentId;
    std::string name;
    std::string course;
    std::string branch;
    int semester;

public:
    
    Student();

   
    Student(
        int studentId,
        const std::string& name,
        const std::string& course,
        const std::string& branch,
        int semester
    );

    
    int getStudentId() const;
    std::string getName() const;
    std::string getCourse() const;
    std::string getBranch() const;
    int getSemester() const;

    
    void display() const;
};

#endif