#include <iostream>
#include <memory>

class Interface_Not_Good {
public:
  int *m_a;
  void set(int a) {
    m_a = new int(a);
  }
};

// Adapter class
class Interface_Good {
  Interface_Not_Good m_Not_Good;
public:
  Interface_Good(int a) {
      m_Not_Good.m_a = new int(a);
  }
  ~Interface_Good() {
    delete m_Not_Good.m_a;
  }
  int get() const {
    return *m_Not_Good.m_a;
  }

};

int main() {

  Interface_Good interface_Good(3);
  std::cout << interface_Good.get() << '\n';
  return 0;
}
