#include <iostream>
#include "factory.h"

/*
  need to register the product before creating one of them
  cannot be defined inside a function
*/
size_t Product1::m_register_fc_creation = Product::register_fc_creation<Product1>("Product1");
size_t Product2::m_register_fc_creation = Product::register_fc_creation<Product2>("Product2");

int main(int argc, char const *argv[]) {


  std::shared_ptr<Product> product1 = Factory::instance()->create("Product1");
  std::shared_ptr<Product> product2 = Factory::instance()->create("Product2");
  std::shared_ptr<Product> product3 = Factory::instance()->create("Product2");

  std::cout << "Product: " << product1->name() << '\n';
  std::cout << "Product: " << product2->name() << '\n';
  std::cout << "Product: " << product2->name() << '\n';
  return 0;
}
