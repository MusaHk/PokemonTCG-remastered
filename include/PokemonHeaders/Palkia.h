#ifndef PALKIA_H
#define PALKIA_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class Palkia final : public Pokemon {
private:
    int energyReduction = 0;  // Changed from bool to int to track the reduction amount

public:
    Palkia();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;
    bool canUseMove(int moveIndex) const override;
    
    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;

    void takeDamage(int amount) override;
};

#endif // PALKIA_H