#ifndef DECORATOR_H
#define DECORATOR_H

#include "../commons.h"
#include <sstream>
#include <type_traits>
#include <utility>
#include <functional>

class ShapeDeco
{
private:
    /* data */
public:
    ShapeDeco(/* args */) {}
    ~ShapeDeco() {}

    virtual std::string str() const = 0;
};
class SquareDeco : public ShapeDeco
{
private:
    float side;
public:
    SquareDeco(const float &side) : side(side) {}
    ~SquareDeco() {}

    void resize(float factor) {
        side*= factor;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A Square of side " << side;
        return oss.str();
    }
};

template <typename T>
class ColoredShapeStatic : public T
{
private:    
    static_assert(std::is_base_of<ShapeDeco, T>::value, "Template argument must be a ShapeDeco");

public:
    std::string color;

public:
    template<typename ...Args>
    ColoredShapeStatic(const std::string &color, Args ...args) : color{color}, T(std::forward<Args>(args)...) { }

    ~ColoredShapeStatic() {}

    std::string str() const override {
        std::ostringstream oss;
        oss << " has the color " << color;
        return oss.str();
    }
};

template <typename T>
class TransparentShapeStatic : public T
{
private:
    static_assert(std::is_base_of<ShapeDeco, T>::value, "Template argument must be a ShapeDeco");

public:
    uint8_t transparency;

public:
    template<typename...Args>
    TransparentShapeStatic(uint8_t &transparency, Args ...args) : T(std::forward<Args>(args)...), transparency{transparency} { }

    ~TransparentShapeStatic() {}

    std::string str() const override {
        std::ostringstream oss;
        oss  << " has " << static_cast<float>(transparency) / 255.f * 100.f<< transparency;
        return oss.str();
    }
};


// Functional Decorator
class Logger
{
public:
    std::function<void()> func;
    std::string name;

    Logger(const std::function<void()>& func, const std::string &name) : func{func}, name{name} {}
    ~Logger() {}

    void operator()() const {
        print("Entering ", name);
        func();
        print("Exiting ", name);
    }
};

template <typename T>
class Logger2
{
private:
    T func;
    std::string name;

public:
    Logger2(const T &func, const std::string &name) : func{func}, name{name} {}
    ~Logger2() {}

    void operator()() const {
        print("Entering Logger2 ", name);
        func();
        print("Exiting Logger2 ", name);
    }

};

void decoFirstExample();

void staticDecoExample();

void functionalDecoExample();

#endif