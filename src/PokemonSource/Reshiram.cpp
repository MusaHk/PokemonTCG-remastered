#include "PokemonHeaders/Reshiram.h"
#include "GameContext.h"
#include "Player.h"
#include "Game.h"

Reshiram::Reshiram()
    : Pokemon("Reshiram", 110, 5, false,
              "assets/sprites/front/reshiramFront.gif",
              "assets/sprites/back/reshiramBack.gif",
              "assets/audio/reshiram.mp3") {}

void Reshiram::onEntry(GameContext& ctx) {
    playTheme();
}

void Reshiram::applyPassive(GameContext& ctx) {
    // Blue Flare passive: +10 damage to all moves
    if (lastDamageTaken > 0) {
        lastDamageTaken += 10;
        ctx.getLogger().logEvent("Blue Flare adds +10 damage!");
    }
}

void Reshiram::onTurnEnd(GameContext& ctx) {
    if (burnTurnsRemaining > 0) {
        Pokemon* target = ctx.getDefender();
        target->takeDamage(10);
        ctx.getLogger().logEvent("Burn effect deals 10 damage!");
        burnTurnsRemaining--;
        
        if (burnTurnsRemaining == 0) {
            ctx.getLogger().logEvent("Burn effect wore off!");
        }
    }
}

void Reshiram::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    Player* current = ctx.getCurrentPlayer();
    int damage = 0;

    switch (moveIndex) {
        case 0: {  // Fusion Flare
            useEnergy(3);
            damage = 40;

            // Check if Zekrom is in the team
            bool hasZekrom = false;
            const Dynamic_array<Pokemon*>& team = current->getTeam();
            for (int i = 0; i < team.size(); ++i) {
                Pokemon* teammate = team[i];
                if (teammate && teammate->getName() == "Zekrom") {
                    hasZekrom = true;
                    break;
                }
            }

            if (hasZekrom) {
                damage += 20;
                ctx.getLogger().logEvent("Fusion Flare power increased due to Zekrom's presence!");
            }

            target->takeDamage(damage);
            ctx.getLogger().logEvent("Reshiram used Fusion Flare for " + string::itos(damage) + " damage!");
            break;
        }

        case 1: {  // Scorching Wind
            useEnergy(2);
            damage = 0;  // Initial damage is 0, damage comes from burn
            burnTurnsRemaining = 2;
            ctx.getLogger().logEvent("Reshiram used Scorching Wind! Target will take 10 damage for 2 turns!");
            break;
        }
        case 2: {  // Flame Charge
            useEnergy(1);
            gainEnergy(1);
            ctx.getLogger().logEvent("Reshiram used Flame Charge! Gained 1 bonus energy!");
            break;
        }
        default:
            break;
    }
}

Dynamic_array<string> Reshiram::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Fusion Flare");
    moves.push("Scorching Wind");
    moves.push("Flame Charge");
    return moves;
}

string Reshiram::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 40 damage. If Zekrom is on your team, deal +20 damage.";
        case 1: return "Burn opponent for 2 turns: +10 damage per turn.";
        case 2: return "Gain +1 bonus energy instantly.";
        default: return "Unknown move.";
    }
}

int Reshiram::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 3;  // Fusion Flare
        case 1: return 2;  // Scorching Wind
        case 2: return 1;  // Flame Charge
        default: return 999;
    }
}

string Reshiram::getPassiveName() const {
    return "Blue Flare";
}

string Reshiram::getPassiveDescription() const {
    return "All moves deal +10 extra damage.";
}