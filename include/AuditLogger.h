#ifndef AUDIT_LOGGER_H
#define AUDIT_LOGGER_H
#include <string>
namespace AuditLogger
{
    bool initialize();
    void log(const std::string &level, const std::string &message);
}
#endif
