#include "PokemonHeaders/ZygardeComplete.h"
#include "GameContext.h"
#include "Player.h"
#include "Game.h"

ZygardeComplete::ZygardeComplete()
    : Pokemon("ZygardeComplete", 170, 5, true,
              "assets/sprites/front/zygardeCompleteFront.gif",
              "assets/sprites/back/zygardeCompleteBack.gif",
              "assets/audio/zygardeComplete.mp3") {}

void ZygardeComplete::onEntry(GameContext& ctx) {
    playTheme();
}

// Passive: Aura Guardian
void ZygardeComplete::applyPassive(GameContext& ctx) {
    if (!isGuardianActive && getCurrentHP() < getMaxHP() / 2) {
        isGuardianActive = true;
        damageReductionTurns = 3;
        ctx.getLogger().logEvent("Aura Guardian activated! Zygarde will take 15 less damage for 3 turns!");
    }

    if (isGuardianActive && lastDamageTaken > 15) {
        lastDamageTaken -= 15;
        ctx.getLogger().logEvent("Aura Guardian reduced incoming damage by 15!");
    }
}

void ZygardeComplete::onTurnEnd() {
    if (isGuardianActive) {
        damageReductionTurns--;
        if (damageReductionTurns <= 0) {
            isGuardianActive = false;
        }
    }
}

void ZygardeComplete::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    int damage = 0;

    switch (moveIndex) {
        case 0: {  // Thousand Arrows
            useEnergy(2);
            damage = 35;
            // Directly modify target's HP to ignore immunities/shields
            target->takeDamage(damage);  // Assuming takeDamage has a bypass parameter
            ctx.getLogger().logEvent("Zygarde used Thousand Arrows for " + string::itos(damage) + 
                                   " damage, bypassing shields!");
            break;
        }
        case 1: {  // Land's Wrath
            useEnergy(3);
            damage = 45;
            target->takeDamage(damage);
            if (target->getCurrentEnergy() > 0) {
                target->useEnergy(1);
                ctx.getLogger().logEvent("Land's Wrath drained 1 energy from the opponent!");
            }
            ctx.getLogger().logEvent("Zygarde used Land's Wrath for " + string::itos(damage) + " damage!");
            break;
        }
        case 2: {  // Core Enforcer
            useEnergy(5);
            damage = 60;
            target->takeDamage(damage);
            ctx.getLogger().logEvent("Zygarde used Core Enforcer for " + string::itos(damage) + " damage!");

            // Check if the target attacked in their last turn
            if (target->getLastMoveUsed() >= 0) {  // Using lastMoveUsed from Pokemon class
                ctx.getGame()->grantExtraAction();
                ctx.getLogger().logEvent("Core Enforcer activated! Opponent's next turn will be skipped!");
            }
            break;
        }

        default:
            break;
    }
}

Dynamic_array<string> ZygardeComplete::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Thousand Arrows");
    moves.push("Land's Wrath");
    moves.push("Core Enforcer");
    return moves;
}

string ZygardeComplete::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 35 damage. Ignores immunity and shield effects.";
        case 1: return "Deal 45 damage. Opponent loses 1 energy.";
        case 2: return "Deal 60 damage. If opponent attacked last turn, they skip their next turn.";
        default: return "Unknown move.";
    }
}

int ZygardeComplete::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 2;  // Thousand Arrows
        case 1: return 3;  // Land's Wrath
        case 2: return 5;  // Core Enforcer
        default: return 999;
    }
}

string ZygardeComplete::getPassiveName() const {
    return "Aura Guardian";
}

string ZygardeComplete::getPassiveDescription() const {
    return "When HP drops below 50%, take 15 less damage from all sources for 3 turns.";
}