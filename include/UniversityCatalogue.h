#ifndef UNIVERSITYCATALOGUE_H
#define UNIVERSITYCATALOGUE_H

#include <string>
#include <vector>

namespace UniversityCatalogue
{
    struct Program
    {
        std::string course;
        std::string branch;
        std::string level;
        int maximumSemester;
    };

    const std::vector<Program> &getPrograms();

    std::vector<std::string> getCourses();

    std::vector<std::string> getBranches(const std::string &course);

    bool isValidCourse(const std::string &course);

    bool isValidBranch(
        const std::string &course,
        const std::string &branch);

    int getMaximumSemester(
        const std::string &course,
        const std::string &branch);

    std::string getProgramLevel(
        const std::string &course,
        const std::string &branch);
}

#endif