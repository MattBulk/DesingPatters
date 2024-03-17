#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <memory>

class Interface {

public:
  Interface();
  ~Interface();
  int value() const;
private:
  class Implementation;
  // declaring a pointer, no need to give an implementation interface
  std::unique_ptr<Implementation> m_pimpl;
};

#endif
