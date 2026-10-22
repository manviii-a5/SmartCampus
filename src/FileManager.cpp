#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cerrno>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#endif

namespace FileManager
{
    bool ensureDataDirectory()
    {
#ifdef _WIN32
        if (_mkdir("data") == 0 || errno == EEXIST)
            return true;
#else
        if (mkdir("data", 0755) == 0 || errno == EEXIST)
            return true;
#endif
        std::cerr << "Error: Could not create data directory (data). errno=" << errno << "\n";
        return false;
    }

    bool fileExists(const std::string &filename)
    {
        std::ifstream file(filename.c_str());
        return file.good();
    }

    bool ensureFileExists(const std::string &filename)
    {
        if (fileExists(filename))
            return true;

        std::ofstream file(filename.c_str());

        if (!file)
        {
            std::cerr << "Error: Could not create file: "
                      << filename << '\n';
            return false;
        }

        return true;
    }

    bool isValidRecord(const std::string &record)
    {
        if (record.empty())
            return false;

        if (record.find('\n') != std::string::npos ||
            record.find('\r') != std::string::npos)
        {
            return false;
        }

        return true;
    }

    bool appendRecord(
        const std::string &filename,
        const std::string &record)
    {
        if (!isValidRecord(record))
        {
            std::cerr << "Error: Invalid record.\n";
            return false;
        }

        std::ofstream file(filename.c_str(), std::ios::app);

        if (!file)
        {
            std::cerr << "Error: Could not open file: "
                      << filename << '\n';
            return false;
        }

        file << record << '\n';
        file.flush();

        return file.good();
    }

    bool readRecords(
        const std::string &filename,
        std::vector<std::string> &records)
    {
        std::ifstream file(filename.c_str());

        if (!file)
        {
            std::cerr << "Error: Could not read file: "
                      << filename << '\n';
            return false;
        }

        records.clear();

        std::string line;

        while (std::getline(file, line))
        {
            // Ignore blank lines and comment/header lines in data files.
            if (line.empty() || line[0] == '#')
                continue;

            records.push_back(line);
        }

        if (file.bad())
        {
            std::cerr << "Error: I/O failure while reading file: " << filename << '\n';
            return false;
        }
        return true;
    }

    bool saveRecords(
        const std::string &filename,
        const std::vector<std::string> &records)
    {
        for (std::size_t i = 0; i < records.size(); i++)
        {
            if (!isValidRecord(records[i]))
            {
                std::cerr << "Error: Invalid record; saving cancelled.\n";
                return false;
            }
        }

        const std::string temporaryFile = filename + ".tmp";

        {
            std::ofstream file(
                temporaryFile.c_str(),
                std::ios::out | std::ios::trunc);

            if (!file)
            {
                std::cerr << "Error: Could not create temporary file.\n";
                return false;
            }

            for (std::size_t i = 0; i < records.size(); i++)
                file << records[i] << '\n';

            file.flush();

            if (!file.good())
            {
                std::cerr << "Error: Failed while writing records.\n";
                file.close();
                std::remove(temporaryFile.c_str());
                return false;
            }
        }

#ifdef _WIN32
        // Replace existing data files atomically on Windows as well.
        if (!MoveFileExA(temporaryFile.c_str(), filename.c_str(),
                         MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
        {
            std::cerr << "Error: Could not replace file: " << filename << '\n';
            std::remove(temporaryFile.c_str());
            return false;
        }
#else
        if (std::rename(temporaryFile.c_str(), filename.c_str()) != 0)
        {
            std::cerr << "Error: Could not replace file: " << filename << '\n';
            std::remove(temporaryFile.c_str());
            return false;
        }
#endif

        return true;
    }

    std::vector<std::string> splitRecord(
        const std::string &record,
        char delimiter)
    {
        std::vector<std::string> fields;
        std::stringstream stream(record);
        std::string field;

        while (std::getline(stream, field, delimiter))
            fields.push_back(field);

        if (!record.empty() && record[record.length() - 1] == delimiter)
            fields.push_back("");

        return fields;
    }

    std::string joinRecord(
        const std::vector<std::string> &fields,
        char delimiter)
    {
        std::string record;

        for (std::size_t i = 0; i < fields.size(); i++)
        {
            if (i > 0)
                record += delimiter;

            record += fields[i];
        }

        return record;
    }
}