#include <iostream>
#include "factory.h"

int main() {

  std::shared_ptr<Product> product = Factory::create(ProductType::Shoes);
  std::cout << product->name() << ": price is "<< product->price() << std::endl;

  std::shared_ptr<Product> product2 = Factory::create(ProductType::Smartphone);
  return 0;

}
