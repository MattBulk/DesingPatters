#include <memory>
#include <string>

class Product {
public:
  virtual std::shared_ptr<const double> price() const = 0;

  virtual Product *clone() const = 0;

  int year() const {
    return(this->m_year);
  }

  std::shared_ptr<const std::string> p_name() {
    return(this->m_p_name);
  }
  void set_p_name(const std::string &name) {
    this->m_p_name = std::make_shared<std::string>(name);
  }

protected:
  static void clone_imp(Product *product) {
    product->m_p_name = std::make_shared<std::string>(*product->m_p_name);
  }

private:
  std::shared_ptr<std::string> m_p_name;

  int m_year = 2019;

};


class Product2: public Product {

public:
  explicit Product2(const std::string &name,double price) {
    this->m_price = std::make_shared<double>(price);
    this->set_p_name(name);
  }

  std::shared_ptr<const double> price() const override {
    return(this->m_price);
  }

  Product2 *clone() const override {
    Product2 *product = new Product2(*this);
    this->clone_imp(product);
    return(product);
  }

protected:
  static void clone_imp(Product2 *product) {
    // here the base class is cloned
    Product::clone_imp(product);
    // adding other cloning features
    product->m_price = std::make_shared<double>(*product->m_price);

  }
private:
  std::shared_ptr<double> m_price;
};
