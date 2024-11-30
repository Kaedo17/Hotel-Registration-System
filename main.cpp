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
void reserveFileFunc();
void bookARoom();
void safetyInput();
void reserveRoomsDisplayFunc();
void userConfirmation();
void reservationListConfirmDelDisplay();
void confirmBooking();
void confirmedBookingsFunc();
void deleteReservationFunc();
void bookingfDisplayFunc();
void deleteBookingFunc();
void removeSoloRooms();
void removeTwinRooms();
void removeDeluxeRooms();
void allDisplayFunc();

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
        cout << "                Login\n";
        cout << "<====================================>\n";
        cout << "[1] Forgot Password\n";
        cout << "[2] Back\n";
        cout << "<====================================>\n";
        cout << "Username: ";
        cin >> staffUserName;

        if (staffUserName == "2")
        { // added back option in case of user mis clicked an option
            staffSignIn();
            system("CLS");
            return;
        }
        else if (staffUserName == "1")
        {
            forgotPass();
            system("CLS");
            return;
        }

        cout << "Password: ";
        cin >> staffPasswd;

        if (staffPasswd == "2")
        {
            system("CLS");
            continue;
        }
        else if (staffPasswd == "1")
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
        cout << " [4]  Confirmed Bookings\n";
        cout << " [5]  Delete Reservation\n";
        cout << " [6]  Delete Bookings\n";
        cout << " [7]  Save and Exit\n";
        cout << "<===========================================>\n";
        cout << "Input: ";
        cin >> userInputStaff;

        if (cin.fail() || userInputStaff >= 8 || userInputStaff <= 0)
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
            system("CLS");
            myBookings();
            return;
        }
        else if (userInputStaff == 3)
        {
            system("CLS");
            myReservationsFunc();
            return;
        }
        else if (userInputStaff == 7)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("CLS");
            main();
            return;
        }
        else if (userInputStaff == 4)
        {
            system("CLS");
            confirmedBookingsFunc();
            return;
        }
        else if (userInputStaff == 5)
        {
            system("CLS");
            deleteReservationFunc();

            return;
        }
        else if (userInputStaff == 6)
        {
            system("CLS");
            deleteBookingFunc();
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
        cout << "[1] Bookings    [2] Reservations   [3] Save and Exit\n";
        cout << "<===========================================>\n";
        allDisplayFunc();
        cout << "<===========================================>\n";

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

        if (roomInput == "3")
        {
            system("CLS");
            staffMenu();

            return;
        }
        else if (roomInput == "1")
        {
            myBookings();
            return;
        }
        else if (roomInput == "2")
        {
            myReservationsFunc();
            return;
        }
    }
}

fstream booKings;

void myBookings()
{

    while (true)
    {
        system("CLS");
        string bookingText;
        int bookingInput;
        system("CLS");
        cout << "                     B O O K I N G S\n";
        cout << "      <===========================================>\n";

        cout << "           [1] Confirm a booking   [2] Back\n";
        cout << "      <===========================================>\n\n";

        bookingfDisplayFunc();
        cout << "\n     <===========================================>\n";

        cout << "       Input: ";

        cin >> bookingInput;

        if (bookingInput == 2)
        {
            staffMenu();
            return;
        }
        else if (bookingInput == 1)
        {
            confirmBooking();
        }

        if (cin.fail())
        {
            safetyInput();
            cout << "Input error\n";
            system("pause");
            system("CLS");
            continue;
            ;
        }
        else if (bookingInput != 1 || bookingInput != 2)
        {
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
        cout << "[1] Confirm     [2] Delete     [3] Back     \n";
        cout << "<===========================================>\n";

        reservationListConfirmDelDisplay();

        cout << "<===========================================>\n";

        cout << "Input: ";
        cin >> reservationInput;

        if (reservationInput == 3)
        {
            staffMenu();
            return;
        }
        else if (reservationInput == 1)
        {
            userConfirmation();
            return;
        }
        else if (reservationInput == 2)
        {
            deleteReservationFunc();
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

        cout << "  [1] Book a room\n";
        cout << "  [2] Reserve Rooms\n";
        cout << "  [3] Back\n";

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
        else if (customerInput == 3)
        {
            safetyInput();
            system("CLS");
            main();
            continue;
        }
        else if (customerInput == 2)
        {
            system("CLS");
            reserveFileFunc();
            return;
        }
        else if (customerInput == 1)
        {
            system("CLS");
            bookARoom();
        }
    }
}

void reserveFileFunc()
{
    system("CLS");

    while (true)
    {
        reserveRoomsDisplayFunc();

        string reserveRoomNumber;
        string reserveListOutput;
        string reserveUsername;

        cout << "<===========================================>\n";

        cout << "Input Username: ";
        cin >> reserveUsername;

        if (reserveUsername == "2")
        {
            system("CLS");
            customerMenu();
            return;
        }
        else if (reserveUsername == "1")
        {
            system("CLS");
            bookARoom();
            return;
        }

        cout << "Input room number to reserve eg. 201 \n";
        cout << "Input: ";

        cin >> reserveRoomNumber;

        if (reserveRoomNumber == "2")
        {
            system("CLS");

            continue;
        }
        else if (reserveRoomNumber == "1")
        {
            system("CLS");
            bookARoom();
            return;
        }

        string userCheck;
        string roomCheck;

        bool roomGoods = false;

        // fstream roomsLists;
        // roomsLists.open("availRooms.txt", ios::in);

        fstream soloRoomsLists;
        fstream twinRoomsLists;
        fstream deluxeRoomsLists;
        string soloRoomListsAuth;
        string twinRoomListsAuth;
        string deluxeRoomListsAuth;
        soloRoomsLists.open("soloRooms.txt", ios::in);
        twinRoomsLists.open("twinBed.txt", ios::in);
        deluxeRoomsLists.open("deluxeBed.txt", ios::in);

        if (!soloRoomsLists.is_open() || !twinRoomsLists.is_open() || !deluxeRoomsLists.is_open())
        {
            cerr << "Error: Rooms Lists File is Missing!";
            return;
        }
        else if (soloRoomsLists.is_open() || twinRoomsLists.is_open() || deluxeRoomsLists.is_open())
        {
            while (getline(soloRoomsLists, soloRoomListsAuth))
            {
                if (reserveRoomNumber == soloRoomListsAuth)
                {
                    roomGoods = true;
                    break;
                }
            }

            while (getline(twinRoomsLists, twinRoomListsAuth))
            {
                if (reserveRoomNumber == twinRoomListsAuth)
                {
                    roomGoods = true;
                    break;
                }
            }

            while (getline(deluxeRoomsLists, deluxeRoomListsAuth))
            {
                if (reserveRoomNumber == deluxeRoomListsAuth)
                {
                    roomGoods = true;
                    break;
                }
            }
        }

        soloRoomsLists.close();
        twinRoomsLists.close();
        deluxeRoomsLists.close();

        fstream soloCheckingFile;
        fstream twinCheckingFile;
        fstream deluxeCheckingFile;
        soloCheckingFile.open("soloReserve.txt", ios::in);
        twinCheckingFile.open("twinReserve.txt", ios::in);
        deluxeCheckingFile.open("deluxeReserve.txt", ios::in);

        string soloUser;
        string soloRoom;
        string twinUser;
        string twinRoom;
        string deluxeUser;
        string deluxeRoom;

        while (soloCheckingFile >> soloUser >> soloRoom)
        {
            if (reserveUsername == soloUser && reserveRoomNumber == soloRoom)
            {
                cout << "Reservation already exisiting! \n";
                system("pause");
                system("CLS");
                reserveFileFunc();
                return;
            }
        }

        while (twinCheckingFile >> twinUser >> twinRoom)
        {
            if (reserveUsername == twinUser && reserveRoomNumber == twinRoom)
            {
                cout << "Reservation already exisiting! \n";
                system("pause");
                system("CLS");
                reserveFileFunc();
                return;
            }
        }

        while (deluxeCheckingFile >> deluxeUser >> deluxeRoom)
        {
            if (reserveUsername == deluxeUser && reserveRoomNumber == deluxeRoom)
            {
                cout << "Reservation already exisiting! \n";
                system("pause");
                system("CLS");
                reserveFileFunc();
                return;
            }
        }

        soloCheckingFile.close();
        twinCheckingFile.close();
        deluxeCheckingFile.close();

        if (!roomGoods)
        {
            cout << "Room not available\n";
            system("pause");
            system("CLS");
            continue;
        }

        fstream soloReserveListFile;
        fstream twinReserveListFile;
        fstream deluxeReserveListFile;

        soloReserveListFile.open("soloReserve.txt", ios::app);
        twinReserveListFile.open("twinReserve.txt", ios::app);
        deluxeReserveListFile.open("deluxeReserve.txt", ios::app);

        if (!soloReserveListFile.is_open() || !twinReserveListFile.is_open() || !deluxeReserveListFile.is_open())
        {
            cerr << "Error: Authenticator File is Missing!";
            return;
        }

        if (reserveRoomNumber == "101" || reserveRoomNumber == "102" || reserveRoomNumber == "103" || reserveRoomNumber == "104" || reserveRoomNumber == "105")
        {

            if (roomGoods)
            {

                cout << "Successfully Reserved!\n";
                soloReserveListFile << reserveUsername << " " << reserveRoomNumber << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("pause");
                system("CLS");
                continue;
            }
        }

        if (reserveRoomNumber == "201" || reserveRoomNumber == "202" || reserveRoomNumber == "203" || reserveRoomNumber == "204" || reserveRoomNumber == "205")
        {

            if (roomGoods)
            {

                cout << "Successfully Reserved!\n";
                twinReserveListFile << reserveUsername << " " << reserveRoomNumber << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("pause");
                system("CLS");
                continue;
            }
        }

        if (reserveRoomNumber == "301" || reserveRoomNumber == "302" || reserveRoomNumber == "303" || reserveRoomNumber == "304" || reserveRoomNumber == "305")
        {

            if (roomGoods)
            {

                cout << "Successfully Reserved!\n";
                deluxeReserveListFile << reserveUsername << " " << reserveRoomNumber << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("pause");
                system("CLS");
                continue;
            }
        }
        soloReserveListFile.close();
        twinReserveListFile.close();
        deluxeReserveListFile.close();
    }
}

void reserveRoomsDisplayFunc()
{
    cout << "               Room Reservation\n";
    cout << "<===========================================>\n";
    cout << "  [1] Book     [2] Back \n";
    cout << "<===========================================>\n";

    allDisplayFunc();
}

void safetyInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void userConfirmation()
{

    string transferReservation;
    string confirmReservationUser;
    string confirmReservationRoomNumber;

    int reservationOptions;

    while (true)
    {

        system("CLS");
        cout << "           C O N F I R M   R E S E R V A T I O N\n";
        cout << "<=========================================================>\n";
        cout << "         [1] Delete Reservation    [2] Back\n";
        cout << "     <===========================================>\n\n";

        reservationListConfirmDelDisplay();

        cout << "<====================================================>\n";

        cout << "Enter User: ";
        cin >> confirmReservationUser;

        if (confirmReservationUser == "2")
        {
            system("CLS");
            staffMenu();
            return;
        }
        else if (confirmReservationUser == "1")
        {
            system("CLS");
            deleteReservationFunc();
            return;
        }

        cout << "Enter room number: ";
        cin >> confirmReservationRoomNumber;

        if (confirmReservationRoomNumber == "2")
        {
            system("CLS");
            userConfirmation();
            return;
        }
        else if (confirmReservationRoomNumber == "1")
        {
            system("CLS");
            deleteReservationFunc();
            return;
        }

        fstream soloCheckingFile;
        fstream twinCheckingFile;
        fstream deluxeCheckingFile;
        soloCheckingFile.open("soloBookings.txt", ios::in);
        twinCheckingFile.open("twinBookings.txt", ios::in);
        deluxeCheckingFile.open("deluxeBookings.txt", ios::in);

        string soloUser;
        string soloRoom;
        string twinUser;
        string twinRoom;
        string deluxeUser;
        string deluxeRoom;

        while (soloCheckingFile >> soloUser >> soloRoom)
        {
            if (confirmReservationUser == soloUser && confirmReservationRoomNumber == soloRoom)
            {
                cout << "Booking already exisiting! \n";
                system("pause");
                system("CLS");
                userConfirmation();
                return;
            }
        }

        while (twinCheckingFile >> twinUser >> twinRoom)
        {
            if (confirmReservationUser == twinUser && confirmReservationRoomNumber == twinRoom)
            {
                cout << "Booking already exisiting! \n";
                system("pause");
                system("CLS");
                userConfirmation();
                return;
            }
        }

        while (deluxeCheckingFile >> deluxeUser >> deluxeRoom)
        {
            if (confirmReservationUser == deluxeUser && confirmReservationRoomNumber == deluxeRoom)
            {
                cout << "Booking already exisiting! \n";
                system("pause");
                system("CLS");
                userConfirmation();
                return;
            }
        }

        soloCheckingFile.close();
        twinCheckingFile.close();
        deluxeCheckingFile.close();

        string findSoloMatchUser;
        string findSoloMatchRoomNumber;
        string findTwinMatchUser;
        string findTwinMatchRoomNumber;
        string findDeluxeMatchUser;
        string findDeluxeMatchRoomNumber;
        string confirmationLine;
        fstream tempSolo;
        fstream tempTwin;
        fstream tempDeluxe;
        fstream mySoloReservations;
        fstream myTwinReservations;
        fstream myDeluxeReservations;
        bool userMatch = false;
        bool isSolo = false;
        bool isTwin = false;
        bool isDeluxe = false;

        tempSolo.open("tempSolo.txt", ios::out);
        tempTwin.open("tempTwin.txt", ios::out);
        tempDeluxe.open("tempDeluxe.txt", ios::out);
        mySoloReservations.open("soloReserve.txt", ios::in);
        myTwinReservations.open("twinReserve.txt", ios::in);
        myDeluxeReservations.open("deluxeReserve.txt", ios::in);

        if (!mySoloReservations.is_open() || !tempSolo.is_open() || !tempDeluxe.is_open() || !tempTwin.is_open() || !myTwinReservations.is_open() || !myDeluxeReservations.is_open())
        {
            cerr << "File not found!";
            return;
        }
        else if (mySoloReservations.is_open() || tempSolo.is_open() || tempDeluxe.is_open() || tempTwin.is_open() || myTwinReservations.is_open() || myDeluxeReservations.is_open())
        {
            while (getline(mySoloReservations, findSoloMatchUser))
            {
                if (findSoloMatchUser == confirmReservationUser + " " + confirmReservationRoomNumber)
                {
                    userMatch = true;
                    isSolo = true;

                    fstream successBooking;

                    successBooking.open("soloBookings.txt", ios::app);
                    if (!successBooking.is_open())
                    {
                        cerr << "File not found!";
                        return;
                    }
                    else if (successBooking.is_open())
                    {
                        successBooking << findSoloMatchUser << endl;
                    }

                    successBooking.close();
                }
                else
                {
                    tempSolo << findSoloMatchUser << endl;
                }
            }

            while (getline(myTwinReservations, findTwinMatchUser))
            {
                if (findTwinMatchUser == confirmReservationUser + " " + confirmReservationRoomNumber)
                {
                    userMatch = true;
                    isTwin = true;

                    fstream successBooking;

                    successBooking.open("twinBookings.txt", ios::app);
                    if (!successBooking.is_open())
                    {
                        cerr << "File not found!";
                        return;
                    }
                    else if (successBooking.is_open())
                    {
                        successBooking << findTwinMatchUser << endl;
                    }

                    successBooking.close();
                }
                else
                {
                    tempTwin << findTwinMatchUser << endl;
                }
            }

            while (getline(myDeluxeReservations, findDeluxeMatchUser))
            {
                if (findDeluxeMatchUser == confirmReservationUser + " " + confirmReservationRoomNumber)
                {
                    userMatch = true;
                    isDeluxe = true;

                    fstream successBooking;

                    successBooking.open("deluxeBookings.txt", ios::app);
                    if (!successBooking.is_open())
                    {
                        cerr << "File not found!";
                        return;
                    }
                    else if (successBooking.is_open())
                    {
                        successBooking << findDeluxeMatchUser << endl;
                    }

                    successBooking.close();
                }
                else
                {
                    tempDeluxe << findDeluxeMatchUser << endl;
                }
            }
        }

        tempSolo.close();
        tempTwin.close();
        tempDeluxe.close();
        mySoloReservations.close();
        myTwinReservations.close();
        myDeluxeReservations.close();

        if (userMatch)
        {
            if (isSolo)
            {
                remove("soloReserve.txt");
                rename("tempSolo.txt", "soloReserve.txt");
                remove("tempSolo.txt");
                cout << "Confirmed Successfully\n";
                system("pause");
                system("CLS");
                continue;
            }
            else if (isTwin)
            {
                remove("twinReserve.txt");
                rename("tempTwin.txt", "twinReserve.txt");
                remove("tempTwin.txt");
                cout << "Confirmed Successfully\n";
                system("pause");
                system("CLS");
                continue;
            }
            else if (isDeluxe)
            {
                remove("deluxeReserve.txt");
                rename("tempDeluxe.txt", "deluxeReserve.txt");
                remove("tempDeluxe.txt");
                cout << "Confirmed Successfully\n";
                system("pause");
                system("CLS");
                continue;
            }
        }
        else
        {
            cout << "No user matching...\n";
            remove("tempSolo.txt");
            remove("tempTwin.txt");
            remove("tempDeluxe.txt");
            system("pause");
            system("CLS");
            continue;
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
    fstream soloList;
    fstream twinList;
    fstream deluxeList;
    string soloRooms;
    string deluxeRooms;
    string twinRooms;

    soloList.open("soloReserve.txt", ios::in);
    twinList.open("twinReserve.txt", ios::in);
    deluxeList.open("deluxeReserve.txt", ios::in);

    if (!soloList.is_open() || !twinList.is_open() || !deluxeList.is_open())
    {
        cout << "Available room file is missing\n";
        return;
    }
    else if (soloList.is_open() || twinList.is_open() || deluxeList.is_open())
    {
        cout << "\n Solo Rooms \n";
        while (getline(soloList, soloRooms))
        {
            // system("CLS");
            cout << "[*] " << soloRooms << endl;
        }
        cout << "\n Twin Bed Rooms \n";

        while (getline(twinList, twinRooms))
        {
            // system("CLS");
            cout << "[*] " << twinRooms << endl;
        }

        cout << "\n Deluxe Rooms \n";

        while (getline(deluxeList, deluxeRooms))
        {
            // system("CLS");
            cout << "[*] " << deluxeRooms << endl;
        }
    }
    soloList.close();
    twinList.close();
    deluxeList.close();
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
        cout << "       [1] Reserve     [2] Save and Exit \n";
        cout << "  <===========================================>\n";

        allDisplayFunc();
        cout << "<=============================================>\n";

        cout << "Enter Username: ";
        cin >> userRoomBooking;

        if (userRoomBooking == "2")
        {
            system("CLS");
            customerMenu();
            return;
        }
        else if (userRoomBooking == "1")
        {
            system("CLS");
            reserveFileFunc();
            return;
        }

        cout << "Enter room number to book: ";
        cin >> roomRoomBooking;

        if (roomRoomBooking == "2")
        {
            system("CLS");
            continue;
        }
        else if (userRoomBooking == "1")
        {
            system("CLS");
            reserveFileFunc();
            return;
        }

        fstream solocheckAvail;
        fstream twincheckAvail;
        fstream deluxecheckAvail;
        string soloavailName;
        string soloavailRoom;
        string twinavailName;
        string twinavailRoom;
        string deluxeavailName;
        string deluxeavailRoom;

        solocheckAvail.open("soloConfirmedBooking.txt", ios::in);
        twincheckAvail.open("twinConfirmedBooking.txt", ios::in);
        deluxecheckAvail.open("deluxeConfirmedBooking.txt", ios::in);

        if (!solocheckAvail.is_open() || !twincheckAvail.is_open() || !deluxecheckAvail.is_open())
        {
            cerr << "File not found\n";
            return;
        }
        else if (solocheckAvail.is_open() || twincheckAvail.is_open() || deluxecheckAvail.is_open())
        {
            while (solocheckAvail >> soloavailName >> soloavailRoom)
            {
                if (roomRoomBooking == soloavailRoom)
                {
                    cout << "Room is not available";
                    system("pause");
                    system("CLS");
                    bookARoom();
                }
            }

            while (twincheckAvail >> twinavailName >> twinavailRoom)
            {
                if (roomRoomBooking == twinavailRoom)
                {
                    cout << "Room is not available";
                    system("pause");
                    system("CLS");
                    bookARoom();
                }
            }

            while (deluxecheckAvail >> deluxeavailName >> deluxeavailRoom)
            {
                if (roomRoomBooking == deluxeavailRoom)
                {
                    cout << "Room is not available";
                    system("pause");
                    system("CLS");
                    bookARoom();
                }
            }
        }

        solocheckAvail.close();
        bool roomChecked = false;

        fstream soloRoomsLists;
        fstream twinRoomsLists;
        fstream deluxeRoomsLists;
        string soloRoomListsAuth;
        string twinRoomListsAuth;
        string deluxeRoomListsAuth;
        soloRoomsLists.open("soloRooms.txt", ios::in);
        twinRoomsLists.open("twinBed.txt", ios::in);
        deluxeRoomsLists.open("deluxeBed.txt", ios::in);

        if (!soloRoomsLists.is_open() || !twinRoomsLists.is_open() || !deluxeRoomsLists.is_open())
        {
            cerr << "Error: Rooms Lists File is Missing!";
            return;
        }
        else if (soloRoomsLists.is_open() || twinRoomsLists.is_open() || deluxeRoomsLists.is_open())
        {
            while (getline(soloRoomsLists, soloRoomListsAuth))
            {
                if (roomRoomBooking == soloRoomListsAuth)
                {
                    roomChecked = true;
                    break;
                }
            }

            while (getline(twinRoomsLists, twinRoomListsAuth))
            {
                if (roomRoomBooking == twinRoomListsAuth)
                {
                    roomChecked = true;
                    break;
                }
            }

            while (getline(deluxeRoomsLists, deluxeRoomListsAuth))
            {
                if (roomRoomBooking == deluxeRoomListsAuth)
                {
                    roomChecked = true;
                    break;
                }
            }
        }

        soloRoomsLists.close();
        twinRoomsLists.close();
        deluxeRoomsLists.close();

        fstream soloCheckingFile;
        fstream twinCheckingFile;
        fstream deluxeCheckingFile;
        soloCheckingFile.open("soloBookings.txt", ios::in);
        twinCheckingFile.open("twinBookings.txt", ios::in);
        deluxeCheckingFile.open("deluxeBookings.txt", ios::in);

        string soloUser;
        string soloRoom;
        string twinUser;
        string twinRoom;
        string deluxeUser;
        string deluxeRoom;

        while (soloCheckingFile >> soloUser >> soloRoom)
        {
            if (userRoomBooking == soloUser && roomRoomBooking == soloRoom)
            {
                cout << "Booking already exisiting! \n";
                system("pause");
                system("CLS");
                bookARoom();
                return;
            }
        }

        while (twinCheckingFile >> twinUser >> twinRoom)
        {
            if (userRoomBooking == twinUser && roomRoomBooking == twinRoom)
            {
                cout << "Booking already exisiting! \n";
                system("pause");
                system("CLS");
                bookARoom();
                return;
            }
        }

        while (deluxeCheckingFile >> deluxeUser >> deluxeRoom)
        {
            if (userRoomBooking == deluxeUser && roomRoomBooking == deluxeRoom)
            {
                cout << "Booking already exisiting! \n";
                system("pause");
                system("CLS");
                bookARoom();
                return;
            }
        }

        soloCheckingFile.close();
        twinCheckingFile.close();
        deluxeCheckingFile.close();

        if (!roomChecked)
        {
            cout << "Room not available\n";
            system("pause");
            system("CLS");
            continue;
        }

        fstream solobookingFile;
        fstream twinBookingFile;
        fstream deluxeBookingFile;
        solobookingFile.open("soloBookings.txt", ios::app);
        twinBookingFile.open("twinBookings.txt", ios::app);
        deluxeBookingFile.open("deluxeBookings.txt", ios::app);

        if (!solobookingFile.is_open() || !twinBookingFile.is_open() || !deluxeBookingFile.is_open())
        {
            cerr << "Error: Booking File is Missing!";
            return;
        }

        if (roomRoomBooking == "101" || roomRoomBooking == "102" || roomRoomBooking == "103" || roomRoomBooking == "104" || roomRoomBooking == "105")
        {
            if (roomChecked)
            {
                cout << "Booking Placed!\n";
                solobookingFile << userRoomBooking << " " << roomRoomBooking << endl;
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

        if (roomRoomBooking == "201" || roomRoomBooking == "202" || roomRoomBooking == "203" || roomRoomBooking == "204" || roomRoomBooking == "205")
        {
            if (roomChecked)
            {
                cout << "Booking Placed!\n";
                twinBookingFile << userRoomBooking << " " << roomRoomBooking << endl;
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

        if (roomRoomBooking == "301" || roomRoomBooking == "302" || roomRoomBooking == "303" || roomRoomBooking == "304" || roomRoomBooking == "305")
        {
            if (roomChecked)
            {
                cout << "Booking Placed!\n";
                deluxeBookingFile << userRoomBooking << " " << roomRoomBooking << endl;
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

        solobookingFile.close();
        twinBookingFile.close();
        deluxeBookingFile.close();
    }
}

void confirmBooking()
{

    system("CLS");

    while (true)
    {
        string bookingUser;

        string bookingRoomNumber;

        system("CLS");

        cout << "            C O N F I R M     B O O K I N G S\n";
        cout << "      <===========================================>\n";

        cout << "           [1] Delete Bookings     [2] Back\n";
        cout << "      <===========================================>\n\n";

        bookingfDisplayFunc();

        cout << " \n     <===========================================>\n";

        cout << "           Enter username: ";
        cin >> bookingUser;

        if (bookingUser == "2")
        {
            system("CLS");
            staffMenu();
            return;
        }
        else if (bookingUser == "1")
        {
            system("CLS");
            deleteBookingFunc();
            return;
        }

        cout << "Enter room number: ";
        cin >> bookingRoomNumber;

        if (bookingRoomNumber == "2")
        {
            system("CLS");
            continue;
        }
        else if (bookingRoomNumber == "1")
        {
            system("CLS");
            deleteBookingFunc();
            return;
        }

        string findSoloMatchUser;
        string findSoloMatchRoomNumber;
        string findTwinMatchUser;
        string findTwinMatchRoomNumber;
        string findDeluxeMatchUser;
        string findDeluxeMatchRoomNumber;
        string confirmationLine;
        fstream tempSolo;
        fstream tempTwin;
        fstream tempDeluxe;
        fstream mySoloReservations;
        fstream myTwinReservations;
        fstream myDeluxeReservations;
        bool userMatch = false;
        bool isSolo = false;
        bool isTwin = false;
        bool isDeluxe = false;

        tempSolo.open("tempSolo.txt", ios::out);
        tempTwin.open("tempTwin.txt", ios::out);
        tempDeluxe.open("tempDeluxe.txt", ios::out);
        mySoloReservations.open("soloBookings.txt", ios::in);
        myTwinReservations.open("twinBookings.txt", ios::in);
        myDeluxeReservations.open("deluxeBookings.txt", ios::in);

        if (!mySoloReservations.is_open() || !tempSolo.is_open() || !tempDeluxe.is_open() || !tempTwin.is_open() || !myTwinReservations.is_open() || !myDeluxeReservations.is_open())
        {
            cerr << "File not found!";
            return;
        }
        else if (mySoloReservations.is_open() || tempSolo.is_open() || tempDeluxe.is_open() || tempTwin.is_open() || myTwinReservations.is_open() || myDeluxeReservations.is_open())
        {
            while (getline(mySoloReservations, findSoloMatchUser))
            {
                if (findSoloMatchUser == bookingUser + " " + bookingRoomNumber)
                {
                    userMatch = true;
                    isSolo = true;

                    fstream successBooking;

                    successBooking.open("soloConfirmedBooking.txt", ios::app);
                    if (!successBooking.is_open())
                    {
                        cerr << "File not found!";
                        return;
                    }
                    else if (successBooking.is_open())
                    {
                        successBooking << findSoloMatchUser << endl;
                    }

                    successBooking.close();
                }
                else
                {
                    tempSolo << findSoloMatchUser << endl;
                }
            }

            while (getline(myTwinReservations, findTwinMatchUser))
            {
                if (findTwinMatchUser == bookingUser + " " + bookingRoomNumber)
                {
                    userMatch = true;
                    isTwin = true;

                    fstream successBooking;

                    successBooking.open("twinConfirmedBooking.txt", ios::app);
                    if (!successBooking.is_open())
                    {
                        cerr << "File not found!";
                        return;
                    }
                    else if (successBooking.is_open())
                    {
                        successBooking << findTwinMatchUser << endl;
                    }

                    successBooking.close();
                }
                else
                {
                    tempTwin << findTwinMatchUser << endl;
                }
            }

            while (getline(myDeluxeReservations, findDeluxeMatchUser))
            {
                if (findDeluxeMatchUser == bookingUser + " " + bookingRoomNumber)
                {
                    userMatch = true;
                    isDeluxe = true;

                    fstream successBooking;

                    successBooking.open("deluxeConfirmedBooking.txt", ios::app);
                    if (!successBooking.is_open())
                    {
                        cerr << "File not found!";
                        return;
                    }
                    else if (successBooking.is_open())
                    {
                        successBooking << findDeluxeMatchUser << endl;
                    }

                    successBooking.close();
                }
                else
                {
                    tempDeluxe << findDeluxeMatchUser << endl;
                }
            }
        }

        tempSolo.close();
        tempTwin.close();
        tempDeluxe.close();
        mySoloReservations.close();
        myTwinReservations.close();
        myDeluxeReservations.close();

        if (userMatch)
        {
            if (isSolo)
            {
                removeSoloRooms();
                remove("soloBookings.txt");
                rename("tempSolo.txt", "soloBookings.txt");

                cout << "Confirmed Successfully\n";
                system("pause");
                system("CLS");
                continue;
            }
            else if (isTwin)
            {
                removeTwinRooms();
                remove("twinBookings.txt");
                rename("tempTwin.txt", "twinBookings.txt");
                cout << "Confirmed Successfully\n";
                system("pause");
                system("CLS");
                continue;
            }
            else if (isDeluxe)
            {
                removeDeluxeRooms();
                remove("deluxeBookings.txt");
                rename("tempDeluxe.txt", "deluxeBookings.txt");
                cout << "Confirmed Successfully\n";
                system("pause");
                system("CLS");
                continue;
            }
        }
        else
        {
            cout << "No user matching...\n";
            remove("tempSolo.txt");
            remove("tempTwin.txt");
            remove("tempDeluxe.txt");
            system("pause");
            system("CLS");
            continue;
        }

        if (cin.fail() || bookingRoomNumber != "1" || bookingRoomNumber != "2" || bookingUser != "2" || bookingUser != "1")
        {
            safetyInput();
            cout << "Input error\n";
            system("pause");
            system("CLS");
            continue;
        }
    }
}

void confirmedBookingsFunc()
{
    system("CLS");

    while (true)
    {
        string options;

        cout << "           C O N F I R M E D   B O O K I N G S\n";
        cout << "      <===========================================>\n";
        cout << "       [1] Back\n";
        cout << "      <===========================================>\n\n";

        fstream soloList;
        fstream twinList;
        fstream deluxeList;
        string soloRooms;
        string deluxeRooms;
        string twinRooms;

        soloList.open("soloConfirmedBooking.txt", ios::in);
        twinList.open("twinConfirmedBooking.txt", ios::in);
        deluxeList.open("deluxeConfirmedBooking.txt", ios::in);

        if (!soloList.is_open() || !twinList.is_open() || !deluxeList.is_open())
        {
            cout << "Available room file is missing\n";
            return;
        }
        else if (soloList.is_open() || twinList.is_open() || deluxeList.is_open())
        {
            cout << "\n Solo Rooms \n";
            while (getline(soloList, soloRooms))
            {
                // system("CLS");
                cout << "[*] " << soloRooms << endl;
            }
            cout << "\n Twin Bed Rooms \n";

            while (getline(twinList, twinRooms))
            {
                // system("CLS");
                cout << "[*] " << twinRooms << endl;
            }

            cout << "\n Deluxe Rooms \n";

            while (getline(deluxeList, deluxeRooms))
            {
                // system("CLS");
                cout << "[*] " << deluxeRooms << endl;
            }
        }
        soloList.close();
        twinList.close();
        deluxeList.close();

        cout << "      <===========================================>\n";

        cout << "       Input: ";
        cin >> options;

        if (cin.fail())
        {
            safetyInput();
            cout << "Input error\n";
            system("pause");
            system("CLS");
            continue;
        }
        else if (options == "1")
        {
            system("CLS");
            staffMenu();
            return;
        }
    }
}

void deleteReservationFunc()
{
    system("CLS");

    while (true)
    {
        string deleteUser;
        string deleteRoom;

        cout << "          D E L E T E    R E S E R V A T I O N\n";
        cout << "      <===========================================>\n";
        cout << "       [1] Confirm User    [2] Back \n";
        cout << "      <===========================================>\n\n";

        reservationListConfirmDelDisplay();

        cout << "      <===========================================>\n";

        cout << "Enter username: ";
        cin >> deleteUser;

        if (deleteUser == "2")
        {
            safetyInput();
            system("CLS");
            staffMenu();
            return;
        }
        else if (deleteUser == "1")
        {
            system("CLS");
            userConfirmation();
            return;
        }

        cout << "Enter room number: ";
        cin >> deleteRoom;

        if (deleteRoom == "2")
        {
            system("CLS");
            continue;
        }
        else if (deleteRoom == "1")
        {
            system("CLS");
            userConfirmation();
            return;
        }

        fstream solodeleteReserve;
        fstream twindeleteReserve;
        fstream deluxedeleteReserve;
        fstream deleteTemp;
        string solotextDelete;
        string twintextDelete;
        string deluxetextDelete;
        bool isDeleted = false;
        bool isSolo = false;
        bool isTwin = false;
        bool isDeluxe = false;

        solodeleteReserve.open("soloReserve.txt", ios::in);
        twindeleteReserve.open("twinReserve.txt", ios::in);
        deluxedeleteReserve.open("deluxeReserve.txt", ios::in);
        deleteTemp.open("deleteResTemp.txt", ios::out);

        if (!solodeleteReserve.is_open() || !deleteTemp.is_open() || !twindeleteReserve.is_open() || !deluxedeleteReserve.is_open())
        {
            cerr << "Error: Delete File is Missing!";
            return;
        }
        else if (solodeleteReserve.is_open() || deleteTemp.is_open() || twindeleteReserve.is_open() || deluxedeleteReserve.is_open())
        {
            if (deleteRoom == "101" || deleteRoom == "102" || deleteRoom == "103" || deleteRoom == "104" || deleteRoom == "105")
            {
                while (getline(solodeleteReserve, solotextDelete))
                {
                    if (solotextDelete != deleteUser + " " + deleteRoom)
                    {
                        deleteTemp << solotextDelete << endl;
                    }
                    else
                    {
                        isDeleted = true;
                        isSolo = true;
                    }
                }
            }

            if (deleteRoom == "201" || deleteRoom == "202" || deleteRoom == "203" || deleteRoom == "204" || deleteRoom == "205")
            {
                while (getline(twindeleteReserve, twintextDelete))
                {
                    if (twintextDelete != deleteUser + " " + deleteRoom)
                    {
                        deleteTemp << twintextDelete << endl;
                    }
                    else
                    {
                        isDeleted = true;
                        isTwin = true;
                    }
                }
            }

            if (deleteRoom == "301" || deleteRoom == "302" || deleteRoom == "303" || deleteRoom == "304" || deleteRoom == "305")
            {
                while (getline(deluxedeleteReserve, deluxetextDelete))
                {
                    if (deluxetextDelete != deleteUser + " " + deleteRoom)
                    {
                        deleteTemp << deluxetextDelete << endl;
                    }
                    else
                    {
                        isDeleted = true;
                        isDeluxe = true;
                    }
                }
            }
        }

        solodeleteReserve.close();
        twindeleteReserve.close();
        deluxedeleteReserve.close();
        deleteTemp.close();

        if (isDeleted && isSolo)
        {
            remove("soloReserve.txt");
            rename("deleteResTemp.txt", "soloReserve.txt");
            cout << "Reservation Deleted!\n";
            system("pause");
            system("CLS");
            continue;
        }
        else if (isDeleted && isTwin)
        {
            remove("twinReserve.txt");
            rename("deleteResTemp.txt", "twinReserve.txt");
            cout << "Reservation Deleted!\n";
            system("pause");
            system("CLS");
            continue;
        }
        else if (isDeleted && isDeluxe)
        {
            remove("deluxeReserve.txt");
            rename("deleteResTemp.txt", "deluxeReserve.txt");
            cout << "Reservation Deleted!\n";
            system("pause");
            system("CLS");
            continue;
        }
        else
        {
            cout << "Reservation not found!\n";
            remove("deleteResTemp.txt");
            system("pause");
            system("CLS");
            continue;
        }
    }
}

void deleteBookingFunc()
{
    system("CLS");

    while (true)
    {
        string userDelBooking;
        string userDelRoom;
        cout << "          D E L E T E    B O O K I N G\n";
        cout << "      <===========================================>\n";
        cout << "       [1] Confirm User    [2] Back\n";
        cout << "      <===========================================>\n\n";

        bookingfDisplayFunc();

        cout << "      <===========================================>\n";

        cout << "Enter username: ";
        cin >> userDelBooking;

        if (userDelBooking == "2")
        {
            safetyInput();
            system("CLS");
            staffMenu();
            return;
        }
        else if (userDelBooking == "1")
        {
            system("CLS");
            confirmBooking();
            return;
        }

        cout << "Enter room number: ";
        cin >> userDelRoom;

        if (userDelRoom == "2")
        {
            system("CLS");
            continue;
        }
        else if (userDelRoom == "1")
        {
            system("CLS");
            userConfirmation();
            return;
        }

        fstream solodeleteBooking;
        fstream twindeleteBooking;
        fstream deluxedeleteBooking;
        fstream deleteTemp;
        string solotextDelete;
        string twintextDelete;
        string deluxetextDelete;
        bool isDeleted = false;
        bool isSolo = false;
        bool isTwin = false;
        bool isDeluxe = false;

        solodeleteBooking.open("soloBookings.txt", ios::in);
        twindeleteBooking.open("twinBookings.txt", ios::in);
        deluxedeleteBooking.open("deluxeBookings.txt", ios::in);
        deleteTemp.open("deleteResTemp.txt", ios::out);

        if (!solodeleteBooking.is_open() || !deleteTemp.is_open() || !twindeleteBooking.is_open() || !deluxedeleteBooking.is_open())
        {
            cerr << "Error: Delete File is Missing!";
            return;
        }
        else if (solodeleteBooking.is_open() || deleteTemp.is_open() || twindeleteBooking.is_open() || deluxedeleteBooking.is_open())
        {
            if (userDelRoom == "101" || userDelRoom == "102" || userDelRoom == "103" || userDelRoom == "104" || userDelRoom == "105")
            {
                while (getline(solodeleteBooking, solotextDelete))
                {
                    if (solotextDelete != userDelBooking + " " + userDelRoom)
                    {
                        deleteTemp << solotextDelete << endl;
                    }
                    else
                    {
                        isDeleted = true;
                        isSolo = true;
                    }
                }
            }

            if (userDelRoom == "201" || userDelRoom == "202" || userDelRoom == "203" || userDelRoom == "204" || userDelRoom == "205")
            {
                while (getline(twindeleteBooking, twintextDelete))
                {
                    if (twintextDelete != userDelBooking + " " + userDelRoom)
                    {
                        deleteTemp << twintextDelete << endl;
                    }
                    else
                    {
                        isDeleted = true;
                        isTwin = true;
                    }
                }
            }

            if (userDelRoom == "301" || userDelRoom == "302" || userDelRoom == "303" || userDelRoom == "304" || userDelRoom == "305")
            {
                while (getline(deluxedeleteBooking, deluxetextDelete))
                {
                    if (deluxetextDelete != userDelBooking + " " + userDelRoom)
                    {
                        deleteTemp << deluxetextDelete << endl;
                    }
                    else
                    {
                        isDeleted = true;
                        isDeluxe = true;
                    }
                }
            }
        }

        solodeleteBooking.close();
        twindeleteBooking.close();
        deluxedeleteBooking.close();
        deleteTemp.close();

        if (isDeleted && isSolo)
        {
            remove("soloBookings.txt");
            rename("deleteResTemp.txt", "soloBookings.txt");
            cout << "Reservation Deleted!\n";
            system("pause");
            system("CLS");
            continue;
        }
        else if (isDeleted && isTwin)
        {
            remove("twinBookings.txt");
            rename("deleteResTemp.txt", "twinBookings.txt");
            cout << "Reservation Deleted!\n";
            system("pause");
            system("CLS");
            continue;
        }
        else if (isDeleted && isDeluxe)
        {
            remove("deluxeBookings.txt");
            rename("deleteResTemp.txt", "deluxeBookings.txt");
            cout << "Reservation Deleted!\n";
            system("pause");
            system("CLS");
            continue;
        }
        else
        {
            cout << "Reservation not found!\n";
            remove("deleteResTemp.txt");
            system("pause");
            system("CLS");
            continue;
        }
    }
}
void bookingfDisplayFunc()
{

    fstream soloList;
    fstream twinList;
    fstream deluxeList;
    string soloRooms;
    string deluxeRooms;
    string twinRooms;

    soloList.open("soloBookings.txt", ios::in);
    twinList.open("twinBookings.txt", ios::in);
    deluxeList.open("deluxeBookings.txt", ios::in);

    if (!soloList.is_open() || !twinList.is_open() || !deluxeList.is_open())
    {
        cout << "Available room file is missing\n";
        return;
    }
    else if (soloList.is_open() || twinList.is_open() || deluxeList.is_open())
    {
        cout << "\n Solo Rooms \n";
        while (getline(soloList, soloRooms))
        {
            // system("CLS");
            cout << "[*] " << soloRooms << endl;
        }
        cout << "\n Twin Bed Rooms \n";

        while (getline(twinList, twinRooms))
        {
            // system("CLS");
            cout << "[*] " << twinRooms << endl;
        }

        cout << "\n Deluxe Rooms \n";

        while (getline(deluxeList, deluxeRooms))
        {
            // system("CLS");
            cout << "[*] " << deluxeRooms << endl;
        }
    }
    soloList.close();
    twinList.close();
    deluxeList.close();
}

void removeSoloRooms()
{

    fstream confirmedBooks;
    string confirmedUser;
    string confirmedRoom;

    confirmedBooks.open("soloConfirmedBooking.txt", ios::in);
    if (!confirmedBooks.is_open())
    {
        cerr << "File not found\n";
        return;
    }
    else if (confirmedBooks.is_open())
    {
        while (confirmedBooks >> confirmedUser >> confirmedRoom)
        {

            fstream roomNoAvail;
            fstream noAvailTemp;
            string noAvailTxt;
            bool notAvail = false;

            roomNoAvail.open("soloRooms.txt", ios::in);
            noAvailTemp.open("tempAvail.txt", ios::out);
            if (!roomNoAvail.is_open() || !noAvailTemp.is_open())
            {
                cerr << "File not found\n";
                return;
            }
            else if (roomNoAvail.is_open() || noAvailTemp.is_open())
            {
                while (getline(roomNoAvail, noAvailTxt))
                {
                    if (noAvailTxt != confirmedRoom)
                    {
                        noAvailTemp << noAvailTxt << endl;
                    }
                    else
                    {
                        notAvail = true;
                    }
                }
                roomNoAvail.close();
                noAvailTemp.close();
            }

            if (notAvail)
            {
                remove("soloRooms.txt");
                rename("tempAvail.txt", "soloRooms.txt");
            }
            else
            {
                remove("tempAvail.txt");
            }
        }
    }
    confirmedBooks.close();
}

void removeTwinRooms()
{

    fstream confirmedBooks;
    string confirmedUser;
    string confirmedRoom;

    confirmedBooks.open("twinConfirmedBooking.txt", ios::in);
    if (!confirmedBooks.is_open())
    {
        cerr << "File not found\n";
        return;
    }
    else if (confirmedBooks.is_open())
    {
        while (confirmedBooks >> confirmedUser >> confirmedRoom)
        {

            fstream roomNoAvail;
            fstream noAvailTemp;
            string noAvailTxt;
            bool notAvail = false;

            roomNoAvail.open("twinBed.txt", ios::in);
            noAvailTemp.open("tempAvail.txt", ios::out);
            if (!roomNoAvail.is_open() || !noAvailTemp.is_open())
            {
                cerr << "File not found\n";
                return;
            }
            else if (roomNoAvail.is_open() || noAvailTemp.is_open())
            {
                while (getline(roomNoAvail, noAvailTxt))
                {
                    if (noAvailTxt != confirmedRoom)
                    {
                        noAvailTemp << noAvailTxt << endl;
                    }
                    else
                    {
                        notAvail = true;
                    }
                }
                roomNoAvail.close();
                noAvailTemp.close();
            }

            if (notAvail)
            {
                remove("twinBed.txt");
                rename("tempAvail.txt", "twinBed.txt");
            }
            else
            {
                remove("tempAvail.txt");
            }
        }
    }
    confirmedBooks.close();
}

void removeDeluxeRooms()
{

    fstream confirmedBooks;
    string confirmedUser;
    string confirmedRoom;

    confirmedBooks.open("deluxeConfirmedBooking.txt", ios::in);
    if (!confirmedBooks.is_open())
    {
        cerr << "File not found\n";
        return;
    }
    else if (confirmedBooks.is_open())
    {
        while (confirmedBooks >> confirmedUser >> confirmedRoom)
        {

            fstream roomNoAvail;
            fstream noAvailTemp;
            string noAvailTxt;
            bool notAvail = false;

            roomNoAvail.open("deluxeBed.txt", ios::in);
            noAvailTemp.open("tempAvail.txt", ios::out);
            if (!roomNoAvail.is_open() || !noAvailTemp.is_open())
            {
                cerr << "File not found\n";
                return;
            }
            else if (roomNoAvail.is_open() || noAvailTemp.is_open())
            {
                while (getline(roomNoAvail, noAvailTxt))
                {
                    if (noAvailTxt != confirmedRoom)
                    {
                        noAvailTemp << noAvailTxt << endl;
                    }
                    else
                    {
                        notAvail = true;
                    }
                }
                roomNoAvail.close();
                noAvailTemp.close();
            }

            if (notAvail)
            {
                remove("deluxeBed.txt");
                rename("tempAvail.txt", "deluxeBed.txt");
            }
            else
            {
                remove("tempAvail.txt");
            }
        }
    }
    confirmedBooks.close();
}

void allDisplayFunc()
{
    fstream soloList;
    fstream twinList;
    fstream deluxeList;
    string soloRooms;
    string deluxeRooms;
    string twinRooms;

    soloList.open("soloRooms.txt", ios::in);
    twinList.open("twinBed.txt", ios::in);
    deluxeList.open("deluxeBed.txt", ios::in);

    if (!soloList.is_open() || !twinList.is_open() || !deluxeList.is_open())
    {
        cout << "Available room file is missing\n";
        return;
    }
    else if (soloList.is_open() || twinList.is_open() || deluxeList.is_open())
    {
        cout << "\n Solo Rooms \n";
        while (getline(soloList, soloRooms))
        {
            // system("CLS");
            cout << "[*] " << soloRooms << endl;
        }
        cout << "\n Twin Bed Rooms \n";

        while (getline(twinList, twinRooms))
        {
            // system("CLS");
            cout << "[*] " << twinRooms << endl;
        }

        cout << "\n Deluxe Rooms \n";

        while (getline(deluxeList, deluxeRooms))
        {
            // system("CLS");
            cout << "[*] " << deluxeRooms << endl;
        }
    }
    soloList.close();
    twinList.close();
    deluxeList.close();
}

// https://stackoverflow.com/questions/29859796/c-auto-vs-auto#:~:text=So%2C%20in%20a%20nutshell%2C%20if,you%20want%20references%2C%20use%20auto%26%20.
// https://www.youtube.com/watch?v=2vOPEuiGXVo
// https://www.youtube.com/watch?v=TUBVZvzEQAs
// https://cplusplus.com/reference/utility/make_pair/
// https://stackoverflow.com/questions/50325078/how-to-send-an-error-message-when-c-string-user-input-empty