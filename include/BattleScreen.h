//
// Created by User on 6/9/2025.
//
#ifndef BATTLESCREEN_H
#define BATTLESCREEN_H
#include "Screen.h"

class BattleScreen final: public Screen {
private:
    Rectangle ActivePokemon1{};
    Rectangle ActivePokemon2{};
public:
    void init() override;
    ScreenType update() override;
    void draw() override;
    void cleanup() override;
};
#endif //BATTLESCREEN_H
