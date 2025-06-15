#ifndef DARKRAI_H
#define DARKRAI_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class Darkrai final : public Pokemon {
private:
    bool skipNextTurn = false;
    int disabledMoveIndex = -1;

public:
    Darkrai();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;

    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;

    void onTurnStart(GameContext& ctx);  // Reset disabled move
    void onTurnEnd();  // Reset status effects
};

#endif // DARKRAI_H