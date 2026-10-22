#include "UniversityCatalogue.h"

#include <algorithm>
#include <cctype>

namespace
{
    std::string normalize(const std::string &value)
    {
        std::string result;

        for (std::string::size_type i = 0;
             i < value.length(); i++)
        {
            unsigned char ch =
                static_cast<unsigned char>(value[i]);

            if (!std::isspace(ch))
            {
                result += static_cast<char>(std::tolower(ch));
            }
        }

        return result;
    }
}

namespace UniversityCatalogue
{
    const std::vector<Program> &getPrograms()
    {
        static std::vector<Program> programs;

        if (programs.empty())
        {
            // Computer Science and IT
            programs.push_back(Program{"B.Tech", "Computer Science and Engineering", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Computer Science and Engineering (AI and ML)", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Computer Science and Engineering (AI and Data Science)", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Computer Science and Engineering (Cyber Security)", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Computer Science and Engineering (Internet of Things)", "Bachelor", 8});

            programs.push_back(Program{"M.Tech", "Computer Science and Engineering", "Master", 4});

            programs.push_back(Program{"BCA", "Computer Applications", "Bachelor", 6});
            programs.push_back(Program{"BCA (Hons)", "Computer Applications", "Bachelor", 8});
            programs.push_back(Program{"BCA", "Artificial Intelligence and Data Science", "Bachelor", 6});
            programs.push_back(Program{"BCA", "Cyber Security", "Bachelor", 6});

            programs.push_back(Program{"B.Sc", "Computer Science", "Bachelor", 6});
            programs.push_back(Program{"B.Sc", "Information Technology", "Bachelor", 6});
            programs.push_back(Program{"B.Sc (Hons)", "Computer Science", "Bachelor", 6});
            programs.push_back(Program{"B.Sc (Hons)", "Information Technology", "Bachelor", 8});

            programs.push_back(Program{"MCA", "Computer Applications", "Master", 4});
            programs.push_back(Program{"MCA", "Artificial Intelligence and Data Science", "Master", 4});
            programs.push_back(Program{"M.Sc", "Information Technology", "Master", 4});

            // Civil Engineering
            programs.push_back(Program{"B.Tech", "Civil Engineering", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Civil Engineering (Working Professionals)", "Bachelor", 6});
            programs.push_back(Program{"M.Tech", "Structural Engineering", "Master", 4});
            programs.push_back(Program{"M.Tech", "Structural Engineering (Working Professionals)", "Master", 4});

            // Mechanical Engineering
            programs.push_back(Program{"B.Tech", "Mechanical Engineering", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Mechanical Engineering (Working Professionals)", "Bachelor", 6});

            // Electrical Engineering
            programs.push_back(Program{"B.Tech", "Electrical and Computer Engineering", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Electrical and Computer Engineering (Electric Vehicles)", "Bachelor", 8});
            programs.push_back(Program{"M.Tech", "Electric Vehicle Technology", "Master", 4});

            // Electronics and Communication Engineering
            programs.push_back(Program{"B.Tech", "Electronics and Communication Engineering", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Electronics and Communication Engineering (VLSI)", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Electronics and Communication Engineering (Working Professionals)", "Bachelor", 6});
            programs.push_back(Program{"M.Tech", "VLSI Design", "Master", 4});

            // Biotechnology
            programs.push_back(Program{"B.Tech", "Biotechnology", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Biotechnology (Sustainable Sciences)", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Biotechnology (Computational Biology)", "Bachelor", 8});
            programs.push_back(Program{"B.Tech", "Biotechnology (Synthetic Biology)", "Bachelor", 8});
            programs.push_back(Program{"M.Tech", "Biotechnology", "Master", 4});

            // Aerospace Engineering
            programs.push_back(Program{"B.Tech", "Aerospace Engineering", "Bachelor", 8});

            // Arts and Humanities
            programs.push_back(Program{"BA (Hons)", "Economics", "Bachelor", 6});
            programs.push_back(Program{"BA (Hons)", "English", "Bachelor", 6});
            programs.push_back(Program{"BA (Hons)", "Political Science", "Bachelor", 6});
            programs.push_back(Program{"BA (Hons)", "Psychology", "Bachelor", 6});
            programs.push_back(Program{"BA (Hons)", "Sociology", "Bachelor", 6});

            programs.push_back(Program{"BA (Hons with Research)", "Economics", "Bachelor", 8});
            programs.push_back(Program{"BA (Hons with Research)", "English", "Bachelor", 8});
            programs.push_back(Program{"BA (Hons with Research)", "Political Science", "Bachelor", 8});
            programs.push_back(Program{"BA (Hons with Research)", "Psychology", "Bachelor", 8});
            programs.push_back(Program{"BA (Hons with Research)", "Sociology", "Bachelor", 8});

            // Design
            programs.push_back(Program{"B.Sc", "Graphic and Interaction Design", "Bachelor", 8});
            programs.push_back(Program{"B.Sc", "Animation and VFX", "Bachelor", 8});
            programs.push_back(Program{"B.Sc", "Product and Interior Design", "Bachelor", 8});

            programs.push_back(Program{"B.Sc (Hons)", "Graphic and Interaction Design", "Bachelor", 8});
            programs.push_back(Program{"B.Sc (Hons)", "Animation and VFX", "Bachelor", 8});
            programs.push_back(Program{"B.Sc (Hons)", "Product and Interior Design", "Bachelor", 8});

            programs.push_back(Program{"M.Des", "Graphic and Interaction Design", "Master", 4});
            programs.push_back(Program{"M.Des", "Product and Interior Design", "Master", 4});
            programs.push_back(Program{"M.Sc", "Graphic and Interaction Design", "Master", 4});
            programs.push_back(Program{"M.Sc", "Product and Interior Design", "Master", 4});
        }

        return programs;
    }

    std::vector<std::string> getCourses()
    {
        std::vector<std::string> courses;
        const std::vector<Program> &programs = getPrograms();

        for (std::size_t i = 0; i < programs.size(); i++)
        {
            bool found = false;

            for (std::size_t j = 0; j < courses.size(); j++)
            {
                if (normalize(courses[j]) ==
                    normalize(programs[i].course))
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                courses.push_back(programs[i].course);
            }
        }

        std::sort(courses.begin(), courses.end());

        return courses;
    }

    std::vector<std::string> getBranches(
        const std::string &course)
    {
        std::vector<std::string> branches;
        const std::vector<Program> &programs = getPrograms();

        for (std::size_t i = 0; i < programs.size(); i++)
        {
            if (normalize(programs[i].course) == normalize(course))
            {
                bool found = false;

                for (std::size_t j = 0; j < branches.size(); j++)
                {
                    if (normalize(branches[j]) ==
                        normalize(programs[i].branch))
                    {
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    branches.push_back(programs[i].branch);
                }
            }
        }

        std::sort(branches.begin(), branches.end());

        return branches;
    }

    bool isValidCourse(const std::string &course)
    {
        const std::vector<Program> &programs = getPrograms();

        for (std::size_t i = 0; i < programs.size(); i++)
        {
            if (normalize(programs[i].course) == normalize(course))
            {
                return true;
            }
        }

        return false;
    }

    bool isValidBranch(
        const std::string &course,
        const std::string &branch)
    {
        const std::vector<Program> &programs = getPrograms();

        for (std::size_t i = 0; i < programs.size(); i++)
        {
            if (normalize(programs[i].course) == normalize(course) &&
                normalize(programs[i].branch) == normalize(branch))
            {
                return true;
            }
        }

        return false;
    }

    int getMaximumSemester(
        const std::string &course,
        const std::string &branch)
    {
        const std::vector<Program> &programs = getPrograms();

        for (std::size_t i = 0; i < programs.size(); i++)
        {
            if (normalize(programs[i].course) == normalize(course) &&
                normalize(programs[i].branch) == normalize(branch))
            {
                return programs[i].maximumSemester;
            }
        }

        return 0;
    }

    std::string getProgramLevel(
        const std::string &course,
        const std::string &branch)
    {
        const std::vector<Program> &programs = getPrograms();

        for (std::size_t i = 0; i < programs.size(); i++)
        {
            if (normalize(programs[i].course) == normalize(course) &&
                normalize(programs[i].branch) == normalize(branch))
            {
                return programs[i].level;
            }
        }

        return "";
    }
}