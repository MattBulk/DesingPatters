#include "factory.h"
#include <memory>
#include <cstring>

enum class CharacterType { Knight=0, Wizard=1 };

class GameCharacterF {
public:
    GameCharacterF() : posX(0), posY(0), HP(10) {
        bitmap = nullptr;
    }
    virtual ~GameCharacterF() {
        if(bitmap != nullptr) {
            delete[] bitmap;
            print("memory freed: ", "base");
        }
    }

    virtual void move(int x, int y) = 0;

    virtual void fight(GameCharacterF &enemy) = 0;

    virtual void draw() {
        unsigned char ch = bitmap[0];
        int number = static_cast<int>(ch);
        print("Draw bitmap at: ", number);
    }
    
    void hit(int point) {
        this->HP -= point;
    } 

    void setBitmap(unsigned char *b, int size) {
        bitmap = b;
    }
protected:
    int posX, posY;
    int HP;

    unsigned char *bitmap;
};

class Knight : public GameCharacterF {
public:
    Knight() : dexterity(1) { }
    
    virtual ~Knight() {
        print("deleted: ", "Knight");
    }

    virtual void move(int x, int y) override {
        this->posX = x;
        this->posY = y;
    }

    virtual void fight(GameCharacterF &enemy) override {
        enemy.hit(2 + dexterity);
    }

private:
    int dexterity;
};

class Wizard : public GameCharacterF {
public:
    Wizard() { }
    virtual ~Wizard() {
        print("deleted: ", "Wizard");
    }

    virtual void move(int x, int y) override {
        this->posX = x;
        this->posY = y;
    }

    virtual void fight(GameCharacterF &enemy) override {
        enemy.hit(2);
    }
};

class CharacterFactory {
public:
    CharacterFactory() {
        print("Loading bitmap resources...", "");
        charactersBitmap = new unsigned char[10 * bitmapSize];
        for (int i = 0; i < 10; i++) {
          /* code */
          for (int j = 0; j < bitmapSize; j++) {
            /* code */
            int starting = i * bitmapSize;
            charactersBitmap[starting + j] = i;
          }
        }
    }

    virtual ~CharacterFactory() {
        delete[] charactersBitmap;
    }

    unsigned char* getBitmapTile(CharacterType type) {
        unsigned char* tile = new unsigned char[bitmapSize];
        switch (type) {
          case CharacterType::Knight:
            std::memcpy(tile, charactersBitmap + 0, bitmapSize);
            return tile;
          case CharacterType::Wizard:
            std::memcpy(tile, charactersBitmap + bitmapSize, bitmapSize);
            return tile;
        }
    }

    std::unique_ptr<GameCharacterF> createCharacter(const CharacterType &type) {
        std::unique_ptr<GameCharacterF> result;
        switch (type) {
          case CharacterType::Knight:
            result = std::unique_ptr<GameCharacterF>(new Knight());
            break;
          case CharacterType::Wizard:
            result = std::unique_ptr<GameCharacterF>(new Wizard());
            break;
        }
        result->setBitmap(getBitmapTile(type), bitmapSize);
        return result;
    }

    GameCharacterF* createCharacter2(const CharacterType &type) {
        GameCharacterF *result;
        switch (type) {
          case CharacterType::Knight:
            result = new Knight();
            break;
          case CharacterType::Wizard:
            result = new Wizard();
            break;
        }
        result->setBitmap(getBitmapTile(type), bitmapSize);
        return result;
    }

private:
    unsigned char *charactersBitmap;
    const int bitmapSize = 4096;
};

void factoryExample() {
    CharacterFactory factory;
#if 1
    GameCharacterF *hero = factory.createCharacter2(CharacterType::Knight);
    GameCharacterF *wizard = factory.createCharacter2(CharacterType::Wizard);
#else
    std::unique_ptr<GameCharacterF> hero = factory.createCharacter(CharacterType::Knight);
    std::unique_ptr<GameCharacterF> enemy = factory.createCharacter(CharacterType::Wizard);
#endif

    hero->draw();
    wizard->draw();
    hero->move(1, 1);
    hero->fight(*wizard);
    wizard->move(2, 2);

    delete hero;
    delete wizard;
}
