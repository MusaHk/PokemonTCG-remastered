#ifndef RESHIRAM_H
#define RESHIRAM_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class Reshiram final : public Pokemon {
private:
    int burnTurnsRemaining = 0;

public:
    Reshiram();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;
    
    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;

    void onTurnEnd(GameContext& ctx);  // Handle burn effect
};

#endif // RESHIRAM_H