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
    if (!currentScreen) return;

    ScreenType next = currentScreen->update();

    if (next == ScreenType::NONE) return;

    switch (next) {
        case ScreenType::BATTLE: {
            if (!game) {
                Dynamic_array<Pokemon*> pool;
                Player* p1 = new Player(pool);
                Player* p2 = new Player(pool);
                game = new Game(p1, p2);
            }
            std::cout << "Switching to BattleScreen\n";
            set_screen(new BattleScreen(game));
            break;
        }
        case ScreenType::LOAD_SAVED: {
            // TODO: implement loading later.
            break;
        }
        default:
            break;
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
    if (game) {
        delete game;
        game = nullptr;
    }
}