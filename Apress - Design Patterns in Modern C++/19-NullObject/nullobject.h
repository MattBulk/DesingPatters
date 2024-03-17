#ifndef NULLOBJECT_H
#define NULLOBJECT_H

#include "../commons.h"
#include <memory>
#include <boost/lexical_cast.hpp>

class LoggerN
{
private:
    /* data */
public:
    LoggerN(/* args */) {}
    ~LoggerN() {}

    virtual void info(const std::string &s) = 0;
    virtual void warn(const std::string &s) = 0;
};

class OptionalLoggerN : public LoggerN
{
    public:
    std::shared_ptr<LoggerN> impl;
    static std::shared_ptr<LoggerN> no_logging;

    OptionalLoggerN(const std::shared_ptr<LoggerN> &logger) : impl{logger} {}
    virtual void info(const std::string &s) override
    {
        if (impl)
            impl->info(s); // null check here
    }

    virtual void warn(const std::string &s) override
    {
        if (impl)
            impl->warn(s); // null check here
    }
    // and similar checks for other members
};

class BankAccountN
{
public:
    /* data */
    std::shared_ptr<LoggerN> log;
    std::string name;
    int balance = 0;

    // pointer to a class that checks nullprt
    std::shared_ptr<OptionalLoggerN> logger;

public:
    BankAccountN(const std::string &name, int balance, const std::shared_ptr<LoggerN> &logger) : log{logger}, name{name}, balance{balance} {}

    ~BankAccountN() {}

    void deposit(int amount)
    {
        balance += amount;
        log->info("Deposited $" + boost::lexical_cast<std::string>(amount) + " to " + name + ", balance is now $" +
                  boost::lexical_cast<std::string>(balance));
    }
};

class ConsoleLoggerN : public LoggerN
{
private:
    /* data */
public:
    ConsoleLoggerN(/* args */) {}
    ~ConsoleLoggerN() {}

    void info(const std::string &s) override
    {
        print("INFO ", s);
    }
    void warn(const std::string &s) override
    {
        print("WARNING!!! ", s);
    }
};

class NullObjectN : public LoggerN
{
private:
    /* data */
public:
    NullObjectN(/* args */) {}
    ~NullObjectN() {}

    void info(const std::string& s) override {}
    void warn(const std::string& s) override {}

};

void nullObjectExample();

#endif