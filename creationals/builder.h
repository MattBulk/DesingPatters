#ifndef BUILDER_H
#define BUILDER_H

#include "../commons.h"


class Person
{
public:
    // address
    std::string address, postCode, city;
    // employment
    std::string companyName, position;
    int income = 0;

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
public:
    Person(/* args */) {}
    ~Person() {}

    static Person& create() {
        PersonBuilder builder;
        return builder.p;
    }
};

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
    Person& person;
    explicit PersonBuilderBase(Person& p) : person{p} { }
public:
    operator Person() {
        return std::move(person);
    }
    ~PersonBuilderBase() {}

    PersonAddressBuilder lives() const;

    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase
{
public:
    Person p;
    PersonBuilder() : PersonBuilderBase{p} {}
    ~PersonBuilder() {}
};

class PersonAddressBuilder : public PersonBuilderBase
{
    typedef PersonAddressBuilder self;

public:
    explicit PersonAddressBuilder(Person& p) : PersonBuilderBase(p) { }
    ~PersonAddressBuilder() {}

    self& at(std::string streetAddress) {
        person.address = streetAddress;
        return(*this);
    }

    self& withPostcode(std::string postCode) {
        person.postCode = postCode;
        return(*this);
    }

    self& in(std::string city) {
        person.city = city;
        return(*this);
    }
    
};

class PersonJobBuilder : public PersonBuilderBase
{
    typedef PersonJobBuilder self;

public:
    explicit PersonJobBuilder(Person& p) : PersonBuilderBase(p) { }
    ~PersonJobBuilder() {}

    self& company(std::string name) {
        person.companyName = name;
        return(*this);
    }

    self& position(std::string pos) {
        person.position = pos;
        return(*this);
    }

    self& in(int income) {
        person.income = income;
        return(*this);
    }
};

void simpleBuilder();

void communicatingIntent();

void groovyExample();

void compositeExample();

#endif