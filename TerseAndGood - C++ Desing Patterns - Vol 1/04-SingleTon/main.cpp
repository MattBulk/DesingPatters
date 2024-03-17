#include <iostream>
#include "factory.h"

int main() {

  std::shared_ptr<Factory> factory1 = Factory::instance();
  std::shared_ptr<Factory> factory2 = Factory::instance();
  std::shared_ptr<Factory> factory3 = Factory::instance();

  /*
   making the constructor private will prevent  
   Factory *instance = new Factory();
  */
  return 0;

}
