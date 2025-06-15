#ifndef ACTION_H
#define ACTION_H

#include "GameContext.h"

class Action {
public:
    virtual ~Action() = default;
    virtual void execute(GameContext& context) = 0;
};

#endif // ACTION_H

