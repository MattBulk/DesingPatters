#include <iostream>

class Object_A;
class Object_B;

// interface to be able to create a new visitor without the need to change this base class
class Visitor {
public:
  virtual void visit(Object_A *a) = 0;
  virtual void visit(Object_B *b) = 0;
};

class Object {
public:
  virtual void accept(Visitor *v) = 0;
};

class Object_A : public Object {
public:
  int m_number = 0;
  void accept(Visitor *v) {
    // send this object to visitor
    v->visit(this);
  }
};

class Object_B : public Object {
public:
  double m_d1 = 9;
  double m_d2 = 3;
  void accept(Visitor *v) {
    // send this object to visitor
    v->visit(this);
  }
};

class Visitor_Imp : public Visitor {
public:
  void visit(Object_A *a) {
    // use the Object_A interface
    std::cout << "A: " << a->m_number << '\n';
  }
  void visit(Object_B *b) {
    // use the Object_B interface
    std::cout << "B: " << b->m_d1 << b->m_d2 << '\n';
  }
};

int main() {

  Object_A obj_a;
  Object_B obj_b;

  Visitor_Imp v;
  // the objects accept the visit from the implementation and launches the classes method
  obj_a.accept(&v);
  obj_b.accept(&v);

  return 0;
}
