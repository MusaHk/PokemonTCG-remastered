//
// Created by User on 6/9/2025.
//
#include "BattlePrepScreen.h"

void BattlePrepScreen::init() {
    background = LoadTexture("assets/images/pikachuBattlePrepScreen.jpg");
}

ScreenType BattlePrepScreen::update() {
    return ScreenType::NONE;
}


void BattlePrepScreen::draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITE);
    DrawText("Preparing for Battle...", 100, 100, 40, GREEN);
    EndDrawing();
}

void BattlePrepScreen::cleanup() {
    UnloadTexture(background);
}
