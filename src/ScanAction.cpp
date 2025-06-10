#include "ScanAction.h"
#include "Player.h"
#include "GameContext.h"
#include "String.h"

static string intToString(int x) {
    return string::itos(x);
}

void ScanAction::execute(GameContext& context) {
    Player* current = context.getCurrentPlayer();
    if (!current->hasUsedPokedex()) {
        current->setUsedPokedex(true);
        Pokemon* defender = context.getDefender();

        {
            string msg = string("Scan: Opponent's active Pokemon: ") + defender->getName();
            context.getLogger().logEvent(msg);
        }

        Dynamic_array<string> moves = defender->getMoveNames();
        for (int i = 0; i < moves.size(); ++i) {
            string idx = intToString(i);

            // Build "Move <i>: <name> - <description>"
            string msg = string("Move ") + idx + string(": ")
                       + moves[i] + string(" - ")
                       + defender->getMoveDescription(i);

            context.getLogger().logEvent(msg);
        }

        {
            string msg = string("Passive: ")
                       + defender->getPassiveName()
                       + string(" - ")
                       + defender->getPassiveDescription();

            context.getLogger().logEvent(msg);
        }
    }
}