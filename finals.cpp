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

    string getFlightNumber() { return flightNumber; }
    string getOrigin() { return origin; }
    string getDestination() { return destination; }
    string getDepartureTime() { return departureTime; }
    string getArrivalTime() { return arrivalTime; }
    int getAvailableSeats() { return availableSeats; }
    string getGate() { return gate; }
    string getTerminal() { return terminal; }

    void decreaseSeats() { availableSeats--; }

    void displayFlightDetails() const {
        cout << "Flight Number: " << flightNumber << "\tOrigin: " << origin << "\tDestination: " << destination
             << "\nDeparture: " << departureTime << "\tArrival: " << arrivalTime << "\tAvailable Seats: " << availableSeats
             << "\nGate: " << gate << "\tTerminal: " << terminal << endl;
    }
};

// AirlineDatabase class to store and manage flights and bookings
class AirlineDatabase {
private:
    vector<Flight> flights;

public:
    void addFlight(const Flight& flight) {
        flights.push_back(flight);
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
            flight.displayFlightDetails();
            cout << "-----------------------------------\n";
        }
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
        string flightChoice;
        cout << "Enter flight number to book: ";
        cin >> flightChoice;
        bookings.push_back(flightChoice);
        cout << "Flight " << flightChoice << " booked successfully.\n";
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

    void displayMenu(AirlineDatabase& db) override {
        bool isRunning = true;

        while (isRunning) {
            string choice;
            SystemClear();
            cout << "\nCustomer Menu:\n";
            cout << "[1] View Personal Information\n";
            cout << "[2] Book a Flight\n";
            cout << "[3] Already Booked?\n";
            cout << "[4] Logout\n";
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

// Admin class inherits from User
class Admin : public User {
public:
    Admin(string username, string password) : User(username, password) {}

    void login() override {
        cout << "\nLogged in as Admin: " << username << endl;
    }

    void manageFlights(AirlineDatabase& db) {
        cout << "\nManage Flights Menu: (Functionality not implemented yet)\n";
    }

    void manageUsers() {
        cout << "\nManage Users Menu: (Functionality not implemented yet)\n";
    }

    void displayMenu(AirlineDatabase& db) override {
        bool isRunning = true;

        while (isRunning) {
            string choice;
            SystemClear();
            cout << "\nAdmin Menu:\n";
            cout << "[1] Manage Flights\n";
            cout << "[2] Manage Users\n";
            cout << "[3] Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1") {
                SystemClear();
                cout << "check\n";
                SystemPause();
                continue;
            } else if (choice == "2") {
                SystemClear();
                cout << "check\n";
                SystemPause();
                continue;
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
    db.addFlight(Flight("PA456", "Manila", "Davao", "2:00 PM", "4:00 PM", 40, "B1", "T2"));
    db.addFlight(Flight("PA789", "Manila", "Iloilo", "6:00 PM", "8:00 PM", 30, "C1", "T3"));

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

        if (roleChoice == "1") {
            SystemClear();
            cout << "Admin Login\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            Admin admin(username, password);
            admin.login();
            admin.displayMenu(db);
        } else if (roleChoice == "2") {
            SystemClear();
            cout << "Customer Login\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            Customer customer(username, password);
            customer.login();
            customer.displayMenu(db);
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
