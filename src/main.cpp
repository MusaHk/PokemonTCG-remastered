#include "ScreenHeaders/ScreenManager.h"
#include "ScreenHeaders/WelcomeScreen.h"
int main() {
    InitWindow(1920, 1180, "PokemonTCG++");
    InitAudioDevice();

    ScreenManager manager;
    manager.set_screen(new WelcomeScreen());

    while (!WindowShouldClose()) {
        manager.update();
        manager.draw();
    }
    manager.cleanup();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}