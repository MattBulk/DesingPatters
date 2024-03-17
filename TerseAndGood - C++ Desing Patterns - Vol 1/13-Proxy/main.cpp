#include <iostream>
#include <memory>
#include <map>
#include <vector>

// the intrinsic class which can be shared
class Character {

public:
  Character(const char &ch) : m_char(ch) {
    this-> m_pixel = std::vector<bool>(10000);
    std::cout << "Character Pixel created for " << ch <<'\n';
  }
  const std::vector<bool>& get() { return m_pixel; }
private:
  char m_char;
  // array of pixel 100*100 mimicking the pixel representation of a diplayed character.
  std::vector<bool> m_pixel;
};

// proxy class
class Letter {
public:
  // Lazy character is not initialised
  Letter(char ch) : m_char(ch) {

  }
  // we need the Character pixel to display it
  const std::vector<bool>& get() {
    if(!m_character) // Lazy
      m_character = std::make_shared<Character>(m_char);
    return m_character->get();
  }
  // for const obj
  const std::vector<bool>& get() const {
    // ouch : need it for Lazy
    return const_cast<Letter*>(this)->get();
  }
private:
  char m_char;
  std::shared_ptr<Character> m_character;
};

int main() {
  // create letters from a to z, save them in a map.
  std::map<char, std::shared_ptr<Letter>> letterMap;
  for (size_t i = 0; i < 26; i++) {
    /* code */
    char c = static_cast<char>('a' + i);
    letterMap[c] = std::make_shared<Letter>(c);
  }

  letterMap['l']->get();
  letterMap['a']->get();
  letterMap['a']->get();
  letterMap['z']->get();
  letterMap['z']->get();
  letterMap['y']->get();
  return 0;
}
