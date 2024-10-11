#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Structure to represent an account
struct Account {
    string accountNumber;
    string username;
    string password;
    double balance;
};

// Function declarations
void createAccount(unordered_map<string, Account>& accounts);
bool login(const unordered_map<string, Account>& accounts, Account& loggedInAccount);
void depositMoney(Account& account);
void withdrawMoney(Account& account);
void checkBalance(const Account& account);
void showMenu();

int main() {
    unordered_map<string, Account> accounts;
    int choice;
    bool isLoggedIn = false;
    Account loggedInAccount;

    while (true) {
        if (!isLoggedIn) {
            cout << "\n1. Create Account\n2. Login\n3. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    createAccount(accounts);
                    break;
                case 2:
                    isLoggedIn = login(accounts, loggedInAccount);
                    break;
                case 3:
                    cout << "Exiting program...\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } else {
            showMenu();
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    depositMoney(loggedInAccount);
                    break;
                case 2:
                    withdrawMoney(loggedInAccount);
                    break;
                case 3:
                    checkBalance(loggedInAccount);
                    break;
                case 4:
                    cout << "Logging out...\n";
                    isLoggedIn = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    return 0;
}

void createAccount(unordered_map<string, Account>& accounts) {
    Account newAccount;
    cout << "Enter account number: ";
    cin >> newAccount.accountNumber;
    cout << "Enter username: ";
    cin >> newAccount.username;
    cout << "Enter password: ";
    cin >> newAccount.password;
    newAccount.balance = 0.0;
    accounts[newAccount.username] = newAccount;
    cout << "Account created successfully!\n";
}

bool login(const unordered_map<string, Account>& accounts, Account& loggedInAccount) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto it = accounts.find(username);
    if (it != accounts.end() && it->second.password == password) {
        loggedInAccount = it->second;
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid username or password.\n";
        return false;
    }
}

void depositMoney(Account& account) {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid amount. Please try again.\n";
        return;
    }
    account.balance += amount;
    cout << "Deposit successful! New balance: $" << account.balance << "\n";
}

void withdrawMoney(Account& account) {
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid amount. Please try again.\n";
    } else if (amount > account.balance) {
        cout << "Insufficient funds.\n";
    } else {
        account.balance -= amount;
        cout << "Withdrawal successful! New balance: $" << account.balance << "\n";
    }
}

void checkBalance(const Account& account) {
    cout << "Current balance: $" << account.balance << "\n";
}

void showMenu() {
    cout << "\n1. Deposit Money\n2. Withdraw Money\n3. Check Balance\n4. Logout\n";
}