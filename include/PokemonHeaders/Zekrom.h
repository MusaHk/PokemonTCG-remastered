#ifndef ZEKROM_H
#define ZEKROM_H

#include "Pokemon.h"
#include "Dynamic_array.h"
#include "String.h"

class Zekrom final : public Pokemon {
private:
    bool lastMoveWasVoltCrash = false;
    bool powerSurgeActive = false;
    void applyFusionBolt(GameContext& ctx); // New helper method

public:
    Zekrom();

    void onEntry(GameContext& ctx) override;
    void applyPassive(GameContext& ctx) override;
    void applyMove(int moveIndex, GameContext& ctx) override;
    
    Dynamic_array<string> getMoveNames() const override;
    string getMoveDescription(int moveIndex) const override;
    int getMoveCost(int moveIndex) const override;

    string getPassiveName() const override;
    string getPassiveDescription() const override;
};

#endif // ZEKROM_H