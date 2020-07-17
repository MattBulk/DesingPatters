#include "bridge.h"

// the pimpl idiom

class PersonBridge
{
public:
    std::string name;
    void greet()
    {
        impl->greet(this);
    }

public:
    PersonBridge() : impl(new PersonImpl) { }
    ~PersonBridge()
    {
        delete impl;
    }
    class PersonImpl
    {
    private:
        /* data */
    public:
        PersonImpl() {}
        ~PersonImpl() {}

        void greet(PersonBridge *p)
        {
            print("Hello ", p->name);
        }
    };
    PersonImpl *impl;
};

void pimplExample()
{
    PersonBridge p;
    p.name = "Matt";

    p.greet();
}


// Bridge Example
class ShapeBridge
{
protected:
    Renderer& renderer;
    
    ShapeBridge(Renderer& renderer) : renderer(renderer) {}
public:
    ~ShapeBridge() {}

    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

class CircleBridge : public ShapeBridge
{
private:
    float x,  y, radius;
public:
    CircleBridge(Renderer& renderer, float x, float y, float radius) : ShapeBridge{renderer}, x{x}, y{y}, radius{radius} {}

    void draw() override
    {
        renderer.renderCircle(x, y, radius);
    }
    void resize(float factor) override
    {
        radius *= factor;
    }

    ~CircleBridge() {}
};

void bridgeExample() {
    RasterRenderer rr;
    CircleBridge rasterCircle{rr, 5, 5, 10};
    rasterCircle.draw();
    rasterCircle.resize(2);
    rasterCircle.draw();

}
