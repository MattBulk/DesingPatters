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

// forward declaration
template<typename T>
class AndSpecification;

template <typename T>
class Specification 
{
public:
    virtual bool isSatisfied(T* item) = 0;

    AndSpecification<T> operator &&(Specification&& other) {
        return AndSpecification<T>(*this, other);   
    }
};

template <typename T>
class Filter {
public:
    virtual std::vector<T*>  filter(std::vector<T*> items, Specification<T>& spec) = 0;
};

class ColorSpecification : public Specification<Product>
{
private:
    Color color;
public:
    ColorSpecification(const Color color) : color{color} {}  // color = color;
    ~ColorSpecification() { }

    bool isSatisfied(Product* item) override {
        return item->color == color;
    }
};

class SizeSpecification : public Specification<Product>
{
private:
    Size size;
public:
    SizeSpecification(const Size sz) : size{sz} {}  // color = color;
    ~SizeSpecification() { }

    bool isSatisfied(Product* item) override {
        return item->size == size;
    }
};

template <typename T>
class AndSpecification : public Specification<T>
{
private:
    Specification<T>& first; 
    Specification<T>& second;
public:
    AndSpecification(Specification<T>& first, Specification<T> &second) : first(first), second(second) { }

    bool isSatisfied(T* item) override {
        return first.isSatisfied(item) && second.isSatisfied(item);
    }
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

// example

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
    
    auto greenAndBig = ColorSpecification(Color::Green) && SizeSpecification(Size::Large);

    auto bigGreenThings = bf.filter(all, greenAndBig);
    for (auto &&i : bigGreenThings)
    {
        print(i->name, " is large and green.");
    }
}
