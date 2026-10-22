#include "StudentManager.h"
#include "FileManager.h"
#include "AuditLogger.h"

#include <iostream>
#include <sstream>
#include <map>

namespace
{
    std::map<long long, Student> students;

    const std::string STUDENT_FILE = "data/students.txt";

    std::string encodeField(const std::string &value)
    {
        std::string encoded;

        for (std::string::size_type i = 0; i < value.length(); i++)
        {
            if (value[i] == '|' ||
                value[i] == '\n' ||
                value[i] == '\r')
            {
                return "";
            }

            encoded += value[i];
        }

        return encoded;
    }

    std::string serializeStudent(const Student &student)
    {
        std::ostringstream output;

        output << student.getStudentId() << '|'
               << encodeField(student.getName()) << '|'
               << encodeField(student.getCourse()) << '|'
               << encodeField(student.getBranch()) << '|'
               << student.getSemester() << '|'
               << encodeField(student.getEmail()) << '|'
               << encodeField(student.getPhone()) << '|'
               << encodeField(student.getPassword());

        return output.str();
    }

    bool parseStudent(const std::string &record, Student &student)
    {
        std::vector<std::string> fields =
            FileManager::splitRecord(record);

        if (fields.size() != 8)
            return false;

        try
        {
            long long id = 0;

            if (fields[0].empty())
                return false;

            for (std::string::size_type i = 0; i < fields[0].length(); i++)
            {
                char ch = fields[0][i];

                if (ch < '0' || ch > '9')
                    return false;

                int digit = ch - '0';

                if (id > (9223372036854775807LL - digit) / 10)
                    return false;

                id = id * 10 + digit;
            }

            if (id <= 0)
                return false;

            int semester = 0;

            if (fields[4].empty())
                return false;

            for (std::string::size_type i = 0; i < fields[4].length(); i++)
            {
                char ch = fields[4][i];

                if (ch < '0' || ch > '9')
                    return false;

                int digit = ch - '0';

                if (semester > (2147483647 - digit) / 10)
                    return false;

                semester = semester * 10 + digit;
            }

            if (semester <= 0)
                return false;

            student = Student(
                id,
                fields[1],
                fields[2],
                fields[3],
                semester,
                fields[5],
                fields[6],
                fields[7]);

            return true;
        }
        catch (...)
        {
            return false;
        }
    }
}

namespace StudentManager
{
    bool loadStudents()
    {
        if (!FileManager::ensureDataDirectory())
            return false;

        if (!FileManager::ensureFileExists(STUDENT_FILE))
            return false;

        std::vector<std::string> records;

        if (!FileManager::readRecords(STUDENT_FILE, records))
            return false;

        students.clear();

        for (std::size_t i = 0; i < records.size(); i++)
        {
            Student student;

            if (!parseStudent(records[i], student))
            {
                std::cerr << "Warning: Invalid student record skipped.\n";
                continue;
            }

            long long id = student.getStudentId();

            if (students.find(id) != students.end())
            {
                std::cerr << "Warning: Duplicate student ID skipped: "
                          << id << '\n';
                continue;
            }

            students.insert(std::make_pair(id, student));
        }

        return true;
    }

    bool saveStudents()
    {
        if (!FileManager::ensureDataDirectory())
            return false;

        std::vector<std::string> records;

        std::map<long long, Student>::const_iterator it;

        for (it = students.begin(); it != students.end(); ++it)
        {
            std::string record = serializeStudent(it->second);

            if (record.empty())
            {
                std::cerr << "Error: Student record contains invalid characters.\n";
                return false;
            }

            records.push_back(record);
        }

        return FileManager::saveRecords(STUDENT_FILE, records);
    }

    bool registerStudent(const Student &student)
    {
        long long id = student.getStudentId();

        if (id <= 0)
        {
            std::cout << "Invalid student ID.\n";
            return false;
        }

        if (students.find(id) != students.end())
        {
            std::cout << "Student ID already exists.\n";
            return false;
        }

        std::string record = serializeStudent(student);

        if (record.empty())
        {
            std::cout << "Student details contain unsupported characters.\n";
            return false;
        }

        students.insert(std::make_pair(id, student));

        if (!saveStudents())
        {
            students.erase(id);
            std::cout << "Could not save student record.\n";
            return false;
        }

        AuditLogger::log("INFO", "Student record persisted; ID=" + std::to_string(id));
        std::cout << "Student registered successfully.\n";
        return true;
    }

    Student *findStudent(long long studentId)
    {
        std::map<long long, Student>::iterator it =
            students.find(studentId);

        if (it == students.end())
            return NULL;

        return &(it->second);
    }

    bool studentExists(long long studentId)
    {
        return students.find(studentId) != students.end();
    }

    void displayAllStudents()
    {
        if (students.empty())
        {
            std::cout << "No students registered.\n";
            return;
        }

        std::map<long long, Student>::const_iterator it;

        for (it = students.begin(); it != students.end(); ++it)
        {
            it->second.displayProfile();
            std::cout << "-----------------------------\n";
        }
    }

    void displayStudentProfile(long long studentId)
    {
        Student *student = findStudent(studentId);

        if (student == NULL)
        {
            std::cout << "Student not found.\n";
            return;
        }

        student->displayProfile();
    }

    int getStudentCount()
    {
        return static_cast<int>(students.size());
    }
}