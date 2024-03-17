#include <string>
#include <memory>

struct BuildDetails {
  std::string name;
  int m_b;
  int m_c;
  BuildDetails(int b, int c) : m_b(b), m_c(c) { }
};

class Product {
public:
  virtual std::string name() const = 0;
};

class Product1 : public Product {
public:
  int m_i;
  std::string name() const override { return("Product1"); };
};

class Product2 :public Product {
public:
  double m_d1;
  double m_d2;
  std::string name() const override { return("Product2"); };
};

//single singleton
template <typename T>
std::shared_ptr<T> singleton() {
  static std::shared_ptr<T> instance = std::make_shared<T>();
  return(instance);
}

class AbstractFactory {
public:
  virtual std::shared_ptr<Product> create(const std::shared_ptr<BuildDetails> &buildDetails) const = 0;
};

class Factory1 : public AbstractFactory {
public:
  std::shared_ptr<Product> create(const std::shared_ptr<BuildDetails> &buildDetails) const override {
    std::shared_ptr<Product1> product = std::make_shared<Product1>();
    product->m_i = buildDetails->m_b + buildDetails->m_c;
    return(product);
  }
  static std::shared_ptr<Factory1> instance() {
    return(singleton<Factory1>());
  }
};

class Factory2 : public AbstractFactory {
public:
  std::shared_ptr<Product> create(const std::shared_ptr<BuildDetails> &buildDetails) const override {
    std::shared_ptr<Product2> product = std::make_shared<Product2>();
    product->m_d1 = buildDetails->m_b;
    product->m_d2 = buildDetails->m_c * 2;
    return(product);
  }
  static std::shared_ptr<Factory2> instance() {
    return(singleton<Factory2>());
  }
};
