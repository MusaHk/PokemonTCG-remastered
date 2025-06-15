#ifndef ATTACKACTION_H
#define ATTACKACTION_H

#include "Action.h"

class AttackAction final: public Action {
private:
    int moveIndex;

public:
    explicit AttackAction(int moveIndex);
    void execute(GameContext& context) override;
};

#endif // ATTACKACTION_H