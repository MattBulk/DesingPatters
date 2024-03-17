#include "chain.h"

void baseChainExample() {
    CreatureChain goblin;
    goblin.attach = 1;
    goblin.defense = 1;
    goblin.name = "Goblin";

    CreatureModifiedChain root{goblin};
    DoubleAttachModified r1{goblin};
    DoubleAttachModified r1_2{goblin};

    IncreaseDefenseModified r2{goblin};

    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle();

    print("Base Chain Example ", goblin);
}

void brokenChainExample() {
    Game game;
    CreatureB goblin{game, "Strong Goblin", 2, 2};
    goblin.getAttach();
    std::cout<< goblin.name << " " << goblin.attack << " " << goblin.defense << std::endl;
    {
      DAMod dam{game, goblin};
      goblin.attack = goblin.getAttach();
      std::cout<< goblin.name << " " << goblin.attack << " " << goblin.defense << std::endl;
    }
    goblin.attack = goblin.getAttach();
    std::cout<< goblin.name << " " << goblin.attack << " " << goblin.defense << std::endl;    
}
