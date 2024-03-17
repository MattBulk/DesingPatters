#include <memory>
#include <string>

class Product {
public:
  explicit Product(int id, const std::string &name) {

      this->m_i = id;
      this->m_p = std::make_shared<std::string>(name);

  }
  Product *clone() const {
    Product *product = new Product(*this);
    product->m_p = std::make_shared<std::string>(*m_p);
    return(product);
  }

public:

  std::shared_ptr<std::string> m_p;

  int m_i;

};
