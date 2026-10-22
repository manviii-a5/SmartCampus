#include "InputValidator.h"
#include "UniversityCatalogue.h"

#include <iostream>
#include <limits>
#include <cctype>
#include <string>

namespace InputValidator
{
    long long getValidStudentId()
    {
        std::string input;

        while (true)
        {
            std::cout << "Enter Student ID (digits only): ";
            std::getline(std::cin, input);

            if (input.empty() || input.length() > 10)
            {
                std::cout << "Invalid ID. Enter 1-10 digits.\n";
                continue;
            }

            bool valid = true;

            for (std::string::size_type i = 0; i < input.length(); i++)
            {
                char ch = input[i];

                if (!std::isdigit(static_cast<unsigned char>(ch)))
                {
                    valid = false;
                    break;
                }
            }

            if (!valid)
            {
                std::cout << "Student ID must contain digits only.\n";
                continue;
            }

            try
            {
                long long id = 0;
                bool conversionValid = true;

                for (std::string::size_type i = 0; i < input.length(); i++)
                {
                    int digit = input[i] - '0';

                    if (id > (9223372036854775807LL - digit) / 10)
                    {
                        conversionValid = false;
                        break;
                    }

                    id = id * 10 + digit;
                }

                if (conversionValid && id > 0)
                    return id;
            }
            catch (...)
            {
                // Invalid numeric input.
            }

            std::cout << "Student ID must be greater than zero.\n";
        }
    }

    bool isValidStudentName(const std::string &name)
    {
        if (name.empty())
            return false;

        for (std::string::size_type i = 0; i < name.length(); i++)
        {
            char ch = name[i];
            unsigned char c = static_cast<unsigned char>(ch);

            if (!std::isalpha(c) && ch != ' ' && ch != '\'')
                return false;
        }

        return true;
    }

    std::string getValidStudentName()
    {
        std::string name;

        while (true)
        {
            std::cout << "Enter Student Name: ";
            std::getline(std::cin, name);

            if (isValidStudentName(name))
                return name;

            std::cout << "Invalid name. Use letters, spaces, and apostrophes only.\n";
        }
    }

    std::string getValidCourse()
    {
        const std::vector<std::string> courses = UniversityCatalogue::getCourses();
        std::string input;

        if (courses.empty())
        {
            std::cout << "ERROR: The university course catalogue is empty.\n";
            return "";
        }

        while (true)
        {
            std::cout << "\nAvailable Courses:\n";
            for (std::size_t i = 0; i < courses.size(); ++i)
                std::cout << "  " << (i + 1) << ". " << courses[i] << "\n";
            std::cout << "Select course by number or enter its exact name: ";
            std::getline(std::cin, input);

            // Numeric menu selection avoids spelling/spacing mismatches.
            bool digitsOnly = !input.empty();
            std::size_t selected = 0;
            for (std::size_t i = 0; i < input.size(); ++i)
            {
                if (!std::isdigit(static_cast<unsigned char>(input[i])))
                {
                    digitsOnly = false;
                    break;
                }
                selected = selected * 10 + static_cast<std::size_t>(input[i] - '0');
            }
            if (digitsOnly && selected >= 1 && selected <= courses.size())
                return courses[selected - 1];

            if (UniversityCatalogue::isValidCourse(input))
            {
                // Return the canonical spelling from the catalogue.
                for (std::size_t i = 0; i < courses.size(); ++i)
                {
                    std::string a = courses[i], b = input;
                    for (std::size_t j = 0; j < a.size(); ++j)
                        a[j] = static_cast<char>(std::tolower(static_cast<unsigned char>(a[j])));
                    for (std::size_t j = 0; j < b.size(); ++j)
                        b[j] = static_cast<char>(std::tolower(static_cast<unsigned char>(b[j])));
                    if (a == b)
                        return courses[i];
                }
            }
            std::cout << "Invalid course. Choose a number from the list above.\n";
        }
    }

    std::string getValidBranch(const std::string &course)
    {
        const std::vector<std::string> branches = UniversityCatalogue::getBranches(course);
        std::string input;

        if (branches.empty())
        {
            std::cout << "ERROR: No branches are configured for course '" << course << "'.\n";
            return "";
        }

        while (true)
        {
            std::cout << "\nAvailable branches/specializations for " << course << ":\n";
            for (std::size_t i = 0; i < branches.size(); ++i)
                std::cout << "  " << (i + 1) << ". " << branches[i] << "\n";
            std::cout << "Select branch by number or enter its exact name: ";
            std::getline(std::cin, input);

            bool digitsOnly = !input.empty();
            std::size_t selected = 0;
            for (std::size_t i = 0; i < input.size(); ++i)
            {
                if (!std::isdigit(static_cast<unsigned char>(input[i])))
                {
                    digitsOnly = false;
                    break;
                }
                selected = selected * 10 + static_cast<std::size_t>(input[i] - '0');
            }
            if (digitsOnly && selected >= 1 && selected <= branches.size())
                return branches[selected - 1];

            if (UniversityCatalogue::isValidBranch(course, input))
            {
                for (std::size_t i = 0; i < branches.size(); ++i)
                {
                    std::string a = branches[i], b = input;
                    for (std::size_t j = 0; j < a.size(); ++j)
                        a[j] = static_cast<char>(std::tolower(static_cast<unsigned char>(a[j])));
                    for (std::size_t j = 0; j < b.size(); ++j)
                        b[j] = static_cast<char>(std::tolower(static_cast<unsigned char>(b[j])));
                    if (a == b)
                        return branches[i];
                }
            }
            std::cout << "Invalid branch for the selected course. Choose a number from the list above.\n";
        }
    }

    int getValidSemester(int maximumSemester)
    {
        int semester;

        while (true)
        {
            std::cout << "Enter Semester (1-" << maximumSemester << "): ";

            if (std::cin >> semester)
            {
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                if (semester >= 1 && semester <= maximumSemester)
                    return semester;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "Invalid semester. Try again.\n";
        }
    }

    std::string getValidBuildingName()
    {
        std::string name;

        while (true)
        {
            std::cout << "Enter Building Name: ";
            std::getline(std::cin, name);

            if (name.empty())
            {
                std::cout << "Building name cannot be empty.\n";
                continue;
            }

            bool valid = true;

            for (std::string::size_type i = 0; i < name.length(); i++)
            {
                char ch = name[i];
                unsigned char c = static_cast<unsigned char>(ch);

                if (!std::isalnum(c) &&
                    ch != ' ' && ch != '&' && ch != '-' &&
                    ch != '.' && ch != '/' && ch != '\'' &&
                    ch != '(' && ch != ')')
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
                return name;

            std::cout << "Building name contains invalid characters.\n";
        }
    }

    std::string getValidBuildingType()
    {
        const std::string types[] = {
            "Academic",
            "Administrative",
            "Residential",
            "Laboratory",
            "Facility",
            "Recreation",
            "Commercial",
            "Other"};

        int choice;

        while (true)
        {
            std::cout << "\nSelect Building Type:\n";

            for (int i = 0; i < 8; i++)
                std::cout << i + 1 << ". " << types[i] << '\n';

            std::cout << "Enter choice: ";

            if (std::cin >> choice)
            {
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                if (choice >= 1 && choice <= 8)
                    return types[choice - 1];
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "Invalid choice. Try again.\n";
        }
    }

    std::string getNonEmptyString(const std::string &prompt)
    {
        std::string input;

        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, input);

            if (!input.empty())
                return input;

            std::cout << "Input cannot be empty.\n";
        }
    }

    bool isValidEmail(const std::string &email)
    {
        if (email.empty() || email.find(' ') != std::string::npos)
            return false;
        const std::size_t at = email.find('@');
        if (at == std::string::npos || at == 0 || at != email.rfind('@') || at + 1 >= email.size())
            return false;
        const std::string local = email.substr(0, at);
        const std::string domain = email.substr(at + 1);
        if (local.front() == '.' || local.back() == '.' || local.find("..") != std::string::npos)
            return false;
        const std::size_t dot = domain.rfind('.');
        if (dot == std::string::npos || dot == 0 || dot + 1 >= domain.size() || domain.find('.') == std::string::npos)
            return false;
        if (domain.front() == '.' || domain.back() == '.' || domain.find("..") != std::string::npos)
            return false;
        for (char ch : email)
        {
            unsigned char c = static_cast<unsigned char>(ch);
            if (!(std::isalnum(c) || ch == '@' || ch == '.' || ch == '_' || ch == '%' || ch == '+' || ch == '-'))
                return false;
        }
        return true;
    }

    bool isValidPhone(const std::string &phone)
    {
        if (phone.length() != 10 || phone[0] < '6' || phone[0] > '9')
            return false;
        for (char ch : phone)
        {
            if (!std::isdigit(static_cast<unsigned char>(ch)))
                return false;
        }
        return true;
    }

    bool isValidPassword(const std::string &password)
    {
        if (password.length() < 8)
            return false;

        bool uppercase = false;
        bool lowercase = false;
        bool digit = false;
        bool special = false;

        for (std::string::size_type i = 0;
             i < password.length(); i++)
        {
            unsigned char ch =
                static_cast<unsigned char>(password[i]);

            if (std::isupper(ch))
                uppercase = true;
            else if (std::islower(ch))
                lowercase = true;
            else if (std::isdigit(ch))
                digit = true;
            else
                special = true;
        }

        return uppercase && lowercase && digit && special;
    }
}