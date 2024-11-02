#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
using namespace std;

fstream authenticator;

void staffSignIn();
void loginMenu();
void signInMenu();
void staffMenu();
void loginError();
void signInSuccess();
void forgotPass();


int main() {

    int userInput;

    system("CLS");

    do
    {
        cout << "                   Sign In\n";
        cout << "<====================================>\n";
        cout << "  [1] Staff\n";
        cout << "  [2] Customer\n";
        cout << "  [3] Save and Exit\n";
        cout << "<====================================>\n\n";
        cout << "Input: ";
        cin >> userInput;

        if (cin.fail() || userInput >=4 || userInput <=0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 to 3.\n";
            cout << "<====================================>\n";
            system("pause");
            main();
            system("CLS");

        }


        switch (userInput)
        {
        case 1: staffSignIn();
            system("CLS");
            
            break;

        case 2:

        
        default:
            break;
        }
        } while (userInput !=3);
    
}

void staffSignIn(){
    system("CLS");
        string staffUserName;
        string staffPasswd;
        int staffAcc;

        while (true) {
            cout << "           Staff Sign In\n";
            cout << "<====================================>\n";
            cout << "  [1] Login\n";
            cout << "  [2] Sign in\n";
            cout << "  [3] Back\n";
            cout << "<====================================>\n";
            cout << "Input: ";
            cin >> staffAcc;

            //error handling if input is not what is expected

            if (cin.fail() || staffAcc >= 4 || staffAcc <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
              
                cout << "Invalid input. Please enter a number between 1 to 3.\n";
                cout << "<===========================================>\n";
                system("pause");
                staffSignIn();
                system("CLS");

            } 
            
            if (staffAcc ==1) {
                loginMenu();
                break;
            } else if (staffAcc == 2){
                signInMenu();
                break;
            } else if (staffAcc == 3){
                main();
                break;
            }
        }

            
    
}

void loginMenu(){

    string staffUserName;
    string staffPasswd;
    string forgotten;
    bool userAuthenticated = false;

    system("CLS");
    cout << "           Login [Type 'Back' to return]\n";
    cout << "<====================================>\n";
    cout << "Username: ";
    cin >> staffUserName;
    


    if (staffUserName == "Back" || staffUserName == "back") { // added back option in case of user mis clicked an option
        
        staffSignIn();
    }

    cout << "type [forgot] if you forgot your password\n";

    cout << "Password: ";
    cin >> staffPasswd;

    if (staffPasswd == "Back" || staffPasswd == "back") {
        
        staffSignIn();
    } else if (staffPasswd == "forgot" || staffPasswd == "Forgot") {
        forgotPass();
        system("CLS");
    }

    string fileUserName;
    string filePasswd;

    authenticator.open("authenticator.txt", ios::in);
    if (!authenticator.is_open()){
        cerr << "Error: Authenticator File is Missing!";
        return;
    }

    // loop that reads data from the txt
// transfers data from the text to a variable "fileUserName and filePasswd"
    while (getline(authenticator, fileUserName) && getline(authenticator, filePasswd)) {
        //cout << fileUserName << " " << filePasswd;
        if (fileUserName == staffUserName && filePasswd == staffPasswd) {
            userAuthenticated = true;
            break;
        }
    }

    authenticator.close();

    if (userAuthenticated == true){ // if login successful, goes to the option for STAFF
        staffMenu();

    } else if (userAuthenticated == false){ // if login is unsuccessful, shows login error
        loginError();
    }


}

void signInMenu(){
    system("CLS"); // clears the console screen

    string signInUsername;
    string signInPasswd;

    cout << "           Sign In [Type 'Back' to return]\n";
    cout << "Create Username: ";
    cin >> signInUsername;

    // back option if user want to go back

    if (signInUsername == "Back" || signInUsername == "back") {
        staffSignIn();
    }

    cout << "Create Password: ";
    cin >> signInPasswd;

    if (signInPasswd == "Back" || signInPasswd == "back") {
        staffSignIn();
    }

// checks if the txt file is present

    authenticator.open("authenticator.txt", ios::in); // opens the authenticator txt file
    if (!authenticator.is_open()){
        cerr << "Error: Authenticator File is Missing!";
        return;
    }

    string accExisted;
    bool usernameExists = false;

    while (authenticator >> accExisted) { //gets the username and password from the text file and assign in to the variable accExisted
        if (accExisted == signInUsername) { //if the user input matches one of the username 
            usernameExists = true;
            break;
        }
    }

    authenticator.close();

    if (usernameExists == true) {
        cout << "Username already exists!\n";
        cout << "<===========================================>\n";
        system("pause");
        signInMenu();
        system("CLS");
        return;
    }

    authenticator.open("authenticator.txt", ios::app);
    if (!authenticator.is_open()){
        cerr << "Error: Authenticator File is Missing!";
        return;
    }

    // if the creation of the username and password is successfull then the code below wil insert
    // the username and password to the file

    authenticator << signInUsername<< endl << signInPasswd << endl;
    authenticator.close(); // will close the file

    signInSuccess(); // display sign in was successful

}

// the things staff can do 

void staffMenu(){

    system("CLS");

    int userInput;
    cout << "               || STAFF MENU ||\n";
    cout << "<===========================================>\n";
    cout << " [1]  Available Rooms\n";
    cout << " [2]  Bookings\n";
    cout << " [3]  Reservations\n";
    
    while (true) {
        cout << "Input: ";
        cin >> userInput;

        if (cin.fail()){

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
            cout << "Input Error\n";
            cout << "<===========================================>\n";
            system("pause");

            staffMenu();
            system("CLS");
        } else {
            
        }

        
    }
    

    system("CLS");
}

// login error

void loginError(){

    cout << "<===========================================>\n";
    cout << "Wrong Credentials\n";
    cout << "<===========================================>\n";
    system("pause");
    loginMenu();
    system("CLS");

}

// successful login message

void signInSuccess(){

    cout << "<===========================================>\n";
    cout << "Sign in Success!\n";
    cout << "<===========================================>\n";
    system("pause");

    staffSignIn();
    system("CLS");

    

}

void forgotPass(){
    system("CLS");
    string entrUser;
    string newPasswd;
    cout << "Enter Username: ";
    cin >> entrUser;
    cout << "Enter New Password: ";
    cin >> newPasswd;

    authenticator.open("authenticator.txt", ios::in);
    if (!authenticator.is_open()) {
        cerr << "Authenticator file is missing!";
        return;
    }

    

    vector <pair<string, string>> userRecords;
    bool userVerify = false;

    string forgotUser;
    string oldPass;

    while (getline(authenticator, forgotUser) && getline(authenticator, oldPass)) {
        if(entrUser == forgotUser) {
            userRecords.push_back(make_pair(forgotUser, newPasswd));
            userVerify = true;
        } else {
            userRecords.push_back(make_pair(forgotUser, oldPass));
        }
        
    }

    authenticator.close();

    if (!userVerify) {
        cout << "User not found!\n";
        return;
    }
    
    cout << "Password successfully updated!\n";

}




















// https://www.youtube.com/watch?v=TUBVZvzEQAs
// https://cplusplus.com/reference/utility/make_pair/
// https://stackoverflow.com/questions/50325078/how-to-send-an-error-message-when-c-string-user-input-empty