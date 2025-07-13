#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Account {
private:
    int accNumber;
    string name;
    double balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() const {
        cout << left << setw(10) << accNumber
             << setw(20) << name
             << right << setw(10) << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient balance.\n";
    }

    int getAccNumber() const { return accNumber; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    void updateAccount() {
        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter New Balance: ";
        cin >> balance;
    }
};

// File Handling Functions
void writeAccount() {
    Account acc;
    acc.createAccount();

    ofstream outFile("accounts.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&acc), sizeof(Account));
    outFile.close();

    cout << "Account created successfully.\n";
}

void displayAll() {
    Account acc;
    ifstream inFile("accounts.dat", ios::binary);

    cout << "\n--- All Accounts ---\n";
    cout << left << setw(10) << "Acc No" << setw(20) << "Name" << right << setw(10) << "Balance" << endl;

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        acc.showAccount();
    }

    inFile.close();
}

void searchAccount(int accNo) {
    Account acc;
    ifstream inFile("accounts.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        if (acc.getAccNumber() == accNo) {
            cout << "\nAccount Found:\n";
            acc.showAccount();
            found = true;
            break;
        }
    }

    inFile.close();
    if (!found)
        cout << "Account not found.\n";
}

void depositWithdraw(int accNo, int option) {
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    Account acc;
    bool found = false;

    while (!file.eof()) {
        streampos pos = file.tellg();
        file.read(reinterpret_cast<char*>(&acc), sizeof(Account));

        if (acc.getAccNumber() == accNo) {
            double amount;
            if (option == 1) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                acc.deposit(amount);
            } else {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                acc.withdraw(amount);
            }

            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&acc), sizeof(Account));
            cout << "Transaction completed.\n";
            found = true;
            break;
        }
    }

    file.close();
    if (!found)
        cout << "Account not found.\n";
}

void deleteAccount(int accNo) {
    Account acc;
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        if (acc.getAccNumber() != accNo) {
            outFile.write(reinterpret_cast<char*>(&acc), sizeof(Account));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found)
        cout << "Account deleted successfully.\n";
    else
        cout << "Account not found.\n";
}

void updateAccount(int accNo) {
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    Account acc;
    bool found = false;

    while (!file.eof()) {
        streampos pos = file.tellg();
        file.read(reinterpret_cast<char*>(&acc), sizeof(Account));

        if (acc.getAccNumber() == accNo) {
            acc.updateAccount();
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&acc), sizeof(Account));
            cout << "Account updated successfully.\n";
            found = true;
            break;
        }
    }

    file.close();
    if (!found)
        cout << "Account not found.\n";
}

// Menu
void menu() {
    int choice, accNo;

    do {
        cout << "\n====== Bank Management System (File Handling) ======\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Delete Account\n";
        cout << "7. Update Account\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: writeAccount(); break;
            case 2: displayAll(); break;
            case 3:
                cout << "Enter Account Number to Search: ";
                cin >> accNo;
                searchAccount(accNo);
                break;
            case 4:
                cout << "Enter Account Number to Deposit: ";
                cin >> accNo;
                depositWithdraw(accNo, 1);
                break;
            case 5:
                cout << "Enter Account Number to Withdraw: ";
                cin >> accNo;
                depositWithdraw(accNo, 2);
                break;
            case 6:
                cout << "Enter Account Number to Delete: ";
                cin >> accNo;
                deleteAccount(accNo);
                break;
            case 7:
                cout << "Enter Account Number to Update: ";
                cin >> accNo;
                updateAccount(accNo);
                break;
            case 0:
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
