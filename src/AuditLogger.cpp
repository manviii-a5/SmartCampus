#include "AuditLogger.h"
#include <fstream>
#include <ctime>
#include <mutex>
#include <cerrno>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif
namespace AuditLogger
{
    namespace
    {
        std::mutex logMutex;
    }
    bool initialize()
    {
#ifdef _WIN32
        if (_mkdir("logs") != 0 && errno != EEXIST)
            return false;
#else
        if (mkdir("logs", 0755) != 0 && errno != EEXIST)
            return false;
#endif
        std::ofstream f("logs/smartcampus.log", std::ios::app);
        if (!f)
            return false;
        log("INFO", "Application logging initialized");
        return true;
    }
    void log(const std::string &level, const std::string &message)
    {
        std::lock_guard<std::mutex> lock(logMutex);
        std::ofstream f("logs/smartcampus.log", std::ios::app);
        if (!f)
            return;
        std::time_t now = std::time(nullptr);
        std::tm tmv{};
#ifdef _WIN32
        localtime_s(&tmv, &now);
#else
        localtime_r(&now, &tmv);
#endif
        char stamp[32];
        std::strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", &tmv);
        std::string safe = message;
        for (char &c : safe)
            if (c == '\n' || c == '\r')
                c = ' ';
        f << stamp << " [" << level << "] " << safe << '\n';
    }
}
