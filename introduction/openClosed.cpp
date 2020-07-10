#include "openClosed.h"

#include <vector>

enum class Color { Red, Green, Blue };

enum class Size { Small, Medium, Large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

typedef std::vector<Product*> Items;

template <typename T>
class Specification {

public:
    virtual bool isSatisfied(T* item) = 0;
};

template <typename T>
class Filter {
public:
    virtual std::vector<T*>  filter(std::vector<T*> items, Specification<T>& spec) = 0;
};

class ColorSpecification : public Specification<Product>
{
public:
    ColorSpecification(const Color color) : color{color} {}  // color = color;
    ~ColorSpecification() { }

    bool isSatisfied(Product* item) override {
        return item->color == color;
    }
public:
    Color color;

};

class BetterFilter : public Filter<Product>
{

public:
    BetterFilter(/* args */) {}
    ~BetterFilter() {}

    Items filter(Items items, Specification<Product>& spec) override {
        Items result;
        for (auto &&p : items)
        {
            if(spec.isSatisfied(p))
                result.push_back(p);
        }
        return result;
    }
};



void openClosedExample() {
    Product apple{ "Apple", Color::Green, Size::Small };
    Product tree{ "Tree", Color::Green, Size::Large };
    Product house{ "House", Color::Blue, Size::Large };

    Items all{&apple, &tree, &house};

    BetterFilter bf;

    ColorSpecification green(Color::Green);

    auto greenThings = bf.filter(all, green);

    for (auto &&i : greenThings)
    {
        print(i->name, " is green.");
    }
    

}
