#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

enum class ProductType { Shoes, Eyeglasses, Smartphone };

class Product {
public:
  virtual std::string name() const = 0;
  virtual double price() const = 0;
};

class Product1 : public Product {
public:
  std::string name() const override {
    return("Shoes");
  }

  double price() const override {
    return(72.90);
  }
};

class Product2 : public Product {
public:
  std::string name() const override {
    return("Eyeglasses");
  }

  double price() const override {
    return(320.00);
  }
};

class Factory {
private:
  Factory() { }

public:
  static std::shared_ptr<Product> create(const ProductType &type) {
    switch (type) {
      case ProductType::Shoes:
        return(std::make_shared<Product1>());
        break;
      case ProductType::Eyeglasses:
        return(std::make_shared<Product2>());
        break;
      default:
        throw std::runtime_error("no item can be found");
        break;
    }
  }
};
