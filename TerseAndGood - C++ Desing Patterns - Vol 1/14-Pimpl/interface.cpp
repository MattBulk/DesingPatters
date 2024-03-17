// implementation class
#include "interface.h"

class Interface::Implementation {
public:
  void setValue(int a) { this->m_a = a; }

  int value() const { return this->m_a; }

private:
  int m_a;
};

Interface::Interface() : m_pimpl(std::make_unique<Interface::Implementation>()) {
  m_pimpl->setValue(10);
}

Interface::~Interface() {};

int Interface::value() const {
  // here the pointer implementation is used. Hidden from the client.
  return m_pimpl->value();
}
