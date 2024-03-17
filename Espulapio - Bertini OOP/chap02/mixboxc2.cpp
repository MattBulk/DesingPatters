// chapters 2.3 through 2.5
#include "mixboxc2.h"

#include <istream>
#include <cmath>

void references() {
    int x = 0;
    int &y = x;     // references
    y = 1;          // x == 1
    // int& z;      // compile error
    std::cout << "x: " << x << " and y: " << y << std::endl;

    int a = 10;
    int &rA = a;    // reference &ra prints the address *&rA prints the value of a   
    int *pA = &a;   // pointer operator

    std::cout << "a: " << a << " " << *&rA << " " << *pA << std::endl;
}

void enums() {
    enum Color {red, green, blue};
    enum Color color = red;
    // color++;      // compile error
}

class Foo {
public:    
    Foo() {
        std::cout << "I am an enemy";
    }
};

void pointers() {
    Foo *pFoo;
    // pFoo = malloc(sizeof(Foo));      // ok in C, error in C++
    pFoo = (Foo*)malloc(sizeof(Foo));   // ok in C, ok in C++

    int i = 3;
    void *ptr = &i;
    int *ptrInt;
    // ptrInt = ptr;        // ok in C, error in C++
    ptrInt = (int*)ptr;     // ok in C, ok in C++
    print("pointer ", *ptrInt);

}

// 2.8 Constructor and destructor

class X {
public:
    X() {}
    X(int ni) : i(ni) {}

public:
int i = 4;       // initialization
float j {3.14};  // uniform initialization

};

void xExample() {

    X a(10), b;
    print("a:i ", a.i);
    print("a:j ", a.j);
    print("b:i ", b.i);
    print("b:j ", b.j);
}

class A {
public:
    A() {}; // implicit casting
};

class B {
public:
    explicit B(int x = 0, bool b = true) {} // explicit casting
};

class C {
public:
    explicit C(B ab=B()) {} // explicit casting
};

void doSomething(B objB) {

}

void doSomethingC(C objC) {

}

void explicitExample() {
    B objB1; // parameters x an b are default
    doSomething(objB1); // ok

    B objB2(28);
    doSomething(objB2); // ok
    // doSomething(28);    // bad, it needs casting
    doSomething(B(28)); // ok

    C objC1;
    doSomethingC(objC1);
    // doSomethingC(objB2); // bad, it need casting
    doSomethingC(C(objB2));

    // doSomething("foo"); // bad, no conversion exists
}

class SalesData {
public:
    // no constructor delegation list of initialization
    SalesData(std::string s, unsigned cnt, double price) : items(s), units_sold(cnt), revenue(cnt*price) {}

    // constructor delegation
    SalesData() : SalesData("", 0, 0) {}
    
    SalesData(std::string s) : SalesData(s, 0, 0) {}

    SalesData(std::istream &is) : SalesData() {}
private:
    std::string items;
    unsigned units_sold;
    double revenue;
};

// 2.10 static members

class Point {
public:
    Point() : x(0), y(0) {
        n++;
    }
    ~Point() {
        n--;
    }
    static int n;

    static float distance(Point a, Point b) {
        std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
    }

private:
    int x, y;
};

int Point::n = 0; // define the static var in the same namespace ... useless example

void staticExample() {

    std::cout << "n: " << Point::n << std::endl;

    float distance = Point::distance(Point(), Point());
    print("distance ", distance);

    Point a;
    print("a: ", a.n);
}

// 2.11 Friend and incapsulation
class PointFriend {
public:
    PointFriend() : x(0), y(0) { }
    ~PointFriend() { }

    friend bool operator==(PointFriend a, PointFriend b);

    static float distance(PointFriend a, PointFriend b) {
        std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
    }

private:
    int x, y;
};

bool operator==(PointFriend a, PointFriend b) {
    if((a.x != b.x) || (a.y != b.y))
        return(false);
    else
        return(true);
}

// 2.12 nested classes
class Algorithm {
public:
    class AlgorithmResults {
        friend class Algorithm;
    public:
        void readAlgoResult() {}
    private:
        void writeAlgoResult() {}
    };

    void calculate(AlgorithmResults &results) {
        // do the math
        results.writeAlgoResult(); // access a private member as friend
    }
};

void friendExample() {

    PointFriend p, q;
    if(p == q) {
        print("friend ", "true");
    }

    Algorithm a;
    Algorithm::AlgorithmResults ar;
    a.calculate(ar);
}

// 2.13 const qualifier
class TextBuffer {
public:
    TextBuffer(const std::string &str) : text(str) { }

    const char& operator[](size_t pos) const {
        return text[pos];
    }

    char& operator[](size_t pos) {
        return text[pos];
    }
private:
    std::string text;

};

void constExample() {
    char greeting[] = "Hello World!";

    char *p0 = greeting;                // no const

    const char *p1 = greeting;          // pointer to a const var !!!

    char* const p2 = greeting;          // const pointer, you cannot reassing it to another var.

    const char* const p3 = greeting ;   // both const, pointer and var 

    TextBuffer buf("Hello");

    print("text buffer position ", buf[1]);

    // mutable lets modify a const member in a const method.
    const int i = 10;
    int *i2 = const_cast<int*>(&i);
    *i2 = 20;
    print("const_cast ", *i2);
}

// 2.14 deep and shallow copy

class Potion {
public:
    Potion(const std::string &name, int power, int cost) : name(name), power(power), cost(cost) {}

public:
    std::string name;
    int power;
    int cost;
};

class GameCharacter {
public:
    GameCharacter(const std::string &name, Potion *inventory) : name(name), inventory(inventory) {}

    GameCharacter(const GameCharacter &other) {
        HP = other.HP;
        posX = other.posX;
        posY = other.posY;

        if(other.inventory != nullptr) 
            inventory = new Potion(*other.inventory);
        else
            inventory = nullptr;
    }

    GameCharacter& operator=(const GameCharacter &other) {

        if(this == &other)
            return(*this);
        if(inventory != nullptr)
            delete inventory;
        
        HP = other.HP;
        posX = other.posX;
        posY = other.posY;

        if(other.inventory != nullptr) 
            inventory = new Potion(*other.inventory);
        else
            inventory = nullptr;
        
        return(*this);

    }

    ~GameCharacter() {
        delete inventory;
    }
public:
    std::string name;
    int posX, posY;
    int HP;
    Potion *inventory;
};

void deepAndShallowExample() {

    Potion *pot = new Potion("healer", 10, 40);

    GameCharacter hero("Tom", pot);

    GameCharacter heroCopy(hero);

    Potion *pot2 = new Potion("damage", 20, 30);
    GameCharacter heroCopy2("Mike", pot2);
    heroCopy2 = heroCopy;

    print("invetory name: ", heroCopy.inventory->name);
    print("invetory name: ", heroCopy2.inventory->name);
}

class FooNoCopy {
public:
    // disable assigment operator
    FooNoCopy operator=(const FooNoCopy&) = delete;
    // disable copy constructor
    FooNoCopy(const FooNoCopy&) = delete;
};


