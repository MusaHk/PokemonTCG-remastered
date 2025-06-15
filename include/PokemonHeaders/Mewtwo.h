#ifndef MEWTWO_H
#define MEWTWO_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class Mewtwo final : public Pokemon {
private:
    bool psychicWallActive = false;

public:
    Mewtwo();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;

    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;

    void onTurnEnd();  // Reset Psychic Wall if needed
};

#endif // MEWTWO_H