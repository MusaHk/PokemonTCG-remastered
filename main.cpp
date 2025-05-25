#include "raylib.h"

int main() {
    const int screenWidth = 736;
    const int screenHeight = 920;

    InitWindow(screenWidth, screenHeight, "Pokemon Simulator");
    InitAudioDevice();
    Music music = LoadMusicStream("audio/giratina.mp3");
    PlayMusicStream(music);

    Texture2D welcomeTexture = LoadTexture("images/giratinaImage.jpg");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTexture(welcomeTexture, 0, 0, WHITE);
        ClearBackground(BLACK);
        UpdateMusicStream(music);
        DrawText("PokemonTCG++", 0, 0, 100, WHITE);
        EndDrawing();
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}