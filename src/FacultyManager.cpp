#include "FacultyManager.h"
#include "FileManager.h"
#include "AuditLogger.h"

#include <iostream>
#include <sstream>
#include <map>
#include <vector>

namespace
{
    std::map<long long, Faculty> facultyRecords;

    const std::string FACULTY_FILE = "data/faculty.txt";

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

    std::string serializeFaculty(const Faculty &faculty)
    {
        std::ostringstream output;

        output << faculty.getFacultyId() << '|'
               << encodeField(faculty.getName()) << '|'
               << encodeField(faculty.getDepartment()) << '|'
               << encodeField(faculty.getDesignation()) << '|'
               << encodeField(faculty.getEmail()) << '|'
               << encodeField(faculty.getPhone()) << '|'
               << encodeField(faculty.getPassword());

        return output.str();
    }

    bool parsePositiveInteger(const std::string &input, long long &value)
    {
        if (input.empty())
            return false;

        value = 0;

        for (std::string::size_type i = 0; i < input.length(); i++)
        {
            char ch = input[i];

            if (ch < '0' || ch > '9')
                return false;

            int digit = ch - '0';

            if (value > (9223372036854775807LL - digit) / 10)
                return false;

            value = value * 10 + digit;
        }

        return value > 0;
    }

    bool parseFaculty(const std::string &record, Faculty &faculty)
    {
        std::vector<std::string> fields =
            FileManager::splitRecord(record);

        if (fields.size() != 7)
            return false;

        long long id = 0;

        if (!parsePositiveInteger(fields[0], id))
            return false;

        faculty = Faculty(
            id,
            fields[1],
            fields[2],
            fields[3],
            fields[4],
            fields[5],
            fields[6]);

        return true;
    }
}

namespace FacultyManager
{
    bool loadFaculty()
    {
        if (!FileManager::ensureDataDirectory())
            return false;

        if (!FileManager::ensureFileExists(FACULTY_FILE))
            return false;

        std::vector<std::string> records;

        if (!FileManager::readRecords(FACULTY_FILE, records))
            return false;

        facultyRecords.clear();

        for (std::size_t i = 0; i < records.size(); i++)
        {
            Faculty faculty;

            if (!parseFaculty(records[i], faculty))
            {
                std::cerr << "Warning: Invalid faculty record skipped.\n";
                continue;
            }

            long long id = faculty.getFacultyId();

            if (facultyRecords.find(id) != facultyRecords.end())
            {
                std::cerr << "Warning: Duplicate faculty ID skipped: "
                          << id << '\n';
                continue;
            }

            facultyRecords.insert(std::make_pair(id, faculty));
        }

        return true;
    }

    bool saveFaculty()
    {
        if (!FileManager::ensureDataDirectory())
            return false;

        std::vector<std::string> records;

        std::map<long long, Faculty>::const_iterator it;

        for (it = facultyRecords.begin(); it != facultyRecords.end(); ++it)
        {
            std::string record = serializeFaculty(it->second);

            if (record.empty())
            {
                std::cerr << "Error: Faculty record contains invalid characters.\n";
                return false;
            }

            records.push_back(record);
        }

        return FileManager::saveRecords(FACULTY_FILE, records);
    }

    bool registerFaculty(const Faculty &faculty)
    {
        long long id = faculty.getFacultyId();

        if (id <= 0)
        {
            std::cout << "Invalid faculty ID.\n";
            return false;
        }

        if (facultyRecords.find(id) != facultyRecords.end())
        {
            std::cout << "Faculty ID already exists.\n";
            return false;
        }

        std::string record = serializeFaculty(faculty);

        if (record.empty())
        {
            std::cout << "Faculty details contain unsupported characters.\n";
            return false;
        }

        facultyRecords.insert(std::make_pair(id, faculty));

        if (!saveFaculty())
        {
            facultyRecords.erase(id);
            std::cout << "Could not save faculty record.\n";
            return false;
        }

        AuditLogger::log("INFO", "Faculty record persisted; ID=" + std::to_string(id));
        std::cout << "Faculty registered successfully.\n";
        return true;
    }

    Faculty *findFaculty(long long facultyId)
    {
        std::map<long long, Faculty>::iterator it =
            facultyRecords.find(facultyId);

        if (it == facultyRecords.end())
            return NULL;

        return &(it->second);
    }

    bool facultyExists(long long facultyId)
    {
        return facultyRecords.find(facultyId) != facultyRecords.end();
    }

    void displayAllFaculty()
    {
        if (facultyRecords.empty())
        {
            std::cout << "No faculty records found.\n";
            return;
        }

        std::map<long long, Faculty>::const_iterator it;

        for (it = facultyRecords.begin(); it != facultyRecords.end(); ++it)
        {
            it->second.displayProfile();
            std::cout << "-----------------------------\n";
        }
    }

    void displayFacultyProfile(long long facultyId)
    {
        Faculty *faculty = findFaculty(facultyId);

        if (faculty == NULL)
        {
            std::cout << "Faculty member not found.\n";
            return;
        }

        faculty->displayProfile();
    }

    int getFacultyCount()
    {
        return static_cast<int>(facultyRecords.size());
    }
}