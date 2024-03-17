#include <iostream>
#include <string>
#include <vector>

// composite Interface
class Interface {
public:
  virtual void show(const std::string &endl="\n") const = 0;
};

class Single : public Interface {
public:
  Single(int a = 0) : m_a(a) {}
  void show(const std::string &endl="\n") const override {
    std::cout << m_a << endl;
  }
private:
  int m_a;
};

class Collection : public Interface {
private:
  std::vector<Interface*> m_vec;
public:
  void add(const int &a) {
    m_vec.emplace_back(new Single(a));
  }
  void show(const std::string &endl="\n") const override {
    for(const Interface* single : m_vec)
      single->show(",");
  }
};

int main() {
  Single single(4);
  single.show();

  Collection collection;
  collection.add(2);
  collection.add(4);
  collection.add(1);
  collection.show();
  return 0;
}
