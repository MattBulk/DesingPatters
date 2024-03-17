#ifndef PERSONCHAT_H
#define PERSONCHAT_H

#include "../commons.h"

class ChatRoom;

class PersonChat
{
public:

    /* data */
    std::string name;
    ChatRoom *room = nullptr;
    std::vector<std::string> chat_log;

public:
    PersonChat(const std::string &name) : name(name) {}
    ~PersonChat() {}

    void receive(const std::string &origin, const std::string &message) {
        std::string s{ origin + ": \"" + message + "\"" };
        std::cout << "[" << name << "'s chat session] " << s << "\n";
        chat_log.emplace_back(s);

    }
    void say(const std::string &message) const;
    void pm(const std::string &who, const std::string &message) const;
};

#endif