//
// Created by User on 6/9/2025.
//

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.h"
#include "Game.h"

class ScreenManager {
private:
    Screen* currentScreen = nullptr;
    Game* game = nullptr;
public:
    void set_screen(Screen* newScreen);
    void update();
    void draw();
    void cleanup();
};
#endif //SCREENMANAGER_H