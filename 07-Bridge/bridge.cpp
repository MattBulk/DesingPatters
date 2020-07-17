#include "bridge.h"

// the pimpl idiom
class Person;

class PersonImpl
{
private:
    /* data */
public:
    PersonImpl(/* args */) {}
    ~PersonImpl() {}

    void greet(Person *p) {
        print("Hello ", p->name);
    }
};

class Person
{
public:
    std::string name;
    void greet() {
        impl->greet(this);
    }
public:
    Person() : impl(new PersonImpl){ }
    ~Person() {
        delete impl;
    }

    PersonImpl *impl;
};

void pimplExample() {

    Person p;
    p.name = "Matt";

    p.greet(); 
}