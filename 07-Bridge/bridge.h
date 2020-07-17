#ifndef BRIDGE_H
#define BRIDGE_H

#include "../commons.h"

class Renderer
{
private:
    /* data */
public:
    virtual void renderCircle(float x, float y, float radius) = 0;
};

class VectorRenderer : public Renderer
{
private:
    /* data */
public:
    VectorRenderer(/* args */) {}
    ~VectorRenderer() {}

    virtual void renderCircle(float x, float y, float radius) override
    {
        print("Rasterizing cicle of the radius ", radius);
    }

};

class RasterRenderer : public Renderer
{
private:
    /* data */
public:
    RasterRenderer(/* args */) {}
    ~RasterRenderer() {}

    virtual void renderCircle(float x, float y, float radius) override
    {
        print("Rasterizing cicle of the radius ", radius);
    }

};

void pimplExample();

void bridgeExample();

#endif