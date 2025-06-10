//
// Created by User on 6/10/2025.
//

#ifndef PASSIVEABILITY_H
#define PASSIVEABILITY_H
#include "String.h"

class GameContext;

class PassiveAbility {
protected:
    std::string name;
    std::string description;

public:
    PassiveAbility(const std::string& name, const std::string& description);
    virtual ~PassiveAbility() = default;

    virtual void onAttack(GameContext& context) = 0;
    virtual void onFaint(GameContext& context) = 0;
    virtual void onSwitch(GameContext& context) = 0;

    std::string getName() const;
    std::string getDescription() const;
};

#endif //PASSIVEABILITY_H
