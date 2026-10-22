#include "IDGenerator.h"
#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include <vector>

namespace
{
    std::map<std::string, unsigned long long> counters;

    const char *COUNTER_FILE = "data/id_counters.txt";

    std::string formatID(
        const std::string &prefix,
        unsigned long long number,
        int width)
    {
        std::ostringstream output;

        output << prefix
               << std::setw(width)
               << std::setfill('0')
               << number;

        return output.str();
    }

    bool saveCounters()
    {
        std::vector<std::string> records;

        std::map<std::string, unsigned long long>::const_iterator it;

        for (it = counters.begin(); it != counters.end(); ++it)
        {
            std::ostringstream line;

            line << it->first << "|" << it->second;

            records.push_back(line.str());
        }

        return FileManager::saveRecords(COUNTER_FILE, records);
    }
}

namespace IDGenerator
{
    bool initialize()
    {
        if (!FileManager::ensureDataDirectory())
            return false;

        if (!FileManager::ensureFileExists(COUNTER_FILE))
            return false;

        counters.clear();

        // Default counters.
        counters["BUILDING"] = 0;
        counters["ROOM"] = 0;
        counters["RESOURCE"] = 0;
        counters["BOOKING"] = 0;
        counters["EMERGENCY"] = 0;
        counters["SERVICE_REQUEST"] = 0;

        std::vector<std::string> records;

        if (!FileManager::readRecords(COUNTER_FILE, records))
            return false;

        for (std::size_t i = 0; i < records.size(); i++)
        {
            std::vector<std::string> fields =
                FileManager::splitRecord(records[i]);

            if (fields.size() != 2)
            {
                std::cerr << "Warning: Invalid ID counter record skipped.\n";
                continue;
            }

            std::istringstream input(fields[1]);
            unsigned long long value = 0;

            if (!(input >> value) || !input.eof())
            {
                std::cerr << "Warning: Invalid counter value skipped.\n";
                continue;
            }

            if (counters.find(fields[0]) != counters.end())
            {
                counters[fields[0]] = value;
            }
        }

        return saveCounters();
    }

    std::string generateBuildingID()
    {
        counters["BUILDING"]++;
        if (!saveCounters())
            return "";
        return formatID("BL", counters["BUILDING"], 3);
    }

    std::string generateRoomID()
    {
        counters["ROOM"]++;
        if (!saveCounters())
            return "";
        return formatID("RM", counters["ROOM"], 3);
    }

    std::string generateResourceID()
    {
        counters["RESOURCE"]++;
        if (!saveCounters())
            return "";
        return formatID("RS", counters["RESOURCE"], 3);
    }

    std::string generateBookingID()
    {
        counters["BOOKING"]++;
        if (!saveCounters())
            return "";
        return formatID("B", counters["BOOKING"], 4);
    }

    std::string generateEmergencyID()
    {
        counters["EMERGENCY"]++;
        if (!saveCounters())
            return "";
        return formatID("E", counters["EMERGENCY"], 4);
    }

    std::string generateServiceRequestID()
    {
        counters["SERVICE_REQUEST"]++;
        if (!saveCounters())
            return "";
        return formatID("SR", counters["SERVICE_REQUEST"], 4);
    }
}