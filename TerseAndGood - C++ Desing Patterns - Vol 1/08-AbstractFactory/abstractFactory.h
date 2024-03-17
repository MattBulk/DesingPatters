#include <string>
#include <memory>

class Product {
public:
  virtual std::string name() const = 0;
};

class Product1 : public Product {
public:
  std::string name() const override { return("Product1"); };
};

class Product2 :public Product {
public:
  std::string name() const override { return("Product2"); };
};

class AbstractFactory {
public:
  virtual std::shared_ptr<Product> create() const = 0;
};

class Factory1 : public AbstractFactory {
public:
  std::shared_ptr<Product> create() const override {
    return(std::make_shared<Product1>());
  }
};

class Factory2 : public AbstractFactory {
public:
  std::shared_ptr<Product> create() const override {
    return(std::make_shared<Product2>());
  }
};
