#include <iostream>
#include "buildDetails.h"

int main(int argc, char const *argv[]) {
  /* code */
  BuildDetails buildDetails(3, 2);
  std::shared_ptr<Product> product = Factory::create(buildDetails);

  std::cout << "Product value: " << product->m_a <<'\n';
  return 0;
}
