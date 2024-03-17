#include <iostream>
#include <memory>
#include <deque>

// command interface
class Command {
public:
  virtual void execute() const = 0;
};

// specialized command
class Command1 : public Command {
public:
  virtual void execute() const {
    std::cout << "Command 1" << '\n';
  }
};

class Command2 : public Command {
public:
  virtual void execute() const {
    std::cout << "Command 2" << '\n';
  }
};

class Script {
public:
  void push_back(const std::shared_ptr<Command> &command) {
    m_commands.push_back(command);
  }

  void execute() {
    while(!m_commands.empty()) {
      m_commands.front()->execute();
      m_commands.pop_front();
    }
  }
private:
  std::deque<std::shared_ptr<Command>> m_commands;
};

int main() {

  Script script;
  script.push_back(std::make_shared<Command1>());
  script.push_back(std::make_shared<Command2>());
  script.push_back(std::make_shared<Command1>());
  script.push_back(std::make_shared<Command2>());

  std::cout << "Script execute" << '\n';
  script.execute();

  return 0;
}
