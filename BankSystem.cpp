#include "BankSystem.h"
#include "SHA256.h"

#include <iostream>
#include <fstream>
#include <sstream>



void BankSystem::run() {
    while (true) {
        showWelcomeMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: std::cout << "Exiting...\n"; return;
            default: std::cout << "Invalid choice.\n";
        }
    }
}

void BankSystem::showWelcomeMenu() {
    std::cout << "\n=== Welcome to Non-GUI Banking App ===\n";
    std::cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
}

bool BankSystem::userExists(const std::string& username) {
    std::ifstream file("data/" + username + ".txt");
    return file.good();

}

std::string BankSystem::getHashedPassword(const std::string& password) {
    return SHA256::hash(password);
}

void BankSystem::registerUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    if (userExists(username)) {
        std::cout << "User already exists.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    std::ofstream file("data/" + username + ".txt");
    file << getHashedPassword(password) << "\n";
    file << 0.0 << "\n"; // initial balance
    file.close();

    std::cout << "Registered successfully.\n";
}

void BankSystem::loginUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    if (!userExists(username)) {
        std::cout << "User not found.\n";
        return;
    }

    std::ifstream file("data/" + username + ".txt");
    std::string storedHash;
    std::getline(file, storedHash);

    std::cout << "Enter password: ";
    std::cin >> password;

    if (getHashedPassword(password) != storedHash) {
        std::cout << "Incorrect password.\n";
        return;
    }

    currentUser = username;
    isLoggedIn = true;
    std::cout << "Login successful.\n";

    showMainMenu();
}

void BankSystem::logoutUser() {
    isLoggedIn = false;
    currentUser = "";
    std::cout << "Logged out.\n";
}

void BankSystem::showMainMenu() {
    while (isLoggedIn) {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Account Details\n5. Logout\nChoose: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: deposit(); break;
            case 2: withdraw(); break;
            case 3: checkBalance(); break;
            case 4: showAccountDetails(); break;
            case 5: logoutUser(); return;
            default: std::cout << "Invalid choice.\n";
        }
    }
}

void BankSystem::deposit() {
    double amount;
    std::cout << "Enter deposit amount: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Invalid amount.\n";
        return;
    }

    std::string filepath = "data/" + currentUser + ".txt";
    std::ifstream inFile(filepath);
    std::string hash;
    double balance;
    inFile >> hash >> balance;
    inFile.close();

    balance += amount;

    std::ofstream outFile(filepath);
    outFile << hash << "\n" << balance << "\n";
    outFile.close();

    std::cout << "Deposited successfully. New Balance: " << balance << "\n";
}

void BankSystem::withdraw() {
    double amount;
    std::cout << "Enter withdrawal amount: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Invalid amount.\n";
        return;
    }

    std::string filepath = "data/" + currentUser + ".txt";
    std::ifstream inFile(filepath);
    std::string hash;
    double balance;
    inFile >> hash >> balance;
    inFile.close();

    if (amount > balance) {
        std::cout << "Insufficient funds.\n";
        return;
    }

    balance -= amount;

    std::ofstream outFile(filepath);
    outFile << hash << "\n" << balance << "\n";
    outFile.close();

    std::cout << "Withdrawal successful. New Balance: " << balance << "\n";
}

void BankSystem::checkBalance() {
    std::ifstream file("data/" + currentUser + ".txt");
    std::string hash;
    double balance;
    file >> hash >> balance;
    std::cout << "Your current balance: " << balance << "\n";
}

void BankSystem::showAccountDetails() {
    std::cout << "Username: " << currentUser << "\n";
    checkBalance();
}
