#include "WelcomeScreen.h"

void WelcomeScreen::init(){
    InitWindow(screenX, screenY, "PokemonTCG++");
    InitAudioDevice();

    background = LoadTexture("assets/images/gyradosWelcomeScreen.jpg");
    music = LoadMusicStream("assets/audio/Route 209.mp3");
    font = LoadFont("assets/fonts/Extrude-90aK.ttf");

    PlayMusicStream(music);

    newGameButton = { 100, 300, 400, 80 };
    loadSavedButton = { 100, 400, 400, 80 };
}

void WelcomeScreen::update(){
    UpdateMusicStream(music);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, newGameButton)) {
            // TODO: transition to BattlePrep screen
        }
        else if (CheckCollisionPointRec(mouse, loadSavedButton)) {
            // TODO: load saved binary file
        }
    }
}

void WelcomeScreen::draw(){
    BeginDrawing();
    ClearBackground(RAYWHITE);

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
    CloseAudioDevice();
    CloseWindow();
}