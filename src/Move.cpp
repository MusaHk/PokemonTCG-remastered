//
// Created by User on 6/10/2025.
//
#include "Move.h"

Move::Move(const std::string& name, const std::string& description, int energyCost, int damage)
    : name(name), description(description), energyCost(energyCost), damage(damage) {}

std::string Move::getName() const { return name; }
std::string Move::getDescription() const { return description; }
int Move::getEnergyCost() const { return energyCost; }
int Move::getDamage() const { return damage; }