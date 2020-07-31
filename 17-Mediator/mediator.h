#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "../commons.h"

struct EventData
{
    virtual ~EventData() = default;
    virtual void print() const = 0;
};

struct GameMediator
{
    boost::signals2::signal<void(EventData *)> events; // observer
};

struct PlayerScoredData : EventData
{
    std::string player_name;
    int goals_scored_so_far;

    PlayerScoredData(const std::string &player_name, const int goals_scored_so_far)
        : player_name(player_name),
          goals_scored_so_far(goals_scored_so_far) {}

    void print() const override
    {
        std::cout << player_name << " has scored! (their " << goals_scored_so_far << " goal)"
                  << "\n";
    }
};

struct PlayerMediator
{
    std::string name;
    int goals_scored = 0;
    GameMediator &game;
    PlayerMediator(const std::string &name, GameMediator &game)
        : name(name), game(game) {}
    void score()
    {
        goals_scored++;
        PlayerScoredData ps{name, goals_scored};
        game.events(&ps);
    }
};

struct Coach
{
    GameMediator &game;
    explicit Coach(GameMediator &game) : game(game)
    {
        // celebrate if player has scored <3 goals
        game.events.connect([](EventData *e) {
            PlayerScoredData *ps = dynamic_cast<PlayerScoredData *>(e);
            if (ps && ps->goals_scored_so_far < 3)
            {
                std::cout << "coach says: well done, " << ps->player_name << "\n";
            }
        });
    }
};

void mediatorExample();

void mediatorSignalExample();

#endif