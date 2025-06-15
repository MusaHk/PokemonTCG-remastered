#include "PokemonHeaders/Dialga.h"
#include "Game.h"
#include "GameContext.h"
#include "Player.h"
#include "Pokemon.h"
#include "String.h"

Dialga::Dialga()
    : Pokemon("Dialga", 170, 5, true,
              "assets/sprites/front/dialgaFront.gif",
              "assets/sprites/back/dialgaBack.gif",
              "assets/audio/dialga.mp3") {
}

void Dialga::onEntry(GameContext& ctx) {
    playTheme();
}

// Passive Ability: Temporal Mastery
// Once per game, if a move of cost >= 3 is used, skip the opponent's next turn
void Dialga::applyPassive(GameContext& ctx) {
    if (!passiveUsed && lastMoveUsed >= 0 && getMoveCost(lastMoveUsed) >= 3) {
        ctx.getGame()->grantExtraAction();
        passiveUsed = true;
        ctx.getLogger().logEvent("Temporal Mastery activated! Opponent loses their next turn.");
    }
}


// Move logic
void Dialga::applyMove(int moveIndex, GameContext& ctx) {
    lastMoveUsed = moveIndex;
    Pokemon* target = ctx.getDefender();
    Player* self = ctx.getCurrentPlayer();

    switch (moveIndex) {
        case 0: { // Dragon Pulse
            int damage = 25;
            if (getCurrentEnergy() == getMaxEnergy()) {
                damage += 15;
                ctx.getLogger().logEvent("Dragon Pulse hits with max power!");
            }
            useEnergy(1);
            target->takeDamage(damage);
            ctx.getLogger().logEvent("Dialga used Dragon Pulse for " + string::itos(damage) + " damage.");
            break;
        }
        case 1: { // Metal Burst
            useEnergy(3);
            int damage = 45;
            target->takeDamage(damage);
            ctx.getLogger().logEvent("Dialga used Metal Burst for " + string::itos(damage) + ".");

            if (getCurrentHP() < getMaxHP() / 2) {
                int reflected = target->getLastDamageTaken();
                int reflectAmount = reflected * 20 / 100;
                target->takeDamage(reflectAmount);
                ctx.getLogger().logEvent("Metal Burst reflected " + string::itos(reflectAmount) + " damage!");
            }
            break;
        }
        case 2: { // Roar of Time
            useEnergy(5);
            target->takeDamage(70);
            Dynamic_array<Pokemon*>& team = ctx.getOpponent()->getTeam();
            for (int i = 0; i < team.size(); i++) {
                Pokemon* mon = team[i];
                mon->useEnergy(1);
            }
            ctx.getLogger().logEvent("Dialga unleashed Roar of Time! 70 damage + energy drain.");
            break;
        }
        default:
            break;
    }
}

// UI: Move names
Dynamic_array<string> Dialga::getMoveNames() const {
    Dynamic_array<string> names;
    names.push("Dragon Pulse");
    names.push("Metal Burst");
    names.push("Roar of Time");
    return names;
}

// UI: Move descriptions
string Dialga::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 25 damage. If energy is full, deal +15.";
        case 1: return "Deal 45 damage. If HP < 50%, reflect 20% of last damage received.";
        case 2: return "Deal 70 damage. Drain 1 energy from all enemy Pokémon.";
        default: return "Unknown move.";
    }
}

// Energy cost per move
int Dialga::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 1;
        case 1: return 3;
        case 2: return 5;
        default: return 999;
    }
}

// Passive UI
string Dialga::getPassiveName() const {
    return "Temporal Mastery";
}

string Dialga::getPassiveDescription() const {
    return "Once per game, using a 3+ energy move skips opponent's next turn.";
}
