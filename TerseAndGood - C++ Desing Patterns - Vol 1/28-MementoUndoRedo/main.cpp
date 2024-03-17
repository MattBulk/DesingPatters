#include <iostream>
#include <vector>
#include <string>

struct Memento {
  // data used to recreate the Object
  int m_number;
  Memento(int number) : m_number(number) {}
};

struct Records {
  std::vector<const Memento*> m_mementos;
  // stack position
  int m_pos = -1;
  // add a new element
  void add(const Memento *memento) {
    if(m_pos + 1 == m_mementos.size()) {
      m_mementos.push_back(memento);
      ++m_pos;
    }
    else {
      // add in the middle, after some undo
      m_mementos[++m_pos] = memento;
      m_mementos.resize(m_pos + 1);
    }
  }

  const Memento* undo() {
    if(m_pos == 0)
      return m_mementos[0];
    return m_mementos[--m_pos];
  }

  const Memento* redo() {
    if(m_pos + 1 == m_mementos.size())
      return m_mementos.back();
    else
      return m_mementos[++m_pos];
  }
  // print
  void print() const {
    std::cout << "{ ";
    for (size_t i = 0; i < m_mementos.size(); i++) {
      // if undo, some elements are not displayed
      if(i > m_pos) std::cout << "(";
      std::cout << m_mementos[i]->m_number;
      if(i > m_pos) std::cout << ")";
      if(i + 1 != m_mementos.size())
        std::cout << ", ";
    }
    std::cout << " }";
  }
};


class Object {
public:
  Object() {
    // add first record when created
    m_records.add(create_memento());
  }

  void update(int num) {
    m_number += num;
    // save update
    m_records.add(create_memento());
  }

  void undo() {
    set_memento(m_records.undo());
  }

  void redo() {
    set_memento(m_records.redo());
  }

  void print(const std::string &msg) {
    std::cout << msg;
    std::cout << m_number << "  // ";
    // show saved memento
    m_records.print();
    std::cout << '\n';
  }
private:
  Memento *create_memento() const {
    return new Memento(m_number);
  }

  void set_memento(const Memento *memento) {
    m_number = memento->m_number;
  }
private:
  // only data to be recreated
  int m_number = 0;
  // Record: collection of memento, to help undo/redo
  Records m_records;

};

int main() {

  Object obj; // {0}
  obj.print("start  : ");
  for (size_t i = 0; i < 6; i++) {
    /* code */
    obj.update(1);
    obj.print("update  : ");
  }

  obj.redo();
  obj.print("redo   : ");
  obj.undo();
  obj.print("undo   : ");
  obj.undo();
  obj.print("undo   : ");
  obj.update(8);
  obj.print("update  : ");
  obj.undo();
  obj.undo();
  obj.undo();
  obj.print("undo   : ");
  return 0;
}
