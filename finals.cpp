#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

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

string getInputWithExitOption(const string& promptMessage) {
    string userInput;
    cout << promptMessage;
    cin >> userInput;

    // Normalize input to uppercase for uniformity
    userInput = normalizeString(userInput);
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

    if (userInput == "EXIT") {
        cout << "Exiting the process.\n";
    }
    return userInput;
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
    double price;

public:
    Flight(string flightNum, string origin, string dest, string depTime, string arrTime, int seats, string gate, string terminal, double price)
            : flightNumber(flightNum), origin(origin), destination(dest), departureTime(depTime), arrivalTime(arrTime),
              availableSeats(seats), gate(gate), terminal(terminal), price(price) {}

    string getFlightNumber() const { return flightNumber; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return departureTime; }
    string getArrivalTime() const { return arrivalTime; }
    int getAvailableSeats() const { return availableSeats; }
    string getGate() const { return gate; }
    string getTerminal() const { return terminal; }
    double getPrice() const { return price; }

    void decreaseSeats() { 
        if (availableSeats > 0) {
            --availableSeats;
        }
    }

    void increaseSeats() {
        ++availableSeats;
    }

    void displayFlightDetails() const {
        cout << "Flight Number: " << "\t" << flightNumber << "\t\tOrigin: " << "\t" << origin << "\t\tDestination: " << "\t\t" << destination
             << "\nDeparture: " << "\t" << departureTime << "\t\tArrival: " << "\t" << arrivalTime << "\t\tAvailable Seats: " << "\t" << availableSeats
             << "\nGate: " << "\t\t" << gate << "\t\tTerminal: " << "\t" << terminal << "\t\tPrice:" << "\t\t" << price << endl; 
    }
};

// AirlineDatabase class to store and manage flights and bookings
class AirlineDatabase {
private:
    vector<Flight> flights;

public:
    vector<Flight>& getFlights() { return flights; }
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
                if (flight.getAvailableSeats() > 0) {
                    flight.decreaseSeats();
                    return true;
                } else {
                    cout << "No seats available for this flight." << endl;
                    return false;
                }
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

    bool increaseSeats(const string& flightNumber) {
    for (auto& flight : flights) {
        if (flight.getFlightNumber() == flightNumber) {
            flight.increaseSeats();
            return true;
        }
    }
    return false;
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
        while (true) {
            db.listFlights();
            cout << "------------------------------------------------------------------------------------------------\n";

            string flightChoice = getInputWithExitOption("Enter flight number to book (or type 'EXIT' to cancel): ");

            if (flightChoice == "EXIT") return; // Exit booking process

            // Check if the flight exists in the database
            bool flightFound = false;
            for (Flight& flight : db.getFlights()) {
                if (flight.getFlightNumber() == flightChoice) {
                    flightFound = true;

                    if (flight.getAvailableSeats() > 0) {
                        flight.decreaseSeats(); // Reduce the available seats
                        bookings.push_back(flightChoice);
                        cout << "Flight " << flightChoice << " booked successfully.\n";
                    } else {
                        cout << "Sorry, no seats available for Flight " << flightChoice << ".\n";
                    }
                    break; // Exit the loop once the flight is found
                }
            }

            if (!flightFound) {
                cout << "Invalid flight number. Please select a valid flight from the list.\n";
                SystemPause();
                SystemClear();
            }
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
        while (true) {
            string flightChoice = getInputWithExitOption("Enter flight number to cancel (or type 'EXIT' to cancel): ");

            if (flightChoice == "EXIT") return; // Exit cancellation process

            // Remove from bookings
            auto it = find(bookings.begin(), bookings.end(), flightChoice);
            if (it != bookings.end()) {
                bookings.erase(it); // Erase flight from bookings
                if (db.increaseSeats(flightChoice)) { // Increase available seats in the database
                    cout << "Booking canceled successfully\n";
                } else {
                    cout << "Error: Could not update seat count.\n";
                }
            } else {
                cout << "Booking not found in your list.\n";
            }
        }
    }

    void generateReports(AirlineDatabase& db) {
        SystemClear();
        cout << "\nGenerating Report of Booked Flights...\n";

        if (bookings.empty()) {
            cout << "No bookings found.\n";
            return;
        }

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
                    SystemPause();
                    bookFlight(db);
                } else {
                    // Display existing bookings
                    cout << "\nYour Bookings:\n";
                    for (const auto& booking : bookings) {
                        cout << "Booking for Flight: " << booking << endl;
                    }

                    // Prompt user to cancel a flight
                    bool isValid = false;
                    while (!isValid) {
                        string cancelChoice;
                        cout << "\nWill you cancel a flight? (Y/N): ";
                        cin >> cancelChoice;

                        if (cancelChoice == "Y" || cancelChoice == "y") {
                            cancelFlight(db); // Call the method to cancel a flight
                            isValid = true;
                        } else if (cancelChoice == "N" || cancelChoice == "n") {
                            cout << "\nNo flights will be canceled. Returning to the menu...\n";
                            isValid = true;
                        } else {
                            cout << "\nInvalid input. Please enter 'Y' for Yes or 'N' for No.\n";
                        }
                    }
                }
                SystemPause();
                continue;
            } else if (choice == "4") {
                SystemClear();
                generateReports(db);
                SystemPause();
                continue;
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

        // Helper functions for input validation
    bool isValidFlightNumber(const string& flightNum) {
        regex pattern("^[A-Z]{2}\\d{3}$"); // Format: Two uppercase letters followed by three digits
        return regex_match(flightNum, pattern);
    }

    bool isValidTimeFormat(const string& time) {
        regex pattern("^(0[1-9]|1[0-2]):[0-5][0-9](AM|PM)$"); // Format: HH:MMAM or HH:MMPM
        return regex_match(time, pattern);
    }

    bool isValidString(const string& input) {
        regex pattern("^[A-Za-z]+$"); // Only alphabets
        return regex_match(input, pattern);
    }

    bool isValidIntegerRange(int value, int min, int max) {
        return value >= min && value <= max;
    }

    int getValidInt(const string& prompt, int min, int max) {
        string input;
        while (true) {
            cout << prompt;
            cin >> input;

            // Check if input contains only digits
            bool isNumber = all_of(input.begin(), input.end(), ::isdigit);

            if (isNumber) {
                int value = stoi(input); // Convert string to integer
                if (value >= min && value <= max) {
                    return value;
                } else {
                    cout << "\nInvalid input. Please enter a number between " << min << " and " << max << ".\n";
                }
            } else {
                cout << "\nInvalid input. Please enter numbers only.\n";
            }
        }
    }

    string getValidInput(const string& prompt, const string& type) {
        string input;
        while (true) {
            cout << prompt;
            cin >> input;
            if ((type == "flightNum" && isValidFlightNumber(input)) ||
                (type == "time" && isValidTimeFormat(input)) ||
                (type == "string" && isValidString(input))) {
                return input;
            } else {
                cout << "Invalid input. ";
                if (type == "flightNum") cout << "\nFlight number should be 2 letters followed by 3 digits (e.g., PA123).\n";
                if (type == "time") cout << "\nTime should be in the format HH:MMAM or HH:MMPM (e.g., 02:00PM).\n";
                if (type == "string") cout << "\nThis field should contain alphabets only.\n";
            }
        }
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
                string flightNumber = getValidInput("\nEnter flight number: ", "flightNum");
                string origin = getValidInput("\nEnter origin: ", "string");
                string destination = getValidInput("\nEnter destination: ", "string");
                string departureTime = getValidInput("\nEnter departure time (HH:MMAM/PM): ", "time");
                string arrivalTime = getValidInput("\nEnter arrival time (HH:MMAM/PM): ", "time");
                int availableSeats = getValidInt("\nEnter number of seats: ", 1, 999);
                int gate = getValidInt("\nEnter gate (1-30): ", 1, 30);
                int terminal = getValidInt("\nEnter terminal (1-15): ", 1, 15);
                double price = getValidInt("\nEnter price: ", 1, 100000); 

                db.addFlight(Flight(flightNumber, origin, destination, departureTime, arrivalTime, availableSeats, to_string(gate), to_string(terminal), price));
                SystemClear();
                cout << "\nFlight added successfully.\n";
                cout << "------------------------------------------------------------------------------------------------\n";
                cout << "Flight Number: " << "\t" << flightNumber << "\t\tOrigin: " << "\t" << origin << "\t\tDestination: " << "\t\t" << destination
                << "\nDeparture: " << "\t" << departureTime << "\t\tArrival: " << "\t" << arrivalTime << "\t\tAvailable Seats: " << "\t" << availableSeats
                << "\nGate: " << "\t\t" << gate << "\t\tTerminal: " << "\t" << terminal << "\t\tPrice:" << "\t\t" << "P" <<price << endl;
                cout << "------------------------------------------------------------------------------------------------\n";
                SystemPause();
            } else if (choice == "2") {
                bool removing = true;

                while (removing) {
                    SystemClear();
                    db.listFlights();
                    cout << "\nRemove a Flight\n";
                    string flightNum = getValidInput("Enter flight number to remove: ", "flightNum");

                    if (db.removeFlight(flightNum)) {
                        cout << "\nFlight removed successfully.\n";
                    } else {
                        cout << "\nFlight not found.\n";
                    }

                    bool isValid = false;
                    while (!isValid) {
                        string option;
                        cout << "\nDo you want to remove another flight? (Y/N): ";
                        cin >> option;

                        if (option == "Y" || option == "y") {
                            isValid = true;
                            removing = true;
                        } else if (option == "N" || option == "n") {
                            isValid = true;
                            removing = false;
                            cout << "\nReturning to Manage Flights Menu...\n";
                        } else {
                            cout << "\nInvalid input. Please enter 'Y' for Yes or 'N' for No.\n";
                        }
                    }
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
                continue;
            }
        }
    }

    void generateReports(AirlineDatabase& db) {
    SystemClear();
    cout << "\nGenerating Reports...\n";

    cout << "\nFlight Details Report:\n";
    db.listFlights(); // Use existing method to display flight details

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
    db.addFlight(Flight("PA123", "Manila", "Cebu", "10:00 AM", "12:00 PM", 50, "A1", "T1", 5000.00));
    db.addFlight(Flight("PA456", "Manila", "Davao", "02:00 PM", "04:00 PM", 40, "B1", "T2", 7500.00));
    db.addFlight(Flight("PA789", "Manila", "Iloilo", "06:00 PM", "08:00 PM", 30, "C1", "T3", 6000.00));

    bool running = true;

    while (running) {
        SystemClear();
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

        if (roleChoice == "1") {
            SystemClear();
            bool isValidPass = true;
            while (isValidPass) {
                // Admin login process
                string username, password;
                SystemClear();
                cout << "\n---------------------------------------------\n";
                cout << "Admin Login\n";
                cout << "---------------------------------------------\n";
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (username == "Admin" && password == "admin123") {
                    Admin admin(username, password);
                    admin.login();
                    admin.displayMenu(db);
                    isValidPass = false;
                } else {
                    SystemClear();
                    cout << "\nInvalid Username & Password. Redirecting to Main Menu...\n\n";
                    SystemPause();
                    break;
                }
            }
        } else if (roleChoice == "2") {
            // Directly access customer menu without login
            SystemClear();
            cout << "\nWelcome to the Customer Menu!\n";
            Customer customer("Guest", ""); // Placeholder username for Customer
            customer.displayMenu(db);
        } else if (roleChoice == "3") {
            // Exit the application
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
