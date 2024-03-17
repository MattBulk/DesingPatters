#include "gameCharacter.h"

void gameCharacter() {
    
    Weapon *heroWeapon = new Sword(20, false);
    GameCharacter hero(heroWeapon);
    hero.fight();

    Bow *otherWeapon = new Bow(5, 10);
    GameCharacter companion(otherWeapon);
    companion.fight();
    companion.fight();
    companion.fight();
    companion.fight();
    companion.fight();

    // compiling it from the command shell, it works, pointers are deleted and the delete method is called.
}