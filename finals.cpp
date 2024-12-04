#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

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
    Customer(string username, string password) : User(username, password) {}

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
        int choice;
        do {
            cout << "\nCustomer Menu:\n";
            cout << "1. View Personal Information\n";
            cout << "2. View Bookings (Update/Cancel)\n";
            cout << "3. View Available Flights\n";
            cout << "4. Book a Flight\n";
            cout << "5. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "\nPersonal Information\n";
                    cout << "Username: " << username << endl;
                    break;
                case 2:
                    viewBookings();
                    cout << "Select a booking to cancel or modify.\n";
                    cancelFlight(db);
                    break;
                case 3:
                    db.listFlights();
                    break;
                case 4:
                    bookFlight(db);
                    break;
                case 5:
                    cout << "Logged out.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                    break;
            }
        } while (choice != 5);
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
        int choice;
        cout << "\nManage Flights Menu:\n";
        cout << "1. Create Flight\n";
        cout << "2. Update Flight\n";
        cout << "3. Delete Flight\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                // Implement create flight logic
                break;
            case 2:
                // Implement update flight logic
                break;
            case 3:
                // Implement delete flight logic
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    void manageUsers() {
        int choice;
        cout << "\nManage Users Menu:\n";
        cout << "1. Create User\n";
        cout << "2. Update User\n";
        cout << "3. Delete User\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                // Implement create user logic
                break;
            case 2:
                // Implement update user logic
                break;
            case 3:
                // Implement delete user logic
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    void displayMenu(AirlineDatabase& db) override {
        int choice;
        do {
            cout << "\nAdmin Menu:\n";
            cout << "1. Manage Flights\n";
            cout << "2. Manage Users\n";
            cout << "3. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    manageFlights(db);
                    break;
                case 2:
                    manageUsers();
                    break;
                case 3:
                    cout << "Logged out.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                    break;
            }
        } while (choice != 3);
    }
};

int main() {
    AirlineDatabase db;
    db.addFlight(Flight("PA123", "Manila", "Cebu", "10:00 AM", "12:00 PM", 50, "A1", "T1"));
    db.addFlight(Flight("PA456", "Manila", "Davao", "2:00 PM", "4:00 PM", 40, "B1", "T2"));
    db.addFlight(Flight("PA789", "Manila", "Iloilo", "6:00 PM", "8:00 PM", 30, "C1", "T3"));

    int roleChoice;
    cout << "Welcome to the Airline Management System!\n";
    cout << "Are you signing up as:\n";
    cout << "1. Admin\n";
    cout << "2. Customer\n";
    cout << "Enter your choice: ";
    cin >> roleChoice;

    string username, password;
    if (roleChoice == 1 || roleChoice == 2) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (roleChoice == 1) {
            Admin admin(username, password);
            admin.login();
            admin.displayMenu(db);  // Pass db to Admin's displayMenu
        } else if (roleChoice == 2) {
            Customer customer(username, password);
            customer.login();
            customer.displayMenu(db);  // Pass db to Customer's displayMenu
        }
    } else {
        cout << "Invalid choice. Please restart the program.\n";
    }

    return 0;
}