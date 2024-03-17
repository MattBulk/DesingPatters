#include "chatroom.h"
#include <algorithm>

void ChatRoom::join(PersonChat *p)
    {
        std::string join_msg = p->name + " joins the chat";
        this->broadcast("room", join_msg);
        p->room = this;
        people.push_back(p);
    }

    void ChatRoom::broadcast(const std::string &origin, const std::string &message)
    {
        for (auto &&p : people)
        {
            if (p->name != origin)
                p->receive(origin, message);
        }
    }
    void ChatRoom::message(const std::string &origin, const std::string &who, const std::string &message)
    {
        auto target = std::find_if(begin(people), end(people),
                              [&](const PersonChat *p) { return p->name == who; });
        if (target != end(people))
        {
            (*target)->receive(origin, message);
        }
    }