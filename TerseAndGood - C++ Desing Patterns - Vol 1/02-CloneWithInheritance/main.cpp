#include <iostream>
#include "clone.h"

template<typename T1, typename T2>
void print(const T1 &t1, const T2 &t2) {
  std::cout << t1 << t2 <<'\n';
}


int main() {

  Product *product = new Product2("tomato", 5.2);
  Product *clone = product->clone();
  // year
  print("Product: m_year=\t", product->year());
  print("Cloned : m_year=\t", clone->year());
  // pointer index
  print("Product: m_p_name=\t", product->p_name());
  print("Cloned : m_p_name=\t", clone->p_name());
  // product name
  print("Product: *m_p_name=\t", *product->p_name());
  print("Cloned : *m_p_name=\t", *clone->p_name());
  // price
  print("Product: *m_price=\t", *product->price());
  print("Cloned : *m_price=\t", *clone->price());

  // price memory index
  print("Product: *m_price=\t", product->price());
  print("Cloned : *m_price=\t", clone->price());
  return 0;
}
