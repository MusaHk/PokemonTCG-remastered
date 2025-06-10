//
// Created by User on 6/10/2025.
//

#ifndef MOVE_H
#define MOVE_H
#include "String.h"

class GameContext;

class Move {
protected:
    std::string name;
    std::string description;
    int energyCost;
    int damage;

public:
    Move(const std::string& name, const std::string& description, int energyCost, int damage);
    virtual ~Move() = default;

    virtual void apply(GameContext& context) = 0;

    std::string getName() const;
    std::string getDescription() const;
    int getEnergyCost() const;
    int getDamage() const;
};

#endif //MOVE_H