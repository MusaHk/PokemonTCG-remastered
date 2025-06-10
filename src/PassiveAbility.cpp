//
// Created by User on 6/10/2025.
//
#include "PassiveAbility.h"

PassiveAbility::PassiveAbility(const std::string& name, const std::string& description)
    : name(name), description(description) {}

std::string PassiveAbility::getName() const { return name; }
std::string PassiveAbility::getDescription() const { return description; }