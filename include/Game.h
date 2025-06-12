#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Logger.h"
#include "GameContext.h"
#include "Dynamic_array.h"
#include "string.h"

class Action;
class Pokemon;

class Game {
private:
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    Player* opponentPlayer;

    Logger logger;
    GameContext* context;

    bool extraActionGranted;
    Pokemon* shieldedPokemon;
    float shieldFactor;

    void assignRandomTeams(const Dynamic_array<Pokemon*>& pool);

public:
    Game(Player* p1, Player* p2);
    ~Game();

    void start();
    void runTurn();
    void processAction(Action* action);
    void switchPlayers();

    bool isGameOver() const;
    Player* getWinner() const;

    void grantExtraAction();
    void shieldNextDamage(Pokemon* p, float factor);

    void saveToFile(const string& filepath) const;
    void loadFromFile(const string& filepath);

    Logger& getLogger()       { return logger; }
    GameContext& getContext() { return *context; }
};

#endif // GAME_H
