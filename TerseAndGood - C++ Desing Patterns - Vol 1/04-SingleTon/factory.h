#include <memory>
#include <iostream>

class Factory {
private:
  Factory() {
    std::cout << "Factory created" << '\n';
  }

public:
  static::std::shared_ptr<Factory> instance() {
      static::std::shared_ptr<Factory> instance(new Factory());
      return(instance);
  }
};
