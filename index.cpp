#include<iostream>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    double balance;

public:
    void createAccount();     // Input details
    void displayAccount();     //Show details
    void deposit(double);      //Add money
    bool withdraw(double);    // Remove money (check balance)
    int getAccountNumber();   // Get account number
    double getBalance();      // Get balance
    void modifyAccount();     // Change name
};

