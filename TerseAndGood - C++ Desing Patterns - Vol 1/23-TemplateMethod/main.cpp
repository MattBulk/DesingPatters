#include <iostream>

class TemplateMethod {
public:
  void apply() const {
    operation1();
    operation2();
  }
private:
    virtual void operation1() const {
      std::cout << "operation1 base" << '\n';
    }
    virtual void operation2() const {
      std::cout << "operation2 base" << '\n';
    }
};

class TemplateMethod_A : public TemplateMethod {
  virtual void operation2() const override {
    std::cout << "operation2 Impl A" << '\n';
  }
};

class TemplateMethod_B : public TemplateMethod {
  virtual void operation2() const override {
    std::cout << "operation2 Impl B" << '\n';
  }
};

int main() {

  TemplateMethod_A method_a;
  TemplateMethod_B method_b;

  method_a.apply();
  method_b.apply();
  return 0;
}
