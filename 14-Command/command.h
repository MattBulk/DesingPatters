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

    bool withdraw(int amount) {
        if(balance - amount >= overdraftLimit)
        {
            balance -= amount;
            print("deposited ", amount);
            print("balance is now ", balance);
            return true;
        }
        return false;
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

    virtual void call() = 0;
    virtual void undo() = 0;
};

class BankAccountCommand : public Command
{
public:
    /* data */
    BankAccount& account;
    enum Action {deposit, withdraw} action;
    int amount;
    bool withdrawalSucceded;
public:
    BankAccountCommand(BankAccount& account, const Action &action, const int &amount) : 
        account(account), action(action), amount(amount), withdrawalSucceded(false) {}

    ~BankAccountCommand() {}

    void call() override {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            break;
        
        case withdraw:
            withdrawalSucceded = account.withdraw(amount);
            break;
        }
    }

    void undo() override
    {
        switch (action)
        {
        case withdraw:
            if(withdrawalSucceded)
                account.deposit(amount);
            break;
        case deposit:
            account.withdraw(amount);
            break;
        }
    }
};

void commandExample();

// Composite Command

#include <vector>
#include <initializer_list>

class CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command
{
public:
    CompositeBankAccountCommand(const std::initializer_list<value_type> &items)
        : std::vector<BankAccountCommand>(items) {}
    void call() override
    {
        bool ok = true;
        for (auto& cmd : *this)
        {
            if(ok) {
                cmd.call();
                ok = cmd.withdrawalSucceded;
            }
            else
            {
                cmd.withdrawalSucceded = false;
            } 
        }

        print("Transfert result ", ok);
    }
    void undo() override
    {
        for (auto it = rbegin(); it != rend(); ++it)
            it->undo();
    }
};

class MoneyTransferCommand : public CompositeBankAccountCommand
{
public:
    MoneyTransferCommand(BankAccount &from,
                         BankAccount &to, int amount) : CompositeBankAccountCommand{
                                                            BankAccountCommand{from, BankAccountCommand::withdraw, amount},
                                                            BankAccountCommand{to, BankAccountCommand::deposit, amount}
                                                        } 
    {
        print("Start Transfert ", ".....");
    }
};

void compositeCommandExample();

// Command Query Separation

enum class CreatureAbility
{
    strength,
    agility
};

struct CreatureCommand
{
    enum Action
    {
        set,
        increaseBy,
        decreaseBy
    } action;
    CreatureAbility ability;
    int amount;
};

struct CreatureQuery
{
    CreatureAbility ability;
};

class CreatureC
{
    int strength, agility;

public:
    CreatureC(int strength, int agility) : strength{strength}, agility{agility} {}
    
    void process_command(const CreatureCommand &cc)
    {
        int *ability;
        switch (cc.ability)
        {
        case CreatureAbility::strength:
            ability = &strength;
            break;
        case CreatureAbility::agility:
            ability = &agility;
            break;
        }
        switch (cc.action)
        {
        case CreatureCommand::set:
            *ability = cc.amount;
            break;
        case CreatureCommand::increaseBy:
            *ability += cc.amount;
            break;
        case CreatureCommand::decreaseBy:
            *ability -= cc.amount;
            break;
        }
    }

    int process_query(const CreatureQuery &q) const
    {
        switch (q.ability)
        {
        case CreatureAbility::strength:
            return strength;
        case CreatureAbility::agility:
            return agility;
        }
        return 0;
    }

    void set_strength(int value)
    {
        process_command(CreatureCommand{CreatureCommand::set, CreatureAbility::strength, value});
    }

    int get_strength() const
    {
        return process_query(CreatureQuery{CreatureAbility::strength});
    }

    int get_agility() const
    {
        return process_query(CreatureQuery{CreatureAbility::agility});
    }

    friend std::ostream& operator<<(std::ostream &os, const CreatureC &p) {
        return os << " strength: "<< p.strength << " agility: "<< p.agility; 
    }
};

void commandQuerySeparationExample();

#endif