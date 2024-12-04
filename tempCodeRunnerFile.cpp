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