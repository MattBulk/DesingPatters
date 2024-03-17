#include <iostream>
#include "buildDetails.h"

int main(int argc, char const *argv[]) {
  /* code */
  BuildDetails buildDetails(2, 3);
  std::shared_ptr<Product> product1 = Factory::create(buildDetails);


  //clone the details
  std::shared_ptr<BuildDetails> buildDetails_cloned = buildDetails.clone();
  buildDetails_cloned->m_b += 1;
  //create new product
  std::shared_ptr<Product> product2 = Factory::create(*buildDetails_cloned);

  std::cout << "Product1 value: " << product1->m_a <<'\n';

  std::cout << "Product2 value: " << product2->m_a <<'\n';
  return 0;
}
