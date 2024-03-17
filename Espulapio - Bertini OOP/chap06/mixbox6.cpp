#include "mixbox6.h"
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>

// 6.2 Template
template<typename T>
T getMax(T a, T b) {
    return(a>b ? a : b);
}

template<typename T>
inline std::string stringify(const T& x) {
    std::ostringstream out;
    out << x;
    return out.str();
}

template<>
inline std::string stringify<bool>(const bool& x) {
    std::ostringstream out;
    out << std::boolalpha << x;
    return out.str();
}

template <typename T>
void foo() {
    typename T::iterator *iter; // typename is needed because C++ not treat qualified names as types. 
}

void templateExample() {
    int j = 4, i = 3;
    int result = getMax<int>(i, j);
    print("specialize: ", result);

    int k = 5;
    result = getMax(j, k);
    print("not specialize: ", result);

    long l = 6;
    // result = getMax(k, l); not working int and long type cannot specified
    print("stringify int ", stringify(3));

    bool b = true;
    print("stringify bool ", stringify(b));
}

template<typename T>
class MyPair {
public:
    MyPair(T first, T second) {
        values[0] = first;
        values[1] = second;
    }

    T getFirst() const {
        return values[0];
    }

    T getSecond() const {
        return values[1];
    }

    T getMax() const {
        T retval = values[0] > values[1] ? values[0] : values[1];
        return retval;
    }

private:
    T values[2];
};

class Vehicle {
public:
    Vehicle(int w=4) : wheels(w) {}

    bool operator< (const Vehicle& rhs) const { return wheels < rhs.wheels; }
    bool operator> (const Vehicle& rhs)const { return rhs.wheels < wheels; }
    bool operator<=(const Vehicle& rhs){ return !(wheels > rhs.wheels); }
    bool operator>=(const Vehicle& rhs){ return !(wheels < rhs.wheels); }

private:
    int wheels;
};

void myPairExample() {

    MyPair<int> myPair(2, 3);
    int result = myPair.getMax();
    print("MyPair getMax: ", result);

    Vehicle v1;
    Vehicle v2(12);
    MyPair<Vehicle> vehicles(v1, v2);

    Vehicle v3 = vehicles.getFirst();
    v3 = vehicles.getMax(); // need to define operators
}

// Functor Function Object
class IntGreater {
public:
    bool operator()(int x, int y) const {
        return x>y;
    }
};

template<typename T>
class Summatory {
public:
    Summatory(T s=0) : sum(s) {}
    void operator()(T arg) {
        sum += arg;
    }
    T getSum() const {
        return sum;
    }
private:
    T sum;
};

#include <functional>
void functorExample() {
    IntGreater intGreater;

    int i = 3;
    int j = 4;
    bool result = intGreater(i, j);

    std::vector<int> vec = {5, 10, 6, 128};
    std::sort(std::begin(vec), std::end(vec), intGreater);
    for (size_t i = 0; i < vec.size(); i++)
        print("i: ",  vec.at(i));

    std::list<int> li  = {10, 5, 20};
    Summatory<int> s;
    for_each(li.begin(), li.end(), std::ref(s)); // I know it !!! need ref :)
    print("Sum: ", s.getSum());
    
}

void lambdaExample() {
    int eventCount = 0;
    std::vector<int> v = {5, 10, 6, 128, 7, 9, 2, 3};
    for_each(v.begin(), v.end(), [&eventCount](int n) {
        if(n % 2 == 0)
            print(n, " is an even number");
    });
}