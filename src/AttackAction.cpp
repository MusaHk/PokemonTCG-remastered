#include "AttackAction.h"
#include "Player.h"
#include "GameContext.h"

AttackAction::AttackAction(int moveIndex)
    : moveIndex(moveIndex) {}

void AttackAction::execute(GameContext& context) {
    // Attacker uses its move
    Pokemon* attacker = context.getAttacker();
    if (attacker->canUseMove(moveIndex)) {
        attacker->applyMove(moveIndex, context);
        attacker->applyPassive(context);
        Pokemon* defender = context.getDefender();
        defender->applyPassive(context);
        // Handle KO & Altar charges
        if (defender->isFainted()) {
            Player* current = context.getCurrentPlayer();
            current->gainAltarCharge(defender->getIsEX() ? 2 : 1);
            current->onPokemonFainted();
        }
    }
}