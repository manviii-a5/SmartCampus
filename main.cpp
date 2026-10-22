#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include "StudentManager.h"
#include "FacultyManager.h"
#include "AuthenticationManager.h"
#include "InputValidator.h"
#include "UniversityCatalogue.h"
#include "CampusDataManager.h"
#include "FileManager.h"
#include "AuditLogger.h"
#include "CampusServices.h"
#ifdef _WIN32
#include <windows.h>
#include <vector>
#endif

using namespace std;

void clearInput() { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
int readChoice(const string& prompt, int low, int high) {
    int n;
    while (true) { cout << prompt; if (cin >> n && n >= low && n <= high) { clearInput(); return n; } cout << "Invalid choice. Try again.\n"; clearInput(); }
}
long long readID(const string& prompt) {
    string s; while (true) { cout << prompt; getline(cin,s); bool ok=!s.empty() && s.size()<=18; long long n=0; for(char c:s){if(c<'0'||c>'9'||n>(9223372036854775807LL-(c-'0'))/10){ok=false;break;} n=n*10+(c-'0');} if(ok&&n>0)return n; cout<<"Enter a positive numeric ID.\n"; }
}
string ask(const string& p) { string s; do { cout<<p; getline(cin,s); if(s.empty()) cout<<"This field cannot be empty.\n"; } while(s.empty()); return s; }
string password() { return ask("Enter Password: "); }
string validEmail() { string v; do { v=ask("Email address: "); if(!InputValidator::isValidEmail(v)) cout<<"Invalid email. Enter a valid address such as name@example.com.\n"; } while(!InputValidator::isValidEmail(v)); return v; }
string validPhone() { string v; do { v=ask("Phone number (10 digits): "); if(!InputValidator::isValidPhone(v)) cout<<"Invalid phone number. Enter exactly 10 digits, without spaces or country code.\n"; } while(!InputValidator::isValidPhone(v)); return v; }

void registerStudent() {
    cout << "\n--- STUDENT REGISTRATION ---\n";
    long long id=readID("Student ID: ");
    string name=InputValidator::getValidStudentName();
    string course=InputValidator::getValidCourse();
    string branch=InputValidator::getValidBranch(course);
    int maxSem=UniversityCatalogue::getMaximumSemester(course,branch);
    if(maxSem<1) maxSem=8;
    int semester=InputValidator::getValidSemester(maxSem);
    string email=validEmail(), phone=validPhone(), pass=password();
    Student s(id,name,course,branch,semester,email,phone,pass);
    if(StudentManager::registerStudent(s)) AuditLogger::log("INFO", "Student registration succeeded; ID=" + to_string(id)); else AuditLogger::log("WARN", "Student registration failed; ID=" + to_string(id));
}
void registerFaculty() {
    cout << "\n--- FACULTY REGISTRATION ---\n";
    long long id=readID("Faculty ID: ");
    string name=ask("Full name: "), dept=ask("Department: "), designation=ask("Designation: ");
    string email=validEmail(), phone=validPhone(), pass=password();
    Faculty f(id,name,dept,designation,email,phone,pass);
    if(FacultyManager::registerFaculty(f)) AuditLogger::log("INFO", "Faculty registration succeeded; ID=" + to_string(id)); else AuditLogger::log("WARN", "Faculty registration failed; ID=" + to_string(id));
}
void studentDashboard(long long id) {
    int c; do {
        cout<<"\n===== STUDENT DASHBOARD =====\n1. View profile\n2. View campus buildings/locations\n3. Search for a room\n4. Campus services (booking/resources/emergency/service requests)\n5. Logout\n";
        c=readChoice("Choice: ",1,5);
        if(c==1) StudentManager::displayStudentProfile(id);
        else if(c==2) CampusDataManager::listBuildings();
        else if(c==3) CampusDataManager::searchRoom();
        else if(c==4) CampusServices::userMenu(id, "STUDENT");
    } while(c!=5);
}
void facultyDashboard(long long id) {
    int c; do {
        cout<<"\n===== FACULTY DASHBOARD =====\n1. View profile\n2. View campus buildings/locations\n3. Search for a room\n4. Campus services (booking/resources/emergency/service requests)\n5. Logout\n";
        c=readChoice("Choice: ",1,5);
        if(c==1) FacultyManager::displayFacultyProfile(id);
        else if(c==2) CampusDataManager::listBuildings();
        else if(c==3) CampusDataManager::searchRoom();
        else if(c==4) CampusServices::userMenu(id, "FACULTY");
    } while(c!=5);
}
void adminDashboard() {
    int c; do {
        cout<<"\n===== ADMINISTRATOR DASHBOARD =====\n1 Register student\n2 List students\n3 Register faculty\n4 List faculty\n5 View buildings/locations\n6 Add building/location\n7 View rooms\n8 Add room\n9 Save/reload student and faculty records\n10 Manage resources\n11 Manage bookings\n12 Manage emergencies/response teams\n13 Manage service requests\n14 View audit log\n15 Logout\n";
        c=readChoice("Choice: ",1,15);
        switch(c){
        case 1:registerStudent();break; case 2:StudentManager::displayAllStudents();break;
        case 3:registerFaculty();break; case 4:FacultyManager::displayAllFaculty();break;
        case 5:CampusDataManager::listBuildings();break; case 6:CampusDataManager::addBuilding();break;
        case 7:CampusDataManager::listRooms();break; case 8:CampusDataManager::addRoom();break;
        case 9:{bool a=StudentManager::saveStudents()&&FacultyManager::saveFaculty();bool b=StudentManager::loadStudents()&&FacultyManager::loadFaculty();cout<<((a&&b)?"Records saved and reloaded.\n":"Could not save/reload all records.\n");break;}
        case 10:CampusServices::adminResources();break;case 11:CampusServices::adminBookings();break;
        case 12:CampusServices::adminEmergencies();break;case 13:CampusServices::adminServiceRequests();break;
        case 14:{ifstream f("logs/smartcampus.log");string line;if(!f)cout<<"Audit log unavailable.\n";else while(getline(f,line))cout<<line<<"\n";break;}
        case 15:cout<<"Administrator logged out.\n";break;
        }
    } while(c!=15);
}
void studentMode() {
    cout<<"\n===== STUDENT MODE =====\n1. Login\n2. Register\n3. Back\n";
    int c=readChoice("Choice: ",1,3); if(c==2){registerStudent();return;} if(c==3)return;
    long long id=readID("Student ID: ");
    if(!StudentManager::studentExists(id)){cout<<"Student not registered. Choose Student Mode > Register first.\n";return;}
    for(int i=1;i<=3;i++){if(AuthenticationManager::authenticateStudent(id,password())){AuditLogger::log("INFO", "Student login succeeded; ID=" + to_string(id));cout<<"Login successful.\n";studentDashboard(id);return;} cout<<"Incorrect password. Attempts remaining: "<<3-i<<"\n";} }
void facultyMode() {
    cout<<"\n===== FACULTY MODE =====\n1. Login\n2. Back\n";
    if(readChoice("Choice: ",1,2)==2)return;
    long long id=readID("Faculty ID: "); if(!FacultyManager::facultyExists(id)){cout<<"Faculty ID is not registered. Contact administrator.\n";return;}
    for(int i=1;i<=3;i++){if(AuthenticationManager::authenticateFaculty(id,password())){AuditLogger::log("INFO", "Faculty login succeeded; ID=" + to_string(id));cout<<"Login successful.\n";facultyDashboard(id);return;} cout<<"Incorrect password. Attempts remaining: "<<3-i<<"\n";} }
void administratorMode(){cout<<"\n===== ADMINISTRATOR LOGIN =====\n"; string name=ask("Administrator name: "); for(int i=1;i<=3;i++){if(AuthenticationManager::authenticateAdministrator(password())){cout<<"Login successful. Welcome, "<<name<<"!\n";adminDashboard();return;}cout<<"Incorrect password. Attempts remaining: "<<3-i<<"\n";}}
int main(){
#ifdef _WIN32
    // Resolve all relative data/ and logs/ paths from the executable directory,
    // not from whichever folder PowerShell or a shortcut happens to use.
    char executablePath[MAX_PATH] = {};
    DWORD pathLength = GetModuleFileNameA(nullptr, executablePath, MAX_PATH);
    if (pathLength > 0 && pathLength < MAX_PATH) {
        std::string fullPath(executablePath, pathLength);
        std::size_t separator = fullPath.find_last_of("\\/");
        if (separator != std::string::npos) {
            fullPath.resize(separator);
            if (!SetCurrentDirectoryA(fullPath.c_str()))
                cerr << "Warning: Could not set working directory to executable folder.\n";
        }
    }
#endif
    if(!AuditLogger::initialize()) cerr << "Warning: Could not initialize logs/smartcampus.log. Check folder permissions and project directory.\n";
    AuditLogger::log("INFO", "Application startup");
    if(!FileManager::ensureDataDirectory()) cerr << "Warning: Could not create data directory under application folder.\n";
    if(!CampusDataManager::initialize()) { cerr<<"Warning: Could not initialize building/room data files. Expected: " << "data/buildings.txt and data/rooms.txt\n"; AuditLogger::log("ERROR", "Could not initialize building/room data files"); }
    if(!StudentManager::loadStudents()) { cerr<<"Warning: Could not load student records from data/students.txt. Verify file exists and is writable/readable.\n"; AuditLogger::log("ERROR", "Could not load student records"); } else AuditLogger::log("INFO", "Student records loaded");
    if(!FacultyManager::loadFaculty()) { cerr<<"Warning: Could not load faculty records from data/faculty.txt. Verify file exists and is writable/readable.\n"; AuditLogger::log("ERROR", "Could not load faculty records"); } else AuditLogger::log("INFO", "Faculty records loaded");
    int c; do {cout<<"\n====================================\n SMARTCAMPUS MANAGEMENT SYSTEM\n====================================\n1. Student Mode\n2. Faculty Mode\n3. Administrator Mode\n4. Exit\n";c=readChoice("Enter your choice: ",1,4);switch(c){case 1:studentMode();break;case 2:facultyMode();break;case 3:administratorMode();break;case 4:AuditLogger::log("INFO", "Application exit");cout<<"Thank you for using SmartCampus!\n";break;}}while(c!=4);return 0;
}
