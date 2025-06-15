#include "PokemonHeaders/Darkrai.h"
#include "GameContext.h"
#include "Player.h"
#include "Game.h"
#include <cstdlib>  // For rand()

Darkrai::Darkrai()
    : Pokemon("Darkrai", 90, 5, false,
              "assets/sprites/front/darkraiFront.gif",
              "assets/sprites/back/darkraiBack.gif",
              "assets/audio/darkrai.mp3") {}

void Darkrai::onEntry(GameContext& ctx) {
    playTheme();
}

void Darkrai::applyPassive(GameContext& ctx) {
    // Dark Dreams is handled in the attack missing logic
}

void Darkrai::onTurnStart(GameContext& ctx) {
    if (disabledMoveIndex >= 0) {
        disabledMoveIndex = -1;  // Re-enable disabled move
    }
}

void Darkrai::onTurnEnd() {
    if (skipNextTurn) {
        skipNextTurn = false;
    }
}

void Darkrai::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    int damage = 0;

    switch (moveIndex) {
        case 0: {  // Dark Pulse
            useEnergy(2);
            damage = 20;
            target->takeDamage(damage);
            ctx.getLogger().logEvent("Darkrai used Dark Pulse for " + string::itos(damage) + " damage!");
            
            // 50% chance to put opponent to sleep
            if (rand() % 2 == 0) {
                ctx.getGame()->grantExtraAction();  // Skip opponent's next turn
                ctx.getLogger().logEvent("Dark Pulse put the opponent to sleep! They skip their next turn!");
            }
            break;
        }
        case 1: {  // Nightmare Bind
            useEnergy(3);
            damage = 30;
            target->takeDamage(damage);
            
            // Disable random move
            int moveCount = target->getMoveNames().size();
            if (moveCount > 0) {
                disabledMoveIndex = rand() % moveCount;
                ctx.getLogger().logEvent("Nightmare Bind disabled " + 
                    target->getMoveNames()[disabledMoveIndex] + " for one turn!");
            }
            
            ctx.getLogger().logEvent("Darkrai used Nightmare Bind for " + string::itos(damage) + " damage!");
            break;
        }
        case 2: {  // Eclipse Slash
            useEnergy(4);
            damage = 60;
            target->takeDamage(damage);
            skipNextTurn = true;
            ctx.getLogger().logEvent("Darkrai used Eclipse Slash for " + string::itos(damage) + " damage!");
            ctx.getLogger().logEvent("Darkrai can't act next turn due to Eclipse Slash's effect!");
            break;
        }
        default:
            break;
    }
}

Dynamic_array<string> Darkrai::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Dark Pulse");
    moves.push("Nightmare Bind");
    moves.push("Eclipse Slash");
    return moves;
}

string Darkrai::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 20 damage. 50% chance to put opponent to sleep (they skip their next turn).";
        case 1: return "Deal 30 damage. Disable one random move for 1 turn.";
        case 2: return "Deal 60 damage. Darkrai can't act next turn.";
        default: return "Unknown move.";
    }
}

int Darkrai::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 2;  // Dark Pulse
        case 1: return 3;  // Nightmare Bind
        case 2: return 4;  // Eclipse Slash
        default: return 999;
    }
}

string Darkrai::getPassiveName() const {
    return "Dark Dreams";
}

string Darkrai::getPassiveDescription() const {
    return "If opponent misses an attack, they lose 1 energy.";
}