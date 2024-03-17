#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "../commons.h"

class Weapon {
public:
    explicit Weapon(int s = 5) : strength(s) {}
    virtual ~Weapon() {}

    virtual int use() = 0;

    virtual Weapon* clone() const = 0;      // virtual copy constructor
    virtual Weapon* create() const = 0;     // virtual default constructor

protected:
    int strength;
};

class Sword : public Weapon {
public:
    explicit Sword(int strength, bool m = false) : Weapon(strength), magic(m) { }
    virtual ~Sword() {}

    virtual int use() {
        int damage = strength;
        if(magic)
            damage *= 2;
            print("sword damage ", damage);
        return damage;
    }

    virtual Sword* clone() const {
        return new Sword(*this);
    }

    virtual Sword* create() const {
        return new Sword(10);
    }

protected:
    bool magic;
};

class Bow : public Weapon {
public:
    explicit Bow(int strength, int a = 10) : Weapon(strength), arrows(a) { }
    virtual ~Bow() {}

    virtual int use() {
        int damage = 0;
        if(arrows) {
            damage = strength;
            arrows--;
            print("arrows count ", arrows);
        }
        return damage;
    }

    virtual Bow* clone() const {
        return new Bow(*this);
    }

    virtual Bow* create() const {
        return new Bow(10, 20);
    }

protected:
    int arrows;
};

class GameCharacter {
public:
    GameCharacter(Weapon *w = nullptr) : weapon(w), posX(0), posY(0) {}

    ~GameCharacter() {
        // delete weapon;
        std::cout << "delete";
    }

    GameCharacter(const GameCharacter &original) {
        posX = original.posX;
        posY = original.posY;
        weapon = original.weapon->clone();
    }

    GameCharacter& operator=(const GameCharacter &right) {
        if(this != &right) {
            posX = right.posX;
            posY = right.posY;
            Weapon *newWeapon = right.weapon->clone();
            if(weapon)
                delete weapon;
            weapon = newWeapon;
        }
        return *this;
    }

    virtual int fight() {
        int damage = weapon->use();
        return damage;
    }

protected:
int posX, posY;
Weapon* weapon;
};

void gameCharacter();

#endif