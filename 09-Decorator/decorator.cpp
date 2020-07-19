#include "decorator.h"

class CircleDeco : public ShapeDeco
{
private:
    float radius;
public:
    CircleDeco(const float &radius) : radius(radius) {}
    ~CircleDeco() {}

    void resize(float factor) {
        radius*= factor;
    }

    std::string str() const override {
        std::ostringstream oss;
        oss << "A Circle of radius " << radius;
        return oss.str();
    }
};

class ColoredShape : public ShapeDeco
{
public:
    ShapeDeco& shape;
    std::string color;
public:
    ColoredShape(ShapeDeco& shape, const std::string &color) : shape{shape}, color{color} { }

    ~ColoredShape() {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

class TransparentShape : public ShapeDeco
{
public:
    ShapeDeco& shape;
    uint8_t transparency;
public:
    TransparentShape(ShapeDeco& shape, uint8_t transparency) : shape{shape}, transparency{transparency} { }

    ~TransparentShape() {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has " << static_cast<float>(transparency) / 255.f * 100.f<< transparency;
        return oss.str();
    }
};

void decoFirstExample() {
    CircleDeco circle(0.5f);
    ColoredShape redCircle{circle, "red"};
    std::cout << redCircle.str() << std::endl;
    TransparentShape transCircle(circle, 50);
    std::cout << transCircle.str() << std::endl;

    CircleDeco circle2(10.f);
    ColoredShape green(circle2, "green");
    TransparentShape myCircle {
        green,
        64
    };

    std::cout << myCircle.str() << std::endl;
}