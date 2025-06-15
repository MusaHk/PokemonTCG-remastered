#include "ActionHeaders/AltarSacrificeAction.h"
#include "Player.h"
#include "GameContext.h"

AltarSacrificeAction::AltarSacrificeAction(int optionID)
    : optionID(optionID) {}

void AltarSacrificeAction::execute(GameContext& context) {
    Player* p = context.getCurrentPlayer();
    if (p->getAltarCharges() <= 0) return;
    p->useAltarCharge();
    Pokemon* active = p->getActivePokemon();

    switch (optionID) {
        case 0: { // Full Restoration
            // Heal to max HP
            int hpToHeal = active->getMaxHP() - active->getCurrentHP();
            if (hpToHeal > 0) active->heal(hpToHeal);
            // Restore energy to max
            int energyToGain = active->getMaxEnergy() - active->getCurrentEnergy();
            if (energyToGain > 0) active->gainEnergy(energyToGain);
            break;
        }
        case 1: { // Revive & Empower
            Dynamic_array<Pokemon*>& team = p->getTeam();
            for (int i = 0; i < team.size(); ++i) {
                Pokemon* mon = team[i];
                if (mon->isFainted()) {
                    // Revive at 50% HP and energy
                    int reviveHP = mon->getMaxHP() / 2;
                    mon->heal(reviveHP);
                    int reviveEnergy = mon->getMaxEnergy() / 2;
                    mon->gainEnergy(reviveEnergy);
                    // Switch to this Pokémon
                    p->switchPokemon(team.find(mon));
                    break;
                }
            }
            break;
        }
        case 2: { // Divine Surge
            active->gainEnergy(3);
            break;
        }
        case 3: { // Purifying Light (stub)
            // TODO: clear statuses in subclass-specific code
            break;
        }
            // cases 4–7 require Game methods not yet implemented
        default:
            break;
    }
}