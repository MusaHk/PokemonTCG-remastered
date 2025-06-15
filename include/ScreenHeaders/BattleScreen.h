#ifndef BATTLESCREEN_H
#define BATTLESCREEN_H

#include "Screen.h"
#include "Game.h"
#include "raylib.h"

class BattleScreen final : public Screen {
private:
    Game* game;

    // Background & audio
    Texture2D background;
    Music     music;
    Font      font;

    // Player 1 (back-view) GIF animation
    Image     gifImageP1;
    Texture2D gifTexP1;
    int       gifFramesP1;
    int       currentFrameP1;
    float     frameTimerP1;
    float     frameDelayP1;

    // Player 2 (front-view) GIF animation
    Image     gifImageP2;
    Texture2D gifTexP2;
    int       gifFramesP2;
    int       currentFrameP2;
    float     frameTimerP2;
    float     frameDelayP2;

public:
     explicit BattleScreen(Game* game);
    ~BattleScreen() override = default;

    void init() override;
    ScreenType update() override;
    void draw() override;
    void cleanup() override;
};

#endif // BATTLESCREEN_H
