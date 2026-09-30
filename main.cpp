#include <iostream>
#include <string>
#include <fstream>

using namespace std;


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
};


void Admin::adminVerify() {

    cout << "Enter username: ";
    cin >> username;

    cout << "\nEnter password: ";
    cin >> password;

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
    cin >> officerPassword;

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

            cout << "\nReview Officer Decisions will be implemented later.\n";

        }

        else if (choice == 3) {

            cout << "\nUser Review System will be implemented later.\n";

        }

        else if (choice == 4) {

            cout << "\nCase Statistics will be implemented later.\n";

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
            cin >> newPassword;

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
    // We will implement this later
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

        // officerMenu() will be implemented
    }

    else if (choice == 'c' || choice == 'C') {

        // userMenu() will be implemented
    }

    else if (choice == 'd' || choice == 'D') {

        // helpMenu() will be implemented
    }

    else if (choice == 'e' || choice == 'E') {

        cout << "Exiting CrimeAssist..." << endl;
        return;
    }

    else {

        cout << "Invalid choice!" << endl;
    }
}


int main() {

    mainMenu();

    return 0;
}