#include <iostream>
#include <cstring>
using namespace std;

class Customer
{
    int id;
    string name;

public:
    Customer(int i, string n) : id(i), name(n) {}
    int getID() { return id; }
    string getName() { return name; }
};

class Account
{
    int accNum;
    double balance;
    Customer owner;

public:
    Account() : accNum(0), balance(0), owner(0, "") {}
    Account(int a, double b, const Customer &c) : accNum(a), balance(b), owner(c) {}
    friend class Bank;

    void deposit(double amount)
    {
        balance += amount;
    }

    bool withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            return true;
        }
        return false;
    }
    double getBalance() { return balance; }
    int getAccountNumber() { return accNum; }
};

class Bank
{
public:
    Account acc[10];
    int numAcc;

    Bank() : numAcc(0) {}

    void openAcc(Customer c, double initialDeposit)
    {
        if (numAcc < 10 && initialDeposit > 0)
        {
            acc[numAcc++] = Account(numAcc, initialDeposit, c);
            cout << "Account opened successfully for customer: " << c.getName() << endl;
        }
        else
        {
            cout << "Cannot open more accounts. Bank is full or initial deposit is not greater than 0." << endl;
        }
    }

    void displayAccountBalance(int accountNumber)
    {
        for (int i = 0; i < numAcc; i++)
        {
            if (acc[i].getAccountNumber() == accountNumber)
            {
                cout << "Account Balance: " << acc[i].getBalance() << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }
};

void operator+(Account &from, Account &to)
{
    double amount;
    cout << "Enter the deposit amount: ";
    cin >> amount;
    if (from.withdraw(amount))
    {
        to.deposit(amount);
        cout << "Transfer successful." << endl;
    }
    else
    {
        cout << "Insufficient funds for transfer." << endl;
    }
}

int main()
{
    Bank bank;
    Customer customer1(1, "Alice");
    Customer customer2(2, "Bob");
    bank.openAcc(customer1, 1000.0);
    bank.openAcc(customer2, 500.0);
    bank.displayAccountBalance(0);
    bank.displayAccountBalance(1);
    Account &aliceAccount = bank.acc[0];
    Account &bobAccount = bank.acc[1];
    aliceAccount + bobAccount;
    bank.displayAccountBalance(1);
    bank.displayAccountBalance(2);
    return 0;
}