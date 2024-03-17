#include "command.h"

void commandExample() {
    BankAccount ba;
    BankAccountCommand cmd(ba, BankAccountCommand::Action::deposit, 100);
    cmd.call();
    cmd.undo();
    cmd.call();
}

void compositeCommandExample() {

    BankAccount to, from;

    BankAccountCommand cmd(from, BankAccountCommand::Action::deposit, 300);
    cmd.call();

    MoneyTransferCommand trans(from, to, 400);
    trans.call();
}

void commandQuerySeparationExample() {
    CreatureQuery query;
    query.ability = CreatureAbility::strength;

    CreatureCommand cmd;
    cmd.action = CreatureCommand::Action::set;
    cmd.amount = 10;
    cmd.ability = CreatureAbility::strength;

    CreatureC creature{5 , 10};
    creature.process_command(cmd);

    print("Creature ", creature);
}