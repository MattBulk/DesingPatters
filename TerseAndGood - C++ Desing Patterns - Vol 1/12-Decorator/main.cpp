#include <iostream>
#include <memory>

// base class to have similar behaviour
struct Base {
  virtual ~Base() {};
};

// original class
class Product : public Base {
public:
  Product(int a) : m_a(a) {}
  int value() { return m_a;}
private:
  int m_a;
};

// decorator we want to add a new function value_new
class Decorator : public Base {
public:
  Decorator(int a, int add=0) : m_product(std::make_shared<Product>(a)), m_add(add) {}
  // reimplement all the Product interface
  int value() const { return m_product->value(); }
  // decorate the class with a new function
  int value_new() const {
    return m_product->value() + m_add;
  }
private:
  std::shared_ptr<Product> m_product;
  int m_add;
};

template<typename T1, typename T2>
void print(const T1 &t1, const T2 &t2) {
  std::cout << t1 << t2 <<'\n';
}

int main() {
  Product product(4);
  print("Product(4).value=", product.value());

  Decorator decorator(4, 5);
  print("Decorator(4).value=", decorator.value());
  print("Decorator(4).value_new=", decorator.value_new());
  return 0;
}
