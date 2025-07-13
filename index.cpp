#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Account class
class Account {
public:
    int accNumber;
    string name;
    double balance;

    Account() : accNumber(0), name(""), balance(0.0) {}
    Account(int acc, string nm, double bal) : accNumber(acc), name(nm), balance(bal) {}

    void display() {
        cout << left << setw(10) << accNumber
             << setw(20) << name
             << right << setw(10) << balance << endl;
    }
};

// Node for Linked List
class Node {
public:
    Account data;
    Node* next;

    Node(Account acc) : data(acc), next(nullptr) {}
};

// Linked List class
class AccountList {
private:
    Node* head;

public:
    AccountList() : head(nullptr) {}

    void addAccount(Account acc) {
        Node* newNode = new Node(acc);
        newNode->next = head;
        head = newNode;
    }

    void displayAll() {
        Node* current = head;
        cout << "\n--- All Accounts ---\n";
        cout << left << setw(10) << "Acc No" << setw(20) << "Name" << right << setw(10) << "Balance" << endl;
        while (current) {
            current->data.display();
            current = current->next;
        }
    }

    Node* search(int accNo) {
        Node* current = head;
        while (current) {
            if (current->data.accNumber == accNo)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    void deleteAccount(int accNo) {
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->data.accNumber == accNo) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Account deleted successfully.\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Account not found.\n";
    }

    void updateAccount(int accNo) {
        Node* node = search(accNo);
        if (node) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, node->data.name);
            cout << "Enter new balance: ";
            cin >> node->data.balance;
            cout << "Account updated.\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void saveToFile() {
        ofstream file("accounts.dat", ios::binary | ios::out);
        Node* current = head;
        while (current) {
            file.write((char*)&current->data, sizeof(Account));
            current = current->next;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("accounts.dat", ios::binary | ios::in);
        if (!file) return;

        Account temp;
        while (file.read((char*)&temp, sizeof(Account))) {
            addAccount(temp);
        }
        file.close();
    }

    ~AccountList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Main Bank System
class BankSystem {
private:
    AccountList accList;

public:
    BankSystem() {
        accList.loadFromFile();
    }

    void menu() {
        int choice;
        do {
            cout << "\n====== Bank Management System ======\n";
            cout << "1. Create Account\n";
            cout << "2. View All Accounts\n";
            cout << "3. Search Account\n";
            cout << "4. Deposit\n";
            cout << "5. Withdraw\n";
            cout << "6. Delete Account\n";
            cout << "7. Update Account\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: createAccount(); break;
                case 2: accList.displayAll(); break;
                case 3: searchAccount(); break;
                case 4: deposit(); break;
                case 5: withdraw(); break;
                case 6: deleteAccount(); break;
                case 7: accList.updateAccount(getAccountNo()); break;
                case 0: 
                    accList.saveToFile();
                    cout << "Exiting... Data saved.\n"; 
                    break;
                default: cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 0);
    }

    void createAccount() {
        int accNo;
        string name;
        double balance;

        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;

        Account acc(accNo, name, balance);
        accList.addAccount(acc);
        cout << "Account Created Successfully!\n";
    }

    void searchAccount() {
        int accNo = getAccountNo();
        Node* node = accList.search(accNo);
        if (node) {
            cout << "Account Found:\n";
            node->data.display();
        } else {
            cout << "Account Not Found.\n";
        }
    }

    void deposit() {
        int accNo = getAccountNo();
        Node* node = accList.search(accNo);
        if (node) {
            double amt;
            cout << "Enter amount to deposit: ";
            cin >> amt;
            node->data.balance += amt;
            cout << "Amount deposited.\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void withdraw() {
        int accNo = getAccountNo();
        Node* node = accList.search(accNo);
        if (node) {
            double amt;
            cout << "Enter amount to withdraw: ";
            cin >> amt;
            if (node->data.balance >= amt) {
                node->data.balance -= amt;
                cout << "Withdrawal successful.\n";
            } else {
                cout << "Insufficient balance.\n";
            }
        } else {
            cout << "Account not found.\n";
        }
    }

    void deleteAccount() {
        int accNo = getAccountNo();
        accList.deleteAccount(accNo);
    }

    int getAccountNo() {
        int accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;
        return accNo;
    }
};

int main() {
    BankSystem system;
    system.menu();
    return 0;
}




int main() {
    int choice;
    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit Money\n";
        cout << "5. Withdraw Money\n";
        cout << "6. Modify Account\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: createNewAccount(); break;
            case 2: showAllAccounts(); break;
            case 3: searchAccount(); break;
            case 4: depositMoney(); break;
            case 5: withdrawMoney(); break;
            case 6: modifyAccount(); break;
            case 7: deleteAccount(); break;
            case 8: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}


