#include <iostream>
#include "interface.h"

template<typename T1>
void print(const T1 &t1) {
  std::cout << t1 <<'\n';
}

int main() {

  Interface_derived_1 interface_1;
  Interface_derived_2 interface_2;

  print(interface_1.value());
  print(interface_2.value());

  return 0;
}
