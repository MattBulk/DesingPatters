#include "mixboxc3.h"

#include "../commons.h"

// 3.1.1 final
class CarFinale final {
public:
    std::string name;
};

// this will throw an error. final cannot let extend CarFinale class
// class CarExtends : CarFinale { };

// 3.1.2 access level

class B {
public:
    void pub();
protected:
    void prot();
private:
    void priv();
};

class pubD : public B {};       //  pubD inherits public and protected methods, with the same level of access
class protD : protected B {};   //  pubD inherits public and protected methods, the access is protected 
class privD : private B {};     //  pubD inherits public and protected methods, the access is private, so no access is granted

void finalClassExample() {

}

// 3.2 Liskov Substition Principle

class Person {
public:
    void setName(const std::string &name) {
        this->name = name;
    }

    std::string getName() const {
        return(name);
    }

    void setPosition(int x, int y) {
        this->xPos = x;
        this->yPos = y;
    }

    int getXPos() const { return(xPos); }

    int getYPos() const { return(yPos); }
private:
    int xPos, yPos;
    std::string name;
};

class Student : public Person {
public:
    void setId(int id) {
        this->id = id;
    }
private:
    int id;
};

class StudentP : private Person {
public:
    StudentP() {
        this->setName("Joe");
        this->setPosition(15, 20);
    }
    void setId(int id) {
        this->id = id;
    }
private:
    int id;
};

void move(Person &p) {
    p.setPosition(p.getXPos()+10, p.getYPos()+10);
}

void study(Student &s) {
    s.setPosition(s.getXPos()+10, s.getYPos()+10);   
}

void substitutionExample() {
    Person p;
    p.setName("Tom");
    p.setPosition(10, 20);
    move(p);
    // study(p);    cannon pass Person as Student

    Student s;
    s.setName("Mark");
    s.setPosition(30, 20);
    s.setId(2246);
    move(s);
    study(s);

    StudentP sp;
    // error cannot set property outside the class
    // sp.setName("Lisa");      
    // sp.setPosition(10, 5);
    sp.setId(4554);

    print(p.getName(), " x and y pos:");
    std::cout << p.getXPos() << " " << p.getYPos() << std::endl;

    print(s.getName()," x and y pos:");
    std::cout << s.getXPos() << " " << s.getYPos() << std::endl;

}

// 3.3.2 Binding

class Base {
public:
    void foo() {
        std::cout << "Base::foo" << std::endl;
    }
    int foo2() {
        std::cout << "Base::foo2" << std::endl;
        return -1;
    }
};

class Derived : public Base {
public:
    void foo() {
        Base::foo();
        std::cout << "Derived::foo" << std::endl;
    }
    int foo2() {
        std::cout << "Derived::foo2" << std::endl;
        return -1;
    }
};

void bindingExample() {
Base *pBase;
Base aB;
Derived aD;
Base &rB = aD;

aB.foo2();      // Base::foo2
aD.foo();       // Derived::foo
rB.foo();       // Base::foo

pBase = &aD;    // Base pointer to derived class
pBase->foo();   // Base::foo with static binding

static_cast<Derived *>(pBase)->foo2();  // after casting, Derived::foo2
static_cast<Derived &>(rB).foo2();      // after casting, Derived::foo2
}

// 3.3.2 Virtual methods are used to activate late binding and remove the due static binding to the class

class BaseV {
public:
    BaseV() {}
    virtual ~BaseV() {}

    void foo() {
        std::cout << "BaseV::foo" << std::endl;
    }
    virtual int bar() {
        std::cout << "BaseV::bar" << std::endl;
        return -1;
    }
};

class DerivedV : public BaseV {
public:
    DerivedV() {}
    virtual ~DerivedV() {}
    void foo() {
        std::cout << "\t";
        BaseV::foo();
        std::cout << "DerivedV::foo" << std::endl;
    }
    virtual int bar() {
        std::cout << "DerivedV::foo2" << std::endl;
        return 1;
    }
};

void virtualExample() {
BaseV *pBase;
BaseV aB;
DerivedV aD;
BaseV &rB = aD;

aB.bar();       // BaseV::bar
aD.foo();       // DerivedV::foo
rB.foo();       // BaseV::foo

pBase = &aD;    // pointer of type Base 
pBase->foo();   // Base::foo due to static binding

pBase->bar();   // late binding: no cast needed
rB.bar();       // late binding: no cast needed

}

class B1 {
public:
    virtual void foo();
    virtual ~B1();          // always declare destructor as virtual in case of polymorphic class
};

class D1 : public B1 {
public:
    void foo() override;
    ~D1() override;         // if ~B1 wasn't virtual an error is thrown
};

// never use a not polymorphic class as base class, for instance std::string

// 3.4 method deletion

class A2 {
public:
    virtual void foo() {}
    void bar() {}
    void foobar() { std::cout << "Class A2\n"; }
};

class B2 : public A2 {
public:
    virtual void foo() {}
    void bar() {}
    void foobar() = delete;
};

class C2 : public B2 {
public:
    C2() {}
    virtual void foo() {}
    void bar() {}
    void foobar() { 
        A2::foobar();
        std::cout << "Class C2\n";
    };
};

void deleteExample() {

    B2 b;
    b.foo();
    b.bar();
    // b.foobar();     // delete compile error

    A2 *pA;
    pA = &b;
    pA->foo();
    pA->bar();
    pA->foobar();   // foobar cannot be virual: A2::foobar() is called

    C2 c;
    c.foobar();     // moethod is activated again
}

// 3.5 Covariant return type

class A3 {};
class B3 : public A3 {
public:
    B3() { std::cout << "Class B3\n"; }
};

class C3 : public B3 {
public:
    C3() { std::cout << "Class C3\n"; }    
};

class X {
public:
    virtual B3 *m1() {
        return new B3();
    }
};

class Y : public X {
public:
    C3 *m1() override {
        return new C3();
    }
};

class Base2 {
public:
    virtual Base2* clone() const {
        return new Base2(*this);
    }
    virtual ~Base2() {}

    int sport = 9;    
};

class Derived2 : public Base2 {
public:
    virtual Derived2* clone() const {
        return new Derived2(*this);
    }
    virtual ~Derived2() {}

    std::string name = "derivata";
};


void covariantExample() {
    X x;
    Y y;
    A3 *aB1 = x.m1();
    B3 *aB2 = y.m1(); // calls b3.m1() and then Y.m1() kind of strange behaviour

    Base2 *b1 = new Base2;
    Base2 *b2 = b1->clone();

    print("Base2 cloned ", b2->sport);

    Derived2 *d1 = new Derived2;
    Derived2 *d2 = d1->clone();

    print("Derived2 cloned ", d2->name);
    print("Derived2 cloned ", d2->sport);
}

// 3.6 name hiding

class BaseH {
public:
    void f(double x) {
        std::cout << "Base::f(double x) - " << x << std::endl;
    }
};

class DerivedH : public BaseH {
public:
    void f(char c) {
        std::cout << "Base::f(double x) - " << c << std::endl;
    }
};

class DerivedH1 : public BaseH {
public:
    using BaseH::f;     // makes f(double x) available

    void f(char c);
};

class DerivedH2 : public BaseH {
public:
    void f(double x) { BaseH::f(x); }     // makes f(double x) available

    void f(char c);
};

void hidingExample() {
    DerivedH *d = new DerivedH;
    BaseH *b = d;

    b->f(65.3);     // ok, calling double on BaseH.
    d->f(65.3);     // no, the name hiding will use just f(char x) because of name hiding, return 'A' 

    delete d;
    b = nullptr;

    DerivedH1 *c = new DerivedH1;
    c->f(22.5);
    c->f(44.7);

    DerivedH2 *e = new DerivedH2;
    e->f(22.5);
    e->f(44.7);

}

// 3.7 Abstact class

class Vehicle {
public:
    virtual int getNumWheels() const = 0;
};

class MotorCycle : public Vehicle {
public:
    virtual int getNumWheels() const {
        return 2;
    }
};

class Car : public Vehicle {
public:
    virtual int getNumWheels() const {
        return 4;
    }
};

class Truck : public Vehicle {
public:
    Truck(int w = 10) : wheels(w) {}
    
    virtual int getNumWheels() const {
        return wheels;
    }
private:
    int wheels;
};

class AbstractBase {
public:
    virtual ~AbstractBase() = 0;
    virtual void foo();
    virtual int bar();
};

void abstractExample() {
    Vehicle *p = new Car();
    print("Car ", p->getNumWheels());

    delete p;
}

// 3.8 Type conversion

class MyBaseConv {

};

class MyClassConv : public MyBaseConv {

};

class MyOtherStuff {

};

void conversionExample() {

    MyBaseConv *pBase = new MyClassConv;
    MyClassConv *pMyClass;

    pMyClass = static_cast<MyClassConv*>(pBase);
    pMyClass = (MyClassConv*)(pBase);

    // MyOtherStuff *pOther = static_cast<MyOtherStuff*>(pMyClass); // won't work
    MyOtherStuff *pOther = (MyOtherStuff*)(pBase);    // C conversion works, take the bit, but can be a problem at run-time

    // in case of conversion of different type just use reinterpreter_cast
}

// 3.9 Run-time identification RTTI

class CastB {
public:
virtual void f() {}
};

class CastD1 : public CastB {
public:
    virtual void f() {}
    void D1specific() {
        print("casting", "D1 is working");
    }
};

class CastD2 : public CastB {
public:
    virtual void f() {}
    void D2specific() {
        print("casting", "D2 is working");
    }
};

#include <typeinfo>

void dynamicCastExample() {
    CastB *pB = new CastD1;
    CastD1 *pD = dynamic_cast<CastD1*>(pB);
    if(pD != 0)
        pD->D1specific();

    
    pB = new CastD2;
    pD = dynamic_cast<CastD1*>(pB);
    if(pD != 0)
        pD->D1specific();
    
    CastD1 aD1;
    CastB &rB = aD1;

    try {
        CastD2 &rD2 = dynamic_cast<CastD2&>(rB);
        rD2.D2specific();
    } catch (std::bad_cast& e) {
        std::cerr << "cannot convert to D2& " << e.what() << std::endl;
    }

    // typeId
    int x = 10;
    if(typeid(x) == typeid(int))
        print("typeid ", "int");

}