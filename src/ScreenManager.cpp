//
// Created by User on 6/9/2025.
//
#include "ScreenManager.h"
#include "BattlePrepScreen.h"

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
        switch (ScreenType next = currentScreen->update()) {
            case ScreenType::BATTLE_PREP:
                set_screen(new BattlePrepScreen());
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