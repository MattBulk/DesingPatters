#ifndef CHAIN_H
#define CHAIN_H

#include "../commons.h"

class CreatureChain
{
public:
    /* data */
    std::string name;
    int attach, defense;
public:
    CreatureChain() {}
    ~CreatureChain() {}

    friend std::ostream& operator<<(std::ostream &os, const CreatureChain &p) {
        return os << "Name: "<< p.name <<" attach: "<<p.attach << " defense: "<< p.defense; 
    }
};

class CreatureModifiedChain
{
public:
    CreatureModifiedChain *next{nullptr};
protected:
    CreatureChain &creature;
public:
    CreatureModifiedChain(CreatureChain& creature) : creature(creature) {}
    ~CreatureModifiedChain() {}

    void add(CreatureModifiedChain* cm) {
        if(next)
            next->add(cm);
        else
            next = cm;
    }

    virtual void handle() {
        if(next)
            next->handle();
    }
};

class DoubleAttachModified : public CreatureModifiedChain
{
public:
    DoubleAttachModified(CreatureChain& creature) : CreatureModifiedChain(creature) {}
    ~DoubleAttachModified() {}

    void handle() override {
        this->creature.attach *= 2;
        CreatureModifiedChain::handle();
    }
};

class IncreaseDefenseModified : public CreatureModifiedChain
{
public:
    IncreaseDefenseModified(CreatureChain& creature) : CreatureModifiedChain(creature) {}
    ~IncreaseDefenseModified() {}

    void handle() override {
        if(this->creature.attach <= 2)
        this->creature.defense += 1;
        CreatureModifiedChain::handle();
    }
};

class NoBonusesModified : public CreatureModifiedChain
{
public:
    NoBonusesModified(CreatureChain& creature) : CreatureModifiedChain(creature) {}
    ~NoBonusesModified() {}

    void handle() override {
        // no bonus is selected
    }
};

void baseChainExample();

#endif