#include "mvc.h"

#include <list>

class Observer {
public:
    virtual ~Observer() {}

    virtual void update() = 0;
};

class Subject {
public:
    virtual ~Subject() {}

    virtual void addObserver(Observer *ob) = 0;
    virtual void removeObserver(Observer *ob) = 0;
    virtual void notify() = 0;
};

class Model : public Subject {
public:
    int getData() { return data; }

    void setData(int i) {
        data = i;
        notify();
    }

    virtual void addObserver(Observer *ob) override {
        observers.push_back(ob);
    }

    virtual void removeObserver(Observer *ob) override {
        observers.remove(ob);
    }

    virtual void notify() {
        for(auto &&ob : observers)
            ob->update();
    }
private:
    int data = 0;
    std::list<Observer*> observers;
};

class Controller {
public:
    Controller(Model *m) : model(m) { }

    void increment() {
        int value = model->getData();
        value++;
        model->setData(value);
    }

    void decrement() {
      int value = model->getData();
      value--;
      model->setData(value);
    }
private:
    Model *model;
};

class View : public Observer {
public:
    View(Model *m, Controller *c) {
        model = m;
        model->addObserver(this);
        controller = c;
    }

    virtual ~View() { model->removeObserver(this); }

    void displeTextField(int i) {
        print("Text field: ", i);
    }

    virtual void update() override {
        int value = model->getData();
        displeTextField(value);
    }

    void incrementButton() { controller->increment(); }

    void decrementButton() { controller->decrement(); }

private:
    Model *model;
    Controller *controller;
};

void mvcExample() {
  Model *model = new Model();
  Controller *controller = new Controller(model);

  View *view = new View(model, controller);

  view->incrementButton();
  view->incrementButton();
  view->decrementButton();
}
