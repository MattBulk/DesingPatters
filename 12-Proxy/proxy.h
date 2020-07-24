#ifndef PROXY_H
#define PROXY_H

#include "../commons.h"

class BankAccountProxy
{
private:
    /* data */
public:
    BankAccountProxy(/* args */) {}
    ~BankAccountProxy() {}

    void deposit(int amount) {
        print("Amount ", amount);
    }
};

template <typename T>
class Property
{
private:
    T value;

public:
    Property(const T initialValue) {
        *this = initialValue;
    }

    operator T() {
        // getter
        return value;
    }

    T operator =(T newValue) {
        // setter
        return value = newValue;
    }

    friend std::ostream& operator<<(std::ostream &os, const Property &p) {
        return os << p.value; 
    }
};

class Image
{
private:
    /* data */
public:
    Image(/* args */) {}
    ~Image() {}

    virtual void draw() = 0;
};


void smartPointerExample();

void lazyExample();

#endif