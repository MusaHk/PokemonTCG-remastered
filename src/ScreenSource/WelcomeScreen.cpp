#include "ScreenHeaders/WelcomeScreen.h"

void WelcomeScreen::init(){
    background = LoadTexture("assets/images/gyradosWelcomeScreen.jpg");
    music = LoadMusicStream("assets/audio/Route 209.mp3");
    font = LoadFont("assets/fonts/Extrude-90aK.ttf");

    PlayMusicStream(music);

    newGameButton = { 100, 300, 400, 80 };
    loadSavedButton = { 100, 400, 400, 80 };
}

ScreenType WelcomeScreen::update() {
    UpdateMusicStream(music);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, newGameButton)) {
            return ScreenType::BATTLE;
        } else if (CheckCollisionPointRec(mouse, loadSavedButton)) {
            return ScreenType::LOAD_SAVED;
        }
    }
    return ScreenType::NONE;
}

void WelcomeScreen::draw(){
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(font, "PokemonTCG++", {100, 100}, 120, 2, DARKBLUE);

    DrawRectangleRec(newGameButton, LIGHTGRAY);
    DrawText("New Game", 110, 320, 40, BLACK);

    DrawRectangleRec(loadSavedButton, LIGHTGRAY);
    DrawText("Load Saved Game", 110, 420, 40, BLACK);

    EndDrawing();
}

void WelcomeScreen::cleanup(){
    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadTexture(background);
    UnloadFont(font);
}