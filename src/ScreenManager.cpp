//
// Created by User on 6/9/2025.
//
#include "ScreenManager.h"
#include "BattleScreen.h"

void ScreenManager::set_screen(Screen* newScreen) {
    if (currentScreen) {
        currentScreen->cleanup();
        delete currentScreen;
    }
    currentScreen = newScreen;
    currentScreen->init();
}
void ScreenManager::update() {
    if (currentScreen) {
        ScreenType next = currentScreen->update();

        switch (next) {
            case ScreenType::BATTLE:
                set_screen(new BattleScreen());
                break;
            case ScreenType::LOAD_SAVED:
                // TODO: implement loading later
                break;
            default:
                break;
        }
    }
}



void ScreenManager::draw() {
    if (currentScreen) currentScreen->draw();
}

void ScreenManager::cleanup() {
    if (currentScreen) {
        currentScreen->cleanup();
        delete currentScreen;
        currentScreen = nullptr;
    }
}