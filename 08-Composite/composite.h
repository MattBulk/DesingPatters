#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "../commons.h"
#include "someneurons.h"
#include <array>
#include <numeric>
#include <algorithm>
#include <vector>

class GraphicObjectComp
{
private:
    /* data */
public:
    GraphicObjectComp(/* args */) {}
    ~GraphicObjectComp() {}

    virtual void draw() = 0;
};


void creatureExample();

void groupingObjectExample();

void neuralExample();

#endif