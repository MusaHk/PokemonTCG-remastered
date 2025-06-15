#ifndef ULTRANECROZMA_H
#define ULTRANECROZMA_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class UltraNecrozma final : public Pokemon {
public:
    UltraNecrozma();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;

    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;
};

#endif // ULTRANECROZMA_H