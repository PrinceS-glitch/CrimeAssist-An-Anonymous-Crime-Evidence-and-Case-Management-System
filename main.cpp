#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> 
#include <limits>        // for timestamp 

using namespace std;
#ifdef _WIN32
#include <conio.h>
#else                          // conditional compilation
#include <termios.h>          // allows us to control how the terminal behaves
#include <unistd.h>
#endif


string getPassword()
{
    string password;
    char ch;

#ifdef _WIN32

    while (true)
    {
        ch = _getch();

        if (ch == '\r')
        {
            break;
        }

        if (ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();  // removes last character from string
                cout << "\b \b";
            }
        }
        else
        {
            password += ch;
            cout << '*';
        }
    }

#else

    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);          // get current terminal configuration
    newt = oldt;
    newt.c_lflag &= ~ECHO;                  // disables echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Remove the newline left by previous cin input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true)
    {
        ch = getchar();

        if (ch == '\n' || ch == '\r')
        {
            break;
        }

        if (ch == 127 || ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            password += ch;
            cout << '*';
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

#endif

    cout << endl;
    return password;
}
class Admin {

private:
    string username;
    string password;

public:

    void adminVerify();
    void adminMenu();
    void addOfficer();
    void updateOfficerInformation();
    void deleteOfficer();

    void viewOngoingCases();
    void viewRejectedCases();
    void approveOfficerDecision();
    void requestReinvestigation();
    void markCaseAsClosed();

    void userReviewSystem();
    void viewUserComments();
    void reviewOfficerComplaints();
    void reopenCase();

    void caseStatistics();

    
};
class Officer {
private:
    int officerID;
    string username;
    string password;

public:
    void officerVerify();
    void officerMenu();
    
    void caseStatistics();

    void verifyPendingCases();

    void postNewCase();
    void searchCase();
    void requestCaseClosure();
};

class User {
private:
    string username;
    string password;

public:
void userAuthMenu();
 void userRegister();
    void userVerify();
    void userMenu();
    void reportCrime();
    void searchCase();
    void viewAllCases();
};


void helpMenu();


// common for both officer and admin
void displayCaseStatistics() {
    ifstream file("cases.txt");

    if (!file) {
        cout << "\n========== CASE STATISTICS ==========\n";
        cout << "No case data available yet.\n";
        return;
    }

    string line;
    string remaining;
    string status;

    int totalCases = 0;
    int waitingVerification = 0;
    int verified = 0;
    int ongoingInvestigation = 0;
    int rejected = 0;
    int closureRequest = 0;
    int reinvestigating = 0;
    int closed = 0;

    // Skip header
    getline(file, line);

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        totalCases++;

        // Remove Case ID
        size_t pos = line.find('|');
        remaining = line.substr(pos + 1);

        // Get Status
        pos = remaining.rfind('|');
        status = remaining.substr(pos + 1);

        if (status == "Waiting Verification") {
            waitingVerification++;
        }
        else if (status == "Verified") {
            verified++;
        }
        else if (status == "Ongoing Investigation") {
            ongoingInvestigation++;
        }
        else if (status == "Rejected") {
            rejected++;
        }
        else if (status == "Case Closure Request") {
            closureRequest++;
        }
        else if (status == "Reinvestigating") {
            reinvestigating++;
        }
        else if (status == "Case Closed") {
            closed++;
        }
    }

    file.close();

    cout << "\n========== CASE STATISTICS ==========\n";

    cout << "Total Cases: " << totalCases << endl;
    cout << "Waiting Verification: " << waitingVerification << endl;
    cout << "Verified: " << verified << endl;
    cout << "Ongoing Investigation: " << ongoingInvestigation << endl;
    cout << "Rejected: " << rejected << endl;
    cout << "Case Closure Request: " << closureRequest << endl;
    cout << "Reinvestigating: " << reinvestigating << endl;
    cout << "Case Closed: " << closed << endl;
}

bool checkEvidenceTimestamp(string evidencePath) {

    if (!filesystem::exists(evidencePath)) {
        cout << "\nEvidence file not found in the system.\n";
        return false;
    }

    try {
        auto fileTime = filesystem::last_write_time(evidencePath);

        cout << "\nEvidence file found successfully." << endl;
        cout << "Evidence timestamp checked successfully." << endl;

        return true;
    }
    catch (const filesystem::filesystem_error& e) {
        cout << "\nUnable to check evidence timestamp." << endl;
        return false;
    }
}


void searchCaseByID() {

    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case data available yet.\n";
        return;
    }

    int searchID;
    cout << "\n========== SEARCH CASE ==========\n";
    cout << "Enter Case ID: ";
    cin >> searchID;

    string line;

    // Skip header
    getline(file, line);

    bool found = false;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        // Case ID
        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Crime Type
        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Location
        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Date and Time
        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Description
        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Evidence
        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Status
        status = line;

        if (stoi(caseID) == searchID) {

            found = true;

            cout << "\n========== CASE DETAILS ==========\n";
            cout << "Case ID: " << caseID << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date and Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;

            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nCase not found.\n";
    }
}
void Admin::adminVerify() {

    cout << "Enter username: ";
    cin >> username;

    cout << "\nEnter password: ";


    password=getPassword();

    if (username == "admin" && password == "admin123") {

        cout << "Admin Verified" << endl;
        cout << "Loading Admin Menu" << endl;

        adminMenu();
    }
    else {

        cout << "Wrong details for admin login" << endl;
        cout << "Please try again" << endl;

        adminVerify();
    }
}


void Admin::addOfficer() {

    int officerID;
    string officerUsername;
    string officerPassword;

    cout << "\n===== ADD OFFICER =====\n";

    cout << "Enter Officer ID: ";
    cin >> officerID;

    cout << "Enter Username: ";
    cin >> officerUsername;

    cout << "Enter Password: ";
    officerPassword = getPassword();

    ofstream file("officer.txt", ios::app);

    if (!file) {
        cout << "Error opening officer.txt\n";
        return;
    }

    file << officerID << " "
         << officerUsername << " "
         << officerPassword << endl;

    file.close();

    cout << "\nOfficer added successfully!\n";
}


void Admin::adminMenu() {

    int choice;
    int adminChoice;

    while (true) {

        cout << "\n////////--- Admin Dashboard ---////////\n";
        cout << "1. Manage Officers" << endl;
        cout << "2. Review Officer Decisions" << endl;
        cout << "3. User Review System" << endl;
        cout << "4. Case Statistics" << endl;
        cout << "5. Logout" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {

            while (true) {

                cout << "\n===== MANAGE OFFICERS =====\n";
                cout << "1. Add Officer" << endl;
                cout << "2. Update Officer Information" << endl;
                cout << "3. Delete Officer" << endl;
                cout << "4. Return to Dashboard" << endl;

                cout << "Enter choice: ";
                cin >> adminChoice;

                if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input! Please enter a number.\n";
        continue;
    }


                if (adminChoice == 1) {

                    addOfficer();

                }
                else if (adminChoice == 2) {

                    updateOfficerInformation();

                }
                else if (adminChoice == 3) {

                    deleteOfficer();

                }
                else if (adminChoice == 4) {

                    break;

                }
                else {

                    cout << "\nInvalid choice!" << endl;

                }
            }
        }

        else if (choice == 2) {

                while (true) {
                     cout << "\n===== REVIEW OFFICER DECISIONS =====\n";

                    cout << "1. View Ongoing Cases" << endl;
                    cout << "2. View Rejected Cases" << endl;                    
                    cout << "3. Approve Officer Decision" << endl;
                    cout << "4. Request Reinvestigation" << endl;
                    cout << "5. Mark Case as Closed" << endl;
                    cout << "6. Return to Dashboard" << endl;

        
                    cout << "Enter choice: ";
                    cin >> adminChoice;

                    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nInvalid input! Please enter a number.\n";
        continue;
    }


        if (adminChoice == 1) {

            viewOngoingCases();

        }
        else if (adminChoice == 2) {

            viewRejectedCases();

        }
        else if (adminChoice == 3) {

            approveOfficerDecision();
        }
        else if (adminChoice == 4) {

            requestReinvestigation();

        }
        else if (adminChoice == 5) {

            markCaseAsClosed();

        }
        else if (adminChoice == 6) {

            break;

        }
        else {

            cout << "\nInvalid choice!" << endl;

        }
    }
}

        else if (choice == 3) {

            userReviewSystem();

        }

        else if (choice == 4) {

            caseStatistics();
        }

        else if (choice == 5) {

            cout << "\nLogging out..." << endl;
            break;

        }

        else {

            cout << "\nInvalid choice!" << endl;

        }
    }
}

   void Admin::updateOfficerInformation() {

    int officerID;
    int id;
    string username;
    string password;
    string newUsername;
    string newPassword;

    cout << "\n===== UPDATE OFFICER INFORMATION =====\n";

    cout << "Enter Officer ID to update: ";
    cin >> officerID;

    ifstream file("officer.txt");

    if (!file) {
        cout << "Error opening officer.txt\n";
        return;
    }

    ofstream temp("temp.txt");

    if (!temp) {
        cout << "Error creating temporary file\n";
        file.close();
        return;
    }

    bool found = false;

    while (file >> id >> username >> password) {

        if (id == officerID) {

            found = true;

            cout << "Enter new Username: ";
            cin >> newUsername;

            cout << "Enter new Password: ";
            newPassword = getPassword();

            temp << id << " "
                 << newUsername << " "
                 << newPassword << endl;

        }
        else {

            temp << id << " "
                 << username << " "
                 << password << endl;
        }
    }

    file.close();
    temp.close();

    remove("officer.txt");
    rename("temp.txt", "officer.txt");

    if (found) {
        cout << "\nOfficer information updated successfully!\n";
    }
    else {
        cout << "\nOfficer ID not found!\n";
    }
}



void Admin::deleteOfficer() {

    int officerID;
    int id;
    string username;
    string password;

    cout << "\n===== DELETE OFFICER =====\n";

    cout << "Enter Officer ID to delete: ";
    cin >> officerID;

    ifstream file("officer.txt");

    if (!file) {
        cout << "Error opening officer.txt\n";
        return;
    }

    ofstream temp("temp.txt");

    if (!temp) {
        cout << "Error creating temporary file\n";
        file.close();
        return;
    }

    bool found = false;

    while (file >> id >> username >> password) {

        if (id == officerID) {

            found = true;

            // Do not write this officer to the temporary file
        }
        else {

            temp << id << " "
                 << username << " "
                 << password << endl;
        }
    }

    file.close();
    temp.close();

    remove("officer.txt");
    rename("temp.txt", "officer.txt");

    if (found) {
        cout << "\nOfficer deleted successfully!\n";
    }
    else {
        cout << "\nOfficer ID not found!\n";
    }
}
void Admin::viewOngoingCases() {

    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case file found.\n";
        return;
    }

    string line;

    cout << "\n========== Ongoing CASES ==========\n";

    bool found = false;

    // Skip the first line containing headings
    getline(file, line);

    while (getline(file, line)) {

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        status = line;

        if (status == "Ongoing Investigation") {

            found = true;

            cout << "\nCase ID: " << caseID << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date & Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;

            cout << "-----------------------------------\n";
        }
    }

    file.close();

    if (!found) {
        cout << "\nNo ongoing cases found.\n";
    }
}

void Admin::viewRejectedCases() {
    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case file found.\n";
        return;
    }

    string line;

    cout << "\n========== REJECTED CASES ==========\n";

    bool found = false;

    // Skip the first line containing headings
    getline(file, line);

    while (getline(file, line)) {

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        status = line;

        if (status == "Rejected") {
            found = true;

            cout << "\nCase ID: " << caseID << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date & Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;
            cout << "-----------------------------------\n";
        }
    }

    file.close();

    if (!found) {
        cout << "\nNo rejected cases found.\n";
    }
}
void Admin::approveOfficerDecision() {
    int caseID;
    int id;
    int decision;

    string line;
    string crimeType;
    string location;
    string dateTime;
    string description;
    string evidence;
    string status;

    cout << "\n========== APPROVE OFFICER DECISION ==========\n";

    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case file found.\n";
        return;
    }

    bool found = false;

    // Skip heading line
    getline(file, line);

    while (getline(file, line)) {

        size_t pos;

        pos = line.find('|');
        id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        status = line;

        if (status == "Case Closure Request") {

            found = true;

            cout << "\nCase ID: " << id << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date & Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;

            caseID = id;

            cout << "\nDo you approve the officer's case closure decision?\n";
            cout << "1. Accept - Close Case" << endl;
            cout << "2. Decline - Request Reinvestigation" << endl;
            cout << "Enter choice: ";
            cin >> decision;

            if (cin.fail()) {
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "\nInvalid input! Please enter 1 or 2.\n";
    return;
}

            if (decision == 1) {
                status = "Case Closed";

                cout << "\nOfficer decision approved." << endl;
                cout << "Case status changed to Case Closed." << endl;
            }
            else if (decision == 2) {
                status = "Reinvestigating";

                cout << "\nOfficer decision declined." << endl;
                cout << "Case status changed to Reinvestigating." << endl;
            }
            else {
                cout << "\nInvalid choice!" << endl;
            }

            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nNo case closure requests found.\n";
        return;
    }

    // If an invalid decision was entered, do not modify the file.
    if (decision != 1 && decision != 2) {
        return;
    }

    // Reopen original file for updating
    ifstream oldFile("cases.txt");

    if (!oldFile) {
        cout << "\nError opening cases.txt\n";
        return;
    }

    ofstream temp("temp.txt");

    if (!temp) {
        cout << "\nError creating temporary file.\n";
        oldFile.close();
        return;
    }

    // Copy heading
    getline(oldFile, line);
    temp << line << endl;

    while (getline(oldFile, line)) {

        string currentLine = line;

        size_t pos = currentLine.find('|');

        int currentID = stoi(currentLine.substr(0, pos));

        if (currentID == caseID) {

            // Remove Case ID
            currentLine.erase(0, pos + 1);

            // Get remaining fields
            string remaining = currentLine;

            temp << caseID << "|" << remaining.substr(0, remaining.rfind('|') + 1)
                 << status << endl;
        }
        else {
            temp << line << endl;
        }
    }

    oldFile.close();
    temp.close();

    remove("cases.txt");
    rename("temp.txt", "cases.txt");
}

void Admin::requestReinvestigation() {
    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case file found.\n";
        return;
    }

    string line;

    cout << "\n========== REQUEST REINVESTIGATION ==========\n";

    bool found = false;

    // Skip the first line containing headings
    getline(file, line);

    while (getline(file, line)) {

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        status = line;

        if (status == "Reinvestigating") {
            found = true;

            cout << "\nCase ID: " << caseID << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date & Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;
            cout << "-----------------------------------\n";
        }
    }

    file.close();

    if (!found) {
        cout << "\nNo cases require reinvestigation.\n";
    }
}

void Admin::markCaseAsClosed() {
    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case file found.\n";
        return;
    }

    string line;

    cout << "\n========== CLOSED CASES ==========\n";

    bool found = false;

    // Skip the first line containing headings
    getline(file, line);

    while (getline(file, line)) {

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        status = line;

        if (status == "Case Closed") {
            found = true;

            cout << "\nCase ID: " << caseID << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date & Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;
            cout << "-----------------------------------\n";
        }
    }

    file.close();

    if (!found) {
        cout << "\nNo closed cases found.\n";
    }
}

void mainMenu() {

    char choice;

    cout << "\\\\\\\\\\\\\\\\\\\\--- MAIN MENU ---\\\\\\\\\\\\\\\\\\\\" << endl << endl;

    cout << "a) Admin" << endl;
    cout << "b) Officer" << endl;
    cout << "c) User" << endl;
    cout << "d) Help" << endl;
    cout << "e) Exit" << endl << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 'a' || choice == 'A') {

        Admin admin;
        admin.adminVerify();
    }

    else if (choice == 'b' || choice == 'B') {

       Officer officer;
       officer.officerVerify();
    }

    else if (choice == 'c' || choice == 'C') {

         User user;
         user.userAuthMenu();
    }

    else if (choice == 'd' || choice == 'D') {

        helpMenu();
    }

    else if (choice == 'e' || choice == 'E') {

        cout << "Exiting CrimeAssist..." << endl;
        return;
    }

    else {

        cout << "Invalid choice!" << endl;
    }
}

void Admin::userReviewSystem() {
    int choice;

    while (true) {
        cout << "\n===== USER REVIEW SYSTEM =====\n";
        cout << "1. View User Comments and Feedback" << endl;
        cout << "2. Review Complaints Against Officer Decisions" << endl;
        cout << "3. Reopen Case if Required" << endl;
        cout << "4. Return to Dashboard" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            viewUserComments();
        }
        else if (choice == 2) {
            reviewOfficerComplaints();
        }
        else if (choice == 3) {
            reopenCase();
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "\nInvalid choice! Please enter 1-4.\n";
        }
    }
}
void Admin::viewUserComments() {
    ifstream file("reviews.txt");

    if (!file) {
        cout << "\nNo user review file found.\n";
        return;
    }

    string line;

    cout << "\n========== USER COMMENTS AND FEEDBACK ==========\n";

    bool found = false;

    // Skip the first line containing headings
    getline(file, line);

    while (getline(file, line)) {

        string caseID;
        string userReview;

        size_t pos;

        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        userReview = line;

        found = true;

        cout << "\nCase ID: " << caseID << endl;
        cout << "User Review: " << userReview << endl;
        cout << "-----------------------------------\n";
    }

    file.close();

    if (!found) {
        cout << "\nNo user comments or feedback found.\n";
    }
}
void Admin::reviewOfficerComplaints() {
    ifstream file("complaints.txt");

    if (!file) {
        cout << "\nNo complaint file found.\n";
        return;
    }

    string line;

    cout << "\n========== OFFICER DECISION COMPLAINTS ==========\n";

    bool found = false;

    // Skip the first line containing headings
    getline(file, line);

    while (getline(file, line)) {

        string caseID;
        string complaint;

        size_t pos;

        pos = line.find('|');

        caseID = line.substr(0, pos);

        line.erase(0, pos + 1);

        complaint = line;

        found = true;

        cout << "\nCase ID: " << caseID << endl;
        cout << "Complaint: " << complaint << endl;
        cout << "-----------------------------------\n";
    }

    file.close();

    if (!found) {
        cout << "\nNo complaints against officer decisions found.\n";
    }
}

void Admin::reopenCase() {
    ifstream file("cases.txt");

    if (!file) {
        cout << "\nError opening cases.txt\n";
        return;
    }

    ofstream temp("temp.txt");

    if (!temp) {
        cout << "\nError creating temporary file\n";
        file.close();
        return;
    }

    string line;

    cout << "\n========== REOPEN CASE ==========\n";

    // Skip the header
    getline(file, line);
    temp << line << endl;

    bool found = false;

    while (getline(file, line)) {

        string caseID;
        string remaining;
        string status;

        size_t pos;

        // Get Case ID
        pos = line.find('|');
        caseID = line.substr(0, pos);

        remaining = line.substr(pos + 1);

        // Get Status
        pos = remaining.rfind('|');
        status = remaining.substr(pos + 1);

        if (status == "Reinvestigating") {

            found = true;

            cout << "\nCase ID: " << caseID << endl;
            cout << "Status: " << status << endl;

            cout << "Reopen this case? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {

                status = "Ongoing Investigation";

                temp << caseID << "|"
                     << remaining.substr(0, pos + 1)
                     << status << endl;

                cout << "Case reopened successfully!" << endl;
                cout << "New Status: Ongoing Investigation" << endl;
            }
            else {
                temp << caseID << "|"
                     << remaining << endl;

                cout << "Case was not reopened." << endl;
            }
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("cases.txt");
    rename("temp.txt", "cases.txt");

    if (!found) {
        cout << "\nNo cases available for reopening.\n";
    }
}

void Admin::caseStatistics() {
    displayCaseStatistics();
}
void Officer::officerMenu() {
    int choice;

    while (true) {

        cout << "\n////////--- Officer Dashboard ---////////\n";
        cout << "1. Case Statistics" << endl;
        cout << "2. Verify Pending Cases" << endl;
        cout << "3. Post New Case" << endl;
        cout << "4. Request Case Closure" << endl;
        cout << "5. Search Case" << endl;
        cout << "6. Logout" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            caseStatistics();
        }
        else if (choice == 2) {
            verifyPendingCases();
        }
        else if (choice == 3) {
            postNewCase();
        }
        else if (choice == 4) {
            requestCaseClosure();
        }
        else if (choice == 5) {
            searchCase();
        }
        else if (choice ==6) {
            cout << "\nLogging out..." << endl;
            break;
        }
        else {
            cout << "\nInvalid choice! Please enter 1-6.\n";
        }
    }
}


void Officer::officerVerify() {
    int enteredID;
    string enteredUsername;
    string enteredPassword;

    cout << "\n========== OFFICER LOGIN ==========\n";

    cout << "Enter Officer ID: ";
    cin >> enteredID;

    cout << "Enter Username: ";
    cin >> enteredUsername;

    cout << "Enter Password: ";
    enteredPassword=getPassword();

    ifstream file("officer.txt");

    if (!file) {
        cout << "\nNo officer records found.\n";
        return;
    }

    int id;
    string username;
    string password;

    bool found = false;

    while (file >> id >> username >> password) {

        if (id == enteredID &&
            username == enteredUsername &&
            password == enteredPassword) {

            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "\nOfficer Verified Successfully!" << endl;
        cout << "Loading Officer Dashboard..." << endl;

        officerMenu();
    }
    else {
        cout << "\nInvalid Officer Login Details!" << endl;
    }
}

void Officer::verifyPendingCases() {

    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case data available yet.\n";
        return;
    }

    ofstream temp("temp.txt");

    if (!temp) {
        cout << "\nError creating temporary file.\n";
        file.close();
        return;
    }

    string line;

    // Copy header
    getline(file, line);
    temp << line << endl;

    bool found = false;

    cout << "\n========== VERIFY PENDING CASES ==========\n";

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        // Case ID
        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Crime Type
        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Location
        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Date and Time
        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Description
        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Evidence
        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Status
        status = line;

        if (status == "Waiting Verification") {

            found = true;

            cout << "\n-----------------------------------\n";
            cout << "Case ID: " << caseID << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date and Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;

            cout << "\nChecking evidence..." << endl;

            checkEvidenceTimestamp(evidence);

            cout << "\n1. Valid Evidence" << endl;
            cout << "2. Invalid Evidence" << endl;
            cout << "Enter choice: ";

            int choice;
            cin >> choice;

            if (cin.fail()) {

                cin.clear();
                cin.ignore(1000, '\n');

                cout << "\nInvalid input. Case was not changed.\n";

                temp << caseID << "|"
                     << crimeType << "|"
                     << location << "|"
                     << dateTime << "|"
                     << description << "|"
                     << evidence << "|"
                     << status << endl;

                continue;
            }

            if (choice == 1) {

                status = "Ongoing Investigation";

                cout << "\nEvidence verified successfully!" << endl;
                cout << "Case status: Ongoing Investigation" << endl;
            }
            else if (choice == 2) {

                status = "Rejected";

                cout << "\nEvidence rejected." << endl;
                cout << "Case status: Rejected" << endl;
            }
            else {

                cout << "\nInvalid choice. Case was not changed.\n";
            }
        }

        // Write the complete record
        temp << caseID << "|"
             << crimeType << "|"
             << location << "|"
             << dateTime << "|"
             << description << "|"
             << evidence << "|"
             << status << endl;
    }

    file.close();
    temp.close();

    remove("cases.txt");
    rename("temp.txt", "cases.txt");

    if (!found) {
        cout << "\nNo cases waiting for verification.\n";
    }
}
void Officer::caseStatistics() {
    displayCaseStatistics();
}

void Officer::postNewCase() {

    ofstream file("cases.txt", ios::app);

if (!file) {
    cout << "\nError opening case file.\n";
    return;
}

if (file.tellp() == 0) {
    file << "CaseID|CrimeType|Location|DateTime|Description|Evidence|Status" << endl;
}
    int caseID;
    string crimeType;
    string location;
    string dateTime;
    string description;
    string evidence;

    cout << "\n========== POST NEW CASE ==========\n";

    cout << "Enter Case ID: ";
    cin >> caseID;
    cin.ignore(1000, '\n');

    cout << "Enter Crime Type: ";
    getline(cin, crimeType);

    cout << "Enter Location: ";
    getline(cin, location);

    cout << "Enter Date and Time: ";
    getline(cin, dateTime);

    cout << "Enter Description: ";
    getline(cin, description);

    cout << "Enter Evidence File Path: ";
    getline(cin, evidence);

    file << caseID << "|"
         << crimeType << "|"
         << location << "|"
         << dateTime << "|"
         << description << "|"
         << evidence << "|"
         << "Ongoing Investigation"
         << endl;

    file.close();

    cout << "\nCase posted successfully!" << endl;
    cout << "Case status: Ongoing Investigation" << endl;
}

void Officer::searchCase() {
    searchCaseByID();
}

void Officer::requestCaseClosure() {

    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case data available yet.\n";
        return;
    }

    ofstream temp("temp.txt");

    if (!temp) {
        cout << "\nError creating temporary file.\n";
        file.close();
        return;
    }

    int searchID;

    cout << "\n========== REQUEST CASE CLOSURE ==========\n";
    cout << "Enter Case ID: ";
    cin >> searchID;

    string line;

    // Copy header
    getline(file, line);
    temp << line << endl;

    bool found = false;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        // Case ID
        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Crime Type
        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Location
        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Date and Time
        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Description
        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Evidence
        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Status
        status = line;

        if (stoi(caseID) == searchID) {

            found = true;

            cout << "\n========== CASE DETAILS ==========\n";
            cout << "Case ID: " << caseID << endl;
            cout << "Crime Type: " << crimeType << endl;
            cout << "Location: " << location << endl;
            cout << "Date and Time: " << dateTime << endl;
            cout << "Description: " << description << endl;
            cout << "Evidence: " << evidence << endl;
            cout << "Status: " << status << endl;

            if (status == "Ongoing Investigation") {

                status = "Case Closure Request";

                cout << "\nCase closure request submitted successfully!" << endl;
                cout << "Case status: Case Closure Request" << endl;
            }
            else if (status == "Case Closure Request") {

                cout << "\nA case closure request has already been submitted." << endl;
            }
            else {

                cout << "\nThis case cannot be submitted for closure." << endl;
                cout << "Only cases under Ongoing Investigation can be requested for closure." << endl;
            }
        }

        temp << caseID << "|"
             << crimeType << "|"
             << location << "|"
             << dateTime << "|"
             << description << "|"
             << evidence << "|"
             << status << endl;
    }

    file.close();
    temp.close();

    remove("cases.txt");
    rename("temp.txt", "cases.txt");

    if (!found) {
        cout << "\nCase ID not found.\n";
    }
}


void User::userVerify() {

    string enteredUsername;
    string enteredPassword;

    cout << "\n========== USER LOGIN ==========\n";

    cout << "Enter Username: ";
    cin >> enteredUsername;

    cout << "Enter Password: ";
    enteredPassword=getPassword();

    ifstream file("users.txt");

    if (!file) {
        cout << "\nNo user records found.\n";
        return;
    }

    string username;
    string password;
    bool found = false;

    while (file >> username >> password) {

        if (username == enteredUsername &&
            password == enteredPassword) {

            found = true;
            break;
        }
    }

    file.close();

    if (found) {

        cout << "\nUser Verified Successfully!" << endl;
        cout << "Loading User Dashboard..." << endl;

        userMenu();
    }
    else {

        cout << "\nInvalid User Login Details!" << endl;
    }
}
void User::userMenu() {

    int choice;

    while (true) {

        cout << "\n////////--- User Dashboard ---////////\n";
        cout << "1. Report Crime (Post)" << endl;
        cout << "2. Search Case" << endl;
        cout << "3. View All Cases" << endl;
        cout << "4. Logout" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            reportCrime();
        }
        else if (choice == 2) {
            searchCase();
        }
        else if (choice == 3) {
            viewAllCases();
        }
        else if (choice == 4) {
            cout << "\nLogging out..." << endl;
            break;
        }
        else {
            cout << "\nInvalid choice! Please enter 1-4.\n";
        }
    }
}

void User::userRegister() {

    string newUsername;
    string newPassword;

    cout << "\n========== USER REGISTRATION ==========\n";

    cout << "Enter Username: ";
    cin >> newUsername;

    cout << "Enter Password: ";
    newPassword=getPassword();

    ifstream checkFile("users.txt");

    string username;
    string password;
    bool exists = false;

    if (checkFile) {

        while (checkFile >> username >> password) {

            if (username == newUsername) {
                exists = true;
                break;
            }
        }

        checkFile.close();
    }

    if (exists) {
        cout << "\nUsername already exists!" << endl;
        return;
    }

    ofstream file("users.txt", ios::app);

    if (!file) {
        cout << "\nError creating user record.\n";
        return;
    }

    file << newUsername << " " << newPassword << endl;

    file.close();

    cout << "\nRegistration successful!" << endl;
    cout << "You can now login." << endl;
}
void User::userAuthMenu() {

    int choice;

    while (true) {

        cout << "\n////////--- User Authentication ---////////\n";
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Return to Main Menu" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input! Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            userRegister();
        }
        else if (choice == 2) {
            userVerify();
        }
        else if (choice == 3) {
            cout << "\nReturning to Main Menu..." << endl;
            break;
        }
        else {
            cout << "\nInvalid choice! Please enter 1-3.\n";
        }
    }
}

void User::reportCrime() {

    ofstream file("cases.txt", ios::app);

    if (!file) {
        cout << "\nError opening case file.\n";
        return;
    }

    int caseID;
    string crimeType;
    string location;
    string dateTime;
    string description;
    string evidence;

    cout << "\n========== REPORT CRIME ==========\n";

    cout << "Enter Case ID: ";
    cin >> caseID;
    cin.ignore(1000, '\n');

    cout << "Enter Crime Type: ";
    getline(cin, crimeType);

    cout << "Enter Location: ";
    getline(cin, location);

    cout << "Enter Date and Time: ";
    getline(cin, dateTime);

    cout << "Enter Description: ";
    getline(cin, description);

    cout << "Enter Evidence File Path: ";
    getline(cin, evidence);

    // Check whether cases.txt is empty
    ifstream checkFile("cases.txt");

    bool fileEmpty = checkFile.peek() == ifstream::traits_type::eof();

    checkFile.close();

    if (fileEmpty) {
        file << "CaseID|CrimeType|Location|DateTime|Description|Evidence|Status" << endl;
    }

    file << caseID << "|"
         << crimeType << "|"
         << location << "|"
         << dateTime << "|"
         << description << "|"
         << evidence << "|"
         << "Waiting Verification"
         << endl;

    file.close();

    cout << "\nCrime report submitted successfully!" << endl;
    cout << "Case ID: " << caseID << endl;
    cout << "Case Status: Waiting Verification" << endl;
}

void User::searchCase() {
    searchCaseByID();
}
void User::viewAllCases() {

    ifstream file("cases.txt");

    if (!file) {
        cout << "\nNo case data available yet.\n";
        return;
    }

    string line;

    // Skip header
    getline(file, line);

    bool found = false;

    cout << "\n========== ALL CASES ==========\n";

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        string caseID;
        string crimeType;
        string location;
        string dateTime;
        string description;
        string evidence;
        string status;

        size_t pos;

        // Case ID
        pos = line.find('|');
        caseID = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Crime Type
        pos = line.find('|');
        crimeType = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Location
        pos = line.find('|');
        location = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Date and Time
        pos = line.find('|');
        dateTime = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Description
        pos = line.find('|');
        description = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Evidence
        pos = line.find('|');
        evidence = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Status
        status = line;

        cout << "\n-----------------------------------\n";
        cout << "Case ID: " << caseID << endl;
        cout << "Crime Type: " << crimeType << endl;
        cout << "Location: " << location << endl;
        cout << "Date and Time: " << dateTime << endl;
        cout << "Description: " << description << endl;
        cout << "Evidence: " << evidence << endl;
        cout << "Status: " << status << endl;

        found = true;
    }

    file.close();

    if (!found) {
        cout << "\nNo cases available.\n";
    }
}

void immediateHelpRequest()
{
    int requestID = 1;

    string phoneNumber;
    string latitude;
    string longitude;

    cout << "\n===== IMMEDIATE HELP REQUEST =====\n";

    cout << "Enter your Phone Number: ";
    cin >> phoneNumber;

    cout << "Enter your Latitude: ";
    cin >> latitude;

    cout << "Enter your Longitude: ";
    cin >> longitude;

    // Read the previous Request ID from the file
    ifstream readFile("help_requests.txt");
    string line;
    int lastRequestID = 0;

    while (getline(readFile, line))
    {
        if (!line.empty())
        {
            size_t position = line.find('|');

            if (position != string::npos)
            {
                int currentID = stoi(line.substr(0, position));

                if (currentID > lastRequestID)
                {
                    lastRequestID = currentID;
                }
            }
        }
    }

    readFile.close();

    // Generate the next Request ID
    requestID = lastRequestID + 1;

    // Open file in append mode
    ofstream file("help_requests.txt", ios::app);

    if (!file)
    {
        cout << "Error: Unable to open help_requests.txt\n";
        return;
    }

    // Store the help request
    file << requestID << "|"
         << phoneNumber << "|"
         << latitude << "|"
         << longitude << "|"
         << "Pending"
         << endl;

    file.close();

    cout << "\nImmediate help request submitted successfully.\n";
    cout << "Request ID: " << requestID << endl;
    cout << "Status: Pending\n";
}
void helpMenu()
{
    int choice;

    while (true)
    {
        cout << "\n========== HELP MENU ==========\n";
        cout << "1. Immediate Help Request\n";
        cout << "2. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            immediateHelpRequest();
        }
        else if (choice == 2)
        {
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
int main() {

    mainMenu();

    return 0;
}