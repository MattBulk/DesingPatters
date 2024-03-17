#include "mixbox8.h"
#include <vector>
#include <functional>

int arr[10];

// 8.2 Auto
auto func(int i) -> int(*)[10] {
    for (int p = 0; p < 10; p++)
    {
        arr[p] = i;
    }
    return(&arr);
}

// int (*func(int i))[10] {
//     int arr[10];
//     for (int p = 0; p < 10; p++)
//     {
//         arr[p] = 0;
//     }
//     return(&arr);    
// }

void autoExample() {
    int i = 10;
    const int c1 = i;
    auto b = c1;
    b++;            // b is not constant anymore
    const auto b2 = c1;

    auto array = func(5);
    print("array ", array[0]);
}

// 8.3 Decltype

auto mul(int x, int y) -> decltype(x*y) {return x*y;}

void decltypeExample() {

    const int ci = 0;
    const int &cj = ci;

    decltype(ci) x = 0;     // x is const int
    decltype(cj) y = x;     // y is const int&

    int *p = new int[5];
    decltype(*p) j = p[0];
    j = 10;

    auto multi = mul(3, 3);
    print("multi ", multi);
}

// 8.4 Move Example
#include <utility>

void f(int &x) {
    print("lvalue reference overload f", x);
}

void f(const int &x) {
    print("lvalue reference to const overload f", x);
}

void f(int &&x) {
    print("rvalue reference overload f", x);
}

class MyBuffer {
public:
    MyBuffer(int sz=512) {
        this->size = sz;
        this->buf = new char[sz];
    }

    MyBuffer(const MyBuffer &orig) {
        this->size = orig.size;
        buf = orig.buf;
    }

    MyBuffer operator+(const MyBuffer &right) {
        
        return(*this);
    }

private:
    size_t size;
    char* buf;
};

class MemoryBuffer {
public:
    explicit MemoryBuffer(int sz=512) : size(sz), buf(new char [size]) {}
    ~MemoryBuffer() {
        delete[] buf;
    }

    MemoryBuffer(MemoryBuffer &&other) noexcept : size(0), buf(nullptr) {
        // steal resources;
        size = other.size;
        buf = other.buf;
        // reset other
        other.size = 0;
        other.buf = nullptr;
    }

    MemoryBuffer& operator=(MemoryBuffer &&other) noexcept {
        if(this != &other) {
          delete[] buf;
          size = other.size;
          buf = other.buf;
          // reset other
          other.size = 0;
          other.buf = nullptr;
        }
        return *this;
    }

    int getSize() {
        return(size);
    }
private:
    size_t size;
    char* buf;
};

void moveExample() {
    int i = 1;
    const int ci = 2;
    f(i);             // call f(int &x);
    f(ci);            // call f(const int&);
    f(3);             // chiama f(int &&); it would call f(const int &x) if f(int &&) was not declared
    f(std::move(i));  // call f(int &&x) thanks to move

    MyBuffer x, y;
    MyBuffer a(x);    // rvalue !!! copy
    MyBuffer b(x+y);  // rvalue !!! copy

    MemoryBuffer x1(100), y1(50);

    MemoryBuffer c(std::move(x1));

    print("c size ", c.getSize());
    print("x1 ", x1.getSize());

    std::vector<MemoryBuffer> v;
    v.push_back(MemoryBuffer(100));
    v.push_back(MemoryBuffer(200));

}

// 8.5 Lambda
void lambda2Example() {
    //  [&]() catches variables by reference
    //  [=]() catches variables passed by values
    //  [&, i, j] all variables by ref, i and y by values
    auto func_mult = [](int a, int b) -> int { return(a * b); };
    print("lambda ", func_mult(2, 3));

    int i = 1;
    [&i]() { i = 1; };        // ok, i is captured by reference
    // [i]() { i = 1}         // error, i is captured by value and not modificable
    [i]() mutable { i = 1; }; // this will work
}

// 8.5.1 std::function
#include <functional>

class SimpleCallback {
public:
    SimpleCallback(std::function<void()> f) : callback(f) {}

    SimpleCallback(std::function<void(int a, int b)> f1) : callback2(f1) {}
    
    void execute() {
      if(callback != nullptr)
          callback();
    }
    void execute2() {
      if(callback2 != nullptr)
          callback2(5, 5);
    }
private:
    std::function<void()> callback;

    std::function<void(int a, int b)> callback2;
};

void func2() {
    print("i am a function ", 10);
}


auto sum = [](int a, int b) -> void {
                                      a += b;
                                      print("sum a + b ", a);
                                    };

std::function<void(int a, int b)> sub = [](int a, int b) {
                                                      a -= b;
                                                      print("sum a - b ", a);
                                                     };
void functionExample() {
  SimpleCallback cb1(func2);
  cb1.execute();

  SimpleCallback cb2(sum);
  cb2.execute2();

  SimpleCallback cb3(sub);
  cb3.execute2();
}

// 8.6 Tuple

#include <tuple>

std::tuple<int, float, char> foo(int i, float f) {
  int result1 = 42 * i;
  float result2 = 3.13 * f;
  char result3 = 'a';
  return std::make_tuple(result1, result2, result3);
}

void tupleExample() {
  int a;
  float b;
  char c;

  std::tie(a, b, c) = foo(2, 3);

  print("a", a);
  print("b", b);
  print("c", c);

  auto results = foo(2, 3);

  print("a", std::get<0>(results));
  print("b", std::get<1>(results));
  print("c", std::get<2>(results));
}