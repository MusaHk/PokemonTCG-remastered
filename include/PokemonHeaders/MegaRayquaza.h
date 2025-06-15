#ifndef MEGARAYQUAZA_H
#define MEGARAYQUAZA_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class MegaRayquaza final : public Pokemon {
private:
    bool defenseBreakUsed = false;
    int extremeSpeedUsesThisTurn = 0;

public:
    MegaRayquaza();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;

    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;

    void onTurnEnd();  // Reset Extreme Speed counter
    bool useDefenseBreak();  // Returns true if defense break was available
};

#endif // MEGARAYQUAZA_H