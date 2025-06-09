//
// Created by User on 6/9/2025.
//
#include "BattleScreen.h"

void BattleScreen::init() {
    InitWindow(screenX, screenY, "Battle");
    InitAudioDevice();
    background = LoadTexture("assets/images/BattleScreenClouds.jpg");
    music = LoadMusicStream("assets/audio/giratina.mp3");
    font = LoadFont("assets/fonts/Extrude-90aK.ttf");

    PlayMusicStream(music);
}

void BattleScreen::draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITE);
    EndDrawing();
}

ScreenType BattleScreen::update() {
    UpdateMusicStream(music);
    return ScreenType::NONE;
}

void BattleScreen::cleanup() {
    StopMusicStream(music);
    UnloadMusicStream(music);
    UnloadTexture(background);
    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();
}
