#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class Character {
public:
  Character(const char &ch) : m_char(ch) {
    this->m_pixel = std::vector<bool>(10000);
  }

  void display(const unsigned short &color) const {
    std::cout << m_char;
  }
private:
  char m_char;

  std::vector<bool> m_pixel;
};

// The factory to store the letters
class Factory {
public:
  // singleton
  static std::shared_ptr<Factory> instance() {
    static std::shared_ptr<Factory> instance = std::make_shared<Factory>();
    return instance;
  }

  static std::shared_ptr<Character> getLetter(char ch) {
    return instance()->get(ch);
  }

  std::shared_ptr<Character> get(char ch) {
    auto iter = mapChar.find(ch);
    if(iter != mapChar.end())
      return iter->second;
    std::shared_ptr<Character> character = std::make_shared<Character>(ch);
    mapChar[ch] = character;
    return character;
  }

private:
  std::map<char, std::shared_ptr<Character>> mapChar;
};

// class Letter which include the color, extrinsic
class Letter {
public:
  Letter(char ch, const unsigned short &color) : m_color(color), m_character(Factory::getLetter(ch)) {}

  void display() const {
    m_character->display(m_color);
  }
private:
  unsigned short m_color;

  std::shared_ptr<Character> m_character;
};

class Text {
public:
  void add_Letters(const std::string &text, const unsigned short &color) {
    for(const char c : text)
      m_letters.emplace_back(c, color);
  }

  void display() const {
    for(const Letter &letter : m_letters)
      letter.display();
  }
private:
  std::vector<Letter> m_letters;
};

int main() {

  Text text;
  text.add_Letters("ababa", 12);
  text.add_Letters("fgggf", 9);
  text.display();
  std::cout << '\n';
  return 0;
}
