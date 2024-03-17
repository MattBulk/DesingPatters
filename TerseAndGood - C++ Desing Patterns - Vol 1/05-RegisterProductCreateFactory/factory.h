#include <string>
#include <memory>
#include <map>
#include <functional>
#include <stdexcept>

class Product;

class Factory {
public:
  // create map string as key and function as value
  std::map<std::string, std::function<std::shared_ptr<Product>()> > m_map_create;

  std::shared_ptr<Product> create(const std::string &name) const {
    // find the index
    auto fc = m_map_create.find(name);
    // if the index is the end - error
    if(fc == m_map_create.end())
      throw std::runtime_error("cannot find the product name");
    return(fc->second());
  }
  // singleton
  static std::shared_ptr<Factory> instance() {
    static std::shared_ptr<Factory> instance = std::make_shared<Factory>();
    return(instance);
  }
};

class Product {
protected:
  template<typename T>
  static size_t register_fc_creation(const std::string &name) {
    // lambda
    Factory::instance()->m_map_create[name] = ([]() {return std::make_shared<T>();});
    return(Factory::instance()->m_map_create.size());
  }
public:
  virtual std::string name() const = 0;
};

class Product1 : public Product {
  static size_t m_register_fc_creation;

public:
  virtual std::string name() const { return "Product1"; }
};

class Product2 : public Product {
  static size_t m_register_fc_creation;

public:
  virtual std::string name() const { return "Product2"; }
};
