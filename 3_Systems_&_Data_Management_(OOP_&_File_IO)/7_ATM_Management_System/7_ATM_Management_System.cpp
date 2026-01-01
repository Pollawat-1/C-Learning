#include <iostream>
#include <vector>
#include <string>

class Account {
private:
    long accountNumber;
    int pin;
    double balance;
    std::string ownerName;

public:
    // Constructor
    Account(long accNum, int p, double initialBalance, std::string name) {
        accountNumber = accNum;
        pin = p;
        balance = initialBalance;
        ownerName = name;
    }

    // GETTER: Allows the main program to read the ID (but not change it)
    long getAccountNumber() const {
        return accountNumber;
    }

    // Login Validation
    bool validatePin(int p) {
        return (pin == p);
    }

    std::string getName() {
        return ownerName;
    }

    void checkBalance() {
        std::cout << "Owner: " << ownerName << " | Balance: $" << balance << std::endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited $" << amount << ". New Balance: $" << balance << std::endl;
        } else {
            std::cout << "Invalid amount." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds." << std::endl;
        } else if (amount <= 0) {
            std::cout << "Invalid amount." << std::endl;
        } else {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << ". Remaining Balance: $" << balance << std::endl;
        }
    }
};

// Function to find an account index in the vector
// Returns -1 if not found
int findAccountIndex(const std::vector<Account>& accounts, long accNum) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNumber() == accNum) {
            return i; // Return the position of the found account
        }
    }
    return -1; // Not found
}

// Function to handle the ATM operations for a specific logged-in user
// We pass 'Account&' (Reference) so changes stick!
void userSession(Account& userAccount) {
    int choice;
    do {
        std::cout << "\n--- Welcome " << userAccount.getName() << " ---" << std::endl;
        std::cout << "1. Check Balance" << std::endl;
        std::cout << "2. Deposit" << std::endl;
        std::cout << "3. Withdraw" << std::endl;
        std::cout << "4. Logout" << std::endl;
        std::cout << "Choose: ";
        std::cin >> choice;

        double amount;
        switch(choice) {
            case 1: userAccount.checkBalance(); break;
            case 2: 
                std::cout << "Amount to deposit: ";
                std::cin >> amount;
                userAccount.deposit(amount);
                break;
            case 3:
                std::cout << "Amount to withdraw: ";
                std::cin >> amount;
                userAccount.withdraw(amount);
                break;
            case 4: std::cout << "Logging out..." << std::endl; break;
            default: std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 4);
}

// Function to create a new account
void createAccount(std::vector<Account>& accounts) {
    long accNum;
    int pin;
    std::string name;
    
    std::cout << "\n=== Create New Account ===" << std::endl;
    std::cout << "Enter Account Number (e.g., 1001): ";
    std::cin >> accNum;
    
    // Check if ID already exists
    if (findAccountIndex(accounts, accNum) != -1) {
        std::cout << "Error: Account Number already exists!" << std::endl;
        return;
    }

    std::cout << "Enter Name (No spaces): ";
    std::cin >> name;
    std::cout << "Set a 4-digit PIN: ";
    std::cin >> pin;

    // Create object and add to vector (Initial balance is always 0 for safety)
    Account newAcc(accNum, pin, 0.0, name);
    accounts.push_back(newAcc);
    
    std::cout << "Account created successfully!" << std::endl;
}

int main() {
    std::vector<Account> bankAccounts;
    int mainChoice;

    // Pre-load one account for testing
    bankAccounts.push_back(Account(12345, 9999, 500.0, "AdminUser"));

    do {
        std::cout << "\n=== BANK SYSTEM MAIN MENU ===" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Create New Account" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Select: ";
        std::cin >> mainChoice;

        if (mainChoice == 1) {
            long loginAcc;
            int loginPin;
            
            std::cout << "Enter Account Number: ";
            std::cin >> loginAcc;
            
            int index = findAccountIndex(bankAccounts, loginAcc);
            
            if (index != -1) {
                std::cout << "Enter PIN: ";
                std::cin >> loginPin;
                
                // Validate PIN using the class method
                if (bankAccounts[index].validatePin(loginPin)) {
                    // Success! Pass the specific account to the session
                    userSession(bankAccounts[index]);
                } else {
                    std::cout << "Error: Incorrect PIN." << std::endl;
                }
            } else {
                std::cout << "Error: Account not found." << std::endl;
            }
        } 
        else if (mainChoice == 2) {
            createAccount(bankAccounts);
        }

    } while (mainChoice != 3);

    return 0;
}