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
void myReservationsFunc();
void customerMenu();
// void reserveRooms();
void reserveFileFunc();
void bookARoom();
void safetyInput();
void reserveRoomsDisplayFunc();
void userConfirmation();
void reservationListConfirmDelDisplay();
void deleteUserReservation();
void confirmBooking();

int main()
{

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

        if (cin.fail() || userInput >= 4 || userInput <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 to 3.\n";
            cout << "<====================================>\n";
            system("pause");
            system("CLS");
            continue;
        }

        if (userInput == 1)
        {
            staffSignIn();
            system("CLS");
        }
        else if (userInput == 2)
        {
            customerMenu();
            system("CLS");
        }
        else if (userInput == 3)
        {
            exit(0);
        }

    } while (true);

    return 0;
}

void staffSignIn()
{
    system("CLS");
    string staffUserName;
    string staffPasswd;
    int staffAcc;

    while (true)
    {
        cout << "           Staff Sign In\n";
        cout << "<====================================>\n";
        cout << "  [1] Login\n";
        cout << "  [2] Sign in\n";
        cout << "  [3] Back\n";
        cout << "<====================================>\n";
        cout << "Input: ";
        cin >> staffAcc;

        // error handling if input is not what is expected

        if (cin.fail() || staffAcc >= 4 || staffAcc <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number between 1 to 3.\n";
            cout << "<===========================================>\n";
            system("pause");
            system("CLS");
            continue;
        }

        if (staffAcc == 1)
        {
            loginMenu();
            break;
        }
        else if (staffAcc == 2)
        {
            signInMenu();
            break;
        }
        else if (staffAcc == 3)
        {
            return;
            break;
        }
    }
}

void loginMenu()
{

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

        if (staffUserName == "1")
        { // added back option in case of user mis clicked an option
            staffSignIn();
            system("CLS");
            return;
        }
        else if (staffUserName == "2")
        {
            forgotPass();
            system("CLS");
            return;
        }

        cout << "Password: ";
        cin >> staffPasswd;

        if (staffPasswd == "1")
        {
            system("CLS");
            continue;
        }
        else if (staffPasswd == "2")
        {
            forgotPass();
            system("CLS");
            return;
        }

        string fileUserName;
        string filePasswd;

        authenticator.open("authenticator.txt", ios::in);
        if (!authenticator.is_open())
        {
            cerr << "Error: Authenticator File is Missing!";
            return;
        }

        // loop that reads data from the txt
        // transfers data from the text to a variable "fileUserName and filePasswd"
        while (authenticator >> fileUserName >> filePasswd)
        {

            if (fileUserName == staffUserName && filePasswd == staffPasswd)
            {
                userAuthenticated = true;
                break;
            }
        }

        authenticator.close();

        if (userAuthenticated == true)
        { // if login successful, goes to the option for STAFF
            staffMenu();
            system("CLS");
            return;
        }
        else if (userAuthenticated == false)
        { // if login is unsuccessful, shows login error
            loginError();
            system("CLS");
            return;
        }
    }
}

void signInMenu()
{
    system("CLS"); // clears the console screen

    string signInUsername;
    string signInPasswd;

    while (true)
    {
        cout << "           Sign In\n";
        cout << "[1] Back\n";
        cout << "Create Username: ";
        cin >> signInUsername;

        // back option if user want to go back

        if (signInUsername == "1")
        {
            staffSignIn();
            system("CLS");
            return;
        }

        cout << "Create Password: ";
        cin >> signInPasswd;

        if (signInPasswd == "1")
        {
            system("CLS");
            continue;
        }

        // checks if the txt file is present

        authenticator.open("authenticator.txt", ios::in); // opens the authenticator txt file
        if (!authenticator.is_open())
        {
            cerr << "Error: Authenticator File is Missing!";
            return;
        }

        string accExisted;
        bool usernameExists = false;

        while (authenticator >> accExisted)
        { // gets the username and password from the text file and assign in to the variable accExisted
            if (accExisted == signInUsername)
            { // if the user input matches one of the username
                usernameExists = true;
                break;
            }
        }

        authenticator.close();

        if (usernameExists == true)
        {
            cout << "Username already exists!\n";
            cout << "<===========================================>\n";
            system("pause");
            signInMenu();
            system("CLS");
            return;
        }

        authenticator.open("authenticator.txt", ios::app);
        if (!authenticator.is_open())
        {
            cerr << "Error: Authenticator File is Missing!";
            return;
        }

        // if the creation of the username and password is successfull then the code below wil insert
        // the username and password to the file

        authenticator << signInUsername << " " << signInPasswd << endl;
        authenticator.close(); // will close the file

        signInSuccess(); // display sign in was successful

        return;
    }
}

// the things staff can do

void staffMenu()
{

    system("CLS");

    int userInputStaff;

    while (true)
    {

        cout << "               || STAFF MENU ||\n";
        cout << "<===========================================>\n";
        cout << " [1]  Available Rooms\n";
        cout << " [2]  Bookings\n";
        cout << " [3]  Reservations\n";
        cout << " [4]  Save and Exit\n";
        cout << "Input: ";
        cin >> userInputStaff;

        if (cin.fail() || userInputStaff >= 5 || userInputStaff <= 0)
        {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
            cout << "Input Error\n";
            cout << "<===========================================>\n";
            system("pause");
            system("CLS");
            continue;
        }

        if (userInputStaff == 1)
        {
            availRooms();
            system("CLS");
            return;
        }
        else if (userInputStaff == 2)
        {
            myBookings();
            system("CLS");
            return;
        }
        else if (userInputStaff == 3)
        {
            myReservationsFunc();
            system("CLS");
            return;
        }
        else if (userInputStaff == 4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
            main();
            return;
        }
    }

    system("CLS");
}

// login error

void loginError()
{

    cout << "<===========================================>\n";
    cout << "Wrong Credentials\n";
    cout << "<===========================================>\n";
    system("pause");
    system("CLS");
    loginMenu();
}

// successful login message

void signInSuccess()
{

    cout << "<===========================================>\n";
    cout << "Sign in Success!\n";
    cout << "<===========================================>\n";
    system("pause");
    system("CLS");
    staffSignIn();
}

void forgotPass()
{
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

        if (entrUser == "1")
        {
            staffSignIn();
            return;
        }

        cout << "Enter New Password: ";
        cin >> newPasswd;

        if (newPasswd == "1")
        {
            forgotPass();
            return;
        }

        authenticator.open("authenticator.txt", ios::in);
        if (!authenticator.is_open())
        {
            cerr << "Authenticator file is missing!";
            return;
        }

        vector<pair<string, string>> userRecords;
        bool userFound = false;

        string forgotUser;
        string oldPass;

        while (authenticator >> forgotUser >> oldPass)
        {
            if (entrUser == forgotUser)
            {
                userRecords.push_back(make_pair(forgotUser, newPasswd));
                userFound = true;
            }
            else
            {
                userRecords.push_back(make_pair(forgotUser, oldPass));
            }
        }

        authenticator.close();

        if (!userFound)
        {
            cout << "User not found!\n";
            return;
        }

        fstream updatedAuth("authenticator.txt", ios::out | ios::trunc);

        if (!updatedAuth.is_open())
        {
            cerr << "Authenticator file not found!\n";
            return;
        }

        for (const auto &record : userRecords)
        {
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

void availRooms()
{

    string roomsOne;
    string roomInput;

    while (true)
    {

        system("CLS");

        cout << "       A V A I L A B L E   R O O M S\n";
        cout << "<===========================================>\n";
        roomOne.open("firstFloorRooms.txt", ios::in);

        if (!roomOne.is_open())
        {
            cout << "Available room file is missing\n";
            return;
        }
        if (roomOne.is_open())
        {
            while (getline(roomOne, roomsOne))
            {
                cout << roomsOne << endl;
            }
        }

        roomOne.close();

        cout << "Input: ";

        cin >> roomInput;

        if (cin.fail() || roomInput >= "4" || roomInput <= "0")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            system("pause");
            system("CLS");
            continue;
        }

        if (roomInput == "1")
        {
            system("CLS");
            staffMenu();

            return;
        }
        else if (roomInput == "2")
        {
            myBookings();
            return;
        }
        else if (roomInput == "3")
        {
            myReservationsFunc();
            return;
        }
    }
}

fstream booKings;

void myBookings()
{

    while (true) {
        system("CLS");
    string bookingText;
    int bookingInput;
    system("CLS");
    cout << "                     B O O K I N G S\n";
    cout << "      <===========================================>\n";

    cout << "           [1] Back  [2] Confirm a booking\n";
    cout << "      <===========================================>\n\n";

    booKings.open("bookings.txt", ios::in);

    if (!booKings.is_open())
    {
        cout << "Available file is missing\n";
        return;
    }

    if (booKings.is_open())
    {
        while (getline(booKings, bookingText))
        {
            cout << "       [*] " << bookingText << endl;
        }
    }

    booKings.close();
    cout << "\n     <===========================================>\n";

    cout << "       Input: ";

    cin >> bookingInput;

    if (bookingInput == 1) {
        staffMenu();
        return;
    }  else if (bookingInput == 2) {
        confirmBooking();
        }

        if (cin.fail()){
            safetyInput();
            cout << "Input error\n";
            system("pause");
            system("CLS");
            continue;;
        } else if (bookingInput != 1 || bookingInput !=2) {
            safetyInput();
            cout << "Input error";
            system("pause");
            system("CLS");
            continue;
        }
    }
}

void myReservationsFunc()
{

    system("CLS");
    int reservationInput;
    while (true)
    {

        cout << "       R E S E R V A T I O N  L I S T\n";
        cout << "<===========================================>\n";
        cout << "[1] Back    [2] Confirm     [3] Delete \n\n";

        reservationListConfirmDelDisplay();

        cout << "Input: ";
        cin >> reservationInput;

        if (reservationInput == 1)
        {
            staffMenu();
            return;
        }
        else if (reservationInput == 2)
        {
            userConfirmation();
            return;
        }
        else if (reservationInput == 3)
        {
        }

        if (cin.fail())
        {
            safetyInput();
            cout << "Input error\n";
            system("pause");
            system("CLS");
            continue;
        }
    }
}

void customerMenu()
{
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

        if (cin.fail() || customerInput >= 4 || customerInput <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input\n";
            system("pause");
            system("CLS");
            continue;
        }
        else if (customerInput == 1)
        {
            safetyInput();
            system("CLS");
            main();
            continue;
        }
        else if (customerInput == 3)
        {
            system("CLS");
            reserveFileFunc();
            return;
        }
        else if (customerInput == 2)
        {
            system("CLS");
            bookARoom();
        }
    }
}

/* void reserveRooms() {

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


} */

void reserveFileFunc()
{
    system("CLS");

    while (true)
    {
        reserveRoomsDisplayFunc();

        string reserveRoomNumber;
        string reserveListOutput;
        string reserveUsername;

        cout << "Input Username: ";
        cin >> reserveUsername;

        if (reserveUsername == "1")
        {
            system("CLS");
            customerMenu();
            return;
        }
        else if (reserveUsername == "2")
        {
            system("CLS");
            bookARoom();
            return;
        }

        cout << "Input room number to reserve eg. 201 \n";
        cout << "Input: ";

        cin >> reserveRoomNumber;

        if (reserveRoomNumber == "1")
        {
            system("CLS");

            continue;
        }
        else if (reserveRoomNumber == "2")
        {
            system("CLS");
            bookARoom();
            return;
        }

        fstream reserveListFile;
        string userCheck;
        string roomCheck;

        bool roomGoods = false;

        fstream roomsLists;
        string roomListsAuth;

        roomsLists.open("roomNumbers.txt", ios::in);
        if (!roomsLists.is_open())
        {
            cerr << "Error: Rooms Lists File is Missing!";
            return;
        }
        else if (roomsLists.is_open())
        {
            while (getline(roomsLists, roomListsAuth))
            {
                if (reserveRoomNumber == roomListsAuth)
                {
                    roomGoods = true;
                    break;
                }
                else
                {
                    roomGoods = false;
                    break;
                }
            }
        }

        roomsLists.close();

        reserveListFile.open("reservedRoomsLists.txt", ios::app);

        if (!reserveListFile.is_open())
        {
            cerr << "Error: Authenticator File is Missing!";
            return;
        }

        if (reserveListFile.is_open())
        {

            if (roomGoods == true)
            {

                cout << "Successfully Reserved!\n";
                system("pause");
                reserveListFile << reserveUsername << " " << reserveRoomNumber << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else
            {
                cout << "Room not available\n";
                system("pause");
                system("CLS");
                continue;
            }
        }
        reserveListFile.close();

        reserveListFile.open("reservedRoomsLists.txt", ios::in);

        if (!reserveListFile.is_open())
        {
            cerr << "Error: Authenticator File is Missing!";
            return;
        }

        if (reserveListFile.is_open())
        {

            while (reserveListFile >> userCheck >> roomCheck)
            {
                if (reserveUsername == userCheck && reserveRoomNumber == roomCheck)
                {
                    cout << "Reservation already exisiting! \n";
                    system("pause");
                    system("CLS");
                    reserveFileFunc();
                    return;
                }
            }
        }

        reserveListFile.close();
    }
}

void reserveRoomsDisplayFunc()
{
    fstream theReservedList;
    string theRooms;
    cout << "               Room Reservation\n";
    cout << "<===========================================>\n";
    cout << "  [1] Back     [2] Book \n";

    theReservedList.open("availRooms.txt", ios::in);

    if (!theReservedList.is_open())
    {
        cout << "Available room file is missing\n";
        return;
    }
    else if (theReservedList.is_open())
    {
        while (getline(theReservedList, theRooms))
        {
            // system("CLS");
            cout << theRooms << endl;
        }
    }
    theReservedList.close();
}

void safetyInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void userConfirmation()
{
    fstream myReservations;

    string transferReservation;
    string confirmReservationUser;
    string confirmReservationRoomNumber;

    int reservationOptions;

    while (true)
    {

        system("CLS");
        cout << "           C O N F I R M   R E S E R V A T I O N\n";
        cout << "<=========================================================>\n";
        cout << "         [1] Back    [2] Delete Reservation\n";
        cout << "     <===========================================>\n";

        reservationListConfirmDelDisplay();

        cout << "Enter User: ";
        cin >> confirmReservationUser;

        if (confirmReservationUser == "1")
        {
            system("CLS");
            staffMenu();
            return;
        }
        else if (confirmReservationUser == "2")
        {
            system("CLS");
            deleteUserReservation();
            return;
        }

        cout << "Enter room number: ";
        cin >> confirmReservationRoomNumber;

        if (confirmReservationRoomNumber == "1")
        {
            system("CLS");
            userConfirmation();
            return;
        }
        else if (confirmReservationRoomNumber == "2")
        {
            system("CLS");
            deleteUserReservation();
            return;
        }

        string findMatchUser;
        string findMatchRoomNumber;
        bool userMatch = false;

        myReservations.open("reservedRoomsLists.txt", ios::in);

        if (!myReservations.is_open())
        {
            cerr << "File not found!";
            return;
        }
        else if (myReservations.is_open())
        {
            while (myReservations >> findMatchUser >> findMatchRoomNumber)
            {
                if (confirmReservationUser == findMatchUser && confirmReservationRoomNumber == findMatchRoomNumber)
                {
                    userMatch = true;
                    break;
                }
            }
        }

        myReservations.close();

        if (!userMatch)
        {
            cout << "No user matching...";
            continue;
        }
        else if (userMatch == true)
        {

            fstream bookingList;
            string addUser;
            string userRoom;
            bool succesConfirmed = false;

            bookingList.open("bookings.txt", ios::app);
            if (!bookingList.is_open())
            {
                cerr << "File not found!";
                return;
            }
            else if (bookingList.is_open())
            {

                cout << "Successfully Confirmed!\n";
                bookingList << confirmReservationUser << " " << confirmReservationRoomNumber << endl;
                system("pause");
                system("CLS");
                myReservationsFunc();
                return;
            }
        }

        if (cin.fail() || confirmReservationRoomNumber != "1" || confirmReservationRoomNumber != "2" || confirmReservationUser != "2" || confirmReservationUser != "1")
        {
            safetyInput();
            cout << "Input error\n";
            system("pause");
            system("CLS");
            continue;
        }
    }
}

void reservationListConfirmDelDisplay()
{
    fstream myReservations;
    string displayReservation;

    myReservations.open("reservedRoomsLists.txt", ios::in);

    if (!myReservations.is_open())
    {
        cerr << "File not found!";
        return;
    }
    else if (myReservations.is_open())
    {
        while (getline(myReservations, displayReservation))
        {
            cout << "[*] " << displayReservation << endl;
        }
    }

    myReservations.close();
}

void bookARoom()
{
    system("CLS");

    while (true)
    {
        string roomBooking;
        fstream bookingRoom;
        string userRoomBooking;
        string roomRoomBooking;

        cout << "             B O O K    A   R O O M\n";
        cout << "  <===========================================>\n";
        cout << "       [1] Save and Exit    [2] Reserve\n";

        bookingRoom.open("bookingDisplay.txt", ios::in);

        if (!bookingRoom.is_open())
        {
            cout << "Available room file is missing\n";
            return;
        }
        if (bookingRoom.is_open())
        {
            while (getline(bookingRoom, roomBooking))
            {
                cout << roomBooking << endl;
            }
        }

        bookingRoom.close();

        cout << "Enter Username: ";
        cin >> userRoomBooking;

        if (userRoomBooking == "1")
        {
            system("CLS");
            customerMenu();
            return;
        }
        else if (userRoomBooking == "2")
        {
            system("CLS");
            reserveFileFunc();
            return;
        }

        cout << "Enter room number to book: ";
        cin >> roomRoomBooking;

        if (roomRoomBooking == "1")
        {
            system("CLS");
            continue;
        }
        else if (userRoomBooking == "2")
        {
            system("CLS");
            reserveFileFunc();
            return;
        }

        fstream roomNumberCheck;
        string roomStringChecker;
        bool roomChecked = false;

        roomNumberCheck.open("roomNumbers.txt", ios::in);

        if (!roomNumberCheck.is_open())
        {
            cerr << "Error: Room Numbers File is Missing!";
            return;
        }
        else if (roomNumberCheck.is_open())
        {
            while (getline(roomNumberCheck, roomStringChecker))
            {
                if (roomRoomBooking == roomStringChecker)
                {
                    roomChecked = true;
                    break;
                }
                else
                {
                    roomChecked = false;
                }
            }
        }

        roomNumberCheck.close();

        fstream bookingFile;
        bookingFile.open("bookings.txt", ios::app);

        if (!bookingFile.is_open())
        {
            cerr << "Error: Booking File is Missing!";
            return;
        }
        else if (bookingFile.is_open())
        {

            if (roomChecked)
            {
                cout << "Booking Placed!\n";
                bookingFile << userRoomBooking << " " << roomRoomBooking << endl;
                system("pause");
                system("CLS");
                continue;
            }
            else
            {
                cout << "Room not available\n";
                system("pause");
                system("CLS");
                continue;
            }
        }

        bookingFile.close();
    }
}

void deleteUserReservation()
{

    system("CLS");

    while (true)
    {
        string selectUser;
        string selectroomNumber;

        cout << "          D E L E T E    R E S E R V A T I O N\n";
        cout << "<====================================================>\n";
        cout << "       [1] Cancel    [2] Confirm Reservation\n";
        cout << "    <===========================================>\n";

        fstream reservedLists;

        reservedLists.open("reservedRoomsLists.txt", ios::in);

        cout << "Select User: ";
        cin >> selectUser;

        cout << "Select Room: ";

        if (selectUser == "1")
        {
            reserveFileFunc();
            return;
        }
    }
}

void confirmBooking() {
    
    system("CLS");

    while (true) {
        string bookingUser;
        string bookingStringDisplay;
        string bookingRoomNumber;
        fstream bookingDisplay;
        system("CLS");

        cout << "                     B O O K I N G S\n";
        cout << "      <===========================================>\n";

        cout << "           [1] Back\n";
        cout << "      <===========================================>\n\n";

        bookingDisplay.open("bookings.txt", ios::in);
        if (!bookingDisplay.is_open()) {
            cerr << "Error: Booking File is Missing!";
            return;
        } else if (bookingDisplay.is_open()) {
            while (getline(bookingDisplay, bookingStringDisplay)) {
                cout << "      [*]" << bookingStringDisplay << endl;
            }
        }

        bookingDisplay.close();

        cout << " \n     <===========================================>\n";

        cout << "           Enter username: ";
        cin >> bookingUser;

        if (bookingUser == "1") {
            system("CLS");
            myBookings();
            return;
        }

        cout << "Enter room number: ";
        cin >> bookingRoomNumber;

        if (bookingRoomNumber == "1") {
            system("CLS");
            continue;
        }
        
        

        string line;
        string lineMatch;

        bool isMatched = false;

        fstream bookingFile;
        fstream tempFile;

        bookingFile.open("bookings.txt", ios::in);
        tempFile.open("temp.txt", ios::out);
        if (!bookingFile.is_open() || !tempFile.is_open()) {
            cerr << "Error: Booking File is Missing!";
            return;
        } else if (bookingFile.is_open()) {
            while (getline(bookingFile, line)) {
                if (line == bookingUser + " " + bookingRoomNumber) {
                    isMatched = true;

                    fstream transferConfirmed;

                    transferConfirmed.open("confirmedBookings.txt", ios::app);
                    if (!transferConfirmed.is_open()) {
                        cerr << "Error: Confirmed Bookings File is Missing!";
                        return;
                    } else if (transferConfirmed.is_open()) {
                        transferConfirmed << line << endl;
                    }

                    transferConfirmed.close();
                    
                    
                } else {
                    tempFile << line << endl;
                }
            }
        }

        bookingFile.close();
        tempFile.close();

        if (isMatched) {
            
            
            remove("bookings.txt");
            rename("temp.txt", "bookings.txt");
            cout << "Booking Confirmed!\n";
            system("pause");
            system("CLS");
            continue;
        } else {
            cout << "Booking not found!" << endl;
            remove("temp.txt");
            system("pause");
            system("CLS");
            continue;
        }

        

    }
}
// https://stackoverflow.com/questions/29859796/c-auto-vs-auto#:~:text=So%2C%20in%20a%20nutshell%2C%20if,you%20want%20references%2C%20use%20auto%26%20.
// https://www.youtube.com/watch?v=2vOPEuiGXVo
// https://www.youtube.com/watch?v=TUBVZvzEQAs
// https://cplusplus.com/reference/utility/make_pair/
// https://stackoverflow.com/questions/50325078/how-to-send-an-error-message-when-c-string-user-input-empty