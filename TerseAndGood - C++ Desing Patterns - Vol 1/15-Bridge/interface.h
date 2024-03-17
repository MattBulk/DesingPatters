#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <memory>

class Implementation;

class Interface {

public:
  virtual int value() const = 0;
protected:
  // declaring a pointer, no need to give an implementation interface
  std::unique_ptr<Implementation> m_pimpl;
};

// derived classes
class Interface_derived_1 : public Interface {
public:
  Interface_derived_1();
  ~Interface_derived_1();
  int value() const;
};

class Interface_derived_2 : public Interface {
public:
  Interface_derived_2();
  ~Interface_derived_2();
  int value() const;
};

#endif
