#include "adapter.h"

class Shape {
public:
    explicit Shape(int ax=0, int ay=0) : x(ax), y(ay) {}
    virtual ~Shape() {}

    virtual void draw() = 0;
    virtual void resize(float newSize) = 0;

    int getX() const {
        return x;
    }

    void setX(int x) {
        Shape::x = x;
    }

    int getY() const {
        return y;
    }

    void setY(int y) {
        Shape::y = y;
    }

protected:
int x, y;
};

class Sprite : public Shape {
public:
    explicit Sprite(std::string fileN, int w=100, int h=200) : width(w), height(h), fileName(fileN) { }

    virtual ~Sprite() { }

    virtual void draw() override {
        std::cout << "drawing sprite" << std::endl;
    }

    virtual void resize(float newSize) override {
        width += newSize;
        height += newSize;
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        Sprite::width = width;
    }

    int getHeigth() const {
        return height;
    }

    void setHeigth(int height) {
        Sprite::height = height;
    }

    const std::string &getFileName() const {
        return fileName;
    }

    void setFileName(const std::string &fileName) {
        Sprite::fileName = fileName;
    }
private:
    int width, height;
    std::string fileName;
};

class Tile : public Shape {
public:
    explicit Tile(std::string fileN, int t=1, int d=50) : type(t), dim(d), fileName(fileN) { }

    virtual ~Tile() { }

    virtual void draw() override {
        std::cout << "drawing tile" << std::endl;
    }

    virtual void resize(float newSize) override {
        dim *= newSize;
    }

    int getType() const {
        return type;
    }

    void setType(int type) {
        Tile::type = type;
    }

    int getDim() const {
        return dim;
    }

    void setDim(int dim) {
        Tile::dim = dim;
    }

    const std::string &getFileName() const {
        return fileName;
    }

    void setFileName(const std::string &fileName) {
        Tile::fileName = fileName;
    }

private:
    int type, dim;
    std::string fileName;
};

class Text {
public:
    explicit Text(std::string t="", int s=8) : text(t), fontSize(s) { }

    virtual ~Text() { }

    virtual void print() {
        std::cout << text << " " << fontSize << std::endl;
    }

    virtual void resize(int newSize) {
        fontSize += newSize;
    }

    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text) {
        Text::text = text;
    }

    int getFontSize() const {
        return fontSize;
    }

    void setFontSize(int fz) {
        Text::fontSize = fz;
    }
private:
    int fontSize;
    std::string text;
};

// Adapter Example inheritance
class TextShapeAdapter : public Shape, private Text {
public:
    explicit TextShapeAdapter(const Text &adaptee) : Text(adaptee.getText(), adaptee.getFontSize()) {}
    TextShapeAdapter(std::string t, int fontSize) : Text(t, fontSize) {}

    virtual ~TextShapeAdapter() {}

    virtual void draw() override {
        Text::print();
    }
    virtual void resize(float newSize) override {
        int textNewSize = static_cast<int>(newSize);
        Text::resize(textNewSize);
    }
};

// composition
class TextShapeAdapter2 : public Shape {
public:
    explicit TextShapeAdapter2(Text *adap) : adaptee(adap) {}
    
    TextShapeAdapter2(std::string t, int fontSize) {
        adaptee = new Text(t, fontSize);
    }

    virtual ~TextShapeAdapter2() {
        delete adaptee;
    }

    virtual void draw() override {
        adaptee->print();
    }
    virtual void resize(float newSize) override {
        int fz = adaptee->getFontSize();
        int textNewSize = static_cast<int>(newSize * fz);
        adaptee->resize(textNewSize);
    }
private:
    Text *adaptee;
};

#include <vector>
#include <memory>

void adapterExample() {
    std::vector<std::unique_ptr<Shape>> drawingElements;

    std::unique_ptr<Shape> hero(new Sprite("hero.png"));
    std::unique_ptr<Shape> monster(new Sprite("monster.png"));
    std::unique_ptr<Shape> floor(new Tile("map_tiles.png", 0));
    std::unique_ptr<Shape> wall(new Tile("map_tiles.png", 2));

    drawingElements.push_back(std::move(hero));
    drawingElements.push_back(std::move(monster));

    drawingElements.push_back(std::move(wall));
    drawingElements.push_back(std::move(floor));

    Text hitPoints("HP: ", 12);
    std::unique_ptr<Shape> textAdapter(new TextShapeAdapter(hitPoints));
    drawingElements.push_back(std::move(textAdapter));

    std::unique_ptr<Shape> textAdapter2(new TextShapeAdapter("Level: ", 14));
    drawingElements.push_back(std::move(textAdapter2));

    Text* bombPoints = new Text("Bombs ", 20);
    std::unique_ptr<Shape> textAdapter3(new TextShapeAdapter2(bombPoints));
    drawingElements.push_back(std::move(textAdapter3));

    for(auto &&value : drawingElements) {
        value->resize(1.2);
        value->draw();
    }

}