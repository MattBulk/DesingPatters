#include <iostream>
#include <list>
#include <string>

//abstract class with the interface
class Observer {
public:
  virtual void update(const std::string &message) = 0;
};


class Observer_Imp : public Observer {
public:
  Observer_Imp(int numero) : m_numero(numero) {}
  // display
  void update(const std::string &message) {
    std::cout << "Observer #" << m_numero << "update : " << message << std::endl;
  }
private:
  int m_numero;
};

// can be defined others Observer
class Subject {
  // collection of observers
  std::list<Observer*> m_observers;
public:
  Subject() {}
  void attach(Observer *observer) {
    m_observers.push_back(observer);
  }

  void detach(Observer *observer) {
    m_observers.remove(observer);
  }
  // will call all attached observer
  void notify() {
    for(auto &observer : m_observers)
      observer->update("from subject");
  }
};

int main() {

  Observer_Imp *observer_1(new Observer_Imp(1));
  Observer_Imp *observer_2(new Observer_Imp(2));

  Subject subject;
  subject.attach(observer_1);
  subject.attach(observer_2);

  subject.notify();

  return 0;
}
