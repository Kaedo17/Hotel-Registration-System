#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

fstream authenticator;

void staffSignIn();
void loginMenu();
void signInMenu();
void staffMenu();
void loginError();
void loginSuccess();


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
        system("CLS");


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
            if (cin.fail() || staffAcc >= 4 || staffAcc == '\0') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("CLS");
            } else if (staffAcc ==1) {
                loginMenu();
            } else if (staffAcc == 2){
                signInMenu();
            } else if (staffAcc == 3){
                main();
            } else {
                system("CLS");
                break;
                
            }
        }

            
    
}

void loginMenu(){

    string staffUserName;
    string staffPasswd;
    bool userAuthenticated = false;

    system("CLS");
    cout << "           Login [Type 'Back' to return\n";
    cout << "<====================================>\n";
    cout << "Username: ";
    cin >> staffUserName;
    


    if (staffUserName == "Back" || staffUserName == "back") {
        
        staffSignIn();
    }

    cout << "Password: ";
    cin >> staffPasswd;

    if (staffPasswd == "Back" || staffPasswd == "back") {
        
        staffSignIn();
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

    if (userAuthenticated == true){
        staffMenu();

    } else if (userAuthenticated == false){
        loginError();
    }


}

void signInMenu(){
    system("CLS");
    string signInUsername;
    string signInPasswd;
    cout << "           Sign In\n";
    cout << "Create Username: ";
    cin >> signInUsername;
    cout << "Create Password: ";
    cin >> signInPasswd;

    authenticator.open("authenticator.txt", ios::app);
    if (!authenticator.is_open()){
        cerr << "Error: Authenticator File is Missing!";
        return;
    }

    authenticator << signInUsername<< endl << signInPasswd << endl;
    authenticator.close();

    loginSuccess();

}

void staffMenu(){

    system("CLS");
    cout << "|| STAFF MENU ||\n";
    cout << "<===========================================>\n";
    cout << "   Available Rooms\n";
    cout << "   Bookings\n";
    cout << "   Reservations\n";

    system("pause");
    system("CLS");
}

void loginError(){

    int loginBack;
    cout << "<===========================================>\n";
    cout << "Wrong Credentials\n";
    cout << "Press [1] to return to Login page\n";
    cout << "<===========================================>\n";
    cout << "Input: ";

    cin >> loginBack;

    if (loginBack == 1) {
        staffSignIn();
    }

}

void loginSuccess(){

    int signInBack;
    cout << "<===========================================>\n";
    cout << "Sign in Success!\n";
    cout << "Press [1] to return to Login page\n";
    cout << "<===========================================>\n";
    cout << "Input: ";

    cin >> signInBack;

    if (signInBack == 1) {
        staffSignIn();
    }

}






















// https://stackoverflow.com/questions/50325078/how-to-send-an-error-message-when-c-string-user-input-empty