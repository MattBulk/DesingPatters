#include "abstractFactory.h"
#include <iostream>

int main(int argc, char const *argv[]) {
  std::shared_ptr<AbstractFactory> factory1 = std::make_shared<Factory1>();
  std::shared_ptr<AbstractFactory> factory2 = std::make_shared<Factory2>();

  std::shared_ptr<Product> product1 = factory1->create();
  std::shared_ptr<Product> product2 = factory2->create();

  std::cout << product1->name() << '\n';
  std::cout << product2->name() << '\n';
  return 0;

}
