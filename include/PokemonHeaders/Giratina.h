#ifndef GIRATINA_H
#define GIRATINA_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class Giratina final : public Pokemon {
private:
    bool shadowForceActive = false;
    int chaosHowlTurnsLeft = 0;
    int attackReduction = 0;

public:
    Giratina();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;
    
    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;
    void takeDamage(int amount, GameContext& context) override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;

    void takeDamage(int amount) override;
    void onTurnEnd(GameContext& ctx) override;
};

#endif // GIRATINA_H