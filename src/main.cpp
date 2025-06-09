#include "ScreenManager.h"
#include "WelcomeScreen.h"

int main() {
    ScreenManager manager;
    manager.set_screen(new WelcomeScreen());

    while (!WindowShouldClose()) {
        manager.update();
        manager.draw();
    }

    manager.cleanup();
    return 0;
}
