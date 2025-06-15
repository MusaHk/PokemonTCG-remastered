#include "UltraNecrozma.h"
#include "GameContext.h"
#include "Player.h"

UltraNecrozma::UltraNecrozma()
    : Pokemon("UltraNecrozma", 160, 5, true,
              "assets/sprites/front/ultraNecrozmaFront.gif",
              "assets/sprites/back/ultraNecrozmaBack.gif",
              "assets/audio/ultraNecrozma.mp3") {}

// Passive: Radiant Overflow
void UltraNecrozma::applyPassive(GameContext& ctx) {
    if (getCurrentHP() < getMaxHP() / 2) {
        gainEnergy(1);  // Bonus +1 energy if HP < 50%
    }
}

void UltraNecrozma::onEntry(GameContext& ctx) {
    playTheme();
}

void UltraNecrozma::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    int damage = 0;

    if (moveIndex == 0) {  // Prismatic Slash
        useEnergy(1);
        damage = 20;
        if (getCurrentEnergy() > target->getCurrentEnergy()) {
            damage += 10;
        }
        target->takeDamage(damage);
    } else if (moveIndex == 1) {  // Light Devourer
        useEnergy(3);
        damage = 40;
        target->takeDamage(damage);
        if (target->getCurrentEnergy() > 0) {
            target->useEnergy(1);
            gainEnergy(1);
        }
    } else if (moveIndex == 2) {  // Light That Burns the Sky
        useEnergy(5);
        // Deal 60 to all opponents (just one for now)
        target->takeDamage(60);
        takeDamage(10); // self-damage
        currentEnergy = 0; // Lose all energy
    }
}

Dynamic_array<string> UltraNecrozma::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Prismatic Slash");
    moves.push("Light Devourer");
    moves.push("Light That Burns the Sky");
    return moves;
}

string UltraNecrozma::getMoveDescription(int moveIndex) const {
    if (moveIndex == 0) {
        return "Deal 20 damage. If you have more energy than the opponent, deal +10.";
    } else if (moveIndex == 1) {
        return "Deal 40 damage and steal 1 energy.";
    } else if (moveIndex == 2) {
        return "Deal 60 to all enemies. Lose all energy and take 10 self-damage.";
    }
    return "Unknown move.";
}

int UltraNecrozma::getMoveCost(int moveIndex) const {
    if (moveIndex == 0) return 1;
    if (moveIndex == 1) return 3;
    if (moveIndex == 2) return 5;
    return 999; // invalid energy.
}

string UltraNecrozma::getPassiveName() const {
    return "Radiant Overflow";
}

string UltraNecrozma::getPassiveDescription() const {
    return "If below 50% HP, gain +1 bonus energy per turn.";
}