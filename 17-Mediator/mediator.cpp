#include "mediator.h"

#include "chatroom.h"

void mediatorExample()
{
    ChatRoom room;
    PersonChat john{"john"};
    PersonChat jane{"jane"};
    room.join(&john);
    room.join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");
    PersonChat simon("simon");
    room.join(&simon);
    simon.say("hi everyone!");
    jane.pm("simon", "glad you could join us, simon");
}

void mediatorSignalExample()
{
    GameMediator game;
    PlayerMediator player{"Sam", game};
    Coach coach{game};
    player.score();
    player.score();
    player.score(); // ignored by coach
}