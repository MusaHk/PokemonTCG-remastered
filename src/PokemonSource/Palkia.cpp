#include "PokemonHeaders/Palkia.h"
#include "GameContext.h"
#include "Player.h"

Palkia::Palkia()
    : Pokemon("Palkia", 110, 5, false,
              "assets/sprites/front/palkiaFront.gif",
              "assets/sprites/back/palkiaBack.gif",
              "assets/audio/palkia.mp3") {}

void Palkia::onEntry(GameContext& ctx) {
    playTheme();
}

void Palkia::applyPassive(GameContext& ctx) {
    // Passive effect is handled in takeDamage
}

void Palkia::takeDamage(int amount) {
    // Spatial Shift: reduce incoming damage by 5
    if (amount > 0) {
        amount = std::max(0, amount - 5);
    }
    Pokemon::takeDamage(amount);
}

bool Palkia::canUseMove(int moveIndex) const {
    int cost = getMoveCost(moveIndex);
    if (energyReduction > 0) {
        cost = (cost > energyReduction) ? cost - energyReduction : 0;
    }
    return getCurrentEnergy() >= cost;
}

void Palkia::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    Player* current = ctx.getCurrentPlayer();
    int actualCost = getMoveCost(moveIndex);

    if (energyReduction > 0) {
        actualCost = (actualCost > energyReduction) ? actualCost - energyReduction : 0;
        energyReduction = 0;  // Reset the reduction after use
    }

    switch (moveIndex) {
        case 0: { // Spacial Rend
            useEnergy(actualCost);
            int damage = 40;
            target->takeDamage(damage);
            ctx.getLogger().logEvent("Palkia used Spacial Rend for " + string::itos(damage) + " damage!");

            // 50% chance to get another turn
            if (rand() % 2 == 0) {
                ctx.getLogger().logEvent("Spacial Rend creates a time distortion! Palkia gets another turn!");
                current->grantExtraTurn();  // Using the new method
            }
            break;
        }
        case 1: { // Aqua Warp
            useEnergy(actualCost);
            int damage = 20;
            target->takeDamage(damage);
            ctx.getLogger().logEvent("Palkia used Aqua Warp for " + string::itos(damage) + " damage!");

            // Switch with a benched Pokemon
            const Dynamic_array<Pokemon*>& team = current->getTeam();
            for (int i = 0; i < team.size(); ++i) {
                Pokemon* teammate = team[i];
                if (teammate && !teammate->isFainted() && teammate != this) {
                    current->switchPokemon(i);
                    ctx.getLogger().logEvent("Palkia warped back to the bench!");
                    break;
                }
            }
            break;
        }
        case 2: { // Dimension Fold
            useEnergy(actualCost);
            energyReduction = 2;  // Set the reduction amount
            ctx.getLogger().logEvent("Palkia used Dimension Fold! Next move's energy cost is reduced by 2!");
            break;
        }
        default:
            break;
    }
}


Dynamic_array<string> Palkia::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Spacial Rend");
    moves.push("Aqua Warp");
    moves.push("Dimension Fold");
    return moves;
}

string Palkia::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 40 damage. 50% chance to get another turn.";
        case 1: return "Deal 20 damage. Switch with a benched Pokemon.";
        case 2: return "Your next move's energy cost is reduced by 2.";
        default: return "Unknown move.";
    }
}

int Palkia::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 3;  // Spacial Rend
        case 1: return 2;  // Aqua Warp
        case 2: return 4;  // Dimension Fold
        default: return 999;
    }
}

string Palkia::getPassiveName() const {
    return "Spatial Shift";
}

string Palkia::getPassiveDescription() const {
    return "Takes 5 less damage from any incoming move.";
}