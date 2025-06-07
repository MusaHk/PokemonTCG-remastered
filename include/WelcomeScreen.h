//
// Created by User on 5/25/2025.
//

#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include "Screen.h"

class WelcomeScreen final: public Screen  {
private:
    Rectangle newGameButton{};
    Rectangle loadSavedButton{};
public:
    void init() override;
    void update() override;
    void draw() override;
    void cleanup() override;
};
#endif //WELCOMESCREEN_H
