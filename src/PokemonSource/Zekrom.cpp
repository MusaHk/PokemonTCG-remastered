#include "PokemonHeaders/Zekrom.h"
#include "GameContext.h"
#include "Player.h"

Zekrom::Zekrom()
    : Pokemon("Zekrom", 110, 5, false,
              "assets/sprites/front/zekromFront.gif",
              "assets/sprites/back/zekromBack.gif",
              "assets/audio/zekrom.mp3") {}

void Zekrom::onEntry(GameContext& ctx) {
    playTheme();
}

void Zekrom::applyPassive(GameContext& ctx) {
    Pokemon* opponent = ctx.getDefender();
    if (getCurrentEnergy() < opponent->getCurrentEnergy()) {
        gainEnergy(1); // Extra energy on top of the base +1
        ctx.getLogger().logEvent("Black Current grants +1 extra energy!");
    }
}

void Zekrom::applyFusionBolt(GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    Player* current = ctx.getCurrentPlayer();
    int damage = 40;

    // Check if Reshiram is in the team
    bool hasReshiram = false;
    const Dynamic_array<Pokemon*>& team = current->getTeam();
    for (int i = 0; i < team.size(); ++i) {
        Pokemon* teammate = team[i];
        if (teammate && teammate->getName() == "Reshiram") {
            hasReshiram = true;
            break;
        }
    }

    if (hasReshiram) {
        damage += 20;
        ctx.getLogger().logEvent("Fusion Bolt power increased due to Reshiram's presence!");
    }

    if (powerSurgeActive) {
        damage *= 2;
        powerSurgeActive = false;
        ctx.getLogger().logEvent("Power Surge doubles the damage!");
    }

    target->takeDamage(damage);
    ctx.getLogger().logEvent("Zekrom used Fusion Bolt for " + string::itos(damage) + " damage!");
}

void Zekrom::applyMove(int moveIndex, GameContext& ctx) {
    Player* opponent = ctx.getOpponent();
    Pokemon* target = opponent->getActivePokemon();
    int damage = 0;

    switch (moveIndex) {
        case 0: { // Fusion Bolt
            useEnergy(3);
            applyFusionBolt(ctx);
            lastMoveWasVoltCrash = false;
            break;
        }
        case 1: { // Volt Crash
            if (lastMoveWasVoltCrash) {
                ctx.getLogger().logEvent("Cannot use Volt Crash twice in a row!");
                return;
            }

            useEnergy(2);
            damage = 20;

            if (powerSurgeActive) {
                damage *= 2;
                powerSurgeActive = false;
                ctx.getLogger().logEvent("Power Surge doubles the damage!");
            }

            target->takeDamage(damage);
            ctx.getLogger().logEvent("Zekrom used Volt Crash for " + string::itos(damage) + " damage!");

            // 25% chance to chain into Fusion Bolt
            if (rand() % 4 == 0) {
                ctx.getLogger().logEvent("Volt Crash chains into Fusion Bolt!");
                lastMoveWasVoltCrash = false;
                if (getCurrentEnergy() >= 3) {  // Check if we have enough energy
                    useEnergy(3);
                    applyFusionBolt(ctx);
                }
            } else {
                lastMoveWasVoltCrash = true;
            }
            break;
        }
        case 2: { // Power Surge
            useEnergy(1);
            powerSurgeActive = true;
            ctx.getLogger().logEvent("Zekrom used Power Surge! Next attack will deal double damage!");
            lastMoveWasVoltCrash = false;
            break;
        }
        default:
            break;
    }
}

Dynamic_array<string> Zekrom::getMoveNames() const {
    Dynamic_array<string> moves;
    moves.push("Fusion Bolt");
    moves.push("Volt Crash");
    moves.push("Power Surge");
    return moves;
}

string Zekrom::getMoveDescription(int moveIndex) const {
    switch (moveIndex) {
        case 0: return "Deal 40 damage. If Reshiram is on your team, deal +20 damage.";
        case 1: return "Deal 20 damage. 25% chance to use another move. Cannot be used twice in a row.";
        case 2: return "Double your next attack's damage.";
        default: return "Unknown move.";
    }
}

int Zekrom::getMoveCost(int moveIndex) const {
    switch (moveIndex) {
        case 0: return 3;  // Fusion Bolt
        case 1: return 2;  // Volt Crash
        case 2: return 1;  // Power Surge
        default: return 999;
    }
}

string Zekrom::getPassiveName() const {
    return "Black Current";
}

string Zekrom::getPassiveDescription() const {
    return "If Zekrom has less energy than opponent, it gains +2 energy per turn.";
}