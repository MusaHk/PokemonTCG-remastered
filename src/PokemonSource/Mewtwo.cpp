#include "PokemonHeaders/Mewtwo.h"
#include "GameContext.h"
#include "Player.h"
#include "Game.h"

Mewtwo::Mewtwo()
    : Pokemon("Mewtwo", 100, 5, false,
              "assets/sprites/front/mewtwoFront.gif",
              "assets/sprites/back/mewtwoBack.gif",
              "assets/audio/mewtwo.mp3") {
    psychicWallActive = false;
}

void Mewtwo::onEntry(GameContext& ctx) {
    playTheme();
}

void Mewtwo::applyPassive(GameContext& ctx) {
    if (psychicWallActive) {
        int originalDamage = lastDamageTaken;
        lastDamageTaken = lastDamageTaken / 2;
        if (originalDamage != lastDamageTaken) {
            ctx.getLogger().logEvent("Psychic Wall halved incoming damage from " + 
                                   string::itos(originalDamage) + " to " + 
                                   string::itos(lastDamageTaken) + "!");
        }
    }
}

void Mewtwo::onTurnEnd() {
    psychicWallActive = false;
}

void Mewtwo::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    int damage = 0;

    switch (moveIndex) {
        case 0: {  // Psystrike
            useEnergy(3);
            damage = 40;
            string passiveName = target->getPassiveName();
            if (passiveName.length() > 0) {  // Using length() instead of empty()
                damage += 10;
                ctx.getLogger().logEvent("Psystrike's power increased due to opponent's passive!");
            }
            target->takeDamage(damage);
            ctx.getLogger().logEvent("Mewtwo used Psystrike for " + string::itos(damage) + " damage!");
            break;
        }
        case 1: {  // Mind Crush
            useEnergy(2);
            // Energy drain effect
            if (target->getCurrentEnergy() > 0) {
                target->useEnergy(1);
                ctx.getLogger().logEvent("Mewtwo used Mind Crush! Opponent lost 1 energy.");
            } else {
                ctx.getLogger().logEvent("Mind Crush had no effect - opponent has no energy!");
            }
            break;
        }
        case 2: {  // Psychic Wall
            useEnergy(3);
            psychicWallActive = true;
            ctx.getLogger().logEvent("Mewtwo created a Psychic Wall! Next turn's damage will be halved.");
            break;
        }
        default:
            break;
    }
}

Dynamic_array<string> Mewtwo::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Psystrike");
    moves.push("Mind Crush");
    moves.push("Psychic Wall");
    return moves;
}

string Mewtwo::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 40 damage. If the opponent has a passive, deal +10 extra.";
        case 1: return "Opponent loses 1 energy.";
        case 2: return "On your next turn, damage taken is halved.";
        default: return "Unknown move.";
    }
}

int Mewtwo::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 3;  // Psystrike
        case 1: return 2;  // Mind Crush
        case 2: return 3;  // Psychic Wall
        default: return 999;
    }
}

string Mewtwo::getPassiveName() const {
    return "Mind Shield";
}

string Mewtwo::getPassiveDescription() const {
    return "Immune to confusion and energy drain effects.";
}