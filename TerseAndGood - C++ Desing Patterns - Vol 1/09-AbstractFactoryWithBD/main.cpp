#include "abstractFactory.h"
#include <iostream>
#include <stdexcept>

std::shared_ptr<AbstractFactory> createFactory(const std::shared_ptr<BuildDetails>& buildDetails) {
  if(buildDetails->name == "Factory1")
    return(Factory1::instance());
  else if(buildDetails->name == "Factory2")
      return(Factory2::instance());
  else
    throw std::runtime_error("no item can be found");
}
//help function to create product
std::shared_ptr<Product> createProduct(const std::shared_ptr<BuildDetails>& buildDetails) {
  return(createFactory(buildDetails)->create(buildDetails));
}

int main(int argc, char const *argv[]) {

  std::shared_ptr<BuildDetails> buildDetails = std::make_shared<BuildDetails>(2, 3);
  buildDetails->name = "Factory2";

  std::shared_ptr<Product> product2 = createProduct(buildDetails);
  std::cout << product2->name() << '\n';

  std::shared_ptr<Product> product1 = Factory1::instance()->create(buildDetails);
  std::cout << product1->name() << '\n';
  return 0;
}
