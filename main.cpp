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
void availRooms();
void myBookings();
void myReservations();
void customerMenu();
void reserveRooms();
void reserveFileFunc();
void bookARoom();
void safetyInput();
void reserveRoomsDisplayFunc();



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
            system("CLS");
            main();
            

        }

        if (userInput == 1){
            staffSignIn();
            system("CLS");
        } else if (userInput ==2) {
            customerMenu();
            system("CLS");
        }


        
        } while (userInput !=3);

        return 0;
    
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
                system("CLS");
                continue;
                

            } 
            
            if (staffAcc ==1) {
                loginMenu();
                break;
            } else if (staffAcc == 2){
                signInMenu();
                break;
            } else if (staffAcc == 3){
                return;
                break;
            }
        }

            
    
}

void loginMenu(){

    string staffUserName;
    string staffPasswd;
    string forgotten;
    bool userAuthenticated = false;

    while (true)
    {
        system("CLS");
    cout << "           Login [Type 'Back' to return]\n";
    cout << "<====================================>\n";
    cout << "[1] Back\n";
    cout << "[2] Forgot Password\n";
    cout << "Username: ";
    cin >> staffUserName;

    if (staffUserName == "1") { // added back option in case of user mis clicked an option
        staffSignIn();
        system("CLS");
        return;

    } else if (staffUserName == "2") {
        forgotPass();
        system("CLS");
        return;
        
    }

    

    cout << "Password: ";
    cin >> staffPasswd;

    if (staffPasswd == "1") {
        system("CLS");
        continue;
    } else if (staffPasswd == "2") {
        forgotPass();
        system("CLS");
        return;
        
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
    while (authenticator >> fileUserName >> filePasswd) {
        
        if (fileUserName == staffUserName && filePasswd == staffPasswd) {
            userAuthenticated = true;
            break;
        }
    }

    authenticator.close();

    if (userAuthenticated == true){ // if login successful, goes to the option for STAFF
        staffMenu();
        system("CLS");
        return;

    } else if (userAuthenticated == false){ // if login is unsuccessful, shows login error
        loginError();
        system("CLS");
        return;
    }
    }
    



}

void signInMenu(){
    system("CLS"); // clears the console screen

    string signInUsername;
    string signInPasswd;

    while (true) {
        cout << "           Sign In\n";
    cout << "[1] Back\n";
    cout << "Create Username: ";
    cin >> signInUsername;

    // back option if user want to go back

    if (signInUsername == "1") {
        staffSignIn();
        system("CLS");
        return;
    }

    cout << "Create Password: ";
    cin >> signInPasswd;

    if (signInPasswd == "1") {
        system("CLS");
        continue;
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

    authenticator << signInUsername<< " " << signInPasswd << endl;
    authenticator.close(); // will close the file

    signInSuccess(); // display sign in was successful

    return;
    }
    

}

// the things staff can do 

void staffMenu(){

    system("CLS");

    int userInputStaff;
    
    
    while (true) {

        cout << "               || STAFF MENU ||\n";
        cout << "<===========================================>\n";
        cout << " [1]  Available Rooms\n";
        cout << " [2]  Bookings\n";
        cout << " [3]  Reservations\n";
        cout << " [4]  Save and Exit\n";
        cout << "Input: ";
        cin >> userInputStaff;

        if (cin.fail() || userInputStaff >=5 || userInputStaff <=0){

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
            cout << "Input Error\n";
            cout << "<===========================================>\n";
            system("pause");
            system("CLS");
            continue;
            
        }

        if (userInputStaff == 1) {
            availRooms();
            system("CLS");
            return;
            
        } else if (userInputStaff == 2){
            myBookings();
            system("CLS");
            return;
        } else if (userInputStaff == 3){
            myReservations();
            system("CLS");
            return;
        } else if (userInputStaff == 4){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
            return;
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
    system("CLS");
    loginMenu();
    

}

// successful login message

void signInSuccess(){

    cout << "<===========================================>\n";
    cout << "Sign in Success!\n";
    cout << "<===========================================>\n";
    system("pause");
    system("CLS");
    staffSignIn();
    

    

}

void forgotPass(){
    system("CLS");
    string entrUser;
    string newPasswd;
    
    while (true)
    {
        cout << "       F O R G O T    P A S S W O R D\n";
        cout << "<===========================================>\n";

        cout << "[1] Back\n";

        cout << "Enter Username: ";
        cin >> entrUser;

        if (entrUser == "1") {
            staffSignIn();
            return;
        }

        cout << "Enter New Password: ";
        cin >> newPasswd;

        if (newPasswd == "1") {
            forgotPass();
            return;
        }

        authenticator.open("authenticator.txt", ios::in);
        if (!authenticator.is_open()) {
            cerr << "Authenticator file is missing!";
            return;
        }

        

        vector <pair<string, string>> userRecords;
        bool userFound = false;

        string forgotUser;
        string oldPass;

        while (authenticator >> forgotUser >> oldPass) {
            if(entrUser == forgotUser) {
                userRecords.push_back(make_pair(forgotUser, newPasswd));
                userFound = true;
            } else {
                userRecords.push_back(make_pair(forgotUser, oldPass));
            }
            
        }

        authenticator.close();

        if (!userFound) {
            cout << "User not found!\n";
            return;
        }

        fstream updatedAuth("authenticator.txt", ios::out | ios::trunc);

        if (!updatedAuth.is_open()){
            cerr << "Authenticator file not found!\n";
            return;
        }

        for (const auto& record : userRecords) {
            updatedAuth << record.first << " " << record.second << endl;
        }

        updatedAuth.close();

        cout << "<===========================================>\n";
        
        cout << "Password successfully updated!\n";
        system("pause");
        system("CLS");
        staffSignIn();
        return;
        }
    

}

fstream roomOne;

void availRooms(){
    
    
    string roomsOne;
    string roomInput;

    
    while (true)
    {

        system("CLS");

        cout << "       A V A I L A B L E   R O O M S\n";
        cout << "<===========================================>\n";
        roomOne.open("firstFloorRooms.txt", ios::in);

        if (!roomOne.is_open()) {
            cout << "Available room file is missing\n";
            return;
        }
        if (roomOne.is_open())
        {
            while (getline(roomOne, roomsOne)) {
            cout << roomsOne << endl;
            }
        }

        roomOne.close();
    
    
        

        cout << "Input: ";

        cin >> roomInput;

        if (cin.fail() || roomInput >= "4" || roomInput <="0") {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            system("pause");
            system("CLS");
            continue;


        }

        if (roomInput == "1") {
            system ("CLS");
            staffMenu();
            
            return;
        } else if (roomInput == "2")
        {
            myBookings();
        }
    
    
    
    }   

    
    
}

fstream booKings;

void myBookings(){
    string bookingText;
    int bookingInput;
    system("CLS");
    cout << "B O O K I N G S\n";

    booKings.open("bookings.txt", ios::in);

    if (!booKings.is_open()) {
        cout << "Available file is missing\n";
        return;
    }

    if (booKings.is_open()) {
        while (getline(booKings, bookingText))
        {
            cout << bookingText;
            
        }
        
    }

    booKings.close();

    cout << "       [1] Back  [2] Confirm a booking\n";
    cout << "<===========================================>\n";

    cin >> bookingInput;

        if (bookingInput == 2) {
            string bookingNumber;
            system("CLS");

            booKings.open("bookings.txt", ios::in);

            if (!booKings.is_open()) {
                cout << "Available file is missing\n";
                return;
            }

            if (booKings.is_open()) {
                while (getline(booKings, bookingText))
                {
                    cout << bookingText;
                    
                }
                
            }

            string bookingConfirmed;

            cout << "Confirm number: ";
            cin >> bookingNumber;

            roomOne.open("fistFloorRooms.txt", ios::in);
            if (!roomOne.is_open()) {
                cout << "Available room file is missing\n";
                return;
            }

            if (roomOne.is_open()){
                while (getline(roomOne, bookingConfirmed))
                {
                    if (bookingConfirmed == bookingNumber){

                    }
                }
                
            }

            roomOne.close();

            
    }

}

void myReservations(){
    while (true) {
        fstream myReservations;
        string displayReservation;
        string transferReservation;
        string confirmReservationUser;
        string confirmReservationRoomNumber;

        cout << "R E S E R V A T I O N  L I S T\n";
        cout << "[1] Back\n";

        myReservations.open("reservedRoomsLists.txt", ios::in);

        if (!myReservations.is_open()) {
            cerr << "File not found!";
            return;
        } else if (myReservations.is_open()) {
            while (getline(myReservations, displayReservation)) {
                cout << "[*] " << displayReservation;
            }
        }

        myReservations.close();

        cout << "Enter User; [1] to go back: ";
        cin >> confirmReservationUser;

        string findMatchUser;
        string findMatchRoomNumber;
        bool userMatch = false;

        myReservations.open("reservedRoomsLists.txt", ios::in);

        if (!myReservations.is_open()) {
            cerr << "File not found!";
            return;
        } else if (myReservations.is_open()) {
            while (myReservations >> findMatchUser >> findMatchRoomNumber) {
                if (findMatchUser == confirmReservationUser) {
                    userMatch = true;
                    break;
                }
            }
        }

        myReservations.close();

        int reservationOptions;

        if (!userMatch) {
            cout << "No user matching...";
            continue;
        } else if (userMatch == true) {
            cout << "[1] Confirm    [2] Delete  [3] Cancel\n";
            cout << "Options: ";
            cin >> reservationOptions;

        }

        if (reservationOptions == 1)

        

        if (confirmReservationUser == "1") {
            system("CLS");
            staffMenu();
            return;
        }

        if (cin.fail()) {
            safetyInput();
            cout << "Input error\n";
            system("pause");
            system("CLS");
            continue;
        }
    }

    
}

void customerMenu() {
    system("CLS");
    int customerInput;
    while (true)
    {
        cout << "               Customer Menu\n";
        cout << "<===========================================>\n";
        cout << "  [1] Back\n";
        cout << "  [2] Book a room\n";
        cout << "  [3] Reserve Rooms\n";

        cout << "<===========================================>\n";

        cout << "Input: ";

        cin >> customerInput;

        if(cin.fail() || customerInput >=4 || customerInput <=0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input\n";
            system("pause");
            system("CLS");
            continue;
        } else if(customerInput == 1) {
            safetyInput();
            system("CLS");
           // main();
            return;

        } else if(customerInput ==3) {
            system("CLS");
            reserveRooms();
            return;
        } else if (customerInput == 2) {
            system("CLS");
            bookARoom();
        }

    }
     
}

void reserveRooms() {
    
    int reserveInput;

        while (true)
        {

            system("CLS");
            reserveRoomsDisplayFunc();

            cout << "Input: ";
            cin >> reserveInput;

            

            if(cin.fail() || reserveInput >=4 || reserveInput <=0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Input\n";
                system("pause");
                system("CLS");
                continue;
            } else if (reserveInput == 1) {
                safetyInput();
                customerMenu();
                return;
            } else if (reserveInput ==2) {
                reserveFileFunc();
                return;
            }
        
    
    }
    
    
}

void reserveFileFunc() {
    system("CLS");
    reserveRoomsDisplayFunc();


        string reserveRoomNumber;
        string reserveListOutput;
        string reserveUsername;
        string roomNumbers[15] = {"101", "102", "103", "104", "105", "201", "202", "203", "204", "205", "301", "302", "303", "304", "305"};

        cout << "Input Username: ";
        cin >> reserveUsername;

        cout << "Input room number to reserve eg. 201 \n";
        cout << "Input: ";

        cin >> reserveRoomNumber;
        fstream reserveListFile;
        reserveListFile.open("reservedRoomsLists.txt", ios::app);
        
        if (!reserveListFile.is_open()) {
            cerr << "Error: Authenticator File is Missing!";
            return;
        } else if (reserveListFile.is_open()) {
            
            if (reserveRoomNumber == "101" || reserveRoomNumber ==  "102" || reserveRoomNumber ==  "103" || reserveRoomNumber ==  "104" || reserveRoomNumber ==  "105" || reserveRoomNumber ==  "201" || reserveRoomNumber ==  "202" || reserveRoomNumber ==  "203" || reserveRoomNumber ==  "204" || reserveRoomNumber ==  "205" || reserveRoomNumber ==  "301" || reserveRoomNumber ==  "302" || reserveRoomNumber ==  "303" || reserveRoomNumber ==  "304" || reserveRoomNumber ==  "305") {
                
                cout << "Successfully Reserved!\n";
                system("pause");
                reserveListFile << reserveUsername << " " << reserveRoomNumber << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                reserveRooms();
            } else {
                cout << "Room not available\n";
                system("pause");
                system("CLS");
                reserveFileFunc();
                //continue;
            }
            


        }
        
        
    }

void reserveRoomsDisplayFunc() {
    fstream theReservedList;
    string theRooms;
    cout << "               Room Reservation\n";
        cout << "<===========================================>\n";
        cout << "  [1] Back    [2] Choose room number \n";

        theReservedList.open("availRooms.txt", ios::in);

        if (!theReservedList.is_open()) {
            cout << "Available room file is missing\n";
            return;
        } else if (theReservedList.is_open())
        {
            while (getline(theReservedList, theRooms)) {
            // system("CLS");
                cout << theRooms << endl;
            }
        }
        theReservedList.close();
}

void safetyInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void bookARoom(){

}

















// https://stackoverflow.com/questions/29859796/c-auto-vs-auto#:~:text=So%2C%20in%20a%20nutshell%2C%20if,you%20want%20references%2C%20use%20auto%26%20.
// https://www.youtube.com/watch?v=2vOPEuiGXVo
// https://www.youtube.com/watch?v=TUBVZvzEQAs
// https://cplusplus.com/reference/utility/make_pair/
// https://stackoverflow.com/questions/50325078/how-to-send-an-error-message-when-c-string-user-input-empty