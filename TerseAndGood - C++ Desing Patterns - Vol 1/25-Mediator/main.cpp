#include <iostream>
#include <list>
#include <string>

// Interface common to Clients and Mediator, used to communicate between Clients and Mediator
class Interface {
public:
  virtual void message_receive(const std::string &message) = 0;

  virtual void message_send(const std::string &message) = 0;
};

class Client : public Interface {
public:
  Client(Interface *mediator, const std::string &numero) {
    m_mediator = mediator;
    m_numero = numero;
  }
  void message_receive(const std::string &message) {
    std::cout << "Client #" << m_numero << " update : " << message << std::endl;
  }

  void message_send(const std::string &message) {
    std::string msg = "from client ";
    msg += m_numero;
    msg += ": ";
    msg += message;
    m_mediator->message_receive(msg);
  }
private:
  // mediator address to send message
  Interface *m_mediator = nullptr;
  // to know which client is called
  std::string m_numero;
};

class Mediator : public Interface {
public:
  Mediator() {}
  // attach clients
  void attach(Interface *client) {
    m_clients.push_back(client);
  }
  void detach(Interface *client) {
    m_clients.remove(client);
  }
  // receive a message from outside (could be a client)
  void message_receive(const std::string &message) {
    message_send(message);
  }

  void message_send(const std::string &message) {
    std::string msg = "from mediator: ";
    msg += message;
    for(auto & client : m_clients)
      client->message_receive(msg);
  }
private:
  std::list<Interface *> m_clients;
};

int main() {

  Mediator mediator;

  Client* client_1(new Client(&mediator, "1"));
  Client* client_2(new Client(&mediator, "2"));
  Client* client_3(new Client(&mediator, "3"));
  //attach client to receive
  mediator.attach(client_2);
  mediator.attach(client_3);
  // send a message from the client to the mediator that will dispatch the message
  client_1->message_send("Tweet!");
  return 0;
}
