#include "mixbox7.h"

#include <cstdio>
#include <exception>
#include <memory>
#include <vector>
#include <algorithm>

// 7.2 RAII example

class FileManager {
public:
    FileManager(const char* filename) : file_handle(std::fopen(filename, "w+")) {
        if(!file_handle) {
            throw std::runtime_error("file open failure");
        }
    }

    ~FileManager() {
        if(std::fclose(file_handle)) {
            // handle error
        }
        // delete file_handle; fclose handles the pointer
        print("FileManager ", "destructor");
    }

    void write(const char* str) {
        if(EOF == std::fputs(str, file_handle)) {
            throw std::runtime_error("file write failure");
        }
    }

    FileManager(const FileManager &) = delete;
    FileManager &operator= (const FileManager &) = delete;
private:
    std::FILE *file_handle;
};

void raiiExample() {
    FileManager logFile("logfile.txt");
    logFile.write("hello logfile!");
}

// 7.3.1 unique_ptr

class MyClass {
public:
    MyClass(const char* s) : s(s) { }
    void methodA() {
        print("Class name", s);
    }
private:
const char* s;
};

void someFunction(MyClass *m) {
    m->methodA();
}

class Steel {
public:
    Steel(int q) : quantity(q) { }
    int get() const { return quantity; }
private:
    int quantity;
};

class Spaceship {
public:
    Spaceship(std::unique_ptr<Steel> steel) {
        total = steel->get() * 2;    
    }
    void prepareEngine() const { print("total ", total ); }

private:
    int total;
};

std::unique_ptr<Spaceship> buildSpaceship() {
    std::unique_ptr<Steel> steel(new Steel(10));
    // move the pointer
    std::unique_ptr<Spaceship> result(new Spaceship(std::move(steel)));
    result->prepareEngine();
    return result;
}

// passing explict pointer
class A {
public:
    A(std::unique_ptr<int> aI) {
        i = std::move(aI);  // receive the pointer
    }
private:
std::unique_ptr<int> i;
};

// nullpointer
std::unique_ptr<MyClass> getData(bool var) {
    
    if(var) {
        std::unique_ptr<MyClass> result(new MyClass("obj 2"));
        return result;
    }
    else {
        // return nullptr;
        return std::unique_ptr<MyClass>{};
    }
}

void uniquePtrExample() {
    std::unique_ptr<MyClass> ptr1(new MyClass("obj1"));
    ptr1->methodA();
    (*ptr1).methodA();

    someFunction(ptr1.get());

    auto mySpaceshit = buildSpaceship(); // implicit std::move

    std::unique_ptr<MyClass> returnData = getData(true);
    if(returnData) {
        //nullControl;
        returnData->methodA();
    }
}

// 7.3.2 Shared ptr
class Song {
public:
    Song(std::string name, std::string t) : artist(name), title(t) {}
    std::string artist, title;
};

void sharedPtrExample() {

    std::shared_ptr<Song> p1 = std::make_shared<Song>("Bob Dylan", "The time...");
    std::shared_ptr<Song> p2 = std::make_shared<Song>("Aretha Franklin", "Bridge over...");
    std::shared_ptr<Song> p3 = std::make_shared<Song>("Francesco Guccini", "Il vecchio...");

    std::vector<std::shared_ptr<Song>> v;

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    std::vector<std::shared_ptr<Song>> v2;

    std::remove_copy_if(v.begin(), v.end(), std::back_inserter(v2), [] (std::shared_ptr<Song> s) {
        return s->artist.compare("Francesco Guccini") == 0;
    });

    for_each(v2.begin(), v2.end(), [](std::shared_ptr<Song> s) {
        print(s->artist, s->title);
    });

    v.pop_back();

    print(p1->artist, p1->title);
    print(p2->artist, p2->title);
    print(p3->artist, p3->title);
}

// 7.3.3 weak ptr

class B;
class A1 {
public:
    A1() {};
    ~A1() {
        print("A1 is destroyed", "");
    }
    std::weak_ptr<B> m_sptrB;    // weak ptr saves loops formation because it doesn't possess, only shared_ptr can use it.
};

class B {
public:
    B() {};
    ~B() {
        print("B is destroyed", "");
    }
    std::weak_ptr<A1> m_sptrA;    // weak ptr saves loops formation because it doesn't possess, only shared_ptr can use it.
};

void weakPtrExample() {

    std::shared_ptr<B> sptrB(new B);
    std::shared_ptr<A1> sptrA(new A1);
    sptrB->m_sptrA = sptrA;
    sptrA->m_sptrB = sptrB;

    std::shared_ptr<int> p1(new int(5));
    std::weak_ptr<int> wp1 = p1;    // p1 possesses the memory
    {
        std::shared_ptr<int> p2 = wp1.lock();   // both p1 than p2
        if(p2) {
            print("p2", " is working");
        } 
    } // p2 destroyed, p1 has the memory

    p1.reset();

    std::shared_ptr<int> p3 = wp1.lock();   // memory was fred, so the pointer is empty
    if(p3)
        print("p3", "something went wrong");
}