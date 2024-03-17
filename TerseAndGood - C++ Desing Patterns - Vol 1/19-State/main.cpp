#include <iostream>

// Handler
class Handler {
public:
  virtual void apply(int number) const = 0;
};

class Handler1 : public Handler {
public:
  void apply(int number) const {
    std::cout << "Handler1 :" << 2 * number << std::endl;
  }
};

class Handler2 : public Handler {
public:
  void apply(int number) const {
    std::cout << "Handler2 :" << 1 + number << std::endl;
  }
};

class Object {
public:
  Object(int number) : m_number(number) {}

  void set_state(const Handler *state) {
    m_state = state;
  }

  void execute() {
    m_state->apply(m_number);
  }
private:
  int m_number = 0;
  const Handler *m_state = nullptr;
};

int main() {

  // WARNING where are the pointers going ????
  Object obj(3);
  obj.set_state(new Handler1());
  obj.execute();

  obj.set_state(new Handler2());
  obj.execute();
  return 0;
}
