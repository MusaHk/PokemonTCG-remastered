#include "PokemonHeaders/MegaRayquaza.h"
#include "GameContext.h"
#include "Player.h"
#include "Game.h"

MegaRayquaza::MegaRayquaza()
    : Pokemon("MegaRayquaza", 160, 5, true,
              "assets/sprites/front/megaRayquazaFront.gif",
              "assets/sprites/back/megaRayquazaBack.gif",
              "assets/audio/megaRayquaza.mp3") {}

void MegaRayquaza::onEntry(GameContext& ctx) {
    playTheme();
}

// Passive: Delta Stream
void MegaRayquaza::applyPassive(GameContext& ctx) {
    // Damage reduction is handled in Pokemon::takeDamage
    // Defense break is handled through useDefenseBreak method
    if (lastDamageTaken > 10) {
        lastDamageTaken -= 10;
        ctx.getLogger().logEvent("Delta Stream reduced incoming damage by 10!");
    }
}

bool MegaRayquaza::useDefenseBreak() {
    if (!defenseBreakUsed) {
        defenseBreakUsed = true;
        return true;
    }
    return false;
}

void MegaRayquaza::onTurnEnd() {
    extremeSpeedUsesThisTurn = 0;
}

void MegaRayquaza::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    int damage = 0;

    switch (moveIndex) {
        case 0: {  // Dragon Ascent
            useEnergy(2);
            damage = 35;
            target->takeDamage(damage);
            takeDamage(10);  // Recoil damage
            ctx.getLogger().logEvent("MegaRayquaza used Dragon Ascent for " + string::itos(damage) + " damage!");
            ctx.getLogger().logEvent("MegaRayquaza took 10 recoil damage.");
            break;
        }
        case 1: {  // Extreme Speed
            if (extremeSpeedUsesThisTurn >= 2) {
                ctx.getLogger().logEvent("Extreme Speed cannot be used more than twice per turn!");
                break;
            }
            useEnergy(1);
            damage = 25;
            target->takeDamage(damage);
            ctx.getLogger().logEvent("MegaRayquaza used Extreme Speed for " + string::itos(damage) + " damage!");
            ctx.getGame()->grantExtraAction();
            extremeSpeedUsesThisTurn++;
            break;
        }
        case 2: {  // Sky Pillar Descent
            useEnergy(5);
            damage = 60;
            Dynamic_array<Pokemon*>& team = opponent->getTeam();
            for (int i = 0; i < team.size(); i++) {
                Pokemon* mon = team[i];
                mon->takeDamage(damage);
            }
            ctx.getLogger().logEvent("MegaRayquaza unleashed Sky Pillar Descent for " + 
                                   string::itos(damage) + " damage to all enemies!");
            break;
        }
        default:
            break;
    }
}

Dynamic_array<string> MegaRayquaza::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Dragon Ascent");
    moves.push("Extreme Speed");
    moves.push("Sky Pillar Descent");
    return moves;
}

string MegaRayquaza::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 35 damage. Recoil: Rayquaza takes 10 damage.";
        case 1: return "Deal 25 damage. Acts immediately after opponent's next turn. Max twice per turn.";
        case 2: return "Deal 60 damage to all enemy Pokemon.";
        default: return "Unknown move.";
    }
}

int MegaRayquaza::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 2;  // Dragon Ascent
        case 1: return 1;  // Extreme Speed
        case 2: return 5;  // Sky Pillar Descent
        default: return 999;
    }
}

string MegaRayquaza::getPassiveName() const {
    return "Delta Stream";
}

string MegaRayquaza::getPassiveDescription() const {
    return "All moves deal 10 less damage to Rayquaza. Once per battle, can ignore all opponent defense effects.";
}