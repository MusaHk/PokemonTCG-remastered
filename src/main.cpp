#include "WelcomeScreen.h"

int main() {
    Screen* currentScreen = new WelcomeScreen();

    currentScreen->init();

    while (!WindowShouldClose()) {
        currentScreen->update();
        currentScreen->draw();
    }

    currentScreen->cleanup();
    delete currentScreen;

    return 0;
}
