#ifndef CHATROOM_H
#define CHATROOM_H

#include "personchat.h"
#include "../commons.h"

class ChatRoom
{
public:
    std::vector<PersonChat *> people;
    /* data */
public:
    ChatRoom(/* args */) {}
    ~ChatRoom() {}
    void join(PersonChat *p);

    void broadcast(const std::string &origin, const std::string &message);
    
    void message(const std::string &origin, const std::string &who, const std::string &message);
    
};
#endif