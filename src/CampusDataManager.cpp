#include "CampusDataManager.h"
#include "Building.h"
#include "Room.h"
#include "FileManager.h"
#include "AuditLogger.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>
#include <cctype>

namespace
{
    const char *BUILDINGS_FILE = "data/buildings.txt";
    const char *ROOMS_FILE = "data/rooms.txt";
    const char *RESOURCES_FILE = "data/resources.txt";
    std::vector<Building> buildings;
    std::vector<Room> rooms;
    std::string clean(std::string s)
    {
        std::replace(s.begin(), s.end(), '|', '/');
        std::replace(s.begin(), s.end(), '\n', ' ');
        std::replace(s.begin(), s.end(), '\r', ' ');
        return s;
    }
    std::string ask(const std::string &prompt)
    {
        std::string s;
        do
        {
            std::cout << prompt;
            std::getline(std::cin, s);
            if (s.empty())
                std::cout << "This field cannot be empty.\n";
        } while (s.empty());
        return clean(s);
    }
    int number(const std::string &prompt, int min, int max)
    {
        for (;;)
        {
            std::cout << prompt;
            int n;
            if (std::cin >> n && n >= min && n <= max)
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return n;
            }
            std::cout << "Enter a number from " << min << " to " << max << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    bool saveBuildings()
    {
        std::vector<std::string> out;
        for (const auto &b : buildings)
        {
            std::ostringstream s;
            s << b.getBuildingId() << '|' << clean(b.getName()) << '|' << clean(b.getType()) << '|' << (b.getHasBasement() ? 1 : 0) << '|' << b.getNumberOfFloors() << '|' << b.getStatus() << '|' << clean(b.getAlias());
            out.push_back(s.str());
        }
        bool primarySaved = FileManager::saveRecords(BUILDINGS_FILE, out);
        // Keep the singular filename requested by the project documentation in sync as a compatibility copy.
        bool compatibilitySaved = FileManager::saveRecords("data/building.txt", out);
        return primarySaved && compatibilitySaved;
    }
    bool saveRooms()
    {
        std::vector<std::string> out;
        for (const auto &r : rooms)
        {
            std::ostringstream s;
            s << r.getRoomId() << '|' << r.getBuildingId() << '|' << clean(r.getFloor()) << '|' << clean(r.getRoomNumber()) << '|' << clean(r.getRoomType()) << '|' << r.getCapacity() << '|' << r.getStatus();
            out.push_back(s.str());
        }
        return FileManager::saveRecords(ROOMS_FILE, out);
    }
    int nextBuildingId()
    {
        int n = 1;
        for (const auto &b : buildings)
            n = std::max(n, b.getBuildingId() + 1);
        return n;
    }
    int nextRoomId()
    {
        int n = 1;
        for (const auto &r : rooms)
            n = std::max(n, r.getRoomId() + 1);
        return n;
    }
    Building *findBuilding(int id)
    {
        for (auto &b : buildings)
            if (b.getBuildingId() == id)
                return &b;
        return nullptr;
    }
    std::string resourceTypeForRoom(const std::string &roomType)
    {
        std::string t = roomType;
        std::transform(t.begin(), t.end(), t.begin(), [](unsigned char c)
                       { return static_cast<char>(std::tolower(c)); });
        if (t == "classroom" || t == "examination hall")
            return "Classroom";
        if (t == "computer lab")
            return "Computer Lab";
        if (t == "laboratory")
            return "Laboratory";
        if (t == "seminar hall" || t == "seminar room")
            return "Seminar Hall";
        if (t == "conference room")
            return "Conference Room";
        if (t == "auditorium")
            return "Auditorium";
        if (t == "library room")
            return "Library Facility";
        if (t == "sports room")
            return "Sports Facility";
        if (t == "medical room")
            return "Medical Facility";
        return "Other";
    }
    std::string nextResourceId()
    {
        std::vector<std::string> records;
        FileManager::readRecords(RESOURCES_FILE, records);
        int n = 1;
        for (const auto &line : records)
        {
            auto f = FileManager::splitRecord(line);
            if (!f.empty() && f[0].size() > 1 && f[0][0] == 'R')
            {
                try
                {
                    n = std::max(n, std::stoi(f[0].substr(1)) + 1);
                }
                catch (...)
                {
                }
            }
        }
        std::ostringstream out;
        out << 'R';
        out.width(4);
        out.fill('0');
        out << n;
        return out.str();
    }
    bool syncRoomResource(const Room &r)
    {
        if (!FileManager::ensureFileExists(RESOURCES_FILE))
            return false;
        std::vector<std::string> records;
        if (!FileManager::readRecords(RESOURCES_FILE, records))
            return false;
        const std::string marker = "ROOMID:" + std::to_string(r.getRoomId());
        for (const auto &line : records)
        {
            auto f = FileManager::splitRecord(line);
            if (f.size() >= 6 && f[5] == marker)
                return true;
        }
        Building *b = findBuilding(r.getBuildingId());
        std::string buildingName = b ? b->getName() : ("Building ID " + std::to_string(r.getBuildingId()));
        std::string location = clean(buildingName + ", Floor " + r.getFloor() + ", Room " + r.getRoomNumber());
        std::string status = "AVAILABLE";
        std::string rt = resourceTypeForRoom(r.getRoomType());
        if (r.getRoomType() == "Faculty Room" || r.getRoomType() == "Department Office" || r.getRoomType() == "Store Room")
            status = "UNAVAILABLE";
        std::string row = nextResourceId() + "|" + clean(r.getRoomNumber()) + " - " + clean(r.getRoomType()) + "|" + rt + "|" + location + "|" + status + "|" + marker;
        records.push_back(row);
        return FileManager::saveRecords(RESOURCES_FILE, records);
    }
}
namespace CampusDataManager
{
    bool initialize()
    {
        if (!FileManager::ensureDataDirectory())
            return false;
        if (!FileManager::ensureFileExists(BUILDINGS_FILE) || !FileManager::ensureFileExists(ROOMS_FILE))
            return false;
        std::vector<std::string> rec;
        if (!FileManager::readRecords(BUILDINGS_FILE, rec))
            return false;
        buildings.clear();
        for (const auto &line : rec)
        {
            auto f = FileManager::splitRecord(line);
            if (f.size() < 7)
                continue;
            try
            {
                buildings.emplace_back(std::stoi(f[0]), f[1], f[2], f[3] == "1", std::stoi(f[4]), f[5], f[6]);
            }
            catch (...)
            {
            }
        }
        struct Seed
        {
            const char *name;
            const char *type;
            const char *alias;
        };
        const Seed seed[] = {
            {"B.Tech Block", "Academic", ""}, {"K. P. Nautiyal Block", "Academic", "Department of Hotel Management"}, {"Chanakya Block", "Academic", "Department of Management Studies"}, {"New Management Block (Under Construction)", "Academic", ""}, {"Department of Mechanical and Automobile Engineering", "Academic", ""}, {"Department of Petroleum Engineering", "Academic", ""}, {"Department of Allied Science", "Academic", ""}, {"Department of Electrical Engineering", "Academic", ""}, {"Civil Block", "Academic", ""}, {"Paramedical Block", "Academic", ""}, {"CSIT Block", "Academic", ""}, {"New CSIT Block", "Academic", ""}, {"GEU Block", "Academic", ""}, {"Aryabhatt Computer Lab", "Laboratory", ""}, {"Param Computer Lab", "Laboratory", ""}, {"Santosh Anand Library", "Library", ""}, {"Chancellor's Residence", "Residential", ""}, {"President House", "Residential", ""}, {"Guest House - Location 1", "Residential", ""}, {"Guest House - Location 2", "Residential", ""}, {"Security", "Administration", ""}, {"Priyadarshini Girls Hostel", "Hostel", ""}, {"Sarojani Girls Hostel", "Hostel", ""}, {"Laxmi Bai Hostel", "Hostel", ""}, {"Sardar Patel Hostel", "Hostel", ""}, {"Chandra Shekhar Hostel", "Hostel", ""}, {"Dispensary", "Facility", ""}, {"Tuckshop", "Facility", ""}, {"Canteen 1", "Food Facility", ""}, {"Canteen 2", "Food Facility", ""}, {"Canteen 3", "Food Facility", ""}, {"Ravi Canteen", "Food Facility", ""}, {"Happiness Hut Cafe", "Food Facility", ""}, {"Vidyarthi Store", "Shop", ""}, {"Basketball Court", "Sports", ""}, {"Badminton Court", "Sports", ""}, {"Play Ground", "Sports", ""}, {"Park 1", "Outdoor", ""}, {"Park 2", "Outdoor", ""}, {"Park 3", "Outdoor", ""}, {"Fountain", "Landmark", ""}, {"Statue", "Landmark", ""}, {"Gate 1", "Entrance", ""}, {"Gate 2", "Entrance", ""}, {"Subway", "Access", ""}, {"Water Point", "Facility", "Map label: Water"}, {"Parking - Location 1", "Parking", ""}, {"Parking - Location 2", "Parking", ""}, {"Unidentified Construction Site", "Construction", "Map does not specify a building name"}};
        bool buildingsChanged = false;
        for (const auto &item : seed)
        {
            bool found = false;
            for (const auto &b : buildings)
                if (b.getName() == item.name)
                {
                    found = true;
                    break;
                }
            if (!found)
            {
                buildings.emplace_back(nextBuildingId(), item.name, item.type, false, 0, "ACTIVE", item.alias);
                buildingsChanged = true;
            }
        }
        // Always persist the merged catalogue, including when buildings.txt already existed but was incomplete.
        if (!saveBuildings())
        {
            AuditLogger::log("ERROR", "Failed saving building catalogue files");
            return false;
        }
        if (buildingsChanged || rec.empty())
            AuditLogger::log("INFO", "Seeded/updated data/buildings.txt with campus locations");
        if (!FileManager::readRecords(ROOMS_FILE, rec))
            return false;
        rooms.clear();
        for (const auto &line : rec)
        {
            auto f = FileManager::splitRecord(line);
            if (f.size() < 7)
                continue;
            try
            {
                rooms.emplace_back(std::stoi(f[0]), std::stoi(f[1]), f[2], f[3], f[4], std::stoi(f[5]), f[6]);
            }
            catch (...)
            {
            }
        }
        if (!FileManager::ensureFileExists(RESOURCES_FILE))
            return false;
        for (const auto &room : rooms)
            if (!syncRoomResource(room))
            {
                AuditLogger::log("ERROR", "Failed syncing room to resource catalogue; room ID=" + std::to_string(room.getRoomId()));
                return false;
            }
        AuditLogger::log("INFO", "Campus data initialized; buildings=" + std::to_string(buildings.size()) + ", rooms=" + std::to_string(rooms.size()));
        return true;
    }
    void listBuildings()
    {
        // Reload from disk when the menu is opened so the list cannot remain stale.
        std::vector<std::string> records;
        if (FileManager::readRecords(BUILDINGS_FILE, records))
        {
            std::vector<Building> loaded;
            for (const auto &line : records)
            {
                auto f = FileManager::splitRecord(line);
                if (f.size() < 7)
                    continue;
                try
                {
                    loaded.emplace_back(std::stoi(f[0]), f[1], f[2], f[3] == "1", std::stoi(f[4]), f[5], f[6]);
                }
                catch (...)
                {
                    AuditLogger::log("WARN", "Skipped malformed building record: " + line);
                }
            }
            if (!loaded.empty())
                buildings.swap(loaded);
        }
        if (buildings.empty())
        {
            std::cout << "\nNo buildings loaded. Attempting to initialize predefined campus locations...\n";
            if (!initialize())
            {
                std::cout << "ERROR: Could not initialize campus data. Check that data/buildings.txt is writable and run the program from its project folder.\n";
                AuditLogger::log("ERROR", "Building list requested but initialization failed");
                return;
            }
        }
        std::cout << "\n========== CAMPUS BUILDINGS / LOCATIONS ==========\n";
        for (const auto &b : buildings)
        {
            std::cout << "ID: " << b.getBuildingId() << " | " << b.getName() << " | Type: " << b.getType();
            if (!b.getAlias().empty())
                std::cout << " | Alias: " << b.getAlias();
            std::cout << " | Floors recorded: " << b.getNumberOfFloors() << "\n";
        }
        std::cout << "Total: " << buildings.size() << " locations\n";
        AuditLogger::log("INFO", "Building list displayed; count=" + std::to_string(buildings.size()));
    }
    void addBuilding()
    {
        std::string name = ask("Building/location name: "), type = ask("Type (Academic/Hostel/Facility/etc.): ");
        int basement = number("Has basement? (0 No, 1 Yes): ", 0, 1);
        int floors = number("Number of above-ground floors (0 if unknown): ", 0, 100);
        std::string alias;
        std::cout << "Alias (press Enter to skip): ";
        std::getline(std::cin, alias);
        alias = clean(alias);
        buildings.emplace_back(nextBuildingId(), name, type, basement == 1, floors, "ACTIVE", alias);
        if (saveBuildings())
        {
            AuditLogger::log("INFO", "Building saved; ID=" + std::to_string(buildings.back().getBuildingId()) + "; name=" + name);
            std::cout << "Building/location saved. ID: " << buildings.back().getBuildingId() << "\n";
        }
        else
        {
            buildings.pop_back();
            AuditLogger::log("ERROR", "Failed to persist building/location record");
            std::cout << "Could not save building. Check data folder permissions.\n";
        }
    }
    void listRooms()
    {
        std::cout << "\n========== ROOMS ==========\n";
        if (rooms.empty())
        {
            std::cout << "No room records have been added yet.\n";
            return;
        }
        for (const auto &r : rooms)
        {
            r.display();
            Building *b = findBuilding(r.getBuildingId());
            if (b)
                std::cout << "Building name: " << b->getName() << "\n";
        }
        std::cout << "Total rooms: " << rooms.size() << "\n";
    }
    void addRoom()
    {
        listBuildings();
        int bid = number("Enter building ID for this room: ", 1, 10000);
        Building *b = findBuilding(bid);
        if (!b)
        {
            std::cout << "Invalid building ID. Room not added.\n";
            return;
        }
        std::string floor = ask("Floor (Basement/Ground/1st/2nd etc.): ");
        std::string roomNo = ask("Room number/name: ");
        for (const auto &r : rooms)
            if (r.getBuildingId() == bid && r.getFloor() == floor && r.getRoomNumber() == roomNo)
            {
                std::cout << "That room already exists in this building and floor.\n";
                return;
            }
        const char *roomTypes[] = {"Classroom", "Computer Lab", "Laboratory", "Seminar Hall", "Conference Room", "Auditorium", "Faculty Room", "Department Office", "Library Room", "Examination Hall", "Sports Room", "Store Room", "Medical Room", "Other"};
        std::cout << "\nSelect Room Type:\n";
        for (int i = 0; i < 14; ++i)
            std::cout << i + 1 << ". " << roomTypes[i] << "\n";
        int typeChoice = number("Enter room type option (1-14): ", 1, 14);
        std::string type = roomTypes[typeChoice - 1];
        int cap = number("Capacity (0 if unknown): ", 0, 10000);
        rooms.emplace_back(nextRoomId(), bid, floor, roomNo, type, cap, "AVAILABLE");
        if (saveRooms() && syncRoomResource(rooms.back()))
        {
            AuditLogger::log("INFO", "Room saved and synchronized as a resource; ID=" + std::to_string(rooms.back().getRoomId()) + "; building ID=" + std::to_string(bid));
            std::cout << "Room saved. Generated Room ID: " << rooms.back().getRoomId() << "\n";
            std::cout << "Resource automatically created. Resource type: " << resourceTypeForRoom(rooms.back().getRoomType()) << "\n";
            if (type == "Faculty Room" || type == "Department Office" || type == "Store Room")
                std::cout << "Booking is disabled by default for this room type; an administrator can enable it in Resource Management.\n";
        }
        else
        {
            rooms.pop_back();
            saveRooms();
            AuditLogger::log("ERROR", "Failed to persist room record or synchronize its resource");
            std::cout << "Could not save room/resource. Check data folder permissions and try again.\n";
        }
    }
    void searchRoom()
    {
        std::string key = ask("Enter room number/name to search: ");
        bool found = false;
        for (const auto &r : rooms)
            if (r.getRoomNumber() == key || r.getRoomNumber().find(key) != std::string::npos)
            {
                r.display();
                Building *b = findBuilding(r.getBuildingId());
                if (b)
                    std::cout << "Building name: " << b->getName() << "\n";
                found = true;
            }
        if (!found)
            std::cout << "No matching room found. Room data can be added by the administrator.\n";
    }
    void listRoomsForBuilding(int id)
    {
        for (const auto &r : rooms)
            if (r.getBuildingId() == id)
            {
                r.display();
            }
    }
}
