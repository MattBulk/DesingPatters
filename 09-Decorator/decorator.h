#ifndef DECORATOR_H
#define DECORATOR_H

#include "../commons.h"
#include <sstream>

class ShapeDeco
{
private:
    /* data */
public:
    ShapeDeco(/* args */) {}
    ~ShapeDeco() {}

    virtual std::string str() const = 0;
};

void decoFirstExample();

#endif