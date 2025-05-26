//
// Created by User on 5/25/2025.
//
#include "WelcomeScreen.h"
void WelcomeScreen::init_window() {
    InitWindow(screenX, screenY, "PokemonTCG++");
    screenTexture = LoadTexture("images/giratinaImage.jpg");
}

void WelcomeScreen::init_music() {
    InitAudioDevice();
    screenMusic = LoadMusicStream("audio/giratina.mp3");
    PlayMusicStream(screenMusic);
}

void WelcomeScreen::while_window_open() const{
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTexture(screenTexture, 0, 0, WHITE);
        UpdateMusicStream(screenMusic);
        DrawText("PokemonTCG++", 0, 0, 80, PURPLE);
        EndDrawing();
    }
}

void WelcomeScreen::clear_music() const{
    UnloadMusicStream(screenMusic);
    StopMusicStream(screenMusic);
    CloseAudioDevice();
}

void WelcomeScreen::clear_window() const{
    UnloadTexture(screenTexture);
    CloseWindow();
}

void WelcomeScreen::draw_button() {

}

void WelcomeScreen::when_button_clicked() {

}

void WelcomeScreen::clear_button() {

}
