#ifndef ZYGARDECOMPLETE_H
#define ZYGARDECOMPLETE_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class ZygardeComplete final : public Pokemon {
private:
    int damageReductionTurns = 0;
    bool isGuardianActive = false;

public:
    ZygardeComplete();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;

    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;

    void onTurnEnd();  // Manage Guardian turns counter
    bool wasAttackedLastTurn = false;  // Track if attacked last turn
};

#endif // ZYGARDECOMPLETE_H