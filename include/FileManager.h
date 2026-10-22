#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

namespace FileManager
{
    bool ensureDataDirectory();

    bool ensureFileExists(const std::string &filename);

    bool appendRecord(
        const std::string &filename,
        const std::string &record);

    bool readRecords(
        const std::string &filename,
        std::vector<std::string> &records);

    bool saveRecords(
        const std::string &filename,
        const std::vector<std::string> &records);

    bool fileExists(const std::string &filename);

    bool isValidRecord(const std::string &record);

    std::vector<std::string> splitRecord(
        const std::string &record,
        char delimiter = '|');

    std::string joinRecord(
        const std::vector<std::string> &fields,
        char delimiter = '|');
}

#endif