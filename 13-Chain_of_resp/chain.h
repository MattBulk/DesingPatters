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

  friend std::ostream &operator<<(std::ostream &os, const CreatureChain &p)
  {
    return os << "Name: " << p.name << " attach: " << p.attach << " defense: " << p.defense;
  }
};

class CreatureModifiedChain
{
public:
  CreatureModifiedChain *next{nullptr};

protected:
  CreatureChain &creature;

public:
  CreatureModifiedChain(CreatureChain &creature) : creature(creature) {}
  ~CreatureModifiedChain() {}

  void add(CreatureModifiedChain *cm)
  {
    if (next)
      next->add(cm);
    else
      next = cm;
  }

  virtual void handle()
  {
    if (next)
      next->handle();
  }
};

class DoubleAttachModified : public CreatureModifiedChain
{
public:
  DoubleAttachModified(CreatureChain &creature) : CreatureModifiedChain(creature) {}
  ~DoubleAttachModified() {}

  void handle() override
  {
    this->creature.attach *= 2;
    CreatureModifiedChain::handle();
  }
};

class IncreaseDefenseModified : public CreatureModifiedChain
{
public:
  IncreaseDefenseModified(CreatureChain &creature) : CreatureModifiedChain(creature) {}
  ~IncreaseDefenseModified() {}

  void handle() override
  {
    if (this->creature.attach <= 2)
      this->creature.defense += 1;
    CreatureModifiedChain::handle();
  }
};

class NoBonusesModified : public CreatureModifiedChain
{
public:
  NoBonusesModified(CreatureChain &creature) : CreatureModifiedChain(creature) {}
  ~NoBonusesModified() {}

  void handle() override
  {
    // no bonus is selected
  }
};

void baseChainExample();

struct Query
{
  std::string creatureName;
  enum Argument
  {
    attack,
    defense
  } argument;
  int result;
};

class Game
{
public:
  /* data */
  boost::signals2::signal<void(Query &)> queries;

public:
  Game(/* args */) {}
  ~Game() {}
};

class CreatureB
{
private:
  Game &game;

public:
  int attack, defense;

public:
  CreatureB(Game &game, std::string name, int attack, int defense) : game(game), name(name), attack(attack), defense(defense)
  {
    
  }
  ~CreatureB() {}

  int getAttach() const
  {
    Query q{name, Query::Argument::attack, attack};
    game.queries(q);
    return q.result;
  }

  std::string name;
};

class CreatureModifier
{
private:
  Game &game;
  CreatureB &creature;

public:
  CreatureModifier(Game &game, CreatureB &creature) : game(game), creature(creature) {}
  ~CreatureModifier() {}
};

class DAMod : public CreatureModifier
{
private:
  boost::signals2::connection conn;

public:
  DAMod(Game &game, CreatureB &creature) : CreatureModifier(game, creature)
  {
    conn = game.queries.connect([&](Query &q) {
      if (q.creatureName == creature.name && q.argument == Query::Argument::attack)
      {
        q.result *= 2;
        print("Signal ", "emitted");
      }
    });
  }
  ~DAMod() { conn.disconnect(); }
};

void brokenChainExample();

#endif