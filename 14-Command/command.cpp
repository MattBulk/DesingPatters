#include "command.h"

void commandExample() {
    BankAccount ba;
    BankAccountCommand cmd(&ba, BankAccount::deposit, 100);
    cmd.call();

}