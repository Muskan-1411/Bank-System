#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <string>

class BankSystem {
public:
    void run();  // Main menu

private:
    std::string currentUser;
    bool isLoggedIn = false;

    void showWelcomeMenu();
    void registerUser();
    void loginUser();
    void logoutUser();

    void showMainMenu();
    void deposit();
    void withdraw();
    void checkBalance();
    void showAccountDetails();

    std::string getHashedPassword(const std::string& password);
    bool userExists(const std::string& username);
};

#endif
