#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <string>
#include <vector>

#include "Student.h"

namespace StudentManager
{
    // Load student records from persistent storage.
    bool loadStudents();

    // Save all student records to persistent storage.
    bool saveStudents();

    // Register a new student.
    bool registerStudent(const Student &student);

    // Find a student using their ID.
    Student *findStudent(long long studentId);

    // Check whether a student ID already exists.
    bool studentExists(long long studentId);

    // Display all registered students.
    void displayAllStudents();

    // Display a particular student's profile.
    void displayStudentProfile(long long studentId);

    // Return the number of registered students.
    int getStudentCount();
}

#endif