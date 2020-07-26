#ifndef COMMAND_H
#define COMMAND_H

#include "../commons.h"

class BankAccount
{
    /* data */
public:
    BankAccount(/* args */) {}
    ~BankAccount() {}

    void deposit(int amount) {
        balance += amount;
        print("deposited ", amount);
        print("balance is now ", balance);
    }

    void withdraw(int amount) {
        if(balance - amount >= overdraftLimit)
        {
            balance -= amount;
            print("deposited ", amount);
            print("balance is now ", balance);
        }
    }

    int balance = 0;
    int overdraftLimit = -500;
};

class Command
{
private:
    /* data */
public:
    Command(/* args */) {}
    ~Command() {}

    virtual void call() const = 0;
};

class BankAccountCommand : public Command
{
private:
    /* data */
    BankAccount& account;
    enum Action {deposit, withdraw} action;
    int amount;
public:
    BankAccountCommand(BankAccount& account, const Action action, const int amount) : 
        account(account), action(action), amount(amount) {}

    ~BankAccountCommand() {}

    void call() const override {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            break;
        
        case withdraw:
            account.withdraw(amount);
            break;
        }
    }
};

void commandExample();

#endif