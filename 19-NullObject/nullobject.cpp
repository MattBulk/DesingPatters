#include "nullobject.h"

std::shared_ptr<LoggerN> OptionalLoggerN::no_logging{};

// I am not able to implement the OptionalLogger... damn example in the book

void nullObjectExample() {

    std::shared_ptr<LoggerN> console = std::make_shared<ConsoleLoggerN>();

    BankAccountN account{"Matteo Bi", 1000, console};
    account.deposit(1000); 
}