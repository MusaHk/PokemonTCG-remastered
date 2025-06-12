//
// Created by User on 6/10/2025.
//

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "Logger.h"

class Game;
class Player;
class Pokemon;

class GameContext {
private:
    Game* game;
    Player* currentPlayer;
    Player* opponent;
    Pokemon* attacker;
    Pokemon* defender;
    Logger* logger;
public:
    GameContext(Game* game, Player* currentPlayer, Player* opponent,
                Pokemon* attacker, Pokemon* defender, Logger* logger);

    Game* getGame() const { return game; }
    Player* getCurrentPlayer() const { return currentPlayer; }
    Player* getOpponent() const { return opponent; }
    Pokemon* getAttacker() const { return attacker; }
    Pokemon* getDefender() const { return defender; }
    Logger& getLogger() { return *logger; }
};

#endif // GAMECONTEXT_H