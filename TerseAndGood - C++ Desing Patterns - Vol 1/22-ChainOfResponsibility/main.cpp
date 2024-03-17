#include <iostream>

class Client {
public:
  Client(int number) : m_number(number) {
    m_result = -1;
  }

  int m_number;
  int m_result;
};

class Handler {
public:
  virtual Client &apply(Client &client) const = 0;
  virtual void add(Handler *handler) = 0;
};

class Handler_Imp : public Handler {
  // chain of responsibility: if we can't update the result in the handler, pass to the next Handler
public:
  Handler_Imp(int numero) : m_numero(numero) {}
  // adding chain of handler
  void add(Handler *handler) {
    if(m_handler)
      m_handler->add(handler);
    else
      m_handler = handler;
  }

  Client &apply(Client &client) const {
    if(client.m_number % m_numero == 0) {
      client.m_result = 10 * m_numero;
      return client;
    }
    else if(m_handler)
      return m_handler->apply(client);
    return client;
  }
private:
  Handler *m_handler = nullptr;
  int m_numero;
};

int main() {
  // create handler
  Handler_Imp handler2(2);
  Handler_Imp handler3(3);
  Handler_Imp handler5(5);
  // create the chain of responsibility
  handler2.add(&handler3);
  handler2.add(&handler5);

  auto Result = [](const Handler &handler, int num) {
    Client client = Client(num);
    std::cout << "Result for Client(" << num << "): " << handler.apply(client).m_result << std::endl;
  };

  Result(handler2, 81);
  Result(handler2, 80);
  Result(handler2, 17);
  Result(handler2, 25);

  return 0;
}
