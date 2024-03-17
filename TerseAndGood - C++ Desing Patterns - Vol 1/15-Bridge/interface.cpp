// implementation class
#include "interface.h"

class Implementation {
public:
  virtual int value() const = 0;
};

class Implementation_derivated_1 : public Implementation {
public:
  Implementation_derivated_1(int a) {
    m_a = a;
  }
  int value() const { return this->m_a; }

private:
  int m_a;
};

class Implementation_derivated_2 : public Implementation {
public:
  Implementation_derivated_2(double d1, double d2) : m_d1(d1), m_d2(d2) { }

  int value() const { return static_cast<int>(m_d1 + m_d2); }

private:
  double m_d1, m_d2;
};

Interface_derived_1::Interface_derived_1() {
  m_pimpl = std::make_unique<Implementation_derivated_1>(3);
}

Interface_derived_1::~Interface_derived_1() {};

int Interface_derived_1::value() const {
  // here the pointer implementation is used. Hidden from the client.
  return m_pimpl->value();
}

Interface_derived_2::Interface_derived_2() {
  m_pimpl = std::make_unique<Implementation_derivated_2>(1., 4.);
}

Interface_derived_2::~Interface_derived_2() {};

int Interface_derived_2::value() const {
  // here the pointer implementation is used. Hidden from the client.
  return m_pimpl->value();
}
