#include "personchat.h"
#include "chatroom.h"

void PersonChat::say(const std::string &message) const {
    room->broadcast(name, message);
}

void PersonChat::pm(const std::string &who, const std::string &message) const {
    room->message(name, who, message);
}