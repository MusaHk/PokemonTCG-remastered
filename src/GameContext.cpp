//
// Created by User on 6/10/2025.
//
#include "GameContext.h"

GameContext::GameContext(Game* game, Player* currentPlayer, Player* opponent, Pokemon* attacker, Pokemon* defender, Logger* logger)
    : game(game), currentPlayer(currentPlayer), opponent(opponent), attacker(attacker), defender(defender),logger(logger){}