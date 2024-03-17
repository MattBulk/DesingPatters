#include <memory>

/*
  it semplify object creation - 04 example
*/
struct BuildDetails {
  int m_b;
  int m_c;

  BuildDetails(int b, int c) : m_b(b), m_c(c) { }

  std::shared_ptr<BuildDetails> clone() const {
    return(std::make_shared<BuildDetails>(*this));
  }
};

class Product {
public:
  int m_a;
  // keep the BuildDetails in the product
  std::shared_ptr<const BuildDetails> m_buildDetails = nullptr;
};

/*
  Factory takes the BuildDetails and passes the value to the class. This example is too simple to
*/
class Factory {
  Factory() {}
public:
  static std::shared_ptr<Product> create(const BuildDetails &buildDetails) {

    std::shared_ptr<Product> product = std::make_shared<Product>();
    product->m_a = buildDetails.m_b + buildDetails.m_c;
    return(product);
  }
};
