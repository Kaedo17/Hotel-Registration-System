#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

fstream authenticator;

void staffSignIn(int staffAcc);
void loginMenu(string staffUserName, string staffPasswd);
void signInMenu();
void staffMenu();

int main() {
    int userInput;
    int staffAcc;

    system("CLS");

    do {
        cout << "                   Sign In\n";
        cout << "  [1] Staff\n";
        cout << "  [2] Customer\n";
        cout << "  [3] Save and Exit\n";
        cout << "<====================================>\n\n";
        cout << "Input: ";
        cin >> userInput;
        system("CLS");

        switch (userInput) {
            case 1: 
                staffSignIn(staffAcc);
                system("CLS");
                break;

            case 2:
                // Add customer functionality here if needed
                break;

            default:
                break;
        }
    } while (userInput != 3);
}

void staffSignIn(int staffAcc) {
    string staffUserName;
    string staffPasswd;

    while (true) {
        cout << "           Staff Sign In\n";
        cout << "  [1] Login\n";
        cout << "  [2] Sign in\n";
        cout << "  [3] Back\n";
        cout << "Input: ";
        cin >> staffAcc;
        if (cin.fail() || staffAcc >= 4 || staffAcc == '\0') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
        } else if (staffAcc == 1) {
            loginMenu(staffUserName, staffPasswd);
        } else if (staffAcc == 2) {
            signInMenu();
        } else if (staffAcc == 3) {
            main();
        } else {
            system("CLS");
            break;
        }
    }
}

void loginMenu(string staffUserName, string staffPasswd) {
    authenticator.open("authenticator.txt", ios::in);
    bool userAuthenticated = false;

    system("CLS");
    cout << "           Login\n";
    cout << "Username: ";
    cin >> staffUserName;
    cout << "Password: ";
    cin >> staffPasswd;

    string fileUserName, filePasswd;

    if (!authenticator.is_open()) {
        cerr << "Error: Authenticator File is Missing!" << endl;
        return;
    }

    // Read the username and password from the file in pairs
    while (getline(authenticator, fileUserName) && getline(authenticator, filePasswd)) {
        cout << "Checking: " << fileUserName << " " << filePasswd << endl; // Debugging output
        if (fileUserName == staffUserName && filePasswd == staffPasswd) {
            userAuthenticated = true;
            break;
        }
    }

    authenticator.close();

    if (userAuthenticated) {
        cout << "Login successful!\n"; // Add a success message
        staffMenu();
    } else {
        cout << "Wrong Credentials\n"; // Indicate failure
    }
}

void signInMenu() {
    system("CLS");
    string signInUsername;
    string signInPasswd;
    cout << "           Sign In\n";
    cout << "Create Username: ";
    cin >> signInUsername;
    cout << "Create Password: ";
    cin >> signInPasswd;

    // Open file in append mode
    authenticator.open("authenticator.txt", ios::app);
    if (!authenticator.is_open()) {
        cerr << "Error: Authenticator File is Missing!" << endl;
        return;
    }

    // Write the username and password, each on a new line
    authenticator << signInUsername << endl << signInPasswd << endl; 
    authenticator.close();

    cout << "Account created successfully!\n";
    system("CLS");
    main();
}

void staffMenu() {
    // Staff menu functionality can be implemented here
}
