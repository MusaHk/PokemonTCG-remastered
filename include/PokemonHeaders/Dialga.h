#ifndef DIALGA_H
#define DIALGA_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class Dialga final : public Pokemon {
public:
    Dialga();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;

    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;
};

#endif // DIALGA_H