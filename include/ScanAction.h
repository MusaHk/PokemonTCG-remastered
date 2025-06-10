#ifndef SCANACTION_H
#define SCANACTION_H

#include "Action.h"

class ScanAction final: public Action {
public:
    void execute(GameContext& context) override;
};

#endif // SCANACTION_H
