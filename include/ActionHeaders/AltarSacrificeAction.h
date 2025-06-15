#ifndef ALTARSACRIFICEACTION_H
#define ALTARSACRIFICEACTION_H

#include "Action.h"

class AltarSacrificeAction final: public Action {
private:
    int optionID;  // 0…7

public:
    explicit AltarSacrificeAction(int optionID);
    void execute(GameContext& context) override;
};

#endif // ALTARSACRIFICEACTION_H
