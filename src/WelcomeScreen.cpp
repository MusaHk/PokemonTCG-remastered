//
// Created by User on 5/25/2025.
//
#include "WelcomeScreen.h"
void WelcomeScreen::init_window() {
    InitWindow(screenX, screenY, "PokemonTCG++");
    screenTexture = LoadTexture("assets/images/gyradosWelcomeScreen.jpg");
    myFont = LoadFont("assets/fonts/Extrude-90aK.ttf");
}

void WelcomeScreen::init_music() {
    InitAudioDevice();
    screenMusic = LoadMusicStream("assets/audio/Route 209.mp3");
    PlayMusicStream(screenMusic);
}

void WelcomeScreen::while_window_open(){
    while (!WindowShouldClose()) {
        BeginDrawing();

        DrawTexture(screenTexture, 0, 0, WHITE);
        DrawTextEx(myFont, "PokemonTCG++", (Vector2){100, 100}, 200 , 2, DARKBLUE);

        UpdateMusicStream(screenMusic);
        EndDrawing();
    }
}

void WelcomeScreen::clear_music() const{
    StopMusicStream(screenMusic);
    UnloadMusicStream(screenMusic);
    CloseAudioDevice();
}

void WelcomeScreen::clear_window() const{
    UnloadTexture(screenTexture);
    UnloadFont(myFont);
    CloseWindow();
}

void WelcomeScreen::draw_button() {

}

void WelcomeScreen::when_button_clicked() {

}

void WelcomeScreen::clear_button() {

}
