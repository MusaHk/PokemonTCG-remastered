#include "PokemonHeaders/Giratina.h"
#include "GameContext.h"
#include "Player.h"

Giratina::Giratina()
    : Pokemon("Giratina", 110, 5, false,
             "assets/sprites/front/giratinaFront.gif",
             "assets/sprites/back/giratinaBack.gif",
             "assets/audio/giratina.mp3") {}

void Giratina::onEntry(GameContext& ctx) {
    playTheme();
}

void Giratina::applyPassive(GameContext& ctx) {
    // Passive effect is handled in takeDamage
}

void Giratina::takeDamage(int amount, GameContext& context) {
    if (shadowForceActive) {
        context.getLogger().logEvent("Shadow Force protects Giratina from damage!");
        return;
    }

    // Distortion World: 10% chance to negate damage
    if (rand() % 10 == 0) {
        context.getLogger().logEvent("Distortion World negates the damage!");
        return;
    }

    Pokemon::takeDamage(amount, context);
}
void Giratina::takeDamage(int amount) {
    // filler.
}


void Giratina::onTurnEnd(GameContext& ctx) {
    shadowForceActive = false;
    
    if (chaosHowlTurnsLeft > 0) {
        chaosHowlTurnsLeft--;
        if (chaosHowlTurnsLeft == 0) {
            Pokemon* opponent = ctx.getDefender();
            opponent->modifyAttackDamage(0); // Reset attack reduction
            ctx.getLogger().logEvent("Chaos Howl's effect has worn off!");
        }
    }
}

void Giratina::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();

    switch (moveIndex) {
        case 0: { // Shadow Force
            useEnergy(3);
            int damage = 40;
            target->takeDamage(damage);
            shadowForceActive = true;
            ctx.getLogger().logEvent("Giratina used Shadow Force for " + string::itos(damage) + " damage!");
            ctx.getLogger().logEvent("Giratina vanishes into the shadows!");
            break;
        }
        case 1: { // Chaos Howl
            useEnergy(2);
            chaosHowlTurnsLeft = 2;
            target->modifyAttackDamage(-10);
            ctx.getLogger().logEvent("Giratina used Chaos Howl! Opponent's attack damage is reduced!");
            break;
        }
        case 2: { // Abyssal Drain
            useEnergy(4);
            int damage = 30;
            target->takeDamage(damage);
            heal(30);
            ctx.getLogger().logEvent("Giratina used Abyssal Drain for " + string::itos(damage) + " damage and healed 30 HP!");
            break;
        }
        default:
            break;
    }
}

Dynamic_array<string> Giratina::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Shadow Force");
    moves.push("Chaos Howl");
    moves.push("Abyssal Drain");
    return moves;
}

string Giratina::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 40 damage. Next turn, Giratina cannot take damage.";
        case 1: return "Lower opponent's attack damage by 10 for 2 turns.";
        case 2: return "Deal 30 damage and heal 30 HP.";
        default: return "Unknown move.";
    }
}

int Giratina::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 3;  // Shadow Force
        case 1: return 2;  // Chaos Howl
        case 2: return 4;  // Abyssal Drain
        default: return 999;
    }
}

string Giratina::getPassiveName() const {
    return "Distortion World";
}

string Giratina::getPassiveDescription() const {
    return "10% chance for an incoming move to deal no damage to Giratina.";
}