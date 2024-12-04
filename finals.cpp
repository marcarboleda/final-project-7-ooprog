#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void SystemClear(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
};

void SystemPause() {
#ifdef _WIN32
    system("pause");
#else
    cout << "Press enter to continue..." << endl;
    string temp;
    getline(cin, temp);
#endif
};

string normalizeString(const string& input) {
    string normalized = input;
    transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}

// Flight class to store flight details
class Flight {
private:
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
    string arrivalTime;
    int availableSeats;
    string gate;
    string terminal;

public:
    Flight(string flightNum, string origin, string dest, string depTime, string arrTime, int seats, string gate, string terminal)
            : flightNumber(flightNum), origin(origin), destination(dest), departureTime(depTime), arrivalTime(arrTime),
              availableSeats(seats), gate(gate), terminal(terminal) {}

    string getFlightNumber() const { return flightNumber; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return departureTime; }
    string getArrivalTime() const { return arrivalTime; }
    int getAvailableSeats() const { return availableSeats; }
    string getGate() const { return gate; }
    string getTerminal() const { return terminal; }

    void decreaseSeats() { availableSeats--; }

    void displayFlightDetails() const {
        cout << "Flight Number: " << "\t" << flightNumber << "\t\tOrigin: " << "\t" << origin << "\t\tDestination: " << "\t\t" << destination
             << "\nDeparture: " << "\t" << departureTime << "\tArrival: " << "\t" << arrivalTime << "\tAvailable Seats: " << "\t" << availableSeats
             << "\nGate: " << "\t\t" << gate << "\t\tTerminal: " << "\t" << terminal << "\t" << endl;
    }
};

// AirlineDatabase class to store and manage flights and bookings
class AirlineDatabase {
private:
    vector<Flight> flights;

public:
    // vector<Flight> getFlights() const {
    //     return flights;
    // }

    void addFlight(const Flight& flight) {
        flights.push_back(flight);
    }

    bool removeFlight(const string& flightNumber) {
        auto it = remove_if(flights.begin(), flights.end(), [&](const Flight& flight) {
            return flight.getFlightNumber() == flightNumber;
        });

        if (it != flights.end()) {
            flights.erase(it, flights.end());
            return true;
        }
        return false;
    }

    bool cancelFlightBooking(const string& flightNumber) {
        for (auto& flight : flights) {
            if (flight.getFlightNumber() == flightNumber) {
                flight.decreaseSeats();
                return true;
            }
        }
        return false;
    }

    void listFlights() {
        cout << "\nAvailable Flights:\n";
        for (const auto& flight : flights) {
            cout << "------------------------------------------------------------------------------------------------\n";
            flight.displayFlightDetails();
        }
    }

    // **Add the getter for flights here**
    vector<Flight> getFlights() const {
        return flights;
    }
};


// User class to represent user details
class User {
protected:
    string username;
    string password;

public:
    User(string username, string password) : username(username), password(password) {}

    virtual void login() = 0;  // Pure virtual function for login
    virtual void displayMenu(AirlineDatabase& db) = 0;
};

// Customer class inherits from User
class Customer : public User {
private:
    vector<string> bookings;  // Store the booked flights

public:
    Customer(string username, string password) : User(username, password) { }

    void login() override {
        cout << "\nLogged in as Customer: " << username << endl;
    }

    void bookFlight(AirlineDatabase& db) {
        db.listFlights();
        cout << "------------------------------------------------------------------------------------------------\n";
        string flightChoice;
        cout << "Enter flight number to book: ";
        cin >> flightChoice;

        // Normalize the input to uppercase
        flightChoice = normalizeString(flightChoice);
        transform(flightChoice.begin(), flightChoice.end(), flightChoice.begin(), ::toupper);

        // Check if the flight exists in the database
        bool flightFound = false;
        for (const auto& flight : db.getFlights()) {
            if (flight.getFlightNumber() == flightChoice) {
                flightFound = true;

                if (flight.getAvailableSeats() > 0) {
                    bookings.push_back(flightChoice);
                    cout << "Flight " << flightChoice << " booked successfully.\n";
                    break;
                } else {
                    cout << "Sorry, no seats available for Flight " << flightChoice << ".\n";
                    break;
                }
            }
        }

        if (!flightFound) {
            cout << "Invalid flight number. Please select a valid flight from the list.\n";
        }
    }


    void viewBookings() {
        cout << "\nYour Bookings:\n";
        if (bookings.empty()) {
            cout << "No bookings found.\n";
            return;
        }
        for (const auto& booking : bookings) {
            cout << "Booking for Flight: " << booking << endl;
        }
    }

    void cancelFlight(AirlineDatabase& db) {
        string flightChoice;
        cout << "Enter flight number to cancel: ";
        cin >> flightChoice;

        // Remove from bookings
        auto it = find(bookings.begin(), bookings.end(), flightChoice);
        if (it != bookings.end()) {
            bookings.erase(it);  // Erase flight from bookings
            db.cancelFlightBooking(flightChoice);  // Decrease available seats in database
            cout << "Booking canceled successfully.\n";
        } else {
            cout << "Booking not found in your list.\n";
        }
    }

    void generateReports(AirlineDatabase& db) {
    SystemClear();
    cout << "\nGenerating Report of Booked Flights...\n";

    if (bookings.empty()) {
        cout << "No bookings found.\n";
    } else {
        for (const auto& booking : bookings) {
            cout << "Details for Booking: " << booking << endl;
            bool flightFound = false;

            // Find and display flight details
            for (const auto& flight : db.getFlights()) {
                if (flight.getFlightNumber() == booking) {
                    flight.displayFlightDetails();
                    flightFound = true;
                    break;
                }
            }

            if (!flightFound) {
                cout << "Flight " << booking << " not found in the database.\n";
            }
        }
    }

    SystemPause();
    }

    void displayMenu(AirlineDatabase& db) override {
        bool isRunning = true;

        while (isRunning) {
            string choice;
            SystemClear();
            cout << "\nCustomer Menu:\n";
            cout << "[1] View Personal Information\n";
            cout << "[2] Book a Flight\n";
            cout << "[3] Already Booked?\n";
            cout << "[4] Generate Reports\n";
            cout << "[5] Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1") {
                SystemClear();
                cout << "\nPersonal Information\n";
                cout << "Username: " << username << endl;
                viewBookings(); // Displays booking history under personal information
                SystemPause();
                continue;
            } else if (choice == "2") {
                SystemClear();
                bookFlight(db);
                SystemPause();
                continue;
            } else if (choice == "3") {
                SystemClear();
                if (bookings.empty()) {
                    cout << "No bookings found. Redirecting to booking...\n";
                    bookFlight(db);
                } else {
                    cout << "Managing bookings...\n";
                    viewBookings();
                    cancelFlight(db); // Option to manage bookings (cancel/update)
                }
                SystemPause();
                continue;
            } else if (choice == "4") {
                SystemClear();
                generateReports(db);
                SystemPause();
                break;
            } else if (choice == "5") {
                SystemClear();
                cout << "\nLogged out...\n";
                SystemPause();
                break;
            } else {
                SystemClear();
                cout << "\nInvalid choice. Try again.\n";
                SystemPause();
            }
        }
    }
};

class UserAccount {
private:
    string username;
    string password;

public:
    UserAccount(string username, string password) : username(username), password(password) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    void displayAccount() const {
        cout << "Username: " << username << endl;
    }
};

// Admin class inherits from User
class Admin : public User {
private:
    vector<UserAccount> userAccounts;

public:
    Admin(string username, string password) : User(username, password) {}

    void login() override {
        cout << "\nLogged in as Admin: " << username << endl;
    }


    void addUser() {
        SystemClear();
        cout << "\nAdd New User\n";
        string newUsername, newPassword;
        cout << "Enter username: ";
        cin >> newUsername;
        cout << "Enter password: ";
        cin >> newPassword;

        // Check if the username already exists
        auto it = find_if(userAccounts.begin(), userAccounts.end(), [&](const UserAccount& user) {
            return user.getUsername() == newUsername;
        });

        if (it != userAccounts.end()) {
            cout << "\nError: Username already exists.\n";
        } else {
            userAccounts.emplace_back(newUsername, newPassword);
            cout << "\nUser added successfully.\n";
        }
        SystemPause();
    }

    void viewUsers() {
        SystemClear();
        cout << "\nList of Users:\n";
        if (userAccounts.empty()) {
            cout << "No users found.\n";
        } else {
            for (const auto& user : userAccounts) {
                user.displayAccount();
            }
        }
        SystemPause();
    }

    void removeUser() {
        SystemClear();
        cout << "\nRemove User\n";
        string usernameToRemove;
        cout << "Enter username to remove: ";
        cin >> usernameToRemove;

        auto it = find_if(userAccounts.begin(), userAccounts.end(), [&](const UserAccount& user) {
            return user.getUsername() == usernameToRemove;
        });

        if (it != userAccounts.end()) {
            userAccounts.erase(it);
            cout << "\nUser removed successfully.\n";
        } else {
            cout << "\nError: User not found.\n";
        }
        SystemPause();
    }
    
    void manageFlights(AirlineDatabase& db) {
        bool isManaging = true;
        while (isManaging) {
            string choice;
            SystemClear();
            cout << "\nManage Flights Menu:\n";
            cout << "[1] Add Flight\n";
            cout << "[2] Remove Flight\n";
            cout << "[3] View All Flights\n";
            cout << "[4] Return to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1") {
                SystemClear();
                cout << "\nAdd a New Flight\n";
                string flightNum, origin, dest, depTime, arrTime, gate, terminal;
                int seats;

                cout << "Enter flight number: ";
                cin >> flightNum;
                cout << "Enter origin: ";
                cin >> origin;
                cout << "Enter destination: ";
                cin >> dest;
                cout << "Enter departure time: ";
                cin >> depTime;
                cout << "Enter arrival time: ";
                cin >> arrTime;
                cout << "Enter number of seats: ";
                cin >> seats;
                cout << "Enter gate: ";
                cin >> gate;
                cout << "Enter terminal: ";
                cin >> terminal;

                db.addFlight(Flight(flightNum, origin, dest, depTime, arrTime, seats, gate, terminal));
                cout << "\nFlight added successfully.\n";
                SystemPause();
            } else if (choice == "2") {
                SystemClear();
                cout << "\nRemove a Flight\n";
                string flightNum;

                cout << "Enter flight number to remove: ";
                cin >> flightNum;

                if (db.removeFlight(flightNum)) {
                    cout << "\nFlight removed successfully.\n";
                } else {
                    cout << "\nFlight not found.\n";
                }
                SystemPause();
            } else if (choice == "3") {
                SystemClear();
                cout << "\nViewing All Flights\n";
                db.listFlights();
                SystemPause();
            } else if (choice == "4") {
                SystemClear();
                cout << "\nReturning to Main Menu...\n";
                SystemPause();
                isManaging = false;
            } else {
                SystemClear();
                cout << "\nInvalid choice. Try again.\n";
                SystemPause();
            }
        }
    }

    void generateReports(AirlineDatabase& db) {
    SystemClear();
    cout << "\nGenerating Reports...\n";

    cout << "\nFlight Details Report:\n";
    db.listFlights(); // Use existing method to display flight details

    cout << "\nUser Accounts Report:\n";
    if (userAccounts.empty()) {
        cout << "No user accounts available.\n";
    } else {
        for (const auto& user : userAccounts) {
            user.displayAccount();
        }
    }

    SystemPause();
}
  
    void displayMenu(AirlineDatabase& db) override {
        bool isRunning = true;

        while (isRunning) {
            string choice;
            SystemClear();
            cout << "\nAdmin Menu:\n";
            cout << "[1] Manage Flights\n";
            cout << "[2] Generate Reports\n";
            cout << "[3] Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1") {
                manageFlights(db);
            } else if (choice == "2") {
                generateReports(db);
            } else if (choice == "3"){
                SystemClear();
                cout << "\nLogged out...\n";
                SystemPause();
                break;
            } else {
                SystemClear();
                cout << "\nInvalid choice. Try again.\n";
                SystemPause();
            }
        }

    }
};

int main() {
    AirlineDatabase db;
    db.addFlight(Flight("PA123", "Manila", "Cebu", "10:00 AM", "12:00 PM", 50, "A1", "T1"));
    db.addFlight(Flight("PA456", "Manila", "Davao", "02:00 PM", "04:00 PM", 40, "B1", "T2"));
    db.addFlight(Flight("PA789", "Manila", "Iloilo", "06:00 PM", "08:00 PM", 30, "C1", "T3"));

    bool running = true;

    while (running) {
        string roleChoice;
        cout << "\n"
                "  _      _                 _ _____  _    _ \n"
                " | |    (_)               | |  __ \\| |  | |\n"
                " | |     _ _ __   __ _  __| | |__) | |__| |\n"
                " | |    | | '_ \\ / _` |/ _` |  ___/|  __  |\n"
                " | |____| | |_) | (_| | (_| | |    | |  | |\n"
                " |______|_| .__/ \\__,_|\\__,_|_|    |_|  |_|\n"
                "          | |                              \n"
                "          |_|                              \n\n";
        cout << "-------------------------------------------\n";
        cout << "Please select an option:\n";
        cout << " [1] Admin\n";
        cout << " [2] Customer\n";
        cout << " [3] Exit\n";
        cout << "-------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> roleChoice;

        string username, password;

        if (roleChoice == "1" || roleChoice == "2") {
            SystemClear();
            cout << "\n---------------------------------------------\n";
            cout << (roleChoice == "1" ? "Admin Login" : "Customer Login") << "\n";
            cout << "---------------------------------------------\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (roleChoice == "1") {
                Admin admin(username, password);
                admin.login();
                admin.displayMenu(db);
            } else if (roleChoice == "2") {
                Customer customer(username, password);
                customer.login();
                customer.displayMenu(db);
            }
        } else if (roleChoice == "3") {
            SystemClear();
            cout << "\nExiting...\n";
            SystemPause();
            break;
        } else {
            cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}
