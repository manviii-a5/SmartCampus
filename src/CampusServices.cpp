#include "CampusServices.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
using namespace std;
namespace
{
    const string RES = "data/resources.txt", BOOK = "data/bookings.txt", EM = "data/emergencies.txt", SR = "data/service_requests.txt", TEAMS = "data/response_teams.txt";
    string ask(const string &p)
    {
        string s;
        do
        {
            cout << p;
            getline(cin, s);
            if (s.empty())
                cout << "This field cannot be empty.\n";
        } while (s.empty());
        return s;
    }
    int choice(const string &p, int lo, int hi)
    {
        for (;;)
        {
            cout << p;
            string s;
            getline(cin, s);
            try
            {
                size_t n;
                int x = stoi(s, &n);
                if (n == s.size() && x >= lo && x <= hi)
                    return x;
            }
            catch (...)
            {
            }
            cout << "Invalid choice.\n";
        }
    }
    vector<string> lines(const string &p)
    {
        vector<string> v;
        ifstream f(p);
        string s;
        while (getline(f, s))
            if (!s.empty() && s[0] != '#')
                v.push_back(s);
        return v;
    }
    bool append(const string &p, const string &s)
    {
        ofstream f(p, ios::app);
        if (!f)
            return false;
        f << s << '\n';
        return bool(f);
    }
    bool rewrite(const string &p, const vector<string> &v)
    {
        ofstream f(p);
        if (!f)
            return false;
        for (auto &s : v)
            f << s << '\n';
        return bool(f);
    }
    vector<string> split(const string &s)
    {
        vector<string> v;
        stringstream ss(s);
        string x;
        while (getline(ss, x, '|'))
            v.push_back(x);
        return v;
    }
    string id(const string &p, const string &prefix)
    {
        int n = 1;
        for (auto &s : lines(p))
        {
            auto f = split(s);
            if (!f.empty() && f[0].rfind(prefix, 0) == 0)
                try
                {
                    n = max(n, stoi(f[0].substr(prefix.size())) + 1);
                }
                catch (...)
                {
                }
        }
        ostringstream o;
        o << prefix;
        o.width(4);
        o.fill('0');
        o << n;
        return o.str();
    }
    string timeVal(const string &p)
    {
        for (;;)
        {
            string t = ask(p + " (HH:MM): ");
            if (t.size() == 5 && t[2] == ':' && isdigit(t[0]) && isdigit(t[1]) && isdigit(t[3]) && isdigit(t[4]) && stoi(t.substr(0, 2)) < 24 && stoi(t.substr(3, 2)) < 60)
                return t;
            cout << "Enter time in 24-hour HH:MM format.\n";
        }
    }
    bool overlap(const string &a, const string &b, const string &c, const string &d) { return a < d && c < b; }
    void show(const string &p, const string &title)
    {
        cout << "\n--- " << title << " ---\n";
        auto v = lines(p);
        if (v.empty())
            cout << "No records found.\n";
        for (auto &s : v)
            cout << s << '\n';
    }
    void statusUpdate(const string &p, const string &key, const string &status, size_t index)
    {
        auto v = lines(p);
        bool found = false;
        for (auto &s : v)
        {
            auto f = split(s);
            if (!f.empty() && f[0] == key && f.size() > index)
            {
                f[index] = status;
                s = "";
                for (size_t i = 0; i < f.size(); i++)
                {
                    if (i)
                        s += '|';
                    s += f[i];
                }
                found = true;
                break;
            }
        }
        if (found && rewrite(p, v))
            cout << "Record updated.\n";
        else
            cout << "Record not found or could not save.\n";
    }
    void addResource()
    {
        const char *types[] = {"", "Classroom", "Computer Lab", "Laboratory", "Seminar Hall", "Conference Room", "Auditorium", "Sports Facility", "Library Facility", "Medical Facility", "Equipment", "Furniture", "Other"};
        cout << "Resource type:\n";
        for (int i = 1; i <= 12; i++)
            cout << i << ". " << types[i] << "\n";
        int t = choice("Choose type (1-12): ", 1, 12);
        string name = ask("Resource name: "), loc = ask("Building/room location: ");
        string rid = id(RES, "R");
        if (append(RES, rid + "|" + name + "|" + types[t] + "|" + loc + "|AVAILABLE"))
            cout << "Resource added. ID: " << rid << '\n';
        else
            cout << "Save failed.\n";
    }
    void booking(long long uid, const string &role)
    {
        const char *types[] = {"Classroom", "Computer Lab", "Laboratory", "Seminar Hall", "Conference Room", "Auditorium", "Sports Facility", "Library Facility", "Medical Facility", "Equipment", "Furniture", "Other"};
        cout << "\n========== SELECT RESOURCE TYPE ==========\n";
        for (int i = 0; i < 12; i++)
            cout << i + 1 << ". " << types[i] << "\n";
        int typeChoice = choice("Select resource type (1-12): ", 1, 12);
        string selectedType = types[typeChoice - 1];
        auto rs = lines(RES);
        vector<vector<string>> eligible;
        for (auto &row : rs)
        {
            auto f = split(row);
            if (f.size() < 5 || f[4] != "AVAILABLE")
                continue;
            string storedType = f[2];
            if (storedType == "Seminar hall" || storedType == "Seminar Room")
                storedType = "Seminar Hall";
            if (storedType == "Conference room")
                storedType = "Conference Room";
            if (storedType == "Library Room")
                storedType = "Library Facility";
            if (storedType == "Medical Room")
                storedType = "Medical Facility";
            if (storedType == selectedType)
                eligible.push_back(f);
        }
        if (eligible.empty())
        {
            cout << "No available resources found for type: " << selectedType << ". Ask an administrator to add or enable one.\n";
            return;
        }
        cout << "\n========== AVAILABLE " << selectedType << " RESOURCES ==========\n";
        for (size_t i = 0; i < eligible.size(); ++i)
        {
            cout << i + 1 << ". " << eligible[i][1] << " | ID: " << eligible[i][0] << " | Location: " << eligible[i][3] << "\n";
        }
        int resourceChoice = choice("Select resource number: ", 1, (int)eligible.size());
        string rid = eligible[resourceChoice - 1][0];
        string date = ask("Date (YYYY-MM-DD): "), start = timeVal("Start time"), end = timeVal("End time");
        if (end <= start)
        {
            cout << "End time must follow start time on the same date.\n";
            return;
        }
        int dur = stoi(end.substr(0, 2)) * 60 + stoi(end.substr(3, 2)) - stoi(start.substr(0, 2)) * 60 - stoi(start.substr(3, 2));
        if (dur < 30 || dur > 240)
        {
            cout << "Bookings must be 30 minutes to 4 hours.\n";
            return;
        }
        for (auto &s : lines(BOOK))
        {
            auto f = split(s);
            if (f.size() >= 10 && f[3] == rid && f[4] == date && (f[9] == "PENDING" || f[9] == "APPROVED") && overlap(start, end, f[5], f[6]))
            {
                cout << "Overlapping booking already exists.\n";
                return;
            }
        }
        string purpose = ask("Purpose: "), bid = id(BOOK, "B");
        if (append(BOOK, bid + "|" + role + "|" + to_string(uid) + "|" + rid + "|" + date + "|" + start + "|" + end + "|" + to_string(dur) + "|" + purpose + "|PENDING"))
            cout << "Request submitted for admin approval. Booking ID: " << bid << '\n';
        else
            cout << "Could not save booking.\n";
    }
    void emergency(long long uid, const string &role)
    {
        cout << "Emergency: 1 Medical 2 Fire 3 Security 4 Accident 5 Other\n";
        int t = choice("Type: ", 1, 5);
        const char *types[] = {"", "Medical", "Fire", "Security", "Accident", "Other"};
        string loc = ask("Exact location: "), desc = ask("Description: "), eid = id(EM, "E");
        const char *priority = (t == 2 || t == 3) ? "CRITICAL" : (t == 1 || t == 4) ? "HIGH"
                                                                                    : "MEDIUM";
        if (append(EM, eid + "|" + role + "|" + to_string(uid) + "|" + types[t] + "|" + loc + "|" + desc + "|OPEN|UNASSIGNED|" + priority))
            cout << "Emergency logged: " << eid << " (priority: " << priority << "). If immediate danger, contact campus security/emergency services directly now.\n";
        else
            cout << "Could not save report; contact campus security directly.\n";
    }
    void serviceRequest(long long uid, const string &role)
    {
        cout << "Category: 1 Maintenance 2 Cleaning 3 Electrical 4 Internet/IT 5 Water 6 Other\n";
        int t = choice("Category: ", 1, 6);
        const char *types[] = {"", "Maintenance", "Cleaning", "Electrical", "Internet/IT", "Water", "Other"};
        string loc = ask("Location: "), desc = ask("Describe issue: "), sid = id(SR, "SR");
        if (append(SR, sid + "|" + role + "|" + to_string(uid) + "|" + types[t] + "|" + loc + "|" + desc + "|PENDING"))
            cout << "Request submitted. ID: " << sid << '\n';
        else
            cout << "Save failed.\n";
    }
    void viewMine(const string &p, const string &role, long long uid)
    {
        bool found = false;
        for (auto &s : lines(p))
        {
            auto f = split(s);
            if (f.size() > 2 && f[1] == role && f[2] == to_string(uid))
            {
                cout << s << '\n';
                found = true;
            }
        }
        if (!found)
            cout << "No matching records.\n";
    }
    void userBookingActions(const string &role, long long uid)
    {
        auto v = lines(BOOK);
        vector<size_t> own;
        for (size_t i = 0; i < v.size(); ++i)
        {
            auto f = split(v[i]);
            if (f.size() >= 10 && f[1] == role && f[2] == to_string(uid))
                own.push_back(i);
        }
        if (own.empty())
        {
            cout << "No bookings to edit/cancel.\n";
            return;
        }
        for (auto i : own)
            cout << v[i] << '\n';
        string bid = ask("Booking ID (X to back): ");
        if (bid == "X" || bid == "x")
            return;
        for (auto i : own)
        {
            auto f = split(v[i]);
            if (f[0] != bid)
                continue;
            if (f[9] == "PENDING")
            {
                cout << "1 Edit pending booking  2 Cancel pending booking\n";
                int c = choice("Choice: ", 1, 2);
                if (c == 2)
                    f[9] = "CANCELLED";
                else
                {
                    string date = ask("New date (YYYY-MM-DD): "), st = timeVal("New start time"), en = timeVal("New end time");
                    if (en <= st)
                    {
                        cout << "End time must follow start time.\n";
                        return;
                    }
                    int dur = stoi(en.substr(0, 2)) * 60 + stoi(en.substr(3, 2)) - stoi(st.substr(0, 2)) * 60 - stoi(st.substr(3, 2));
                    if (dur < 30 || dur > 240)
                    {
                        cout << "Duration must be 30 minutes to 4 hours.\n";
                        return;
                    }
                    for (auto &row : v)
                    {
                        auto g = split(row);
                        if (g.size() >= 10 && g[0] != bid && g[3] == f[3] && g[4] == date && (g[9] == "PENDING" || g[9] == "APPROVED") && overlap(st, en, g[5], g[6]))
                        {
                            cout << "Overlapping booking exists. Edit cancelled.\n";
                            return;
                        }
                    }
                    f[4] = date;
                    f[5] = st;
                    f[6] = en;
                    f[7] = to_string(dur);
                    f[8] = ask("Updated purpose: ");
                }
                v[i] = "";
                for (size_t j = 0; j < f.size(); j++)
                {
                    if (j)
                        v[i] += '|';
                    v[i] += f[j];
                }
                cout << (rewrite(BOOK, v) ? "Booking updated.\n" : "Could not save change.\n");
                return;
            }
            if (f[9] == "APPROVED")
            {
                cout << "Request cancellation of this approved booking? 1 Yes 2 No\n";
                if (choice("Choice: ", 1, 2) == 1)
                {
                    f[9] = "CANCEL_REQUESTED";
                    v[i] = "";
                    for (size_t j = 0; j < f.size(); j++)
                    {
                        if (j)
                            v[i] += '|';
                        v[i] += f[j];
                    }
                    cout << (rewrite(BOOK, v) ? "Cancellation request sent to administrator.\n" : "Could not save request.\n");
                }
                return;
            }
            cout << "This booking is already " << f[9] << " and cannot be changed.\n";
            return;
        }
        cout << "Booking ID not found in your records.\n";
    }
    void setResourceAvailability()
    {
        show(RES, "RESOURCES");
        string rid = ask("Resource ID (X to back): ");
        if (rid == "X" || rid == "x")
            return;
        auto v = lines(RES);
        for (auto &row : v)
        {
            auto f = split(row);
            if (f.size() >= 5 && f[0] == rid)
            {
                cout << "1 AVAILABLE  2 UNAVAILABLE\n";
                f[4] = choice("Choose status: ", 1, 2) == 1 ? "AVAILABLE" : "UNAVAILABLE";
                row = "";
                for (size_t j = 0; j < f.size(); j++)
                {
                    if (j)
                        row += '|';
                    row += f[j];
                }
                cout << (rewrite(RES, v) ? "Resource availability updated.\n" : "Save failed.\n");
                return;
            }
        }
        cout << "Resource not found.\n";
    }
}
namespace CampusServices
{
    void userMenu(long long uid, const string &role)
    {
        int c;
        do
        {
            cout << "\n--- CAMPUS SERVICES ---\n1 View resources\n2 Request resource booking\n3 View booking history\n4 Edit/cancel booking or request cancellation\n5 Report emergency\n6 Submit service request\n7 View my service requests\n8 Back\n";
            c = choice("Choice: ", 1, 8);
            switch (c)
            {
            case 1:
                show(RES, "RESOURCES");
                break;
            case 2:
                booking(uid, role);
                break;
            case 3:
                viewMine(BOOK, role, uid);
                break;
            case 4:
                userBookingActions(role, uid);
                break;
            case 5:
                emergency(uid, role);
                break;
            case 6:
                serviceRequest(uid, role);
                break;
            case 7:
                viewMine(SR, role, uid);
                break;
            }
        } while (c != 8);
    }
    void adminResources()
    {
        int c;
        do
        {
            cout << "\n1 List resources\n2 Add resource\n3 Change resource availability\n4 Back\n";
            c = choice("Choice: ", 1, 4);
            if (c == 1)
                show(RES, "RESOURCES");
            else if (c == 2)
                addResource();
            else if (c == 3)
                setResourceAvailability();
        } while (c != 4);
    }
    void adminBookings()
    {
        show(BOOK, "ALL BOOKINGS");
        string bid = ask("Booking ID to update (or X to back): ");
        if (bid == "X" || bid == "x")
            return;
        cout << "1 Approve 2 Reject 3 Cancel booking 4 Approve cancellation request 5 Reject cancellation request\n";
        int c = choice("Choice: ", 1, 5);
        statusUpdate(BOOK, bid, c == 1 ? "APPROVED" : c == 2 ? "REJECTED"
                                                  : c == 3   ? "CANCELLED"
                                                  : c == 4   ? "CANCELLED"
                                                             : "APPROVED",
                     9);
    }
    void adminEmergencies()
    {
        show(EM, "EMERGENCY REPORTS");
        string eid = ask("Emergency ID to update (or X to back): ");
        if (eid == "X" || eid == "x")
            return;
        cout << "1 In progress 2 Resolved 3 Assign response team\n";
        int c = choice("Choice: ", 1, 3);
        if (c < 3)
        {
            statusUpdate(EM, eid, c == 1 ? "IN_PROGRESS" : "RESOLVED", 6);
            return;
        }
        auto teams = lines(TEAMS);
        if (teams.empty())
        {
            for (int i = 1; i <= 6; i++)
                append(TEAMS, "TEAM" + to_string(i) + "|Campus Response Team " + to_string(i) + "|AVAILABLE");
            teams = lines(TEAMS);
        }
        for (auto &s : teams)
            cout << s << '\n';
        string team = ask("Team ID: ");
        auto v = lines(EM);
        bool found = false;
        for (auto &s : v)
        {
            auto f = split(s);
            if (f.size() >= 8 && f[0] == eid)
            {
                f[7] = team;
                s = "";
                for (size_t i = 0; i < f.size(); i++)
                {
                    if (i)
                        s += '|';
                    s += f[i];
                }
                found = true;
                break;
            }
        }
        cout << (found && rewrite(EM, v) ? "Team assigned.\n" : "Could not assign team.\n");
    }
    void adminServiceRequests()
    {
        show(SR, "SERVICE REQUESTS");
        string sid = ask("Request ID to update (or X to back): ");
        if (sid == "X" || sid == "x")
            return;
        cout << "1 In Progress 2 Resolved 3 Pending\n";
        int c = choice("Choice: ", 1, 3);
        if (c == 2)
        {
            string note = ask("Resolution note: ");
            auto v = lines(SR);
            for (auto &row : v)
            {
                auto f = split(row);
                if (f.size() >= 7 && f[0] == sid)
                {
                    f[6] = "RESOLVED";
                    f.push_back("Resolution: " + note);
                    row = "";
                    for (size_t j = 0; j < f.size(); j++)
                    {
                        if (j)
                            row += '|';
                        row += f[j];
                    }
                    cout << (rewrite(SR, v) ? "Request resolved and note saved.\n" : "Save failed.\n");
                    return;
                }
            }
            cout << "Request not found.\n";
            return;
        }
        statusUpdate(SR, sid, c == 1 ? "IN_PROGRESS" : "PENDING", 6);
    }
}
