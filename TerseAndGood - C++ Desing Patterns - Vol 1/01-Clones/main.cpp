#include <iostream>
#include "clone.h"

template<typename T1, typename T2>
void print(const T1 &t1, const T2 &t2) {
  std::cout << t1 << t2 <<'\n';
}


int main() {

  Product *product = new Product(4, "tomato");
  Product *clone = product->clone();

  print("Product: m_i=", product->m_i);
  print("Cloned : m_i=", clone->m_i);
  // pointer index
  print("Product: m_p=", product->m_p);
  print("Cloned : m_p=", clone->m_p);
  //
  print("Product: *m_p=", *product->m_p);
  print("Cloned : *m_p=", *clone->m_p);
  return 0;
}
