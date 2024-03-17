#include <iostream>

struct Memento {
  // data used to recreate the Object
  int m_number;
  Memento(int number) : m_number(number) {}
};

class Object {
public:
  int get() const {
    return m_number;
  }
  void update() {
    ++m_number;
  }
  // get Memento
  Memento *create_memento() const {
    return new Memento(m_number);
  }
  void set_memento(const Memento *memento) {
    m_number = memento->m_number;
  }
private:
  // only data to be recreated
  int m_number = 0;

};

int main() {

  Object obj;
  obj.update();
  // check point. Return a copy to the point you have updated
  Memento *memento1 = obj.create_memento();
  std::cout << "memento at: " << obj.get() << '\n';
  // do something
  obj.update();
  obj.update();
  std::cout << "before set: " << obj.get() << '\n';
  obj.set_memento(memento1);
  std::cout << "after set: " << obj.get() << '\n';

  return 0;
}
