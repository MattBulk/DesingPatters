#include "multipleHeritage.h"

// 3.10 Multiple heritage

class Mammal {
public:
    Mammal() {}
    void eat() {
        print("Mammal ", "eats");
    }
};

class Winged {
public:
    Winged() {}
    void eat() {
        print("Winged ", "eats");
    }
};

class Bat : public Mammal, public Winged {  // this is the heritage order Mammal, Winged
public:
    Bat() {} // Mammal invoke upfront of Winged
};

void mammalExample() {
    Bat aBat;
    aBat.Winged::eat();
    // aBAt.eat(); is ambiguos
}

class A {
public:
    void foo() {
        print("A::foo()","");
    }
    virtual void bar() {
        print("A::bar()", "");
    }
};

class B {
public:
    void foo() {
        print("B::foo()","");
    }
    virtual void bar() {
        print("B::bar()", "");
    }
};

class C :public A {
public:
    void foo() {
        print("C::foo()","");
    }
    virtual void bar() {
        print("C::bar()", "");
    }
};

class D : public B, public C {
public:
    void foo() {
        print("D::foo()","");
    }
    virtual void bar() {
        print("D::bar()", "");
    }
};


class D2 : public B, public C {
public:
    void baz() {
        print("D2::baz()","");
    }
};

void diamondExample() {
    D aD;
    aD.foo();
    aD.bar();

    // ambiguous
    // D2 aD2;
    // aD2.foo();
    // aD2.bar();
    
    // ambiguous conversion from derived class D to base A
    A* pA = &aD;
    pA->foo();      // calls A
    pA->bar();      // calls D
}

class Base {
public:
    virtual void foo() {

    }
protected:
    int data;
};

class Der1 : public virtual Base {
public:
    void foo() override {
        print("Der1::foo()","");
    }
};

class Der2 : public virtual Base {
public:
    void foo() override {
        print("Der2::foo()","");
    }
};

class Join : public Der1, public Der2 {
public:
    void method() {
        this->data = 1; // not ambiguous  
    }
    void foo() override {
        print("Join::foo()", "");
        this->Der1::foo();
        this->Der2::foo();
    }

    int getData() {
        return(this->data);
    }
};

void solvingExample() {
    Join j;
    j.method();
    print("data ", j.getData());

    Base *b = &j;
    b->foo();
}


