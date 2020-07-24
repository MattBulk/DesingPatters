#include "proxy.h"
#include <memory>

struct CreatureProxy {
    Property<int> strength{10};
    Property<double> agility{5.5};
};

void smartPointerExample() {
    BankAccountProxy *ba = new BankAccountProxy;
    ba->deposit(123);

    auto ba2 = std::make_shared<BankAccountProxy>();
    ba2->deposit(123);

    CreatureProxy creature;
    creature.agility = 10.5;
    auto x = creature.strength;

    print("Creature Agility ", creature.agility);
    print("Creature strength ", x);
}

class Bitmap : Image
{
private:
    /* data */
public:
    Bitmap(const std::string &filename) {
        print("Loading image from ", filename);
    }
    ~Bitmap() {}

    void draw() override {
        print("Drawing image", "");
    }
};

class LazyBitmap : Image
{
private:
    /* data */
    Bitmap *bmp{nullptr};
    std::string filename;

public:
    LazyBitmap(const std::string &filename) :filename(filename) {}
    ~LazyBitmap() {
        delete bmp;
    }
    void draw() {
        if(!bmp)
            bmp = new Bitmap(filename);
        bmp->draw();
    }
};

void lazyExample() {
    Bitmap img{"guyver.gif"};

    LazyBitmap img2{"hero.bmp"};
    print("About to draw", "...");
    img2.draw();
    print("Done drawing the image", "...");
}